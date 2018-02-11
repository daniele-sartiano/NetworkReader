//
// Created by daniele on 02/02/18.
//

#ifndef NETWORKREADER_RRD_READER_H
#define NETWORKREADER_RRD_READER_H

#include <iostream>
#include <ctime>
#include <rrd.h>
#include <list>
#include <utility>
#include <vector>
#include "reader_interface.h"

using namespace std;

class RrdReader : ReaderInterface {
    string filename;
public:
    RrdReader() {};

    int read(string filename);
};


#endif //NETWORKREADER_RRD_READER_H
