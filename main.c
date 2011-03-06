#include <iostream>
#include <vector>
#include <cstdlib>
#include "Polynomial.h"
#include "Term.h"
#include "Coefficient.h"

using namespace std;

int main()
{

  vector<unsigned int> alphas;
  Coefficient firstCoefficient(4.0,alphas);

  vector<Coefficient> firstTermCoefficients;
  firstTermCoefficients.push_back(firstCoefficient);

  vector<char> firstTermOperators;
  firstTermOperators.push_back('B');
  firstTermOperators.push_back('A');
  firstTermOperators.push_back('B');
  firstTermOperators.push_back('A');

  Term firstTerm(firstTermOperators,
		 firstTermCoefficients,
		 1);

  vector<Term> normalOrderedTerms;
  normalOrderedTerms = firstTerm.normalOrder();

  Polynomial firstPolynomial(normalOrderedTerms);

  firstPolynomial.simplify();

  /* vector<Term> unorderedTerms; */
  /* unorderedTerms.push_back(firstTerm); */

  /* Polynomial firstPolynomial(unorderedTerms); */

  firstPolynomial.print();
  cout << endl;

  return 0;
}
