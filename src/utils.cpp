//
// Created by daniele on 11/02/18.
//

#include <utils.h>
#include <iostream>

using namespace std;

namespace Utils
{
    list<string> getFiles(string path) {
        struct dirent *entry;
        DIR *dp;

        dp = opendir(path.c_str());
        if (dp == NULL) {
            perror("opendir: Path does not exist or could not be read.");
            return list<string>();
        }

        while ((entry = readdir(dp)))
            cout << entry->d_name << endl;

        closedir(dp);
        return list<string>();
    }
}