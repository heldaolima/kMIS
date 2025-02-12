#include "results_writer.h"
#include <ctime>
#include <fstream>
#include <sstream>

ResultsWriter::ResultsWriter(const string &outFilePath, const string &header)
    : outFilePath(outFilePath) {

  std::ofstream outFile(this->outFilePath, std::ofstream::out);
  outFile << header;
  outFile.close();
}

void ResultsWriter::writeResults(const string &inputFileName,
                                 const Objectives &objs, const Times &times,
                                 int k) const {
  std::ofstream outFile(outFilePath, std::ios_base::app);

  outFile << inputFileName << ",";
  outFile << k << ",";
  outFile << objs.best << "," << objs.worst << ",";
  outFile << objs.average << "," << times.avgTimeToFindBest << ",";
  outFile << times.average << "\n";

  outFile.close();
}

void ResultsWriter::writeTTT(const string &inputFileName,
                             const string &heuristic, const Times &times,
                             int target) const {
  const string dir = "results_ttt/";
  std::ostringstream ss;
  ss << dir << heuristic << target << "_" << inputFileName << ".dat";
  std::cout << ss.str() << "\n";

  std::ofstream outFile(ss.str(), std::ios_base::app);
  outFile << times.average << "\n";
  outFile.close();
}
