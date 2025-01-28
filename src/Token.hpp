#include <string>
#include "TokenType.hpp"


template <typename T> class Token {
    
    TokenType type_;
    std::string lexme_;
    T literal_;
    int line_;

    public:
        Token(TokenType type, std::string lexeme, T literal, int line);
        friend ostream & operator<<(ostream&out, const Token<T>& t);

}; //class Token<T>