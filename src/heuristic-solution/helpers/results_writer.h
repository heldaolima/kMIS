#ifndef __results_writer_h__
#define __results_writer_h__

#include "../data_structures/objectives.h"
#include "../data_structures/solution.h"
#include "../data_structures/times.h"
#include <string>

using std::string;

class ResultsWriter {
private:
  string outFilePath;

public:
  ResultsWriter(const string &outFilePath, const string &header);
  void writeResults(const string &inputFileName, const Objectives &objs,
                    const Times &times, int k);
};

#endif
