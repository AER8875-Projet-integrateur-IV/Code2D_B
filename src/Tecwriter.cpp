/*
/Fichier Tecwritter.cpp
/Date: Novembre 2020
/Projet: Projet Integrateur 4 (AER8875)
*/

#include "./Tecwriter.hpp"

using std::ofstream;

Tecwriter::Tecwriter(string &path, meshdata *Mesh, solution *Results)
{
	_path = path;
	_meshdata = Mesh;
	_solution = Results;
	_outputFile = NULL;

}

///Verification de lecture du fichier
Tecwriter::~Tecwriter()
{
	if (_outputFile != NULL)
	{
		fclose(_outputFile);
	}
	return;
}

void Tecwriter::writefile()
{
	///Ecriture de fichier
	ofstream filestream(_path);
	beginFile(filestream);
	writeNewzone(filestream);
	writeCoord(filestream);
	writeVar(filestream);
	///FaceConnectivity(filestream) 
	writeElementConnectivity(filestream);
	filestream.close();
}

///File Start
void Tecwriter::beginFile(ofstream &filestream)
{
	filestream << "TITLE = \"Example\"\n VARIABLES = \"X\",\"Y\",\"Density\",\"Speed U\",\"Speed V\", \"Pressure\", \"Energy\"" << endl;
}

void Tecwriter::writeNewzone(ofstream &filestream)
{
	filestream << "ZONE "
	           << "ZONETYPE = FEQUADRILATERAL " 
	           << "NODES = " << _meshdata->nPoin() << ", "
	           << "ELEMENTS = " << _meshdata->nElem() << ", "
	           << "FACES = " << _meshdata->getnface() << ", "
	           << "NUMCONNECTEDBOUNDARYFACES = 0, TOTALNUMBOUNDARYCONNECTIONS = 0\n " ;
	           << "DATAPACKING = BLOCK, VARLOCATION = ([3-7] = CELLCENTERED) \n " ;
}

///POINTS COORDINATES
void Tecwriter::writeCoord(ofstream &filestream)
{

	uint32_t returnline = 0;
	for (returnline = 0; returnline < unsigned(_meshdata->nPoin()); returnline = returnline + 1)
	{
	  filestream << _meshdata->getNodes()->at(2 * returnline) << "\n";
	}
	for returnline = 0; returnline < unsigned(_meshdata->nPoin()); returnline = returnline + 1)
    {
    	filestream << _meshdata->getNodes()->at(2 * returnline + 1) << "\n";
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
	filestream << "\n";
}