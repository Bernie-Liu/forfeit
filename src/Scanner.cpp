#include <string>
#include "Scanner.hpp"
//#include "Token.hpp"
//#include "TokenType.hpp"
#include "Forfeit.hpp"


using namespace std;


Scanner::Scanner(std::string source){
    source_=source;
    start_=0;
    current_=0;
    line_=1;

    keywords_["and"]=TokenType::AND;
    keywords_["class"]=TokenType::CLASS;
    keywords_["else"]=TokenType::ELSE;
    keywords_["false"]=TokenType::FALSE;
    keywords_["for"]=TokenType::FOR;
    keywords_["fun"]=TokenType::FUN;
    keywords_["if"]=TokenType::IF;
    keywords_["nil"]=TokenType::NIL;
    keywords_["or"]=TokenType::OR;
    keywords_["print"]=TokenType::PRINT;
    keywords_["return"]=TokenType::RETURN;
    keywords_["super"]=TokenType::SUPER;
    keywords_["this"]=TokenType::THIS;
    keywords_["true"]=TokenType::TRUE;
    keywords_["var"]=TokenType::VAR;
    keywords_["while"]=TokenType::WHILE;


    TokenTypes_[TokenType::LEFT_PAREN]="LEFT_PAREN";
    TokenTypes_[TokenType::RIGHT_PAREN]="RIGHT_PAREN";
    TokenTypes_[TokenType::LEFT_BRACE]="LEFT_BRACE";
    TokenTypes_[TokenType::RIGHT_BRACE]="RIGHT_BRACE";
    TokenTypes_[TokenType::COMMA]="COMMA";
    TokenTypes_[TokenType::DOT]="DOT";
    TokenTypes_[TokenType::MINUS]="MINUS";
    TokenTypes_[TokenType::PLUS]="PLUS";
    TokenTypes_[TokenType::SEMICOLON]="SEMICOLON";
    TokenTypes_[TokenType::SLASH]="SLASH";
    TokenTypes_[TokenType::STAR]="STAR";
    
    TokenTypes_[TokenType::BANG]="BANG";
    TokenTypes_[TokenType::BANG_EQUAL]="BANG_EQUAL";
    TokenTypes_[TokenType::EQUAL]="EQUAL";
    TokenTypes_[TokenType::EQUAL_EQUAL]="EQUAL_EQUAL";
    TokenTypes_[TokenType::GREATER]="GREATER";
    TokenTypes_[TokenType::GREATER_EQUAL]="REATER_EQUAL";
    TokenTypes_[TokenType::LESS]="LESS";
    TokenTypes_[TokenType::LESS_EQUAL]="LESS_EQUAL";

    TokenTypes_[TokenType::STRING]="STRING";
    TokenTypes_[TokenType::NUMBER]="NUMBER";
    TokenTypes_[TokenType::IDENTIFIER]="IDENTIFIER";
    
    
    TokenTypes_[TokenType::AND]="AND";
    TokenTypes_[TokenType::CLASS]="CLASS";
    TokenTypes_[TokenType::ELSE]="ELSE";
    TokenTypes_[TokenType::FALSE]="FALSE";
    TokenTypes_[TokenType::FOR]="FOR";
    TokenTypes_[TokenType::FUN]="FUN";
    TokenTypes_[TokenType::IF]="IF";
    TokenTypes_[TokenType::NIL]="NIL";
    TokenTypes_[TokenType::OR]="OR";
    TokenTypes_[TokenType::PRINT]="PRINT";
    TokenTypes_[TokenType::RETURN]="RETURN";
    TokenTypes_[TokenType::SUPER]="SUPER";
    TokenTypes_[TokenType::THIS]="THIS";
    TokenTypes_[TokenType::TRUE]="TRUE";
    TokenTypes_[TokenType::VAR]="VAR";
    TokenTypes_[TokenType::WHILE]="WHILE";
    TokenTypes_[TokenType::END_OF_FILE]="END_OF_FILE";




}

//Add tokens from the source code until it runs out of characters
list<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        //beginning of next lexeme
        start_=current_;
        scanToken();
    }

    Token token(TokenTypes_[TokenType::END_OF_FILE], "", NULL, line_);
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
                while (peek()!= '\n'&& !isAtEnd()) {
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
        
        case '"':
            string();
            break;

        default:
            if (isDigit(c)) {
                number();
            }
            else if (isAlpha(c)) {
                identifier();
            }
            else{
                error(line_, "Unexpected character.");
                break;
            }    
    }
}

void Scanner::identifier() {
    while (isAlphaNumeric(peek())) {
        advance();
    }

    std::string text=source_.substr(start_, current_-start_);
    TokenType type=keywords_[text];
    if (0==type) {
        type=TokenType::IDENTIFIER;
    }
    addToken(type);
}



void Scanner::string() {
    //cout<<peek()<<endl;
    while (peek()!= '"' && !isAtEnd()) {
        if (peek()=='\n') {
            line_++;
        }
        advance();
    }

    if (isAtEnd()) {
        error(line_, "Unterminated string.");
    }

    //closing "
    advance();

    //trim ""
    std::string value=source_.substr(start_+1, current_-start_-2);

    addToken(TokenType::STRING, value);
}


bool Scanner::isAtEnd() {
    return current_>=(int)source_.size();
}

//consumes current character if it's what we're looking for
bool Scanner::match(char expected) {
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

char Scanner::peekNext() {
    if (current_+1>=(int)source_.length()) {
        return '\0';
    }

    return source_.at(current_+1);
}

bool Scanner::isAlpha(char c) {
    return (c>='a' && c <= 'z') || (c>='A' && c<='Z') || c=='_';
}

bool Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

bool Scanner::isDigit(char c) {
    return c>='0'&& c<='9';
}

void Scanner::number() {
    while (isDigit(peek())) {
        advance();
    }

    if (peek()=='.' && isDigit(peekNext())) {
        //consume .
        advance();

        while (isDigit(peek())) {
            advance();
        }
    }

    addToken(TokenType::NUMBER, stod(source_.substr(start_, current_-start_)));
}

//consumes the next character of the source file and returns it
char Scanner::advance() {
    return source_.at(current_++);
}

void Scanner::addToken(TokenType type) {
    addToken(type, NULL);
}

void Scanner::addToken(TokenType type, std::any literal) {
    std::string text(source_.substr(start_, current_-start_));
    Token token(TokenTypes_[type], text, literal, line_);
    tokens_.push_back(token);
}



