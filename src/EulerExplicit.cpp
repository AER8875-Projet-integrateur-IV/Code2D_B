#include "EulerExplicit.h"

// Constructor
EulerExplicit::EulerExplicit(Mesh &mesh, std::vector<vector<double>> dWn, std::vector<double> dt, std::vector<vector<double>> res, std::vector<double> area){
  _mesh = mesh;
  _dWn = dWn;
  _dt = dt;
  _res = res;
  _area = area;
}

void EulerExplicit::CalcDiscret(){
  for (int iElem = 0; iElem<_mesh.nElem; iElem++){
    _dWn[iElem][0] = - _dt[iElem]/_area[iElem]*_res[iElem][0];
    _dWn[iElem][1] = - _dt[iElem]/_area[iElem]*_res[iElem][1];
    _dWn[iElem][2] = - _dt[iElem]/_area[iElem]*_res[iElem][2];
    _dWn[iElem][3] = - _dt[iElem]/_area[iElem]*_res[iElem][3];
  }
}

EulerExplicit::~EulerExplicit(){}
