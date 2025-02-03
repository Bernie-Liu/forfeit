#include <string>
#include <any>
#include "TokenType.hpp"



class Token {
    
    TokenType type_;
    std::string lexeme_;
    std::any literal_;
    int line_;

    public:
        Token(TokenType type, std::string lexeme, std::any literal, int line);
        friend ostream & operator<<(ostream&out, const Token& t);

}; //class Token<T>