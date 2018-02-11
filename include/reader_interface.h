//
// Created by daniele on 02/02/18.
//

#ifndef NETWORKREADER_READER_INTERFACE_H
#define NETWORKREADER_READER_INTERFACE_H

using namespace std;

class ReaderInterface {
public:
    virtual int read(string filename)=0;
};

#endif //NETWORKREADER_READER_INTERFACE_H
