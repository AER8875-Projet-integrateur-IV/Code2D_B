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

    // Vector containg the boundary condition information
    vector<vector<vector<int>>> bCond;

    // Vectors used for the linked list
    int* eSup2;
    int* eSup1;

    // Arrays used for the node surrouning node connectivity
    int* pSup2;
    vector<int> pSup1;

    // Variables used for the elements surrounding elements connectivity
    vector<vector<int>> eSuel;
    vector<int> nFael;
    //vector<vector<vector<int>>> lPofa;

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
};
