//
// Created by daniele on 02/02/18.
//


#include <step.h>
#include "rrd_reader.h"

int RrdReader::read(string filename) {

    int status;
    unsigned long ds_cnt = 0;
    char **ds_name;
    unsigned long step = 1;
    rrd_value_t *data;
    pair<vector<string>, list<Step>> results;

    bool names_initialized = false;

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
        double values[ds_cnt];
        for (j=0; j < ds_cnt; ++j) {
            if (!names_initialized) {
                results.first.push_back(ds_name[j]);
            }
            if (ds_name[j] >= 0) {
                time_t timestamp = t;
                double value = *data;
                //cout << ds_name[j] << "\t" << timestamp << "\t" << value << endl;
                values[j] = value;
            }
            ++data;
        }
        //cout << t << values[0] << "|" << values[1] << endl;
        results.second.push_back(Step(static_cast<unsigned long>(t), values));
        if (!names_initialized) {
            names_initialized = true;
        }
    }

    /*for (unsigned int column=0; column < ds_cnt; ++column) {
        cout << ds_name[column] << endl;
        for (unsigned int row=0; row < length; ++row) {
            cout << row << "\t" << data[row*ds_cnt+column] << endl;
        }
    }*/


    /*for (list<Step>::iterator it = results.second.begin(); it != results.second.end(); it++) {
        Step s = (*it);
        cout << s.getTimestamp() << " " << s.getData()[0] << "-" << s.getData()[1] << endl;
    }*/

    cout << results.first.front() << endl;
    cout << results.second.front().getTimestamp() << endl;
    cout << results.second.back().getTimestamp() << endl;
    cout << results.second.size() << endl;
    cout << status << endl;
}
