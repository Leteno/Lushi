
#include "FrameState.h"

using namespace frame;

FrameState::FrameState()
    : mFSM(fsm::FSM<std::string, std::string>("Init"))
{}

bool FrameState::accept(std::string instruction)
{
    return mFSM.accept(instruction);
}

bool FrameState::addPath(std::string from,
                        std::string inst,
                        std::string to)
{
    return mFSM.addPath(from, inst, to);
}

void FrameState::mapFrame(std::string stateCode, Frame* frame)
{
    mFrameMap[stateCode] = frame;
}

Frame* FrameState::getCurrentFrame()
{
    std::string curState = mFSM.getCurrentState();
    return mFrameMap[curState];
}