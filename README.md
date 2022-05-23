# ideal-octo-barnacle
This repository contains some C++ code implementing a scheduling algorithm for the allocation of a number of trains on some platforms, so that certain constraints are satisfied. 
More details on the problem statement and solution requirements are contained in the file `exercise.pdf`.

## Build instructions
The program makes use of a small part of the [Boost Library](https://www.boost.org), which was employed to construct a simple
command line parser. 

The [CMake](https://cmake.org) was used for build automation.
In order to compile and build the program one can use the following commands

```
mkdir build
cd build 
cmake ../
make 
```
Note that these installation instructions have been tested only on Mac OS and Linux machines.
## Execute on sample dataset
In order to execute the program on a sample dataset, which is stored in the `data` folder
one can type the following command

```asm
cd build
./src/assign_platform_run \
--n_platforms 10 \
--input ../data/input_small.csv \ 
--assign_first false > out
```
The command-line parameter `n_platforms` is the number of the available platforms on which 
trains can be assigned. If `n_plaforms = -1` then the program assumes that there is an infinite amout of platforms on which one can 
assign the trains. The `input` parameters is the path to the input files containing train information.
The parameter `assign_first` is a `bool` value controlling the option of assigning a train to a compatible platform at
the first available time point. The output of the algorithm is a `csv` table, printed to `stdout`, listing, 
for each train, the train plate, the train type, the assigned platform and the effective start date (if the platform is not 
`Unassigned`).

A sample output is of the form
```asm
 Train_plate,Train_type,Platform,Effective_start_date
 CO057GD,ELETTRICO 700Hz,5,Wed Jan  1 02:00:00 2020
 AA437PK,DIESEL 4000.0,2,Sat Jan 11 20:00:00 2020
 BO027QB,ELETTRICO 1000Hz,3,Wed Jan 15 17:00:00 2020
 BG184EN,ELETTRICO 1000Hz,3,Thu Jan 16 10:00:00 2020
 DJ501FI,DIESEL 3800.0,0,Thu Jan 30 12:00:00 2020
 DG239OM,ELETTRICO 900Hz,7,Sat Feb  1 16:00:00 2020
 FG054EW,ELETTRICO 1000Hz,3,Thu Feb  6 13:00:00 2020
 DH654SW,DIESEL 3800.0,0,Mon Feb 10 08:00:00 2020
 BQ925NA,ELETTRICO 700Hz,5,Thu Feb 13 10:00:00 2020
 EM306OH,ELETTRICO 700Hz,5,Mon Feb 17 06:00:00 2020
 BA304HQ,ELETTRICO 800Hz,6,Mon Feb 17 22:00:00 2020
 DZ398GC,DIESEL 3900.0,1,Tue Feb 25 20:00:00 2020
 AZ401MW,DIESEL 4000.0,2,Tue Mar  3 07:00:00 2020
 BY257FI,DIESEL 3900.0,1,Fri Mar  6 06:00:00 2020
 DA573IL,DIESEL 3900.0,1,Tue Mar 10 16:00:00 2020
```
