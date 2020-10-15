#include "Mesh.h"
#include <iostream>


int main(int argc, char const *argv[])
{

  std::cout << "Euler2D_B" << std::endl;
  //std::string filePath = "../tests/Known_Mesh/square_5x5.su2";

  Mesh File = Mesh();
  File.ReadSu2("../tests/Known_Mesh/square_5x5.su2");
  std::cout << "Euler2D_B" << std::endl;

  return 0;
}
