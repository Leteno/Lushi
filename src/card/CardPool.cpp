#include "CardPool.h"

using namespace card;

CardPool::CardPool() {}
CardPool::~CardPool() {}
void CardPool::readFromParcel(Parcel*) {}
void CardPool::writeToParcel(Parcel*) {}
void CardPool::addCard(Card card) {}
Card CardPool::get(int index) { return Card(); }
int CardPool::count() { return -1; }
