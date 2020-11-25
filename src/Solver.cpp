#include "Solver.h"

// Constructor
Solver::Solver(Mesh &mesh, Input &inputVals, Metrics &metrics)
  :mesh_sol(mesh), input_sol(inputVals), metrics_sol(metrics){
  // Initialize the first results
  dt.resize(mesh_sol.nElem);
}

// Compute the solver
void Solver::ComputeSolver(){
  std::cout << "----- Starting iterative process -----" << '\n';
  Solver::UpdateBC();
  std::vector<double> res = {0,0,0,0};
  int nb_it = 0;

  Results Simulation = Results(mesh_sol, input_sol);

  // Iteration process until convergence
  while (/*res[0] > input_sol.errMax &&*/ nb_it < input_sol.nbIterMax){
    Solver::ComputeDeltaT(Simulation.u, Simulation.v);
    nb_it += 1;
    /*for (int iElem = 0; iElem <mesh_sol.nElem; iElem++){
      Solver::CalcRes(iElem, {0,0,0,0});
    }*/
  }
}

// Calculate deltaT
void Solver::ComputeDeltaT(std::vector<double> u, std::vector<double> v){
  for (int iElem = 0; iElem<mesh_sol.nElem; iElem++){
    CalcRadii(iElem, u, v);
    dt[iElem] = input_sol.cfl*metrics_sol.area[iElem]/1;
    // Missing spectral radii
  }
}

// Calculate residual (valid for 1 element)
void Solver::CalcRes(int elem1, std::vector<std::vector<double>> Fc){
  double resRho = 0;
  double resRhoU = 0;
  double resRhoV = 0;
  double resRhoH = 0;

  int faces = mesh_sol.iNpoel[elem1].size();

  for (int iFace = 0; iFace<faces; iFace++){
    double area = metrics_sol.faceArea[elem1][iFace];
    resRho += Fc[iFace][0]*area;
    resRhoU += Fc[iFace][1]*area;
    resRhoV += Fc[iFace][2]*area;
    resRhoH += Fc[iFace][3]*area;
  }
}

// Calculate the spectral radii ()  // -> COMPLÉTÉ MAIS AVEC PLUSIEURS PROBLÈMES (deltaS et c)
void Solver::CalcRadii(int elem1, std::vector<double> u, std::vector<double> v){
  double Sx = 0;
  double Sy = 0;
  double c = 1; // À compléter

  for (int iFace = 0; iFace < mesh_sol.nNode[elem1]; iFace++){
    Sx += metrics_sol.normalVec[elem1][iFace][0];
    Sy += metrics_sol.normalVec[elem1][iFace][1];
  }
  double convecRadiiX = (std::abs(u[elem1])+c)*0.5*Sx;
  double convecRadiiY = (std::abs(v[elem1])+c)*0.5*Sy;
  convecRadiiTotal = convecRadiiX+convecRadiiY;
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

/*std::std::vector<double> Solver::RoeScheme(){

}*/
