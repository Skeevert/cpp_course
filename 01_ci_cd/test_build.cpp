#define BOOST_TEST_MODULE test_version

#include "lib.h"

#include <gtest/gtest.h>

TEST(BuildTest, BasicAssertions) {
    EXPECT_GT(buildNumber(), 0);
}
