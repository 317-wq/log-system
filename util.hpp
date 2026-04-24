#pragma once
#ifndef LOG_UTIL_H
#define LOG_UTIL_H

/*
    实现一些工具：
    1、获取当前时间
    2、判断文件资源是否存在
    3、获取文件目录
    3、创建所需文件资源
*/

#include <iostream>
#include <ctime>
#include <string>
#include <sys/stat.h>

using std::cout;
using std::endl;

namespace ljt{
    // 工具
    namespace util{
        // 设置成静态函数，方便调用，不需要实例化对象
        class Data{
        public:
            // 获取当前时间戳
            static size_t getNowTime(){
                return (size_t)time(nullptr);
            }
        };

        class File{
        public:
            // 判断文件是否存在
            static bool fileIsExist(const std::string& filepath){
                struct stat statbuf;
                // stat可以跨平台，移植性好
                return (stat(filepath.c_str(), &statbuf) == 0);
            }

            // 获取文件目录
            static std::string getDir(const std::string &filepath){
                size_t pos = filepath.find_last_of("/\\");
                if (pos == std::string::npos){
                    return "";
                }
                return filepath.substr(0, pos);
            }

            // 创建文件资源
            static void createDirSource(const std::string& filepath){
                size_t pos = 0, idx = 0;
                while(idx < filepath.size()){
                    // cout << "start" << endl;
                    pos = filepath.find_first_of("/\\", idx);
                    // cout << "pos: " << pos << endl;
                    if(pos == std::string::npos){
                        mkdir(filepath.c_str(), 0777);
                        break;
                    }

                    // a/b/test.txt
                    std::string parent_dir = filepath.substr(0, pos + 1);
                    // cout << parent_dir << endl;
                    idx = pos + 1;
                    // if(parent_dir == "." || parent_dir == "..")
                    //     continue;
                    if(fileIsExist(parent_dir))
                        continue;
                    mkdir(parent_dir.c_str(), 0777);
                }
            }
        };

    }
}
#endif