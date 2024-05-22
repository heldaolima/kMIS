/*
mARESTA

forall i in R 
x[i] == 1   i está na solução
x[i] == 0   cc

forall j in L
y[j] == 1   caso j seja um dos k subconjuntos da solução
y[j] == 0   cc

Objetivo:
  max(sum(x[i]))

S.A:
  sum(y[j]) == k [1]

  x[i] + y[j] <= 1, forall j in L, forall i in naoVizinhos(j) [2]
  x[i] in {0, 1} [3]
  y[j] in {0, 1} [4]

*/

#include <iostream>
#include <filesystem>
#include <ilcplex/cplex.h>
#include <ilcplex/ilocplex.h>
#include "input.h"
#include <string>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;
string summaryPath = "results.txt";

void solveInstance(string instance, string instancePath, string outputPath) {
  IloEnv env;
  try {
    Input input(instancePath.c_str());

    unsigned int i = 0, j = 0;

    IloModel model(env);

    stringstream name;

    // decision variables
    IloNumVarArray x(env, input.quantityOfElements);
    IloNumVarArray y(env, input.quantityOfSubsets);

    for (i = 0; i < input.quantityOfElements; i++) {
      name << "elem_" << i;
      x[i] = IloNumVar(env, 0, 1, IloNumVar::Bool, name.str().c_str());
      name.str("");
    }

    for (j = 0; j < input.quantityOfSubsets; j++) {
      name << "subset_" << j;
      y[j] = IloNumVar(env, 0, 1, IloNumVar::Bool, name.str().c_str());
      name.str("");
    }

    IloExpr expr(env);

    // constraint [1]
    for (j = 0; j < input.quantityOfSubsets; j++) {
      expr += y[j];
    }

    model.add(expr == input.k);
    expr.clear();

    // constraint [2]
    for (j = 0; j < input.quantityOfSubsets; j++) {
      for (i = 0; i < input.quantityOfElements; i++) {
        if (input.nonNeighbors(j, i)) {
          model.add(y[j] + x[i] <= 1);
        }
      }
    }

    // objective function
    for (i = 0; i < input.quantityOfElements; i++) {
      expr += x[i];
    }
    IloObjective obj(env, expr, IloObjective::Maximize);
    model.add(obj);
    expr.end();

    IloCplex cplex(model);

    cplex.exportModel("kmis_model.lp");
    if (cplex.solve()) {
      ofstream outFile(outputPath);
      ofstream outFileSummary(summaryPath);

      outFile << "Cplex Success\n";
      outFile << "Status: " << cplex.getStatus() << "\n";
      outFile << "Objective value: " << cplex.getObjValue() << "\n\n";

      outFileSummary << instance << "," << cplex.getObjValue() << "\n";

      outFile << "Subsets: ";
      for (j = 0; j < input.quantityOfSubsets; j++) {
        if (cplex.getValue(y[j])) {
          outFile << j + 1 << " ";
        }
      }
      outFile << "\nIntersection: ";
      for (i = 0; i < input.quantityOfElements; i++) {
        if (cplex.getValue(x[i])) {
          outFile << i + 1 << " ";
        }
      }
      outFile << "\n";

      outFile.close();
      outFileSummary.close();
    } else {
      cerr << "Cplex error on instance " << instancePath << "!\n";
      cerr << "Status: " << cplex.getStatus() << "\n";
      cerr << "Solver status: " << cplex.getCplexStatus() << "\n";
    }
  } catch (const IloException& e) {
    cerr << "CPLEX Raised an exception on instance " << instancePath << ":\n";
    cerr << e << "\n";
  } catch (const exception& e) {
    cerr << "Standard exception on instance " << instancePath << ":\n";
    cerr << e.what() << "\n";
  } catch (...) {
    cerr << "Unknown exception on instance " << instancePath << "!\n";
  }
  env.end();
}

int main(int argc, char* argv[]) {
  const string path = "../instances/";
  string dirs[3] = {"type1", "type2", "type3"};

  for (const auto dir: dirs) {
    for (const auto& file : fs::directory_iterator(path + dir)) {
      if (file.is_regular_file()) {
        string instancePath = file.path().string();
        string instance = file.path().stem().string();
        string outputFileName = instance +  "_result.txt";
        string outputPath = "./results/" + outputFileName;

        cout << "file: " << instancePath << "\n";
        solveInstance(instance, instancePath, outputPath);
      }
    }
  }
  return 0;
}
