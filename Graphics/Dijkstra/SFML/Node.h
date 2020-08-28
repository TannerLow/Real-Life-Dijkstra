#pragma once

#include <cstdint>
#include <forward_list>
#include <climits>
#include "Point.h"

class Node {
private:
	Point point;

public:
	uint64_t id;
	double latitude, longitude;
	double x, y;
	uint32_t dist = INT_MAX;
	std::forward_list<Node*> neighbors;

	Node();
	Node(uint64_t ID, double lat, double lon);
	Node(uint64_t ID, double lat, double lon, double y, double x);

	void display() const;
	void addNeighbor(Node* n);
	Point getPoint() const;

	// True is node id is smaller than the given node's
	bool operator<(const Node& b) const;
	bool operator<(const uint64_t&) const;
};


