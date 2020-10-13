#pragma once
#include "Graph.h"
#include <fstream>

class DataLoader {
private:
	Graph graph;
	std::ifstream nodeFileHandle;
	std::ifstream waysFileHandle;

	//helper functions for load()
	void loadNodes();
	void loadWays();

public:
	//constructors
	DataLoader();
	~DataLoader();
	
	// loads data from the provided files
	// nodes file required format: id latitude longitude\n
	//                             ...
	//
	//  ways file required format: id id ...\n
	//                             ...
	// THROWS EXCEPTION if files cannot be loaded
	void load(const char* nodeFilename = "nodes.txt", const char* waysFilename = "ways.txt");

	//getter for the graph constructed from the input data
	Graph* getGraph();
};

