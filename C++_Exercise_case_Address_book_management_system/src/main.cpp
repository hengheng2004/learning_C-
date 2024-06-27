#include <iostream>
#include<string>
#define MAX 1000
using namespace std;
//通讯录管理系统
//通讯录是一个可以记录亲人、好友信息的工具
//系统中需要实现的功能如下:
//添加联系人:向通讯录中添加新人，信息包括(姓名、性别、年龄、联系电话、家庭住址)最多记录1000人
//显示联系人:显示通讯录中所有联系人信息
//删除联系人:按照姓名进行删除指定联系人
//查找联系人:按照姓名查看指定联系人信息
//修改联系人:按照姓名重新修改指定联系人
//清空联系人:清空通讯录中所有信息
//退出通讯录:退出当前使用的通讯

//第一步：菜单功能
//封装函数显示该界面
//在main函数调用封装好的函数

//第二步：退出功能
//根据用户不同的选择，进入不同的功能，可以选择switch分支结构，将整个框架进行搭建
//用户选择0时，执行退出，选择其他先不做操作，也不会退出程序

//第三步：添加联系人
//向通讯录中添加新人，信息包括(姓名、性别、年龄、联系电话、家庭住址)最多记录1000人
//设计联系人结构体
//设计通讯录结构体
//main函数中创建通讯录
//封装添加联系人函数
//测试添加联系人功能

//第四步：显示联系人
//封装显示联系人函数
//测试显示联系人功能
//判断如果当前通讯录中没有人员，就提示记录为空，人数大于0，显示通讯录信息

//第五步: 删除联系人
//按照姓名进行删除指定联系人
//封装检测联系人是否存在
//封装删除联系人函数
//测试删除联系人功能
//删除联系人前，先判断是否存在，如果存在删除，不存在提示用户没有要删除的联系人，如果存在返回联系人在通讯录中的位置，不存在返回-1

//第六步：查找联系人
//按照姓名查看指定联系人信息
//封装查找联系人函数
//测试查找指定联系人

//第七步修改联系人
//按照姓名重新修改联系人
//封装修改联系人函数
//测试修改联系人功能

//第八步清空联系人
//将通讯录所有联系人信息清除，只要将通讯录记录的联系人数量置为0，做逻辑清空即可


//显示菜单函数
void showMenu();

//联系人结构体
struct Person
{
    string m_Name;//姓名
    int m_Gender;//性别 1男 2女
    int m_Age;//年龄
    string m_Tel;//联系电话
    string m_Address;//家庭地址

};

//通讯录结构体：维护一个容量为1000的联系人数组，记录通讯录联系人数量
struct AddressBook
{
    Person personArray[MAX];//联系人数组
    int m_Size;//联系人数量
};

//添加联系人函数
void addPerson(AddressBook * abs);

//显示联系人函数
void showPerson(AddressBook * abs);

//判断联系人存在函数
int isExist(AddressBook * abs, string findName);

//删除联系人函数
void delPerson(AddressBook * abs);

//查找联系人函数
void findPerson(AddressBook * abs);

//修改联系人函数
void changePerson(AddressBook * abs);

//清空联系人函数
void clearPerson(AddressBook * abs);


int main()
{
    //创建通讯录变量
    AddressBook abs;

    //初始化联系人数量
    abs.m_Size = 0;

    int select = 0;

    while (true)
    {
        showMenu();//创建用户选择输入变量

        cin>>select;//用户选择输入变量

        switch (select)
        {
        case 1://添加联系人
            addPerson(&abs);//利用地址传递修改实际参数
            break;
        case 2://显示联系人
            showPerson(&abs);
            break;
        case 3://删除联系人
            delPerson(&abs);
            break;
        case 4://查找联系人
            findPerson(&abs);
            break;
        case 5://修改联系人
            changePerson(&abs);
            break;
        case 6://清空联系人
            clearPerson(&abs);
            break;
        default://退出通讯录
            cout<<"欢迎下次使用"<<endl;
            return 0;
            break;
        }
    }
    

    system("pause");

    return 0;
}

//显示菜单函数
void showMenu()
{
    cout<<"**************************"<<endl;
    cout<<"*****  1.添加联系人  *****"<<endl;
    cout<<"*****  2.显示联系人  *****"<<endl;
    cout<<"*****  3.删除联系人  *****"<<endl;
    cout<<"*****  4.查找联系人  *****"<<endl;
    cout<<"*****  5.修改联系人  *****"<<endl;
    cout<<"*****  6.清空联系人  *****"<<endl;
    cout<<"*****  0.退出通讯录  *****"<<endl;
    cout<<"**************************"<<endl;

}

//添加联系人函数
void addPerson(AddressBook * abs)
{
    if (abs->m_Size == MAX)
    {
        cout<<"通讯录已满，无法添加!"<<endl;
        return ;
    }
    else
    {
        //添加具体联系人

        //姓名
        string name;
        cout<<"请输入姓名: "<<endl;
        cin>>name;
        abs->personArray[abs->m_Size].m_Name = name;

        //性别
        int gender;
        cout<<"请输入性别："<<endl;
        cout<<"1 -- 男"<<endl;
        cout<<"2 -- 女"<<endl;
        while (true)
        {

            //如果输入为1或2可以退出循环，因为输入正确
            //如果输入有误，重新输入
            cin>>gender;

            if (gender == 1 || gender == 2)
            {
                abs->personArray[abs->m_Size].m_Gender = gender;
                break;
            }
            cout<<"输入有误, 请重新输入"<<endl;
        }
        
        
        

        //年龄
        int age;
        cout<<"请输入年龄："<<endl;
        cin>>age;
        abs->personArray[abs->m_Size].m_Age = age;

        //联系电话
        string tel;
        cout<<"请输入联系电话: "<<endl;
        cin>>tel;
        abs->personArray[abs->m_Size].m_Tel = tel;

        //家庭住址
        string address;
        cout<<"请输入家庭住址："<<endl;
        cin>>address;
        abs->personArray[abs->m_Size].m_Address = address;
    }

    //更新通讯录人数
    abs->m_Size++;

    //提示输入成功
    cout<<"添加成功"<<endl;
}

//显示联系人函数
void showPerson(AddressBook * abs)
{
    if (abs->m_Size == 0)
    {
        cout<<"记录为空"<<endl;
    }
    else
    {
        for (int i = 0; i < abs->m_Size; i++)
        {
            cout<<"姓名: "<<abs->personArray[i].m_Name<<" 性别: "<<(abs->personArray[i].m_Gender == 1 ? "男" : "女")<<" 年龄: "<<abs->personArray[i].m_Age<<" 联系电话: "<<abs->personArray[i].m_Tel<<" 家庭住址: "<<abs->personArray[i].m_Address<<endl;
        }
        
    }
}

//判断联系人存在函数
int isExist(AddressBook * abs, string findName)
{
    for (int i = 0; i < abs->m_Size; i++)
    {
        if (abs->personArray[i].m_Name == findName)
        {
            return i;//找到，返回所在位置
        }
    }

    return -1;
    
}

//删除联系人函数
void delPerson(AddressBook * abs)
{
    cout<<"请输入删除联系人姓名: "<<endl;
    string findName;
    cin>>findName;
    int flag = isExist(abs, findName);
    if (flag == -1)
    {
        cout<<"联系人不存在"<<endl;
        return ;
    }
    else
    {
        //查到此人，进行删除
        //用后面的数据向前移动覆盖，并且联系人数量-1
        for (int i = flag; i < abs->m_Size - 1; i++)
        {
            abs->personArray[i] = abs->personArray[i + 1];
        }

        abs->m_Size--;
        cout<<"删除成功"<<endl;
        return ;
        
    }
}

//查找联系人函数
void findPerson(AddressBook * abs)
{
    cout<<"请输入查找联系人姓名: "<<endl;
    string findName;
    cin>>findName;

    int flag = isExist(abs, findName);

    if (flag == -1)
    {
        cout<<"联系人不存在"<<endl;
    }
    else
    {
        cout<<"姓名: "<<abs->personArray[flag].m_Name<<" 性别: "<<(abs->personArray[flag].m_Gender == 1 ? "男" : "女")<<" 年龄: "<<abs->personArray[flag].m_Age<<" 联系电话: "<<abs->personArray[flag].m_Tel<<" 家庭住址: "<<abs->personArray[flag].m_Address<<endl;
    }
}

//修改联系人函数
void changePerson(AddressBook * abs)
{
    cout<<"请输入修改联系人姓名: "<<endl;
    string findName;
    cin>>findName;

    int flag = isExist(abs, findName);

    if (flag == -1)
    {
        cout<<"联系人不存在"<<endl;
    }
    else
    {
        //找到指定联系人

        //姓名
        string name;
        cout<<"请输入姓名: "<<endl;
        cin>>name;
        abs->personArray[abs->m_Size].m_Name = name;

        //性别
        int gender;
        cout<<"请输入性别："<<endl;
        cout<<"1 -- 男"<<endl;
        cout<<"2 -- 女"<<endl;
        while (true)
        {

            //如果输入为1或2可以退出循环，因为输入正确
            //如果输入有误，重新输入
            cin>>gender;

            if (gender == 1 || gender == 2)
            {
                abs->personArray[abs->m_Size].m_Gender = gender;
                break;
            }
            cout<<"输入有误, 请重新输入"<<endl;
        }
        
        
        

        //年龄
        int age;
        cout<<"请输入年龄："<<endl;
        cin>>age;
        abs->personArray[abs->m_Size].m_Age = age;

        //联系电话
        string tel;
        cout<<"请输入联系电话: "<<endl;
        cin>>tel;
        abs->personArray[abs->m_Size].m_Tel = tel;

        //家庭住址
        string address;
        cout<<"请输入家庭住址："<<endl;
        cin>>address;
        abs->personArray[abs->m_Size].m_Address = address;

    }
}

//清空联系人函数
void clearPerson(AddressBook * abs)
{
    abs->m_Size = 0;
    return ;
}
