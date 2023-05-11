#include "mom.hpp"

Mom::
Mom(char* process, int port) : table(JobTable()), process(process), port(port), server(Socket(process)) {
    banner();
}

// main driver of the Mom class
// sets up the welcome socket for clients to connect
// calls startPolling() to start the main polling loop
void Mom::
startServer(){
	gethostname(hostname, 242);			// get name of local host.
	cout <<"server is " << hostname <<endl;

	// Socket class call to start listening on the port
    server.listen(port); 
    int welcomeFD = server.sockfd();

	// assign welcome socket information
    welcome->fd = welcomeFD;
    welcome->events = POLLIN; // lets socket listen to clients

    printf("Opened socket as fd (%d) on port (%d) for stream i/o\n",
		   welcomeFD, ntohs(server.port()));
	cout << "welcome" << server;

    startPolling();
}

// main polling loop
// uses abstractions doWelcome() and doService() to do associated events
// When the timer finishes, exit the polling loop and count each kid's allowance
void Mom::
startPolling(){
    int status = 0;
	int bytes;
	sockStat ACK = sockStat::ACK;

	char greeting[284];
	sprintf(greeting, "Connected to (%s.%d)\n", hostname, port);

    for (;;) {
		status = poll(userFDs, 1 + currentClients, -1);

		if (status < 0)  fatalp("Error in poll().\t");
		if (status == 0) sayp("%s: poll timed out\t", process);


		// If welcome socket has a caller, service it.
		if (welcome->revents != 0 )	{
			if (welcome->revents & POLLIN)	{
				if (currentClients < MAXCLIENTS) // create a new client connection.
					currentClients += doWelcome(welcome->fd, &currentClients, worker, greeting);
            }
            else fatalp("Error involving welcome mat: %d", welcome->revents);
		}

		// Scan the working sockets and process whatever tasks you find
		// only execute if there is enough clients connected and if the timer is done
		// if the timer is done, doService handles sending QUIT to the client
		if (currentClients >= MAXCLIENTS || isTimerFinished()){
			// start the timer only when all clients are connected
			if (startTime == 0) { startTimer(); cout << "Start Time: " << startTime << endl; }
			
			short k;
			for (k = 0; k < currentClients; k++) {
				if (worker[k].revents != 0) {
					status = doService( &worker[k], k+1 ); // main server function
					if ( status == -1 ){		// remove socket from the list

						// tell client to stop
						cout << "Stopping Socket" << endl;
						status = sockStat::QUIT;
						bytes = write(worker[k].fd, &status, sizeof(status) );
						if (bytes < 1) { fatalp("Failed to write to socket"); }

						// decrement # of workers
						worker[k] = worker[--currentClients];		
					}
					else {	// let client know to keep going
						ACK = sockStat::ACK;
						bytes = write(worker[k].fd, &ACK, sizeof(ACK) );
						if (bytes < 1) { fatalp("Failed to write to socket"); }
					}
				}
			}
		}
		else {
			cout << "Not enough clients" << endl;
		}

		// if the timer is done and all connections are terminated, leave the polling loop
		if (isTimerFinished() && currentClients == 0) {
			cout << "My timer is done!" << endl;
			break;
		}

		// stop looking for new clients if max has been reached
		// prevents new connections from comming in
		welcome->events = (currentClients < MAXCLIENTS) ? POLLIN : 0;
	}	// ENDLOOP

	cout << "~End of Polling Loop~" << endl;

	countAllowance();
}


// implementation of socket welcoming
// accepts new connections from the welcome socket, sends an SYN ACK to confirm connection
// finally adds connection to worker array
int Mom::
doWelcome(int welcomeSock, int* nClip, toPoll* worker, const char* greeting){
	int nCli = *nClip;	// Make a local copy of the in/out parameter
	sockaddr_in newCaller;
	socklen_t sockLen = sizeof(newCaller);
	
	int newfd = accept(welcomeSock, (sockaddr*) &newCaller, &sockLen);
	if (newfd < 0) {
		cout <<"False alarm: packet was rejected.\n";
		return 0;  // False alarm, nobody there, 0 new clients.
	}

	printsockaddr_in("working--from newCaller", newCaller);  // same as getpeername
	
	// We have a new caller -- send an ack.
	int buf[2];
	buf[0] = sockStat::ACK; // acknowledgment for client
	buf[1] = nCli+1; // kid ID
	int bytes = write(newfd, &buf, sizeof(buf)); // write the ACK
	if (bytes < 1) say("Error while writing to socket");

	// checks if client is okay
	int nBytes = read( newfd, buf, sizeof buf );
	if (nBytes > 0){
		if ((sockStat)buf[0] == sockStat::ACK) cout << "Client Has Sent ACK" << endl;
		else { cout << "Client Has Not Sent ACK" << endl; return 0; }
	}
	
	
	// Put new socket into our polling list.
	worker[nCli].fd = newfd;
	worker[nCli].events = POLLIN | POLLOUT;
	worker[nCli].revents = 0;
	
	*nClip = nCli;		// Return the possibly-modified index of last client.
	totalClients++; // used to track allowances
	return 1;
}

// implementation of server services
// does a handshake to see if the job table is needed
// if the job table is sent, read in a job from the client
// confirm if that job is valid, if it is mark it off as complete 
int Mom::
doService(toPoll* p, short id){
	char buf[BUFSIZ + 1];
	int retval = 0;		// Change in number of workers.
	
	if (p->revents == 0)  return -1;

	//  Test for a message event.
	if (p->revents & POLLIN) {// This is a read event--read it
		int bytes = read(p->fd, buf, (sizeof buf) - 1);
		//  We got a message, so handle it.
		if (bytes > 0) {		
			buf[bytes] = '\0';	// read does not null terminate.
			printf("\nFrom port %d:\t\t( %s ", getPort(p->fd), buf);
		} 
		// -----------------------No message, so handle the possible errors.
		else if (bytes == 0) {	// Indicates end of file.
			printf("closing socket on port %d\n", getPort(p->fd));
			close(p->fd);
			retval = -1;
		} else if (errno == ECONNRESET) {
			sayp("socket %d disappeared", getPort(p->fd));
			close(p->fd);
			retval = -1;
		} else {
			fatalp("Error %d from read, port %d", bytes, getPort(p->fd));
		}
	}
	// Write event
	else if (p->revents & POLLOUT){
		/*
			Currently:
			if timer is done: send QUIT
			else: send an ACK
			sends the job table
			reads in a job from client
			if valid job: send ACK
			if not valid: send NACK
		*/

		int ACK = sockStat::ACK;
		int bytes;

		// send the first ACK
		// if the timer is done, send QUIT instead
		if (isTimerFinished()) {
			cout << "Time's Up!" << endl;
			ACK = sockStat::QUIT;
			bytes = write(p->fd, &ACK, sizeof(ACK) );
			if (bytes < 1) { fatalp("Failed to write to socket"); }
			return -1;
		}
		else {
			cout << "Telling sock to keep going" << endl;
			ACK = sockStat::ACK;
			bytes = write(p->fd, &ACK, sizeof(ACK) );
			if (bytes < 1) { fatalp("Failed to write to socket"); }
			retval = 0;
		}

		// send the table 
		bytes = write(p->fd, &table, sizeof(table) );
		if (bytes < 1) { cout << "Failed to write to socket" << endl; }
			
		// read the incoming ACK
		bytes = read(p->fd, &ACK, sizeof ACK );

		// if the client did not pick a job, stop doing the service
		// else read the job
		if (ACK == sockStat::NACK) return retval;

		Job chosenJob;
		bytes = read(p->fd, &chosenJob, sizeof (chosenJob));
		if (bytes < 0) { cout << "Could not read socket on " << p->fd << endl; return -1; }
		
		cout << p->fd << " picked " << chosenJob.getID() <<" with Value : " << chosenJob.getValue() << endl;
		
		// check the jobs array if the chosen job is matched, and reserve that job and send an ACk
		// if that job is already reserved, send an NACK
		for(int i = 0; i < 10; i++) {
			if (chosenJob.getID() == table.jobs[i].getID()){
				if (table.jobs[i].getKid() == -1 && table.jobs[i].getStatus() == jobStat::notStarted){
					cout << "\n" << id << " Choosing Job " << table.jobs[i].getID() << "\n" << endl;
					cout << table.jobs[i] << endl;
					cout << "------------------------" << endl;

					table.jobs[i].chooseJob(id); 
					completedJobs.push_back(table.jobs[i]);
					cout << table.jobs[i] << endl;

					ACK = sockStat::ACK;
					bytes = write(p->fd, &ACK, sizeof(ACK) );
					if (bytes < 1) { cout << "Failed to write to socket" << endl; }

					break;
				}
				else {
					cout << "Job cannot be picked, sending back" << endl;
					ACK = sockStat::NACK;
					bytes = write(p->fd, &ACK, sizeof(ACK) );
					if (bytes < 1) { cout << "Failed to write to socket" << endl; }
					break;
				}
			}
			// edge case where job is not in table
			if (i >= 9){
				cout << "Job cannot be FOUND, sending back" << endl;
				ACK = sockStat::NACK;
				bytes = write(p->fd, &ACK, sizeof(ACK) );
				if (bytes < 1) { cout << "Failed to write to socket" << endl; }
				break;
			}
		}
		
		// display the jobs
		cout << "Job Table: " << endl;
		for (int i =0; i < 10; i++) {
			cout << table.jobs[i].getID() << " : " << table.jobs[i].getKid() << " | ";
		}
		cout << "\n" << endl;
	}
	// ---------------------------- It wasn't a message, so test for hangup.
	else if (p->revents & POLLHUP) {  // Caller hung up.
		say("Removing dead socket %d\n", getPort(p->fd));
		close(p->fd);
		retval = -1;
	}	// end if p has events.
	
	return retval;
}

// prints the sockarr_in structure from unistd.h
// designed to indicate which client was assigned to which port
void Mom::
printsockaddr_in(const char* who, sockaddr_in sock) {
	printf("%s socket is  {\n\t"
		   "sin_family        = %d\n\t"
		   "sin_addr.s_addr   = %s\n\t"
		   "sin_port          = %d\n\t"
		   "}\n", who, sock.sin_family, inet_ntoa(sock.sin_addr),
		   ntohs(sock.sin_port));
}


// returns port information of the connected socket
int Mom::
getPort(int fd){
	sockaddr_in client;
	socklen_t sockLen = sizeof client;
	int status = getpeername(fd, (sockaddr*) &client, &sockLen);
	if (status<0) fatalp("Can't get port# of socket (%d)", fd);
	return ntohs(client.sin_port);
}


// To be run once the main polling loop is done
// Goes through the completedJobs vector and creates an pay table for each kid
// The kid with the highest earnings gets $5 extra
// The allowances are then printed to the console
void Mom::
countAllowance(){
	cout <<"Completed Jobs: " << completedJobs.size() <<endl;
	int kidMoney[totalClients + 1] = {0, 0, 0, 0};
	int highest, compare = 0;

	// go through each job
	for (Job j : completedJobs){
		int kidIndex = j.getKid() - 1;
		kidMoney[kidIndex] += j.getValue();

		// if the current amount of money is the the highest, store it
		if (compare < kidMoney[kidIndex]){
			highest = kidIndex;
			compare = kidMoney[kidIndex];
		}
	}

	// reward the highest earner
	kidMoney[highest] += 5;
	cout << highest+1 << " has earned the most and gets $5 extra!" << endl;

	// print out each reward
	for (int i = 0; i < totalClients; i++){
		cout << "Kid: " << i+1 <<" Money: " <<kidMoney[i] <<endl;
	}
}