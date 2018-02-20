//
// Created by daniele on 10/02/18.
//

#ifndef NETWORKREADER_STEP_H
#define NETWORKREADER_STEP_H

#include <iostream>
#include <cmath>
#include <limits>
#include <vector>

class Step {
    unsigned long nfields;
    unsigned long timestamp;
    std::vector<double> data;
public:
    Step(unsigned long nfields, unsigned long timestamp, std::vector<double> data) : nfields(nfields), timestamp(timestamp), data(data) {

    }

    inline unsigned long getTimestamp() const;

    inline void setTimestamp(unsigned long timestamp);

    inline const std::vector<double> getData() const;

    inline std::string toString() const;

    inline bool operator < (const Step& obj) const
    {
        return (this->timestamp < obj.timestamp);
    }
};

unsigned long Step::getTimestamp() const {
    return timestamp;
}

void Step::setTimestamp(unsigned long timestamp) {
    Step::timestamp = timestamp;
}

const std::vector<double> Step::getData() const {
    return data;
}

std::string Step::toString() const {
    std::string s = std::to_string(this->getTimestamp());
    for (int i=0;i < this->nfields; i++) {
        s.append(" " + std::to_string(this->data[i]));
    }
    return s;
}


inline std::ostream& operator<<(std::ostream & outs, const Step& obj) {
    // print something from v to str, e.g: Str << v.getX();
    return outs << obj.toString();
}
inline std::ostream& operator<<(std::ostream& outs, const Step* obj ) {
    return outs << obj->toString();
}

#endif //NETWORKREADER_STEP_H
