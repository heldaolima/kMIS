#include "results_writer.h"
#include <fstream>
#include <chrono>
#include <ctime>

ResultsWriter::ResultsWriter(string outFilePath, string header) {
  this->outFilePath = outFilePath;

  std::ofstream outFile(outFilePath, std::ofstream::out);
  outFile << header;
  outFile.close();
}

void ResultsWriter::writeResults(const string inputFileName, Objectives* objs, Times* times, int k) {
  std::ofstream outFile(outFilePath, std::ios_base::app);

  outFile << inputFileName << ",";
  outFile << k << ",";
  outFile << objs->best << "," << objs->worst << ",";
  outFile << objs->average << "," << times->avgTimeToFindBest << "\n";


  outFile.close();
}
