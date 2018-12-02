#include <iostream>

#include "C/Controller.h"
#include <pthread.h>
#include <chrono>
#include <thread>

#if (__linux__)

#include<X11/Xlib.h>

#endif

class Thread
{
public:

    static void* listen(void * param)
    {
        Controller * controller = (Controller*) param;

        while(controller->getServerStatus())
        {
            controller->listen();
        }

        pthread_exit(0);
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
                    if (controller->read_write())
                    {
                        std::cout << "New Message  ";
                        controller->printMessage();
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
            }
        }
    }

    controller->printErrorCode();

    delete controller;

    return 0;
}