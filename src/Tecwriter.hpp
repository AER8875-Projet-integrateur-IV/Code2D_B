/*
/Fichier Tecwriter.hpp
/Date: November 2020
/Projet: Projet Integrateur 4 (AER8875)
*/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "../mesh/meshdata/meshdata.hpp"
#include "../../tools/stringTools.hpp"
#include "../solver/solutioStruct.hpp"

using namespace std;

class Tecwriter
{
private:
	string_path;
Mesdata *_meshdata;
Solution *_solution;
file *_outputfile;
bool isfilevalid();

public:
Tecwriter(string &path, meshdata *Mesh, solution *Results);
~Tecwriter();
void writeFile();
void beginFile(std::ofstream &);
void writeNewZone(std::ofstream &);
void writeCoord(std::ofstream &);
void writeVar(std::ofstream &);
void writeElementConnectivity(ofstream &filestream);

};