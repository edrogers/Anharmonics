#ifndef COEFFICIENT_H
#define COEFFICIENT_H

#include <vector>

class Coefficient
{
 private:
  float fNumericalFactor;
  std::vector<unsigned int> fAlphas;

 public:
  Coefficient(float numericalFactor,
	      std::vector<unsigned int> alphas);
  
  Coefficient& operator*=(const Coefficient& rhs);
  const Coefficient& operator*(const Coefficient& rhs) const;

  float getNumericalFactor() { return fNumericalFactor; };
  std::vector<unsigned int> getAlphas() { return fAlphas; };

  void orderAlphas();

  void print();
  void printTex();
};

#endif
