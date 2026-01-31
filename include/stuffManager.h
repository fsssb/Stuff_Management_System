#pragma once
#include <iostream>
#include "stuff.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "stuffFile.txt"

using namespace std;

class StuffManager
{
public:

    //构造函数
    StuffManager();

    //展示菜单
    void showMenu(StuffManager& vm);

    //退出系统
    void exitSystem();

    //添加职工函数
    void add_Stuff();

    //保存文件
    void saveFile();

    //获取职工人数
    int GetStuffNum();

    //初始化员工
    void initStuff();

    //显示职工信息
    void showStuffInfo();

    //职工是否在系统里
    int isExist(int id);

    //删除离职职工(按职工ID删除)
    void delStuff();

    //修改职工信息
    void modify_Stuff();

    //查找职工
    void findStuff();

    //清理屏幕并暂停
    void CleanAndPause();

    //析构函数
    ~StuffManager();

private:

    //员工数组的指针
    Stuff** m_StuffArray;

    //记录当前文件中的人员个数
    int m_StuffNum;

    //文件是否为空的标志
    bool m_FileIsEmpty;

   

    
};