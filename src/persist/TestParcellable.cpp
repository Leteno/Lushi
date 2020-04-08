
#include "Parcel.h"
#include "Parcellable.h"
#include "TestParcellable.h"

using namespace persist;

UT::Report testParcellable()
{
    UT::Report report;

    TestParcellableChild child(123, 456);
    TestParcellable father(234, 1.0, "I am your father", child, 345);
    Parcel parcel(1024);
    father.writeToParcel(&parcel);
    TestParcellable stranger;
    stranger.readFromParcel(&parcel);

    report.addTest(UT::Test::assertEquals(stranger.i, 234));
    report.addTest(UT::Test::assertEquals(stranger.d, 1.0));
    report.addTest(UT::Test::assertEquals(stranger.s, "I am your father"));
    report.addTest(UT::Test::assertEquals(stranger.iAgain, 345));
    report.addTest(UT::Test::assertEquals(stranger.tc.a, 123));
    report.addTest(UT::Test::assertEquals(stranger.tc.b, 456));
    report.addTest(UT::Test::assertTrue(parcel.meetEnd()));

    return report;
}

TestParcellable::TestParcellable() {}

TestParcellable::TestParcellable(int i, double d, std::string s, TestParcellableChild tc, int i2)
    : i(i), d(d), s(s), tc(tc), iAgain(i2)
{}

void TestParcellable::readFromParcel(Parcel* parcel) {
    this->i = parcel->readInt();
    this->d = parcel->readDouble();
    this->s = parcel->readString();
    this->tc.readFromParcel(parcel);
    this->iAgain = parcel->readInt();
}

void TestParcellable::writeToParcel(Parcel* parcel)
{
    parcel->writeInt(this->i);
    parcel->writeDouble(this->d);
    parcel->writeString(this->s);
    this->tc.writeToParcel(parcel);
    parcel->writeInt(this->iAgain);
}

TestParcellableChild::TestParcellableChild() {}

TestParcellableChild::TestParcellableChild(int a, int b)
    : a(a), b(b) {}

void TestParcellableChild::readFromParcel(Parcel* parcel)
{
    this->a = parcel->readInt();
    this->b = parcel->readInt();    
}

void TestParcellableChild::writeToParcel(Parcel* parcel)
{
    parcel->writeInt(this->a);
    parcel->writeInt(this->b);
}
