#include <inc/main.h>

static void *net_thread(void *ptr)
{
    while(1)
    {
        net_connection('c',256,67677,"127.0.01");

    }
    return (void *) 0;
}
static void *serial_thread(void *ptr)
{
    while(1)
    {
        serial_comm("/dev/ttyUSB0",9600,256,'s');


    }
    return (void *) 0;
}



int main()
{
    pthread_t nettcp;
    pthread_t terminal;

    pthread_create(&nettcp,NULL,net_thread,NULL);
    pthread_create(&terminal,NULL,serial_thread,NULL);


    pthread_join(nettcp,NULL);
    pthread_join(terminal,NULL);

    return 0;
}
