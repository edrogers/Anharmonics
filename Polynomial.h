#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <iostream>
#include "Term.h"

class Polynomial
{
 private:
  std::vector<Term> fTerms;

 public:
  Polynomial(std::vector<Term> terms);

  Polynomial& operator+=(const Polynomial& rhs);
  const Polynomial operator+(const Polynomial& rhs) const;
  Polynomial& operator*=(const Polynomial& rhs);
  const Polynomial operator*(const Polynomial& rhs) const;
  Polynomial& operator^=(const unsigned int& rhs);
  const Polynomial operator^(const unsigned int& rhs) const;

  std::vector<Term> getTerms() const { return fTerms; };

  void gatherTerms();
  void simplify();
  void normalOrder();
  
  void print();
  void printTex();
};

#endif
