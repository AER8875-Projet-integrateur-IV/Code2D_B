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
  std::vector<double> res = {1,1,1,1};
  int nb_it = 0;

  Results Simulation = Results(mesh_sol, input_sol);
  res.resize(mesh_sol.nElem);
  conservativeVars.resize(mesh_sol.nElem);

  // Iteration process until convergence
  while (/*res[0] > input_sol.errMax &&*/ nb_it < input_sol.nbIterMax){

    // Reset the residuals for every element
    Solver::ResReset(res);

    Solver::ComputeDeltaT(Simulation.u, Simulation.v);
    nb_it += 1;
    for (int iFace = 0; iFace <mesh_sol.nbFace; iFace++){
      //Solver::CalcRes(iFace, Simulation);
      /*std::vector<std::vector<double>> deltaW = EulerExplicit(mesh_sol, dt[iElem], res[iElem], metrics_sol.area[iElem]);
      conservativeVars[0] += deltaW[0];
      conservativeVars[1] += deltaW[1];
      conservativeVars[2] += deltaW[2];
      conservativeVars[3] += deltaW[3];*/
    }
  }
}

// Calculate deltaT
std::vector<double> Solver::ComputeDeltaT(std::vector<double> u, std::vector<double> v){
  for (int iElem = 0; iElem<mesh_sol.nElem; iElem++){
    CalcRadii(iElem, u, v);
    dt[iElem] = input_sol.cfl*metrics_sol.area[iElem]/1;
    // Missing spectral radii
  }
  return dt;
}

// Calculate residual (valid for 1 element)
void Solver::CalcRes(int iFace, Results &simulation){
  double resRho = 0;
  double resRhoU = 0;
  double resRhoV = 0;
  double resRhoH = 0;

  int elem1 = 0;
  int faces = mesh_sol.iNpoel[elem1].size();
  res[elem1].resize(faces);

  for (int iFace = 0; iFace<faces; iFace++){
    double area = metrics_sol.faceArea[elem1][iFace];
    RoeScheme Fc = RoeScheme(iFace, metrics_sol, simulation, mesh_sol);

    resRho += Fc.Fluxes[0]*area;
    resRhoU += Fc.Fluxes[1]*area;
    resRhoV += Fc.Fluxes[2]*area;
    resRhoH += Fc.Fluxes[3]*area;
  }
  res[elem1].push_back(resRho);
  res[elem1].push_back(resRhoU);
  res[elem1].push_back(resRhoV);
  res[elem1].push_back(resRhoH);
}

// Calculate the spectral radii ()  // -> COMPLÉTÉ MAIS AVEC PLUSIEURS PROBLÈMES (deltaS et c)
void Solver::CalcRadii(int elem1, std::vector<double> u, std::vector<double> v){
  double Sx = 0;
  double Sy = 0;
  double c = 1; // À compléter

  // Initialize a vector that will contain all the faces surrounding one element
  std::vector<int> faceList;

  // Find the faces that surround elem1
  for (int iFace = 0; iFace < mesh_sol.nbFace; iFace++){
    faceList = {};
    for (int iElem = 0; iElem < mesh_sol.eSufa[iFace].size(); iElem++){
      if (elem1 == iElem){
        faceList.push_back(iFace);
      }
    }
  }

  // Loop over the element of faceList to calculate Sx and Sy
  for (int iFace = 0; iFace < faceList.size(); iFace++){
    Sx += metrics_sol.normalVec[iFace][0];
    Sy += metrics_sol.normalVec[iFace][1];
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

std::vector<double> Solver::EulerExplicit(Mesh &mesh, double dt, std::vector<double> res, double area){
  std::vector<double> _dWn;
  _dWn.resize(4);
  _dWn[0] = - dt/area*res[0];  // calcul de rho
  _dWn[1] = - dt/area*res[1];  // rhoU
  _dWn[2] = - dt/area*res[2];  // rhoV
  _dWn[3] = - dt/area*res[3];  // rhoEiElem
  return _dWn;
}

void Solver::ResReset(std::vector<double> &res){
  for (int i = 0; i < res.size(); i++){
    res[i] = 0;
  }
}

/*std::std::vector<double> Solver::RoeScheme(){

}*/
