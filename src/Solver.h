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
#include "RoeScheme.h"
//#include "EulerExplicit.h"
#include <iostream>
#include <cmath>

class Solver{
public:
    Solver(Mesh &, Input &, Metrics &);
    void ComputeSolver(); // Contains the whole process of the solver and runs every function
    void UpdateBC();  // Update every boundary condition accordignly
    std::vector<double> ComputeDeltaT(std::vector<double> u, std::vector<double> v); // Compute local time step
    void CalcRes(int faceI, Results &); // Calculate the residual
    void CalcRadii(int elem1, std::vector<double> u, std::vector<double> v); // Calculate the radii for the local time step
    void EulerExplicit(int iElem); // Euler Explicit Scheme
    void ResReset(); // Reset the residuals vector
    void NormalVecIntern(int &); // Flip internal normal vector if necessary
    void NormalVecBC(int &);  // Flip boundary normal vector if necessary
    void SortFaces(); // Sort the faces to see if they are on the boundary or not
    void RMS(Results &);

    std::vector<double> dt;
    std::vector<std::vector<double>> res;
    std::vector<std::vector<double>> conservativeVars;
    std::vector<int> internFace;
    std::vector<int> boundFace;
    std::vector<std::vector<double>> deltaW;
    std::vector<double> rmsRho;
    std::vector<double> rmsU;
    std::vector<double> rmsV;
    std::vector<double> rmsH;

    Mesh &mesh_sol;
    Input &input_sol;
    Metrics &metrics_sol;
    double convecRadiiTotal;

    // Objects
};
