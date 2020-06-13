#pragma once

#include <map>
#include <string>

#include "../fsm/FSM.h"
#include "Frame.h"

namespace frame{
class Frame;
const static std::string sInit = "Init";
class FrameState
{
public:
    FrameState();

    bool accept(std::string instruction);
    bool addPath(std::string from, std::string instruction, std::string to);
    void beginAt(std::string begin);
    void mapFrame(std::string stateCode, Frame* frame);
    Frame* getCurrentFrame();

private:
    std::map<std::string, Frame*> mFrameMap;
    fsm::FSM<std::string, std::string> mFSM;
};
}