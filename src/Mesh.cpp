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

      // Find the dimension of the mesh
      if (word.compare("NDIME=") == 0)
      {
        ss >> word;
        nDimn = std::stoi(word);
      }
      else if (word.compare("NELEM=") == 0)
      {
        ss >> word;
        // Find the number of elements
        nElem = std::stoi(word);

        for (int i = 0; i<nElem; i++)
        {
          // Find the number of nodes for one element using the su2 convention for the number of nodes
          // 3 -> Line (2), 5 -> Triangle (3), 9 -> Quadrilateral (4), 10 -> Tetrahedral (4), 12 -> Hexahedral (6), 13 -> Prism, 14 ->, Pyramid ->
          std::getline(file, line);
          std::stringstream ss_2(line);
          //ss_2 >> word;
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

vector<vector<int>> Mesh::LinkedList(int nPoin, int nElem, int nNode, vector<vector<int>> iNpoel)
{
  vector<int> eSup2;
  vector<int> eSup1; //Initialisation du linked list
  eSup2.reserve(nElem);
  eSup1.reserve(nElem);

  for (int iElem = 0; iElem < nElem; iElem++)
  {
    for (int iNode = 0; iNode < nNode; iNode++)
    {
      int iPoil = iNpoel[iNode][iElem] + 1;
      eSup2[iPoil] = eSup2[iPoil] + 1;
    }
  }

  for (int iPoin = 1; iPoin <= nPoin + 1; iPoin++)
  {
    eSup2[iPoin] = eSup2[iPoin] + eSup2[iPoin - 1];
  }

  for (int iElem = 0; iElem < nElem; iElem++)
  {
    for (int iNode = 0; iNode < nNode; iNode++)
    {
      int iPoin = iNpoel[iNode][iElem];
      int iStor = eSup2[iPoin] + 1;
      eSup2[iPoin] = iStor;
      eSup1[iStor] = iElem;
    }
  }

  for (int iPoin = nPoin; iPoin > 0; iPoin--)
  {
    eSup2[iPoin] = eSup2[iPoin - 1];
  }

  eSup2[0] = 0;
}
