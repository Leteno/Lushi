#pragma once

#include <map>

namespace fsm {
template<class State, class Instruction>
class RoadMap {
public:
    RoadMap()
        : mMap(std::map<Instruction, State>())
     {}

    bool addPath(Instruction inst, State to)
    {
        if(mMap.find(inst) != mMap.end())
        {
            return false;
        }
        mMap[inst] = to;
        return true;
    }

    bool accept(Instruction inst, State* out)
    {
        auto f = mMap.find(inst);
        if (f != mMap.end())
        {
            if (out != nullptr)
            {
                *out = f->second;
            }
            return true;
        }
        return false;
    }

private:
    std::map<Instruction, State> mMap;
};
}

