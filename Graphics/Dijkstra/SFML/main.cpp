#include <cstdio>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Line.h"

#define WINDOW_WIDTH   800
#define WINDOW_HEIGHT  600
#define CAMERA_SPEED   0.05f
#define ROTATION_SPEED 0.01f

float handleRotation();
void  handleCameraMovement(sf::RenderWindow&, sf::View&);

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dijkstras");
    sf::View view(sf::FloatRect(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT));
    
    Point p1(200.f, 400.f);
    Point p2(500.f, 500.f);
    Point p3(100.f, 50.f);
    Point p4(10.f, 200.f);

    Line line1(p1, p2, sf::Color::Green);
    Line line2(p3, p4, sf::Color::Magenta);
    Line line3(p1, p4, sf::Color::Cyan);
    
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
        line1.draw(window);
        line2.draw(window);
        line3.draw(window);
        p1.draw(window);
        p2.draw(window);
        p3.draw(window);
        p4.draw(window);
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
    view.setCenter(view.getCenter().x + xOffset, view.getCenter().y + yOffset);
    window.setView(view);
}