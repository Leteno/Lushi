#include <sstream>
#include "Effect.h"

Effect::Effect(std::string name, std::string commandStream, std::string desc)
    : m_Name(name), m_CommandStream(commandStream), m_Desc(desc), m_Next(nullptr) {}

std::string Effect::description()
{
    std::stringstream ss;
    ss << m_Desc;
    Effect* next = m_Next;
    while (next)
    {
        ss << ", " << next->description();
        next = next->m_Next;
    }
    return ss.str();
}

void Effect::setDisable(bool disable)
{
    m_IsDisabled = disable;
}

std::string Effect::getCommand()
{
    return m_CommandStream;
}