/*
 * Author Tarkan Dalay
 * mail: tarkandalay52@gmail.com
 * date: 28/11/2016
 * rev:0.02b
 *
 * */

#include <inc/main.h>




static void *net_thread(void *ptr)
{
    while(1)
    {
        net_connection(socket_1);

    }
    return (void *) 0;
}
static void *serial_thread(void *ptr)
{
    while(1)
    {
        serial_comm(serial_data);


    }
    return (void *) 0;
}



int main()
{
    socket_1.buff_size=256;
    socket_1.ip="127.0.01";
    socket_1.portnum=67677;
    socket_1.socket_status='s';

    serial_data.baudrate=9600;
    serial_data.buff=256;
    serial_data.display='s';
    serial_data.port="/dev/ttyUSB0";

    pthread_t nettcp;
    pthread_t terminal;

    pthread_create(&nettcp,NULL,net_thread,NULL);
    pthread_create(&terminal,NULL,serial_thread,NULL);


    pthread_join(nettcp,NULL);
    pthread_join(terminal,NULL);

    return 0;
}
