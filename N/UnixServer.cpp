//
// Created by Dordovel on 08.10.2018.
//

#ifdef __linux__

#include "Server.h"

Server::Server(int port)
{
    this->port=port;
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

    if(FD_ISSET(param,&write_set))
    {
        FD_CLR(param, &write_set);


        if (strcmp(message, "200") ) {
            std::cout << message << std::endl;
        }


        if ((read_write = send(param, message, sizeof(message), 0)) < 0)
        {
            return false;
        }
    }
    return true;
}

bool Server::reading(SOCKET param)
{
    if(FD_ISSET(param,&read_set))
    {
        FD_CLR(param, &read_set);

        if ((read_write = recv(param, buffer, sizeof(buffer), 0)) < 0)
        {
            return false;
        }

    }
    return true;
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
        FD_ZERO(&write_set);
        FD_ZERO(&read_set);

        FD_SET(socketList[a],&read_set);
        FD_SET(socketList[a],&write_set);

        if(select(FD_SETSIZE,&read_set,&write_set,NULL,&time)<0)
        {
            continue;
        }

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