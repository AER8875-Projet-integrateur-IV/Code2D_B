#include "Metrics.h"
#include <iostream>
#include <limits>

// =============================================================================
// CONSTRUCTOR
//==============================================================================
Metrics::Metrics(){};

// Function used to define the area and the centroid of each element
void Metrics::CalcArea(const Mesh &Connec){

  // Resize centroid vector to match the number of elements
  centroid.resize(Connec.nElem);

  // Initialize normal array
  int num_rows = Connec.nElem;
  int num_cols = Connec.nDimn;
  //normal = new int[num_rows*num_cols]{};

  // Initialize b coefficient (assume its value is 1)
  double b = 1;

  // Loop over the elements of the Mesh object
  for (int iElem = 0; iElem<Connec.nElem; iElem++){

    // Verify if the element is a triangle
    if (Connec.iNpoel[iElem].size() == 3){

      // Find what nodes compose this element
      int node1 = Connec.iNpoel[iElem][0];
      int node2 = Connec.iNpoel[iElem][1];
      int node3 = Connec.iNpoel[iElem][2];

      // Find each node's coordinates
      std::vector<double> coord1 = Connec.coord[node1];
      std::vector<double> coord2 = Connec.coord[node2];
      std::vector<double> coord3 = Connec.coord[node3];

      area.push_back(std::abs(b/2*((coord1[0]-coord2[0])*(coord1[1]+coord2[1])
                    +(coord2[0]-coord3[0])*(coord2[1]+coord3[1])
                    +(coord3[0]-coord1[0])*(coord3[1]+coord1[1]))));

      centroid[iElem].push_back(1/3*(coord1[0]+coord2[0]+coord3[0]));
      centroid[iElem].push_back(1/3*(coord1[1]+coord2[1]+coord3[1]));
      std::cout << centroid[iElem][0] << '\n';
      std::cout << centroid[iElem][1] << '\n';
    }
    // Verify if the element is a quadrelateral
    else if (Connec.iNpoel[iElem].size() == 4) {

      // Find what nodes compose this element
      int node1 = Connec.iNpoel[iElem][0];
      int node2 = Connec.iNpoel[iElem][1];
      int node3 = Connec.iNpoel[iElem][2];
      int node4 = Connec.iNpoel[iElem][3];

      // Find each node's coordinates
      std::vector<double> coord1 = Connec.coord[node1];
      std::vector<double> coord2 = Connec.coord[node2];
      std::vector<double> coord3 = Connec.coord[node3];
      std::vector<double> coord4 = Connec.coord[node4];

      // Store each calculated area in array
      area.push_back(std::abs(b/2*((coord1[0]-coord3[0])*(coord2[1]-coord4[1])
                    +(coord4[0]-coord2[0])*(coord1[1]-coord3[1]))));

      // Define the two triangles from the decomposition of the quadrilateral element
      double area123 = std::abs(b/2*((coord1[0]-coord2[0])*(coord1[1]+coord2[1])
                    +(coord2[0]-coord3[0])*(coord2[1]+coord3[1])
                    +(coord3[0]-coord1[0])*(coord3[1]+coord1[1])));
      double area134 = std::abs(b/2*((coord1[0]-coord3[0])*(coord1[1]+coord3[1])
                +(coord3[0]-coord4[0])*(coord3[1]+coord4[1])
                +(coord4[0]-coord1[0])*(coord4[1]+coord1[1])));

      // Define the centroid of each sub-triangle
      std::vector<double> centroid123{
        1/3*(coord1[0]+coord2[0]+coord3[0]),
        1/3*(coord1[1]+coord2[1]+coord3[1])
      };
      std::vector<double> centroid134{
        1/3*(coord1[0]+coord3[0]+coord4[0]),
        1/3*(coord1[1]+coord3[1]+coord4[1])
      };

      centroid[iElem].push_back(area123*centroid123[0]+area134*centroid134[0]*area123+area134);
      centroid[iElem].push_back(area123*centroid123[1]+area134*centroid134[1]*area123+area134);

      //std::cout << std::to_string(centroid123[0]) << '\n';
      //std::cout << std::to_string(centroid123[1]) << '\n';
    }
    // Print error message if the element type is wrong
    else {
      std::cout << "[ERROR] : Element is not a triangle or a quadrilateral. Cannot treat element." << std::endl;
    }
  }
}
// =============================================================================
// DESTRUCTOR
//==============================================================================
Metrics::~Metrics(){
  //delete[] normal;
}
