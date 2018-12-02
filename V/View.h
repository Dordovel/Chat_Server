//
// Created by Dordovel on 10/30/2018.
//

#ifndef UNTITLED1_VIEW_H
#define UNTITLED1_VIEW_H

#include <iostream>
#include "../Interface/IView.h"

class View: public IView
{
    public:

        void printMessage(char* message) override;

};

#endif //UNTITLED1_VIEW_H
