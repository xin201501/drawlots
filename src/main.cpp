#include<iostream>
#include<fstream>
#include"../include/managestudentID.h"
#include"../include/randomgetstudentID.h"
using std::cin, std::cout, std::cerr, std::endl;
namespace {
    std::string mainInstruction = "默认系统从与程序同路径的ID.txt中读取数据，手动编辑文件需一个ID一行。若输入数量超出学生总数样本数为学生总数。\n输入1抽取学生，输入2管理学生数据,输入0退出：";
}
int main(int argc, char const* argv[]) {
    system("chcp 65001");
    RandomGetStudentID randomGetStudentIDInstance;
    MangageStudentID mangageStudentIDInstance;
    cout << mainInstruction;
    int choice;
    while (cin >> choice) {
        switch (choice) {
        case 1: {
            randomGetStudentIDInstance.userGUI();
            cout << mainInstruction;
        }
              break;
        case 2:
            mangageStudentIDInstance.userGUI();
            cout << mainInstruction;
            break;
        case 0:
            return 0;
        default:
            cerr << "输入数字非法，请重新输入:";
        }
    }
}