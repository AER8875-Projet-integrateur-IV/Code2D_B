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
	m_outputSol = NULL;
};

Writer::~Writer(){}
////////////
// File Reading Verication (OPTIONAL)
//////////


// =============================================================================
// Writing function
// =============================================================================
void Writer::writeSol()
{
  //Sol.open("Solution.dat");  // Open file
	_path= "src" ;
    ofstream filestream(_path);
    writeHeader(filestream); // Writing header
	writeNewZone(filestream);
	writeCoord(filestream);
	std::cout << "1" << '\n';
	writeVar(filestream);
	std::cout << "2" << '\n';
	//FaceConnectivity(filestream)
	//writeElementConnectivity(filestream);
	std::cout << "3" << '\n';

  filestream.close(); // Close file
}

// =============================================================================
// HEADER
// =============================================================================
void Writer::writeHeader(std::ofstream &filestream)
{
  //file << "hello \n";
filestream << "TITLE = \"Example\"\n VARIABLES = \"X\",\"Y\",\"Density\",\"Speed U\",\"Speed V\", \"Pressure\", \"Energy\"" << endl;
}

void Writer::writeNewZone(std::ofstream &filestream)
{
	filestream << "ZONE "
	           << "ZONETYPE = FEQUADRILATERAL "
	           << "NODES = " << m_meshdata-> nPoin << ", "
	           << "ELEMENTS = " << m_meshdata-> nElem << ", "
	           //<< "FACES = " << m_meshdata-> getnface << ", "
	           << "NUMCONNECTEDBOUNDARYFACES = 0, TOTALNUMBOUNDARYCONNECTIONS = 0\n "
	           << "DATAPACKING = BLOCK, VARLOCATION = ([3-7] = CELLCENTERED) \n " ;
}

///POINTS COORDINATES
void Writer::writeCoord(ofstream &filestream)
{
	for (int iDim = 0; iDim < m_meshdata-> nDimn; iDim++){
		for (int iPoin = 0; iPoin < m_meshdata-> nPoin; iPoin++){
			filestream << m_meshdata-> coord[iPoin][iDim] << "\n";
		}
	}

	/*uint32_t returnline = 0;
	for (returnline = 0; returnline < unsigned(m_meshdata-> nPoin); returnline = returnline + 1)
	{
	  filestream << m_meshdata-> coord  .at(2 * returnline) << "\n";
	}
	for (returnline = 0; returnline < unsigned(m_meshdata-> nPoin); returnline = returnline + 1){
			filestream << m_meshdata-> coord .at(2 * returnline + 1) << "\n";
	}*/
}



///Variables Writing
void Writer::writeVar(ofstream &filestream)
{
	for (int iElem = 0; iElem < m_meshdata-> nElem; iElem++)
	{
		filestream << m_solution-> rho[iElem] << "\n";
	}
	for (int iElem = 0; iElem < m_meshdata-> nElem; iElem++)
	{
		filestream << m_solution-> u[iElem] / m_solution-> rho[iElem] << "\n";
	}
	for (int iElem = 0; iElem < m_meshdata-> nElem; iElem++)
	{
		filestream << m_solution-> v[iElem] / m_solution-> rho[iElem] << "\n";
	}
	for (int iElem = 0; iElem < m_meshdata-> nElem ; iElem++)
	{
		filestream << m_solution-> H[iElem] / m_solution-> rho[iElem] << "\n";
	}

	for (int iElem = 0; iElem < m_meshdata-> nElem ; iElem++)

	{
		filestream << m_solution-> p[iElem] << "\n";
	}
}

///Connectivity Writing
void Writer::writeElementConnectivity(ofstream &filestream)
{
	for (int iElem = 0; iElem < m_meshdata-> nElem ; iElem++)
	{
		for (int jNode = m_meshdata-> lNofa .at(iElem) .at(0); jNode < m_meshdata-> lNofa .at(iElem + 1) .at(0); jNode++)
		{
			filestream << m_meshdata-> lNofa .at(jNode) .at(0) + 1 << "\t";
		}
	}

}
