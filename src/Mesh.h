#include <vector>
using std::vector;

class Mesh
{
public:
    vector<vector<int>> iNpoel;
    int mEsup, nPoin, nNode;
    // la focntion
    vector<vector<int>> LinkedList(int nPoin, int nElem, int nNode, vector<vector<int>> iNpoel);
};