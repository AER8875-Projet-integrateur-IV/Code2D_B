// =============================================================================
//                                  WRITER
//
// The purpose of this class is to write the solution to the desired format.
// The first iteration of the class will write the solution to the VTK format.
//
// =============================================================================

#pragma once
#include "Mesh.h"
#include <string>
#include <iostream>
#include <fstream>

class Writer {

  public:

    // Write class constructor
    Writer();

    // Function to write solution
    void WriteSol();

    // WWriting header
    void Header(std::ofstream&);

  private:

};
