#pragma once

class GameObject
{
private:
    int m_Health;
    int m_Attack;
    int m_CurrentHealth;
    int m_CurrentAttack;
public:
    GameObject(int health, int attack);
    void addHealth(int increment);
    void addAttack(int increment);
    void setDisable();

    int getHealth();
    int getAttack();
};