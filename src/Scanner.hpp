#include <string>
#include <list>
#include "TokenType.hpp"
#include "Token.hpp"

class Scanner {
    private:
        std::string source_;
        std::list<Token> tokens_;

        //start_: first character of the lexeme
        int start_;
        int current_;
        int line_;

        bool isAtEnd();

    public:
        Scanner(std::string source);
        std::list<Token> scanTokens();
        void scanToken();

        char advance();
        void addToken(TokenType type);
        void addToken(TokenType type, std::any literal);
        bool match(char expected);
        char peek();
};