#include "Mesh.h"
#include "vector"
#include <fstream>
#include <iostream>
#include <sstream>

//Constructor
Mesh::Mesh(){};

// Function to read a su2 file
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
}

Mesh::~Mesh() {
  delete[] eSup1;
  delete[] eSup2;
}
