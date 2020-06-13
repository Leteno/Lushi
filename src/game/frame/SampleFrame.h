#pragma once

#include <SFML/Graphics.hpp>

#include "Event.h"
#include "Frame.h"

namespace frame {
class SampleFrame : public Frame
{
public:
    SampleFrame(sf::Color color);
    ~SampleFrame();
    bool ReceiveEvent(Event e) override;
    void DoLogic(FrameState* state, GlobalData* data) override;
    sf::Drawable* getDrawable(GlobalData* data) override;

private:
    sf::Drawable*   mDrawable;
    bool            mNextFrame;
};
}
