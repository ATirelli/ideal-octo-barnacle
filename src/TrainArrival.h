//
// Created by Andrea Tirelli on 21/05/22.
//

#include <ctime>
#include <string>

#ifndef SCHEDULE_TRAIN_ARRIVALS_TRAINARRIVAL_H
#define SCHEDULE_TRAIN_ARRIVALS_TRAINARRIVAL_H

using namespace std;

class TrainArrival {

private:
    string type{};
    string plate{};
    time_t start_date{};
    int duration;
    int assigned_platform;

public:
    TrainArrival(const string& type, const string& plate, time_t start_date, int duration);

    bool operator < (TrainArrival const &obj) const;

    time_t get_start_date() const;

    string get_type();

    string get_plate();

    int get_duration() const;

    int get_platform() const;

    void set_platform(int);

};
#endif //SCHEDULE_TRAIN_ARRIVALS_TRAINARRIVAL_H
