#include "Coefficient.h"

using namespace std;

Coefficient::Coefficient(NumericalFraction numericalFactor,
			 vector<unsigned int> alphas)
{
  fNumericalFactor = numericalFactor;
  fAlphas = alphas;
}

Coefficient::Coefficient(string inputString)
{
  fAlphas.clear();
  if (inputString.length() == 0)
    {
      fNumericalFactor = NumericalFraction(1);
    }
  else 
    {
      size_t firstAlphaLocation = inputString.find('a');
      if (firstAlphaLocation != string::npos)
	{
	  if (firstAlphaLocation != 0) 
	    {
	      string factorString = inputString.substr(0,firstAlphaLocation-1);
	      fNumericalFactor = NumericalFraction(factorString);
	    }
	  else 
	    {
	      fNumericalFactor = NumericalFraction(1);
	    }
	  string alphaString = inputString.substr(firstAlphaLocation);
	  while (alphaString.length() > 0)
	    {
	      size_t alphaSubstringLength = alphaString.find("*");
	      if (alphaSubstringLength != string::npos)
		{
		  string alphaSubstring = alphaString.substr(0,alphaSubstringLength);
		  size_t alphaSubstringExponentiationLocation = alphaSubstring.find('^');
		  int exponentiation = 1;
		  if (alphaSubstringExponentiationLocation != string::npos)
		    {
		      exponentiation = atoi((alphaSubstring.substr(alphaSubstringExponentiationLocation+1)).c_str());
		    }
		  string alphaIndex = alphaSubstring.substr(2,alphaSubstringExponentiationLocation-2);
		  while (exponentiation > 0) 
		    {
		      fAlphas.push_back((unsigned int) atoi(alphaIndex.c_str()));
		      exponentiation--;
		    }
		  alphaString = alphaString.substr(alphaSubstringLength+1);
		}
	      else
		{
		  string alphaSubstring = alphaString;
		  size_t alphaSubstringExponentiationLocation = alphaSubstring.find('^');
		  int exponentiation = 1;
		  if (alphaSubstringExponentiationLocation != string::npos)
		    {
		      exponentiation = atoi((alphaSubstring.substr(alphaSubstringExponentiationLocation+1)).c_str());
		    }
		  string alphaIndex = alphaSubstring.substr(2,alphaSubstringExponentiationLocation-2);
		  while (exponentiation > 0) 
		    {
		      fAlphas.push_back((unsigned int) atoi(alphaIndex.c_str()));
		      exponentiation--;
		    }
		  alphaString.clear();
		}
	    }
	}
      else
	{
	  fNumericalFactor = NumericalFraction(inputString);
	}
    }
}

Coefficient& Coefficient::operator*=(const Coefficient& rhs)
{
  vector<unsigned int> rhsAlphas = rhs.getAlphas();
  fAlphas.insert(fAlphas.end(),
		 rhsAlphas.begin(),
		 rhsAlphas.end());

  fNumericalFactor*=rhs.getNumericalFactor();

  return *this;
}

const Coefficient Coefficient::operator*(const Coefficient& rhs) const
{
  Coefficient output = *this;
  output*=rhs;
  return output;
}

bool Coefficient::isUnity() const
{
  if ((fNumericalFactor.getNumerator() == fNumericalFactor.getDenominator()) &&
      (fAlphas.size() == 0))
    {
      return true;
    }
  return false;
}

void Coefficient::orderAlphas()
{
  sort(fAlphas.begin(), fAlphas.end());
}

void Coefficient::print(ostream& outputStream)
{
  fNumericalFactor.print(outputStream);
  if (fAlphas.size() != 0)
    {
      outputStream << "*";
    }
  for (vector<unsigned int>::iterator it = fAlphas.begin();
       it != fAlphas.end(); it++)
    {
      if (it != fAlphas.begin())
	{
	  outputStream << "*";
	}
      outputStream << "a_" << *it;
    }
}

void Coefficient::printTex(ostream& outputStream)
{
  fNumericalFactor.printTex(outputStream);
  if (fAlphas.size() != 0)
    {
      outputStream << "{\\cdot}";
    }
  if (fAlphas.size() != 0) 
    {
      int consecutiveAlphas = 1;
      outputStream << "{\\alpha}_{" << fAlphas[0] << "}";
      for (vector<unsigned int>::iterator it = fAlphas.begin();
	   it != fAlphas.end()-1; it++)
	{
	  if (*it == *(it+1))
	    {
	      consecutiveAlphas++;
	    } 
	  else
	    {
	      if (consecutiveAlphas != 1)
		{
		  outputStream << "^{" << consecutiveAlphas << "}";
		}
	      outputStream << "{\\cdot}" << "{\\alpha}_{" << *(it+1) << "}";
	      consecutiveAlphas=1;
	    }
	}
      if (consecutiveAlphas != 1)
	{
	  outputStream << "^{" << consecutiveAlphas << "}";
	}
    }
}
