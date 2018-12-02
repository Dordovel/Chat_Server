//
// Created by Dordovel on 08.10.2018.
//
#ifdef _WIN32

#include "Server.h"
Server::Server() = default;

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
    }

    socketList.push_back(read_write);

    listenFlag = true;
}

bool Server::reading()
{
    if ( SOCKET_ERROR == recv( read_write, buffer, 20, 0 ) )
    {
        error_code=WSAGetLastError();
        closesocket( read_write );
        return false;
    }

    return true;
}

bool Server::writing()
{
    for(int a=0; a<socketList.size();a++)
    {
        if (SOCKET_ERROR == send(socketList[a], buffer, 20, 0))
        {
            error_code = WSAGetLastError();
        }
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

#endif