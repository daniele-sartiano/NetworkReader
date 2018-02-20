//
// Created by daniele on 29/01/18.
//

#include <iostream>
#include <getopt.h>
#include <pcap_reader.h>
#include <rrd.h>
#include <rrd_reader.h>
#include <utils.h>
#include <fstream>
#include <map>

using namespace std;

int main(int argc, char* argv[]) {

    const char* nvalue = "";
    int c ;
    while( ( c = getopt (argc, argv, "f:") ) != -1 )
    {
        switch(c)
        {
            case 'f':
                if(optarg) {
                    nvalue = optarg;
                }
                else {
                    cerr << "got a nullptr for optarg for -n\n" ;
                    return(-1);
                }
        }
    }

    map<unsigned long, vector<Step>> data;


    int i=0;
    string line;
    ifstream myfile (nvalue);
    if (myfile.is_open())
    {
        RrdReader *r = new RrdReader();
        while ( getline (myfile,line) )
        {
            i++;
            pair<vector<string>, vector<Step>> results;// = new pair<vector<string>, vector<Step>>();
            cout << line << '\n';
            r->read(line, results);

            for (vector<Step>::iterator it = results.second.begin(); it != results.second.end(); it++) {
                Step s = (*it);
                data[s.getTimestamp()].push_back(s);
            }

            /*cout << "timestamp";
            for (vector<string>::iterator it = results.first.begin(); it != results.first.end(); it++) {
                cout << " " << (*it);
            }
            cout << endl;

            for (vector<Step>::iterator it = results.second.begin(); it != results.second.end(); it++) {
                Step s = (*it);
                cout << s << endl;
            }*/

            if (i>50) {
                break;
            }
        }
        myfile.close();

    }

    else cout << "Unable to open file";


    for( auto const& v : data )
    {
        unsigned long timestamp = v.first;
        vector<Step> values = v.second;
        cout << timestamp;
        for (vector<Step>::iterator it = values.begin(); it != values.end(); it++) {
            cout << "|";
            cout << (*it);
        }
        cout << endl;

    }

    return 0;

    Utils::getFiles(nvalue);

    /*RrdReader *r = new RrdReader();
    r->read(nvalue);
    delete r;*/

    //-f /projects/ntop/c++/NetworkReader/data/pcap/snort.log.1425823194
    /*PcapReader *reader = new PcapReader(nvalue);
    reader->read();*/



    return(0);
}