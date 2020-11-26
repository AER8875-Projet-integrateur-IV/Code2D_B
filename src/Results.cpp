#include "Results.h"

Results::Results(Mesh &mesh, Input &inputVals){

  // Resize each solution vector to match the number of elements in the mesh
  rho.resize(mesh.nElem);
  H.resize(mesh.nElem);
  u.resize(mesh.nElem);
  v.resize(mesh.nElem);
  p.resize(mesh.nElem);
  V.resize(mesh.nElem);
  pInf = inputVals.p;
  uInf = inputVals.u;
  vInf = inputVals.v;
  rhoInf = inputVals.rho;
  HInf = inputVals.H;
  EInf = inputVals.E;
  gamma = inputVals.gammaGas;

  // Initialize each vector with the input values
  std::fill(rho.begin(), rho.end(), inputVals.rho);
  std::fill(H.begin(), H.end(), inputVals.H);
  std::fill(u.begin(), u.end(), inputVals.u);
  std::fill(v.begin(), v.end(), inputVals.v);
  std::fill(p.begin(), p.end(), inputVals.p);
  std::fill(V.begin(), V.end(), 0);
}
