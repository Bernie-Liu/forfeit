#include <any>
#include "Token.hpp"
using namespace std;

class Expr{
public:
    template <typename R>
    class Visitor {
        virtual R visitBinaryExpr(Binary expr) = 0;
        virtual R visitGroupingExpr(Grouping expr) = 0;
        virtual R visitLiteralExpr(Literal expr) = 0;
        virtual R visitUnaryExpr(Unary expr) = 0;
        virtual R accept(Visitor<R> visitor);
    };
};

class Binary : public Expr{
public:
    Expr left_;
    Token op_;
    Expr right_;
    Binary(Expr left, Token op, Expr right) {
        this->left_ = left;
        this->op_ = op;
        this->right_ = right;
    }
    template <typename R>
    R accept(Visitor<R> visitor){
        return visitor.visitBinaryExpr(*this);
    }
};

class Grouping : public Expr{
public:
    Expr expression_;
    Grouping(Expr expression) {
        this->expression_ = expression;
    }
    template <typename R>
    R accept(Visitor<R> visitor){
        return visitor.visitGroupingExpr(*this);
    }
};

class Literal : public Expr{
public:
    any value_;
    Literal(any value) {
        this->value_ = value;
    }
    template <typename R>
    R accept(Visitor<R> visitor){
        return visitor.visitLiteralExpr(*this);
    }
};

class Unary : public Expr{
public:
    Token op_;
    Expr right_;
    Unary(Token op, Expr right) {
        this->op_ = op;
        this->right_ = right;
    }
    template <typename R>
    R accept(Visitor<R> visitor){
        return visitor.visitUnaryExpr(*this);
    }
};


