#include "DataLoader.h"
#include <string>
#include <sstream>

typedef unsigned long long ull;

DataLoader::DataLoader() {}

DataLoader::~DataLoader() {}

//loads data from input files to the graph, throws exception if files cannot be opened
void DataLoader::load(const char* nodeFilename, const char* waysFilename) {
	nodeFileHandle.open(nodeFilename);
	waysFileHandle.open(waysFilename);
	if (nodeFileHandle.fail() or waysFileHandle.fail()) 
		throw "Nodes/Ways file(s) could not be opened";
	loadNodes();
	loadWays();
}

// nodes file required format: id latitude longitude\n
//                             ...
void DataLoader::loadNodes() {
	std::stringstream ss;
	std::string line;
	ull id;
	double lat, lon;
	if (std::getline(nodeFileHandle, line)) {
		ss << line;
		ss >> id >> lat >> lon;
		ss.clear();
		graph.setReference(lat, lon);
		graph.addNodeNormalized(id, lat, lon);
	}
	while (std::getline(nodeFileHandle, line)) {
		ss << line;
		ss >> id >> lat >> lon;
		ss.clear();
		graph.addNodeNormalized(id, lat, lon);
	}
	nodeFileHandle.close();
}

//  ways file required format: id id ...\n
//                             ...
void DataLoader::loadWays() {
	std::string line;
	std::stringstream ss;
	ull src, dst;
	while (std::getline(waysFileHandle, line)) {
		ss << line;
		ss >> src;
		while (ss >> dst) {
			graph.formAdjacency(src, dst);
			src = dst;
		}
		ss.clear();
	}
	waysFileHandle.close();
}

Graph* DataLoader::getGraph() {
	return &graph;
}
