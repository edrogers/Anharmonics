#include "Polynomial.h"

using namespace std;

Polynomial::Polynomial(vector<Term> terms)
{
  fTerms=terms;
  fDoubleTerms.clear();
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs)
{
  ungroupDoubleTerms();
  Polynomial rhsCopy = rhs;
  rhsCopy.ungroupDoubleTerms();
  vector<Term> rhsTerms = rhsCopy.getTerms();
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

Polynomial& Polynomial::operator-=(const Polynomial& rhs)
{
  ungroupDoubleTerms();
  Polynomial rhsCopy = rhs;
  rhsCopy.ungroupDoubleTerms();
  vector<Term> rhsTerms = rhsCopy.getTerms();
  Term negativeOne("(-1)");
  vector<Term> rhsTermsNegative;
  for (vector<Term>::iterator it = rhsTerms.begin();
       it != rhsTerms.end(); it++)
    {
      rhsTermsNegative.push_back(negativeOne*(*it));
    }
  fTerms.insert(fTerms.end(),
		rhsTermsNegative.begin(),
		rhsTermsNegative.end());
  return *this;
}

const Polynomial Polynomial::operator-(const Polynomial& rhs) const
{
  Polynomial output = *this;
  output-=rhs;
  return output;
}

Polynomial& Polynomial::operator*=(const Polynomial& rhs)
{
  ungroupDoubleTerms();
  Polynomial rhsCopy = rhs;
  rhsCopy.ungroupDoubleTerms();
  vector<Term> productTerms;
  vector<Term> rhsTerms = rhsCopy.getTerms();
  for (vector<Term>::iterator it1 = fTerms.begin();
       it1 != fTerms.end(); it1++) 
    {
      for (vector<Term>::iterator it2 = rhsTerms.begin();
	   it2 != rhsTerms.end(); it2++) 
	{
	  if (it1->getOrderInLambda()+it2->getOrderInLambda() <= 3)
	    {
	      Term lhs = *it1;
	      Term rhs = *it2;
	      Term product = lhs*rhs;
	      productTerms.push_back(product);
	    }
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

Polynomial& Polynomial::operator^=(const unsigned int& rhs)
{
  if (rhs == 0) 
    {
      Term unity;
      fTerms.clear();
      fTerms.push_back(unity);
      return *this;
    }

  Polynomial recursivePolynomial = *this;
  (*this)^=(rhs-1);
  (*this)*=recursivePolynomial;
  return *this;
}

const Polynomial Polynomial::operator^(const unsigned int& rhs) const
{
  Polynomial output = *this;
  output^=rhs;
  return output;
}

const Polynomial Polynomial::commutedWith(const Polynomial& rhs) const
{
  Polynomial output = (*this)*rhs-rhs*(*this);
  return output;
}

void Polynomial::identifyDoubleTerms()
{
  for (vector<Term>::iterator itT0 = fTerms.begin();
       itT0 < fTerms.end()-1; )
    {
      bool foundMatchForThisTerm = false;
      for (vector<Term>::iterator itT1 = itT0+1;
	   itT1 < fTerms.end(); )
	{
	  if (itT0->getOrderInLambda() == itT1->getOrderInLambda())

	    {
	      vector<char> t0Operators = itT0->getOperators();
	      vector<char> t1Operators = itT1->getOperators();
	      bool operatorMatch = false;
	      int nBsT0 = 0;
	      int nBsT1 = 0;
	      if ((t0Operators.size() != t1Operators.size()) ||
		  (t0Operators.size() == 0))
		{
		  itT1++;
		  continue;
		}
	      else
		{
		  vector<char>::iterator          it = t0Operators.begin();
		  vector<char>::reverse_iterator rit = t1Operators.rbegin();
		  operatorMatch = true;
		  while(it != t0Operators.end())
		    {
		      operatorMatch &= ((*it)!=(*rit));
		      if ((*it)  == 'B') nBsT0++;
		      if ((*rit) == 'B') nBsT1++;
		      it++;
		      rit++;
		    }
		}
	      if (operatorMatch)
		{
		  foundMatchForThisTerm = true;
		  if (nBsT0 > nBsT1) fDoubleTerms.push_back(DoubleTerm(*itT0,*itT1,true));
		  else               fDoubleTerms.push_back(DoubleTerm(*itT1,*itT0,true));
		  fTerms.erase(itT1);
		  break;
		}
	      else
		{
		  itT1++;
		  continue;
		}
	    }
	  else
	    {
	      itT1++;
	      continue;
	    }
	}
      if (foundMatchForThisTerm) 
	{
	  fTerms.erase(itT0);
	}
      else
	{
	  itT0++;
	}
    }
}

void Polynomial::ungroupDoubleTerms()
{
  for (vector<DoubleTerm>::iterator it = fDoubleTerms.begin();
       it != fDoubleTerms.end(); )
    {
      fTerms.push_back(it->getTerm(0));
      Term negativeOne("(-1)");
      if (it->getIsPlusTerm()) fTerms.push_back(it->getTerm(1));
      else                     fTerms.push_back(negativeOne*(it->getTerm(1)));
      fDoubleTerms.erase(it);
    }
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

void Polynomial::groupTerms()
{
  ungroupDoubleTerms();
  normalOrder();
  simplify();
  stable_sort(fTerms.begin(),fTerms.end());
  identifyDoubleTerms();
}

void Polynomial::simplify()
{
  gatherTerms();
  for (vector<Term>::iterator it = fTerms.begin();
       it != fTerms.end(); )
    {
      it->simplifyCoefficients();
      vector<Coefficient> newTermCoefficients = it->getCoefficients();
      if (newTermCoefficients.size() == 0) 
	{
	  fTerms.erase(it);
	}
      else
	{
	  it++;
	}
    }
}

void Polynomial::normalOrder()
{
  vector<Term> normalOrderedPolynomial;
  for (vector<Term>::iterator it = fTerms.begin();
       it != fTerms.end(); it++)
    {
      vector<Term> thisTermNormalOrdered = it->normalOrder();
      normalOrderedPolynomial.insert(normalOrderedPolynomial.end(),
				     thisTermNormalOrdered.begin(),
				     thisTermNormalOrdered.end());
    }
  fTerms = normalOrderedPolynomial;
}

void Polynomial::print(ostream& outputStream)
{
  for (vector<DoubleTerm>::iterator it = fDoubleTerms.begin();
       it != fDoubleTerms.end(); it++) 
    {
      if (it != fDoubleTerms.begin())
	{
	  outputStream << " + ";
	}
      it->print(outputStream);
    }
  for (vector<Term>::iterator it = fTerms.begin();
       it != fTerms.end(); it++)
    {
      if ((it != fTerms.begin()) || (fDoubleTerms.size() != 0))
	{
	  outputStream << " + ";
	}
      it->print(outputStream);
    }
}

void Polynomial::printTex(ostream& outputStream, unsigned int termsAtATime, unsigned int termSetNum)
{
  unsigned int termsSoFar = 0;
  for (vector<DoubleTerm>::iterator it = fDoubleTerms.begin();
       it != fDoubleTerms.end(); it++) 
    {
      if ( (termsAtATime == 0) ||
	   ((termsSoFar >= termSetNum*termsAtATime) &&
	    (termsSoFar <  (termSetNum+1)*termsAtATime)) )
	{
	  if (it != fDoubleTerms.begin())
	    {
	      outputStream << " + ";
	    }
	  it->printTex(outputStream);
	}
      termsSoFar++;
    }
  for (vector<Term>::iterator it = fTerms.begin();
       it != fTerms.end(); it++)
    {
      if ( (termsAtATime == 0) ||
	   ((termsSoFar >= termSetNum*termsAtATime) &&
	    (termsSoFar <  (termSetNum+1)*termsAtATime)) )
	{
	  if ((it != fTerms.begin()) || (fDoubleTerms.size() != 0))
	    {
	      outputStream << " + ";
	    }
	  it->printTex(outputStream);
	}
      termsSoFar++;
    }
}
