#include "Mesh.h"
#include <iostream>


int main(int argc, char const *argv[])
{

  std::cout << "Euler2D_B" << std::endl;

  Mesh File = Mesh();
  File.ReadSu2();

  return 0;
}
