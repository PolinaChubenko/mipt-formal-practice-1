#pragma once

#include <gmock/gmock.h>
#include "RegularExpression.h"

struct maxPrefNode {
    int64_t max_pref_len;
    int64_t max_word_len;
    maxPrefNode(int64_t pref_len, int64_t word_len) : max_pref_len(pref_len),max_word_len(word_len) {}
};

class RegularExpressionMock : public RegularExpression {
public:
    maxPrefNode checkParsingSummation(const maxPrefNode&, const maxPrefNode&);
    maxPrefNode checkParsingConcatenation(const maxPrefNode&, const maxPrefNode&);
    maxPrefNode checkParsingStar(const maxPrefNode&);
};

