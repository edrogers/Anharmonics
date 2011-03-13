#include "Coefficient.h"

using namespace std;

Coefficient::Coefficient(float numericalFactor,
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
      fNumericalFactor = 1.0;
    }
  else 
    {
      size_t firstAlphaLocation = inputString.find('a');
      if (firstAlphaLocation != string::npos)
	{
	  if (firstAlphaLocation != 0) 
	    {
	      string factorString = inputString.substr(0,firstAlphaLocation-1);
	      fNumericalFactor = atof(factorString.c_str());
	    }
	  else 
	    {
	      fNumericalFactor = 1.0;
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
	  fNumericalFactor = atof(inputString.c_str());
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
  if ((fNumericalFactor == 1.0) &&
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
  outputStream << fNumericalFactor;
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
  outputStream << fNumericalFactor;
  if (fAlphas.size() != 0)
    {
      outputStream << "{\\cdot}";
    }
  if (fAlphas.size() != 0) 
    {
      int consecutiveAlphas = 1;
      outputStream << "{\\beta}_{" << fAlphas[0] << "}";
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
	      outputStream << "{\\cdot}" << "{\\beta}_{" << *(it+1) << "}";
	      consecutiveAlphas=1;
	    }
	}
      if (consecutiveAlphas != 1)
	{
	  outputStream << "^{" << consecutiveAlphas << "}";
	}
    }
}
