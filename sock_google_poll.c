

#include <poll.h>
#include<stdio.h>
#include <netdb.h> // gethostbyname
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h> //for send()
#include<string.h> //strlen
#include <arpa/inet.h> //inet_addr
#include <fcntl.h>

int main(int argc, char **argv) {

  struct hostent* hp;

  if (argc == 2) { 
    printf("%s\n", argv[1]);
    hp = gethostbyname(argv[1]); }
  else
    hp = gethostbyname("www.google.com"); 

  if (hp == NULL) {
       printf("gethostbyname() failed\n");
    } else {
       printf("%s = ", hp->h_name);
       unsigned int i=0;
       while ( hp -> h_addr_list[i] != NULL) {
          printf( "%s ", inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i])));  //ntoa gives the dotted notation from network order
          i++;
           }
       printf("\n");
       }


  int ms;
  struct in_addr addr;
  
 
  ms = socket(AF_INET, SOCK_STREAM, 0);
  if (ms== -1) {
    printf("could not make socket\n");
    return -1;
  }
  
  struct sockaddr_in add;
  add.sin_family = AF_INET;
  add.sin_port = htons(80);
  //add.sin_addr.s_addr = INADDR_ANY; //inet_aton("192.168.1.100");  //ntoa opposite of inet_addr
  
  char* ip = inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[0]));  //taking the first ip address from the hostnet struct
 
  if (inet_aton(ip, &addr ) == 0) {
        printf("iten_aton not working\n");
        exit(-1);
    }
 
  add.sin_addr = addr;
  
  if (connect(ms, (struct sockaddr*) &add, sizeof(add)) == -1) {
    printf("Connection failed\n");
    return -1;
  }


  //Send some data
  char message[] = "GET / HTTP/1.1\r\n\r\n";
  if( send(ms , message , strlen(message) , 0) < 0)
  {
    puts("Send failed");
    return 1;
  }
  
  puts("Data Send\n");  
  
/*
  //Receive a reply from the server
  if( recv(ms, server_reply , 2000 , 0) < 0) {
    puts("recv failed");
  }
*/

// Put the socket in non-blocking mode:
if(fcntl(ms, F_SETFL,O_NONBLOCK) < 0) {
    fprintf(stderr, "error with setting read nonblocking\n");
}

char server_reply[2000];
int rec_bytes;
//---- starting here---
while ((rec_bytes= recv(ms, server_reply, 2000, 0) )> 0) {
  printf("------------------bytes reeceived = %d--------\n", rec_bytes);
  puts(server_reply);
  puts("----------------------");

}
puts("ending the receive\n");

//---end here----
 // puts("Reply received\n");
  //puts(server_reply); 
	
  close(ms);

  return 0;
}
