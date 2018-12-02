//
// Created by Dordovel on 08.10.2018.
//

#ifdef __linux__

#include "Server.h"

Server::Server()= default;

bool Server::startServer()
{

    sock=socket(AF_INET,SOCK_STREAM,0);

    if(sock<0)
    {
        error_code = sock;
        return false;
    }
    else
        {
            addr_in.sin_family=AF_INET;
            addr_in.sin_port=htons(port);
            addr_in.sin_addr.s_addr=INADDR_ANY;
        }

        return true;

}

bool Server::binding()
{
    bool flag= false;

    if((error_code=bind(sock,(struct sockaddr *)&addr_in,sizeAddr_in))<0)
    {

    }
    else
        {
            flag = true;
        }

    return flag;
}

void Server::listenning()
{

    if((error_code=listen(sock,SOMAXCONN))<0)

    else
    {
        if((read_write=accept(sock,(struct sockaddr *)&addr_in,(socklen_t*) &sizeAddr_in))<0)
        {
            error_code = read_write;
        }

        else
        {
            listenFlag=false;
        }

    }

    listenFlag=true;

}

bool Server::writing()
{
    if ((read_write=send(read_write,buffer, sizeof(buffer),0))<0)
    {
        return false;
    }
    return true;
}

bool Server::reading()
{
    if((read_write=recv(read_write,buffer,sizeof(buffer),0))<0)
    {
        return false;
    }
    return true;
}

int Server::getErrorCode() {
    return error_code;
}
char *Server::getMessage()
{
    return buffer;
}


Server::~Server() {}

bool Server::getListenFlag()
{
    return listenFlag;
}

#endif