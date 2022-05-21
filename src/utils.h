//
// Created by Andrea Tirelli on 21/05/22.
//

#ifndef SCHEDULE_TRAIN_ARRIVALS_UTILS_H
#define SCHEDULE_TRAIN_ARRIVALS_UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

#include "TrainArrival.h"

using namespace std;


// utility functions in order to:
//     -- convert string to time, read
//     -- read the csv input
//     -- parse the input and encode it into the correct format
//     -- sort train arrivals in ascending temporal order

time_t convert_str_to_time(string);

vector<vector<string>> read_csv(string &, char);

vector<TrainArrival> get_input(const string &);

#endif //SCHEDULE_TRAIN_ARRIVALS_UTILS_H
