#include <iostream>
#include <string>
#include <streambuf>
#include <ostream>
#include "chatserver.h"
#include <sstream>
int main()
{
    ChatServer* server = new ChatServer();
    server->init();
    server->run();

    return 0;
}
