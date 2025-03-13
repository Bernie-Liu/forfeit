#include <any>
#include "Token.hpp"
using namespace std;

class Expr{
public:
};

class  Binary : public Expr{
public:
  Expr left_;
  Token op_;
  Expr right_;
  Binary(Expr left, Token op, Expr right) {
    this->left_ = left;
    this->op_ = op;
    this->right_ = right;
  }
};

class  Grouping : public Expr{
public:
  Expr expression_;
  Grouping(Expr expression) {
    this->expression_ = expression;
  }
};

class  Literal : public Expr{
public:
  any value_;
  Literal(any value) {
    this->value_ = value;
  }
};

class  Unary : public Expr{
public:
  Token op_;
  Expr right_;
  Unary(Token op, Expr right) {
    this->op_ = op;
    this->right_ = right;
  }
};

