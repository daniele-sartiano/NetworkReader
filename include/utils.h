//
// Created by daniele on 11/02/18.
//

#ifndef NETWORKREADER_UTILS_H
#define NETWORKREADER_UTILS_H

#include <list>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <locale>


using namespace std;

namespace Utils {
    list<string> getFiles(string directory);
    bool isInteger(const string & s);
    inline bool file_exists(const string & name) {
        struct stat buffer;
        return (stat (name.c_str(), &buffer) == 0);
    }
    list<string> split(const string &s, char delim);
    // trim from start (in place)
    static inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    };
    // trim from end (in place)
    static inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    };
    // trim from both ends (in place)
    static inline void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }
}

#endif //NETWORKREADER_UTILS_H
