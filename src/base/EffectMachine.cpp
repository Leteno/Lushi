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
}

bool EffectMachine::apply(std::stack<GameObject*> targetStack)
{
    m_It = m_Command.begin();
    m_End = m_Command.end();

    GameObject* currentObj;
    std::string::iterator mark;
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
            if (currentObj == nullptr)
            {
                skipInternal();
            }
            else
            {
                applyInternal(currentObj);
            }
            break;
        case Code::PUSH:
            targetStack.push(currentObj);
            break;
        case Code::APPLY_FRIEND:
        case Code::APPLY_ENEMY:
        case Code::APPLY_OTHER:
            mark = m_It;
            ++m_It;
            currentObj = targetStack.top(); targetStack.pop();
            if (currentObj == nullptr)
            {
                skipInternal();
            }
            else
            {
                applyInternal(currentObj);
            }
            goto CONTINUE;
        case Code::LOOP:
            m_It = mark;
            goto CONTINUE;
        }
        ++m_It;
        CONTINUE:;
    }
    return true;
}

/*
 * After invoke, this will leave NONE, LOOP
 * However, in main flow, we got '++m_It' after invoke skipInternal()
 * which means: it will handle this for us.
 */
void EffectMachine::skipInternal()
{
    GameObject ignore(2, 3);
    applyInternal(&ignore);
    ++m_It; // SKIP NONE/LOOP
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
            case LOOP:
                // When meet these code, leave it to parent
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