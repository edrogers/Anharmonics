#include "NumericalFraction.h"

using namespace std;

NumericalFraction::NumericalFraction(long numerator, long denominator)
{
  fNumerator = numerator;
  fDenominator = denominator;
}

NumericalFraction::NumericalFraction(string inputString)
{
  fNumerator = 1;
  fDenominator = 1;
  if (inputString.length() != 0)
    {
      size_t divisionSignLocation = inputString.find('/');
      if (divisionSignLocation != string::npos)
	{
	  fNumerator   = atol(inputString.substr(0,divisionSignLocation).c_str());
	  fDenominator = atol(inputString.substr(divisionSignLocation+1).c_str());
	}
      else 
	{
	  fNumerator = atol(inputString.c_str());
	  fDenominator = 1;
	}
    }
}

NumericalFraction& NumericalFraction::operator+=(const NumericalFraction& rhs)
{
  cout << "Adding Numerical Fractions: "; 
  print();
  cout << " + ";
  rhs.print();
  cout << " == ";
  if (fDenominator == rhs.getDenominator()) 
    {
      fNumerator += rhs.getNumerator();
    }
  else
    {
      fNumerator = fNumerator*rhs.getDenominator()+rhs.getNumerator()*fDenominator;
      fDenominator*=rhs.getDenominator();
    }
  print();
  cout << endl;
  return *this;
}

const NumericalFraction NumericalFraction::operator+(const NumericalFraction& rhs) const
{
  NumericalFraction output = *this;
  output+=rhs;
  return output;
}

NumericalFraction& NumericalFraction::operator-=(const NumericalFraction& rhs)
{
  if (fDenominator == rhs.getDenominator())
    {
      fNumerator -= rhs.getNumerator();
    }
  else
    {
      fNumerator = fNumerator*rhs.getDenominator()-rhs.getNumerator()*fDenominator;
      fDenominator*=rhs.getDenominator();
    }

  return *this;
}

const NumericalFraction NumericalFraction::operator-(const NumericalFraction& rhs) const
{
  NumericalFraction output = *this;
  output-=rhs;
  return output;
}

NumericalFraction& NumericalFraction::operator*=(const NumericalFraction& rhs)
{
  fNumerator*=rhs.getNumerator();
  fDenominator*=rhs.getDenominator();

  return *this;
}

const NumericalFraction NumericalFraction::operator*(const NumericalFraction& rhs) const
{
  NumericalFraction output = *this;
  output*=rhs;
  return output;
}

NumericalFraction& NumericalFraction::operator/=(const NumericalFraction& rhs)
{
  fNumerator*=rhs.getDenominator();
  fDenominator*=rhs.getNumerator();

  return *this;
}

const NumericalFraction NumericalFraction::operator/(const NumericalFraction& rhs) const
{
  NumericalFraction output = *this;
  output/=rhs;
  return output;
}

void NumericalFraction::simplify() 
{
  vector<int> numeratorFactors;
  while (abs(fNumerator) != 1) 
    {
      int divisor = 2;
      while (fNumerator % divisor != 0) divisor++;
      numeratorFactors.push_back(divisor);
      fNumerator/=divisor;
    }

  vector<int> denominatorFactors;
  while (abs(fDenominator) != 1) 
    {
      int divisor = 2;
      while (fDenominator % divisor != 0) divisor++;
      denominatorFactors.push_back(divisor);
      fDenominator/=divisor;
    }

  for (vector<int>::iterator itD = denominatorFactors.begin();
       itD != denominatorFactors.end(); )
    {
      bool foundCommonFactor = false;
      for (vector<int>::iterator itN = numeratorFactors.begin();
	   itN != numeratorFactors.end(); itN++)
	{
	  if ((*itN) == (*itD))
	    {
	      foundCommonFactor = true;
	      numeratorFactors.erase(itN);
	      break;
	    }
	}
      if (foundCommonFactor)
	{
	  denominatorFactors.erase(itD);
	}
      else
	{
	  itD++;
	}
    }

  for (vector<int>::iterator itN = numeratorFactors.begin();
       itN != numeratorFactors.end(); itN++)
    {
      fNumerator*=(*itN);
    }
    
  for (vector<int>::iterator itD = denominatorFactors.begin();
       itD != denominatorFactors.end(); itD++)
    {
      fDenominator*=(*itD);
    }
}

void NumericalFraction::print(ostream& outputStream) const
{
  if (fDenominator != 1) 
    {
      outputStream << "(" << fNumerator << "/" << fDenominator << ")";
    }
  else
    {
      outputStream << fNumerator;
    }
}

void NumericalFraction::printTex(ostream& outputStream) const
{
  if (fDenominator != 1)
    {
      outputStream << "(\\frac{" << fNumerator << "}{" << fDenominator << "})";
    }
  else
    {
      outputStream << fNumerator;
    }
}
