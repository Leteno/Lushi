
#include <SFML/Graphics.hpp>

#include "SampleFrame.h"

using namespace frame::view;

SampleFrame::SampleFrame(sf::Color color)
{
    sf::CircleShape* shape = new sf::CircleShape(100.f);
    shape->setFillColor(color);
    mDrawable = shape;
}
SampleFrame::~SampleFrame()
{
    delete mDrawable;
}

bool SampleFrame::ReceiveEvent(Event event)
{
    if (event.type == Event::RELEASED &&
        event.code == Event::LEFT)
    {
        mNextFrame = true;
        return true;
    }
    return false;
}

void SampleFrame::DoLogic(FrameState* state, GlobalData* data)
{
    if (mNextFrame)
    {
        mNextFrame = false;
        state->accept("next");
    }
}

void SampleFrame::draw(sf::RenderTarget* target, GlobalData * data)
{
    target->clear();
    target->draw(*mDrawable);
}
