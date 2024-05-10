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
  outFile << times->average << "," << objs->average << ",";
  outFile << objs->averageFound << ",";
  outFile << objs->worst << "," << objs->best << "\n";

  outFile.close();
}

void writeSolution(const string inputFileName, Solution& solution) {
  std::ofstream outFile("../outputs/"+inputFileName, std::ios_base::app);


  std::time_t now = std::time(nullptr);
  string now_str = std::asctime(std::localtime(&now));
  now_str.pop_back();

  outFile << "[" << now_str << "]\n";
  outFile << solution.toString() << "\n";
  outFile.close();

  std::cout << "wrote\n";
}
