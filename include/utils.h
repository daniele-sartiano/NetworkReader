//
// Created by daniele on 11/02/18.
//

#ifndef NETWORKREADER_UTILS_H
#define NETWORKREADER_UTILS_H

#include <list>
#include <string>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

namespace Utils {
    list<string> getFiles(string directory);
    bool isInteger(const string & s);
    inline bool file_exists(const string & name) {
        struct stat buffer;
        return (stat (name.c_str(), &buffer) == 0);
    }
}

#endif //NETWORKREADER_UTILS_H
