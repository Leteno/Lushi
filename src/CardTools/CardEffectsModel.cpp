
#include <iostream>
#include "../persist/FileDB.h"
#include "CardEffectsModel.h"

using namespace CardTools;

CardEffectsModel::CardEffectsModel()
{
    mList.clear();
}

CardEffectsModel::~CardEffectsModel() {}

void CardEffectsModel::readFromParcel(Parcel* parcel)
{
    mList.clear();
    if (parcel->meetEnd()) return;
    int size = parcel->readInt();
    for (int i = 0; i < size; ++i)
    {
        CardEffect effect;
        effect.readFromParcel(parcel);
        mList.push_back(effect);
    }
}

void CardEffectsModel::writeToParcel(Parcel* parcel)
{
    parcel->writeInt(mList.size());
    auto it = mList.begin();
    for (; it != mList.end(); ++it)
    {
        it->writeToParcel(parcel);
    }
}

void CardEffectsModel::saveToFile(std::string filePath)
{
    Parcel parcel(1024 * 20);
    writeToParcel(&parcel);
    int retCode = 0;
    persist::FileDB::saveToFile(filePath, parcel.toString(), &retCode);
    if (retCode != 0)
    {
        std::cout << "CardEffectsModel: Fail to saveToFile " << retCode;
    }
}

void CardEffectsModel::readFromFile(std::string filePath)
{
    int retCode = 0;
    std::string content = persist::FileDB::readFromFile(filePath, &retCode);
    if (retCode != 0)
    {
        std::cout << "CardEffectsModel: Fail to readFromFile " << retCode;
    }
    Parcel parcel(content);
    readFromParcel(&parcel);
}

CardEffect* CardEffectsModel::addNew()
{
    CardEffect effect;
    mList.push_back(effect);
    auto ret = mList.begin();
    std::advance(ret, mList.size() - 1);
    return &(*ret);
}

CardEffect* CardEffectsModel::add(CardEffect effect)
{
    mList.push_back(effect);
    auto ret = mList.begin();
    std::advance(ret, mList.size() - 1);
    return &(*ret);
}

bool CardEffectsModel::remove(CardEffect* effect)
{
    if (effect == nullptr) return false;
    auto it = mList.begin();
    for (; it != mList.end(); ++it)
    {
        if (&(*it) == effect)
        {
            mList.erase(it);
            return true;
        }
    }
    return false;
}

std::list<CardEffect*> CardEffectsModel::getCardEffectList()
{
    std::list<CardEffect*> result;

    auto it = mList.begin();
    for (; it != mList.end(); ++it)
    {
        result.push_back(&(*it));
    }
    return result;
}