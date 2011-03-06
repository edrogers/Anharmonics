#include "Coefficient.h"

using namespace std;

Coefficient::Coefficient(float numericalFactor,
			 vector<unsigned int> alphas)
{
  fNumericalFactor = numericalFactor;
  fAlphas = alphas;
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
  vector<unsigned int> orderedAlphas;
  unsigned int iAlpha = 0;
  while (fAlphas.size() > 0) 
    {
      for (vector<unsigned int>::iterator it = fAlphas.begin();
	   it < fAlphas.end(); ) // iteration may happen at erase
	{
	  if ((*it) == iAlpha)
	    {
	      orderedAlphas.push_back(*it);
	      fAlphas.erase(it);
	      continue;
	    }
	  it++;
	}
      iAlpha++;
    }
  fAlphas = orderedAlphas;
}

void Coefficient::print()
{
  if (fNumericalFactor != 1.0)
    {
      cout << fNumericalFactor;
      if (fAlphas.size() != 0)
	{
	  cout << "*";
	}
    }
  for (vector<unsigned int>::iterator it = fAlphas.begin();
       it != fAlphas.end(); it++)
    {
      if (it != fAlphas.begin())
	{
	  cout << "*";
	}
      cout << "a" << *it;
    }
}

void Coefficient::printTex()
{

}
