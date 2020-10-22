#include "Metrics.h"
#include <iostream>

// =============================================================================
// CONSTRUCTOR
//==============================================================================
Metrics::Metrics(){};

// Function used to define the area of each element
void Metrics::CalcArea(const Mesh &Connec){

  // Initialize Area array
  area = new int[Connec.nElem]{};

  // Initialize normal array
  int num_rows = Connec.nElem;
  int num_cols = Connec.nDimn;
  //normal = new int[num_rows*num_cols]{};

  // Initialize b coefficient (assume its value is 1)
  int b = 1;

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

      area[iElem] = b/2*((coord1[0]-coord2[0])*(coord1[1]+coord2[1])
                    +(coord2[0]-coord3[0])*(coord2[1]+coord3[1])
                    +(coord3[0]-coord1[0])*(coord3[1]+coord1[1]));
    }
    // Verify if the element is a quadrelateral
    else if (Connec.iNpoel.size() == 4) {

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
      area[iElem] = b/2*((coord1[0]-coord3[0])*(coord2[1]-coord4[1])
                    +(coord4[0]-coord2[0])*(coord1[1]-coord3[1]));

      // Store each calculated normal in array
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
  delete[] area;
  delete[] normal;
}
