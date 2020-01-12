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
Report testSkip();
Report testMulti();
Effect addFriend1HealthDecEnemy1Attack();
void addHealth(std::string& command, int increament);
void addAttack(std::string& command, int increment);
bool concatCommand(std::string& command, int code);

int main()
{
    Report report;
    report.mergeReport(testAddHealth());
    report.mergeReport(testAddAttach());
    report.mergeReport(testBoth());
    report.mergeReport(testDisable());
    report.mergeReport(testSkip());
    report.mergeReport(testMulti());
    Result result = report.getResult();
    std::cout << result.toString();
    return result.totalPass() ? 0 : 1;
}

Report testAddHealth()
{
    Report report;
    std::string command; addHealth(command, 1);
    Effect effect(std::string("Add Health"), command, std::string("Add 1 Health"));
    GameObject me(2, 3);
    GameObject::applyEffect(&me, Effect::TYPE::BUFF, effect);
    report.addTest(Test::assertEquals(me.getHealth(), 3));
    return report;
}

Report testAddAttach()
{
    Report report;
    std::string command;
    addAttack(command, 1);
    Effect effect(std::string("Add Attack"), command, std::string("Add 1 Attach"));
    GameObject me(2, 3);
    GameObject::applyEffect(&me, Effect::TYPE::BUFF, effect);
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
    GameObject me(2, 3);
    GameObject::applyEffect(&me, Effect::TYPE::BUFF, effect);
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

Report testSkip()
{
    Report report;

    Effect effect = addFriend1HealthDecEnemy1Attack();
    EffectMachine mac(effect);

    GameObject enemy(1, 3);
    std::stack<GameObject*> enemyOnly;
    enemyOnly.push(nullptr); // end of enemy
    enemyOnly.push(&enemy);
    enemyOnly.push(nullptr); // end of friends
    mac.apply(enemyOnly);
    report.addTest(Test::assertEquals(enemy.getAttack(), 2)); // 3 -1
    report.addTest(Test::assertEquals(enemy.getHealth(), 1)); // remain

    GameObject friend1(2, 3);
    GameObject friend2(3, 4);
    std::stack<GameObject*> friendOnly;
    friendOnly.push(nullptr); // end of enemy
    friendOnly.push(nullptr); // end of friends
    friendOnly.push(&friend2);
    friendOnly.push(&friend1);

    mac.apply(friendOnly);
    report.addTest(Test::assertEquals(friend1.getHealth(), 3)); // 2 +1
    report.addTest(Test::assertEquals(friend1.getAttack(), 3)); // remain
    report.addTest(Test::assertEquals(friend2.getHealth(), 4)); // 3 +1
    report.addTest(Test::assertEquals(friend2.getAttack(), 4)); // remain
    return report;
}

Report testMulti()
{
    Report report;
    return report;
}

Effect addFriend1HealthDecEnemy1Attack()
{
    std::string command;
    concatCommand(command, EffectMachine::Code::APPLY_FRIEND);
    concatCommand(command, EffectMachine::Code::ADD_HEALTH);
    concatCommand(command, 1);
    concatCommand(command, EffectMachine::Code::LOOP);

    concatCommand(command, EffectMachine::Code::APPLY_ENEMY);
    concatCommand(command, EffectMachine::Code::ADD_ATTACK);
    concatCommand(command, -1);
    concatCommand(command, EffectMachine::Code::LOOP);

    std::string name("addFriend1HealthDecEnemy1Attack");
    return Effect(name, command, name);
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

bool concatCommand(std::string& command, int code)
{
    command.append(1, code);
}
