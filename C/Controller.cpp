//
// Created by Dordovel on 10/30/2018.
//

#include "Controller.h"

    Controller::Controller(IServer *server,IView *view)
    {
        this->view=view;
        this->server=server;
    }

    Controller::~Controller()
    {
        serverStatus=false;
        delete view;
        view = nullptr;
        delete server;
        server = nullptr;
    }


    bool Controller::bind()
    {
        return server->binding();
    }

    bool Controller::listen()
    {
        return this->server->listenning();
    }

    bool Controller::read_write()
    {
        return this->server->Request();
    }

    bool Controller::start()
    {
        serverStatus=server->startServer();
        return serverStatus;
    }

    void Controller::printMessage()
    {
        view->printMessage(server->getMessage());
    }

    void Controller::printErrorCode()
    {
        view->printMessage((char*)(to_string(server->getErrorCode())).c_str());
    }

    bool Controller::getServerStatus()
    {
        return this->serverStatus;
    }

    void Controller::getClientPropirties()
    {
        this->server->getClientProperties();
    }