// =============================================================================
//                                  EULER EXPLICIT
//
// Class designed to calculate the Euler explicit temporal discretization
//
// =============================================================================
#pragma once
#include <vector>
#include "Mesh.h"

    // Functions
    std::vector<std::vector<double>> EulerExplicit(Mesh &mesh, std::vector<std::vector<double>> dWn, std::vector<double> dt, std::vector<std::vector<double>> res, std::vector<double> area);

    // Vectors
    Mesh _mesh;
    std::vector<std::vector<double>> _dWn;
    std::vector<double> _dt;
    std::vector<std::vector<double>> _res;
    std::vector<double> _area;
