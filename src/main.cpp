#include "Mesh.h"
//#include "Metrics.h"
#include <iostream>


int main(int argc, char const *argv[])
{

  std::cout << "Euler2D_B" << std::endl;
  //std::string filePath = "../tests/Known_Mesh/square_5x5.su2";

  Mesh File = Mesh();
  File.ReadSu2("../tests/Known_Mesh/square_5x5.su2");
  File.LinkedList();
  File.NodeSurrNode();
  File.ElemSurrElem();
  //Metrics metrics = Metrics();
  //metrics.CalcArea(File);

  return 0;
}
