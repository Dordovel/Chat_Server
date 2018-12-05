//
// Created by Dordovel on 10/30/2018.
//

#ifndef UNTITLED1_IVIEW_H
#define UNTITLED1_IVIEW_H


class IView
{
public:
    virtual void printMessage(char* message)=0;
    virtual ~IView(){};
};


#endif //UNTITLED1_IVIEW_H
