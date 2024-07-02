#include"workerManager.h"

//构造函数
WorkerManager::WorkerManager()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    //文件不存在的情况
    if (! ifs.is_open())
    {
        // cout<<"文件不存在"<<endl;//测试输出
        m_EmpNum = 0;//初始化人数
        m_EmpArray = NULL;//初始化数组指针
        m_FileIsEmpty = true;//初始化文件是否为空标志
        ifs.close();//关闭文件

        return;
    }

    //文件存在 数据为空
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        //文件为空
        // cout<<"文件为空"<<endl;//测试输出
        m_EmpNum = 0;//初始化人数
        m_EmpArray = NULL;//初始化数组指针
        m_FileIsEmpty = true;//初始化文件是否为空标志
        ifs.close();//关闭文件

        return;
    }

    //文件存在 并且记录数据
    int num = get_EmpNum();
    // cout<<"职工人数为: "<<num<<endl;
    m_EmpNum = num;
    m_FileIsEmpty = false;
    

    //开辟空间
    m_EmpArray = new Worker*[m_EmpNum];
    //将文件中数据 存到数组中
    init_Emp();

    //测试代码
    // for (int i = 0; i < m_EmpNum; i++)
    // {
    //     m_EmpArray[i]->showInfo();
    // }
    

};

//析构函数
WorkerManager::~WorkerManager()
{
    if(m_EmpArray != NULL)
    {
        for (int i = 0; i < m_EmpNum; i++)
        { 
            delete m_EmpArray[i];
            m_EmpArray = NULL;
        }
        
        delete[] m_EmpArray;
        m_EmpArray = NULL;
    }
};


//显示菜单
void WorkerManager::show_Menu()
{
    cout<<"******************************************"<<endl;
    cout<<"********* 欢迎使用职工管理系统 *********"<<endl;
    cout<<"************* 0.退出管理系统 *************"<<endl;
    cout<<"************* 1.增加职工信息 *************"<<endl;
    cout<<"************* 2.显示职工信息 *************"<<endl;
    cout<<"************* 3.删除离职职工 *************"<<endl;
    cout<<"************* 4.修改职工信息 *************"<<endl;
    cout<<"************* 5.查找职工信息 *************"<<endl;
    cout<<"************* 6.按照编号排序 *************"<<endl;
    cout<<"************* 7.清空所有文档 *************"<<endl;
    cout<<endl;
}

//退出系统
void WorkerManager::exitSystem()
{
    cout<<"欢迎下次使用"<<endl;
    system("pause");
    exit(0);
}

//添加职工
void WorkerManager::Add_Emp()
{
    cout<<"请输入添加职工数量: "<<endl;

    int addNum = 0;
    cin>>addNum;

    if (addNum > 0)
    {
        //计算新添加空间
        int newSize = m_EmpNum + addNum;

        //开辟新空间
        Worker ** newSpace = new Worker*[newSize];

        //将原空间下内容存放到新空间中
        if (m_EmpArray != NULL)
        {
            for (int i = 0; i < m_EmpNum; i++)
            {
                newSpace[i] = m_EmpArray[i];
            }
        }

        //输入新数据
        for (int i = 0; i < addNum; i++)
        {
            int id;
            string name;
            int dSelect;

            cout<<"请输入第"<< i + 1 <<"个新职工编号: "<<endl;
            cin>>id;

            cout<<"请输入第"<< i + 1 <<"个新职工姓名"<<endl;
            cin>>name;

            cout<<"请选择该职工岗位: "<<endl;
            cout<<"1. 普通职工"<<endl;
            cout<<"2. 经理"<<endl;
            cout<<"3. 老板"<<endl;
            cin>>dSelect;

            Worker * worker = NULL;
            switch (dSelect)
            {
            case 1://普通员工
                worker = new Employee(id, name, dSelect);
                break;
            case 2://经理
                worker = new Manager(id, name, dSelect);
                break;
            case 3://老板
                worker = new Boss(id, name, dSelect);
                break;
            default:
                break;
            }

            newSpace[m_EmpNum + i] = worker;
        }

        //释放原有空间
        delete m_EmpArray;

        //更改新空间指向
        m_EmpArray = newSpace;

        //更新职工数量
        m_EmpNum = newSize;

        //成功添加后 保存到文件
        save();

        //更新职工不为空标志
        m_FileIsEmpty = false;

        //提示添加职工
        cout<<"成功添加"<<addNum<<"名新职工"<<endl;
    }
    else
    {
        cout<<"输入错误"<<endl;
    }
}

//保存文件
void WorkerManager::save()
{
    ofstream ofs;

    ofs.open(FILENAME, ios::out);

    for (int i = 0; i < m_EmpNum; i++)
    {
        ofs<<m_EmpArray[i]->m_Id<<" "
        <<m_EmpArray[i]->m_Name<<" "
        <<m_EmpArray[i]->m_DeptId<<endl;
    }

    ofs.close();
    
}

//统计文件中人数
int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);//打开文件 读
    
    int id;
    string name;
    int dId;

    int num = 0;

    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        //统计人数变量
        num++;
    }

    return num;
    
}

//初始化员工
void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int index = 0;

    while(ifs >> id && ifs >> name && ifs >> dId)
    {
        Worker * worker = NULL;

        if (dId == 1)//普通员工
        {
            worker = new Employee(id, name, dId);

        }
        else if (dId == 2)//经理
        {
            worker = new Manager(id, name, dId);
        }
        else
        {
            worker = new Boss(id, name, dId);
        }

        m_EmpArray[index] = worker;
        index++;
        
    }

}

//显示职工
void WorkerManager::Show_Emp()
{
    if (m_FileIsEmpty)
    {
        cout<<"文件不存在或者记录为空"<<endl;
    }
    else
    {
        for (int i = 0; i < m_EmpNum; i++)
        {
            m_EmpArray[i]->showInfo();
        }
        
    }
}

//按照职工编号判断职工是否存在，存在返回在数组中位置，不存在返回-1
int WorkerManager::IsExist(int id)
{
    for (int i = 0; i < m_EmpNum; i++)
    {
        if (m_EmpArray[i]->m_Id == id)
        {
            return i;
        }
    }
    
    return -1;
    
}

//删除职工
void WorkerManager::Del_Emp()
{

    if (m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空" << endl;
    }
    else
    {
        // 按照职工编号删除
        int id;
        cout << "请输入要删除职工的编号" << endl;
        cin >> id;

        int flag = IsExist(id);
        if (flag == -1)
        {
            cout << "员工不存在" << endl;
        }
        else
        {
            // cout<<"员工在数组中位置为"<<flag<<endl;//测试代码

            //数据前移
            for (int i = flag; i < m_EmpNum - 1; i++)
            {
                m_EmpArray[i] = m_EmpArray[i + 1];
            }

            m_EmpNum--;//更新数组中记录人员个数
            save();//数据同步更新到文件中
            cout<<"删除成功"<<endl;
            
            //如果人数归0 更新文件是否为空标志
            if (m_EmpNum == 0)
            {
                m_FileIsEmpty = true;
            }

            
        }
    }
} 

//修改职工
void WorkerManager::Mod_Emp()
{
    if (m_FileIsEmpty == -1)
    {
        cout<<"文件不存在或记录为空"<<endl;
    }
    else
    {
        // 按照职工编号修改
        int id;
        cout << "请输入要修改职工的编号" << endl;
        cin >> id;

        int flag = IsExist(id);
        if (flag == -1)
        {
            cout << "员工不存在" << endl;
        }
        else
        {
            delete m_EmpArray[flag];

            int new_Id = 0;
            string newName;
            int dSelect;

            cout<<"查到: "<<id<<"号职工, 请输入新职工号: "<<endl;
            cin>>new_Id;

            cout<<"请输入新姓名: "<<endl;
            cin>>newName;

            cout<<"请输入岗位: "<<endl;
            cout<<"请选择该职工岗位: "<<endl;
            cout<<"1. 普通职工"<<endl;
            cout<<"2. 经理"<<endl;
            cout<<"3. 老板"<<endl;
            cin>>dSelect;

            Worker * worker = NULL;
            switch (dSelect)
            {
            case 1://普通员工
                worker = new Employee(new_Id, newName, dSelect);
                break;
            case 2://经理
                worker = new Manager(new_Id, newName, dSelect);
                break;
            case 3://老板
                worker = new Boss(new_Id, newName, dSelect);
                break;
            default:
                break;
            }

            //更新数据到数组中
            m_EmpArray[flag] = worker;

            cout<<"修改成功"<<m_EmpArray[flag]->m_DeptId<<endl;

            //保存到文件中
            save();


        }
    }


}

//查找职工
void WorkerManager::Find_Emp()
{
    if(m_FileIsEmpty)
    {
        cout<<"文件不存在或记录为空"<<endl;
    }
    else
    {
        cout<<"请输入查找方式: "<<endl;
        cout<<"1.按职工编号查找"<<endl;
        cout<<"2.按姓名查找"<<endl;

        int select = 0;
        cin>>select;

        if (select == 1)
        {
            //按编号查
            int id;
            cout<<"请输入查找职工编号: "<<endl;
            cin>>id;

            int flag = IsExist(id);
            if (flag != -1)
            {
                cout<<"查找成功, 信息如下"<<endl;
                m_EmpArray[flag]->showInfo();
            }
            else
            {
                cout<<"查无此人"<<endl;
            }
            
        }
        else if (select == 2)
        {
            // 按照姓名查
            string name;
            cout<<"请输入查找姓名: "<<endl;
            cin>>name;
            
            //加入判断是否查到标志
            bool flag = false;

            for (int i = 0; i < m_EmpNum; i++)
            {
                if (m_EmpArray[i]->m_Name == name)
                {
                    cout << "查找成功, 信息如下: " << endl;
                    flag = true;
                    m_EmpArray[i]->showInfo();
                }
            }

            if (!flag)
            {
                cout<<"查无此人"<<endl;
            }
            
            
        }
        else
        {
            cout<<"输入错误"<<endl;
        }
    }
}

//排序职工
void WorkerManager::Sort_Emp()
{
    if (m_FileIsEmpty)
    {
        cout<<"文件不存在或记录为空"<<endl;
    }
    else
    {
        cout<<"请选择排序方式: "<<endl;
        cout<<"1.升序"<<endl;
        cout<<"2.降序"<<endl;
        int select = 0;
        cin>>select;

        if (select == 1)
        {
            //升序, 选择排序, 每次选出最大的序号交换到末尾
            //交换m_EmpNum-1次
            for (int i = 0; i < m_EmpNum - 1; i++)
            {
                int maxIndex = 0;
                //选出最大序号
                for (int j = 0; j < m_EmpNum - i; j++)
                {
                    if (m_EmpArray[j]->m_Id > m_EmpArray[maxIndex]->m_Id)
                    {
                        maxIndex = j;
                    }
                    
                }

                //交换到末尾

                Worker * tmp;
                tmp = m_EmpArray[maxIndex];
                m_EmpArray[maxIndex] = m_EmpArray[m_EmpNum - i - 1];
                m_EmpArray[m_EmpNum - i - 1] = tmp;
                
            }
            //保存到文件
            save();
            cout<<"排序成功"<<endl;
            
        }
        else if (select == 2)
        {
            //降序, 选择排序, 每次选出最小的序号交换到末尾
            //交换m_EmpNum-1次
            for (int i = 0; i < m_EmpNum - 1; i++)
            {
                int minIndex = 0;
                //选出最大序号
                for (int j = 0; j < m_EmpNum - i; j++)
                {
                    if (m_EmpArray[j]->m_Id < m_EmpArray[minIndex]->m_Id)
                    {
                        minIndex = j;
                    }
                    
                }

                //交换到末尾

                Worker * tmp;
                tmp = m_EmpArray[minIndex];
                m_EmpArray[minIndex] = m_EmpArray[m_EmpNum - i - 1];
                m_EmpArray[m_EmpNum - i - 1] = tmp;
                
            }
            //保存到文件
            save();
            cout<<"排序成功"<<endl;
        }
        else
        {
            cout<<"输入错误"<<endl;
        }
        
    }
}

//清空文件
void WorkerManager::Clean_File()
{
    cout<<"确认清空?"<<endl;
    cout<<"1.确认"<<endl;
    cout<<"2.取消"<<endl;

    int select = 0;
    cin>>select;

    if (select == 1)
    {
        // 清空文件
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();

        if (m_EmpArray != NULL)
        {
            for (int i = 0; i < m_EmpNum; i++)
            {
                
                delete m_EmpArray[i];
                m_EmpArray = NULL;
                
            }

            delete[] m_EmpArray;
            m_EmpArray = NULL;
            m_EmpNum = 0;
            m_FileIsEmpty = true;
        }
        cout<<"清空成功"<<endl;
    }
}