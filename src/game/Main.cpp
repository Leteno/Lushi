#include <iostream>
#include <SFML/Graphics.hpp>

#include "frame/Event.h"
#include "frame/Frame.h"
#include "frame/FrameState.h"
#include "frame/GlobalData.h"
#include "frame/SampleFrame.h"

frame::SampleFrame* curFrame;
frame::SampleFrame* nextFrame;
frame::FrameState state;
frame::GlobalData data;
void renderThread(sf::RenderWindow* window)
{
    window->setActive(true);

    while (window->isOpen())
    {
        window->clear();
        window->draw(*curFrame->getDrawable(&data));
        window->display();
    }
}

int main()
{
    frame::SampleFrame f1(sf::Color::Red);
    frame::SampleFrame f2(sf::Color::Blue);
    curFrame = &f1;
    nextFrame = &f2;

    sf::RenderWindow window(sf::VideoMode(200, 200), "Game!");
    window.setFramerateLimit(60);
    window.setActive(false);

    sf::Thread thread(&renderThread, &window);
    thread.launch();

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                goto exit;
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    auto tmp = curFrame;
                    curFrame = nextFrame;
                    nextFrame = tmp;
                }
            }

            curFrame->ReceiveEvent(frame::Event::from(event));
        }
        curFrame->DoLogic(&state, &data);
    }
    exit:
    return 0;
}