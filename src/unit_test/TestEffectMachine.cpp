#include <stack>
#include "stdio.h"

#include "../base/Effect.h"
#include "../base/EffectMachine.h"
#include "../base/GameObject.h"

bool testAddHealth();
bool testAddAttach();
bool testBoth();
bool concatCommand(std::string& command, int code);
bool assertTrue(bool detection, std::string errorMessage);

int main()
{
    bool pass = true;
    pass |= testAddHealth();
    pass |= testAddAttach();
    pass |= testBoth();
    printf("pass: %s\n", pass ? "pass" : "fail");
    return pass ? 0 : 1;
}

void addHealth(std::string& command, int increament)
{
    concatCommand(command, EffectMachine::Code::POP);
    concatCommand(command, EffectMachine::Code::ADD_HEALTH);
    concatCommand(command, increament);
    concatCommand(command, EffectMachine::Code::NONE);
}

void addAttack(std::string& command, int increment)
{
    concatCommand(command, EffectMachine::Code::POP);
    concatCommand(command, EffectMachine::Code::ADD_ATTACK);
    concatCommand(command, 1);
    concatCommand(command, EffectMachine::Code::NONE);
}

bool testAddHealth()
{
    std::string command;
    addHealth(command, 1);
    Effect effect(std::string("Add Health"), command, std::string("Add 1 Health"));
    EffectMachine machine(effect);
    GameObject me(2, 3);
    std::stack<GameObject*> s;
    s.push(&me);
    machine.apply(s);
    return assertTrue(me.getHealth() == 3, "Error: health is not 3\n");
}

bool testAddAttach()
{
    std::string command;
    addAttack(command, 1);
    Effect effect(std::string("Add Attack"), command, std::string("Add 1 Attach"));
    EffectMachine machine(effect);
    GameObject me(2, 3);
    std::stack<GameObject*> s;
    s.push(&me);
    machine.apply(s);
    return assertTrue(me.getAttack() == 4, "Error: attack is not 4\n");
}

bool testBoth()
{
    std::string command;
    addAttack(command, 1);
    concatCommand(command, EffectMachine::Code::PUSH);
    addHealth(command, 1);
    Effect effect(std::string("Add Attack and Health"), command, std::string("Add 1 Attach and 1 Health"));
    EffectMachine machine(effect);
    GameObject me(2, 3);
    std::stack<GameObject*> s;
    s.push(&me);
    machine.apply(s);
    return assertTrue(me.getAttack() == 4, "Error: attack is not 4\n") &&
            assertTrue(me.getHealth() == 3, "Error: health is not 3\n");
}

bool concatCommand(std::string& command, int code)
{
    command.append(1, code);
}

bool assertTrue(bool detection, std::string errorMessage)
{
    if (!detection)
    {
        printf(errorMessage.c_str());
    }
    return detection;
}