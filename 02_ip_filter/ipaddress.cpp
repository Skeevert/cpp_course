#include "ipaddress.h"
#include <stdexcept>

IpAddress::IpAddress(const std::string &ip) :
    m_ipString(ip)
{
    std::smatch sm;
    const std::regex &re = getIpRegex();
    regex_match(m_ipString, sm, re);

    if (sm.size() - 1 != 4) {
        throw std::runtime_error("Malformed ip (ip does not have exactly 4 bytes)");
    }
    
    for (size_t i = 0; i < m_ip.max_size(); i++) {

        int token = std::stoi(sm[i + 1]);
        if (token > 255) {
            throw std::runtime_error("Malformed ip (value exceeds byte limit)");
        }

        m_ip[i] = token;
    }
}

IpAddress::IpAddress(const IpAddress &other) :
    m_ip(other.m_ip),
    m_ipString(other.m_ipString)
{
}

IpAddress::IpAddress(IpAddress &&other) :
    m_ip(std::move(other.m_ip)),
    m_ipString(std::move(other.m_ipString))
{
}

IpAddress& IpAddress::operator=(const IpAddress &other)
{
    m_ip = other.m_ip;
    m_ipString = other.m_ipString;
    return *this;
}

IpAddress& IpAddress::operator=(IpAddress &&other)
{
    m_ip = std::move(other.m_ip);
    m_ipString = std::move(other.m_ipString);
    return *this;

}

std::regex &IpAddress::getIpRegex()
{
    static std::regex re ("(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})");

    return re;
}

std::string_view IpAddress::ipView() const
{
    return std::string_view { m_ipString };
}

bool IpAddress::checkByte(uint8_t value, size_t i) const
{
    return m_ip[i] == value;
}

bool IpAddress::checkAnyByte(uint8_t value) const
{
    return std::any_of(m_ip.cbegin(), m_ip.cend(), [value] (uint8_t byte) { return byte == value; });
}

bool IpAddress::operator<(const IpAddress &other) const
{
    return m_ip < other.m_ip;
}
