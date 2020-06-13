#pragma once

#include <SFML/Graphics.hpp>

#include "Event.h"
#include "FrameState.h"
#include "GlobalData.h"

namespace frame {
class FrameState;
class Frame
{
public:
    Frame();
    ~Frame();
    virtual bool ReceiveEvent(Event event) = 0;
    virtual void DoLogic(FrameState* state, GlobalData* data) = 0;
    virtual sf::Drawable* getDrawable(GlobalData* data) = 0;
};
}
