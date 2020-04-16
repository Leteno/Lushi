#pragma once

#include <list>

#include "../persist/Parcel.h"
#include "../persist/Parcellable.h"

using namespace persist;

#include "Card.h"

namespace card {
    class CardPool : Parcellable {
    public:
        CardPool();
        ~CardPool();
        void readFromParcel(Parcel*);
        void writeToParcel(Parcel*);

        void addCard(Card card);
    private:
        std::list<Card> cards;
    };
}