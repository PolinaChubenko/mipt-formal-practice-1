#include "RegularExpressionTestCase.h"
#include "RegularExpression.h"


TEST_F(RegularExpressionTestCase, checkDefaultAlphabet) {
    auto alphabet = mock_object.getAlphabet();
    std::string alphabet_in_str;
    for (auto symbol : alphabet) {
        alphabet_in_str += symbol;
    }
    EXPECT_EQ(alphabet_in_str, "*+.1abc");
}

TEST_F(RegularExpressionTestCase, checkCustomizedAlphabet) {
    mock_object.setAlphabet(std::set<char>{'a', 'b', 'c', 'd'});
    auto alphabet = mock_object.getAlphabet();
    std::string alphabet_in_str;
    for (auto symbol : alphabet) {
        alphabet_in_str += symbol;
    }
    EXPECT_EQ(alphabet_in_str, "*+.1abcd");
}
