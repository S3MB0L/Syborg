#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

struct socket_data{
    int opt;
    int portnum;
    char *ip;
    int buff_size;
    char socket_status;
}socket_1;

struct commands{
    char *close;
    char *status;
    char *set;
} command;

struct serialcomm{

    int baudrate;
    char *port;
    int buff;
    int display;
}serial_data;

void error(const char *msg);
int client(struct socket_data socket_1);
int server(struct socket_data socket_1);
int check_command(char *buff, struct commands *x);
int net_connection (int status, int buffer, int port, char *ip);
int serialcomm(char *port, int baudR,int buffer, int display);

#endif // MAIN_H
