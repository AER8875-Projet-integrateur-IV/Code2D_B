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
  // Initialize residuals vector
  res.resize(mesh_sol.nElem);
  for (int i = 0; i < mesh_sol.nElem; i++){
    res[i].resize(4);
    for (int j = 0; j < 4; j++){
      res[i][j] = 1;
    }
  }
  int nb_it = 0;

  Results Simulation = Results(mesh_sol, input_sol);
  //res.resize(mesh_sol.nElem);
  conservativeVars.resize(mesh_sol.nElem);
  for (int iElem = 0; iElem < mesh_sol.nElem; iElem++){
    for (int j = 0; j < 4; j++){
      conservativeVars[iElem].push_back(0);
    }
  }

  // Identify what are the internal faces
  Solver::SortFaces();

  // Iteration process until convergence
  while (/*res[0] > input_sol.errMax &&*/ nb_it < 1000){
    // Reset the residuals for every element
    Solver::ResReset();

    Solver::ComputeDeltaT(Simulation.u, Simulation.v);
    nb_it += 1;
    // Looping over the internal faces
    for (int iFace = 0; iFace <internFace.size(); iFace++){
      int currFace = internFace[iFace];

      // Rearranging normal vector if necessary
      Solver::NormalVecIntern(currFace);
      Solver::CalcRes(currFace, Simulation);
    }

    // Looping ovr the boundary faces
    for (int iFace = 0; iFace <boundFace.size(); iFace++){
      int currFace = internFace[iFace];

      // Rearranging normal vector if necessary
      Solver::NormalVecBC(currFace);
      Solver::CalcRes(currFace, Simulation);
    }

    // Looping over the elements to update deltaW
    // Initialize the deltaW vector
    deltaW.resize(mesh_sol.nElem);
    for (int iElem = 0; iElem < mesh_sol.nElem; iElem++){
      for (int j = 0; j < 4; j++){
        deltaW[iElem].push_back(0);
      }
    }
    for (int iElem = 0; iElem<mesh_sol.nElem; iElem++){
      Solver::EulerExplicit(iElem);
      conservativeVars[iElem][0] += deltaW[iElem][0];
      conservativeVars[iElem][1] += deltaW[iElem][1];
      conservativeVars[iElem][2] += deltaW[iElem][2];
      conservativeVars[iElem][3] += deltaW[iElem][3];
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

  // Identify the faces surrounding the face
  int elem1 = mesh_sol.eSufa[iFace][0];
  int elem2 = mesh_sol.eSufa[iFace][1];

  int faces = mesh_sol.iNpoel[elem1].size();

  double area = metrics_sol.faceArea[iFace];
  RoeScheme Fc = RoeScheme(iFace, metrics_sol, simulation, mesh_sol);
  Fc.ComputeFluxes();
  resRho = Fc.Fluxes[0]*area;
  resRhoU = Fc.Fluxes[1]*area;
  resRhoV = Fc.Fluxes[2]*area;
  resRhoH = Fc.Fluxes[3]*area;

  // Adding residual to both sides of the face
  res[elem1][0] += resRho;
  res[elem1][1] += resRhoU;
  res[elem1][2] += resRhoV;
  res[elem1][3] += resRhoH;

  res[elem2][0] += resRho;
  res[elem2][1] += resRhoU;
  res[elem2][2] += resRhoV;
  res[elem2][3] += resRhoH;
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

void Solver::EulerExplicit(int iElem){
  double area = metrics_sol.area[iElem];
  deltaW[iElem][0] = - dt[iElem]/area*res[iElem][0];  // calcul de rho
  deltaW[iElem][1] = - dt[iElem]/area*res[iElem][1];  // rhoU
  deltaW[iElem][2] = - dt[iElem]/area*res[iElem][2];  // rhoV
  deltaW[iElem][3] = - dt[iElem]/area*res[iElem][3];  // rhoEiElem
}

void Solver::ResReset(){
  for (int i = 0; i < res.size(); i++){
    res[i].resize(0);
    for (int j = 0; j < res[i].size(); j++){
      res[i][j] = 0;
    }
  }
}

void Solver::NormalVecIntern(int &iFace){

  // Extract the elements on both sides of the face
  int elem1 = mesh_sol.eSufa[iFace][0];
  int elem2 = mesh_sol.eSufa[iFace][1];

  // Extract the coordinates of both centroid
  double x1 = metrics_sol.centroidVec[elem1][0];
  double y1 = metrics_sol.centroidVec[elem1][1];
  double x2 = metrics_sol.centroidVec[elem2][0];
  double y2 = metrics_sol.centroidVec[elem2][1];
  double x = x2-x1;
  double y = y2-y1;

  double scalarProd = x*metrics_sol.normalVec[iFace][0]+y*metrics_sol.normalVec[iFace][1];

  // Flip side if necessary
  if (scalarProd < 0){
    metrics_sol.normalVec[iFace][0] *= -1;
    metrics_sol.normalVec[iFace][1] *= -1;
  }
}

void Solver::NormalVecBC(int &iFace){
  int elem1 = mesh_sol.eSufa[iFace][0];

  // Extract the coordinates of both centroid
  double x1 = metrics_sol.centroidVec[elem1][0];
  double y1 = metrics_sol.centroidVec[elem1][1];

  int node = mesh_sol.iNpoed[iFace][0];

  double coordNodeX = metrics_sol.centroidVec[elem1][0];
  double coordNodeY = metrics_sol.centroidVec[elem1][1];

  double x = coordNodeX - x1;
  double y = coordNodeY - y1;

  double scalarProd = x*metrics_sol.normalVec[iFace][0]+y*metrics_sol.normalVec[iFace][1];

  // Flip side if necessary
  if (scalarProd < 0){
    metrics_sol.normalVec[iFace][0] *= -1;
    metrics_sol.normalVec[iFace][1] *= -1;
  }
}

void Solver::SortFaces(){
  internFace = {};
  boundFace = {};
  for(int iFace = 0; iFace < mesh_sol.nbFace; iFace++){
    if(mesh_sol.eSufa[iFace].size() == 2){
      internFace.push_back(iFace);
    }
    else{
      boundFace.push_back(iFace);
    }
  }
}

/*std::std::vector<double> Solver::RoeScheme(){

}*/
