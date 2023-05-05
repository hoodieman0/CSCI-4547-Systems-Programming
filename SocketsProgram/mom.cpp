#include "mom.hpp"

Mom::
Mom(char* process, int port) : process(process), port(port), server(Socket(process)) {
    banner();
    table = JobTable();
}

void Mom::
startServer(){
	gethostname(hostname, 256);			// get name of local host.
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

	char greeting[256];
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
		int k;
		for (k = 0; k < currentClients; k++) {
			if (worker[k].revents != 0) {
				status = doService( &worker[k] );
				if ( status == -1){		// Remove dead socket from polling table
					worker[k] = worker[--currentClients];		// decrement # of workers
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
	// --------------------------- Put new socket into our polling list.
	worker[nCli].fd = newfd;
	worker[nCli].events = POLLIN;
	worker[nCli].revents = 0;
	
	// ----------------------------- We have a new caller -- send an ack.
	int bytes = write(newfd, greeting, strlen(greeting));
	if (bytes < 1) say("Error while writing to socket");
	
	*nClip = nCli;		// Return the possibly-modified index of last client.
	return 1;
}

int Mom::
doService(toPoll* p){
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