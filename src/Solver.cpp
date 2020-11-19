#include "Solver.h"

// Constructor
Solver::Solver(Mesh &mesh, Input &inputVals)
  :mesh_sol(mesh), input_sol(inputVals){
  // Initialize the first results
  Results Simulation = Results(mesh, inputVals);
  //mesh_sol = mesh;
  //input_sol = inputVals;
}

// Compute the solver
void Solver::ComputeSolver(){
  std::cout << "----- Starting iterative process -----" << '\n';
  Solver::UpdateBC();
}

// Update boundary condition
void Solver::UpdateBC(){
  for (int iElem = 0; iElem<mesh_sol.nElem; iElem++){
    for (int iNfael = 0; iNfael<mesh_sol.nFael[iElem]; iNfael++){
      
    }
  }
}
