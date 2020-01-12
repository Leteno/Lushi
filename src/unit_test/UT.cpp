#include "UT.h"
#include "string.h"
#include <string>
#include <sstream>

namespace UT {

void Report::mergeReport(Report r)
{
    m_TotalCount += r.m_TotalCount;
    m_PassCount += r.m_PassCount;

    m_TestList.insert(m_TestList.end(),
        r.m_TestList.begin(),
        r.m_TestList.end());
}

void Report::addTest(Test t)
{
    ++m_TotalCount;
    if (t.m_Pass)
    {
        ++m_PassCount;
    }
    m_TestList.push_back(t);
}

Result Report::getResult()
{
    Result r;
    r.m_TotalCount = m_TotalCount;
    r.m_PassCount = m_PassCount;
    if (m_PassCount != m_TotalCount)
    {
        std::stringstream ss;
        for (auto it = m_TestList.begin();
             it != m_TestList.end();
             ++it)
        {
            if (!(*it).m_Pass)
            {
                ss << (*it).m_ErrorMessage;
            }
        }
        r.m_Text = ss.str();
    }
    return r;
}

Test Test::assertEquals(char* a, char* b)
{
    Test t;
    t.m_Pass = strcmp(a, b) == 0;
    std::stringstream ss;
    ss << "chars not equals: \"" << a << "\" \"" << b << "\"\n";
    t.m_ErrorMessage = ss.str();
    return t;
}

Test Test::assertEquals(std::string a, std::string b)
{
    Test t;
    t.m_Pass = a.compare(b) == 0;
    std::stringstream ss;
    ss << "String not equals: \"" << a << "\" \"" << b << "\"\n";
    t.m_ErrorMessage = ss.str();
    return t;
}

Test Test::assertEquals(int a, int b)
{
    Test t;
    t.m_Pass = a == b;
    std::stringstream ss;
    ss << "int not equals: \"" << a << "\" \"" << b << "\"\n";
    t.m_ErrorMessage = ss.str();
    return t;
}

Test Test::assertEquals(float a, float b)
{
    Test t;
    t.m_Pass = a == b;
    std::stringstream ss;
    ss << "float not equals: \"" << a << "\" \"" << b << "\"\n";
    t.m_ErrorMessage = ss.str();
    return t;
}

Test Test::assertEquals(double a, double b)
{
    Test t;
    t.m_Pass = a == b;
    std::stringstream ss;
    ss << "double not equals: \"" << a << "\" \"" << b << "\"\n";
    t.m_ErrorMessage = ss.str();
    return t;
}

Test Test::assertEquals(bool a, bool b)
{
    Test t;
    t.m_Pass = a == b;
    std::stringstream ss;
    ss << "bool not equals: \"" << a << "\" \"" << b << "\"\n";
    t.m_ErrorMessage = ss.str();
    return t;
}

Test Test::assertTrue(bool a)
{
    Test t;
    t.m_Pass = a;
    t.m_ErrorMessage = "It should be true\n";
    return t;
}

Test Test::assertFalse(bool a)
{
    Test t;
    t.m_Pass = !a;
    t.m_ErrorMessage = "It should be false\n";
    return t;
}

std::string Result::toString()
{
    std::stringstream ss;
    ss << m_PassCount << "/" << m_TotalCount << std::endl;
    if (!m_Text.empty())
    {
        ss << m_Text << std::endl;
    }
    return ss.str();
}

} // End of namespace UT