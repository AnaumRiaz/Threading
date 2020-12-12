//client that calls a server on the same pc and receive a text message. 


#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h> //right now?
#include<sys/socket.h>
#include <netinet/in.h>  //STRUCT sockaddr_in, 
#include<unistd.h> //for closing sockets
#include<string.h>

int main() {
  int my_socket;
  my_socket = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in sa;
  sa.sin_family = AF_INET;
  sa.sin_port = htons(8888);
  sa.sin_addr.s_addr = INADDR_ANY;

  int cs=connect(my_socket, (struct sockaddr *) &sa, sizeof(sa));

  if (cs == -1) {
    printf("THere was an error making a connection");
    return 1;
  }

  char data_r[256];
  int n_s = recv(my_socket, &data_r, sizeof(data_r), 0);
  printf("-d1: %s\n", data_r);
  
  recv(my_socket, &data_r, sizeof(data_r), 0);
  printf("-d2: %s\n", data_r);
   
  char mess[400] = "sending from client";
  write(n_s , mess , strlen(mess));

  printf("gonna send empty string now\n");
  strcpy(mess , "");
  write(n_s , mess , strlen(mess));
  close(my_socket);

return 0;
}
