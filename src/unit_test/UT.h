#include <string>
#include <vector>

namespace UT {

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

static std::string getLastInvokePlace();

} // End of namespace UT