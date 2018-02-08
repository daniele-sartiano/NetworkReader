//
// Created by daniele on 29/01/18.
//

#include <iostream>
#include <getopt.h>
#include <pcap_reader.h>

#include <rrd.h>
#include <rrd_reader.h>

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


    RrdReader *r = new RrdReader(nvalue);
    r->read();

    //-f /projects/ntop/c++/NetworkReader/data/pcap/snort.log.1425823194
    /*PcapReader *reader = new PcapReader(nvalue);
    reader->read();*/



    return(0);
}