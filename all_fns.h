#include "header.h"

//#define REMOTEPORT 1235
//#define BUFLEN 1024

void mysend(char* messageStr, int REMOTEPORT )
{
  int opt = 1;
  int sockfd;
  int BUFLEN = 10000;
  char buffer[BUFLEN];
  //char *messageStr = "very important Good Morning message with 100s of emojis!!!";
  struct sockaddr_in   receiverAddr;
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  memset(&receiverAddr, 0, sizeof(receiverAddr));

  receiverAddr.sin_family = AF_INET;
  receiverAddr.sin_port = htons(REMOTEPORT);
  receiverAddr.sin_addr.s_addr = INADDR_ANY;
  sendto(sockfd, (const char *)messageStr, strlen(messageStr), 0, (const struct sockaddr *) &receiverAddr, sizeof(receiverAddr));
  
  //printf("message sent from here");
  system("clear");
  close(sockfd);
  //return 0;
}

void write_msg(int port)
{
  char mymsg[1000];
  int mymsg_len = 0;
  char take;
  while((take = getchar()) != 10)
  {

    mymsg[mymsg_len] = take;
    mymsg_len++;
  }
  //mymsg_len++;
  mymsg[mymsg_len] = '\0';


 
  char len_conv[40];
  sprintf(len_conv, "%d", mymsg_len);
 
  mysend(mymsg, port);
  


  printf("\n");

}



void recvr(int LISTENPORT)
{
  int BUFLEN = 10000;
  int opt = 1;
  int sockfd, len, n;
  char buffer[BUFLEN];
  struct sockaddr_in receiverAddr, senderAddr;

  if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("socket system call failed");
    exit(EXIT_FAILURE);
  }

  memset(&receiverAddr, 0, sizeof(receiverAddr));
  memset(&senderAddr, 0, sizeof(senderAddr));

  

  receiverAddr.sin_family = AF_INET;
  receiverAddr.sin_addr.s_addr = INADDR_ANY;
  receiverAddr.sin_port = htons(LISTENPORT);

   int flag = 1;  
    if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag))) {  
        perror("setsockopt fail");  
    }  

  if(bind(sockfd, (const struct sockaddr *)&receiverAddr, sizeof(receiverAddr)) < 0)
  {
    perror("bind syscall failed");
    exit(EXIT_FAILURE);
  }
  len = sizeof(senderAddr);
  //printf("waiting for data to be received: \n");
  n = recvfrom(sockfd, (char *)buffer, BUFLEN, MSG_WAITALL, (struct sockaddr *) &senderAddr, &len);
  buffer[n] = '\0';
  printf("\ndata received: %s\n", buffer);
  //printf("--------------\n");
  //return 0;
  close(sockfd);
}

void get_msg(int port)
{
 // int buflen = recv_buflen(1234);
  recvr(port);
  printf("\n");
}



