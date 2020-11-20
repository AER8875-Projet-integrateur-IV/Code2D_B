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
	string _path;
    Mesh *m_meshdata;
    Results *m_solution;
    //ofstream m_outfile;
    file *m_outputSol;

    public:
  	// Write class constructor
    Writer();
    Writer(string &path, Mesh *meshdata, Results *solution);
    ~Writer();

  // Function to write solution
    void writeSol();

  // WWriting header
    void writeHeader(std::ofstream &);
    void writeNewZone(std::ofstream &);
    void writeCoord(std::ofstream &);
    void writeVar(std::ofstream &);
    void writeElementConnectivity(ofstream &filestream);

};
