#ifndef _Token_hpp_
#define _Token_hpp_

#include <string>
#include <any>
#include <iostream>
#include "TokenType.hpp"





class Token {
    
    std::string type_;
    std::string lexeme_;
    std::any literal_;
    int line_;

    public:
        Token(std::string type, std::string lexeme, std::any literal, int line);
        friend std::ostream & operator<<(std::ostream &out, const Token &t);


}; //class Token<T>

#endif // _Token_hpp_