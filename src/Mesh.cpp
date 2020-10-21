#include "Mesh.h"
#include "vector"
#include <fstream>
#include <iostream>
#include <sstream>

// =============================================================================
// CONSTRUCTOR
//==============================================================================
Mesh::Mesh(){};

// =============================================================================
// READING SU2 FILE
//==============================================================================
std::string Mesh::ReadSu2(std::string filePath){
  std::ifstream file (filePath); //Stocking su2 file inside a variable
  std::string name;
  /*std::vector<std::string> names;
  std::string input;*/

  name = "hello";

  if (file.is_open()) {

    // Define string that will contain one line from the file
    std::string line;

    // Read file line by line
    while (std::getline(file, line)) {

      std::getline(file, line);

      //Skip lines that only contain % (We do not need them)
      if (line == "%")
      {
        continue;
      }

      // Divide the line in different words
      std::stringstream ss(line);

      // Store one word at a time
      std::string word;
      ss >> word;

      //Skip lines that only contain % (We do not need them)

      // First condition if the line encountered concerns the number of dimensions
      if (word.compare("NDIME=") == 0)
      {
        ss >> word;
        nDimn = std::stoi(word);
        // Resize the vector coord to match the dimension of the mesh
        coord.resize(nDimn);

      }

      // Other condition if the line encountered is the for the number of elements
      else if (word.compare("NELEM=") == 0)
      {
        ss >> word;
        // Find the number of elements
        nElem = std::stoi(word);
        iNpoel.reserve(nElem);
        for (int i = 0; i<nElem; i++)
        {
          // Find the number of nodes for one element using the su2 convention for the number of nodes
          // 3 -> Line (2), 5 -> Triangle (3), 9 -> Quadrilateral (4), 10 -> Tetrahedral (4), 12 -> Hexahedral (6), 13 -> Prism, 14 ->, Pyramid ->
          // Each element will be assigned a different number of nodes. Useful for unstructured meshes
          std::getline(file, line);
          std::stringstream ss_2(line);

          std::string word_2;
          ss_2 >> word_2;

          if (word_2.compare("3") == 0)
          {
            nNode.push_back(2);
          }
          else if (word_2.compare("5") == 0)
          {
            nNode.push_back(3);
          }
          else if (word_2.compare("9") == 0)
          {
            nNode.push_back(4);

          }
          else
          {
            std::cout << "[ERROR] : Nombre de nodes pas reconnu" << '\n';
            break;
          }

          // Store each node in the right line and in the right order in the iNpoel vector
          ss_2 >> word_2;

          iNpoel.push_back({});

          for (int j = 0; j<nNode[i]; j++)
          {
            iNpoel[i].push_back(std::stoi(word_2));
            ss_2 >> word_2;

          }
        }
      }

      else if (word.compare("NPOIN=") == 0)
      {
        ss >> word;
        // Number of points inside the mesh
        nPoin = std::stoi(word);

        // Loop to store each point's coordinates inside the coord vector
        for (int i = 0; i < nPoin; i++)
        {
          std::getline(file, line);
          std::stringstream ss_2(line);

          for (int j = 0; j<nDimn; j++)
          {
            std::string word_2;
            ss_2 >> word_2;
            coord[j].push_back(std::stod(word_2));
          }
        }
      }
      // The next few conditions concern the boundary condition of our mesh
      // Determine the number of boundary conditions inside our mesh
      else if (word.compare("NMARK=") == 0)
      {
        ss >> word;
        nMark = std::stoi(word);
        bCond.resize(nMark);

        // Create a loop to extract all the info on the boundary conditions
        for (int i = 0; i<nMark; i++)
        {
          std::getline(file, line);
          std::stringstream ss_2(line);

          std::string word_2;
          ss_2 >> word_2;

          // Make sure that the next line is the marker_tag
          if (word_2.compare("MARKER_TAG=") == 0)
          {
            std::getline(file, line);
            std::stringstream ss_3(line);
            std::string word_3;
            ss_3 >> word_3;

            // Find the number of elements per boundary condition
            if (word_3.compare("MARKER_ELEMS=") == 0)
            {
              ss_3 >> word_3;
              nElemb.push_back(std::stoi(word_3));
            }
            else
            {
              std::cout << "[ERROR] : Nombre d'éléments pas reconnu" << std::endl;
              break;
            }

            bCond[i].resize(nElemb[i]);

            // Stock the boundary point numbers
            for (int j = 0; j<nElemb[i]; j++)
            {
              std::getline(file, line);
              std::stringstream ss_4(line);
              std::string word_4;

              ss_4 >> word_4;

              // Find the number of nodes per boundary element
              if (word_4.compare("3") == 0)
              {
                nNodeb.push_back(2);
              }
              else if (word_4.compare("5") == 0)
              {
                nNodeb.push_back(3);
              }
              else if (word_4.compare("9") == 0)
              {

                nNodeb.push_back(4);
              }
              else
              {
                std::cout << "[ERROR] : Nombre de nodes pas reconnu" << std::endl;
                break;
              }

              for (int k = 0; k<nNodeb[j]; k++)
              {
                ss_4 >> word_4;
                bCond[i][j].push_back(std::stoi(word_4));
              }
            }
          }
          // Show error if "MARKER_TAG=" is not the next input
          else
          {
            std::cout << "[ERROR]: Could not read file correctly. Missing 'MARKER_TAG='" << std::endl;
            break;
          }
        }


      }
    }
  }
  else {
    // show message:
    std::cout << "Error opening file";
  }
  return name;
}

// =============================================================================
// NODE TO ELEMENTS CONNECTIVITY FROM THE ELEMENTS TO NODE CONNECTIVITY
//==============================================================================
void Mesh::LinkedList()
{

  //Initialisation du linked list
  eSup2 = new int[nPoin+1];
  for(int i=0; i<nPoin +1;i++){
    eSup2[i] = 0;
  }

  int size_esup1 = 0;
  for(size_t i=0; i<nNode.size(); i++){
    size_esup1 += nNode[i];
  }

  eSup1 = new int[size_esup1];
  for (int i = 0; i<size_esup1; i++){
    eSup1[i] = 0;
  }

  // First pass to count the number of elements connected to each point
  for (int iElem = 0; iElem < nElem; iElem++)
  {
    for (int iNode = 0; iNode < nNode[iElem]; iNode++)
    {
      int iPoil = iNpoel[iElem][iNode]+1;
      eSup2[iPoil] = eSup2[iPoil] + 1;
    }
  }

  // Reshuffling
  for (int iPoin = 1; iPoin < nPoin + 1; iPoin++)
  {
    eSup2[iPoin] = eSup2[iPoin] + eSup2[iPoin - 1];
  }

  for (int iElem = 0; iElem < nElem; iElem++)
  {
    for (int iNode = 0; iNode < nNode[iElem]; iNode++)
    {
      int iPoin = iNpoel[iElem][iNode];
      int iStor = eSup2[iPoin]+1;
      eSup2[iPoin] = iStor;
      eSup1[iStor-1] = iElem;
      //std::cout << eSup1[iStor-1] << '\n';
    }
  }

  for (int iPoin = nPoin; iPoin > 0; iPoin--)
  {
    eSup2[iPoin] = eSup2[iPoin - 1];
  }

  eSup2[0] = 0;

  // Verifying function result
  /*for (int i = 0; i<size_esup1; i++){
    std::cout << eSup1[i] << '\n';
  }

  std::cout << "==========================" << '\n';

  for (int i = 0; i<nPoin+1; i++){
    std::cout << eSup2[i] << '\n';
  }*/
}

// =============================================================================
// NODE SURROUNDING NODE CONNECTIVITY
//==============================================================================
void Mesh::NodeSurrNode(){
  // Arrays initialization
  int* lPoin;
  lPoin = new int[nPoin]();
  pSup2 = new int[nPoin+1]();
  pSup2[0] = 0;

  // Initialize variables
  int iStor = 0;
  int iElem;
  int jPoin;

  for (int iPoin = 0; iPoin<nPoin; iPoin++){
      for (int iEsup = eSup2[iPoin]; iEsup<eSup2[iPoin+1]; iEsup++){
        iElem = eSup1[iEsup];
        for (int iNode = 0; iNode<nNode[iElem]; iNode++){
          jPoin = iNpoel[iElem][iNode];
          if ((jPoin != iPoin) && (lPoin[jPoin] != iPoin || iPoin == 0)){
            iStor +=1;
            pSup1.push_back(jPoin);
            lPoin[jPoin] = iPoin;
          }
        }
        pSup2[iPoin+1] = iStor;
      }
  }

  // Verifying function result
  /*for (int i = 0; i<pSup1.size(); i++){
    std::cout << pSup1[i] << '\n';
  }

  std::cout << "==========================" << '\n';

  for (int i = 0; i<nPoin+1; i++){
    std::cout << pSup2[i] << '\n';
  }*/
  delete[] lPoin;
}

// =============================================================================
// ELEMENT SURROUNDING ELEMENT CONNECTIVITY
//==============================================================================
void Mesh::ElemSurrElem(){

  // Define function variables
  int* lPoin;
  lPoin = new int[nPoin]();

  // Initialize nNofa
  int nNofa = 2; // Always two node per face in 2D

  // Initialize the nFael vector (contains number of faces for each element)
  nFael.reserve(nElem);
  for (int iElem = 0; iElem<nElem; iElem++){
    nFael.push_back(iNpoel[iElem].size());
  }

  std::cout << "hello" << '\n';
  // Initialize esuel vector
  eSuel.resize(nElem);
  for (int iElem = 0; iElem<nElem; iElem++){
    eSuel[iElem].resize(nFael[iElem]);
    for (int iNfael = 0; iNfael<nFael[iElem]; iNfael++){
      eSuel[iElem].push_back(0);
      std::cout << eSuel[iElem][iNfael] << '\n';
    }
  }

  /*for (int iElem = 0; iElem<nElem; iElem++){
    for (int iFael = 0; iFael<nFael; iFael++){
      nNofa = lNofa[iFael];
    }
  }*/

  // Verifying Vectors

  delete[] lPoin;
}

// =============================================================================
// DESTRUCTOR
//==============================================================================
Mesh::~Mesh() {
  delete[] eSup1;
  delete[] eSup2;
  //delete[] lPoin;
  delete[] pSup2;
}
