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
        {
                listenFlag=false;
                return;
        }

    else
    {
        if((read_write=accept(sock,(struct sockaddr *)&addr_in,(socklen_t*) &sizeAddr_in))<0)
        {
            error_code = read_write;
            listenFlag=false;
            return;
        }

        else
        {
            socketList.push_back(read_write);

            listenFlag=true;
        }

    }

}

bool Server::writing(SOCKET param,char* message)
{
    if ((read_write=send(param,message, sizeof(message),0))<0)
    {
        return false;
    }
    return true;
}

bool Server::reading(SOCKET param)
{
    if((read_write=recv(param,buffer,sizeof(buffer),0))<0)
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

unsigned long long Server::getConnectionClientCount()
{
    return this->socketList.size();
}


bool Server::Request()
{
    for(int a=0;a<socketList.size();++a)
    {
        if(writing(socketList[a],(char*)"request"))
        {
            if(reading(socketList[a]))
            {

                if (!strcmp(this->buffer,"200"))
                {
                    return false;
                }
                else
                {
                    Response();
                }

            }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

        return true;
    }

bool Server::Response()
{
    for (int i = 0; i < socketList.size(); ++i)
    {
        writing(socketList[i], buffer);
    }
}


#endif