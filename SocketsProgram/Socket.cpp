#include "Socket.hpp"

// Socket Creation
Socket::
Socket(char* process) : process(process){
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) fatalp("Socket: Can't create socket");
}

// Update struct (info) with the current information
void Socket::
refresh(){
    socklen_t addrlen = sizeof(sockInfo);
    int status = getsockname(fd, (sockaddr*)&info, &addrlen);
    if ( status < 0 ) fatalp("Socket: getsockname failed on socket %d.", fd);
    cout << *this;
}

// returns peer of connected socket
int Socket::
peer(Socket* pr) const {
    socklen_t addrlen = sizeof(sockaddr_in);
    sockInfo peeraddr; // Send to getpeername as an output parameter.
    int status = getpeername(fd, (sockaddr*)&peeraddr, &addrlen);
    if (addrlen != sizeof(sockInfo))
        fatal("Buffer length error %d!=%d\n", addrlen, sizeof(sockInfo));

    *(sockInfo*)pr = peeraddr;
    return status;
}

// Server side function, listens for any conenctions to the socket
void Socket::
listen(int port) {
	info.sin_family = AF_INET;
	info.sin_port = htons(port);
	info.sin_addr.s_addr = INADDR_ANY;

    // sockaddr is used to set fields of kernel socket.
    int status = ::bind(fd, (sockaddr*)&info, sizeof(struct sockaddr_in));
    if (status < 0) fatalp("Can't bind socket (%d)", fd);
    refresh();
    cout << "Just bound socket " << fd << ": " << *this << endl;

    // Declare that this is the welcome socket and it listens for clients.
    status = ::listen(fd, 1);
    if (status < 0) fatalp("Socket: Unable to listen on socket %d.", fd);
    cout << "Just called listen(); now waiting for a client to show up\n";
}

// Client side function, uses the coordinated port to connect the sockets
void Socket::
connect(const char* host, int port) {
	info.sin_family = AF_INET;
	info.sin_port = htons(port);

	// Use domain name server to get IP address associated with server.
	struct hostent* remoteHost = gethostbyname(host);
	if (remoteHost == NULL) fatalp("Socket: unknown host: %s\n", host);

// Copy info about the host into this Socket's base class.
// The name server returns a list of IP addresses.  We
// want the first. h_addr_list[0] is the first address
// found by gethostbyname().  h_length is the length of
// addresses in the h_addr_list[].
   memmove(&info.sin_addr, remoteHost->h_addr_list[0], remoteHost->h_length);

// Copy the agreed-upon port number into this Socket's
// base class. Convert first from the local
// representation to the internet standard.
	info.sin_port = htons(port);
    cout << *this;

// Info in client sockaddr struct is now ready to connect to server.
	cout << "Ready to connect socket " << fd << " to " << host << endl;
	int status = ::connect(fd, (sockaddr*)&info, sizeof(struct sockaddr_in));
	if (status < 0) fatalp("Client: Connection to %s refused.", host);
	refresh();
	cout << "Socket: connection established to " << host << ".\n";

    char buf[BUFSIZ+1];
    // wait for server to acknowledge the connection. 
    int nBytes = read( fd, buf, sizeof buf );
    if( nBytes >= 0 )  cout <<nBytes <<"  " <<buf;	// the connection message.
    else fatal("%s: Error while reading from socket.", process );
    
    // Write lines until message is complete.
    // Number of lines to write from defined poem
    char* line = "We Are Here!\n";
    for( int k = 0; k < 10; k++ ) {
        sleep(1);
        nBytes = write( fd, line, strlen(line) );
		cout <<"@";
        if( nBytes < 0 ) fatal("%s: Error while writing to socket.", process);
    }
    cout <<endl;
}

ostream&
Socket::print(ostream& out) const {
    out <<  "\t{\n"
    "\tsin_family       = " << info.sin_family << "\n"
    "\tsin_addr.s_addr  = " << inet_ntoa(info.sin_addr) << "\n"
    "\tsin_port         = " << ntohs(info.sin_port) << "\n"
    "\t}\n";
    return out;
}