#pragma once

#include <SFML/Graphics.hpp>

class Point
{
public:
	Point();
	Point(float x, float y);
	Point(const sf::Vector2f& pos);
	~Point() {}

	void draw(sf::RenderWindow& window) const;
	sf::Vector2f getCenter() const;

private:
	sf::CircleShape dot;
};

