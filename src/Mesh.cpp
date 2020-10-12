#include "Mesh.h"
#include "vector"
#include <fstream>
#include <iostream>

std::string Mesh::ReadSu2(){
  std::ifstream file ("../tests/Known_Mesh/square_5x5.su2"); //Stocking su2 file inside a variable
  std::string name;
  std::vector<std::string> names;
  std::string input;

  if (file.is_open()) {
    // print file:
    char c = file.get();
    while (file.good()) {
      std::cout << c;
      c = file.get();
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
