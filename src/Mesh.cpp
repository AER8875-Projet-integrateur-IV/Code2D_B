#include "Mesh.h"
#include "vector"

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
