//
// Created by Andrea Tirelli on 21/05/22.
//

#include <string>
#include "TrainArrival.h"
using namespace std;

TrainArrival::TrainArrival(const string& type, const string& plate, const time_t start_date, const int duration) {
        this->type = type;
        this->plate = plate;
        this->start_date = start_date;
        this->duration = duration*3600; // converting hours to time
        this->assigned_platform = -1;
    }

time_t TrainArrival::get_start_date() const {
    return start_date;
}

string TrainArrival::get_type() {
    return type;
}

string TrainArrival::get_plate() {
    return plate;
}

int TrainArrival::get_duration() const {
    return duration;
}

void TrainArrival::set_platform(int platform) {
    this->assigned_platform = platform;
}

bool TrainArrival::operator<(const TrainArrival & obj) const {
    if (obj.get_start_date()> this->get_start_date()) {
        return true;
    }
    else {
        return false;
    }
}

int TrainArrival::get_platform() const {
    return this->assigned_platform;
}

