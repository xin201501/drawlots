#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<cstdlib>
#include<unordered_set>
#include<ctime>
#include<memory>
#include<optional>
#include"dao.h"
using std::cin, std::cout, std::endl, std::cerr;
class RandomGetStudentID {
private:
    std::weak_ptr<std::vector<int>>studentInfo;
    const Dao* dao = Dao::getInstance();
    std::optional<std::unordered_set<int>> randomGetStudentID(size_t size) {
        auto studentInfo = dao->readFile("ID.txt");
        size_t studentNum = studentInfo->size();
        [[unlikely]] if (0 == studentNum) {
            return std::nullopt;
        }
        size = std::min(studentNum, size);
        std::unordered_set<int> result;
        srand(time(0));
        for (size_t i = 1;result.size() < size;i++) {
            result.insert((*studentInfo)[rand() % studentNum]);
        }
        return std::make_optional(result);
    }
public:
    RandomGetStudentID() {
        studentInfo = dao->getPointer();
    }
    void userGUI() {
        size_t size;
        cout << "请输入想要抽取学生数量：";
        cin >> size;
        auto result = randomGetStudentID(size);
        [[unlikely]] if (!result) {
            cerr << "您尚未添加学号，请先添加学号。" << endl;
            return;
        }
        for (const auto& x : *result) {
            cout << x << '\n';
        }
    }
};