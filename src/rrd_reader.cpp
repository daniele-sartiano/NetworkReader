//
// Created by daniele on 02/02/18.
//


#include "rrd_reader.h"

int RrdReader::read(string filename) {
    return 0;
}


int RrdReader::read(string filename, string metric, string ip, pair<vector<string>, vector<Step>>& results) {
    int status;
    unsigned long ds_cnt = 0;
    char **ds_name;
    unsigned long step = 1;
    rrd_value_t *data;
    //pair<vector<string>, vector<Step>> *results = new pair<vector<string>, vector<Step>>();

    bool names_initialized = false;

    time_t start =(time_t) 0;
    time_t end = time(0);

    status = rrd_fetch_r(filename.c_str(), "AVERAGE", &start, &end, &step, &ds_cnt, &ds_name, &data);

    if (status != 0) {
        cout << rrd_get_error() << endl;
        return status;
    }

    //const unsigned long length = (end - start) / step;

    size_t i, j;
    long c = 0;
    vector<string> fields;
    for (time_t t=(start + step); t <= end; t += step) {
        //i = (size_t) (t-start) / (size_t) step;
        vector<double> values;

        bool are_nan = true;
        for (j=0; j < ds_cnt; ++j) {
            if (!names_initialized) {
                results.first.push_back(ds_name[j]);
                fields.push_back(ds_name[j]);
            }
            if (ds_name[j] >= 0) {
                values.push_back(data[c]);
            }
            if (are_nan && !isnan(data[c])) {
                are_nan = false;
            }
            ++c;
        }
        if (!are_nan) {
            Step s = Step(metric, ip, ds_cnt, static_cast<unsigned long>(t), fields, values);
            results.second.push_back(s);
        }
        if (!names_initialized) {
            names_initialized = true;
        }
    }

    //std::sort(results.second.begin(), results.second.end());

    free(data);
    free(ds_name);
    return 0;
}