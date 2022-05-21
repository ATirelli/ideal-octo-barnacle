#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/program_options.hpp>
#include "utils.h"

using namespace std;
using namespace boost::program_options;


void assign_platform(size_t available_platforms, vector<TrainArrival>& train_arrivals) {
    /**
    * Train assignment algorithm
    * @param available_platforms Number of available platforms on which we can assign train
    * @param train_arrivals vector of TrainArrival objects representing trains to be assigned
    */
    int j;

    vector<time_t> occupation {};
    vector<string> type_platform {};
    if (available_platforms != -1) {
        occupation.reserve(available_platforms);
        type_platform.reserve(available_platforms);
        for (j=0; j<available_platforms; j++) {
            occupation.push_back(0);
            type_platform.emplace_back("");
        }
        cout << "heree" << endl;
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
        }

    }
}

int main(int argc, const char *argv[])
{
    try {
        int available_platforms;
        std::string fast5, input, barcodes, adapter, outdir, umi_dir;
        options_description desc{"Options"};
        desc.add_options()
                ("help,h", "Help screen")
                ("n_platforms", value<int>(&available_platforms)->default_value(10), "number of available platforms")
                ("input", value<string>(&input)->default_value(""), "input file to process");

        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);
        auto train_arrivals = get_input(input);
        sort(train_arrivals.begin(), train_arrivals.end());
        cout << "main"<<endl;
        assign_platform(available_platforms, train_arrivals);
        for (auto &train:train_arrivals) {
            cout << "Train plate: " << train.get_plate() << " Train type: " << train.get_type()
                 << " Platform: " << ((train.get_platform()==-1) ? "Unassigned" : to_string(train.get_platform())) << endl;
        }

    }

    catch (const error &ex)
    {
        std::cerr << ex.what() << '\n';
    }


}