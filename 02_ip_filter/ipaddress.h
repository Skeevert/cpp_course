#pragma once

#include <stdint.h>
#include <tuple>
#include <string>
#include <string_view>
#include <regex>

struct IpAddress {
private:
    std::array<uint8_t, 4>  m_ip;
    std::string m_ipString;
public:
    IpAddress(const std::string &ip, const std::regex &re);
    IpAddress(const IpAddress &other);
    IpAddress(IpAddress &&other);
    IpAddress& operator=(const IpAddress &other);
    IpAddress& operator=(IpAddress &&other);
    
    bool parse();

    std::string_view ipView()const;
    bool checkByte(uint8_t value, size_t i) const;
    bool checkAnyByte(uint8_t value) const;
    
    bool operator<(const IpAddress &other) const;
};
