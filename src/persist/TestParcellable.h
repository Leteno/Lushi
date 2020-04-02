#pragma once

#include <string>

#include "../unit_test/UT.h"
#include "Parcellable.h"

UT::Report testParcellable();

namespace persist {

    class TestParcellableChild : Parcellable {
    public:
        TestParcellableChild(int a, int b);
        TestParcellableChild(Parcel*);
        void writeToParcel(Parcel*);
        int a;
        int b;
    };

    class TestParcellable : Parcellable {
    public:
        TestParcellable(int i, double d, std::string s, TestParcellableChild tc, int i2);
        TestParcellable(Parcel*);
        void writeToParcel(Parcel*);
        int i;
        double d;
        std::string s;
        TestParcellableChild tc;
        int iAgain;
    };
}