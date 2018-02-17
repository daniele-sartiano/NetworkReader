//
// Created by daniele on 10/02/18.
//

#ifndef NETWORKREADER_STEP_H
#define NETWORKREADER_STEP_H

class Step {
    unsigned long timestamp;
    double *data;
public:
    Step(unsigned long timestamp, double *data) : timestamp(timestamp), data(data) {}

    unsigned long getTimestamp() const;

    void setTimestamp(unsigned long timestamp);

    const double *getData() const;
};

unsigned long Step::getTimestamp() const {
    return timestamp;
}

void Step::setTimestamp(unsigned long timestamp) {
    Step::timestamp = timestamp;
}

/*const double *Step::getData() const {
    return data;
}*/


#endif //NETWORKREADER_STEP_H
