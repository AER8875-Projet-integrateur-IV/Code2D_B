#include "Writer.h"
#include "Mesh.h"
#include "Results.h"
#include "Solver.h"


#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
// =============================================================================
// CONSTRUCTOR
// =============================================================================
Writer::Writer(string &path, Mesh *meshdata, Results *solution)
{
	string _path;
	m_meshdata = meshdata;
	m_solution = solution;
};

////////////
// File Reading Verication (OPTIONAL)
//////////


// =============================================================================
// Writing function
// =============================================================================
void Writer::~writeSol()
{
  //ofstream filestream(_path);
  file.open("Solution.dat");  // Open file

  WriteHeader(filestream); // Writing header

    filestream(_path);
	beginFile(filestream);
	writeNewzone(filestream);
	writeCoord(filestream);
	writeVar(filestream);
	///FaceConnectivity(filestream) 
	writeElementConnectivity(filestream);

  file.close(); // Close file
}

// =============================================================================
// HEADER
// =============================================================================
void Writer::Header(std::ofstream &file){
  file << "hello \n";
}
