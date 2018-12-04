//
// Created by Dordovel on 10/30/2018.
//

#ifndef UNTITLED1_CONTROLLER_H
#define UNTITLED1_CONTROLLER_H

#include "../N/Server.h"
#include "../V/View.h"


class Controller
{
    private:
        IServer * server;
        IView * view;
        bool serverStatus;

    public:
        Controller(IServer *,IView *);

        ~Controller();

        bool bind();

        bool listen();

        bool read_write();

        bool start();

        void printMessage();

        void printErrorCode();

        bool getServerStatus();

        int getConnectionClientCount();

        void getClientPropirties();

        bool Request();
};


#endif //UNTITLED1_CONTROLLER_H
