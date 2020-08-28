#include "Graph.h"
#include <algorithm>

void Graph::addNode(uint64_t id, double lat, double lon) {
	nodes.push_back(Node(id, lat, lon));
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
}

void Graph::normalizeCoords() {
	float x = 33, y = -118;
	double scaleFactor = 10000000;
	for (Node node : nodes) {
		node.latitude  -= x;
		node.longitude -= y;
		node.latitude  *= scaleFactor;
		node.longitude *= scaleFactor;
	}
}

void Graph::draw(sf::RenderWindow& window) {
	for (Node node : nodes) {
		node.getPoint().draw(window);
	}
}