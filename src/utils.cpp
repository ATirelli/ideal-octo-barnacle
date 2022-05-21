//
// Created by Andrea Tirelli on 21/05/22.
//
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "utils.h"
using namespace std;


// utility functions in order to:
//     -- convert string to time, read
//     -- read the csv input
//     -- parse the input and encode it into the correct format

time_t convert_str_to_time(string t) {
    time_t t_time_t;
    int yy, month, dd, hh, mm, ss;
    struct tm whenStart;
    const char *zStart = t.c_str();

    sscanf(zStart, "%d-%d-%d %d:%d:%d", &yy, &month, &dd, &hh, &mm, &ss);
    whenStart.tm_year = yy - 1900;
    whenStart.tm_mon = month - 1;
    whenStart.tm_mday = dd;
    whenStart.tm_hour = hh;
    whenStart.tm_min = mm;
    whenStart.tm_sec = ss;
    whenStart.tm_isdst = -1;

    t_time_t = mktime(&whenStart);
    return t_time_t;
}
vector<vector<string>> read_csv(const string & fname, char sep) {
    std::vector<std::vector<string> > items;
    std::ifstream ifs(fname);
    if (ifs.fail()) {
        std::cerr << "error" << std::endl;
        exit(-1);
    }
    string line;
    while (getline(ifs, line)) {
        std::stringstream ss(line);
        std::vector<std::string> item;
        std::string tmp;
        while(getline(ss, tmp, sep)) {
            item.push_back(tmp);
        }
        items.push_back(item);
    }
    return items;
}

vector<TrainArrival> get_input(const string &fname) {
    vector<vector<string>> train_info = read_csv(fname, ',');

    vector<TrainArrival> train_arrivals {};

    for (const vector<string> &info:train_info) {
        if (info.at(0) == "type") {}
        else {
            TrainArrival train(info.at(0),
                               info.at(1),
                               convert_str_to_time(info.at(2)),
                               stoi(info.at(3)));
            train_arrivals.push_back(train);
        }

    }
    return train_arrivals;
}