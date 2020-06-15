#include <assert.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "frame/Event.h"
#include "frame/Frame.h"
#include "frame/FrameState.h"
#include "frame/GlobalData.h"
#include "frame/view/SampleFrame.h"

frame::FrameState state;
frame::GlobalData data;

void initFrameState(frame::FrameState* state);
void cleanUp();

void renderThread(sf::RenderWindow* window)
{
    window->setActive(true);

    while (window->isOpen())
    {
        sf::Event event;
        frame::Frame* curFrame = state.getCurrentFrame();
        assert(curFrame);
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                return;
            }

            curFrame->ReceiveEvent(frame::Event::from(event));
        }
        curFrame->DoLogic(&state, &data);
        window->clear();
        window->draw(*curFrame->getDrawable(&data));
        window->display();
    }
}

int main()
{
    initFrameState(&state);

    sf::RenderWindow window(sf::VideoMode(550, 400), "Game!");
    window.setActive(false);

    sf::Thread thread(&renderThread, &window);
    thread.launch();

    thread.wait();

    cleanUp();

    return 0;
}

void initFrameState(frame::FrameState* state)
{
    frame::view::SampleFrame* f1 = new frame::view::SampleFrame(sf::Color::Blue);
    frame::view::SampleFrame* f2 = new frame::view::SampleFrame(sf::Color::Red);
    state->mapFrame("Init", f2);
    state->mapFrame("F1", f1);
    state->mapFrame("F2", f2);
    state->addPath("Init", "next", "F1");
    state->addPath("F1", "next", "F2");
    state->addPath("F2", "next", "F1");
    state->beginAt("Init");
}

void cleanUp()
{
    // TODO free f1, f2
}