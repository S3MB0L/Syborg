/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include "main.h"



int server(struct socket_data socket_1)
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[socket_1.buff_size];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno =socket_1.portnum;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     while(1){
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     check_command(buffer,&command);

     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     fgets(buffer,socket_1.buff_size,stdin);
     n = write(newsockfd,buffer,strlen(buffer));
     if (n < 0) error("ERROR writing to socket");

     }


     close(newsockfd);
     close(sockfd);
     return 0; 
}

