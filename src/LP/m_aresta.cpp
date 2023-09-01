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
#include "input.h"
#include <ilcplex/cplex.h>
#include <ilcplex/ilocplex.h>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cout << "USAGE: ./m_aresta <input_file>";
    exit(1);
  }

  stringstream path;

  path << "../instances/" << argv[1];

  Input input(path.str().c_str());

  unsigned int i = 0, j = 0;

  IloEnv env;
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

  // contraint [1]
  for (j = 0; j < input.quantityOfSubsets; j++) {
    expr += y[j];
  }

  model.add(expr == input.k);

  expr.clear();

  // constraint [2]
  for (j = 0; j < input.quantityOfSubsets; j++) {
    for (i = 0; i <input.quantityOfElements; i++) {
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
  try {
    if (cplex.solve()) {
      cout << "\nCplex Success\n";
      cout << "\tStatus: " << cplex.getStatus() << "\n";
      cout << "\tObjective value: " << cplex.getObjValue() << "\n";
      cout << "\n";

      cout << "Subsets: ";
      for (j = 0; j < input.quantityOfSubsets; j++) {
        if (cplex.getValue(y[j])) {
          cout << j+1 << " ";
        }
      }

      cout << "\nIntersection: ";
      for (i = 0; i < input.quantityOfElements; i++) {
        if (cplex.getValue(x[i])) {
          cout << i+1 << " ";
        }
      }
      cout << "\n";

    } else {
      cerr << "\n\nCplex error!\n";
      cerr << "\tStatus: " << cplex.getStatus() << "\n";
      cerr << "\tSolver status: " << cplex.getCplexStatus() << "\n";
    }
  } catch(const IloException& e) {
      cerr << "\n\nCPLEX Raised an exception:\n";
      cerr << e << "\n";
      env.end();
      throw;
  }

  env.end();

  return 0;
}
