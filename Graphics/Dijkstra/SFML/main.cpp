#include <iostream>
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Line.h"
#include "Graph.h"
#include "DataLoader.h"

#define WINDOW_WIDTH   1000
#define WINDOW_HEIGHT  800

void  handleCameraMovement(sf::RenderWindow&, sf::View&, float);
void  adjustCameraSpeed(float&);

float Point::radius = 1.5f;

int main(int argc, char* argv[]) {
    float cameraSpeed = 2.5f;

    //Attempt to load graph from data files using DataLoader
    Graph* graph = nullptr;
    DataLoader dataloader;
    try {
        if (argc == 1) { //no arguments
            dataloader.load();
            graph = dataloader.getGraph();
        }
        else if (argc == 3) { //input files specified
            dataloader.load(argv[1], argv[2]);
            graph = dataloader.getGraph();
        }
        else {
            std::cout << "Invalid arguments" << std::endl;
            return EXIT_FAILURE;
        }
    }
    catch (const char* msg) {
        std::cout << msg << std::endl
            << "press Enter to terminate" << std::endl;
        std::cin.get();
        return EXIT_FAILURE;
    }

    //Setup windows and initial view
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dijkstras");
    sf::View view(sf::FloatRect(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT));
    sf::Vector2f center = view.getCenter();
    float zoomFactor = 1.0f;

    Node *source = nullptr, *dest = nullptr;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            //Window is resized
            else if (event.type == sf::Event::Resized) {
                view.setSize(event.size.width, event.size.height);
                view.setCenter(event.size.width / 2, event.size.height / 2);
                window.setView(view);
                center.x = view.getCenter().x;
                center.y = view.getCenter().y;
                zoomFactor = 1.0f;
            }
            //Zooming in and out with mouse wheel
            else if (event.type == sf::Event::MouseWheelMoved)
            {
                //zoom in
                if (event.mouseWheel.delta > 0) {
                    view.zoom(0.9f);
                    zoomFactor *= 0.9f;
                }
                //zoom out
                else {
                    view.zoom(1.1f);
                    zoomFactor *= 1.1f;
                }
                window.setView(view);
            }
            //Mouse click events
            else if (event.type == sf::Event::MouseButtonReleased) {
                //get node nearest click
                Node* temp = (graph->getNearestNode(
                                ((float) event.mouseButton.x - center.x) * zoomFactor + center.x + (view.getCenter().x - center.x),
                                ((float) event.mouseButton.y - center.y) * zoomFactor + center.y + (view.getCenter().y - center.y)
                              ));

                temp->getPoint().setColor(sf::Color::Red);

                //only keep track of last 2 points clicked and perform dijkstra when two points are selected
                if (source == nullptr) {
                    source = temp;
                }
                else if(dest == nullptr){
                    dest = temp;
                    graph->dijkstra(source, dest);
                }
                else {
                    //reset previous two points
                    source->getPoint().setColor(sf::Color::White);
                    dest->getPoint().setColor(sf::Color::White);
                    source = temp;
                    dest = nullptr;
                }
            }
        }


        window.setView(view);

        // Handle camera movement
        adjustCameraSpeed(cameraSpeed);
        handleCameraMovement(window, view, cameraSpeed);

        // Render cycle
        window.clear();
        graph->draw(window);
        window.display();
    }

    return EXIT_SUCCESS;
}

//Move view based on which WASD keys are pressed
void  handleCameraMovement(sf::RenderWindow& window, sf::View& view, float cameraSpeed) {
    float xOffset = 0.f, yOffset = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) yOffset -= cameraSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) xOffset -= cameraSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) yOffset += cameraSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) xOffset += cameraSpeed;
    view.move(xOffset, yOffset);
    window.setView(view);
}

//Adjust camera speed based on + or - keys being pressed
void adjustCameraSpeed(float& cameraSpeed) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) 
        cameraSpeed += 0.2f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) 
        cameraSpeed -= 0.2f;

    if (cameraSpeed < 0.0f)
        cameraSpeed = 0.0f;
}