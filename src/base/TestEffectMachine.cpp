#include <iostream>
#include <sstream>
#include <stack>
#include "stdio.h"

#include "Effect.h"
#include "EffectMachine.h"
#include "GameObject.h"

bool testAddHealth();
bool testAddAttach();
bool testBoth();
bool testDisable();
bool concatCommand(std::string& command, int code);
bool assertTrue(bool detection, std::string errorMessage);

int main()
{
    bool pass = true;
    pass = testAddHealth() && pass;
    pass = testAddAttach() && pass;
    pass = testBoth() && pass;
    pass = testDisable() && pass;
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

bool testDisable()
{
    std::string addHealthDesc("Add 1 Health");
    std::string addHealthCommand; addHealth(addHealthCommand, 1);
    Effect addHealthEffect(addHealthDesc, addHealthCommand, addHealthDesc);

    std::string addAttackDesc("Add 1 Attack");
    std::string addAttackCommand; addAttack(addAttackCommand, 1);
    Effect addAttackEffect(addAttackDesc, addAttackCommand, addAttackDesc);

    GameObject me(2, 3);
    GameObject::applyEffect(&me, Effect::TYPE::ONCE, addHealthEffect);
    GameObject::applyEffect(&me, Effect::TYPE::BUFF, addAttackEffect);
    bool result = assertTrue(me.getAttack() == 4, "Error: attack is not 4\n");
    result = assertTrue(me.getHealth() == 3, "Error: health is not 3\n") && result;

    std::string expectDesc;
    expectDesc.append(addHealthDesc); expectDesc.append("\n");
    expectDesc.append(addAttackDesc); expectDesc.append("\n");
    std::string currentDesc = me.showEffectList();
    std::stringstream error_message;
    error_message << "desc not equal: \"" << expectDesc << "\"\n ===== \n\"" << currentDesc << "\"";
    result = assertTrue(expectDesc.compare(currentDesc) == 0, error_message.str()) && result;

    me.setDisable();
    result = assertTrue(me.getAttack() == 4, "Error: after disabled, attack should be 4\n") && result;
    result = assertTrue(me.getHealth() == 2, "Error: after disabled, attach should be 2") && result;
    std::string expectDesc2; expectDesc2.append(addAttackDesc); expectDesc2.append("\n");
    std::string currentDesc2 = me.showEffectList();
    std::stringstream error_message2;
    error_message2 << "after disable, desc not equal: \"" << expectDesc2 << "\"\n ===== \n\"" << currentDesc2 << "\"";
    result = assertTrue(expectDesc2.compare(currentDesc2) == 0, error_message2.str()) && result;

    return result;
}

bool concatCommand(std::string& command, int code)
{
    command.append(1, code);
}

bool assertTrue(bool detection, std::string errorMessage)
{
    if (!detection)
    {
        std::cout << errorMessage << std::endl;
    }
    return detection;
}