#include <assert.h>
#include <stack>
#include <string>

#include "GameObject.h"
#include "Effect.h"
#include "EffectMachine.h"

EffectMachine::EffectMachine(Effect effect)
    : m_Effect(effect)
{
    m_Command = m_Effect.getCommand();
    m_It = m_Command.begin();
    m_End = m_Command.end();
}

bool EffectMachine::apply(std::stack<GameObject*> targetStack)
{
    GameObject* currentObj;
    while (m_It != m_End)
    {
        switch (*m_It)
        {
        case Code::NONE:
            // The flow for currentObj is finished
            currentObj = nullptr;
            break;
        case Code::POP:
            currentObj = targetStack.top();
            targetStack.pop();
            ++m_It;
            applyInternal(currentObj);
            break;
        case Code::PUSH:
            targetStack.push(currentObj);
            break;
        }
        ++m_It;
    }
    return true;
}

void EffectMachine::applyInternal(GameObject* target)
{
    assertTrue(target);
    while (m_It != m_End)
    {
        switch(*m_It)
        {
            case NONE:
            case PUSH:
            case POP:
                return;
            case ADD_HEALTH:
                ++m_It;
                assertTrue(m_It != m_End);
                target->addHealth(*m_It);
                break;
            case ADD_ATTACK:
                ++m_It;
                assertTrue(m_It != m_End);
                target->addAttack(*m_It);
                break;
            case SET_DISABLE:
                target->setDisable();
                break;
        }
        ++m_It;
    }
}

bool EffectMachine::assertTrue(bool detection)
{
    if (!detection)
    {
        printf("we are not at: %c", *m_It);
    }
    assert(detection);
}