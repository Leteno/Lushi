
#include <SFML/Graphics.hpp>

#include "SampleFrame.h"

using namespace frame;

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

void SampleFrame::ReceiveEvent(Event event)
{
    if (event.type == Event::RELEASED &&
        event.code == Event::LEFT)
    {
        mNextFrame = true;
    }
}

void SampleFrame::DoLogic(FrameState* state, GlobalData* data)
{
    if (mNextFrame)
    {
        mNextFrame = false;
        state->state = FrameState::NEXT;
    }
}

sf::Drawable* SampleFrame::getDrawable(GlobalData* data)
{
    return mDrawable;
}