#pragma once

#include <map>

#include "RoadMap.h"

namespace fsm {

template <typename State, typename Instruction>
class FSM {
public:
    FSM() :
        mMap(std::map<State, RoadMap<State, Instruction>*>())
     {};
    ~FSM()
    {
        auto it = mMap.begin();
        for (; it != mMap.end(); ++it)
        {
            delete it->second;
        }
    }

    State getCurrentState()
    {
        return mCurrent;
    }

    bool addPath(State from, Instruction inst, State to)
    {
        return getOrCreateRoadMap(from)->addPath(inst, to);
    }

    bool accept(Instruction inst)
    {
        RoadMap<State, Instruction>* roadMap = getOrCreateRoadMap(mCurrent);
        State tmp;
        bool success = roadMap->accept(inst, &tmp);
        if (success)
        {
            mCurrent = tmp;
        }
        return success;
    }

    void beginAt(State begin)
    {
        mCurrent = begin;
    }

private:
    State mCurrent;
    std::map<State, RoadMap<State, Instruction>*> mMap;

    RoadMap<State, Instruction>* getOrCreateRoadMap(State from)
    {
        auto f = mMap.find(from);
        if (f == mMap.end())
        {
            mMap[from] = new RoadMap<State, Instruction>();
        }
        return mMap[from];
    }
};
}


