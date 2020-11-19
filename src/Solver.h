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
#include <iostream>

class Solver{
public:
    Solver(Mesh &, Input &);
    void ComputeSolver();
    void UpdateBC();

    Mesh &mesh_sol;
    Input &input_sol;
};
