#pragma once
#include <vector>
#include <string>

using std::vector;
class Mesh
      {
      public:
          //
          vector<vector<int>> iNpoel;

          // Number of nodes per elements
          vector<int> nNode;

          // Number of nodes per boundary elements
          vector<int> nNodeb;

          // Number of elements per boundary condition
          vector<int> nElemb;

          // Point coordinates inside the mesh
          vector<vector<double>> coord;

          int mEsup, nPoin;
          //Number of dimensions of mesh
          int nDimn;

          // Nombre d'éléments dans le maillage
          int nElem;
          // Path and name of file containing the mesh
          std::string filePath;

          // Number of boundary conditions
          int nMark;

          // Number of faces in the mesh
          int nFace;

          int nbFace;

          // Vector containg the boundary condition information
          vector<vector<vector<int>>> bCond;

          // Vectors used for the linked list
          int* eSup2;
          int* eSup1;
          int* fSup2;
          int* fSup1;

          int* lFace;

          // Arrays used for the node surrouning node connectivity
          int* pSup2;
          vector<int> pSup1;
          int nEdge;

          // Arrays used for the node surrounding faces connectivity
          vector<vector<int>> iNpoed;
          int* iNpoel2;

          // Elements used for the face surrounding element connectivity
          vector<vector<int>> iNedel;

          // Variables used for the elements surrounding elements connectivity
          vector<vector<int>> eSuel;
          vector<int> nFael;
          vector<vector<int>> lNofa;
          int nNofa;
          vector<vector<vector<int>>> lPofa;
          vector<vector<int>> bFace;
          vector<vector<int>> bounType;
          //vector<vector<vector<int>>> lPofa;

          // Variables used for the element surrounding faces connectivity
          vector<vector<int>> eSufa;

      //Constructor
      public:
          Mesh();
          ~Mesh();

          // la focntion
          void LinkedList();

          // Function reading su2 file
          std::string ReadSu2(std::string filePath);

          // Node surrounding node connectivity
          void NodeSurrNode();

          // Element surrounding element connectivity
          void ElemSurrElem();

          // Node surrounding faces connectivity
          void NodeSurrFaces();

          // External faces connectivity
          void ExternalFaces();

          // Face surrounding element connectivity
          void FaceSurrElem();

          // Element surrounding faces connectivity
          void ElemSurrFace();

          // Function to call other functions
          void SolveMesh(std::string filePath);
        };
