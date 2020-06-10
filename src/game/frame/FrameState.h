#pragma once

namespace frame{
class FrameState
{
public:
    enum State {
        NORMAL,
        NEXT,
    };

    FrameState() : state(State::NORMAL) {}

    State state;
};
}