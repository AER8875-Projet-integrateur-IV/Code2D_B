#include "Solver.h"

// Constructor
Solver::Solver(Mesh &mesh, Input &inputVals)
  :mesh_sol(mesh), input_sol(inputVals){
  // Initialize the first results
  Results Simulation = Results(mesh, inputVals);
  mesh_sol = mesh;
  input_sol = inputVals;
}

// Compute the solver
void Solver::ComputeSolver(){
  std::cout << "----- Starting iterative process -----" << '\n';
  Solver::UpdateBC();
  for (int iElem = 0; iElem<mesh_sol.nElem; iElem++){

  }
}

// Update boundary condition
void Solver::UpdateBC(){
  std::cout << "Boundary conditions update not done" << '\n';
  for (int iElem = 0; iElem<mesh_sol.nElem; iElem++){
    for (int iNfael = 0; iNfael<mesh_sol.nFael[iElem]; iNfael++){
      if (mesh_sol.eSuel[iElem][iNfael] > mesh_sol.nElem){

      }
    }
  }
}
