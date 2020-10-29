#pragma once
#include<fstream>
#include<vector>
#include<algorithm>
#include<memory>
#include<filesystem>
class Dao {
private:
    std::shared_ptr<std::vector<int>>studentIDs;
    inline static std::unique_ptr<Dao> daoInstance;
public:
    auto readFile(const std::string& filename)const {
        if (!std::filesystem::exists(filename)) {
            std::cout << "当前目录无ID.txt文件，将创建一个空文件。" << std::endl;
            std::ofstream out(filename);
            out.close();
        }
        std::ifstream in(filename);
        if (!in) {
            throw std::runtime_error("文件打开失败，程序终止！");
        }
        auto studentIDs = std::make_shared<std::vector<int>>();
        std::copy(std::istream_iterator<int>(in), std::istream_iterator<int>(), std::back_inserter(*studentIDs));
        return studentIDs;
    }
    void writefile(const std::string& filename)const {
        std::ofstream out(filename);
        std::copy(studentIDs->cbegin(), studentIDs->cend(), std::ostream_iterator<int>(out, "\n"));
    }
    const std::shared_ptr<std::vector<int>>& getPointer()const {
        return studentIDs;
    }
    static auto getInstance() {
        if (!daoInstance) {
            daoInstance.reset(new Dao());
        }
        return daoInstance.get();
    }
private:
    Dao(const std::string& filename = "ID.txt") {
        studentIDs = readFile(filename);
    }
};