#include "tools.hpp"
#include "Socket.hpp"
#include "kid.hpp"
#include "enums.hpp"

#define PORT 1099

// arg 1 is remote host
int main(int argc, char* argv[]){
    char* process = argv[0];
    if ( argc != 2 ) fatal( "usage: %s hostname\n", process );

    char* serverName = argv[1];

    Socket client(process);
    client.connect(serverName, PORT);

    


    int buf[BUFSIZ+1];
    int responseBuffer[BUFSIZ+1];
    // wait for server to acknowledge the connection. 
    int nBytes = read( client.sockfd(), buf, sizeof buf );

    // Kid kid();
    if( nBytes >= 0 )  cout <<nBytes <<"  " <<buf[0] << "   " << buf[1] << endl;
    else fatal("%s: Error while reading from socket.", process );
    Kid kid(buf[1]);

    responseBuffer[0] = sockStat::ACK;
    nBytes = write( client.sockfd(), &responseBuffer, sizeof(responseBuffer) );
    if( nBytes < 0 ) fatal("%s: Error while writing to socket.", process);

    
    
    
    // Write lines until message is complete.
    // Number of lines to write from defined poem
    const char* line = "We Are Here!";
    for( int k = 0; k < 5; k++ ) {
        sleep(1);
        nBytes = write( client.sockfd(), line, strlen(line) );
		cout <<"@";
        if( nBytes < 0 ) fatal("%s: Error while writing to socket.", process);
    }
    cout <<endl;


    return 0;
}