// =============================================================================
//                                  bOUNDARY CONDITIONS
//
// Script detailing the boundary conditions of the simulation
//
// =============================================================================
#pragma once
#include "Mesh.h"
#include "Metrics.h"
#include "Results.h"

std::vector<double> WallCond(int &elem1, int &face1, Mesh &, Results &, Metrics &);
std::vector<double> SuperInflow(Results &);
std::vector<double> SuperOutflow(Results &, int elem1);
std::vector<double> SubInflow(Results &, int elem1, int face1, double c0, Metrics &);
std::vector<double> SubOutflow(Results &, int elem1, int face1, double c0, Metrics &);
