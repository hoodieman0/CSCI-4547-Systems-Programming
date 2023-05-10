#include "mom.hpp"

Mom::
Mom(char* process, int port) : table(JobTable()), process(process), port(port), server(Socket(process)) {
    banner();
}

void Mom::
startServer(){
	gethostname(hostname, 242);			// get name of local host.
	cout <<"server is " << hostname <<endl;

    server.listen(port);
    int welcomeFD = server.sockfd();

    welcome->fd = welcomeFD;
    welcome->events = POLLIN; // lets socket listen to clients

    printf("Opened socket as fd (%d) on port (%d) for stream i/o\n",
		   welcomeFD, ntohs(server.port()));
	cout << "welcome" << server;

    startPolling();
}

void Mom::
startPolling(){
    int status = 0;

	char greeting[284];
	sprintf(greeting, "Connected to (%s.%d)\n", hostname, port);

    for (;;) {
		status = poll(userFDs, 1 + currentClients, -1);
		//printf("."); fflush(stdout);
		if (status < 0)  fatalp("Error in poll().\t");
		if (status == 0) sayp("%s: poll timed out\t", process);
		// =====================================================================
		// If welcome socket has a caller, service it.
		if (welcome->revents != 0 )	{
			if (welcome->revents & POLLIN)	{
				if (currentClients < MAXCLIENTS) // create a new client connection.
					currentClients += doWelcome(welcome->fd, &currentClients, worker, greeting);
            }
            else fatalp("Error involving welcome mat: %d", welcome->revents);
		}
		// =====================================================================
		// Scan the working sockets and process whatever tasks you find
		if (currentClients >= 1){
		short k;
		for (k = 0; k < currentClients; k++) {
			
			if (worker[k].revents != 0) {
				status = doService( &worker[k], k+1 );
				if ( status == -1){		// Remove dead socket from polling table
					status = sockStat::QUIT;
					int bytes = write(worker[k].fd, &status, sizeof(status) );
					if (bytes < 1) { fatalp("Failed to write to socket"); }
					worker[k] = worker[--currentClients];		// decrement # of workers
				}
				else {
					status = sockStat::ACK;
					int bytes = write(worker[k].fd, &status, sizeof(status) );
					if (bytes < 1) { fatalp("Failed to write to socket"); }
				}
			}
		}
	}
		// stop looking for new clients if max has been reached ----------------
		welcome->events = (currentClients < MAXCLIENTS) ? POLLIN : 0;
	}	// end polling loop
}



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
	// ----------------------------- We have a new caller -- send an ack.
	//int bytes = write(newfd, greeting, strlen(greeting)); TODO
	int buf[2];
	buf[0] = sockStat::ACK;
	buf[1] = nCli+1;
	int bytes = write(newfd, &buf, sizeof(buf)); // write the ACK
	if (bytes < 1) say("Error while writing to socket");

	int nBytes = read( newfd, buf, sizeof buf );
	if (nBytes > 0){
		if ((sockStat)buf[0] == sockStat::ACK) cout << "Client Has Sent ACK" << endl;
		else { cout << "Client Has Not Sent ACK" << endl; return 0; }
	}
	
	
	// --------------------------- Put new socket into our polling list.
	worker[nCli].fd = newfd;
	worker[nCli].events = POLLIN | POLLOUT;
	worker[nCli].revents = 0;
	
	*nClip = nCli;		// Return the possibly-modified index of last client.
	return 1;
}

int Mom::
doService(toPoll* p, short id){
	char buf[BUFSIZ + 1];
	int retval = 0;		// Change in number of workers.
	
	if (p->revents == 0)  return -1;

		// ------------------------------------------- Test for a message event.
		if (p->revents & POLLIN) {// This is a read event--read it
			int bytes = read(p->fd, buf, (sizeof buf) - 1);
			// --------------------------------- We got a message, so handle it.
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
		else if (p->revents & POLLOUT){
			// probably need a quitFlag
				/*
					Currently:
					sends an ACK
					sends the job table
					reads in a job
					if valid job: send ACK
					if not valid: send NACK
				*/

			int ACK = sockStat::ACK;
			int bytes = write(p->fd, &ACK, sizeof(ACK) );
			//if (bytes < 1) { cout << "Failed to write to socket" << endl; }

				bytes = write(p->fd, &table, sizeof(table) );
				if (bytes < 1) { cout << "Failed to write to socket" << endl; }
				
				Job chosenJob;
				bytes = read(p->fd, &chosenJob, sizeof (chosenJob));
				if (bytes < 0) { cout << "Could not read socket on " << p->fd << endl; return -1; }
				cout << p->fd << " picked " << chosenJob.getID() <<" with Value : " << chosenJob.getValue() << endl;
				for(int i = 0; i<10;i++) {//job : table.jobs){
					if (chosenJob.getID() == table.jobs[i].getID()){
						if (table.jobs[i].getKid() == -1 && table.jobs[i].getStatus() == jobStat::notStarted){
							cout << "Choosing Job " << table.jobs[i].getID() << "\n" << endl;
							cout << table.jobs[i] << endl;
							cout << "------------------------" << endl;
							table.jobs[i].chooseJob(id); 
							cout << table.jobs[i] << endl;
							ACK = sockStat::ACK;
							int bytes = write(p->fd, &ACK, sizeof(ACK) );
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
				}
				for (int i =0; i < 10; i++) {
					cout << table.jobs[i].getID() << " _ " << table.jobs[i].getKid() << " | ";
				}
				cout << endl;
				
			retval = 0;
			
		}
		// ---------------------------- It wasn't a message, so test for hangup.
		else if (p->revents & POLLHUP) {  // Caller hung up.
			say("Removing dead socket %d\n", getPort(p->fd));
			close(p->fd);
			retval = -1;
		}	// end if p has events.
	
	return retval;
}

void Mom::
printsockaddr_in(const char* who, sockaddr_in sock) {
	printf("%s socket is  {\n\t"
		   "sin_family        = %d\n\t"
		   "sin_addr.s_addr   = %s\n\t"
		   "sin_port          = %d\n\t"
		   "}\n", who, sock.sin_family, inet_ntoa(sock.sin_addr),
		   ntohs(sock.sin_port));
}

int Mom::
getPort(int fd){
	sockaddr_in client;
	socklen_t sockLen = sizeof client;
	int status = getpeername(fd, (sockaddr*) &client, &sockLen);
	if (status<0) fatalp("Can't get port# of socket (%d)", fd);
	return ntohs(client.sin_port);
}