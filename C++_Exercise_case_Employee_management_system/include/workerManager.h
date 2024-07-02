#pragma once//防止头文件重复包含
#include<iostream>
#include<fstream>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;

#define FILENAME "emFile.txt"

//WorkManager类
class WorkerManager
{
public:
    //构造函数
    WorkerManager();

    //析构函数
    ~WorkerManager();

    //展示菜单
    void show_Menu();

    //退出系统
    void exitSystem();

    //添加职工
    void Add_Emp();

    //保存文件
    void save();

    //统计文件中人数
    int get_EmpNum();

    //初始化员工
    void init_Emp();

    //显示职工
    void Show_Emp();

    //按照职工编号判断职工是否存在，存在返回在数组中位置，不存在返回-1
    int IsExist(int id);

    //删除职工
    void Del_Emp();

    //修改职工
    void Mod_Emp();

    //查找职工
    void Find_Emp();

    //排序职工
    void Sort_Emp();

    //清空文件
    void Clean_File();

    int m_EmpNum;//记录文件中人数个数
    Worker ** m_EmpArray;//员工数组的指针
    bool m_FileIsEmpty;//标志文件是否为空
};