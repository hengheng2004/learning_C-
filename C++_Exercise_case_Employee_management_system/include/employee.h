#pragma once
#include"worker.h"

//普通员工类
class Employee: public Worker
{
public:
    //构造函数
    Employee(int id, string name, int dId);

    //析构函数
    ~Employee();

    //显示个人信息
    void showInfo();

    //获取职工岗位名称
    string getDeptName();
};