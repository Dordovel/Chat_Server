//
// Created by Dordovel on 08.10.2018.
//
#ifdef _WIN32

#include <inaddr.h>
#include "Server.h"
Server::Server(int port)
{
    this->port=port;
};


bool Server::startServer()
{
    if ( !FAILED( WSAStartup( WINSOCK_VERSION, &data ) ) )
    {
        if ( INVALID_SOCKET == ( sock = socket( AF_INET, SOCK_STREAM, 0 ) ) )
        {
            error_code=WSAGetLastError();
            return false;
        }
        else
        {
            addr_in.sin_addr.S_un.S_addr = htonl( INADDR_ANY );
            addr_in.sin_family = AF_INET;
            addr_in.sin_port = htons( port );
        }

    }
    else
    {
        error_code=WSAGetLastError();
        WSACleanup();
        return false;
    }

    return true;
}

bool Server::binding()
{
    if ( SOCKET_ERROR == ( bind( sock, ( sockaddr* ) &addr_in, sizeAddr_in ) ) )
    {
        error_code=WSAGetLastError();
        closesocket( sock );
        return false;
    }

    return true;
}

bool Server::listenning()
{
    if ( SOCKET_ERROR==listen( sock, SOMAXCONN ) )
    {
        error_code=WSAGetLastError();
        closesocket( sock );
        return false;
    }
    else
    {

        if ( INVALID_SOCKET == ( read_write = accept( sock, ( sockaddr* ) &addr_in, &sizeAddr_in ) ) )
        {
            error_code=WSAGetLastError();
            closesocket( sock );
            return false;

        }
        else
            {
                int size=sizeof(client_addr);

                getsockname(read_write,(sockaddr *)&client_addr, & size);

                socketList.push_back(read_write);

                return true;
            }
    }

}

bool Server::reading(SOCKET param)
{
    if ( SOCKET_ERROR == recv( param, buffer, 20, 0 ) )
    {
        error_code=WSAGetLastError();
        closesocket( read_write );
        return false;
    }

    return true;
}

bool Server::writing(SOCKET param, char* message)
{
        if (SOCKET_ERROR == send(param, message, 20, 0))
        {
            error_code = WSAGetLastError();
            closesocket(param);

            return false;
        }

    return true;
}

Server::~Server()
{

    closesocket( sock );

    close(read_write);

    for(int a=0;a<socketList.size();a++)
    {
        closesocket(socketList[a]);
    }

    WSACleanup();

}

int Server::getErrorCode() {
    return error_code;
}

char *Server::getMessage()
{
    return buffer;
}

unsigned long long Server::getConnectionClientCount()
{
    return this->socketList.size();
}

bool Server::Request()
{
    for(int a=0;a<socketList.size();++a)
    {
        if (writing(socketList[a], (char *) "request"))
        {
            if (reading(socketList[a]))
            {

                if (!strcmp(this->buffer, "200"))
                {
                    return false;
                }
                else
                {
                    std::cout<<"Data "<<buffer<<std::endl;

                    return Response();
                }

            }
        } else
            {

                std::cout<<"Delete Client ";
                this->getClientProperties();

                closesocket(socketList[a]);
                socketList.erase(socketList.begin()+a);
            }

    }
}

bool Server::Response()
{
    for (int i = 0; i <socketList.size(); ++i)
    {
        writing(socketList[i],buffer);
    }
}


void Server::getClientProperties()
{
    std::cout<<client_addr.sin_addr.S_un.S_addr<<"   "<<client_addr.sin_port<<std::endl;
}

#endif