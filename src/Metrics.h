#include "Mesh.h"



  class Metrics {

    public:
      // PUBLIC VARIABLES
      // Area array
      int* area;

      // Normal array
      int** normal;

      // PUBLIC FUNCTION
      // Constructor
      Metrics();

      // Destructor
      ~Metrics();

      // Function to calculate Area of each element
      void CalcArea(const Mesh &Connec);

    private:

  };
