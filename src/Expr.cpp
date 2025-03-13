#include "Token.hpp"

class Expr{
public:
};

class  Binary : public Expr{
public:
  Expr left_;
  Token operator_;
  Expr right_;
  Binary(Expr left, Token operator, Expr right) {
    this->left_ = left;
    this->operator_ = operator;
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
  Object value_;
  Literal(Object value) {
    this->value_ = value;
  }
};

class  Unary : public Expr{
public:
  Token operator_;
  Expr right_;
  Unary(Token operator, Expr right) {
    this->operator_ = operator;
    this->right_ = right;
  }
};

