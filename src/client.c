#include <inc/main.h>

int client(struct socket_data socket_1)
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];

    portno = socket_1.portnum;
    do{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
        printf("connecting socket\n");
    }while(sockfd<0);

    do{
    server = gethostbyname(socket_1.ip);
        printf("waiting for server\n");
    }while(server==NULL);

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);

    while(connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        printf("waiting for connecting\n");
    while(1){
        printf("Please enter the message: ");
        bzero(buffer,256);
        fgets(buffer,255,stdin);
        n = write(sockfd,buffer,strlen(buffer));
        if (n < 0)
             error("ERROR writing to socket");
        bzero(buffer,256);
        n = read(sockfd,buffer,255);

        if (n < 0)
             error("ERROR reading from socket");
        printf("%s\n",buffer);
        check_command(buffer,&command);


    }
    printf("closing socket\n");
    close(sockfd);
    return 0;
}
