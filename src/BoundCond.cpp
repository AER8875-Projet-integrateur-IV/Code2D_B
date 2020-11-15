/*#include "BoundCond.h"

// Wall condition
std::vector<double> WallCond(int elem1, int face1, Mesh &mesh, Results &SimResults, Metrics &metrics){
  // Set the density and pressure values equal
  double p = SimResults.p[elem1];
  double rho = SimResults.rho[elem1];

  // Condition on the speed
  double v2 = SimResults.u[elem1]*metrics.normalVec[elem1][face1][0]+SimResults.v[elem1]*metrics.normalVec[elem1][face1][1];
  double u = SimResults.u[elem1]-2*v2*metrics.normalVec[elem1][face1][0];
  double v = SimResults.v[elem1]-2*v2*metrics.normalVec[elem1][face1][1];
  std::vector<double> bound = {p, rho, u, v};
  return bound;
}

// FUNCTIONS FOR EVERY FARFIELD CONDITIONS
// Supersonic inflow
std::vector<double> SuperInflow(Results &SimResults){
  double p = SimResults.pInf;
  double rho = SimResults.rhoInf;
  double u = SimResults.uInf;
  double v = SimResults.vInf;

  std::vector<double> bound = {p, rho, u, v};
  return bound;
}

// Supersonic outflow
std::vector<double> SuperOutflow(Results &SimResults, int elem1){
  double p = SimResults.p[elem1];
  double rho = SimResults.rho[elem1];
  double u = SimResults.u[elem1];
  double v = SimResults.v[elem1];

  std::vector<double> bound = {p, rho, u, v};
  return bound;
}

// Subsonic inflow
std::vector<double> SubInflow(Results &SimResults, int elem1, int face1, double c0, Metrics &metrics){
  double p = 0.5*(SimResults.pInf+SimResults.p[elem1]-SimResults.rho[elem1]*c0*(metrics.normalVec[elem1][face1][0]*(SimResults.uInf-SimResults.u[elem1])+metrics.normalVec[elem1][face1][1]*(SimResults.vInf-SimResults.v[elem1])));
  double rho = SimResults.rhoInf+(p-SimResults.pInf)/(c0*c0);
  double u = SimResults.uInf-metrics.normalVec[elem1][face1][0]*(SimResults.pInf-p)/(SimResults.rho[elem1]*c0);
  double v = SimResults.vInf-metrics.normalVec[elem1][face1][1]*(SimResults.pInf-p)/(SimResults.rho[elem1]*c0);

  std::vector<double> bound = {p, rho, u, v};
  return bound;
}

// Subsonic outflow
std::vector<double> SubOutflow(Results &SimResults, int elem1, int face1, double c0, Metrics &metrics){
  double p = SimResults.pInf;
  double rho = SimResults.rho[elem1]+(p-SimResults.p[elem1])/(c0*c0);
  double u = SimResults.u[elem1]+metrics.normalVec[elem1][face1][0]*(SimResults.p[elem1]-p)/(SimResults.rho[elem1]*c0);
  double v = SimResults.u[elem1]+metrics.normalVec[elem1][face1][1]*(SimResults.p[elem1]-p)/(SimResults.rho[elem1]*c0);

  std::vector<double> bound = {p, rho, u, v};
  return bound;
}*/
