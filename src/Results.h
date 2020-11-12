// =============================================================================
//                                  RESULTS
//
// Class designed to initialize and store the solution of the simulation
//
// =============================================================================
#pragma once
#include "Mesh.h"
#include "Input.h"

class Results {
  public:

    //Constructor
    Results(Mesh &, Input &);

    // Vectors
    std::vector<double> u;
    std::vector<double> v;
    std::vector<double> rho;
    std::vector<double> H;
    std::vector<double> p;
};
