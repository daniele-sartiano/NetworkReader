//
// Created by daniele on 29/01/18.
//

#include <iostream>
#include <sstream>
#include <string>
#include <getopt.h>
#include <pcap_reader.h>
#include <rrd.h>
#include <utils.h>
#include <rrd_reader.h>
#include <utils.h>
#include <fstream>
#include <map>
#include <cstring>
#include <iterator>

using namespace std;

int main(int argc, char* argv[]) {

    const int PARAM_PATH = 0;
    const int PARAM_METRIC = 1;
    const int PARAM_IP = 2;

    const char* fvalue = "";
    const char* dvalue = "";
    int c ;
    while( ( c = getopt (argc, argv, "fd:") ) != -1 )
    {
        switch(c)
        {
            case 'f':
                if(optarg) {
                    fvalue = optarg;
                }
                else {
                    cerr << "got a nullptr for optarg for -n\n" ;
                    return(-1);
                }
                break;
            case 'd':
                if (optarg) {
                    dvalue = optarg;
                } else {
                    cerr << "got a nullptr for optarg for -n\n" ;
                    return(-1);
                }
                break;
        }
    }

    if (dvalue != "") {
        list<string> files = Utils::getFiles(dvalue);

        files.sort();

        for (list<string>::iterator it = files.begin(); it != files.end(); it++) {
            //cout << *it << endl;
            string f = (*it);
            if (f == "." || f == "..") {
                continue;
            }
            string path = string(dvalue) + f;
            std::ifstream ifs(path);
            std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

            list<string> tokens = Utils::split(content, '|');
            tokens.sort();

            stringstream res;
            copy(tokens.begin(), tokens.end(), ostream_iterator<string>(res, "|"));

            cout << f << "|" << res.str() << endl;

        }


    } else if (fvalue != "") {

        map<unsigned long, vector<Step>> data;
        vector<string> metrics;

        int i = 0;
        string line;
        ifstream myfile(fvalue);
        if (myfile.is_open()) {
            RrdReader *r = new RrdReader();
            while (getline(myfile, line)) {
                istringstream ss(line);
                string params[3];
                int n = 0;
                for (string field; getline(ss, field, '\t'); ++n) {
                    params[n] = field;
                }

                i++;
                pair<vector<string>, vector<Step>> results;// = new pair<vector<string>, vector<Step>>();
                cout << line << '\n';

                metrics.push_back(params[PARAM_METRIC]);
                r->read(params[PARAM_PATH], params[PARAM_METRIC], params[PARAM_IP], results);

                for (vector<Step>::iterator it = results.second.begin(); it != results.second.end(); it++) {
                    Step s = (*it);
                    data[s.getTimestamp()].push_back(s);
                }

                if (i > 40) {
                    break;
                }

                if (i % 30 == 0) {
                    cout << "writing " << i << endl;
                    //write out files
                    bool first = false;

                    for (auto const &v : data) {
                        unsigned long timestamp = v.first;
                        vector<Step> values = v.second;

                        first = !Utils::file_exists("output/" + to_string(timestamp));

                        ofstream file;
                        file.open("output/" + to_string(timestamp), std::ios::out | std::ios::app);
                        if (file.fail())
                            throw std::ios_base::failure(std::strerror(errno));

                        //file << timestamp;
                        for (vector<Step>::iterator it = values.begin(); it != values.end(); it++) {
                            if (!first) {
                                file << " | ";
                            } else {
                                first = false;
                            }
                            file << (*it);
                        }
                        file.close();
                    }

                    data.clear();
                }
            }

            //write out files
            bool first = false;

            cout << "writing " << i << endl;

            for (auto const &v : data) {
                unsigned long timestamp = v.first;
                vector<Step> values = v.second;

                first = !Utils::file_exists("output/" + to_string(timestamp));

                ofstream file;
                file.open("output/" + to_string(timestamp), std::ios::out | std::ios::app);
                if (file.fail())
                    throw std::ios_base::failure(std::strerror(errno));

                //file << timestamp;
                for (vector<Step>::iterator it = values.begin(); it != values.end(); it++) {
                    if (!first) {
                        file << " | ";
                    } else {
                        first = false;
                    }
                    file << (*it);
                }
                file.close();
            }

            data.clear();

            myfile.close();

        } else {
            cout << "Unable to open file";
            return 1;
        }

        for (auto const &v : data) {
            unsigned long timestamp = v.first;
            vector<Step> values = v.second;
            cout << timestamp;
            for (vector<Step>::iterator it = values.begin(); it != values.end(); it++) {
                cout << " | " << (*it);
            }
            cout << endl;

        }

    }
    return 0;

    /*RrdReader *r = new RrdReader();
    r->read(nvalue);
    delete r;*/

    //-f /projects/ntop/c++/NetworkReader/data/pcap/snort.log.1425823194
    /*PcapReader *reader = new PcapReader(nvalue);
    reader->read();*/



    return(0);
}
