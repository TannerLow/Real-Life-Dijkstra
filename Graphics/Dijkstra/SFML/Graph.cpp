#include "Graph.h"
#include <algorithm>

Graph::Graph(double lat, double lon) 
	: referenceLat(lat), referenceLong(lon) {}

void Graph::addNode(uint64_t id, double lat, double lon) {
	nodes.push_back(Node(id, lat, lon));
}

void Graph::addNodeNormalized(uint64_t id, double lat, double lon) {
	double y = lat, x = lon;
	normalizeCoords(y, x);
	nodes.push_back(Node(id, lat, lon, y, x));
}

void Graph::addNode(Node node) {
	nodes.push_back(node);
}

void Graph::organize() {
	std::sort(nodes.begin(), nodes.end());
}

void Graph::formAdjacency(uint64_t src, uint64_t dst) {
	//find each in the nodes vector
	Node* from = &(*(std::lower_bound(nodes.begin(), nodes.end(), src)));
	Node* to   = &(*(std::lower_bound(nodes.begin(), nodes.end(), dst)));
	//point to each other
	from->neighbors.push_front(to);
	to->neighbors.push_front(from);
	//add line to list for drawing purposes
	graphConnections.push_back(Line(from->getPoint(), to->getPoint()));
}

void Graph::draw(sf::RenderWindow& window) {
	//draw lines
	for (Line connection : graphConnections) 
		connection.draw(window);
	
	//draw nodes
	for (Node node : nodes) 
		node.getPoint().draw(window);
}

void Graph::setReference(double lat, double lon) {
	referenceLat  = lat;
	referenceLong = lon;
}

#define PI 3.14159265359
double greatCircleDistance(double pLat, double pLong,
	double qLat, double qLong, double radius) {
	pLat *= PI / 180; pLong *= PI / 180;
	qLat *= PI / 180; qLong *= PI / 180;
	return radius * acos(cos(pLat) * cos(pLong) * cos(qLat) * cos(qLong) +
		cos(pLat) * sin(pLong) * cos(qLat) * sin(qLong) +
		sin(pLat) * sin(qLat));
}

#define EARTH_RADIUS 6137000
void Graph::normalizeCoords(double& originalLat, double& originalLong) {
	double yComponent = greatCircleDistance(referenceLat, referenceLong, originalLat, referenceLong, EARTH_RADIUS);
	double xComponent = greatCircleDistance(referenceLat, referenceLong, referenceLat, originalLong, EARTH_RADIUS);
	originalLat  = (originalLat  > referenceLat ) ? -yComponent : yComponent;
	originalLong = (originalLong < referenceLong) ? -xComponent : xComponent;
	std::cout << originalLat  << std::endl;
	std::cout << originalLong << std::endl;
	//FIX THIS MAKE IT NO ABSOLUTE VALUE
}

