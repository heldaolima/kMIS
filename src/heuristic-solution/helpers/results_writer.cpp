#include "results_writer.h"
#include <chrono>
#include <ctime>
#include <fstream>

ResultsWriter::ResultsWriter(const string &outFilePath, const string &header)
    : outFilePath(outFilePath) {

  std::ofstream outFile(this->outFilePath, std::ofstream::out);
  outFile << header;
  outFile.close();
}

void ResultsWriter::writeResults(const string &inputFileName, const Objectives& objs,
                                 const Times &times, int k) {
  std::ofstream outFile(outFilePath, std::ios_base::app);

  outFile << inputFileName << ",";
  outFile << k << ",";
  outFile << objs.best << "," << objs.worst << ",";
  outFile << objs.average << "," << times.avgTimeToFindBest << "\n";

  outFile.close();
}
