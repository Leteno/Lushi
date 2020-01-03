#include "GameObject.h"

GameObject::GameObject(int health, int attack)
{
    m_Health = health; m_Attack = attack;
    m_CurrentHealth = health; m_CurrentAttack = attack;
}

void GameObject::addHealth(int increament)
{
    m_CurrentHealth += increament;
}

void GameObject::addAttack(int increment)
{
    m_CurrentAttack += increment;
}

void GameObject::setDisable()
{
    // clear current effect.
}

int GameObject::getHealth()
{
    return m_CurrentHealth;
}

int GameObject::getAttack()
{
    return m_CurrentAttack;
}