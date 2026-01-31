#include "stuffManager.h"
#include <iostream>
using namespace std;



StuffManager::StuffManager()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    //文件不存在的情况
    if (!ifs.is_open())
    {
        cout << "文件不存在！" << endl;
        this->m_FileIsEmpty = true;//文件为空标志为真
        this->m_StuffNum = 0;
        this->m_StuffArray = nullptr;
        ifs.close();
        return;
    }

    //文件存在但为空的情况
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        cout << "文件为空！" << endl;
        this->m_FileIsEmpty = true;//文件为空标志为真
        this->m_StuffNum = 0;
        this->m_StuffArray = nullptr;
        ifs.close();
        return;
    }  

    //文件存在且不为空的情况 
    int num = this->GetStuffNum();
    // cout << "职工个数为：" << num << endl;

    this->m_StuffNum = num;

    //将文件中的数据存到数组中
    this->initStuff();
    
    //文件为空标志为假！
    this->m_FileIsEmpty = false;

    // for(int i = 0;i < this->m_StuffNum;i++)
    // {
    //     cout << "职工编号： " << this->m_StuffArray[i]->m_Id
    //         <<"\t职工姓名：" << this->m_StuffArray[i]->m_name
    //         <<"\t部门编号：" << this->m_StuffArray[i]->m_DeptId 
    //         << endl;
    // }
    


}

StuffManager::~StuffManager()
{
    if (this->m_StuffArray != nullptr)
    {
        for (int i = 0; i < this->m_StuffNum; i++)
        {   
            if (this->m_StuffArray[i] != nullptr)
            {
            //删除每一个职工对象
            delete this->m_StuffArray[i];
            }
        }
        //删除职工数组
        delete[] this->m_StuffArray;
    }
}

void StuffManager::showMenu(StuffManager& vm)
{
    cout << "--------------------------------------" << endl;
    cout << "--------欢迎使用职工管理系统！--------" << endl;
    cout << "--------------------------------------" << endl;
    cout << endl;
    cout << "\t0.退出管理系统" << endl;
    cout << "\t1.增加职工信息" << endl;
    cout << "\t2.显示职工信息" << endl;
    cout << "\t3.删除离职员工" << endl;
    cout << "\t4.修改职工信息" << endl;
    cout << "\t5.查找职工信息" << endl;
    cout << "\t6.按照编号排序" << endl;
    cout << "\t7.清空所有文档" << endl;
    cout << endl;
    cout << "--------------------------------------" << endl;
    cout << endl;
}

void StuffManager::exitSystem()
{
    system("clear");
    cout << "欢迎下次使用！" << endl;

    //清空屏幕并退出
    this->CleanAndPause();
    
    exit(0);
}



void StuffManager::add_Stuff()
{
    cout << "请输入要添加的职工数量：" << endl;
    int addNum = 0;
    cin >> addNum;

    if (addNum > 0)
    {
        //计算一下新的空间的大小
        int newSize = this->m_StuffNum + addNum;

        //开辟一个新空间
        Stuff** newSpace = new Stuff*[newSize];

        //将原来空间下的数据拷贝到新空间下
        if (this->m_StuffArray != nullptr)
        {
            for (int i = 0; i < this->m_StuffNum; i++)
            {
                newSpace[i] = this->m_StuffArray[i];
            }

        }
        //输入新数据
        for (int i = 0; i < addNum; i++)
        {
            int id;
            string name;
            int dSelect;
            cout << "请输入第 " << i + 1 << " 个新职工的编号：" << endl;
            cin >> id;
            cout << "请输入第 " << i + 1 << " 个新职工的姓名：" << endl;
            cin >> name;
            cout << "请选择该职工的岗位：" << endl;
            cout << "\t1.普通员工" << endl;
            cout << "\t2.经理" << endl;
            cout << "\t3.老板" << endl;
            cin >> dSelect;

            //根据岗位选择创建不同类型的职工对象
            Stuff* newStuff = nullptr;
            switch (dSelect)
            {
                case 1:
                    newStuff = new Employee(id, name, 1);
                    break;
                case 2:
                    newStuff = new Manager(id, name, 2);
                    break;
                case 3:
                    newStuff = new Boss(id, name, 3);
                    break;
                default:
                    cout << "输入有误！" << endl;
                    delete[] newSpace; 
                    return; // 如果输入无效，直接返回
            }

            //将新职工添加到数组中
            newSpace[this->m_StuffNum + i] = newStuff;
        }

        //释放原有空间
        delete[] this->m_StuffArray;    
        this->m_StuffArray = nullptr;

        //更新成员变量
        this->m_StuffArray = newSpace;
        this->m_StuffNum = newSize;

        //更新文件为空标志
        this->m_FileIsEmpty = false;

        //t提示添加成功
        cout << "成功添加 " << addNum << " 名新职工！" << endl; 
        
        //保存文件
        this->saveFile();

        //清理屏幕并暂停
        this->CleanAndPause();

    }

    else
    {
        cout << "输入有误！" << endl;
    }
}



void StuffManager::CleanAndPause()
{
    cout << "请按任意键继续..." << endl;
    cin.ignore(1024, '\n');
    cin.get();
    system("clear");
}
//保存文件
void StuffManager::saveFile()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);   
    for (int i = 0; i < this->m_StuffNum; i++)
    {
        ofs << this->m_StuffArray[i]->m_Id << "\t "
            << this->m_StuffArray[i]->m_name << "\t "
            << this->m_StuffArray[i]->m_DeptId << endl;
    }
    ofs.close();
}


int StuffManager::GetStuffNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in); //读文件

    int id;
    string name;
    int dId;

    int num = 0;

    while (ifs >> id && ifs >> name && ifs >> dId) 
    {
        num++;
    }

    this->m_StuffNum = num;

    ifs.close();

    return num;
}

void StuffManager::initStuff()
{
    //初始化职工
    ifstream ifs;
    ifs.open(FILENAME, ios::in); //读文件

    int id;
    string name;
    int dId;
    int index = 0;
    
    //开辟内存
    this->m_StuffArray = new Stuff * [this->m_StuffNum];
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        Stuff* s = nullptr;
        switch (dId)
        {
            case 1:
                s = new Employee(id, name, dId);
                break;
            case 2:
                s = new Manager(id, name, dId);
                break;
            case 3:
                s = new Boss(id, name, dId);
                break;
        }
        this->m_StuffArray[index] = s;
        index++;
    }
    ifs.close();
}

void StuffManager::showStuffInfo()
{
    if(this->m_FileIsEmpty)
    {
        cout <<"文件不存在或者文件记录为空！"<< endl;
    }

    else
    {
        for(int i = 0;i < this->m_StuffNum;i++)
        {
            this->m_StuffArray[i]->showInfo();
        }
    }

    this->CleanAndPause();
}


int StuffManager::isExist(int id)
{
    int index = -1;
    for(int i = 0;i < this->m_StuffNum; i++)
    {
        if(this->m_StuffArray[i]->m_Id == id)
        {
            index = i;
            break;
        }
    }
    return index;
}

 void StuffManager::delStuff()
 {
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空！" << endl;
    }

    else
    {
        int id;
        cout << "请输入您要删除的职工ID:" << endl;
        cin >> id;

        if(this->isExist(id) == -1)
        {
            cout << "系统中不存在该员工！" << endl; 
        }

        else
        {
            int target = this->isExist(id);
            for (int i = target; i < this->m_StuffNum - 1; i++) //边界条件
             {
                this->m_StuffArray[i] = this->m_StuffArray[i+1];
            }
            this->m_StuffNum--;

            //数据重新写入文件中
            this->saveFile();
            
            cout << " 已经成功删除该员工！" << endl;
        }
    }

    this->CleanAndPause();

 }


