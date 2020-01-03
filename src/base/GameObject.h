#pragma once

#include <vector>
#include "Effect.h"

class GameObject
{
private:
    int m_Health;
    int m_Attack;
    int m_CurrentHealth;
    int m_CurrentAttack;
    std::vector<Effect> m_EffectOnce;

    std::vector<Effect> m_EffectConstant;
public:
    GameObject(int health, int attack);
    void addHealth(int increment);
    void addAttack(int increment);
    void setDisable();
    static void applyEffect(GameObject* obj, Effect::TYPE type, Effect effect);
    std::string showEffectList();

    int getHealth();
    int getAttack();
};