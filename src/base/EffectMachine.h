#include "GameObject.h"
#include "Effect.h"

class EffectMachine
{
private:
    Effect m_Effect;
    std::string m_Command;
    std::string::iterator m_It;
    std::string::iterator m_End;
    /**
     * apply the `effect` to `target`
     */
    void applyInternal(GameObject* target);
    bool assertTrue(bool detection);
public:
    EffectMachine(Effect effect);
    bool apply(std::stack<GameObject*> targetStack);

    enum Code
    {
        PUSH = -2,
        POP = -1,
        NONE = 0,
        ADD_HEALTH = 1,
        ADD_ATTACK = 2,
        SET_DISABLE = 3
    };
};