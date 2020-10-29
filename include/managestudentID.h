#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<memory>
#include<iomanip>
#include<optional>
#include"dao.h"
using std::cin, std::cout, std::cerr, std::endl;
class MangageStudentID {
private:
    std::weak_ptr<std::vector<int>>studentInfo;
    const Dao* dao = Dao::getInstance();
    inline static std::string subInstruction = "输入1查看所有学号信息,输入2单条或批量添加学号，输入3单条或批量删除学号，输入4单条更改学号,输入0退出子模块:";
    auto check() {
        auto infos = studentInfo.lock();
        if (!infos) {
            throw std::runtime_error("程序内部错误");
        }
        return infos;
    }
    auto find(int studentID) {
        auto& infos = *check();
        auto pos = std::find(infos.begin(), infos.end(), studentID);
        return pos != infos.cend() ? std::optional(pos) : std::nullopt;
    }
    auto findIndex(int studentID) {
        auto& infos = *check();
        auto pos = std::find(infos.begin(), infos.end(), studentID);
        return pos != infos.cend() ? std::optional(pos - infos.begin()) : std::nullopt;
    }
    void show() {
        for (size_t i = 1;const auto x : *check()) {
            cout << "序号" << std::setw(10) << "学号" << endl;
            cout << std::setw(-2) << i++ << std::setw(12) << x << endl;
        }
    }
    void printIDPos(int studentID) {
        auto pos = findIndex(studentID);
        if (pos) {
            cout << *pos;
        }
        else {
            cout << "学号不存在！";
        }
        cout << endl;
    }
    void add(std::vector<int> studentIDs) {
        [[unlikely]] if (studentIDs.size() == 0) {
            cerr << "没有输入学号，返回。" << endl;
            return;
        }
        for (auto studentID : studentIDs) {
            if (find(studentID)) {
                cerr << "学号" << studentID << "已存在，忽略。" << endl;
                continue;
            }
            auto& infos = *check();
            infos.push_back(studentID);
        }
        dao->writefile("ID.txt");
        cout << "添加成功！" << endl;
    }
    void remove(std::vector<int>studentIDs) {
        [[unlikely]] if (studentIDs.size() == 0) {
            cerr << "没有输入学号，返回。" << endl;
            return;
        }
        decltype(find(*studentIDs.begin())) removePos;
        for (const auto& studentID : studentIDs) {
            if (!(removePos = find(studentID))) {
                cerr << "学号" << studentID << "不存在，忽略。" << endl;
                continue;
            }
            auto& infos = *check();
            std::swap(**removePos, infos.back());
            infos.erase(infos.end() - 1);
        }
        dao->writefile("ID.txt");
        cout << "删除成功！" << endl;
    }
    void modifyID(std::vector<int>::iterator pos, size_t newID) {
        *pos = newID;
        dao->writefile("ID.txt");
        cout << "修改成功！" << endl;
    }
public:
    MangageStudentID() {
        studentInfo = dao->getPointer();
    }
    void userGUI() {
        int option;
        cout << subInstruction;
        while (cin >> option) {
            switch (option) {
            case 1:
                show();
                cout << subInstruction;
                break;
                int ID;
            case 2: {
                std::vector<int> newIDs;
                cout << "请输入学号，输入0结束";
                while (cin >> ID) {
                    [[unlikely]] if (0 == ID) {
                        break;
                    }
                    [[unlikely]] if (ID > 30000000 || ID < 20180000) {
                        cerr << "学号" << ID << "非法,此ID不会被添加。" << endl;
                    }
                    else {
                        newIDs.push_back(ID);
                    }
                }
                add(newIDs);
                cout << subInstruction;
            }
                  break;
            case 3: {
                std::vector<int> modifyIDs;
                cout << "请输入学号：";
                while (cin >> ID) {
                    [[unlikely]] if (0 == ID) {
                        break;
                    }
                    modifyIDs.push_back(ID);
                }
                remove(modifyIDs);
                cout << subInstruction;
            }
                  break;
            case 4: {
                std::vector<int>::iterator pos;
                cout << "请输入原学号：";
                while (cin >> ID) {
                    auto cur = find(ID);
                    [[unlikely]] if (!cur) {
                        cerr << "原学号不存在，请重新输入:";
                    }
                    else {
                        pos = *cur;
                        break;
                    }
                }
                cout << "请输入新学号：";
                while (cin >> ID) {
                    [[unlikely]] if (ID > 30000000 || ID < 20180000) {
                        cerr << "学号非法，请重新输入：";
                    }
                    else {
                        [[unlikely]] if (*pos == ID) {
                            cerr << "新旧学号相同，请重新输入新学号：";
                        }
                        else {
                            break;
                        }
                    }
                }
                modifyID(pos, ID);
                cout << subInstruction;
            }
                  break;
            case 0:
                return;
            default:
                cerr << "输入选项错误，请重新输入!" << endl;
            }
        }
    }
};