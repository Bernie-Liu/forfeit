#include <string>
#include <iostream>
#include <any>

#include "Token.hpp"

using namespace std;



Token::Token(string type, string lexeme, std::any literal, int line) {
    type_=type;
    lexeme_=lexeme;
    literal_=literal;
    line_=line;
}



std::ostream & operator<<(ostream&out, const Token& t) {
    out << t.type_ << " " << t.lexeme_ << " ";

    if (t.literal_.has_value()) {
        if (t.literal_.type()==typeid(double)) {
            out << any_cast<double>(t.literal_);
        }

        else if (t.literal_.type()==typeid(string)) {
            out << any_cast<string>(t.literal_);
        }

        else if (t.literal_.type()==typeid(int)) {
            out << any_cast<int>(t.literal_);
        }
        else if (t.literal_.type()==typeid(NULL)) {
            out << "NIL";
        }

        else {
            out << "Unknown type";
        }
    }
    else {
        out << "NIL";
    }


    return out;
}
