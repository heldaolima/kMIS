#ifndef __tester_h__
#define __tester_h__

#include "../data_structures/objectives.h"
#include "../data_structures/times.h"
#include <ctime>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;
using std::string;

#define NUMBER_OF_TESTS 10

class Tester {
public:
  ~Tester() {}
  virtual void testFile(const fs::directory_entry &inputFile) const = 0;
};

#endif
