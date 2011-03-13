#include "DoubleTerm.h"

using namespace std;

DoubleTerm::DoubleTerm(Term t0, Term t1, bool isPlusTerm)
{
  fIsPlusTerm = isPlusTerm;

  bool lambdaMatch   = false;
  bool operatorMatch = false;

  if (t0.getOrderInLambda() != t1.getOrderInLambda())
    {
      cout << "ERROR: DoubleTerm constructor called with mismatching Terms (lambda)" << endl;
    }
  else
    {
      int orderInLambda = t0.getOrderInLambda();
      lambdaMatch = true;
    }

  vector<char> t0Operators = t0.getOperators();
  vector<char> t1Operators = t1.getOperators();
  if ((t0Operators.size() != t1Operators.size()) ||
      (t0Operators.size() == 0))
    {
      cout << "ERROR: DoubleTerm constructor called with mismatching Terms (operators)" << endl;
    }
  else
    {
      vector<char>::iterator          it = t0Operators.begin();
      vector<char>::reverse_iterator rit = t1Operators.rbegin();
      operatorMatch = true;
      while(it != t0Operators.end())
	{
	  operatorMatch &= ((*it)!=(*rit));
	  it++;
	  rit++;
	}
    }
  if (operatorMatch == false)
    {
      cout << "ERROR: DoubleTerm constructor called with mismatching Terms (operators)" << endl;
    }

  fTermPair[0] = t0;
  if (isPlusTerm) 
    {
      fTermPair[1] = t1;
    }
  else 
    {
      Term negativeOne("(-1)");
      fTermPair[1] = t1*negativeOne;
    }
}

bool DoubleTerm::isDiagonal()
{
  fTermPair[0].simplifyCoefficients();
  fTermPair[1].simplifyCoefficients();

  vector<Coefficient> t0Coefficients = fTermPair[0].getCoefficients();
  vector<Coefficient> t1Coefficients;
  if (fIsPlusTerm) 
    {
      t1Coefficients = fTermPair[1].getCoefficients();
    }
  else
    {
      Term negativeOne("(-1)");
      Term t1Negative = negativeOne*fTermPair[1];
      t1Coefficients = t1Negative.getCoefficients();
    }

  for (vector<Coefficient>::iterator it0 = t0Coefficients.begin();
       it0 != t0Coefficients.end(); ) 
    {
      bool foundMatch = false;
      for (vector<Coefficient>::iterator it1 = t1Coefficients.begin();
	   it1 != t1Coefficients.end(); )
	{
	  if ( (it0->getNumericalFactor() == it1->getNumericalFactor()) &&
	       (it0->getAlphas()          == it1->getAlphas()) )
	    {
	      foundMatch = true;
	      t1Coefficients.erase(it1);
	      break;
	    }
	  it1++;
	}
      if (foundMatch)
	{
	  t0Coefficients.erase(it0);
	} 
      else
	{
	  it0++;
	}
    }
  if ( (t0Coefficients.size() != 0) || (t1Coefficients.size() != 0) )
    {
      return false;
    }  
  return true;
}

vector<DoubleTerm> DoubleTerm::diagonalize()
{
  vector<DoubleTerm> outputDoubleTerms;

  if (!fTermPair) return outputDoubleTerms;

  if (isDiagonal()) 
    {
      outputDoubleTerms.push_back(*this);
      return outputDoubleTerms;
    }

  Term t0 = fTermPair[0];
  Term t1 = fTermPair[1];
  Term negativeOne    = Term("(-1)");
  Term oneHalf        = Term("(0.5)");
  Term t0Half         = t0*oneHalf;
  Term t1Half         = t1*oneHalf;
  Term t1NegativeHalf = t1*negativeOne*oneHalf;

  vector<Coefficient> t0HalfCoefficients         = t0Half.getCoefficients();
  vector<Coefficient> t1HalfCoefficients         = t1Half.getCoefficients();
  vector<Coefficient> t1NegativeHalfCoefficients = t1NegativeHalf.getCoefficients();


  vector<Coefficient> dtPlusCoefficients = t0HalfCoefficients;
  dtPlusCoefficients.insert(dtPlusCoefficients.end(),
			    t1HalfCoefficients.begin(),
			    t1HalfCoefficients.end());

  vector<Coefficient> dtMinusCoefficients = t0HalfCoefficients;
  dtMinusCoefficients.insert(dtMinusCoefficients.end(),
			     t1NegativeHalfCoefficients.begin(),
			     t1NegativeHalfCoefficients.end());

  int dtOrderInLambda = t0.getOrderInLambda();

  vector<char> dtFirstOperators  = t0.getOperators();
  vector<char> dtSecondOperators = t1.getOperators();

  Term dtFirstPlus  (dtFirstOperators, dtPlusCoefficients, dtOrderInLambda);
  Term dtSecondPlus (dtSecondOperators,dtPlusCoefficients, dtOrderInLambda);
  Term dtFirstMinus (dtFirstOperators, dtMinusCoefficients,dtOrderInLambda);
  Term dtSecondMinus(dtSecondOperators,dtMinusCoefficients,dtOrderInLambda);

  dtFirstPlus.simplifyCoefficients();
  dtSecondPlus.simplifyCoefficients();
  dtFirstMinus.simplifyCoefficients();
  dtSecondMinus.simplifyCoefficients();

  DoubleTerm dtPlus (dtFirstPlus,  dtSecondPlus,  true);
  DoubleTerm dtMinus(dtFirstMinus, dtSecondMinus, false);
  
  if (dtFirstPlus.getCoefficients().size()  != 0) outputDoubleTerms.push_back(dtPlus);
  if (dtFirstMinus.getCoefficients().size() != 0) outputDoubleTerms.push_back(dtMinus);
  return outputDoubleTerms;
}

Term DoubleTerm::getTerm(unsigned int iTerm)
{
  if (iTerm < 2) 
    {
      return fTermPair[iTerm];
    } 
  return Term("(0.0)");
}

void DoubleTerm::print(ostream& outputStream)
{
  if (!isDiagonal())
    {
      vector<DoubleTerm> diagonalizedDoubleTerms = diagonalize();
      for (vector<DoubleTerm>::iterator it = diagonalizedDoubleTerms.begin();
	   it != diagonalizedDoubleTerms.end(); it++)
	{
	  if (it != diagonalizedDoubleTerms.begin())
	    {
	      outputStream << " + ";
	    }
	  it->print(outputStream);
	}
      return;
    }

  int numberOfFactors = 1; //operators are always non-trivial, or constructor would issue errors.

  fTermPair[0].simplifyCoefficients();
  vector<Coefficient> dtCoefficients = fTermPair[0].getCoefficients();
  bool printThisDoubleTerm = (dtCoefficients.size() != 0);

  bool coefficientIsUnity = false;
  if ((dtCoefficients.size() == 1) &&
      (dtCoefficients[0].isUnity()))
    {
      coefficientIsUnity = true;
    }
  else
    {
      numberOfFactors++;
    }

  int fOrderInLambda = fTermPair[0].getOrderInLambda();
  if (fOrderInLambda != 0) numberOfFactors++;

  vector<char> t0Operators = fTermPair[0].getOperators();
  vector<char> t1Operators = fTermPair[1].getOperators();

  if (fOrderInLambda != 0)
    {
      outputStream << "lambda";
      if (fOrderInLambda != 1)
	{
	  outputStream << "^" << fOrderInLambda;
	}
      if (numberOfFactors > 1) outputStream << "*";
      numberOfFactors--;
    }
  if (!coefficientIsUnity)
    {
      outputStream << "(";
      for (vector<Coefficient>::iterator it = dtCoefficients.begin();
	   it != dtCoefficients.end(); it++)
	{
	  if ((it != dtCoefficients.begin()) &&
	      (it->getNumericalFactor() >= 0))
	    {
	      outputStream << "+";
	    }
	  it->print(outputStream);
	}
      outputStream << ")";
      if (numberOfFactors > 1) outputStream << "*";
      numberOfFactors--;
    }
  outputStream << "(";
  for (vector<char>::iterator it = t0Operators.begin();
       it != t0Operators.end(); it++)
    {
      outputStream << *it;
    }
  fIsPlusTerm ? outputStream << "+" : outputStream << "-";
  for (vector<char>::iterator it = t1Operators.begin();
       it != t1Operators.end(); it++)
    {
      outputStream << *it;
    }
  outputStream << ")";
}

void DoubleTerm::printTex(ostream& outputStream)
{
  if (!isDiagonal())
    {
      vector<DoubleTerm> diagonalizedDoubleTerms = diagonalize();
      for (vector<DoubleTerm>::iterator it = diagonalizedDoubleTerms.begin();
	   it != diagonalizedDoubleTerms.end(); it++)
	{
	  if (it != diagonalizedDoubleTerms.begin())
	    {
	      outputStream << " + ";
	    }
	  it->printTex(outputStream);
	}
      return;
    }

  int numberOfFactors = 1; //operators are always non-trivial, or constructor would issue errors.

  fTermPair[0].simplifyCoefficients();
  vector<Coefficient> dtCoefficients = fTermPair[0].getCoefficients();
  bool printThisDoubleTerm = (dtCoefficients.size() != 0);

  bool coefficientIsUnity = false;
  if ((dtCoefficients.size() == 1) &&
      (dtCoefficients[0].isUnity()))
    {
      coefficientIsUnity = true;
    }
  else
    {
      numberOfFactors++;
    }

  int fOrderInLambda = fTermPair[0].getOrderInLambda();
  if (fOrderInLambda != 0) numberOfFactors++;

  vector<char> t0Operators = fTermPair[0].getOperators();
  vector<char> t1Operators = fTermPair[1].getOperators();

  if (fOrderInLambda != 0)
    {
      outputStream << "{\\lambda}";
      if (fOrderInLambda != 1)
	{
	  outputStream << "^" << fOrderInLambda;
	}
      if (numberOfFactors > 1) outputStream << "{\\cdot}";
      numberOfFactors--;
    }
  if (!coefficientIsUnity)
    {
      outputStream << "(";
      for (vector<Coefficient>::iterator it = dtCoefficients.begin();
	   it != dtCoefficients.end(); it++)
	{
	  if ((it != dtCoefficients.begin()) &&
	      (it->getNumericalFactor() >= 0))
	    {
	      outputStream << "+";
	    }
	  it->printTex(outputStream);
	}
      outputStream << ")";
      if (numberOfFactors > 1) outputStream << "{\\cdot}";
      numberOfFactors--;
    }
  outputStream << "(";

  int consecutiveOperators = 1;
  outputStream << t0Operators[0];
  for (vector<char>::iterator it = t0Operators.begin();
       it != t0Operators.end()-1; it++)
    {
      if (*it == *(it+1))
	{
	  consecutiveOperators++;
	} 
      else
	{
	  if (consecutiveOperators != 1)
	    {
	      outputStream << "^{" << consecutiveOperators << "}";
	    }
	  outputStream << *(it+1);
	  consecutiveOperators=1;
	}
    }
  if (consecutiveOperators != 1)
    {
      outputStream << "^{" << consecutiveOperators << "}";
    }
  fIsPlusTerm ? outputStream << "+" : outputStream << "-";
  consecutiveOperators = 1;
  outputStream << t1Operators[0];
  for (vector<char>::iterator it = t1Operators.begin();
       it != t1Operators.end()-1; it++)
    {
      if (*it == *(it+1))
	{
	  consecutiveOperators++;
	} 
      else
	{
	  if (consecutiveOperators != 1)
	    {
	      outputStream << "^{" << consecutiveOperators << "}";
	    }
	  outputStream << *(it+1);
	  consecutiveOperators=1;
	}
    }
  if (consecutiveOperators != 1)
    {
      outputStream << "^{" << consecutiveOperators << "}";
    }
  outputStream << ")";
}
