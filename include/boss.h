#pragma once
#include <iostream>
#include "stuff.h"



class Boss: public Stuff
{
public:

    Boss(int id,std::string name,int dId);
    virtual void showInfo();
    virtual std::string getDeptName();
};