#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<string.h>


int main() {

  int socket_desc , new_socket , c;
  struct sockaddr_in server , client;
	
  //Create socket
  socket_desc = socket(AF_INET , SOCK_STREAM , 0); 
  if (socket_desc == -1)
  {
	printf("Could not create socket");
  }
	
  //Prepare the sockaddr_in structure
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons( 6200 );
	
  //Bind
  if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
  {
	puts("bind failed");
  }
  puts("bind done");

  //Listen
  listen(socket_desc , 3);
	
  //Accept and incoming connection
  puts("Waiting for incoming connections...");
  c = sizeof(struct sockaddr_in);
  new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
  if (new_socket<0)
  {
		perror("accept failed");
  }
	
  puts("Connection accepted");

  char message[] = "message sending";
  if( send(new_socket , message , strlen(message) , 0) < 0)
  {
    puts("Send failed");
    return 1;
  }

  return 0;
}
