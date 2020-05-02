#pragma once

#include <list>
#include <string>

#include "../machine/Sequence.h"

#include "../persist/Parcel.h"
#include "../persist/Parcellable.h"

using namespace persist;
using namespace machine;

namespace card {
class CardEffect : Parcellable {
    public:
        CardEffect();
        ~CardEffect();
        void readFromParcel(Parcel*);
        void writeToParcel(Parcel*);

        void setOriginalCode(std::string newCode) { originalCode = newCode; }
        std::string getOriginalCode() { return originalCode; }
        void setInstructionList(std::list<Sequence::Instruction> newCodes) { instructionList = newCodes; }
        std::list<Sequence::Instruction> getInstructionList() { return instructionList; }
    private:
        std::string originalCode;
        std::list<Sequence::Instruction> instructionList;
};
}