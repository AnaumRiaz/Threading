#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

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
          printf( "%s \n", inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i])));
          i++;
           }
       
       }

  char* ip = inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[0]));  //taking the first ip address from the hostnet struct
  struct und {
    char* mess ;
  };


  struct und mine;
  if (argc == 2) {
    mine.mess = argv[1]; } 
  else {
    mine.mess = "No second argument"; }
 
  struct und* a;
  a= &mine;


  printf("%s\n",a->mess);
  return 0;
}
