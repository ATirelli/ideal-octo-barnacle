#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/program_options.hpp>
#include <limits>
#include <ctime>
#include "utils.h"

using namespace std;
using namespace boost::program_options;


void assign_platform(size_t available_platforms, vector<TrainArrival>& train_arrivals,
                     bool & assign_first_available) {
    /**
    * Train assignment algorithm
    * @param available_platforms Number of available platforms on which we can assign train
    * @param train_arrivals vector of TrainArrival objects representing trains to be assigned
    */
    int j, min_index, min_value;
    vector<string>::iterator ip;
    vector<string> train_types;
    for (auto &train: train_arrivals) {
        train_types.push_back(train.get_type());
    }
    sort( train_types.begin(), train_types.end() );
    train_types.erase( unique( train_types.begin(), train_types.end() ), train_types.end() );

    size_t number_train_types {train_types.size()};

    vector<time_t> occupation {};
    vector<string> type_platform {};

    if (available_platforms != -1 && number_train_types> available_platforms) {
        cout << "Number of train types larger than available platform!" << endl;
        cout << "On this input the minimum number of platforms is: " << number_train_types << endl;
        cout << "Assignment task cannot be performed, exiting program." << endl;
        exit(1);
    }

    if (available_platforms != -1) {
        occupation.reserve(available_platforms);
        type_platform.reserve(available_platforms);
        for (j=0; j<available_platforms; j++) {
            occupation.push_back(0);
            type_platform.emplace_back("");
        }
        for (j=0; j<number_train_types; j++) {
            type_platform.at(j) = train_types.at(j);
        }
    }

    if (available_platforms == -1) {
        /* case in which there is an infinite amount of platforms */
        for (auto &train: train_arrivals) {
            cout << train.get_start_date() << endl;
            if (occupation.empty()) {
                occupation.push_back(train.get_start_date() + train.get_duration());
                type_platform.push_back(train.get_type());
                train.set_platform(j);
            }
            else {
                for (j = 0; j < occupation.size(); j++) {
                    if (type_platform.at(j) == train.get_type()) {
                        if (train.get_start_date() >= occupation.at(j)) {
                            train.set_platform(j);
                            occupation.at(j) = train.get_start_date() + train.get_duration();
                            break;
                        }
                    }
                }
                if (train.get_platform()==-1) {
                    occupation.push_back(train.get_start_date() + train.get_duration());
                    type_platform.push_back(train.get_type());
                    train.set_platform(j+1);
                }
            }
        }
    } else {
        /* case in which there is a finite amount of platforms */
        for (auto &train: train_arrivals) {
            for (j = 0; j < available_platforms; j++) {
                if (type_platform.at(j).empty()) {
                    train.set_platform(j);
                    occupation.at(j) = train.get_start_date() + train.get_duration();
                    type_platform.at(j) = train.get_type();
                    break;

                } else if (type_platform.at(j) == train.get_type()) {
                    if (train.get_start_date() >= occupation.at(j)) {
                        train.set_platform(j);
                        occupation.at(j) = train.get_start_date() + train.get_duration();
                        break;
                    }
                }
            }
            if (train.get_platform()==-1 && assign_first_available) {
                min_index = 0;
                min_value = numeric_limits<int>::max();
                for (j = 0; j < available_platforms; j++) {
                    if (type_platform.at(j) == train.get_type()) {
                        if (train.get_duration() < min_value) {
                            min_index = j;
                            min_value = train.get_duration();
                        }
                    }
                }
                train.set_platform(min_index);
                train.set_start_date(occupation.at(min_index));
                occupation.at(min_index) += train.get_duration();
            }
        }
    }
}


int main(int argc, const char *argv[])
{
    try {
        int available_platforms, train_platform;
        bool assign_first_available;
        string input, train_plate, train_type;
        time_t effective_start_date;
        options_description desc{"Options"};
        desc.add_options()
                ("help,h", "Help screen")
                ("n_platforms", value<int>(&available_platforms)->default_value(10), "number of available platforms")
                ("input", value<string>(&input)->default_value(""), "input file to process")
                ("assign_first", value<bool>(&assign_first_available)->default_value(false),
                        "in case of unavailability, assign to first available platform and time");

        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);
        auto train_arrivals = get_input(input);
        sort(train_arrivals.begin(), train_arrivals.end());
        assign_platform(available_platforms, train_arrivals, assign_first_available);

        // Printing output to stdout in csv format
        cout << "Train_plate,Train_type,Platform,Effective_start_date" << endl;
        for (auto &train:train_arrivals) {
            train_plate = train.get_plate();
            train_type = train.get_type();
            train_platform = train.get_platform();
            effective_start_date = train.get_start_date();
            cout << train_plate << "," << train_type<<","<<
            ((train_platform==-1) ? "Unassigned" : to_string(train_platform))
            <<"," << ((train_platform==-1) ? "\n" : ctime(&effective_start_date));
        }

    }

    catch (const error &ex)
    {
        std::cerr << ex.what() << '\n';
    }


}