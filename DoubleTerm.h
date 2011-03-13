#ifndef DOUBLETERM_H
#define DOUBLETERM_H

#include "Term.h"
#include "Coefficient.h"
#include <vector>
#include <iostream>
#include <fstream>

class DoubleTerm
{
 private:
  Term fTermPair[2];
  bool fIsPlusTerm;
  std::vector<DoubleTerm> diagonalize();
  bool isDiagonal();

 public:
  DoubleTerm(Term t0,
	     Term t1,
	     bool isPlusTerm = true);

  Term getTerm(unsigned int iTerm);
  bool getIsPlusTerm() { return fIsPlusTerm; };

  void print(std::ostream& outputStream = std::cout);
  void printTex(std::ostream& outputStream = std::cout);

};

#endif
