# An ILS algorithm for the Maximum k-Subset Intersection Problem

## How to run

1. `$ cd src/heuristic-solution`
2. Add [`cxxopts`](https://github.com/jarro2783/cxxopts) to the available headers on your system. Alternatively, you can download the header, place it in this repository, and update the include in `parse_arguments.cpp` to use `#include "cxxopts.hpp"` instead of `#include <cxxopts.hpp>`.
2. Run `make`
3. Run `./main.out -h` to see all command line options that change the way the algorithm behaves
4. Run `make run_standard` to run the algorithm in the standard way

## External Dependencies

- [`cxxopts`](https://github.com/jarro2783/cxxopts)
