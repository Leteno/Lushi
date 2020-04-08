#pragma once

#include <string>

#include "../unit_test/UT.h"
#include "Parcellable.h"

UT::Report testParcellable();

namespace persist {

    class TestParcellableChild : Parcellable {
    public:
        TestParcellableChild();
        TestParcellableChild(int a, int b);
        void readFromParcel(Parcel*);
        void writeToParcel(Parcel*);
        int a;
        int b;
    };

    class TestParcellable : Parcellable {
    public:
        TestParcellable();
        TestParcellable(int i, double d, std::string s, TestParcellableChild tc, int i2);
        void readFromParcel(Parcel*);
        void writeToParcel(Parcel*);
        int i;
        double d;
        std::string s;
        TestParcellableChild tc;
        int iAgain;
    };
}