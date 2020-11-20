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

#include "Mesh.h"
#include "Results.h" 
#include "Solver.h"


using namespace std;
//cout << "here" << endl
class Writer 
{

	private:
	//string_path;
    Mesh *m_meshdata;
    Results *m_solution;
    ofstream m_outfile;

    public:
  	// Write class constructor
    Writer();
    Writer(string &path, Mesh *meshdata, Results *solution);
    
    ~Writer();

  // Function to write solution
     void WriteSol(std::string outpath);
     void WriteSol(std::string outpath, std::vector<std::string> options);

  // WWriting header
    void WriteHeader(std::vector<std::string> options);
    void writeNewZone(std::vector<std::string> options);
    void writeCoord();
    void writeVar(std::vector<std::string> options);
    void writeElementConnectivity();

};
