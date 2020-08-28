#include "Point.h"

Point::Point() {
	dot.setRadius(10.f);
}

Point::Point(float x, float y) {
	dot.setRadius(10.f);
	dot.setPosition(x, y);
}

Point::Point(const sf::Vector2f& pos) {
	dot.setRadius(10.f);
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