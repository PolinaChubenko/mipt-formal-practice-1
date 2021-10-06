#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
#include <set>
#include <stack>


class RegularExpression {
private:
    std::string expression_in_rpn;
    std::string expression;
    std::set<char> alphabet = {'1', '.', '+', '*'};
private:
    bool isSymbolInAlphabet(char);
public:
    RegularExpression();
    explicit RegularExpression(const std::set<char>&);
    ~RegularExpression() = default;

    friend std::istream& operator >> (std::istream&, RegularExpression&);
    friend std::ostream& operator << (std::ostream&, const RegularExpression&);

    void parseExpression();
    int64_t findMaxPrefix(char);
};

bool RegularExpression::isSymbolInAlphabet(char symbol) {
    return alphabet.find(symbol) != alphabet.end();
}

RegularExpression::RegularExpression() {
    alphabet.emplace('a');
    alphabet.emplace('b');
    alphabet.emplace('c');
}

RegularExpression::RegularExpression(const std::set<char> &alphabet) {
    for (const auto &symbol : alphabet) {
        this->alphabet.emplace(symbol);
    }
}


std::istream &operator>>(std::istream &in, RegularExpression &regularExpression) {
    in >> regularExpression.expression_in_rpn;
    char symbol;
    while (in.read(&symbol, 1)) {
        if (symbol == '\0' || symbol == '\n') {
            break;
        }
        if (!regularExpression.isSymbolInAlphabet(symbol)) {
            throw std::invalid_argument("Regular expression has a symbol which does not exist in the alphabet");
        }
        if (symbol == ' ') {
            continue;
        }
        regularExpression.expression_in_rpn.push_back(symbol);
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const RegularExpression &regularExpression) {
    out << regularExpression.expression;
    return out;
}

void RegularExpression::parseExpression() {
    std::stack<char> stack;
}

int64_t RegularExpression::findMaxPrefix(char symbol) {
    // if max_amount == -1 -> INF
    int64_t max_amount = -2;
    return max_amount;
}


int main() {
    RegularExpression r;
    std::cin >> r;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
