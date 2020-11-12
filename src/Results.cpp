#include "Results.h"

Results::Results(Mesh &mesh, Input &inputVals){

  // Resize each solution vector to match the number of elements in the mesh
  rho.resize(mesh.nElem);
  H.resize(mesh.nElem);
  u.resize(mesh.nElem);
  v.resize(mesh.nElem);
  p.resize(mesh.nElem);

  // Initialize each vector with the input values
  std::fill(rho.begin(), rho.end(), inputVals.rho);


}
