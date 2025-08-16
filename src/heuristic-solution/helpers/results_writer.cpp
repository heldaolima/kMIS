#include "results_writer.h"
#include <ctime>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

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

void ResultsWriter::writeGlobalTTT(const string &instance, const string& algorithm, const vector<double>& times) {
  const string out = "results_ttt/results.csv";
  bool exists = std::filesystem::exists(out);
  std::ofstream outFile(out, std::ios_base::app);
 
  if (!exists) {
    outFile << "instance,algorithm,time\n";
  }

  for (double time: times) {
    outFile << instance << ","
      << algorithm << ","
      << time << "\n";
  }

  outFile.close();
}

void ResultsWriter::writeInstanceTTT(const string &instance, map<string, vector<double>> times, int target) const {
  const string dir = "results_ttt/";
  const string filename = dir + instance + "_" + std::to_string(target) + ".csv";
  bool exists = std::filesystem::exists(filename);

  std::ofstream outFile(filename);

  vector<string> algorithms;
  for (const auto &entry: times){
    algorithms.push_back(entry.first);
  }
  for (size_t i = 0; i < algorithms.size(); ++i) {
    outFile << algorithms[i];
    if (i < algorithms.size() - 1)
      outFile << ",";
  }
  outFile << "\n";

  for (int i = 0; i < times.begin()->second.size(); i++) {
    for (int j = 0; j < algorithms.size(); j++) {
      outFile << times[algorithms[j]][i];
      if (j < algorithms.size() - 1) {
        outFile << ",";
      }
    }
    outFile << "\n";
  }

  outFile.close();
}

void ResultsWriter::writePartial(const string &inputFileName, const string &outPath, 
                                const Times &times, const Objectives &objs) {

  std::ofstream outFile(outPath, std::ios_base::app);

  outFile << inputFileName << ",";
  outFile << objs.best << "," << objs.worst << ",";
  outFile << objs.average << "," << times.avgTimeToFindBest << ",";
  outFile << times.average << "\n";

  outFile.close();

}

void ResultsWriter::writePartialDetailed(const string &inputFileName, const string &outPath,
                                         const double time, const int obj) {
  std::ofstream outFile(outPath, std::ios_base::app);

  outFile << "instance,obj,time\n";
  outFile << inputFileName << "," << obj << "," << time << "\n";

  outFile.close();
}