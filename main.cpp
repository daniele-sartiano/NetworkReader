//
// Created by daniele on 29/01/18.
//

#include <iostream>
#include <string>
#include <pcap.h>
#include <getopt.h>


using namespace std;

class PcapReader {
    string filename;
public:
    explicit PcapReader (string f) : filename(f) {}

    void read() {
        cout << this->filename << "\n";
    }
};

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

    PcapReader *reader = new PcapReader(nvalue);
    reader->read();

    std::cout << "Hello world\n";
    return(0);
}