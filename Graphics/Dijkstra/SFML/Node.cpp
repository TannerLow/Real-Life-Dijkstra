#include "node.h"
#include <cmath>

//Default ctor zero's all initial data fields
Node::Node() : id(0), latitude(0), longitude(0), y(0), x(0) {
	point.setPosition(0, 0);
}

Node::Node(uint64_t ID, double lat, double lon) 
	: id(ID), latitude(lat), longitude(lon), y(lat), x(lon) {
	point.setPosition(x, y);
}

Node::Node(uint64_t ID, double lat, double lon, double y, double x) 
	: id(ID), latitude(lat), longitude(lon), y(y), x(x){
	point.setPosition(x, y);
}

void Node::addNeighbor(Node* n) {
	neighbors.push_front(n);
}

Point& Node::getPoint() {
	return point;
}

//Euclidian distance between given coords and x and y fields
double Node::distance(double X, double Y) {
	return sqrt(pow(X-x, 2) + pow(Y-y, 2));
}

//Euclidian distance between given Node and x and y fields
double Node::distance(const Node& to) const {
	return sqrt(pow(to.x - x, 2) + pow(to.y - y, 2));
}

//Sets dijstra data back to a default state
void Node::reset() {
	parent = nullptr;
	dist = INT_MAX;
	visited = false;
}

//true if node has a smaller id than given Node
bool Node::operator<(const Node& b) const {
	return id < b.id;
}

//true if node has a smaller id than given Node
bool Node::operator<(const uint64_t& b) const {
	return id < b;
}