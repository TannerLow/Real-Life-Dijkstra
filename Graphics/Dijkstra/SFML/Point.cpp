#include "Point.h"

Point::Point() {
	dot.setRadius(radius);
}

Point::Point(float x, float y) {
	dot.setRadius(radius);
	dot.setPosition(x, y);
}

Point::Point(const sf::Vector2f& pos) {
	dot.setRadius(radius);
	dot.setPosition(pos);
}

void Point::draw(sf::RenderWindow& window) const {
	window.draw(dot);
}

sf::Vector2f Point::getCenter() const {
	return sf::Vector2f(dot.getPosition().x + dot.getRadius(), 
						dot.getPosition().y + dot.getRadius());
}

void Point::setPosition(float x, float y) {
	dot.setPosition(x, y);
}

void Point::setColor(sf::Color color) {
	dot.setFillColor(color);
}