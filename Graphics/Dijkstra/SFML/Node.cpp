#include "node.h"
#include <cstdio>

Node::Node() : id(0), latitude(0), longitude(0), y(0), x(0) {
	point.setPosition(0, 0);
}

Node::Node(uint64_t ID, double lat, double lon) 
	: id(ID), latitude(lat), longitude(lon), y(lat), x(lon) {}

Node::Node(uint64_t ID, double lat, double lon, double y, double x) 
	: id(ID), latitude(lat), longitude(lon), y(y), x(x){
	point.setPosition(x, y);
}

void Node::display() const {
	printf("id: %llu\nlat:   %.7f\nlon: %.7f\n\n", id, latitude, longitude);
}

void Node::addNeighbor(Node* n) {
	neighbors.push_front(n);
}

Point Node::getPoint() const {
	return point;
}

bool Node::operator<(const Node& b) const {
	return id < b.id;
}

bool Node::operator<(const uint64_t& b) const {
	return id < b;
}