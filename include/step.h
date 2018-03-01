//
// Created by daniele on 10/02/18.
//

#ifndef NETWORKREADER_STEP_H
#define NETWORKREADER_STEP_H

#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <string>

using namespace std;

class Step {
    string ip;
    string metric;
    unsigned long nfields;
    unsigned long timestamp;
    vector<string> fields;
    vector<double> data;
public:
    Step(string metric, string ip, unsigned long nfields, unsigned long timestamp, vector<string> fields,
         vector<double> data) : metric(metric), ip(ip), nfields(nfields), timestamp(timestamp), fields(fields),
                                data(data) {

    }

    inline unsigned long getTimestamp() const;

    inline void setTimestamp(unsigned long timestamp);

    inline const vector<double> getData() const;

    inline string toString() const;

    inline bool operator<(const Step &obj) const {
        return (this->timestamp < obj.timestamp);
    }
};

unsigned long Step::getTimestamp() const {
    return timestamp;
}

void Step::setTimestamp(unsigned long timestamp) {
    Step::timestamp = timestamp;
}

const vector<double> Step::getData() const {
    return data;
}

string Step::toString() const {
    string ret;
    string s = ip + " " + metric; //to_string(this->getTimestamp());
    for (int i = 0; i < this->nfields; i++) {
        if (i>0) {
            ret.append(" | ");
        }
        double value = this->data[i] > 0 ? this->data[i] : 0;
        //double value = this->data[i];
        ret.append(s + " " + this->fields[i] + " " + to_string(value));

        //s.append(" " + this->fields[i] + " " + to_string(this->data[i]));
    }
    return ret;
}


inline ostream &operator<<(ostream &outs, const Step &obj) {
    // print something from v to str, e.g: Str << v.getX();
    return outs << obj.toString();
}

inline ostream &operator<<(ostream &outs, const Step *obj) {
    return outs << obj->toString();
}

#endif //NETWORKREADER_STEP_H
