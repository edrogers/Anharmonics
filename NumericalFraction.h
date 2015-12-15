#ifndef NUMERICALFRACTION_H
#define NUMERICALFRACTION_H

#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <math.h>

class NumericalFraction
{
 private:
  long fNumerator;
  long fDenominator;
  
 public:
  NumericalFraction(long numerator,
		    long denominator = 1);

  NumericalFraction(std::string inputString = "");

  NumericalFraction& operator+=(const NumericalFraction& rhs);
  const NumericalFraction operator+(const NumericalFraction& rhs) const;
  NumericalFraction& operator-=(const NumericalFraction& rhs);
  const NumericalFraction operator-(const NumericalFraction& rhs) const;
  NumericalFraction& operator*=(const NumericalFraction& rhs);
  const NumericalFraction operator*(const NumericalFraction& rhs) const;
  NumericalFraction& operator/=(const NumericalFraction& rhs);
  const NumericalFraction operator/(const NumericalFraction& rhs) const;
   
  void setNumerator(long numerator)     { fNumerator = numerator; };
  void setDenominator(long denominator) { fDenominator = denominator; };

  long getNumerator() const { return fNumerator; };
  long getDenominator() const { return fDenominator; };

  void simplify();

  void print(std::ostream& outputStream = std::cout) const;
  void printTex(std::ostream& outputStream = std::cout) const;

};

#endif
