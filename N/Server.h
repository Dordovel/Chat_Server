//
// Created by Dordovel on 08.10.2018.
//

#ifndef UNTITLED1_SERVER_H
#define UNTITLED1_SERVER_H

#ifdef _WIN32

#include <WinSock2.h>
#include <ws2tcpip.h>


#elif __linux__

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#define WSADATA void*
#define SOCKET int


#endif


#include <iostream>
#include "../Interface/IServer.h"
#include <vector>
#include<cstring>

using namespace std;

    class Server: public IServer
    {
        private:

                WSADATA data;
                SOCKET sock;
                sockaddr_in addr_in;
                int port;
                int sizeAddr_in = sizeof(addr_in);
                char buffer[20];
                long error_code=0;

                sockaddr_in client_addr;

                SOCKET read_write;

                fd_set set,read_set,write_set;

                struct timeval time;

                std::vector<SOCKET> socketList;

        public:

                Server(int port);

                ~Server() override;

                bool startServer() override;

                bool binding() override;

                bool listenning() override;

                bool reading(SOCKET param);

                bool writing(SOCKET param,char* message);

                int getErrorCode() override;

                char * getMessage() override;

                void Response();

                bool Request();

                unsigned long long getConnectionClientCount() override;

                void getClientProperties() override;
    };



#endif //UNTITLED1_SERVER_H