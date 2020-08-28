#pragma once
#include "Node.h"
#include <vector>
#include <cstdint>
#include <SFML/Graphics.hpp>

#include <iostream>

class Graph
{
private:
	std::vector<Node> nodes;
	double referenceLat, referenceLong;

	void normalizeCoords(double&, double&); // Make coords easier to draw

public:
	Graph() : referenceLat(0), referenceLong(0) {}
	Graph(double latitude, double longitude);
	~Graph() {}
	
	void addNode(uint64_t id, double latitude, double longitude);
	void addNodeNormalized(uint64_t id, double latitude, double longitude);
	void addNode(Node node);
	void organize(); // sort the nodes vector
	void formAdjacency(uint64_t source, uint64_t dest); // Connect 2 nodes together
	void setReference(double latitude, double longitude); // set reference coords for normalizing
	void draw(sf::RenderWindow& window);

	void test() {
		//Test code to see if it worked
		for (Node* n : nodes[0].neighbors) {
			std::cout << "connected to\n";
			n->display();
		}
	}
};

