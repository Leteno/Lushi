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
    /**
     * Skip effect command sequence until we meet NONE
     */
    void skipInternal();
    bool assertTrue(bool detection);
public:
    EffectMachine(Effect effect);
    bool apply(std::stack<GameObject*> targetStack);

    /**
     * Command Sequence
     * | APPLY_FRIEND |
     * | --Commands-- |
     * |     LOOP     |
     * |Other Commands|
     *
     * GameObject stack:
     * | FRIEND 1 | // pop this out and apply Commands, meet LOOP, back to APPLY_FRIEND
     * |----------|
     * | FRIEND 2 | // pop this out and apply Commands, meet LOOP, back to APPLY_FRIEND
     * |----------|
     * |   NULL   | // pop this out, find out it is null, skip the Commands and LOOP
     * |----------|
     * |  OTHERS  | // pop this out, and apply <Other Commands>
     * |   ...    |
     */
    enum Code
    {
        LOOP = -6,
        APPLY_OTHER = -5,
        APPLY_ENEMY = -4,
        APPLY_FRIEND = -3,
        PUSH = -2,
        POP = -1,
        NONE = 0,
        ADD_HEALTH = 1,
        ADD_ATTACK = 2,
        SET_DISABLE = 3
    };
};