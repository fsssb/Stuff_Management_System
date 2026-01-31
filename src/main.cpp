#include <iostream>
#include "stuffManager.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"
#include "stuff.h"

#include <unistd.h>
#include <termios.h>


inline void pauseLinux()
{
    write(STDOUT_FILENO, "\n按回车继续...", 18);
    char c;
    read(STDIN_FILENO, &c, 1);
}


// void test01()  //代码重复，可以改进！
// {
//     Stuff* stuff = nullptr;
//     stuff = new Employee(1111,"fsssb",6);    
//     stuff->showInfo();
//     delete stuff;
//     stuff = nullptr;

//     stuff = new Manager(2222,"czy",5);    
//     stuff->showInfo();
//     delete stuff;
//     stuff = nullptr;

//     stuff = new Boss(3333,"HITSZ",9);    
//     stuff->showInfo();
//     delete stuff;
//     stuff = nullptr;
// }

int main()
{

    // test01();

    //实例化管理者
    StuffManager sm;

    int choice = 0;
    while(true)
    {
        //调用展示菜单成员函数
        sm.showMenu(sm);
        cout << "请输入您的选择：" << endl;

        cin >> choice;
        
        switch(choice)
        {
            case 0://退出系统
                sm.exitSystem();
                break;
            case 1://添加职工
                sm.add_Stuff();
                break;
            case 2://显示职工
                sm.showStuffInfo();
                break;
            case 3://删除职工
                sm.delStuff();
                break;
            case 4://修改职工
                break;
            case 5://查找职工
                break;
            case 6://排序职工
                break;
            case 7://清空文件
                break;
            default:
                system("clear");
                break;
        }
    }

    //调用展示菜单成员函数
    sm.showMenu(sm);
    return 0;

}

