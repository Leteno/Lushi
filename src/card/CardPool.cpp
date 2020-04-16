
#include <assert.h>

#include "CardPool.h"

using namespace card;

CardPool::CardPool() {}

CardPool::~CardPool() {}

void CardPool::readFromParcel(Parcel* parcel)
{
    this->cards.empty();

    int count = parcel->readInt();
    for (int i = 0; i < count; i++)
    {
        Card card;
        card.readFromParcel(parcel);
        this->cards.push_back(card);
    }
}

void CardPool::writeToParcel(Parcel* parcel)
{
    parcel->writeInt(this->cards.size());
    for (auto it = this->cards.begin();
        it != this->cards.end();
        ++it)
    {
        it->writeToParcel(parcel);
    }
}

void CardPool::addCard(Card card)
{
    this->cards.push_back(card);
}

Card CardPool::get(int index)
{
    assert(index < this->cards.size());
    auto it = this->cards.begin();
    std::advance(it, index);
    return *it;
}

int CardPool::count()
{
    return this->cards.size();
}
