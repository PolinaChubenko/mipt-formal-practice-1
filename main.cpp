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
    static const int64_t infinity = 1e5;

    class maxPrefForRegular {
    private:
        int64_t max_pref_len = 0; // len of max prefix = letter^k
        // (0=no pref of such letter)
        int64_t max_word_len = -1; // len of max word = letter^k
        // (-1=no empty word and language has no word letter^k)
    public:
        maxPrefForRegular() = default;
        maxPrefForRegular(int64_t pref, int64_t word) : max_pref_len(pref), max_word_len(word) {}
        [[nodiscard]] int64_t getMaxPrefLen() const;
        [[nodiscard]] int64_t getMaxWordLen() const;
        static maxPrefForRegular parseSummation(maxPrefForRegular&, maxPrefForRegular&);
        static maxPrefForRegular parseConcatenation(maxPrefForRegular &, maxPrefForRegular &);
        static maxPrefForRegular parseStar(maxPrefForRegular &);
        void controlInfinity();
    };
private:
    bool isSymbolInAlphabet(char);
    static void parseOperationWithValenceOne(std::string&, std::stack<std::string>&);
    static void parseOperationWithValenceTwo(std::string&, std::stack<std::string>&);
    static void CountMaxPrefForOneValenceOperation(std::string&, std::stack<maxPrefForRegular>&);
    static void CountMaxPrefForTwoValenceOperation(std::string&, std::stack<maxPrefForRegular>&);
    void normaliseExpression();
public:
    RegularExpression();
    explicit RegularExpression(const std::set<char>&);
    ~RegularExpression() = default;

    friend std::istream& operator >> (std::istream&, RegularExpression&);
    friend std::ostream& operator << (std::ostream&, const RegularExpression&);

    std::pair<int64_t, bool> findMaxPrefix(char);
};

int64_t RegularExpression::maxPrefForRegular::getMaxPrefLen() const {
    return max_pref_len;
}

int64_t RegularExpression::maxPrefForRegular::getMaxWordLen() const {
    return max_word_len;
}

RegularExpression::maxPrefForRegular
RegularExpression::maxPrefForRegular::parseSummation(RegularExpression::maxPrefForRegular &left_operand,
                                                     RegularExpression::maxPrefForRegular &right_operand) {
    maxPrefForRegular new_regular_max_pref;
    new_regular_max_pref.max_pref_len = std::max(left_operand.max_pref_len, right_operand.max_pref_len);
    new_regular_max_pref.max_word_len = std::max(left_operand.max_word_len, right_operand.max_word_len);
    new_regular_max_pref.controlInfinity();
    return new_regular_max_pref;
}

RegularExpression::maxPrefForRegular
RegularExpression::maxPrefForRegular::parseConcatenation(RegularExpression::maxPrefForRegular &left_operand,
                                                         RegularExpression::maxPrefForRegular &right_operand) {
    maxPrefForRegular new_regular_max_pref;
    new_regular_max_pref.max_pref_len = left_operand.max_word_len != -1 ?
            std::max(left_operand.max_pref_len, left_operand.max_word_len + right_operand.max_pref_len) :
            left_operand.max_pref_len;
    new_regular_max_pref.max_word_len = left_operand.max_word_len != -1 && right_operand.max_word_len != -1 ?
                left_operand.max_word_len + right_operand.max_word_len : -1;
    new_regular_max_pref.controlInfinity();
    return new_regular_max_pref;
}

RegularExpression::maxPrefForRegular
RegularExpression::maxPrefForRegular::parseStar(RegularExpression::maxPrefForRegular &operand) {
    maxPrefForRegular new_regular_max_pref;
    if (operand.max_word_len > 0) {
        new_regular_max_pref.max_word_len = new_regular_max_pref.max_pref_len = infinity;
    } else {
        new_regular_max_pref.max_pref_len = operand.max_pref_len;
        new_regular_max_pref.max_word_len = 0;
    }
    return new_regular_max_pref;
}

void RegularExpression::maxPrefForRegular::controlInfinity() {
    if (this->max_pref_len >= infinity || this->max_word_len >= infinity) {
        this->max_pref_len = this->max_word_len = infinity;
    }
}

bool RegularExpression::isSymbolInAlphabet(char symbol) {
    return alphabet.find(symbol) != alphabet.end();
}

void RegularExpression::parseOperationWithValenceOne(std::string &operation,
                                                            std::stack<std::string> &unprocessed_elements) {
    std::string operand = unprocessed_elements.top();
    unprocessed_elements.pop();
    if (operand.size() == 1 || operand[0] == '(') {
        unprocessed_elements.push(operand + operation);
    } else {
        unprocessed_elements.push('(' + operand + ')' + operation);
    }
}

void RegularExpression::parseOperationWithValenceTwo(std::string &operation,
                                                            std::stack<std::string> &unprocessed_elements) {
    std::string right_operand = unprocessed_elements.top();
    unprocessed_elements.pop();
    std::string left_operand = unprocessed_elements.top();
    unprocessed_elements.pop();
    if (operation == "+") {
        unprocessed_elements.push("(" + left_operand + operation + right_operand + ")");
    }
    else {
        unprocessed_elements.push(left_operand + right_operand);
    }
}

void RegularExpression::normaliseExpression() {
    std::stack<std::string> unprocessed_elements;
    for (char symbol : expression_in_rpn) {
        if (isalpha(symbol)) {
            unprocessed_elements.push(std::string(1, symbol));
        } else {
            int32_t operator_valence = (symbol == '*') ? 1 : 2;
            std::string operation = std::string(1, symbol);
            if (operator_valence == 1) {
                if (unprocessed_elements.empty()) throw std::out_of_range("Expression has incorrect operation");
                parseOperationWithValenceOne(operation, unprocessed_elements);
            } else {
                if (unprocessed_elements.size() < 2) throw std::out_of_range("Expression has incorrect operation");
                parseOperationWithValenceTwo(operation, unprocessed_elements);
            }
        }
    }
    if (unprocessed_elements.size() > 1) throw std::out_of_range("Expression is incorrect");
    expression = unprocessed_elements.top();
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
    normaliseExpression();
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
    regularExpression.normaliseExpression();
    return in;
}

std::ostream &operator<<(std::ostream &out, const RegularExpression &regularExpression) {
    out << regularExpression.expression;
    return out;
}


void RegularExpression::CountMaxPrefForOneValenceOperation(std::string &operation,
                                                           std::stack<maxPrefForRegular> &unprocessed_elements) {
    maxPrefForRegular operand = unprocessed_elements.top();
    unprocessed_elements.pop();
    unprocessed_elements.push(maxPrefForRegular::parseStar(operand));
}


void RegularExpression::CountMaxPrefForTwoValenceOperation(std::string &operation,
                                                           std::stack<maxPrefForRegular> &unprocessed_elements) {
    maxPrefForRegular right_operand = unprocessed_elements.top();
    unprocessed_elements.pop();
    maxPrefForRegular left_operand = unprocessed_elements.top();
    unprocessed_elements.pop();
    if (operation == "+") {
        unprocessed_elements.push(maxPrefForRegular::parseSummation(left_operand, right_operand));
    } else {
        unprocessed_elements.push(maxPrefForRegular::parseConcatenation(left_operand, right_operand));
    }
}


std::pair<int64_t, bool> RegularExpression::findMaxPrefix(char letter) {
    if (!isalpha(letter)) throw std::invalid_argument("Function accepts only letters");
    if (!isSymbolInAlphabet(letter)) throw std::invalid_argument("This letter does not exists in the alphabet");
    std::stack<maxPrefForRegular> unprocessed_elements;
    for (char symbol : expression_in_rpn) {
        if (isalpha(symbol)) {
            unprocessed_elements.push(symbol == letter ? maxPrefForRegular(1,1) : maxPrefForRegular());
        } else {
            int32_t operator_valence = (symbol == '*') ? 1 : 2;
            std::string operation = std::string(1, symbol);
            if (operator_valence == 1) {
                CountMaxPrefForOneValenceOperation(operation, unprocessed_elements);
            } else {
                CountMaxPrefForTwoValenceOperation(operation, unprocessed_elements);
            }
        }
    }
    maxPrefForRegular wanted_expression = unprocessed_elements.top();
    int64_t max_pref_answer = std::max(wanted_expression.getMaxPrefLen(), wanted_expression.getMaxWordLen());
    return std::make_pair(max_pref_answer, max_pref_answer != infinity ? 0 : 1);
}


int main() {
    RegularExpression r;
    std::cin >> r;
    std::cout << r << std::endl;
    char letter;
    std::cin >> letter;
    auto ans = r.findMaxPrefix(letter);
    if (ans.second) std::cout << "INF\n";
    else std::cout << ans.first << std::endl;
    return 0;
}

// aaab.c+*.b.*.
// aa.a.b.aa.+aa..
// ba*c+.a.

// ab+*
// ab+c.aba.*.bac.+.+*
// acb..bab.c.*.ab.ba.+.+*a.