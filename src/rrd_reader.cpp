//
// Created by daniele on 02/02/18.
//

#include "rrd_reader.h"


int RrdReader::read() {

    int status;
    unsigned long ds_cnt = 0;
    char **ds_name;
    unsigned long step = 1;
    rrd_value_t *data;

    time_t start =(time_t) 0;
    time_t end = time(0);

    status = rrd_fetch_r(this->filename.c_str(), "AVERAGE", &start, &end, &step, &ds_cnt, &ds_name, &data);

    if (status != 0) {
        return status;
    }

    for (unsigned int column=0; column < ds_cnt; column++) {
        cout << ds_name[column] << endl;
        for (unsigned int row=0; ; row++) {
            cout << data[row*ds_cnt+column] << endl;
            break;
        }
    }

    cout << status << endl;
}
