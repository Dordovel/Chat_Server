//
// Created by Dordovel on 08.10.2018.
//

#ifdef __linux__

#include "Server.h"

Server::Server(int port)
{
    this->port=port;

    time.tv_sec=15;
    time.tv_usec=0;
};

bool Server::startServer()
{

    sock=socket(AF_INET,SOCK_STREAM,0);

    if(sock<0)
    {
        error_code = sock;
        close(sock);
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
    if((error_code=bind(sock,(struct sockaddr *)&addr_in,sizeAddr_in))<0)
    {
        close(sock);
        return false;
    }

    return true;
}



bool Server::listenning()
{

    if((error_code=listen(sock,SOMAXCONN))<0)
        {
          close(sock);
          return false;
        }

    else
    {
        if((read_write=accept(sock,(struct sockaddr *)&addr_in,(socklen_t*) &sizeAddr_in))<0)
        {
            error_code = read_write;
            close(sock);
            return false;
        }

        else
        {
            socklen_t size=sizeof(client_addr);

            getsockname(read_write,(sockaddr *)&client_addr,& size);

            socketList.push_back(read_write);

            return true;
        }

    }

}



bool Server::writing(SOCKET param,char* message)
{
    std::cout<<"Response     "<<message<<std::endl;

        if ((error_code = send(param, message, buffer_size, 0)) < 0)
        {
            return false;
        }

   return true;
}



bool Server::reading(SOCKET param)
{
    FD_ZERO(&set);
    FD_SET(param,&set);

    if(select(FD_SETSIZE,&set,NULL,NULL,&time)>0)
    {
        if(FD_ISSET(param,&set))
        {
            FD_CLR(param,&set);

            if ((error_code = recv(param, buffer, buffer_size, 0)) > 0)
            {
                return true;
            }
        }

    }
    return false;
}



int Server::getErrorCode()
{
    return error_code;
}


char *Server::getMessage()
{
    return buffer;
}


Server::~Server()
{
    close( sock );
    close(read_write);

    for(unsigned int a=0;a<socketList.size();a++)
    {
        close(socketList[a]);
    }
}


unsigned long long Server::getConnectionClientCount()
{
    return this->socketList.size();
}


bool Server::Request()
{
    for(unsigned int a=0;a<socketList.size();++a)
    {
        if (writing(socketList[a], (char *) "request"))
        {
            if (reading(socketList[a]))
            {
                if (strcmp(this->buffer, "200"))
                {
                    Response();
                }
            }

        }
        else
        {
            std::cout << "Delete Client ";
            this->getClientProperties();

            close(socketList[a]);
            socketList.erase(socketList.begin() + a);
        }
    }

    return true;

}

void Server::Response()
{

    for (unsigned int i = 0; i < socketList.size(); ++i)
    {
        if(!writing(socketList[i], buffer))
       {
           this->getClientProperties();
       }
    }
}


void Server::getClientProperties()
{
    std::cout<<client_addr.sin_addr.s_addr<<"   "<<client_addr.sin_port<<std::endl;
}

#endif