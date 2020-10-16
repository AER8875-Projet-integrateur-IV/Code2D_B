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

//Constructor
public:
    Mesh();

    // la focntion
    vector<vector<int>> LinkedList(int nPoin, int nElem, vector<int> nNode, vector<vector<int>> iNpoel);

    // Function reading su2 file
    std::string ReadSu2(std::string filePath);
};
