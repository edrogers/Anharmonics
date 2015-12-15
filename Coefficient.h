#ifndef COEFFICIENT_H
#define COEFFICIENT_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "NumericalFraction.h"

class Coefficient
{
 private:
  NumericalFraction fNumericalFactor;
  std::vector<unsigned int> fAlphas;

 public:
  Coefficient(NumericalFraction numericalFactor,
	      std::vector<unsigned int> alphas);
  Coefficient(std::string inputString = "");
  
  Coefficient& operator*=(const Coefficient& rhs);
  const Coefficient operator*(const Coefficient& rhs) const;

  float getNumericalFactor() const { return (float) fNumericalFactor.getNumerator()/(float) fNumericalFactor.getDenominator(); };
  std::vector<unsigned int> getAlphas() const { return fAlphas; };

  void setNumericalFactor(NumericalFraction numericalFactor)   { fNumericalFactor = numericalFactor; };
  void setAlphas(std::vector<unsigned int> alphas) { fAlphas = alphas; };

  bool isUnity() const;

  void orderAlphas();

  void print(std::ostream& outputStream = std::cout);
  void printTex(std::ostream& outputStream = std::cout);
};

#endif
