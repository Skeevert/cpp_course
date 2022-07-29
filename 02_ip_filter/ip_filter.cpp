#include "ipaddress.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

std::ostream &operator<<(std::ostream &os, const IpAddress &m)
{
    os << m.ipView();
    return os;
}
std::string parseIp(const std::string &str)
{
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of("\t");

    return str.substr(start, stop - start);
}

int main(int argc, char const *argv[])
{
    (void) argc;
    (void) argv;
    try
    {
        std::vector<IpAddress> ips;

        for(std::string line; std::getline(std::cin, line);)
        {
            ips.emplace_back(parseIp(line));
        }

        // reverse lexicographically sort
        std::sort(ips.begin(), ips.end(), [] (IpAddress a, IpAddress b) { return !(a < b); });

        for (const auto &ip : ips) {
            std::cout << ip.ipView() << std::endl;
        }

        // filter by first byte and output (1)
        std::copy_if(ips.cbegin(),
                     ips.cend(),
                     std::ostream_iterator<IpAddress>(std::cout, "\n"),
                     [] (IpAddress ip) { return ip.checkByte(1, 0); }
        );

        // filter by first and second bytes and output (46, 70)
        std::copy_if(ips.cbegin(),
                     ips.cend(),
                     std::ostream_iterator<IpAddress>(std::cout, "\n"),
                     [] (IpAddress ip) { return ip.checkByte(46, 0) && ip.checkByte(70, 1); }
        );

        // filter by any byte and output (46)
        std::copy_if(ips.cbegin(),
                     ips.cend(),
                     std::ostream_iterator<IpAddress>(std::cout, "\n"),
                     [] (IpAddress ip) { return ip.checkAnyByte(46); }
        );
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
