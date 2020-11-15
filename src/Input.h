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
#include <cmath>

class Input{
  public:

    // Constructor
    Input(Mesh &mesh);

    // Functions
    void ComputeInput(std::string trigger);

    void HardCoded();

    void Calculations();

    // Variables
    double errMax;
    int nbIterMax;
    double gammaGas;
    double gasConstant;
    double mach;
    double cfl;
    double rho;
    double p;
    double tempInf;
    double u;
    double v;
    double H;
    double E;
    double aoa;

};
