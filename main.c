#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc , char *argv[]){

	int socket_desc;
	struct sockaddr_in server;
	char *message , server_reply[30];
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1){
		printf("Could not create socket");
	}
		
	server.sin_addr.s_addr = inet_addr("10.0.0.248");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8081 );

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0){
		puts("connect error");
		return 1;
	}
	
	puts("Connected\n");
	
	//Receive a reply from the server
    while(1){
	    if( recv(socket_desc, server_reply , 30 , 0) < 0){
		    puts("recv failed");
	    }

        printf("%s", server_reply);
        printf("\n");
        //puts(server_reply);
    }

	return 0;
}