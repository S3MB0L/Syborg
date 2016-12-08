#include <main.h>

#define DISPLAY_STRING



int baudrate_select(int x);
int set_interface_attribs(int fd, int speed);
void set_mincount(int fd, int mcount);


int serialcomm(char *port, int baudR,int buffer, int display)
{
    serial_data.baudrate=baudR;
    serial_data.port=port;
    serial_data.buff=buffer;
    serial_data.display=display;

    int opt;
//    while((opt=getopt(argc,argv,"p:b:r:d:"))!=-1){
//        switch (opt) {
//        case 'p':
//            opts_1.port=optarg;
//            break;
//        case 'b':
//            if(baudrate_select(atoi(optarg))==-1){
//                printf("Wrong baudrate\n");
//            exit(EXIT_FAILURE);
//            }
//            break;
//        case 'r':
//            opts_1.buff=atoi(optarg);
//            break;
//        case 'd':
//            opts_1.display=atoi(optarg);
//            break;
//        default:
//           //printf("Invalid parameters\n");
//           //printf("Usage -p port -b baudrate -r buffer -s 1 display string 0 diplay hex\n");
//           // exit(EXIT_FAILURE);
//            break;
//        }
//    }

    printf("port=%s, BR=%d",serial_data.port,serial_data.baudrate);
    char *portname = serial_data.port;
    int fd;
    int wlen;

    fd = open(portname, O_RDWR | O_NOCTTY | O_ASYNC);
    if (fd < 0) {
        printf("Error opening %s: %s\n", portname, strerror(errno));
        return -1;
    }
    /*baudrate 115200, 8 bits, no parity, 1 stop bit */
    set_interface_attribs(fd, serial_data.baudrate);

    //set_mincount(fd, 0);                /* set to pure timed read */

    /* simple output */
    wlen = write(fd, "Hello!\n", 7);
    if (wlen != 7) {
        printf("Error from write: %d, %d\n", wlen, errno);
    }
    tcdrain(fd);    /* delay for output */



    /* simple noncanonical input */
    do {
        unsigned char buf[serial_data.buff];
        int rdlen;

        rdlen = read(fd, buf, sizeof(buf) - 1);

            if (rdlen > 0) {
                if(serial_data.display==1){
                buf[rdlen] = 0;
                printf("%s", buf);
            }
            else{
                unsigned char   *p;
                printf("Read %d:", rdlen);
                for (p = buf; rdlen-- > 0; p++)
                    printf(" 0x%x", *p);
                printf("\n");
            }
        } else if (rdlen < 0) {
            printf("Error from read: %d: %s\n", rdlen, strerror(errno));
        }
        /* repeat read to get full message */
    } while (1);
}

int set_interface_attribs(int fd, int speed)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

void set_mincount(int fd, int mcount)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error tcgetattr: %s\n", strerror(errno));
        return;
    }

    tty.c_cc[VMIN] = mcount ? 1 : 0;
    tty.c_cc[VTIME] = 5;        /* half second timer */

    if (tcsetattr(fd, TCSANOW, &tty) < 0)
        printf("Error tcsetattr: %s\n", strerror(errno));
}

int baudrate_select(int x){
    if(x==0) serial_data.baudrate=B0;
    else if(x==50) serial_data.baudrate=B50;
    else if(x==75) serial_data.baudrate=B75;
    else if(x==110) serial_data.baudrate=B110;
    else if(x==134) serial_data.baudrate=B134;
    else if(x==150) serial_data.baudrate=B150;
    else if(x==200) serial_data.baudrate=B200;
    else if(x==300) serial_data.baudrate=B300;
    else if(x==600) serial_data.baudrate=B600;
    else if(x==1200) serial_data.baudrate=B1200;
    else if(x==1800) serial_data.baudrate=B1800;
    else if(x==2400) serial_data.baudrate=B2400;
    else if(x==4800) serial_data.baudrate=B4800;
    else if(x==9600) serial_data.baudrate=B9600;
    else if(x==19200) serial_data.baudrate=B19200;
    else if(x==38400) serial_data.baudrate=B38400;
    else if(x==57600) serial_data.baudrate=B57600;
    else if(x==115200) serial_data.baudrate=B115200;
    else if(x==230400) serial_data.baudrate=B230400;
    else
        return -1;
  return 0;
}
