#pragma once

#include <SFML/Graphics.hpp>

//Point class for wrapping sf::CircleShape objects
//RADIUS MUST BE SET BEFORE CONSTRUCTING POINTS
class Point
{
public:
	//constructors
	Point();
	Point(float x, float y);
	Point(const sf::Vector2f& pos);
	~Point() {}

	//functions
	void draw(sf::RenderWindow& window) const;
	sf::Vector2f getCenter() const;
	void setPosition(float x, float y);
	void setColor(sf::Color color);

private:
	sf::CircleShape dot;

public:
	//Static variable representing point radius when drawn
	static float radius;
};