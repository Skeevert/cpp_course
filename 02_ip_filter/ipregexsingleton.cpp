#include "ipregexsingleton.h"

IpRegexSingleton& IpRegexSingleton::getInstance()
{
    static IpRegexSingleton instance;
    return instance;
}

IpRegexSingleton::IpRegexSingleton()
{
    m_re = std::regex("(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})")
}
