#include <assert.h>
#include <stack>
#include <string>

#include "GameObject.h"
#include "EffectMachine.h"

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
    m_CurrentHealth = m_Health;
    m_CurrentAttack = m_Attack;

    // clear effectOnce
    m_EffectOnce.clear();

    // reapply effectConstant
    for (auto it = m_EffectConstant.begin();
        it != m_EffectConstant.end();
        ++it)
    {
        std::stack<GameObject*> s; s.push(this);
        EffectMachine(*it).apply(s);
    }
}

void GameObject::applyEffect(GameObject * obj, Effect::TYPE type, Effect effect)
{
    assert(obj);
    switch (type)
    {
    case Effect::TYPE::ONCE:
        obj->m_EffectOnce.push_back(effect);
        break;
    case Effect::TYPE::BUFF:
        obj->m_EffectConstant.push_back(effect);
        break;
    }
    std::stack<GameObject*> s; s.push(obj);
    EffectMachine(effect).apply(s);
}

std::string GameObject::showEffectList()
{
    std::string result;
    for (auto it = m_EffectOnce.begin(); it != m_EffectOnce.end(); ++it)
    {
        Effect effect = *it;
        result.append(effect.description());
        result.append("\n");
    }

    for (auto it = m_EffectConstant.begin(); it != m_EffectConstant.end(); ++it)
    {
        Effect effect = *it;
        result.append(effect.description());
        result.append("\n");
    }
    return result;
}

int GameObject::getHealth()
{
    return m_CurrentHealth;
}

int GameObject::getAttack()
{
    return m_CurrentAttack;
}