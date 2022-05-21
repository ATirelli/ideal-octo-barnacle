#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/program_options.hpp>
#include "utils.h"

using namespace std;
using namespace boost::program_options;

// this is the main algorithm of the exercise, where we assign each train to a platform, if possible
void assign_platform(size_t available_platoforms, vector<TrainArrival>& train_arrivals) {
    int j, designed_platform;
    
    vector<time_t> occupation(available_platoforms);
    fill(occupation.begin(), occupation.end(), 0);

    vector<string> type_platform(available_platoforms);
    fill(type_platform.begin(), type_platform.end(), "");

    if (available_platoforms < 0) { 
        available_platoforms = train_arrivals.size();
        cout << "The assigment algorithm is now assuming we have an infinite amount of platforms!" << endl;
    } 

    for (auto &train:train_arrivals) { 
        for (j=0; j<available_platoforms; j++) { 
            if (type_platform.at(j).empty()) {
                train.set_platform(j); 
                occupation.at(j) = train.get_start_date() + train.get_duration();
                type_platform.at(j)=train.get_type(); 
                break;

            }
            else if (type_platform.at(j)==train.get_type()) { 
                if (train.get_start_date() >= occupation.at(j)) {
                    train.set_platform(j); 
                    occupation.at(j) = train.get_start_date() + train.get_duration();
                    break;
                    }

            }
        }
        if (j == available_platoforms - 1) { 
            //cout << "No platform available for train with plate: " << train.get_plate() << endl;
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
        for (auto &train:train_arrivals) {
            cout << "Train plate: " << train.get_plate() << " Start date: " << train.get_start_date()
                 << " Platform: " << train.get_platform() << endl;
        }
        assign_platform(available_platforms, train_arrivals);
        for (auto &train:train_arrivals) {
            cout << "Train plate: " << train.get_plate() << " Train type: " << train.get_type()
                 << " Platform: " << train.get_platform() << endl;
        }

    }

    catch (const error &ex)
    {
        std::cerr << ex.what() << '\n';
    }


}