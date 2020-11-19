// =============================================================================
//                                  MAIN
//
// This scripts represents the main code for the 2D solver.
//
// =============================================================================
#include "Mesh.h"
#include "Metrics.h"
#include "Writer.h"
#include "Input.h"
#include "Results.h"
#include "Solver.h"
#include <iostream>


int main(int argc, char const *argv[])
{

  std::cout << "Euler2D_B" << std::endl;
  //std::string filePath = "../tests/Known_Mesh/square_5x5.su2";

  Mesh mesh = Mesh();
  mesh.SolveMesh("../tests/Known_Mesh/square_5x5.su2");
  Metrics metrics = Metrics();
  metrics.SolveMetrics(mesh);

  Input inputs = Input(mesh);
  inputs.ComputeInput("Hardcoded");
  Solver solution = Solver(mesh, inputs, metrics);
  solution.ComputeSolver();

  //Writer VtuFile = Writer();

  return 0;
}
