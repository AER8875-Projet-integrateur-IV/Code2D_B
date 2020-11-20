#include "Solver.h"

// Constructor
Solver::Solver(Mesh &mesh, Input &inputVals, Metrics &metrics)
  :mesh_sol(mesh), input_sol(inputVals), metrics_sol(metrics){
  // Initialize the first results
  Results Simulation = Results(mesh, inputVals);
  dt.resize(mesh_sol.nElem);
}

// Compute the solver
void Solver::ComputeSolver(){
  std::cout << "----- Starting iterative process -----" << '\n';
  Solver::UpdateBC();
  std::vector<double> res = {0,0,0,0};
  int nb_it = 0;

  // Iteration process until convergence
  while (/*res[0] > input_sol.errMax &&*/ nb_it < input_sol.nbIterMax){
    Solver::ComputeDeltaT();
    Solver::CalcRes();
    nb_it += 1;
    for (int iElem = 0; iElem <mesh_sol.nElem; iElem++){
      //std::cout << dt[iElem] << '\n';
    }
  }
}

// Calculate deltaT
void Solver::ComputeDeltaT(){
  for (int iElem = 0; iElem<mesh_sol.nElem; iElem++){
    dt[iElem] = input_sol.cfl*metrics_sol.area[iElem]/1;
    // Missing spectral radii
  }
}

// Calculate residu
void Solver::CalcRes(){
  double resRho = 0;
  double resRhoU = 0;
  double resRhoV = 0;
  double resRhoH = 0;

  for (int iFace = 0; iFace<mesh_sol.nFace; iFace++){
    //resRh0 += Fc[iFace]*
  }
}

// Calculate the spectral radii ()
/*void CalcRadii(int &elem1){
  double Sx = 0;
  double Sy = 0;

  for (int iFace = 0; iFace < meconvectiveRadiish_sol.nNode[elem1]; iFace++){
    Sx +=
  }
  convecRadiiX = std::abs(Simulation.u[elem1]+c)*0.5*Sx;
  convecRadiiY = std::abs(Simulation.v[elem1]+c)*0.5*Sy;
  convecRadiiTotal = convecRadiiX+convecRadiiY;
}*/

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
