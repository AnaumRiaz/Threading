#include<stdio.h>
#include <netdb.h> // gethostbyname
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h> //for send()
#include<string.h> //strlen
#include <arpa/inet.h> //inet_addr

int main(int argc, char **argv) {
  
    //defining the default server and port
    int ms; //socket identifier
    struct sockaddr_in add; //for the address used in connecting the socket to server
    struct in_addr addr; //this is only to save the ip address for the server. tis is used in connect statement as add.sin_addr only takes addr type
    char server_reply[2000];
    struct hostent* hp;
    
    //default values
    hp = gethostbyname("www.google.com"); 
    int option_char = 0;
    char *ip, *message = "GET / HTTP/1.1\r\n\r\n"; 
    add.sin_family = AF_INET;
    add.sin_port = htons(80);
    

    // Parse and set command line arguments. : means that an option after -alphabet is required. s:server, p:port, m:message and h is help
    while ((option_char = getopt(argc, argv, "s:p:m:hx")) != -1) {
      switch (option_char)
        {
        case 's': // server
            hp = gethostbyname(optarg); 
            break;
        case 'p': // listen-port
            printf("the added port is %d\n", atoi(optarg));
            add.sin_port = htons(atoi(optarg));
            break;
        default:
            fprintf(stderr, "%s", "Default message inside while loop(most likely wrong option alphabet?\n");
            exit(1);
        case 'm': // message...try not to use this
            message = optarg;
            break;
        }
    }


    //check if the value for the hp(server) is legit and we can go on
    if (hp == NULL) {
       printf("gethostbyname() failed\n");
    } else {
       printf("%s = ", hp->h_name);
       unsigned int i=0;
       while ( hp -> h_addr_list[i] != NULL) {
          printf( "%s ", inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i])));  //ntoa gives the dotted notation from network order
          i++; }
       ip = inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[0]));
       printf("\n");
       }


  //make socket
  ms = socket(AF_INET, SOCK_STREAM, 0);
  if (ms== -1) {
    printf("could not make socket\n");
    return -1;
  }

  
  //getting the address in addr(in binary) to connect to the internet
  if (inet_aton(ip, &addr ) == 0) {
        printf("iten_aton not working\n");
        exit(-1);
    }
 
  //setting the address in sockaddr_in to send in connect
  add.sin_addr = addr;
  
  if (connect(ms, (struct sockaddr*) &add, sizeof(add)) == -1) {
    printf("Connection failed\n");
    return -1;
  }


  //Send some data
  if( send(ms , message , strlen(message) , 0) < 0)
  {
    puts("Send failed");
    return 1;
  }
  puts("Data Send\n");  
  

  //Receive a reply from the server
  if( recv(ms, server_reply , 2000 , 0) < 0) {
    puts("recv failed");
  }

  puts("Reply received\n");
  puts(server_reply); 
	
  close(ms);

  return 0;
}


//add.sin_addr.s_addr = INADDR_ANY; //inet_aton("192.168.1.100");  
//ntoa opposite of inet_addr
//inaddr_any basically says that connect to whatever Ip the computer has at the time of connection?
//char *inet_ntoa(struct in_addr in);
/*
  
  //just for the sake of printing the address
  char* ip = inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[0]));  //taking the first ip address from the hostnet struct
  printf("ip notation is %s\n", ip);  //we get dotted notation
*/



