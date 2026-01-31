#pragma once
#include <iostream>
#include "stuff.h"



class Manager: public Stuff
{
public:

    Manager(int id,std::string name,int dId);
    virtual void showInfo();
    virtual std::string getDeptName();
};