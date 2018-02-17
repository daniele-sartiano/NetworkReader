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

    int i=0;
    string line;
    ifstream myfile (nvalue);
    if (myfile.is_open())
    {
        RrdReader *r = new RrdReader();
        while ( getline (myfile,line) )
        {
            i++;
            cout << line << '\n';
            r->read(line);
        }
        myfile.close();
    }

    else cout << "Unable to open file";

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