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
  centroidVec.resize(Connec.nElem);

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

      centroidVec[iElem].push_back(1/3*(coord1[0]+coord2[0]+coord3[0]));
      centroidVec[iElem].push_back(1/3*(coord1[1]+coord2[1]+coord3[1]));
      std::cout << centroidVec[iElem][0] << '\n';
      std::cout << centroidVec[iElem][1] << '\n';

      // Calculate the normal vector to each face

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
        1.0d/3.0d*(coord1[0]+coord2[0]+coord3[0]),
        1.0d/3.0d*(coord1[1]+coord2[1]+coord3[1])
      };
      std::vector<double> centroid134{
        1.0d/3.0d*(coord1[0]+coord3[0]+coord4[0]),
        1.0d/3.0d*(coord1[1]+coord3[1]+coord4[1])
      };

      centroidVec[iElem].push_back(area123*centroid123[0]+area134*centroid134[0]*area123+area134);
      centroidVec[iElem].push_back(area123*centroid123[1]+area134*centroid134[1]*area123+area134);
    }
    // Print error message if the element type is wrong
    else {
      std::cout << "[ERROR] : Element is not a triangle or a quadrilateral. Cannot treat element." << std::endl;
    }
  }
}

// =============================================================================
// CALCULATE THE NORMAL VECTOR OF EACH FACE
//==============================================================================
void Metrics::CalcNormal(const Mesh &Connec){

  // Resize the normal vector to match the number of elements
  normalVec.resize(Connec.nElem);

  for (int iElem = 0; iElem<Connec.nElem; iElem++){
    // Find the number of points inside the element
    int nbPoint = Connec.iNpoel[iElem].size();

    // Resize the next vector in the normal array
    normalVec[iElem].resize(nbPoint); // True because in 2D number of faces = number of points

    // Store in a vector the nodes associated with an element
    // Store for a second time the first point at the end of the vector to
    // calculate the last normal vector
    std::vector<int> numPt = Connec.iNpoel[iElem];
    numPt.push_back(Connec.iNpoel[iElem][0]);

    // Loop over the number of points to calculate the normals
    for (int i = 0; i<nbPoint; i++){
      std::vector<double> coord1 = Connec.coord[numPt[i]];
      std::vector<double> coord2 = Connec.coord[numPt[i+1]];

      normalVec[iElem][i].push_back(coord2[1]-coord1[1]);
      normalVec[iElem][i].push_back(coord1[0]-coord2[0]);

      // Verify normal coordinates
      /*for (int j = 0; j<2; j++){
        std::cout << normalVec[iElem][i][j] << ' ';
      }
      std::cout << "\n" << '\n';
      std::cout << "===========" << '\n';*/
    }
  }
}

// =============================================================================
// DESTRUCTOR
//==============================================================================
Metrics::~Metrics(){
  //delete[] normal;
}
