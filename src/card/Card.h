#pragma once

#include "../persist/Parcel.h"
#include "../persist/Parcellable.h"

#include "CardEffect.h"

using namespace persist;

namespace card {
    class Card : Parcellable {
    public:
        Card();
        ~Card();
        void readFromParcel(Parcel*);
        void writeToParcel(Parcel*);

        std::string name;
        CardEffect cardEffect;
    };
}