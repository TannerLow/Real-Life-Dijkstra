#include <cstdio>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Line.h"
#include "Graph.h"
#include <cmath>

#define WINDOW_WIDTH   800
#define WINDOW_HEIGHT  600
#define CAMERA_SPEED   0.05f
#define ROTATION_SPEED 0.01f

float handleRotation();
void  handleCameraMovement(sf::RenderWindow&, sf::View&);

#define PI 3.14159265359
double gCD(double pLat, double pLong,
           double qLat, double qLong, double radius) {
    pLat *= PI / 180; pLong *= PI / 180;
    qLat *= PI / 180; qLong *= PI / 180;
    return radius * acos(cos(pLat) * cos(pLong) * cos(qLat) * cos(qLong) +
        cos(pLat) * sin(pLong) * cos(qLat) * sin(qLong) +
        sin(pLat) * sin(qLat));
}

int main() {
    std::cout << gCD(33.8168780, -118.0177677, 33.8149927, -118.0177460, 6137000) << std::endl;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dijkstras");
    sf::View view(sf::FloatRect(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT));
    
    Point p1(200.f, 400.f);
    Point p2(500.f, 500.f);
    Point p3(100.f, 50.f);
    Point p4(10.f, 200.f);

    Line line1(p1, p2, sf::Color::Green);
    Line line2(p3, p4, sf::Color::Magenta);
    Line line3(p1, p4, sf::Color::Cyan);

    Graph graph;
    graph.addNode(122878922, 33.8168780, -118.0177677);
    graph.addNode(122878925, 33.8149927, -118.0177460);
    graph.addNode(122878927, 33.8149753, -118.0185713);
    graph.addNode(122958863, 33.8168759, -118.0185970);
    graph.addNode(122958866, 33.8142651, -118.0185437);

    graph.formAdjacency(122878922, 122878925);
    graph.formAdjacency(122878925, 122878927);
    graph.formAdjacency(122958863, 122878927);
    graph.formAdjacency(122878927, 122958866);

    graph.test();
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized) {
                //Smart resize: resizes window and moves image to its new spot
                view.setSize(event.size.width, event.size.height);
                window.setView(view);
            }
            //Zooming in and out with mouse wheel
            else if (event.type == sf::Event::MouseWheelMoved)
            {
                if (event.mouseWheel.delta > 0) {
                    view.zoom(0.9f);
                }
                else {
                    view.zoom(1.1f);
                }
                window.setView(view);
                //std::cout << "mouse x: " << event.mouseWheel.x << std::endl;
                //std::cout << "mouse y: " << event.mouseWheel.y << std::endl;
            }
        }

        // Handle Rotations with arrow keys
        view.rotate(handleRotation());
        window.setView(view);

        // Handle camera movement
        handleCameraMovement(window, view);

        // Render cycle
        window.clear();
        /*line1.draw(window);
        line2.draw(window);
        line3.draw(window);
        p1.draw(window);
        p2.draw(window);
        p3.draw(window);
        p4.draw(window);*/

        graph.draw(window);
        window.display();
    }

    return EXIT_SUCCESS;
}

float handleRotation() {
    float netRotation = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left )) netRotation -= ROTATION_SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) netRotation += ROTATION_SPEED;
    return netRotation;
}

void  handleCameraMovement(sf::RenderWindow& window, sf::View& view) {
    float xOffset = 0.f, yOffset = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) yOffset += CAMERA_SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) xOffset += CAMERA_SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) yOffset -= CAMERA_SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) xOffset -= CAMERA_SPEED;
    view.move(xOffset, yOffset);
    window.setView(view);
}