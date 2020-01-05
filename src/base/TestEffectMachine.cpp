#include <iostream>
#include <sstream>
#include <stack>
#include "stdio.h"

#include "../unit_test/UT.h"

#include "Effect.h"
#include "EffectMachine.h"
#include "GameObject.h"

using namespace UT;

Report testAddHealth();
Report testAddAttach();
Report testBoth();
Report testDisable();
bool concatCommand(std::string& command, int code);

int main()
{
    Report report;
    report.mergeReport(testAddHealth());
    report.mergeReport(testAddAttach());
    report.mergeReport(testBoth());
    report.mergeReport(testDisable());
    Result result = report.getResult();
    std::cout << result.toString();
    return result.totalPass() ? 0 : 1;
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

Report testAddHealth()
{
    Report report;
    std::string command; addHealth(command, 1);
    Effect effect(std::string("Add Health"), command, std::string("Add 1 Health"));
    EffectMachine machine(effect);
    GameObject me(2, 3);
    std::stack<GameObject*> s;
    s.push(&me);
    machine.apply(s);
    report.addTest(Test::assertEquals(me.getHealth(), 3));
    return report;
}

Report testAddAttach()
{
    Report report;
    std::string command;
    addAttack(command, 1);
    Effect effect(std::string("Add Attack"), command, std::string("Add 1 Attach"));
    EffectMachine machine(effect);
    GameObject me(2, 3);
    std::stack<GameObject*> s;
    s.push(&me);
    machine.apply(s);
    report.addTest(Test::assertEquals(me.getAttack(), 4));
    return report;
}

Report testBoth()
{
    Report report;
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
    report.addTest(Test::assertEquals(me.getAttack(), 4));
    report.addTest(Test::assertEquals(me.getHealth(), 3));
    return report;
}

Report testDisable()
{
    Report report;
    std::string addHealthDesc("Add 1 Health");
    std::string addHealthCommand; addHealth(addHealthCommand, 1);
    Effect addHealthEffect(addHealthDesc, addHealthCommand, addHealthDesc);

    std::string addAttackDesc("Add 1 Attack");
    std::string addAttackCommand; addAttack(addAttackCommand, 1);
    Effect addAttackEffect(addAttackDesc, addAttackCommand, addAttackDesc);

    GameObject me(2, 3);
    GameObject::applyEffect(&me, Effect::TYPE::ONCE, addHealthEffect);
    GameObject::applyEffect(&me, Effect::TYPE::BUFF, addAttackEffect);
    report.addTest(Test::assertEquals(me.getAttack(), 4));
    report.addTest(Test::assertEquals(me.getHealth(), 3));

    std::string expectDesc;
    expectDesc.append(addHealthDesc); expectDesc.append("\n");
    expectDesc.append(addAttackDesc); expectDesc.append("\n");
    std::string currentDesc = me.showEffectList();
    report.addTest(Test::assertEquals(expectDesc, currentDesc));

    me.setDisable();
    report.addTest(Test::assertEquals(me.getAttack(), 4));
    report.addTest(Test::assertEquals(me.getHealth(), 2));
    std::string expectDesc2; expectDesc2.append(addAttackDesc); expectDesc2.append("\n");
    std::string currentDesc2 = me.showEffectList();
    report.addTest(Test::assertEquals(expectDesc2, currentDesc2));

    return report;
}

bool concatCommand(std::string& command, int code)
{
    command.append(1, code);
}
