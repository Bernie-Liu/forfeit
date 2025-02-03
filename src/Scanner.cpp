#include <string>
#include "Scanner.hpp"
#include "Token.hpp"
#include "TokenType.hpp"
#include "Forfeit.cpp"


using namespace std;


Scanner::Scanner(std::string source){
    source_=source;
    start_=0;
    current_=0;
    line_=1;

}

//Add tokens from the source code until it runs out of characters
list<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        //beginning of next lexeme
        start_=current_;
        scanToken();
    }

    Token token(TokenType::END_OF_FILE, "", NULL, line_);
    tokens_.push_back(token);
    return tokens_;
}

void Scanner::scanToken() {

    char c = advance();
    switch (c) {
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break; 

        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        // if we find the second /, consume characters until end of line
        case '/':
            if (match('/')) {
                while (peek()!= '\n'&& isAtEnd()) {
                    advance();
                }
            }
            else {
                addToken(TokenType::SLASH);
            }

        case ' ':
        case '\r':
        case '\t':
            break;
        
        case '\n':
            line_++;
            break;
            
        default:
            error(line_, "Unexpected character.");
            break;
    }
}




bool Scanner::isAtEnd() {
    return current_>=source_.length();
}

//consumes current character if it's what we're looking for
bool Scanner::match(char expected) {
    bool temp=isAtEnd();
    if (isAtEnd()) return false;
    if (source_.at(current_)!=expected) return false;

    current_++;
    return true;
} 

char Scanner::peek() {
    if (isAtEnd()) {
        return '\0';
    }
    return source_.at(current_);
}

//consumes the next character of the source file and returns it
char Scanner::advance() {
    return source_.at(current_++);
}

void Scanner::addToken(TokenType type) {
    addToken(type, NULL);
}

void Scanner::addToken(TokenType type, std::any literal) {
    string text=source_.substr(start_, current_-start_);
}



