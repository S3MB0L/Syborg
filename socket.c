/*
 * Author Tarkan Dalay
 * mail: tarkandalay52@gmail.com
 * date: 28/11/2016
 * rev:0.01b
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int net_connection (int status, int buffer, int port, char *ip) {
    int cnt=0;

    command.close="./close\n";
    command.set="./set_relayx\n";
    command.status="./status\n";

    socket_1.buff_size=buffer;
    socket_1.portnum=port;
    socket_1.socket_status=status;
    socket_1.ip=ip;

//    while((socket_1.opt=getopt(argc,argv,"sc:p:b:n:"))!=-1){
//        //printf("%c",opt[cnt]);

//        cnt++;
//        switch (socket_1.opt) {
//        case 'c':
//            socket_1.socket_status='c';
//            printf("%s\n",optarg);
//            printf("client selected\n");
//            break;
//        case 's':
//            socket_1.socket_status='s';
//            printf("server selected\n");
//            break;
//        case 'b':
//            socket_1.buff_size=atoi(optarg);
//            printf("Buffer size=%d\n",socket_1.buff_size);
//            break;
//        case 'p':
//            socket_1.portnum=atoi(optarg);
//            printf("port numarası= %d\n",socket_1.portnum);
//            break;
//        case 'n':
//            socket_1.ip=optarg;
//            printf("ip numarası=%s\n",socket_1.ip);
//            break;
//        default:
//            break;
//        }

//    }

    if(socket_1.socket_status=='c')
        client(socket_1);
    else if (socket_1.socket_status=='s')
        server(socket_1);

    return 0;
}

int check_command(char *buff,struct commands *x){
    printf("Entering check_command\n");
    if(!strcmp(buff,x->close)){
        printf("./close selected\n");

        //Enter commands here.

    }
    else if(!strcmp(buff,x->set)){

        printf("./relay set selecte\n");

        //Enter commands here.

    }
    else if(!strcmp(buff,x->status)){
        printf("./status selected\n");

        //Enter commands here

    }
    return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
