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

    int mEsup, nPoin;
    //Number of dimensions of mesh
    int nDimn;

    // Nombre d'éléments dans le maillage
    int nElem;
    // Path and name of file containing the mesh
    std::string filePath;

//Constructor
public:
    Mesh();

    // la focntion
    vector<vector<int>> LinkedList(int nPoin, int nElem, int nNode, vector<vector<int>> iNpoel);

    // Function reading su2 file
    std::string ReadSu2(std::string filePath);
};
