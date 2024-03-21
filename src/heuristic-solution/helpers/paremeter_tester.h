#ifndef __parameter_tester_h__
#define __parameter_tester_h__

#include "results_writer.h"
#include "tester.h"

enum ParametersEnum {
  RESTART_THRESHOLD,
};

class ParameterTester: Tester {
private:
  ResultsWriter* writer;
  ParametersEnum param;

  void testRestart(fs::directory_entry* inputFile);
public:
  ParameterTester(string outputPath, ParametersEnum param);
  void testFile(fs::directory_entry inputFile) override;
  ~ParameterTester() {
    delete writer;
  }

};

#endif
