#include "CardEffectsModel.h"

using namespace CardTools;

CardEffectsModel::CardEffectsModel() {}
CardEffectsModel::~CardEffectsModel() {}
void CardEffectsModel::readFromParcel(Parcel*) {}
void CardEffectsModel::writeToParcel(Parcel*) {}

void CardEffectsModel::saveToFile(std::string filePath) {}
void CardEffectsModel::readFromFile(std::string filePath) {}

CardEffect* CardEffectsModel::addNew() { return nullptr; }
void CardEffectsModel::remove(CardEffect*) {}
std::list<CardEffect*> CardEffectsModel::getCardEffectList() { return std::list<CardEffect*>(); }