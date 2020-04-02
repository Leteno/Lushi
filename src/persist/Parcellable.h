#pragma once

#include "Parcel.h"

namespace persist {
    class Parcellable {
    public:
        Parcellable();
        virtual void writeToParcel(Parcel*);
        virtual ~Parcellable();
    };
}