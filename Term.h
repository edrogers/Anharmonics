#ifndef TERM_H
#define TERM_H

#include <vector>
#include <string>
#include <iostream>
#include "Coefficient.h"

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
  const Term operator*(const Term& rhs) const;

  std::vector<char>         getOperators() const     { return fOperators; };
  std::vector<Coefficient>  getCoefficients() const  { return fCoefficients; };
  int                       getOrderInLambda() const { return fOrderInLambda; };

  void setOperators    (std::vector<char> operators);
  void setCoefficients (std::vector<Coefficient>  coefficients) { fCoefficients = coefficients; };
  void setOrderInLambda(int orderInLambda) { fOrderInLambda = orderInLambda; };

  bool isNormalOrdered();
  std::vector<Term> normalOrder();

  void simplifyCoefficients();

  void print();
  void printTex();
};

#endif
