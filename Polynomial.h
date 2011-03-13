#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Term.h"
#include "DoubleTerm.h"

class Polynomial
{
 private:
  std::vector<Term> fTerms;
  std::vector<DoubleTerm> fDoubleTerms;

 public:
  Polynomial(std::vector<Term> terms);

  Polynomial& operator+=(const Polynomial& rhs);
  const Polynomial operator+(const Polynomial& rhs) const;
  Polynomial& operator-=(const Polynomial& rhs);
  const Polynomial operator-(const Polynomial& rhs) const;
  Polynomial& operator*=(const Polynomial& rhs);
  const Polynomial operator*(const Polynomial& rhs) const;
  Polynomial& operator^=(const unsigned int& rhs);
  const Polynomial operator^(const unsigned int& rhs) const;

  std::vector<Term>       getTerms() const       { return fTerms; };
  std::vector<DoubleTerm> getDoubleTerms() const { return fDoubleTerms; };

  const Polynomial commutedWith(const Polynomial& rhs) const;

  void identifyDoubleTerms();
  void ungroupDoubleTerms();

  void gatherTerms();
  void groupTerms();
  void simplify();
  void normalOrder();
  
  void print(std::ostream& outputStream = std::cout);
  void printTex(std::ostream& outputStream = std::cout, unsigned int termsAtATime = 0, unsigned int termSetNum = 0);
};

#endif
