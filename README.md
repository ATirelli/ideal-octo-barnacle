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
## Execute on sample dataset
In order to execute the program on a sample dataset, which is stored in the `data` folder
one can type the following command

```asm
cd build
./src/assign_platform_run \
--n_platforms -1 \
--input ../data/input_small.csv > out
```
The command-line parameter `n_platforms` is the number of the available platforms on which 
trains can be assigned. If `n_plaforms = -1` then the program assumes that there is an infinite amout of platforms on which one can 
assign the trains. The `input` parameters is the path to the input files containing train information.
The algorithm output is printed to `stdout`, so, with the above command, the outout will be contained in the `out` file.

The output is of the form
```asm
Train plate: EY097TC Train type: DIESEL 3800.0 Platform: Unassigned
Train plate: BY765AU Train type: ELETTRICO 600Hz Platform: Unassigned
Train plate: BN423XF Train type: DIESEL 3900.0 Platform: 2
Train plate: BZ028TH Train type: ELETTRICO 800Hz Platform: Unassigned
Train plate: AC413DG Train type: DIESEL 4000.0 Platform: 3
```