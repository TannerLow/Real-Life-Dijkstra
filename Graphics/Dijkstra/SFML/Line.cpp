#include "Line.h"

Line::Line() {
	line[0] = sf::Vector2f(0.f, 0.f);
	line[1] = sf::Vector2f(0.f, 0.f);
}

Line::Line(float x1, float y1, float x2, float y2) {
	line[0] = sf::Vector2f(x1, y1);
	line[1] = sf::Vector2f(x2, y2);
}

Line::Line(const sf::Vector2f& pos1, const sf::Vector2f& pos2) {
	line[0] = pos1;
	line[1] = pos2;
}

Line::Line(const Point& p1, const Point& p2) {
	line[0] = p1.getCenter();
	line[1] = p2.getCenter();
}

Line::Line(const Point& p1, const Point& p2, const sf::Color& color) {
	line[0] = p1.getCenter();
	line[0].color = color;
	line[1] = p2.getCenter();
	line[1].color = color;
}

void Line::draw(sf::RenderWindow& window) const {
	window.draw(line, 2, sf::Lines);
}

void Line::setColor(const sf::Color& color) {
	line[0].color = color;
	line[1].color = color;
}