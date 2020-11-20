#include "EulerExplicit.h"

// Constructor
std::vector<std::vector<double>> EulerExplicit(Mesh &mesh, std::vector<vector<double>> dWn, std::vector<double> dt, std::vector<vector<double>> res, std::vector<double> area){
  _mesh = mesh;
  _dWn = dWn;
  _dt = dt;
  _res = res;
  _area = area;

  for (int iElem = 0; iElem<_mesh.nElem; iElem++){
    _dWn[iElem][0] = - _dt[iElem]/_area[iElem]*_res[iElem][0];  // calcul de rho
    _dWn[iElem][1] = - _dt[iElem]/_area[iElem]*_res[iElem][1];  // rhoU
    _dWn[iElem][2] = - _dt[iElem]/_area[iElem]*_res[iElem][2];  // rhoV
    _dWn[iElem][3] = - _dt[iElem]/_area[iElem]*_res[iElem][3];  // rhoE
  }

  return _dWn;
}
