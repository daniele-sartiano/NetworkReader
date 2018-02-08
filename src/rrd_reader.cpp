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

    const unsigned long length = (end - start) / step;
    size_t i, j;
    for (time_t t=(start + step); t <= end; t += step) {
        i = (size_t) (t-start) / (size_t) step;
        for (j=0; j < ds_cnt; ++j) {
            if (ds_name[j] >= 0) {
                time_t timestamp = t;
                double value = *data;
                cout << ds_name[j] << "\t" << timestamp << "\t" << value << endl;
            }
            ++data;
        }
    }

    /*for (unsigned int column=0; column < ds_cnt; ++column) {
        cout << ds_name[column] << endl;
        for (unsigned int row=0; row < length; ++row) {
            cout << row << "\t" << data[row*ds_cnt+column] << endl;
        }
    }*/

    cout << status << endl;
}
