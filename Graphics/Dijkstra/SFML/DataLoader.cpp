#include "DataLoader.h"

DataLoader::DataLoader() {

}

DataLoader::DataLoader(const char* nodeFilename, const char* waysFilename) {
	nodeFileHandle.open(nodeFilename);
	waysFileHandle.open(waysFilename);
}

DataLoader::~DataLoader() {

}

Graph& DataLoader::getGraph() {
	return graph;
}
