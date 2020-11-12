// =============================================================================
//                                  RESULTS
//
// Class designed to store the user's inputs
//
// =============================================================================
#pragma once
#include <iostream>
#include <string>
#include "Mesh.h"

class Input{
  public:

    // Constructor
    Input(Mesh &);

    // Variables
    double errMax;
    int nbIterMax;
    double gammaGas;
    double gasConstant;
    double mach;
    double cfl;
    double rho;

    // Functions
    void ComputeInput(std::string trigger);

    void HardCoded();

};
