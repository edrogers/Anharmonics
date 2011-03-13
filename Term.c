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

Term::Term(string inputString)
{
  //Proper formatting:
  //  lambda^2*(2*a_1*a_2^3*a_3+7*a_3^2)*ABABA
  //  (2*a_2)*BBAAAA
  //  lambda*AB
  //  lambda^3*(2-7*a_1)

  //Improper formatting:
  //  (2*a_1*(a_2+3*a_3))*ABABA  // should be (2*a_1*a_2+6*a_1*a_3)*ABABA
  //  3*lambda*BABA              // should be lambda*(3)*BABA
  //  5*A                        // should be (5)*A

  // first: no parenthesis --> no coefficients (just 1.0)
  //           parenthesis --> coefficient(s) contained
  size_t openParenthesisLocation = inputString.find('(');
  string coefficientsStringFull = "";
  if (openParenthesisLocation != string::npos)
    {
      // find the close parenthesis.  Extract the coefficient(s) substring.
      size_t closeParenthesisLocation = inputString.find(')', openParenthesisLocation+1);
      if (closeParenthesisLocation == string::npos) 
	{
	  cout << "ERROR: Mismatched parenthesis in Term constructor: " << inputString << endl;
	}
      else
	{
	  coefficientsStringFull = inputString.substr(openParenthesisLocation+1,
						      closeParenthesisLocation-openParenthesisLocation-1);

	  // separate the string into coefficients, starting from the back.
	  fCoefficients.clear();

	  while (coefficientsStringFull.length() > 0)
	    {
	      size_t lastPlusSignPosition  = coefficientsStringFull.rfind('+');
	      size_t lastMinusSignPosition = coefficientsStringFull.rfind('-');
	      size_t coefficientLength = coefficientsStringFull.length();
	      size_t coefficientPosition = 0;

	      if (!((lastPlusSignPosition  == string::npos) &&
		    (lastMinusSignPosition == string::npos)))
		{
		  if  (lastPlusSignPosition  != string::npos)
		    {
		      coefficientLength = coefficientsStringFull.length()-lastPlusSignPosition;
		      coefficientPosition = lastPlusSignPosition;
		      if ((lastMinusSignPosition != string::npos) && 
			  (lastMinusSignPosition > lastPlusSignPosition))
			{
			  coefficientLength = coefficientsStringFull.length()-lastMinusSignPosition;
			  coefficientPosition = lastMinusSignPosition;
			}
		    }
		  else
		    {
		      coefficientLength = coefficientsStringFull.length()-lastMinusSignPosition;
		      coefficientPosition = lastMinusSignPosition;
		    }
		}
	      Coefficient latestCoefficient(coefficientsStringFull.substr(coefficientPosition,coefficientLength));
	      fCoefficients.push_back(latestCoefficient);
	      coefficientsStringFull.resize(coefficientPosition);
	    }
	  reverse(fCoefficients.begin(),fCoefficients.end());

	  inputString.replace(openParenthesisLocation,closeParenthesisLocation-openParenthesisLocation+1,"");
	  size_t duplicateStarLocation = inputString.find("**");
	  if (duplicateStarLocation != string::npos) 
	    {
	      inputString.replace(duplicateStarLocation,2,"*");
	    }
	  else if ((inputString.length() > 0) &&
		   (inputString.at(0) == '*'))
	    {
	      inputString.replace(0,1,"");
	    }
	  else if ((inputString.length() > 0) &&
		   (inputString.at(inputString.length()-1) == '*'))
	    {
	      inputString.replace(inputString.length()-1,1,"");
	    }
	}
    }
  else
    {
      // Coefficient == 1.0
      fCoefficients.clear();
      Coefficient unity;
      fCoefficients.push_back(unity);
    }

  size_t lambdaLocation = inputString.find("lambda");
  if (lambdaLocation != string::npos)
    {
      if (inputString.length() > lambdaLocation+6)
	{
	  bool lambdaIsExponentiated = (inputString.at(lambdaLocation+6) == '^');
	  if (lambdaIsExponentiated)
	    {
	      size_t endOfExponentiation = inputString.find('*',lambdaLocation+7);
	      if (endOfExponentiation != string::npos)
		{
		  string exponentiation = inputString.substr(lambdaLocation+7,endOfExponentiation-(lambdaLocation+7));
		  inputString.replace(lambdaLocation,endOfExponentiation-lambdaLocation+1,"");
		  fOrderInLambda = atoi(exponentiation.c_str());
		}
	      else
		{
		  string exponentiation = inputString.substr(lambdaLocation+7,endOfExponentiation);
		  inputString.replace(lambdaLocation,endOfExponentiation,"");
		  fOrderInLambda = atoi(exponentiation.c_str());
		}
	    }
	  else
	    {
	      fOrderInLambda = 1;
	      inputString.replace(lambdaLocation,6,"");
	      if ((inputString.length() > 0) && (inputString.at(0) == '*')) inputString.replace(0,1,"");
	    }
	}
      else
	{
	  fOrderInLambda = 1;
	  inputString.replace(lambdaLocation,6,"");
	  if ((inputString.length() > 0) && (inputString.at(0) == '*')) inputString.replace(0,1,"");
	}
    }
  else
    {
      fOrderInLambda = 0;
    }

  if (inputString.length() > 0)
    {
      for (string::iterator it = inputString.begin();
	   it != inputString.end(); it++) 
	{
	  fOperators.push_back(*it);
	}
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

const Term Term::operator*(const Term& rhs) const
{
  Term outputTerm = *this;
  outputTerm*=rhs;
  return outputTerm;
}

const bool Term::operator<(const Term& rhs) const
{
  vector<char> rhsOperators = rhs.getOperators();
  if (fOperators.size() > rhsOperators.size()) return true;
  if (fOperators.size() < rhsOperators.size()) return false;
  int numAsLhs = (int) count(fOperators.begin(),   fOperators.end(),   'A');
  int numBsLhs = (int) count(fOperators.begin(),   fOperators.end(),   'B');
  int diffLhs  = abs(numBsLhs-numAsLhs);
  int numAsRhs = (int) count(rhsOperators.begin(), rhsOperators.end(), 'A');
  int numBsRhs = (int) count(rhsOperators.begin(), rhsOperators.end(), 'B');
  int diffRhs  = abs(numBsRhs-numAsRhs);

  if (diffLhs > diffRhs) return true;
  if (diffLhs < diffRhs) return false;

  return (numBsLhs > numBsRhs);
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
  if (fOperators.size() < 2) return true;
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

vector<Term> Term::normalOrder()
{
  vector<Term> output;

  if (this->isNormalOrdered()) 
    {
      output.push_back(*this);
      return output;
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

	  firstTermOperators.insert (firstTermOperators.end(),
				     it+2,fOperators.end());
	  secondTermOperators.insert(secondTermOperators.end(),
				     it+2,fOperators.end());
	  
	  break;
	}
    }

  Term firstTerm(firstTermOperators,
		 fCoefficients,
		 fOrderInLambda);

  Term secondTerm(secondTermOperators,
		  fCoefficients,
		  fOrderInLambda);

  vector<Term> firstTermNormalOrdered  = firstTerm.normalOrder();
  vector<Term> secondTermNormalOrdered = secondTerm.normalOrder();

  output.insert(output.end(),
		firstTermNormalOrdered.begin(),
		firstTermNormalOrdered.end());
  output.insert(output.end(),
		secondTermNormalOrdered.begin(),
		secondTermNormalOrdered.end());
		
  return output;
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

void Term::print(ostream& outputStream)
{
  if (fCoefficients.size() == 0)
    {
      return;
    }
  bool coefficientIsUnity = false;
  int numberOfFactors = 0;
  if ((fCoefficients.size() == 1) && 
      (fCoefficients[0].isUnity()))
    {
      coefficientIsUnity = true;
    }
  else
    {
      numberOfFactors++;
    }
  if (fOrderInLambda != 0)    numberOfFactors++;
  if (fOperators.size() != 0) numberOfFactors++;

  if (numberOfFactors == 0) 
    {
      outputStream << "1";
      return;
    }

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
      for (vector<Coefficient>::iterator it = fCoefficients.begin();
	   it != fCoefficients.end(); it++)
	{
	  if ((it != fCoefficients.begin()) &&
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
  if (fOperators.size() != 0) 
    {
      for (vector<char>::iterator it = fOperators.begin();
	   it != fOperators.end(); it++)
	{
	  outputStream << *it;
	}
    }
}

void Term::printTex(ostream& outputStream)
{
  bool coefficientIsUnity = false;
  int numberOfFactors = 0;
  if ((fCoefficients.size() == 1) && 
      (fCoefficients[0].isUnity()))
    {
      coefficientIsUnity = true;
    }
  else 
    {
      numberOfFactors++;
    }
  if (fOrderInLambda != 0)    numberOfFactors++;
  if (fOperators.size() != 0) numberOfFactors++;

  if (numberOfFactors == 0) 
    {
      outputStream << "1";
      return;
    }

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
      for (vector<Coefficient>::iterator it = fCoefficients.begin();
	   it != fCoefficients.end(); it++)
	{
	  if ((it != fCoefficients.begin()) &&
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
  if (fOperators.size() != 0) 
    {
      int consecutiveOperators = 1;
      outputStream << fOperators[0];
      for (vector<char>::iterator it = fOperators.begin();
	   it != fOperators.end()-1; it++)
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
    }
}
