#pragma once
#include "Mesh.h"
#include <cmath>

  class Metrics {

    public:
      // PUBLIC VARIABLES
      // Area vector
      std::vector<double> area;

      // Face area vector
      std::vector<std::vector<double>> faceArea;

      // Centroid vector
      std::vector<std::vector<double>> centroidVec;

      // Normal vector
      std::vector<std::vector<double>> normalVec;

      // Normal array
      //int** normal;

      // PUBLIC FUNCTION
      // Constructor
      Metrics();

      // Destructor
      ~Metrics();

      // Function to calculate Area of each element
      void CalcArea(const Mesh &Connec);

      // Function to calculate the normal vector to each face of each element#
      void CalcNormal(const Mesh &Connec);

      // Function to compute metrics calculations
      void SolveMetrics(const Mesh &Connec);

    private:

  };
