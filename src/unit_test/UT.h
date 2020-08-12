#pragma once

#include <string>
#include <vector>
#include <execinfo.h>
#include <sstream>

namespace UT {

/**
 * You will get such string:
 * '''
 * ./test(+0x8538) [0x5585a715b538]
 * '''
 * You can use this to know where this is executed:
 * addr2line -e test 0x8538
 */
static std::string getLastInvokePlace();

class Test;
class Result;

class Report
{
private:
    int m_TotalCount = 0;
    int m_PassCount = 0;
    std::vector<Test> m_TestList;

public:
    void mergeReport(Report r);
    void addTest(Test t);
    Result getResult();
}; // End of class Report

class Test
{
friend Report;
private:
    bool m_Pass = false;
    std::string m_ErrorMessage;
public:
    static Test assertEquals(char*, char*);
    static Test assertEquals(std::string, std::string);
    static Test assertEquals(int a, int b);
    static Test assertEquals(float a, float b);
    static Test assertEquals(double a, double b);
    static Test assertEquals(bool a, bool b);
    static Test assertTrue(bool a);
    static Test assertFalse(bool a);

    template<class T>
    static Test assertEquals(T& t1, T& t2)
    {
        Test t;
        t.m_Pass = t1 == t2;
        if (!t.m_Pass)
        {
            std::stringstream ss;
            ss << "Not Equals: \"" << t1 << "\" \"" << t2 << "\"";
            ss << getLastInvokePlace() << std::endl;
            t.m_ErrorMessage = ss.str();
        }
        return t;
    }

    bool isPass() { return m_Pass; }
}; // End of class Test

class Result
{
friend Report;
private:
    int m_TotalCount;
    int m_PassCount;
    std::string m_Text;
public:
    std::string toString();
    int getPassCount() { return m_PassCount; }
    int getTotalCount() { return m_TotalCount; }
    bool totalPass() { return m_TotalCount == m_PassCount; }
}; // End of class Result

std::string getLastInvokePlace()
{
    int levelNumber = 3;
    void* array[levelNumber];
    size_t size;
    char **strings;
    size = backtrace (array, levelNumber);
    strings = backtrace_symbols(array, size);

    size_t prev_line = levelNumber - 1;
    std::string out(strings[prev_line]);

    free (strings);

    return out;
}
} // End of namespace UT