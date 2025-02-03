#include <string>
#include <iostream>

#include "Token.hpp"

using namespace std;



Token::Token(TokenType type, string lexeme, std::any literal, int line) {
    type_=type;
    lexeme_=lexeme;
    literal_=literal;
    line_=line;
}

template <typename T>
ostream & operator<<(ostream&out, const Token& t) {
    out << t.type_ << " " << t.lexeme_ << " " << t.literal_;
    return out;
}
