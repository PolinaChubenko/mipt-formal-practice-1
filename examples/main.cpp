#include <RegularExpression.h>
#include <iostream>

int main() {
    RegularExpression r;
    // r.setExpressionInRpn("aaab.c+*.b.*.");
    std::cin >> r;
    std::cout << r << std::endl << "Enter the letter: ";
    char letter;
    std::cin >> letter;
    auto ans = r.findMaxPrefix(letter);
    if (ans.second) std::cout << "INF\n";
    else std::cout << ans.first << std::endl;
    return 0;
}


// aaab.c+*.b.*.                = a(a(ab+c)*b)*              ans=3
// aa.a.b.aa.+aa..              = (aaab+aa)aa                ans=4
// ba*c+.a.                     = b(a*+c)a                   ans=0
// ab+*                         = (a+b)*                     ans=INF
// ab+c.aba.*.bac.+.+*          = ((a+b)c+a(ba)*(b+ac))*     ans=2
// acb..bab.c.*.ab.ba.+.+*a.    = (acb+b(abc)*(ab+ba))*a     ans=1
