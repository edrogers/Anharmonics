#include "Term.h"
using namespace std;

Term::Term(vector<char> operators,
	   vector<Coefficient> coefficients,
	   int orderInLambda) 
{
  bool legalOperators = true;
  for (vector<char>::iterator it = operators.begin();
       it != operators.end(); it++)
    {
      if ((*it != 'A') &&
	  (*it != 'B'))
	{
	  cout << "ERROR: Term constructor given illegal vector" << endl;
	  legalOperators = false;
	}
    }

  bool legalCoefficients = true;
  if (coefficients.size() == 0)
    {
      cout << "ERROR: Term constructors given empty coefficient vector" << endl;
      legalCoefficients = false;
    }

  if (legalOperators && legalCoefficients)
    {
      fOperators=operators;
      fCoefficients=coefficients;
      fOrderInLambda=orderInLambda;
    }
}


Term& Term::operator*=(const Term& rhs)
{
  //multiply operators
  vector<char> rhsOperators = rhs.getOperators();
  fOperators.insert(fOperators.end(),
		    rhsOperators.begin(),
		    rhsOperators.end());

  //multiply coefficients
  vector<Coefficient> productCoefficients;
  vector<Coefficient> rhsCoefficients = rhs.getCoefficients();
  for (vector<Coefficient>::iterator it1 = rhsCoefficients.begin();
       it1 != rhsCoefficients.end(); it1++)
    {
      for (vector<Coefficient>::iterator it2 = fCoefficients.begin();
	   it2 != fCoefficients.end(); it2++)
	{
	  productCoefficients.push_back((*it2)*(*it1));
	}
    }
  fCoefficients=productCoefficients;

  //multiply lambdas
  int rhsOrderInLambda = rhs.getOrderInLambda();
  fOrderInLambda+=rhsOrderInLambda;

  //return result
  return *this;
}

const Term& Term::operator*(const Term& rhs) const
{
  Term outputTerm = *this;
  outputTerm*=rhs;
  return outputTerm;
}

const Polynomial& Term::operator+(const Term& rhs) const
{
  vector<Term> polynomialTerms;
  polynomialTerms.push_back(*this);
  polynomialTerms.push_back(rhs);
  Polynomial outputPolynomial(polynomialTerms);
  return outputPolynomial;
}

void Term::setOperators(vector<char> operators)
{
  bool legalOperators = true;
  for (vector<char>::iterator it = operators.begin();
       it != operators.end(); it++)
    {
      if ((*it != 'A') &&
	  (*it != 'B'))
	{
	  cout << "ERROR: setOperators given illegal vector" << endl;
	  legalOperators = false;
	}
    }

  if (legalOperators)
    {
      fOperators=operators;
    }
}

bool Term::isNormalOrdered()
{
  for (vector<char>::iterator it = fOperators.begin();
       it < fOperators.end()-1; it++) 
    {
      if ((*it     == 'A') &&
	  (*(it+1) == 'B'))
	{
	  return false;
	}
    }
  return true;
}

Polynomial Term::normalOrder()
{
  if (this->isNormalOrdered()) 
    {
      vector<Term> outputPolynomialVector;
      outputPolynomialVector.push_back(*this);
      Polynomial myPolynomial(outputPolynomialVector);
      return myPolynomial;
    }
  vector<char> firstTermOperators;
  vector<char> secondTermOperators;

  for (vector<char>::iterator it = fOperators.begin();
       it < fOperators.end()-1; it++) 
    {
      if ((*it     == 'A') &&
	  (*(it+1) == 'B')) 
	{
	  firstTermOperators.assign (fOperators.begin(),it);
	  secondTermOperators.assign(fOperators.begin(),it);

	  firstTermOperators.push_back('B');
	  firstTermOperators.push_back('A');

	  firstTermOperators.insert (it+2,fOperators.end());
	  secondTermOperators.insert(it+2,fOperators.end());
	  
	  break;
	}
    }

  Term firstTerm(firstTermOperators,
		 fCoefficients,
		 fOrderInLambda);
  Term secondTerm(secondTermOperators,
		  fCoefficients,
		  fOrderInLambda);

  Polynomial orderedFirstPolynomial =  firstTerm.normalOrder();
  Polynomial orderedSecondPolynomial = secondTerm.normalOrder();

  Polynomial outputPolynomial = orderedFirstPolynomial+orderedSecondPolynomial;
  return outputPolynomial;
}

void Term::simplifyCoefficients() 
{
  for (vector<Coefficient>::iterator it1 = fCoefficients.begin();
       it1 < fCoefficients.end(); it1++)
    {
      it1->orderAlphas();
    }

  vector<Coefficient> simplifiedCoefficients;

  for (vector<Coefficient>::iterator it1 = fCoefficients.begin();
       it1 < fCoefficients.end(); ) // iteration happens at erase
    {
      vector<unsigned int> newCoefficientAlphas = it1->getAlphas();
      float newCoefficientNumericalFactor = it1->getNumericalFactor();

      for (vector<Coefficient>::iterator it2 = it1+1;
	   it2 < fCoefficients.end(); ) // iteration may happen at erase
	{
	  vector<unsigned int> secondAlphas = it2->getAlphas();
	  float secondNumericalFactor = it2->getNumericalFactor();

	  if (newCoefficientAlphas == secondAlphas)
	    {
	      newCoefficientNumericalFactor+=secondNumericalFactor;
	      fCoefficients.erase(it2);
	      continue;
	    }
	  it2++;
	}
      if (newCoefficientNumericalFactor != 0.0)
	{
	  Coefficient newCoefficientSimplified(newCoefficientNumericalFactor,
					       newCoefficientAlphas);
	  simplifiedCoefficients.push_back(newCoefficientSimplified);
	}
      fCoefficients.erase(it1);
    }
  fCoefficients = simplifiedCoefficients;
}

void Term::print()
{
  bool coefficientIsUnity = false;
  int numberOfFactors = 0;
  if (fCoefficients.size() > 1 || 
      fCoefficients[0].getAlphas().size() != 0 ||
      fCoefficients[0].getNumericalFactor != 1.0) 
    {
      numberOfFactors++;
    }
  else 
    {
      coefficientIsUnity = true;
    }
  if (fOrderInLambda != 0)    numberOfFactors++;
  if (fOperators.size() != 0) numberOfFactors++;

  if (fOrderInLambda != 0)
    {
      cout << "lambda";
      if (fOrderInLambda != 1)
	{
	  cout << "^" << fOrderInLambda;
	}
      numberOfFactors--;
      if (numberOfFactors > 1) cout << "*";
    }
  if (!coefficientIsUnity)
    {
      cout << "(";
      for (vector<Coefficient>::iterator it = fCoefficients.begin();
	   it != fCoefficients.end(); it++)
	{
	  if (it != fCoefficients.begin())
	    {
	      cout << "+";
	    }
	  Coefficient.print();
	}
      numberOfFactors--;
      cout << ")";
      if (numberOfFactors > 1) cout << "*";
    }
  if (fOperators.size() != 0) 
    {
      for (vector<char>::iterator it = fOperators.begin();
	   it != fOperators.end(); it++)
	{
	  cout << *it;
	}
    }
}

void Term::printTex()
{

}