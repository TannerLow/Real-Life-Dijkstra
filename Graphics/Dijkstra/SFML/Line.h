#pragma once
#include "Point.h"
#include <SFML/Graphics.hpp>

class Line
{
public:
	Line();
	Line(float x1, float y1, float x2, float y2);
	Line(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
	Line(const Point& p1, const Point& p2);
	Line(const Point& p1, const Point& p2, const sf::Color& color);
	~Line() {}

	void draw(sf::RenderWindow& window) const;
	void setColor(const sf::Color& color);

private:
	sf::Vertex line[2];

};

