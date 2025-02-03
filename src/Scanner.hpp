#include <string>
#include <list>
#include <unordered_map>
//#include "TokenType.hpp"
#include "Token.hpp"

class Scanner {
    private:
        std::string source_;
        std::list<Token> tokens_;

        //start_: first character of the lexeme
        int start_;
        int current_;
        int line_;

        std::unordered_map<std::string, TokenType> keywords_;


        bool isAtEnd();
        bool match(char expected);
        char peek();
        void string();
        bool isDigit(char c);
        void number();
        char peekNext();
        bool isAlpha(char c);
        void identifier();
        bool isAlphaNumeric(char c);

    public:
        Scanner(std::string source);
        std::list<Token> scanTokens();
        void scanToken();

        char advance();
        void addToken(TokenType type);
        void addToken(TokenType type, std::any literal);
        
};