//
// Created by Dordovel on 08.10.2018.
//

#ifndef UNTITLED1_SERVER_H
#define UNTITLED1_SERVER_H

#include <iostream>
#include "../Interface/IServer.h"
#include <vector>

using namespace std;


#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>


#elif __linux__
#include <sys/socket.h>

#include <netinet/in.h>

#define WSADATA void*
#define SOCKET int


#endif

    class Server: public IServer
    {
        private:

                WSADATA data;
                SOCKET sock;
                sockaddr_in addr_in;
                int port = 6000;
                int sizeAddr_in = sizeof(addr_in);
                char buffer[20];
                long error_code=0;

                bool listenFlag;

                SOCKET read_write;

                std::vector<SOCKET> socketList;

        public:

                Server();

                ~Server();

                bool startServer() override;

                bool binding() override;

                void listenning() override;

                bool reading() override;

                bool writing() override;

                int getErrorCode() override;

                char * getMessage() override;

                bool getListenFlag() override;
    };


#endif //UNTITLED1_SERVER_H