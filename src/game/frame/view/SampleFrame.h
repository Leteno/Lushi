#pragma once

#include <SFML/Graphics.hpp>

#include "../Event.h"
#include "../Frame.h"

namespace frame::view {
class SampleFrame : public Frame
{
public:
    SampleFrame(sf::Color color);
    ~SampleFrame();
    bool ReceiveEvent(Event e) override;
    void DoLogic(FrameState* state, GlobalData* data) override;
    void draw(sf::RenderTarget* target, GlobalData * data) override;

private:
    sf::Drawable*   mDrawable;
    bool            mNextFrame;
};
}
