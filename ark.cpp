#include <fstream>
#include <iostream>
#include <string>
#include <io.h>
#include"ark.h"

using namespace std;

inline void CheckMistake(p_egg node)
{
    if (!node)
    {
        cout << "分配内存失败" << endl;
        system("pause");
        exit(3);
    }
}

inline string ReplaceTypeName(string str)
{
    //已经得知我们要删的是.txt和data/
    int len = str.size() - 4;
    //erase从字符串第len位开始删除后4个字符
    str.erase(len, 4);
    str.erase(0, 5);
    return str;
}

void SearchDis(p_egg head)
{
    //数据少，不加查找算法
    string _name;
    p_egg temp = head->next;
    cout << "恐龙名:";
    cin >> _name;
    printf("\n");
    while (temp)
    {
        //find()函数返回_name 在 name 的位置,如果能返回，那么字符串是匹配的
        //find()没匹配到返回string::npos
        if (temp->name.find(_name) != string::npos)
        {
            cout << temp->name << "     ";
            cout << temp->type << endl;
            system("pause");
            return;
        }
        else
        {
            temp = temp->next;
        }
    }
    cout << "没有该恐龙信息" << endl;
    system("pause");
}

p_egg start()
{
    //首先检查文件完整性
    _finddata_t file;
    if (_findfirst("data",&file ) == -1)
    {
        cout << "缺少data文件" << endl;
        exit(1);
    }
    //现需6个txt文件
    p_egg end, temp;
    p_egg head = new egg;//头指针是一个坐标
    CheckMistake(head);
    end = head;//尾指针是一个搬运工

    //将蛋类型导入链表
    temp = LoadEggData(end, "data/超小型蛋.txt");
    temp = LoadEggData(temp, "data/小型蛋.txt");        //赋值号优先级较低
    temp = LoadEggData(temp, "data/中型蛋.txt");        //可以无限套娃，但为了可读性，还是别了
    temp = LoadEggData(temp, "data/大型蛋.txt");
    temp = LoadEggData(temp, "data/超大型蛋.txt");
    temp = LoadEggData(temp, "data/特型蛋.txt");
    end = temp;//可读性
    end->next = NULL;
    //将饲料配方导入十字链表

    
    //初始化完成
    return head;
}

p_egg LoadEggData(p_egg end, string _type)
{
    ifstream load;
    load.open(_type, ios::in);//以读入模式打开
    if (!load)
    {
        cout << "打开文件失败" << endl;
        exit(4);
    }
    _type = ReplaceTypeName(_type);
    while (load.peek() != EOF)
    {
        p_egg temp = new egg;
        CheckMistake(temp);
        load >> temp->name;
        temp->type = _type;
        end->next = temp;
        end = temp;
    }
    load.close();
    return end;
}

void LoadFeedData()
{
    string str;
    ifstream load;
    load.open("data/饲料.txt", ios::in);//以读入模式打开
    if (!load)
    {
        cout << "打开文件失败" << endl;
        exit(4);
    }
    system("cls");
    while (load.peek() != EOF)
    {
        getline(load, str);//遇到\n停止读取
        cout << str<<endl;
    }
    printf("\n");
    system("pause");
}

void LoadConsumablesData()
{
    string str;
    ifstream load;
    load.open("data/消耗品.txt", ios::in);//以读入模式打开
    if (!load)
    {
        cout << "打开文件失败" << endl;
        exit(4);
    }
    system("cls");
    while (load.peek() != EOF)
    {
        getline(load, str);//遇到\n停止读取
        cout << str<<endl;
    }
    printf("\n");
    system("pause");
}

void show(p_egg head)
{
    p_egg temp = head->next;
    while (temp)
    {
        cout << temp->name << "       " << temp->type << endl;
        temp = temp->next;
    }
}