#include "tools.hpp"
#include "Socket.hpp"
#include "kid.hpp"
#include "enums.hpp"
#include "job.hpp"
#include "jobTable.hpp"

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
    if( nBytes < 8 ) fatal("%s: Did not pass ACK.", process );
    Kid kid(buf[1]);
    cout << process << " ID in server is " << kid.getID() << endl;
    cout << process << ": My mood is " << kid.getMood() << endl;

    responseBuffer[0] = sockStat::ACK;
    nBytes = write( client.sockfd(), &responseBuffer, sizeof(responseBuffer) );
    if( nBytes < 0 ) fatal("%s: Error while writing to socket.", process);

    sockStat status;

    JobTable table;
    Job* picked;

    do {
    do{
        nBytes = read( client.sockfd(), &status, sizeof status ); // reads in the firstACK

        // reads in the job table from socket
        cout << "\nFetching jobs" << endl;
        nBytes = read( client.sockfd(), &table, sizeof (table) ); 
        if (nBytes < 0) { cout << "Could not read welcome socket" << endl;}
        cout << process << " Acknowledgement: Has received Job Table" << endl;

        // chooses a job from the table
        kid.setTable(&table);
        cout << "Here1" << endl;
        picked = kid.pickJob();
        cout << "Here2" << endl;
        if (picked == nullptr) { cout << "No jobs left to do!" << endl; break;} 
        cout << "Here0" << endl;

        // send picked job over the socket
        cout << process << " picked " << picked->getID() <<" with Value : " << picked->getValue() << endl;
        nBytes = write( client.sockfd(), picked, sizeof(*picked) ); 

        // read in the ACK, if ACK break, if NACK repeat
        nBytes = read( client.sockfd(), &status, sizeof status );
        for (int i =0; i < 10; i++) {
					cout << table.jobs[i].getID() << " _ " << table.jobs[i].getKid() << " | ";
				}
				cout << endl;
        if (status == sockStat::NACK) { cout << "Server has denied request" << endl; }
    } while(status == sockStat::NACK);

    if (status == sockStat::ACK){
            cout << process << " is doing their chore!" << endl;
            sleep(picked->getTime());
            cout << process << " finished its chore.\n" << endl;
        }

    nBytes = read( client.sockfd(), &status, sizeof status );
    cout << status << endl;
    } while (status != sockStat::QUIT);
    
    cout << process << " is finished!" << endl;
    // Write lines until message is complete.
    // Number of lines to write from defined poem


    return 0;
}