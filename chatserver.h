#ifndef CHATSERVER_H
#define CHATSERVER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "jsoncpp/json/json.h"
#define MAX_BUFF_SIZE 1400
#include <map>
#include "client.h"
#include <thread>
class ChatServer
{
public:
    ChatServer();
    void run();
    void init();
    void send_mess_to_all(std::string message);
    void send_mess(std::string client_id, std::string message);
    std::string recive_mess();
    void close_connection();
    void dissconnect(std::string client_id);
    void register_client(std::string client_id, std::string client_pass);
    void login_client(std::string client_id, std::string client_pass);
    bool is_register(std::string client_id, std::string client_pass);
private:
    void send_mess(int client_socket, std::string mess);
    int sendall(int s, const char *buf, int len, int flags);
    std::map<std::string, int> clients;
    void on_client_connect(int client_socket);
    unsigned short int server_port = 4345;
    int server_sock;
    struct sockaddr_in bind_addr;
    int bytes_read;
    std::string create_resp(int type, std::string body);
};

#endif // CHATSERVER_H
