// =============================================================================
//                                  WRITER
//
// The purpose of this class is to write the solution to the desired format.
// The first iteration of the class will write the solution to the VTK format.
//
// =============================================================================

#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "../Mesh.h"
#include "../Results.h"
//#include "../../tools/stringTools.h"/

using namespace std;

class Writer {

	private:
    string _path;
    Mesdata *_meshdata;
    Solution *_solution;
    file *_outputfile;
    bool isfilevalid();

    public:
  	// Write class constructor
    //Writer();

    Tecwriter(string &path, meshdata *Mesh, solution *Results);
    ~Tecwriter();


  // Function to write solution
     void WriteSol();

  // WWriting header
  // void Header(std::ofstream&);
    void writeNewZone(std::ofstream &);
    void writeCoord(std::ofstream &);
    void writeVar(std::ofstream &);
    void writeElementConnectivity(ofstream &filestream);

};
