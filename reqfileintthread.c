//requesting the file from the internet and saving to file

#include <netdb.h> // gethostbyname
#include<string.h>	//memcpy
#include<stdlib.h>	//strlen
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h> //for send()
#include<pthread.h> //for threading , link with lpthread

void* connect_handler(void *);
void check_err(int exp, char *msg){ 
  if (exp<0) {
    perror(msg);
    exit(1); }
}

int main(int argc, char ** argv) {

  printf("INSIDE!\n");
  //make a socket
  int main_socket;
  check_err( (main_socket = socket(AF_INET, SOCK_STREAM,0)), "Problem creating socket");

   //getting address from user if possible using short/long options
    int portno = 80;
    char *message = "GET / HTTP/1.1\r\n\r\n";
    char *hostname = "www.gooogle.com";


    // Parse and set command line arguments. s:server, p:port,m:message and h:help
    int option_char = 0;
    char* help = "Add server by using -s, port by adding -p and message by -m followed by the value";
    while ((option_char = getopt(argc, argv, "s:p:m:h")) != -1)
    { 
        switch (option_char)
        {
        case 's': // server
            hostname = optarg;
            break;
        case 'p': // listen-port
            if (atoi(optarg) >1023 && atoi(optarg) < 49151) {
            portno = atoi(optarg); }
            break;
        case 'm': // message
            message = optarg;
            break;
        default:
            printf("%s\n",help);

        }
    }

 //check if the value for the server(server) is legit and we can go on
    char* ip;
    //struct hostent *hp =    gethostbyname("www.google.com");
    struct hostent* re_ser= gethostbyname(hostname);
    if (re_ser == NULL) {
       printf("gethostbyname() failed\n");
    } else {
       printf("%s = ", re_ser->h_name);
       unsigned int i=0;
   
    //checking all the IPs       
    while ( re_ser -> h_addr_list[i] != NULL) {
          printf( "%s ", inet_ntoa( *( struct in_addr*)( re_ser -> h_addr_list[i])));  //ntoa gives the dotted notation from network order
          i++; }
       ip = inet_ntoa( *( struct in_addr*)( re_ser -> h_addr_list[0]));
       printf("\n");
       }
   //using the first IP to change into network to connect 
   struct in_addr addr; //this is only to save the ip address for the server in add.sin_addr=addr type
   if (inet_aton(ip, &addr ) == 0) {
        printf("iten_aton not working\n");
        exit(-1); }

   //making a sockaddr structure for connect
   struct sockaddr_in ser;
   ser.sin_family = AF_INET;
   ser.sin_port = htons(portno);
   ser.sin_addr= addr;

   //connect to server
   check_err(connect(main_socket, (struct sockaddr*)&ser, sizeof(ser)), "Problem connecting to the server");


   //Send some data
   check_err( send(main_socket , message , strlen(message) , 0), "Problem with sending data");
   puts("Data Send\n");  
  
  //this will wiat 5 seconds in receive. if no data received for 5 seconds, it will close the socket?
  struct timeval tv;
  tv.tv_sec = 2;
  tv.tv_usec = 0;
  setsockopt(main_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
  
  int total_data = 0;
  int p_d;

  //Receive a reply from the server
  char server_reply[2000];
  FILE *fptr = fopen("mf.txt","a+");

  while ((p_d = recv(main_socket, server_reply , 2000 , 0)) > 0) {
     //printf("Reply received %d\n", p_d);
     fprintf(fptr,"%s",server_reply);
     total_data += p_d;
     //puts(server_reply); 
  }
  printf("total bytes received: %d\n", total_data);
  
  fseek(fptr, 0, SEEK_SET);
  char buf[20];
  fgets(buf, 20, fptr );
  printf("first 20 characters from file: %s\n", buf);
  close(main_socket);
  fclose(fptr);
  return 0;
}
