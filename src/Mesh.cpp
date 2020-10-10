class Mesh {
private:
  /* data */

 public:
  int mEsup, nPoin;

  // Linked list construction
  int LinkedList(int nPoin, int nElem, int nNode, int iNpoel[][nElem-1])
  {
    int eSup2[nPoin+1] = {0};  //Initialisation du linked list

    for (int iElem = 0; iElem < nElem; iElem++){
      for (int iNode = 0; iNode < nNode; iNode++) {
        int iPoil = iNpoel[iNode][iElem]+1;
        eSup2[iPoil] = eSup2[iPoil]+1;
      }
    }

    for (int iPoin = 1; iPoin <= nPoin+1; iPoin++){
      eSup2[iPoin] = eSup2[iPoin] + eSup2[iPoin-1];
    }

    for (int iElem = 0; iElem < nElem; iElem++){
      for (int iNode = 0; iNode < nNode; iNode++){
        iPoin = iNpoel[iNode][iElem];
        iStor = eSup2[iPoin]+1;
        eSup2[iPoin] = iStor;
        eSup1[iStor] = iElem;
      }
    }

    for (iPoin = nPoin; iPoin > 0; iPoin--){
      eSup2[iPoin] = eSup2[iPoin-1];
    }

    eSup2[0] = 0;
  }



};
