#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/sendfile.h>

using namespace std;

int main(){
	//Setup socket
	int sockfd;

	//Create socket
	do{
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
	}while(sockfd < 0);

	//Set up server address
	int servPort = 1025;
	struct sockaddr_in serv_addr;

	//Zero out server memory block
	bzero((char *) &serv_addr, sizeof(serv_addr));

	//Set server address attributes
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(servPort);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	//Bind socket to port
	while(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		servPort++;
		serv_addr.sin_port = htons(servPort);
		if(servPort == 20000){
			printf("This is unusual... Binding is continuing to fail.\n");
		}
		else if(servPort == 65535){
			printf("Binding to all ports have been attempted, so clearly something is very wrong.\n");
		}
	}

	//Listen on socket for incoming connections
	listen(sockfd, 5);

	
	//Output host socket/port
	printf("Server started, port number %d.\n", servPort);

	/*On accept, create pthread to handle incoming connection while continuing to 
	listen*/

	//Accept client connection
	//While not quitting(implement after first success){
	struct sockaddr_in cli_addr;
	socklen_t clilen = sizeof(cli_addr);
	int clientSocket = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(clientSocket < 0){
		fprintf(stderr, "ERROR on accept");
	}
	//If all is well, create thread to handle client request
	//At end of while loop, break if not main thread to handle client request
	//printf details of connection ******COMPLETE ME******

	char buffer[2048];
	bzero(buffer, 2048);
	string tempS;
	int retCode = recv(clientSocket, buffer, 2048, 0);
	int recvd = 0;
	while(retCode != -1 && retCode != 0 && recvd < 2048){
		// successfully received some data; buffer it
		tempS.append(buffer, retCode);
		recvd += retCode;
    	}

	if(retCode < 0){
		fprintf(stderr, "ERROR reading from socket.\n");
		exit(1);
	}
	
	//Null terminates buffer
	buffer[2047] = '\0';
	if(buffer[2046] == '\n'){
		buffer[2046] = '\0';
	}
	printf("%s\n", tempS.c_str());
	istringstream stringIn(tempS, istringstream::in);
	string holder;
	//stringIn.clear();
	stringIn >> holder;
	if(holder != "GET"){
		fprintf(stderr, "%s\n", tempS.c_str());
		fprintf(stderr, "Client request is not an HTTP GET. Terminating...\n");
		int err = write(clientSocket,"Error: this server only services a small set of GET requests", 60);
		if(err < 0){
			fprintf(stderr, "Man, something is really wrong here...\n");
		}
		exit(1);
	}

	//Create filepath
	stringIn >> holder;
	string fileIn = "www" + holder;

	//Debug
	printf("Here is the file requested: %s\n", fileIn.c_str());

	//Open file
	const char* mode = "r";
	FILE* fileOut = fopen(fileIn.c_str(), mode);
	retCode = read(fileno(fileOut), buffer, 2048); //Problems
	if(retCode < 0){
		fprintf(stderr, "Error sending file size.\n");
		exit(EXIT_FAILURE);
        }

	//Send file size to client
	retCode = send(clientSocket, fileOut, sizeof(fileOut), 0);
	if(retCode < 0){
		fprintf(stderr, "Error sending file size.\n");
		exit(1);
        }

        //Send file data to client
        int offset = 0;
        int remain_data = sizeof(fileOut);
	int sent_bytes = 0;
        while(((sent_bytes = sendfile(clientSocket, fileno(fileOut), (off_t*)&offset, sizeof(fileOut))) > 0) && (remain_data > 0)){
		remain_data -= sent_bytes;
        }

	//Closes sockets, terminates program
	close(clientSocket);
	close(sockfd);
	return 0; 
}
