#include <string>
#include <vector>
#include "TokenType.hpp"
#include "Token.hpp"

template <typename T>
class Scanner {
    private:
        std::string source_;
        std::vector<Token> tokens_;

        int start_;
        int current_;
        int line_;

        bool isAtEnd();

    public:
        Scanner(std::string source);
        vector<Token> scanTokens();
        void scanToken();

        char advance();
        void addToken(TokenType type);
        void addToken(TokenType type, T literal);
};