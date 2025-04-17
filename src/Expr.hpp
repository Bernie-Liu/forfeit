#include <any>
#include "Token.hpp"
class Expr{
public:
    template <typename R>
    class Visitor {
        virtual R visitBinaryExpr(Binary expr);
        virtual R visitGroupingExpr(Grouping expr);
        virtual R visitLiteralExpr(Literal expr);
        virtual R visitUnaryExpr(Unary expr);
        virtual R accept(Visitor<R> visitor);
    };
};

class Binary : public Expr{
public:
    Expr left_;
    Token op_;
    Expr right_;
    Binary(Expr left, Token op, Expr right);
    template <typename R>
    R accept(Visitor<R> visitor);
};

class Grouping : public Expr{
public:
    Expr expression_;
    Grouping(Expr expression);
    template <typename R>
    R accept(Visitor<R> visitor);
};

class Literal : public Expr{
public:
    std::any value_;
    Literal(std::any value);
    template <typename R>
    R accept(Visitor<R> visitor);
};

class Unary : public Expr{
public:
    Token op_;
    Expr right_;
    Unary(Token op, Expr right);
    template <typename R>
    R accept(Visitor<R> visitor);
};


