#include <iostream>
#include <filesystem>
#include <fstream>

using std::cout;
using std::endl;

int main() {
    // 创建、删除文件和文件夹
    std::filesystem::path path("directory");
    if(!std::filesystem::exists(path)) {
        std::filesystem::create_directory(path);
    }
    std::filesystem::path file_path = path / "file.txt";
    if(!std::filesystem::exists(file_path)) {
        std::ofstream out(file_path);
        out << "hello";
        out.close();
    }

    // 检查文件类型
    if(std::filesystem::is_regular_file("filesystem.cpp")) {
        cout << "regular file\n";
    }
    if(std::filesystem::is_directory(path)) {
        cout << "directory\n";
    }
    if(std::filesystem::is_empty(path)) {
        cout << "directory empty\n";
    }
    else {
        cout << "directory not empty\n";
    }

    // 遍历目录
    for(auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
        if(entry.is_regular_file()) {
            cout << "  regular file: " << entry.path() << ", size: " << entry.file_size() << endl;
        }
        if(entry.is_directory()) {
            cout << "directory: " << entry.path() << endl;
        }
    }

    // std::filesystem::remove(path);
    std::filesystem::remove_all(path);
    return 0;
}