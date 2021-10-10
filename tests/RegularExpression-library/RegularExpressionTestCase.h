#pragma once

#include <gtest/gtest.h>
#include "RegularExpressionMock.h"

class RegularExpressionTestCase: public ::testing::Test{
public:
    RegularExpressionMock mock_object;
};

