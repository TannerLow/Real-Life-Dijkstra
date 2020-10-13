#pragma once

#include <cstdint>
#include <forward_list>
#include <climits>
#include "Point.h"

class Node {
private:
	//Point object for drawing purposes
	Point point;

public:
	//Data directly from input files
	uint64_t id;
	double latitude, longitude;

	//2D coordinates obtained from normalizing lat and long
	double x, y;

	//Data used dijkstras
	uint32_t dist = INT_MAX;
	Node* parent = nullptr;
	bool visited = false;

	std::forward_list<Node*> neighbors;

	//Constructors
	Node();
	Node(uint64_t ID, double lat, double lon);
	Node(uint64_t ID, double lat, double lon, double y, double x);

	//Functions
	void addNeighbor(Node* n);
	Point& getPoint();
	//distance functions use x and y, NOT lat and long
	double distance(double X, double Y);
	double distance(const Node& to) const;
	//Sets dijstra data back to a default state
	void reset();

	//Overloaded operators
	//True if node id is smaller than the given node's
	bool operator<(const Node&)     const;
	bool operator<(const uint64_t&) const;
};


