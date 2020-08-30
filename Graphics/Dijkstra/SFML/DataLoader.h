#pragma once
#include "Graph.h"
#include <fstream>

class DataLoader {
private:
	Graph graph;
	std::ifstream nodeFileHandle;
	std::ifstream waysFileHandle;

public:
	DataLoader();
	DataLoader(const char* nodeFilename, const char* waysFilename);
	~DataLoader();

	Graph& getGraph();
};

