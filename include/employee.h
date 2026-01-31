#pragma once
#include <iostream>
#include "stuff.h"



class Employee: public Stuff
{
public:

    Employee(int id,std::string name,int dId);
    virtual void showInfo();
    virtual std::string getDeptName();
};