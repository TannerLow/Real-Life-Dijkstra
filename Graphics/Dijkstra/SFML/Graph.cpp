#include "Graph.h"
#include <algorithm>
#include <utility>
#include <queue>

#define PI 3.14159265359
#define EARTH_RADIUS 6137000

Graph::Graph(double lat, double lon) 
	: referenceLat(lat), referenceLong(lon) {}

void Graph::addNode(uint64_t id, double lat, double lon) {
	nodes.emplace_back(id, lat, lon);
}

//normalize coords of and create and add node to the graph
void Graph::addNodeNormalized(uint64_t id, double lat, double lon) {
	double y = lat, x = lon;
	normalizeCoords(y, x);
	nodes.emplace_back(id, lat, lon, y, x);
}

void Graph::addNode(Node node) {
	nodes.push_back(node);
}

// sort the nodes vector based on id
void Graph::organize() {
	std::sort(nodes.begin(), nodes.end());
}

//connects the two nodes (described by given id's) to each other and adds the 
//corresponding line to the graphConnections vector
void Graph::formAdjacency(uint64_t src, uint64_t dst) {
	//find each in the nodes vector
	Node* from = &(*(std::lower_bound(nodes.begin(), nodes.end(), src)));
	Node* to   = &(*(std::lower_bound(nodes.begin(), nodes.end(), dst)));
	//point to each other
	from->neighbors.push_front(to);
	to->neighbors.push_front(from);
	//add line to list for drawing purposes
	graphConnections.emplace_back(from->getPoint(), to->getPoint());
}

//draws nodes, connections, and shortest path to the screen
void Graph::draw(sf::RenderWindow& window) {
	sf::FloatRect bounds(
		window.getView().getCenter() - window.getView().getSize() / 2.f,
		window.getView().getSize()
	);

	//draw lines that have both end points in visible range
	for (Line& connection : graphConnections) {
		if (bounds.contains(sf::Vector2f(connection.getLine()[0].position.x, connection.getLine()[0].position.y)) or
			bounds.contains(sf::Vector2f(connection.getLine()[1].position.x, connection.getLine()[1].position.y))) 
		{
				connection.draw(window);
		}
	}
	
	//draw nodes that are in visible range
	for (Node& node : nodes) {
		if (bounds.contains(sf::Vector2f(node.x, node.y))) {
			node.getPoint().draw(window);
		}
	}

	//draw shortest path
	for (Line& connection : shortestPath)
		connection.draw(window);
}

//Finds the nearest node the given corrds based off euclidian distance, O(n) runtime
Node* Graph::getNearestNode(double x, double y) {
	int smallest = 0;

	if (!nodes.size()) {
		return nullptr;
	}

	//finds index of node with the least distance to the given coords
	double minDistance = nodes[smallest].distance(x, y);
	for (int i = 1; i < nodes.size(); i++) {
		if (nodes[i].distance(x, y) < minDistance) {
			minDistance = nodes[i].distance(x, y);
			smallest = i;
		}
	}

	return &(nodes[smallest]);
}

// set reference coords for normalizing
void Graph::setReference(double lat, double lon) {
	referenceLat  = lat;
	referenceLong = lon;
}

//helper function, gets arc distance between two sets of lat and lon
double greatCircleDistance(double pLat, double pLong,
	double qLat, double qLong, double radius) {
	pLat *= PI / 180; pLong *= PI / 180;
	qLat *= PI / 180; qLong *= PI / 180;
	return radius * acos(cos(pLat) * cos(pLong) * cos(qLat) * cos(qLong) +
		cos(pLat) * sin(pLong) * cos(qLat) * sin(qLong) +
		sin(pLat) * sin(qLat));
}

//Maps lat and lon to 2D corrdinates for convenient drawing and distance calculations
void Graph::normalizeCoords(double& originalLat, double& originalLong) {
	double yComponent = greatCircleDistance(referenceLat, referenceLong, originalLat, referenceLong, EARTH_RADIUS);
	double xComponent = greatCircleDistance(referenceLat, referenceLong, referenceLat, originalLong, EARTH_RADIUS);
	originalLat  = (originalLat  > referenceLat ) ? -yComponent : yComponent;
	originalLong = (originalLong < referenceLong) ? -xComponent : xComponent;
}

//Perform dijkstras shortest path algorithm on the graph going from source to dest
void Graph::dijkstra(Node* source, Node* dest) {
	//reset every nodes' dijkstra data members
	for (Node& n : nodes)
		n.reset();

	//setup queue and current pointer
	typedef std::pair<uint32_t, Node*> pairIntNode;
	std::priority_queue<pairIntNode, std::vector<pairIntNode>, std::greater<pairIntNode>> nodeQueue;
	Node* current = nullptr;

	//manually enter data for 
	source->dist = 0;
	nodeQueue.push(pairIntNode(0, source));

	while (!nodeQueue.empty()) {
		//get node in queue with the smallest distance from source
		current = nodeQueue.top().second;

		//target found?
		if (current == dest) {
			break;
		}
		nodeQueue.pop();
		current->visited = true;

		//Check all neighbors of current
		for (Node* neighbor : current->neighbors) {
			double weight = current->distance(*neighbor);
			if (!neighbor->visited and current->dist + weight < neighbor->dist) {
				neighbor->dist   = current->dist + weight;
				neighbor->parent = current;
				nodeQueue.emplace(neighbor->dist, neighbor);
			}
		}
	}

	//reset shortestPath vector and check validity of current
	shortestPath.clear();
	if (current == nullptr or current != dest) {
		return;
	}

	//add display line of shortest path found to shortestPath vector
	Node* to = current;
	while (to->parent != nullptr) {
		shortestPath.emplace_back(to->getPoint(), to->parent->getPoint());
		shortestPath.back().setColor(sf::Color::Red);
		to = to->parent;
	}
}