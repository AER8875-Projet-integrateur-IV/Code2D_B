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
    void ComputeSolver();
    void UpdateBC();
    void ComputeDeltaT();
    void CalcRes();

    std::vector<double> dt;

    Mesh &mesh_sol;
    Input &input_sol;
    Metrics &metrics_sol;
};
