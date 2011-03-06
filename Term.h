#ifndef TERM_H
#define TERM_H

#include <vector>
#include <string>
#include <iostream>
#include "Polynomial.h"

class Term
{
 private:
  std::vector<char>         fOperators;
  std::vector<Coefficient>  fCoefficients;
  int                       fOrderInLambda;

 public:
  Term(std::vector<char>         operators,
       std::vector<Coefficient>  coefficients,
       int orderInLambda = 0);

  Term& operator*=(const Term& rhs);
  const Term& operator*(const Term& rhs) const;
  const Polynomial& operator+(const Term& rhs) const;

  std::vector<char>         getOperators()     { return fOperators; };
  std::vector<Coefficient>  getCoefficients()  { return fCoefficients; };
  int                       getOrderInLambda() { return fOrderInLambda; };

  void setOperators    (std::vector<char> operators);
  void setCoefficients (std::vector<Coefficient>  coefficients) { fCoefficients = coefficients; };
  void setOrderInLambda(int orderInLamdba) { fOrderInLambda = orderInLambda; };

  bool isNormalOrdered();
  Polynomial normalOrder();

  void simplifyCoefficients();

  void print();
  void printTex();
};

#endif
