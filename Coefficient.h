#ifndef COEFFICIENT_H
#define COEFFICIENT_H

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

class Coefficient
{
 private:
  float fNumericalFactor;
  std::vector<unsigned int> fAlphas;

 public:
  Coefficient(float numericalFactor,
	      std::vector<unsigned int> alphas);
  Coefficient(std::string inputString = "");
  
  Coefficient& operator*=(const Coefficient& rhs);
  const Coefficient operator*(const Coefficient& rhs) const;

  float getNumericalFactor() const { return fNumericalFactor; };
  std::vector<unsigned int> getAlphas() const { return fAlphas; };
  bool isUnity() const;

  void orderAlphas();

  void print();
  void printTex();
};

#endif
