#include "load_ttt_files.h"

#include <fstream>
#include <iostream>

std::map<string, int> load_ttt_files(const std::string &path) {
  std::map<std::string, int> instance_target;
  std::ifstream file(path);
  if (!file) {
    std::cerr << "Erro ao abrir o arquivo de configuração!\n";
    return instance_target;
  }

  std::string filename;
  int value;
  while (file >> filename >> value) {
    instance_target[filename] = value;
  }

  file.close();

  return instance_target;
}
