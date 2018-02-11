//
// Created by daniele on 11/02/18.
//

#ifndef NETWORKREADER_UTILS_H
#define NETWORKREADER_UTILS_H

#include <list>
#include <string>
#include <dirent.h>

using namespace std;

namespace Utils {
    list<string> getFiles(string directory);
    bool isInteger(const string & s);
}

#endif //NETWORKREADER_UTILS_H
