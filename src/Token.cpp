#include <string>
#include <iostream>

#include "Token.hpp"

using namespace std;

template <typename T>

Token<T>::Token(TokenType type, string lexeme, T literal, int line) {
    type_=type;
    lexeme_=lexeme;
    literal_=literal;
    line_=line;
}

template <typename T>
ostream & operator<<(ostream&out, const Token<T>& t) {
    out << t.type_ << " " << t.lexeme_ << " " << t.literal_;
    return out;
}
