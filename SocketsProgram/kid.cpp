#include "tools.hpp"
#include "Socket.hpp"

#define PORT 1099

void printSockInfo( const char* who, sockInfo sock );

// arg 1 is remote host
int main(int argc, char* argv[]){
    char* process = argv[0];
    if ( argc != 2 ) fatal( "usage: %s hostname\n", process );

    char* serverName = argv[1];

    Socket client(process);
    client.connect(serverName, PORT);

}