#include "chatserver.h"
#include <mutex>
ChatServer::ChatServer()
{
}

int ChatServer::sendall(int s, const char *buf, int len, int flags)
{
    int total = 0;
    int n;

    while(total < len)
    {
        n = send(s, buf+total, len-total, flags);
        if(n == -1) { break; }
        total += n;
    }

    return (n==-1 ? -1 : total);
}


void ChatServer::run()
{
    while (true) {
        int client_sock = accept(server_sock, nullptr, nullptr);

        std::thread thread1(&ChatServer::on_client_connect, this, client_sock);
        thread1.detach();

    }
}

void ChatServer::init()
{
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    //check for error
    if (server_sock < 0)
    {
        perror("Socket");
        exit(1);
    }
    bind_addr.sin_family = AF_INET;
    bind_addr.sin_port = htons(server_port);
    bind_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //check for error
    if (bind(server_sock, (struct sockaddr *)&bind_addr, sizeof(bind_addr)) < 0)
    {
        perror("Bind");
        exit(1);
    }
   if( listen(server_sock, 50))
   {
       perror("Listen");
       exit(1);
   }

}


void ChatServer::send_mess(std::string client_id, std::string message)
{

}

std::string ChatServer::recive_mess()
{

}

void ChatServer::close_connection()
{

}

void ChatServer::register_client(std::string client_id, std::string client_pass)
{
    return;
}

bool ChatServer::is_register(std::string client_id, std::string client_pass)
{
    return true;
}

void ChatServer::send_mess(int client_socket, std::string mess)
{
   const  char* message = mess.c_str();
    sendall(client_socket, message, strlen(message), 0);
}

void ChatServer::on_client_connect(int client_socket)
{

    std::cout<<"Client connected, id: "<<client_socket<<std::endl;

    char buff[MAX_BUFF_SIZE];

    std::cout<<"Thread id: "<<std::this_thread::get_id()<<std::endl;
    while (true) {
               bytes_read = recv(client_socket, buff, MAX_BUFF_SIZE, 0);
               if(bytes_read <= 0) break;
               std::cout<<buff<<std::endl;
               Json::Value jmess;
               Json::Reader jreader;
               jreader.parse(buff, buff + MAX_BUFF_SIZE, jmess, true);
               std::cout<<"Jsoon value: "<<jmess<<std::endl;

               if(jmess["type"] == "REG")
               {
                   std::string user_name = jmess["user"]["id"].asString();
                   std::string user_pass = jmess["user"]["pass"].asString();
                   //check for register user
                   if(!is_register(user_name, user_pass))
                   {
                       register_client(user_name, user_pass);
                   }
                   else{
                        send_mess(client_socket, create_resp(0, ""));
                   }


               }
               else{
                   send_mess(client_socket, "OK");
               }

               std::cout<<"Server send"<<std::endl;
               bzero(buff, sizeof (buff));
            }
    close(client_socket);
}

std::string ChatServer::create_resp(int type, std::string body = "")
{
    Json::Value message;
    switch (type) {
    case 0://error: username is allready taked
    {
         message["status"] = "REGERR";
         message["type"] = "ERR";
         message["body"] = "Username is allready taked. Please choose somethink other.";
    }
    }

    message["timestamp"] = "00.00.00";

    return message.toStyledString();
}
