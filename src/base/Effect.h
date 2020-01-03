#pragma once
#include <string>

class Effect
{
private:
    std::string m_Name;
    std::string m_CommandStream;
    std::string m_Desc;
    bool m_IsDisabled;
    Effect* m_Next;
public:
    Effect(std::string name, std::string commandStream, std::string desc);
    std::string description();
    void setDisable(bool disable);
    std::string getCommand();

    enum TYPE
    {
        ONCE = 1,
        BUFF = 2,
    };
};