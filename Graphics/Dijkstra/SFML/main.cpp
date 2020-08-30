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
#define ROTATION_SPEED 0.02f

float handleRotation();
void  handleCameraMovement(sf::RenderWindow&, sf::View&);

int main() {

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dijkstras");
    sf::View view(sf::FloatRect(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT));

    Graph graph;
    graph.setReference(33.8168780, -118.0177677);
    graph.addNodeNormalized(122878922, 33.8168780, -118.0177677);
    graph.addNodeNormalized(122878925, 33.8149927, -118.0177460);
    graph.addNodeNormalized(122878927, 33.8149753, -118.0185713);
    graph.addNodeNormalized(122958863, 33.8168759, -118.0185970);
    graph.addNodeNormalized(122958866, 33.8142651, -118.0185437);

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
            }
        }

        // Handle Rotations with arrow keys
        view.rotate(handleRotation());
        window.setView(view);

        // Handle camera movement
        handleCameraMovement(window, view);

        // Render cycle
        window.clear();
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