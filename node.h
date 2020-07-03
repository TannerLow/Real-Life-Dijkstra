#ifndef NODE_H
#define NODE_H

#include <cstdint>
#include <forward_list>
#include <climits>

class Node{
public:
	uint64_t id;
	double latitude, longitude;
	uint32_t dist = INT_MAX;
	std::forward_list<Node*> neighbors;

	Node() : id(0), latitude(0), longitude(0) {}

	Node(uint64_t ID, double lat, double lon) 
		: id(ID), latitude(lat), longitude(lon) {}

	void display();
	void addNeighbor(Node* n);

	bool operator<(const Node& b) const;
	bool operator<(const uint64_t&) const;
};

#endif