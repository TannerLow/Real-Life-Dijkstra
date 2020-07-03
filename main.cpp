#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "node.h"

int main(){
	std::vector<Node> nodes;

//Assemble Node data
	std::ifstream nodeFile("inputs/nodes.txt");
	std::string line;
	while(getline(nodeFile, line)){
		std::cout << line << '\n';
		std::stringstream ss;
		ss << line;
		uint64_t id;
		double lat, lon;
		ss >> id >> lat >> lon;

		nodes.push_back(Node(id,lat,lon));
	}
	nodeFile.close();

	std::sort(nodes.begin(), nodes.end());

	for(Node n : nodes){
		n.display();
	}

//Assemble Edge/Way data
	nodeFile.open("inputs/ways.txt");
	while(getline(nodeFile, line)){
		std::cout << line << '\n';

		//Parse way data into adjacencies
		std::stringstream ss;
		ss << line;
		uint64_t sourceID, destID;
		ss >> sourceID;
		while(ss >> destID){
			//get src and dest nodes
			Node* from = &(*(std::lower_bound(nodes.begin(), nodes.end(), sourceID)));
			Node* to   = &(*(std::lower_bound(nodes.begin(), nodes.end(),   destID)));
			//point to each other
			from->neighbors.push_front(to  );
			to  ->neighbors.push_front(from);

			sourceID = destID;
		}
	}
	nodeFile.close();

	//Test code to see if it worked
	for(Node* n : nodes[0].neighbors){
		std::cout << "connected to\n";
		n->display();
	}

	return 0;
}