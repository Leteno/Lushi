#pragma once

#include <SFML/Graphics.hpp>

#include "FrameState.h"
#include "GlobalData.h"

namespace frame {
class Frame
{
public:
    Frame();
    ~Frame();
    virtual void DoLogic(FrameState* state, GlobalData* data);
    virtual sf::Drawable* getDrawable(GlobalData* data);
};
}
