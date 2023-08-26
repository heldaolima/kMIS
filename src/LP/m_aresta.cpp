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

int main() {
  Input input("entry.dat");
  
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

  // constraints
  
  // contraint [1]
  for (j = 0; j < input.quantityOfSubsets; j++) {
    expr += y[j];
  }
  IloRange sumY(env, input.k, expr, input.k, "somatorio");
  model.add(sumY);

  expr.clear();

  // constraint [2]
  for (j = 0; j < input.quantityOfSubsets; j++) {
    for (i = 0; i <input.quantityOfElements; i++) {
      if (input.nonNeighbors(j, i)) {
        name << "non_neighbors_" << j << "_" << i;

        IloExpr restrExpr(env);
        restrExpr += y[j] + x[i];
        IloRange nonNeighborsConstraint(env, -IloInfinity, restrExpr, 1, name.str().c_str());
        model.add(nonNeighborsConstraint);
        
        restrExpr.end();
        name.str("");
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
        if (cplex.getValue(y[j]) == 1) {
          cout << j+1 << " ";
        }
      }

      cout << "\nIntersection: ";
      for (i = 0; i < input.quantityOfElements; i++) {
        if (cplex.getValue(x[i]) == 1) {
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
