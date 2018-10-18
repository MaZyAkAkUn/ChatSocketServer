#ifndef SERVER_H
#define SERVER_H
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <sched.h>
//#include <pthread.h>
#include <thread>

class Server
{
public:
    Server(unsigned short int port);
    void init();
    void run();
private:
    void client_proc_func();
    unsigned short int server_port;
    int server_socket;

};

#endif // SERVER_H
