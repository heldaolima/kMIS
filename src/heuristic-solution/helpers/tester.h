#ifndef __tester_h__
#define __tester_h__

#include <filesystem>
#include <ctime>
#include <string>
#include "../data_structures/objectives.h"
#include "../data_structures/times.h"

namespace fs = std::filesystem;
using std::string;

#define NUMBER_OF_TESTS 10

class Tester {
public: 
  virtual void testFile(fs::directory_entry inputFile) = 0;
};

#endif
