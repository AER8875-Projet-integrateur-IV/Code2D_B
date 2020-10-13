#include <vector>
#include <string>
using std::vector;

class Mesh
{
public:
    vector<vector<int>> iNpoel;
    int mEsup, nPoin, nNode;
    //Number of dimensions of mesh
    int nDimn;
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
