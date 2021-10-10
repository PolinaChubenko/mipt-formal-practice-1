#pragma once

#include "RegularExpression.h"

class RegularExpressionMock : public RegularExpression {
public:
    auto convertPairToMaxPrefForRegular(int64_t pref_len, int64_t word_len);
    auto checkParsingSummation(const maxPrefForRegular& left_operand, const maxPrefForRegular& right_operand);
    auto checkParsingConcatenation(const maxPrefForRegular& left_operand, const maxPrefForRegular& right_operand);
    auto checkParsingStar(const maxPrefForRegular& operand);
    bool isMaxPrefsForRegularsEqual(const maxPrefForRegular& left_operand, const maxPrefForRegular& right_operand);
};

