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

////////////
// File Reading Verication (OPTIONAL)
//////////


// =============================================================================
// Writing function
// =============================================================================
void Writer::writeSol()
{
  //Sol.open("Solution.dat");  // Open file
    ofstream filestream(_path);
    writeHeader(filestream); // Writing header
	writeNewZone(filestream);
	writeCoord(filestream);
	writeVar(filestream);
	///FaceConnectivity(filestream) 
	writeElementConnectivity(filestream);

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
	           << "FACES = " << m_meshdata-> getnface << ", "
	           << "NUMCONNECTEDBOUNDARYFACES = 0, TOTALNUMBOUNDARYCONNECTIONS = 0\n "
	           << "DATAPACKING = BLOCK, VARLOCATION = ([3-7] = CELLCENTERED) \n " ;
}

///POINTS COORDINATES
void Writer::writeCoord(ofstream &filestream)
{

	uint32_t returnline = 0;
	for (returnline = 0; returnline < unsigned(m_meshdata-> nPoin); returnline = returnline + 1)
	{
	  filestream << m_meshdata-> ostringstream(nNode) ; ->at(2 * returnline) << "\n";
	}
	for returnline = 0; returnline < unsigned(m_meshdata-> nPoin); returnline = returnline + 1)
    {
    	filestream << m_meshdata->getNodes()->at(2 * returnline + 1) << "\n";
    } 
}


///Variables Writing
void Tecwriter::writeVar(ofstream &filestream)
{
	for (int iElem = 0; iElem < _meshdata->getNELEM(); iElem++)
	{
		filestream << _solution->rho[iElem] << "\n";
	}
	for (int iElem = 0; iElem < _meshdata->getNELEM(); iElem++)
	{
		filestream << _solution->rhoU[iElem] / _solution-> rho[iElem] << "\n";
	}
	for (int iElem = 0; iElem < _meshdata->getNELEM(); iElem++)
	{
		filestream << _solution->rhoV[iElem] / _solution-> rho[iElem] << "\n";
	}
	for (int iElem = 0; iElem < _meshdata->getNELEM(); iElem++)
	{
		filestream << _solution->rhoE[iElem] / _solution-> rho[iElem] << "\n";
	}
	for (int iElem = 0; iElem < _meshdata->getNELEM(); iElem++)	
	{
		filestream << _solution->p[iElem] << "\n";
	}
}

///Connectivity Writing
void Tecwriter::writeElementConnectivity(ofstream &filestream)
{
	for (int iElem = 0; iElem < _meshdata->getNELEM(); iElem++)
	{
		for (int jNode = _meshdata->getElement2NodesStart()->at(iElem); jNode < _meshdata->getElement2NodesStart()->at(iElem + 1); jNode++)
		{
			filestream << _meshdata->getElement2Nodes()->at(jNode) + 1 << "\t";
		}
	}
