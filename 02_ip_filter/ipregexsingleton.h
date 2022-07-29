#pragma once

class IpRegexSingleton {
public:
    static IpRegexSingleton& getInstance();

    IpRegexSingleton(const IpRegexSingleton &) = delete;
    void operator=(const IpRegexSingleton &) = delete;

private:
    IpRegexSingleton();
    std::regex m_re;
}
