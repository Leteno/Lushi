#pragma once

#include "../card/CardEffect.h"
#include "../persist/FileDB.h"
#include "../persist/Parcel.h"
#include "../persist/Parcellable.h"

using namespace card;
using namespace persist;

namespace CardTools {
    class CardEffectsModel : Parcellable {
    public:
        CardEffectsModel();
        ~CardEffectsModel();
        void readFromParcel(Parcel*);
        void writeToParcel(Parcel*);

        void saveToFile(std::string filePath);
        void readFromFile(std::string filePath);

        CardEffect* addNew();
        CardEffect* add(CardEffect);
        bool remove(CardEffect*);
        std::list<CardEffect*> getCardEffectList();

    private:
        std::list<CardEffect> mList;
    };
}