#include "ipaddress.h"

#include <gtest/gtest.h>
#include <stdexcept>

TEST(IpTest, BasicAssertions)
{
        // Testing ip construction
    EXPECT_THROW(IpAddress("a.1.1.1"), std::runtime_error);
    EXPECT_THROW(IpAddress(""), std::runtime_error);
    EXPECT_THROW(IpAddress("1.1.1.1.1"), std::runtime_error);
    EXPECT_THROW(IpAddress("1.1.256.1"), std::runtime_error);

    // Testing byte checking
    EXPECT_TRUE(IpAddress("1.1.1.1").checkByte(1, 0));
    EXPECT_TRUE(IpAddress("1.2.3.4").checkAnyByte(3));

    // Testing less operator
    EXPECT_TRUE(IpAddress("1.1.1.1") < IpAddress("1.1.1.2"));
    EXPECT_TRUE(IpAddress("1.1.255.255") < IpAddress("1.2.1.1"));
}
