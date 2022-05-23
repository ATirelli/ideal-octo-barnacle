//
// Created by Andrea Tirelli on 21/05/22.
//
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "utils.h"
using namespace std;


time_t convert_str_to_time(string t) {
    /**
    * Convert string to time_t
    * @param t string representing a timestamp to be converted
    * @return t_time_time time_t converted timestamp
    */
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
    /**
    * Read csv file
    * @param fname name of the file to be read
    * @param sep character separator for file to be parsed
    * @return matrix of string representing parsed files
    */
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
    /**
    * Parse input file and convert it into a vector of TrainArrival objects
    * @param fname name of the file to be read
    * @return vector of TrainArrival objects
    */
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

char* convert_time_t_to_string(time_t) {
    time_t buf;
    return ctime(&buf);
}