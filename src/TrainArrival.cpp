//
// Created by Andrea Tirelli on 21/05/22.
//

#include <string>
#include "TrainArrival.h"
using namespace std;

TrainArrival::TrainArrival(const string& type, const string& plate, const time_t start_date, const int duration) {
    /**
    * Constructor method of the TrainArrival class
    * @param type string representing the train type
    * @param plate string representing the plate number of the train
    * @param start_date timestamp represeting the beginning of the maintenance for the train
    * @param duration time in seconds of the duration of the maintenance works for the train
    */
        this->type = type;
        this->plate = plate;
        this->start_date = start_date;
        this->duration = duration*3600; // converting hours to time
        this->assigned_platform = -1;
    }

time_t TrainArrival::get_start_date() const {
    /**
    * getter method fort the start_date attribute
    * @return start_date attribute
    */
    return start_date;
}

string TrainArrival::get_type() {
    /**
    * getter method fort the type attribute
    * @return type attribute
    */
    return type;
}

string TrainArrival::get_plate() {
    /**
    * getter method fort the plate attribute
    * @return plate attribute
    */
    return plate;
}

int TrainArrival::get_duration() const {
    /**
    * getter method fort the duration attribute
    * @return duration attribute
    */
    return duration;
}

void TrainArrival::set_platform(int platform) {
    /**
    * setter method fort the platform attribute
    * @param platform attribute
    */
    this->assigned_platform = platform;
}

bool TrainArrival::operator<(const TrainArrival & train) const {
    /**
    * "<" operator overloading for the TrainArrival class
    * @param train TrainArrival object attribute
    * @return boolean: true if the first argument start date is smaller then the second argument start date
    */
    if (train.get_start_date()> this->get_start_date()) {
        return true;
    }
    else {
        return false;
    }
}

int TrainArrival::get_platform() const {
    /**
    * getter method fort the platform attribute
    * @return platform attribute
    */
    return this->assigned_platform;
}

