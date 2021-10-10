#pragma once

#include <iostream>
#include <string>
#include <set>
#include <stack>


class RegularExpression {
private:
    std::string expression_in_rpn;
    std::string expression;
    std::set<char> alphabet = {'*', '+', '.', '1'};
    static const int64_t infinity = 1e5;

protected:
    class maxPrefForRegular {
    private:
        int64_t max_pref_len = 0; // len of max prefix = letter^k
        // (0 means no pref of such letter)
        int64_t max_word_len = -1; // len of max word = letter^k
        // (-1 means no empty word and language has no word letter^k)
    public:
        maxPrefForRegular() = default;
        maxPrefForRegular(int64_t pref, int64_t word) : max_pref_len(pref), max_word_len(word) {}
        ~maxPrefForRegular() = default;
        [[nodiscard]] int64_t getMaxPrefLen() const;
        [[nodiscard]] int64_t getMaxWordLen() const;
        void setMaxPrefLen(int64_t);
        void setMaxWordLen(int64_t);
        static maxPrefForRegular parseSummation(const maxPrefForRegular&, const maxPrefForRegular&);
        static maxPrefForRegular parseConcatenation(const maxPrefForRegular&, const maxPrefForRegular&);
        static maxPrefForRegular parseStar(const maxPrefForRegular&);
        void controlInfinity();
    };

protected:
    static void parseUnivalentOperation(std::string&, std::stack<std::string>&);
    static void parseBivalentOperation(std::string&, std::stack<std::string>&);
    static void CountMaxPrefForUnivalentOperation(std::string&, std::stack<maxPrefForRegular>&);
    static void CountMaxPrefForBivalentOperation(std::string&, std::stack<maxPrefForRegular>&);
    void normaliseExpression();

public:
    RegularExpression();
    ~RegularExpression() = default;

    void setAlphabet(const std::set<char>&);
    void setExpressionInRpn(const std::string&);
    friend std::istream& operator >> (std::istream&, RegularExpression&);
    friend std::ostream& operator << (std::ostream&, const RegularExpression&);
    std::string getExpressionInRpn();
    std::string getExpression();
    std::set<char> getAlphabet();
    bool isSymbolInAlphabet(char);

    std::pair<int64_t, bool> findMaxPrefix(char);
};
