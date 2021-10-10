#include "RegularExpressionTestCase.h"
#include <sstream>


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

TEST_F(RegularExpressionTestCase, ErrorsInSettingExpressionInRpn) {
    EXPECT_THROW(mock_object.setExpressionInRpn("ab+*cd"), std::invalid_argument);
//    EXPECT_THROW(mock_object.setExpressionInRpn("+"), std::invalid_argument);
//    EXPECT_THROW(mock_object.setExpressionInRpn("*"), std::invalid_argument);
    EXPECT_THROW(mock_object.setExpressionInRpn("ab+*c"), std::out_of_range);
}

TEST_F(RegularExpressionTestCase, NormalisingExpression) {
    mock_object.setExpressionInRpn("aab+*.");
    EXPECT_EQ(mock_object.getExpressionInRpn(), "aab+*.");
    EXPECT_EQ(mock_object.getExpression(), "a(a+b)*");
}

TEST_F(RegularExpressionTestCase, GettingExpressionFromStream) {
    std::stringstream stream;
    stream << "ba *c+  .a.\0";
    stream >> mock_object;
    EXPECT_EQ(mock_object.getExpression(), "b(a*+c)a");
    EXPECT_NO_THROW(stream << mock_object);
    std::stringstream().swap(stream);
    stream << "ad\0";
    EXPECT_THROW(stream >> mock_object, std::invalid_argument);
}

TEST_F(RegularExpressionTestCase, ParsingSummation1) {
    maxPrefNode left_operand(1,1), right_operand(0,-1);
    auto parsed_summation = mock_object.checkParsingSummation(left_operand, right_operand);
    EXPECT_EQ(parsed_summation.max_pref_len, 1);
    EXPECT_EQ(parsed_summation.max_word_len, 1);
}

TEST_F(RegularExpressionTestCase, ParsingSummation2) {
    maxPrefNode left_operand(100000,100000), right_operand(0,-1);
    auto parsed_summation = mock_object.checkParsingSummation(left_operand, right_operand);
    EXPECT_EQ(parsed_summation.max_pref_len, 100000);
    EXPECT_EQ(parsed_summation.max_word_len, 100000);
}

TEST_F(RegularExpressionTestCase, ParsingConcatenation1) {
    maxPrefNode left_operand(1,1), right_operand(0,-1);
    auto parsed_summation = mock_object.checkParsingConcatenation(left_operand, right_operand);
    EXPECT_EQ(parsed_summation.max_pref_len, 1);
    EXPECT_EQ(parsed_summation.max_word_len, -1);
}

TEST_F(RegularExpressionTestCase, ParsingConcatenation2) {
    maxPrefNode left_operand(1,1), right_operand(1,1);
    auto parsed_summation = mock_object.checkParsingConcatenation(left_operand, right_operand);
    EXPECT_EQ(parsed_summation.max_pref_len, 2);
    EXPECT_EQ(parsed_summation.max_word_len, 2);
}

TEST_F(RegularExpressionTestCase, ParsingStar) {
    maxPrefNode operand(0,-1);
    auto parsed_summation = mock_object.checkParsingStar(operand);
    EXPECT_EQ(parsed_summation.max_pref_len, 0);
    EXPECT_EQ(parsed_summation.max_word_len, 0);
}
