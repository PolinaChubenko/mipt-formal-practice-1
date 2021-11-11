#include "RegularExpressionMock.h"

maxPrefNode RegularExpressionMock::checkParsingSummation(const maxPrefNode &leftNode, const maxPrefNode &rightNode) {
    maxPrefForRegular left_operand(leftNode.max_pref_len, leftNode.max_word_len);
    maxPrefForRegular right_operand(rightNode.max_pref_len, rightNode.max_word_len);
    auto answer = maxPrefForRegular::parseSummation(left_operand, right_operand);
    return maxPrefNode(answer.getMaxPrefLen(), answer.getMaxWordLen());
}
maxPrefNode RegularExpressionMock::checkParsingConcatenation(const maxPrefNode &leftNode, const maxPrefNode &rightNode) {
    maxPrefForRegular left_operand(leftNode.max_pref_len, leftNode.max_word_len);
    maxPrefForRegular right_operand(rightNode.max_pref_len, rightNode.max_word_len);
    auto answer = maxPrefForRegular::parseConcatenation(left_operand, right_operand);
    return maxPrefNode(answer.getMaxPrefLen(), answer.getMaxWordLen());
}
maxPrefNode RegularExpressionMock::checkParsingStar(const maxPrefNode &Node) {
    maxPrefForRegular operand(Node.max_pref_len, Node.max_word_len);
    auto answer = maxPrefForRegular::parseStar(operand);
    return maxPrefNode(answer.getMaxPrefLen(), answer.getMaxWordLen());
}