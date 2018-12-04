//
// Created by Dordovel on 08.10.2018.
//
#ifdef _WIN32

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

void Server::listenning()
{
    if ( SOCKET_ERROR==listen( sock, SOMAXCONN ) )
    {
        error_code=WSAGetLastError();
        closesocket( sock );
        listenFlag=false;
        return;
    }
    else
    {

        if ( INVALID_SOCKET == ( read_write = accept( sock, ( sockaddr* ) &addr_in, &sizeAddr_in ) ) )
        {
            error_code=WSAGetLastError();
            closesocket( sock );
            listenFlag=false;
            return;
        }
        else
            {
                getsockname(read_write,(sockaddr_in *)client_addr, sizeof(client_addr));
                socketList.push_back(read_write);
            }
    }


    listenFlag = true;
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

bool Server::getListenFlag()
{
    return listenFlag;
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
                std::cout << buffer << std::endl;

                if (!strcmp(this->buffer, "200"))
                {
                    return false;
                }
                else
                {
                    return Response();
                }
            }
        }
    }
        return true;
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
    std::cout<<client_addr.sin_addr.s_addr<<"   "<<client_addr.sin_port;
}

#endif