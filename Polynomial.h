#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include "Term.h"

class Polynomial
{
 private:
  vector<Term> fTerms;

 public:
  Polynomial(std::vector<Term> terms);

  Polynomial& operator+=(const Polynomial& rhs);
  const Polynomial& operator+(const Polynomial& rhs) const;
  Polynomial& operator*=(const Polynomial& rhs);
  const Polynomial& operator*(const Polynomial& rhs) const;

  std::vector<Term> getTerms() { return fTerms; };

  void gatherTerms();

  void print();
  void printTex();
};

#endif
