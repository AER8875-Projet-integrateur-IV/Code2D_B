#include "Input.h"

// Constructor
Input::Input(Mesh &mesh){}

// Function to run every other function
void Input::ComputeInput(std::string trigger){
  std::cout << "----- Starting initialization of inputs... ----" << '\n';
  if (trigger == "Hardcoded"){
    Input::HardCoded();
  }
  //Input::Calculations();
  std::cout << "----- Initialization of inputs completed ------" << '\n';
  std::cout << nbIterMax << '\n';
}

void Input::HardCoded(){
  errMax = 0.001;
  nbIterMax = 1000;
  gammaGas = 1.4;  // Assuming it's in the air
  gasConstant = 8.3145; // J/mol*K
  mach = 1.2;
  cfl = 0.7;
  rho = 1;
  tempInf = 1;
  aoa = 0;
  p = 1;
}

/*void Input::Calculations(){
  u = mach*sqrt(gammaGas*gasConstant*temp)*std::cos(3.14159265358979/180*aoa);
  v = mach*sqrt(gammaGas*gasConstant*temp)*std::sin(3.14159265358979/180*aoa);
  E = p/((gammaGas-1)*rho)+(u*u+v*v)/2;
  H = E+p/rho;
}*/
