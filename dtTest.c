#include <iostream>
#include <vector>
#include <cstdlib>
#include "Polynomial.h"
#include "Term.h"
#include "Coefficient.h"
#include "DoubleTerm.h"

using namespace std;

int main()
{

  Term First("lambda^3*(2)*BBBB");
  Term Second("lambda^3*AAAA");
  vector<Term> myPolyTermVect;
  myPolyTermVect.push_back(First);
  myPolyTermVect.push_back(Second);
  Polynomial myPolynomial(myPolyTermVect);
  myPolynomial.groupTerms();
  myPolynomial.printTex(cout);


  /* DoubleTerm myDT(First,Second,true); */
  /* myDT.printTex(); */
  cout << endl;


  return 0;
}
