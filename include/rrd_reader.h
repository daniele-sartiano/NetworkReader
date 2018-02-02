//
// Created by daniele on 02/02/18.
//

#ifndef NETWORKREADER_RRD_READER_H
#define NETWORKREADER_RRD_READER_H

#include <iostream>
#include <ctime>
#include <rrd.h>
#include "reader_interface.h"

using namespace std;

class RrdReader : ReaderInterface {
    string filename;
public:
    RrdReader(string f) : filename(std::move(f)) {};

    int read();
};


#endif //NETWORKREADER_RRD_READER_H
