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
                    const Times &times, int k) const;
  void writeInstanceTTT(const string &instance, map<string, vector<double>> times, int target) const;
  void writeGlobalTTT(const string &instance, const string& algorithm,
                    const vector<double>& times);
  void writePartial(const string &inputFileName, const string &outPath,
                    const Times &times, const Objectives &objs);
  void writePartialDetailed(const string &inputFileName, const string &outPath,
                            const double time, const int obj);
  };

#endif
