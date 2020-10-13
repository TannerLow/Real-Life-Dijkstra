#pragma once
#include "Node.h"
#include "Line.h"
#include <vector>
#include <cstdint>
#include <SFML/Graphics.hpp>

class Graph
{
private:
	std::vector<Node> nodes; //nodes, drawn as white dots
	std::vector<Line> graphConnections; //node connections drawn as white lines
	std::vector<Line> shortestPath; //dijkstra path, displayed in red
	double referenceLat, referenceLong; //reference lat and lon for the normalizing process

	//Maps lat and lon to 2D corrdinates for convenient drawing and distance calculations
	void normalizeCoords(double&, double&);

public:
	//constructors
	Graph() : referenceLat(0), referenceLong(0) {}
	Graph(double latitude, double longitude);
	~Graph() {}
	


	//functions
	void addNode(Node node); //non-normalized
	void addNode(uint64_t id, double latitude, double longitude); //non-normalized
	void addNodeNormalized(uint64_t id, double latitude, double longitude);

	// sort the nodes vector based on id
	void organize();
	// Connect 2 nodes together and add each other as neighbors
	void formAdjacency(uint64_t source, uint64_t dest);
	// set reference coords for normalizing
	void setReference(double latitude, double longitude);
	void draw(sf::RenderWindow& window);
	//returns pointer to node nearest the given coords
	Node* getNearestNode(double x, double y);
	//performs dijkstras on graph, displays results as red path (if results are found)
	void dijkstra(Node* source, Node* dest);
};

