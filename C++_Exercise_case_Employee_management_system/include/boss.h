#pragma once
#include"worker.h"

//老板类
class Boss: public Worker
{
public:
    //构造函数
    Boss(int id, string name, int dId);

    //析构函数
    ~Boss();

    //显示个人信息
    void showInfo();

    //获取岗位名称
    string getDeptName();  
};