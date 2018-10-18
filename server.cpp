#include "server.h"

Server::Server(unsigned short int port)
{

    server_port = port;
    init();
    printf("Constr startedd");

}

void Server::client_proc_func()
{
    printf("Client proc func was called!!!");
}

void Server::init()
{
    printf("Init started");
    server_socket = socket(AF_INET, SOCK_STREAM,  0);
    struct sockaddr_in bind_addr_struct;

    bzero(&bind_addr_struct, sizeof (bind_addr_struct));
    bind_addr_struct.sin_family = AF_INET;
    bind_addr_struct.sin_port = htons(server_port);
    bind_addr_struct.sin_addr.s_addr = INADDR_ANY;
    printf("Bind started");

    bind(server_socket,(struct sockaddr *)&bind_addr_struct, sizeof (bind_addr_struct));
    printf("Bind ended");
}

void Server::run()
{

    printf("Run started");
    struct sockaddr client_addr;
    bzero(&client_addr, sizeof (client_addr));
    listen(server_socket, 100);
    printf("Listening...");
    for(;;)
    {
        unsigned int size = sizeof (client_addr);

        int client_socket;
        client_socket = accept(server_socket, &client_addr, &size);//accept connection and create client-socket

        if(client_socket > 0){

        printf("Socket Created!");
        sleep(5);
        printf("fegrthh");
        close(client_socket);
        }
    }
}

























