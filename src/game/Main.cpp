#include <SFML/Graphics.hpp>

#include "frame/Frame.h"
#include "frame/SampleFrame.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    frame::SampleFrame f1(sf::Color::Red);
    frame::SampleFrame f2(sf::Color::Blue);
    frame::SampleFrame* curFrame = &f1;

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        window.draw(*curFrame->getDrawable(nullptr));
        window.display();
    }
    return 0;
}