//
// Created by daniele on 11/02/18.
//

#include <utils.h>

using namespace std;

namespace Utils
{
    list<string> getFiles(string path) {
        struct dirent *entry;
        DIR *dp;
        list<string> ret;

        dp = opendir(path.c_str());
        if (dp == NULL) {
            perror("opendir: Path does not exist or could not be read.");
            return list<string>();
        }

        while ((entry = readdir(dp))) {

            ret.push_back(entry->d_name);

            /*struct stat path_stat;
            string name(entry->d_name);
            stat(entry->d_name, &path_stat);

            if (isInteger(name)) {
                cout << "--->\t";
            }

            if (name.find(".rrd") != string::npos) {
                cout << "rrd\t";
            }
            cout << entry->d_name << " f:" << S_ISREG(path_stat.st_mode) << " d:" << S_ISDIR(path_stat.st_mode) << endl;*/
        }

        closedir(dp);
        return ret;
    }

    bool isInteger(const std::string & s)
    {
        if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

        char * p ;
        strtol(s.c_str(), &p, 10) ;

        return (*p == 0) ;
    }

    template<typename Out>
    void split(const std::string &s, char delim, Out result) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            trim(item);
            *(result++) = item;
        }
    }

    list<string> split(const string &s, char delim) {
        list<string> elems;
        split(s, delim, back_inserter(elems));
        return elems;
    }

}