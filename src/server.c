#include <inc/main.h>


int server(struct socket_data socket_1)
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[socket_1.buff_size];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
    do{
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
        printf("Waiting for openning socket\n");
     }while(sockfd<0);

     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno =socket_1.portnum;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     while((bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) )
              printf("waiting for binding\n");

     listen(sockfd,5);
     clilen = sizeof(cli_addr);

     do{
     newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,  &clilen);
          printf("waiting for accept\n");
     }while(newsockfd<0);

     while(1){
     bzero(buffer,256);

     do{
     n = read(newsockfd,buffer,255);
     check_command(buffer,&command);
     printf("Reading socket\n");
     }while(n<0);

     printf("Here is the message: %s\n",buffer);

     do{
     fgets(buffer,socket_1.buff_size,stdin);
     n = write(newsockfd,buffer,strlen(buffer));
     printf("Waiting for  write\n");
    }while(n<0);
     }


     close(newsockfd);
     close(sockfd);
     return 0; 
}

