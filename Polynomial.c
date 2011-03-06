#include "Polynomial.h"

using namespace std;

Polynomial::Polynomial(vector<Term> terms)
{
  fTerms=terms;
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs)
{
  vector<Term> rhsTerms = rhs.getTerms();
  fTerms.insert(fTerms.end(),
		rhsTerms.begin(),
		rhsTerms.end());
  return *this;
}

const Polynomial Polynomial::operator+(const Polynomial& rhs) const
{
  Polynomial output = *this;
  output+=rhs;
  return output;
}

Polynomial& Polynomial::operator*=(const Polynomial& rhs)
{
  vector<Term> productTerms;
  for (vector<Term>::iterator it1 = fTerms.begin();
       it1 != fTerms.end(); it1++) 
    {
      for (vector<Term>::iterator it2 = fTerms.begin();
	   it2 != fTerms.end(); it2++) 
	{
	  Term lhs = *it1;
	  Term rhs = *it2;
	  Term product = lhs*rhs;
	  productTerms.push_back(product);
	}
    }
  fTerms = productTerms;
  return *this;
}

const Polynomial Polynomial::operator*(const Polynomial& rhs) const
{
  Polynomial output = *this;
  output*=rhs;
  return output;
}

void Polynomial::gatherTerms()
{
  vector<Term> gatheredTerms;
  for (vector<Term>::iterator it1 = fTerms.begin();
       it1 < fTerms.end(); ) // iteration happens at erase
    {
      vector<char> newTermOperators = it1->getOperators();
      vector<Coefficient> newTermCoefficients = it1->getCoefficients();
      int newTermOrderInLambda = it1->getOrderInLambda();

      for (vector<Term>::iterator it2 = it1+1;
	   it2 < fTerms.end(); ) // iteration may happen at erase
	{
	  vector<char> secondTermOperators = it2->getOperators();
	  vector<Coefficient> secondTermCoefficients = it2->getCoefficients();
	  int secondTermOrderInLambda = it2->getOrderInLambda();

	  if ((newTermOperators == secondTermOperators) &&
	      (newTermOrderInLambda == secondTermOrderInLambda))
	    {
	      newTermCoefficients.insert(newTermCoefficients.end(),
					 secondTermCoefficients.begin(),
					 secondTermCoefficients.end());
	      fTerms.erase(it2);
	      continue;
	    }
	  it2++;
	}
      Term newTerm(newTermOperators,
		   newTermCoefficients,
		   newTermOrderInLambda);
      gatheredTerms.push_back(newTerm);
      fTerms.erase(it1);
    }
  fTerms = gatheredTerms;
}

void Polynomial::simplify()
{
  gatherTerms();
  for (vector<Term>::iterator it = fTerms.begin();
       it != fTerms.end(); it++)
    {
      it->simplifyCoefficients();
    }
}

void Polynomial::print()
{
  for (vector<Term>::iterator it = fTerms.begin();
       it != fTerms.end(); it++)
    {
      if (it != fTerms.begin())
	{
	  cout << " + ";
	}
      it->print();
    }
}

void Polynomial::printTex()
{
  for (vector<Term>::iterator it = fTerms.begin();
       it != fTerms.end(); it++)
    {
      if (it != fTerms.begin())
	{
	  cout << " + ";
	}
      it->printTex();
    }
}
