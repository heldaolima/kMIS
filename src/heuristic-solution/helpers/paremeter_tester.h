#ifndef __parameter_tester_h__
#define __parameter_tester_h__

#include "results_writer.h"
#include "tester.h"

enum ParametersEnum {
  RESTART_THRESHOLD,
  TABU_TENURE,
  NORMAL_LS_TWO,
  RANDOM_LS_TWO,
  RANDOM_LS_TWO_TABU,
};

class ParameterTester: Tester {
private:
  ResultsWriter* writer;
  ParametersEnum param;

  void testRestart(fs::directory_entry* inputFile);
  void testTenure(fs::directory_entry* inputFile);
  void lsTwo(fs::directory_entry* inputFile, bool random);
  void lsTwoTabu(fs::directory_entry* inputFile, bool random);
  void testRandomLSTwoTabu(fs::directory_entry* inputFile);
public:
  ParameterTester(string outputPath, ParametersEnum param);
  void testFile(fs::directory_entry inputFile) override;
  ~ParameterTester() {
    delete writer;
  }

};

#endif
