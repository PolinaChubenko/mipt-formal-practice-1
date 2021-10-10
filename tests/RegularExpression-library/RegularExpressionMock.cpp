#include "RegularExpressionMock.h"

auto RegularExpressionMock::convertPairToMaxPrefForRegular(int64_t pref_len, int64_t word_len) {
    return maxPrefForRegular(pref_len, word_len);
}
auto RegularExpressionMock::checkParsingSummation(const maxPrefForRegular& left_operand,
                                                  const maxPrefForRegular& right_operand) {
    return maxPrefForRegular::parseSummation(left_operand, right_operand);
}
auto RegularExpressionMock::checkParsingConcatenation(const maxPrefForRegular& left_operand,
                                                      const maxPrefForRegular& right_operand) {
    return maxPrefForRegular::parseConcatenation(left_operand, right_operand);
}
auto RegularExpressionMock::checkParsingStar(const maxPrefForRegular& operand) {
    return maxPrefForRegular::parseStar(operand);
}
bool RegularExpressionMock::isMaxPrefsForRegularsEqual(const maxPrefForRegular& left_operand,
                                                       const maxPrefForRegular& right_operand) {
    return left_operand.getMaxWordLen() == right_operand.getMaxWordLen() &&
           left_operand.getMaxPrefLen() == right_operand.getMaxPrefLen();
}
