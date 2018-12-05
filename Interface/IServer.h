//
// Created by Dordovel on 10/30/2018.
//

#ifndef UNTITLED1_ISERVER_H
#define UNTITLED1_ISERVER_H


class IServer
{

public:

    virtual ~IServer(){};

    virtual bool binding()=0;

    virtual bool listenning()=0;

    virtual bool Request()=0;

    virtual bool startServer()=0;

    virtual int getErrorCode()=0;

    virtual char * getMessage()=0;

    virtual unsigned long long getConnectionClientCount()=0;

    virtual void getClientProperties()=0;

};


#endif //UNTITLED1_ISERVER_H
