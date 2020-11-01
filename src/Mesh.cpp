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

        // Resize the coord vector to match the number of points inside the mesh
        coord.resize(nPoin);

        // Loop to store each point's coordinates inside the coord vector
        for (int i = 0; i < nPoin; i++)
        {
          std::getline(file, line);
          std::stringstream ss_2(line);

          for (int j = 0; j<nDimn; j++)
          {
            std::string word_2;
            ss_2 >> word_2;
            //std::cout << coord.size() << '\n';
            coord[i].push_back(std::stod(word_2));
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
  nNofa = 2; // Always two node per face in 2D
  int* lHelp;
  lHelp = new int[nNofa];

  // Initialize the nFael vector (contains number of faces for each element)
  nFael.reserve(nElem);
  for (int iElem = 0; iElem<nElem; iElem++){
    nFael.push_back(iNpoel[iElem].size());
  }

  // Initialize lNofa (contains the number of nodes per faces)
  lNofa.resize(nElem);
  for (int iElem = 0; iElem<nElem; iElem++){
    lNofa[iElem].reserve(nFael[iElem]);
    for (int iNfael = 0; iNfael<nFael[iElem]; iNfael++){
      lNofa[iElem][iNfael] = nNofa;
    }
  }

  // Initialize esuel vector
  eSuel.resize(nElem);
  for (int iElem = 0; iElem<nElem; iElem++){
    eSuel[iElem].reserve(nFael[iElem]);
    for (int iNfael = 0; iNfael<nFael[iElem]; iNfael++){
      eSuel[iElem][iNfael] = -1;
    }
  }

  // Initialize lPofa vector

  vector<vector<int>> lPofa4 = {{0, 1}, {1, 2}, {2, 3}, {3, 0}};
  vector<vector<int>> lPofa3 = {{0, 1}, {1, 2}, {2, 0}};

  /*lPofa.resize(nElem);
  for (int iElem = 0; iElem<nElem; iElem++){
    lPofa[iElem].resize(nFael[iElem]);
    for (int iNfael = 0; iNfael<nFael[iElem]; iNfael++){
      lPofa[iElem][iNfael].reserve(nNofa);
      for (int iNnofa = 0; iNnofa<nNofa; iNnofa++){
        lPofa[iElem][iNfael][iNnofa] = 0;
        std::cout <<  lPofa[iElem][iNfael][iNnofa] << '\n';
      }
    }
  }*/



  for (int iElem = 0; iElem<nElem; iElem++){
    for (int iFael = 0; iFael<nFael[iElem]; iFael++){
      nNofa = lNofa[iElem][iFael];

      // Reinitialize values of lHelp
      for (int iNnofa = 0; iNnofa<nNofa; iNnofa++){
        lHelp[iNnofa] = iNpoel[iElem][lPofa4[iFael][iNnofa]];
      }

      for (int iNnofa = 0; iNnofa<nNofa; iNnofa++){
        lPoin[lHelp[iNnofa]] = 1;
      }
      int iPoin = lHelp[0];

      for (int iStor = eSup2[iPoin]; iStor<eSup2[iPoin+1]; iStor++){
        int jElem = eSup1[iStor];
        if (jElem != iElem){
          for (int jFael = 0; jFael<nFael[iElem]; jFael++){
            int nNofj = lNofa[iElem][jFael];
            if (nNofj == nNofa){
              int iCoun = 0;
              for (int jNofa = 0; jNofa<nNofa; jNofa++){
                int jPoin = iNpoel[jElem][lPofa4[jFael][jNofa]];
                iCoun = iCoun + lPoin[jPoin];
              }
              if (iCoun == nNofa){
                eSuel[iElem][iFael] = jElem;
              }
            }
          }
        }
      }
      for (int iNnofa = 0; iNnofa<nNofa; iNnofa++){
        lPoin[lHelp[iNnofa]] = 0;
      }
    }
  }

  // Loop over the eSuel array to identify ghost cells
  int count = nElem;

  for (int iElem = 0; iElem<nElem; iElem++){
    for (int i = 0; i<nFael[iElem]; i++){
      if (eSuel[iElem][i] == -1){
        eSuel[iElem][i] = count;
        count += 1;
      }
    }
  }

  // Verifying Vectors
  /*for (int i = 0; i<nElem; i++){
    for (int j = 0; j < nFael[i]; j++){
      std::cout << eSuel[i][j] << '\n';
    }
    std::cout << "==================" << '\n';
  }*/

  delete[] lPoin;
}

// =============================================================================
// NODE SURROUNDING ELEMENT CONNECTIVITY
//==============================================================================

void Mesh::NodeSurrFaces(){
  // Arrays initialization
  int* lPoin;
  lPoin = new int[nPoin]();
  iNpoel2 = new int[nPoin+1]();
  iNpoel2[0] = 0;

  // Initialize variables
  int nEdge = 0;
  int iElem;
  int jPoin;

  for (int iPoin = 0; iPoin<nPoin; iPoin++){
      for (int iEsup = eSup2[iPoin]; iEsup<eSup2[iPoin+1]; iEsup++){
        iElem = eSup1[iEsup];
        for (int iNode = 0; iNode<nNode[iElem]; iNode++){
          jPoin = iNpoel[iElem][iNode];
          /*if (nNode[iElem] == 4){

          }*/
          if ((jPoin != iPoin) && (lPoin[jPoin] != iPoin || iPoin == 0)){
            nEdge +=1;
            iNpoed.push_back(jPoin);
            lPoin[jPoin] = iPoin;
          }
        }
        iNpoel2[iPoin+1] = nEdge;
      }
  }

  // Verifying function result
  /*for (int i = 0; i<iNpoed.size(); i++){
    std::cout << iNpoed[i] << '\n';
  }

  std::cout << "==========================" << '\n';

  for (int i = 0; i<nPoin+1; i++){
    std::cout << iNpoel2[i] << '\n';
  }*/
  delete[] lPoin;
}
// =============================================================================
// EXTERNAL FACES CONNECTIVITY
//==============================================================================

void Mesh::ExternalFaces(){
  // Variables initialization
  int* lPoin;
  lPoin = new int[nPoin]();

  vector<vector<int>> lPofa4 = {{0, 1}, {1, 2}, {2, 3}, {3, 0}};
  vector<vector<int>> lPofa3 = {{0, 1}, {1, 2}, {2, 0}};

  int nFace = 0;

  for (int inMark = 0; inMark<nMark; inMark++){
    for(int inElemb = 0; inElemb < nElemb[inMark]; inElemb++){
      lPoin[bCond[inMark][inElemb][0]] = 1;
    }
  }


  // lPoin verification
  /*for (int i = 0; i < nPoin;i++){
    std::cout << lPoin[i] << '\n';
  }*/

  for (int iElem = 0; iElem<nElem; iElem++){

    for (int iFael = 0; iFael<nFael[iElem]; iFael++){
      nNofa = lNofa[iElem][iFael];

      std::vector<int> lHelp;
      lHelp.push_back(iNpoel[iElem][lPofa4[iFael][0]]);
      lHelp.push_back(iNpoel[iElem][lPofa4[iFael][1]]);
      /*for (int iNnofa = 0; iNnofa<nNofa; iNnofa++){
        lHelp.push_back(iNpoel[iElem][lPofa4[iFael][iNnofa]]);
      }*/

      int iCoun = 0;

      for (int iNnofa = 0; iNnofa<nNofa; iNnofa++){
        iCoun = iCoun + lPoin[lHelp[iNnofa]];
      }

      if (iCoun == nNofa){
        nFace += 1;
        bFace.push_back(lHelp);
      }
    }
  }

  /*
  for (int i = 0; i<bFace.size(); i++){
    for (int j = 0; j < bFace[i].size(); j++){
      std::cout << bFace[i][j] << '\n';
    }
    std::cout << "=======" << '\n';
  }*/



// Step2 remove the doubly defined faces

// Build the list fsup1 fsup2

lFace = new int[nFace];
for (int i = 0; i<nFace; i++){
  lFace[i] = 1;
}

//Initialisation du linked list
fSup2 = new int[nPoin+1];
for (int i = 0; i<nPoin+1; i++){
  fSup2[i] = 0;
}

// First pass to count the number of faces connected to each point
for (int iFace = 0; iFace < nFace; iFace++){
  for (int iNode = 0; iNode < nNode[iFace]; iNode++){
    int iPoil = iNpoel[iFace][iNode]+1;
    fSup2[iPoil] = fSup2[iPoil]+1;
  }
}
// Reshuffling
for (int iPoin = 1; iPoin < nPoin+1; iPoin++){
  fSup2[iPoin] = fSup2[iPoin]+fSup2[iPoin-1];
}

// Initialize fSup1
int size_fsup1 = fSup2[nPoin];
fSup1 = new int[size_fsup1];
for (int i = 0; i < size_fsup1; i++){
  fSup1[i] = 0;
}

//std::cout << size_fsup1 << '\n';
for (int iFace = 0; iFace < nFace; iFace ++){
  for (int iNode = 0; iNode < nNode[iFace]; iNode++){
    int iPoin = iNpoel[iFace][iNode];
    int iStor = fSup2[iPoin]+1;
    fSup2[iPoin] = iStor;
    fSup1[iStor-1] = iFace;
  }
}

for (int iPoin = nPoin; iPoin > 0; iPoin--){
  fSup2[iPoin] = fSup2[iPoin-1];
}
fSup2[0] = 0;


/*
// Verify vectors
for (int i = 0; i < size_fsup1; i++){
  std::cout << fSup1[i] << '\n';
}
std::cout << "====" << '\n';
for (int i = 0; i<nPoin+1; i++){
  std::cout << fSup2[i] << '\n';
}*/


int nBoun = nMark;

for (int i = 0; i < bCond.size(); i++){
  for (int iboun = 0; iboun<bCond[i].size(); iboun++){
    int ipoin = bCond[i][iboun][1];
    for (int istor = fSup2[ipoin]; istor < fSup2[ipoin+1]-1; istor++){
      int iface = fSup1[istor];
      if (lFace[iface] != 0){
        for (int jstor = istor; jstor < fSup2[ipoin+1]; jstor++){
          int jface = fSup1[jstor];
          if (iface != jface){
            lFace[iface] = 0;
            lFace[jface] = 0;
          }
        }
      }
    }
  }
}
/*
// Verify lFace vector
for (int i = 0; i < nFace; i++){
  std::cout << lFace[i] << '\n';
}*/


  //-------------------------------------------------------------------------------------
  /*for (int iboun = 0; iboun<nBoun; iboun++){
    int ipoin = bconi[iboun];
    for int istor = fsup2[ipoin] +1; iStor<fSup2[iPoin+1]; iStor++){
      int iFace = fSup1[iStor];
      if (lface[iFace] != 0){
        for (int jstor = istor; jstor < fsup2[ipoin+_1]){
          int jFace = fsup1[jstor];
          if (iFace != jFace){
            if ipoin[iFace]==ipoin[jFace]{
              int lFace[iFace] = 0
              int lFace[jFace] = 0
            }
          }
        }
      }
    }
  }
}*/
}
// =============================================================================
// DESTRUCTOR
//==============================================================================
Mesh::~Mesh() {
  delete[] eSup1;
  delete[] eSup2;
  delete[] pSup2;
  delete[] fSup1;
  delete[] fSup2;
  delete[] lFace;
  delete[] iNpoel2;
}
