//server that listens for a client and send a message. 

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<unistd.h>


int main() {
  char message[256] = "anaum is awesomes!";
  //create a socket. tcp.
  int ser_sock = socket(AF_INET, SOCK_STREAM, 0);

  //for connection, this address wll be used
  struct sockaddr_in sa;
  sa.sin_family= AF_INET;
  sa.sin_port = htons(9002);
  sa.sin_addr.s_addr = INADDR_ANY;   //gets ip at the time of running

  bind(ser_sock, (struct sockaddr*) &sa, sizeof(sa));
  listen(ser_sock, 10);

  int client_socket;
  client_socket = accept(ser_sock, NULL, NULL);
  send(client_socket, message, sizeof(message), 0);

  close(ser_sock);

  return 0;

}
