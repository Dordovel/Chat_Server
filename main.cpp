#include <iostream>

#include "C/Controller.h"
#include <pthread.h>

#if (__linux__)

#include<X11/Xlib.h>

#endif

class Thread
{
public:

    static void* listen(void * param)
    {
        Controller * controller = (Controller*) param;

        while(true)
        {
            controller->listen();
        }
    }

};


int main()
{

#if (__linux__)

    if(!XInitThreads())return 0;

#endif

    Controller *controller=new Controller(new Server(),new View());

    pthread_t thread;
    pthread_attr_t attr;

    pthread_attr_init(&attr);


    if(controller->start())
    {
        if (controller->bind())
        {
            controller->listen();

            if (controller->getListenFlag())
            {
                pthread_create(&thread, &attr, Thread::listen, controller);

                while (true)
                {
                    if (controller->read())
                    {
                        std::cout << "New Message  ";
                        controller->printMessage();

                        controller->write();
                    }
                }
            }
        }
    }

    controller->printErrorCode();

    delete controller;

    return 0;
}