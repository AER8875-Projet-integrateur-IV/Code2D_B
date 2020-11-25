// =============================================================================
//                                  SOLVER
//
// This class contains everything related to the proccess of resolution of the
// equations.
//
// =============================================================================
#pragma once
#include "Mesh.h"
#include "Input.h"
#include "Results.h"
#include "Metrics.h"
#include <iostream>

class Solver{
public:
    Solver(Mesh &, Input &, Metrics &);
    void ComputeSolver(); // Contains the whole process of the solver and runs every function
    void UpdateBC();  // Update every boundary condition accordignly
    void ComputeDeltaT(std::vector<double> u, std::vector<double> v); // Compute local time step
    void CalcRes(int elem1, std::vector<std::vector<double>> Fc); // Calculate the residual
    void CalcRadii(int elem1, std::vector<double> u, std::vector<double> v); // Calculate the radii for the local time step

    std::vector<double> dt;

    Mesh &mesh_sol;
    Input &input_sol;
    Metrics &metrics_sol;
    double convecRadiiTotal;

    // Objects
};
