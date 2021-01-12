#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include <arpa/inet.h>
#define PORT 8080

int main(int argc, char* argv[]){
	int create_socket;
	int bufsize=4096;
	char *buffer=malloc(bufsize);
	char fname[256];
	struct sockaddr_in address;
	int count;

	if((create_socket=socket(AF_INET, SOCK_STREAM,0))>0)
		printf("The socket was created\n\n");
	address.sin_family=AF_INET;
	address.sin_port=htons(PORT);
	inet_pton(AF_INET, argv[1],&address.sin_addr);
	if(connect(create_socket,(struct sockaddr*)&address,sizeof(address))==0)
		printf("The connection was accepted with the server %s",argv[1]);
	printf("Enter the filename to request:");
	scanf("%s",fname);
	send(create_socket,fname,sizeof(fname),0);
	printf("The request was accepted......Receiving file....\n\n");
	while((count=recv(create_socket, buffer, bufsize,0))>0){
		write(1,buffer,count);
	}
	printf("\nEOF\n");
	return close(create_socket);




}