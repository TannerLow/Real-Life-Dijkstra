#include "node.h"
#include <cstdio>

void Node::display() {
	printf("id: %llu\nlat:   %.7f\nlon: %.7f\n\n", id, latitude, longitude);
}

void Node::addNeighbor(Node* n) {
	neighbors.push_front(n);
}

bool Node::operator<(const Node& b) const {
	return id < b.id;
}

bool Node::operator<(const uint64_t& b) const {
	return id < b;
}