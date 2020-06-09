#pragma once

#include <SFML/Graphics.hpp>

#include "Frame.h"

namespace frame {
class SampleFrame : Frame
{
public:
    SampleFrame(sf::Color color);
    ~SampleFrame();
    void DoLogic(FrameState* state, GlobalData* data) override;
    sf::Drawable* getDrawable(GlobalData* data) override;
private:
    sf::Drawable* mDrawable;
};
}
