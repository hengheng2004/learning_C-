#include"employee.h"

Employee::Employee(int id, string name, int dId)
{
    m_Id = id;
    m_Name = name;
    m_DeptId = dId;
}

Employee::~Employee()
{

}

void Employee::showInfo()
{
    cout<<"职工编号: "<<m_Id
    <<"\t职工姓名: "<<m_Name
    <<"\t岗位: "<<this->getDeptName()
    <<"\t岗位职责: 完成经理交给的任务"<<endl;
}

string Employee::getDeptName()
{
    return string("员工");
}