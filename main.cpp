//
// Created by daniele on 29/01/18.
//

#include <iostream>
#include <string>
#include <pcap.h>


using namespace std;

class PcapReader {
    string filename;
public:
    explicit PcapReader (string f) : filename(f) {}
    void read() {
        cout << this->filename;
    }
};

int main() {

    PcapReader *reader = new PcapReader("afile");
    reader->read();

    std::cout << "Hello world\n";
    return(0);
}