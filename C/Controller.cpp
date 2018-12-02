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

    void Controller::listen()
    {
       this->server->listenning();
    }

    bool Controller::getListenFlag()
    {
        return this->server->getListenFlag();
    }

    bool Controller::read()
    {
        return server->reading();
    }

    bool Controller::write()
    {
        return server->writing();
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