#include <fstream>
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

  ofstream texFile;
  texFile.open("Anharmonic_4.tex", fstream::trunc);
  texFile << "\\documentclass{article}"                                           << endl;
  texFile << "\\title{Anharmonic Group Elements as Generated by Machine}"         << endl;
  texFile << "\\author{Ed Rogers}"                                                << endl;
  texFile << "\\date{March 2011}"                                                 << endl;
  texFile << "\\begin{document}"                                                  << endl;
  texFile << "   \\maketitle"                                                     << endl;
									          
  texFile << "\\begin{table}[!hp]"                                                << endl;
  texFile << "\\begin{center}"                                                    << endl;
  texFile << "\\begin{tabular}{rcl}"                                              << endl;
  texFile << "\\textbf{Typed in by hand} & & \\textbf{Computed by machine} \\\\"  << endl;
  texFile << "\\hline"                                                            << endl;


  vector<Term> L0Terms;
  L0Terms.push_back(Term("(1)"));
  Polynomial L0(L0Terms);

  vector<Term> L1Terms;
  L1Terms.push_back(Term("BA"));
  Polynomial L1(L1Terms);

  vector<Term> L2Terms;
  L2Terms.push_back(Term("lambda"));
  Polynomial L2(L2Terms);

  vector<Term> L3Terms;
  L3Terms.push_back(Term("lambda*BA"));
  Polynomial L3(L3Terms);

  vector<Term> L4Terms;
  L4Terms.push_back(Term("lambda*BBAA"));
  Polynomial L4(L4Terms);

  vector<Term> L5Terms;
  L5Terms.push_back(Term("lambda*BBBB"));
  L5Terms.push_back(Term("lambda*AAAA"));
  Polynomial L5(L5Terms);

  vector<Term> L6Terms;
  L6Terms.push_back(Term("lambda*BBBA"));
  L6Terms.push_back(Term("lambda*BAAA"));
  Polynomial L6(L6Terms);

  vector<Term> L7Terms;
  L7Terms.push_back(Term("lambda*BB"));
  L7Terms.push_back(Term("lambda*AA"));
  Polynomial L7(L7Terms);

  vector<Term> L8Terms;
  L8Terms.push_back(Term("lambda*BBBB"));
  L8Terms.push_back(Term("lambda*(-1)*AAAA"));
  Polynomial L8(L8Terms);

  vector<Term> L9Terms;
  L9Terms.push_back(Term("lambda*BBBA"));
  L9Terms.push_back(Term("lambda*(-1)*BAAA"));
  Polynomial L9(L9Terms);

  vector<Term> L10Terms;
  L10Terms.push_back(Term("lambda*BB"));
  L10Terms.push_back(Term("lambda*(-1)*AA"));
  Polynomial L10(L10Terms);



  /* vector<Term> L0Terms; */
  /* L0Terms.push_back(Term("(a_0)")); */
  /* Polynomial L0(L0Terms); */

  /* vector<Term> L1Terms; */
  /* L1Terms.push_back(Term("(a_1)*BA")); */
  /* Polynomial L1(L1Terms); */

  /* vector<Term> L2Terms; */
  /* L2Terms.push_back(Term("lambda*(a_2)")); */
  /* Polynomial L2(L2Terms); */

  /* vector<Term> L3Terms; */
  /* L3Terms.push_back(Term("lambda*(a_3)*BA")); */
  /* Polynomial L3(L3Terms); */

  /* vector<Term> L4Terms; */
  /* L4Terms.push_back(Term("lambda*(a_4)*BBAA")); */
  /* Polynomial L4(L4Terms); */

  /* vector<Term> L5Terms; */
  /* L5Terms.push_back(Term("lambda*(a_5)*BBBB")); */
  /* L5Terms.push_back(Term("lambda*(a_5)*AAAA")); */
  /* Polynomial L5(L5Terms); */

  /* vector<Term> L6Terms; */
  /* L6Terms.push_back(Term("lambda*(a_6)*BBBA")); */
  /* L6Terms.push_back(Term("lambda*(a_6)*BAAA")); */
  /* Polynomial L6(L6Terms); */

  /* vector<Term> L7Terms; */
  /* L7Terms.push_back(Term("lambda*(a_7)*BB")); */
  /* L7Terms.push_back(Term("lambda*(a_7)*AA")); */
  /* Polynomial L7(L7Terms); */

  /* vector<Term> L8Terms; */
  /* L8Terms.push_back(Term("lambda*(a_8)*BBBB")); */
  /* L8Terms.push_back(Term("lambda*(-1*a_8)*AAAA")); */
  /* Polynomial L8(L8Terms); */

  /* vector<Term> L9Terms; */
  /* L9Terms.push_back(Term("lambda*(a_9)*BBBA")); */
  /* L9Terms.push_back(Term("lambda*(-1*a_9)*BAAA")); */
  /* Polynomial L9(L9Terms); */

  /* vector<Term> L10Terms; */
  /* L10Terms.push_back(Term("lambda*(a_10)*BB")); */
  /* L10Terms.push_back(Term("lambda*(-1*a_10)*AA")); */
  /* Polynomial L10(L10Terms); */

  /* vector<Term> L11Terms; */
  /* L11Terms.push_back(Term("lambda^2*(a_11)")); */
  /* Polynomial L11(L11Terms); */

  /* vector<Term> L12Terms; */
  /* L12Terms.push_back(Term("lambda^2*(a_12)*BA")); */
  /* Polynomial L12(L12Terms); */

  /* vector<Term> L13Terms; */
  /* L13Terms.push_back(Term("lambda^2*(a_13)*BBAA")); */
  /* Polynomial L13(L13Terms); */

  /* vector<Term> L14Terms; */
  /* L14Terms.push_back(Term("lambda^2*(a_14)*BBBAAA")); */
  /* Polynomial L14(L14Terms); */

  /* vector<Term> L15Terms; */
  /* L15Terms.push_back(Term("lambda^2*(a_15)*BBBBBB")); */
  /* L15Terms.push_back(Term("lambda^2*(a_15)*AAAAAA")); */
  /* Polynomial L15(L5Terms); */

  /* vector<Term> L16Terms; */
  /* L16Terms.push_back(Term("lambda^2*(a_16)*BBBBBA")); */
  /* L16Terms.push_back(Term("lambda^2*(a_16)*BAAAAA")); */
  /* Polynomial L16(L16Terms); */

  /* vector<Term> L17Terms; */
  /* L17Terms.push_back(Term("lambda^2*(a_17)*BBBBAA")); */
  /* L17Terms.push_back(Term("lambda^2*(a_17)*BBAAAA")); */
  /* Polynomial L17(L17Terms); */

  /* vector<Term> L18Terms; */
  /* L18Terms.push_back(Term("lambda^2*(a_18)*BBBB")); */
  /* L18Terms.push_back(Term("lambda^2*(a_18)*AAAA")); */
  /* Polynomial L18(L18Terms); */

  /* vector<Term> L19Terms; */
  /* L19Terms.push_back(Term("lambda^2*(a_19)*BBBA")); */
  /* L19Terms.push_back(Term("lambda^2*(a_19)*BAAA")); */
  /* Polynomial L19(L19Terms); */

  /* vector<Term> L20Terms; */
  /* L20Terms.push_back(Term("lambda^2*(a_20)*BB")); */
  /* L20Terms.push_back(Term("lambda^2*(a_20)*AA")); */
  /* Polynomial L20(L20Terms); */

  /* vector<Term> L21Terms; */
  /* L21Terms.push_back(Term("lambda^2*(a_21)*BBBBBB")); */
  /* L21Terms.push_back(Term("lambda^2*(-1*a_21)*AAAAAA")); */
  /* Polynomial L21(L21Terms); */

  /* vector<Term> L22Terms; */
  /* L22Terms.push_back(Term("lambda^2*(a_22)*BBBBBA")); */
  /* L22Terms.push_back(Term("lambda^2*(-1*a_22)*BAAAAA")); */
  /* Polynomial L22(L22Terms); */

  /* vector<Term> L23Terms; */
  /* L23Terms.push_back(Term("lambda^2*(a_23)*BBBBAA")); */
  /* L23Terms.push_back(Term("lambda^2*(-1*a_23)*BBAAAA")); */
  /* Polynomial L23(L23Terms); */

  /* vector<Term> L24Terms; */
  /* L24Terms.push_back(Term("lambda^2*(a_24)*BBBB")); */
  /* L24Terms.push_back(Term("lambda^2*(-1*a_24)*AAAA")); */
  /* Polynomial L24(L24Terms); */

  /* vector<Term> L25Terms; */
  /* L25Terms.push_back(Term("lambda^2*(a_25)*BBBA")); */
  /* L25Terms.push_back(Term("lambda^2*(-1*a_25)*BAAA")); */
  /* Polynomial L25(L25Terms); */

  /* vector<Term> L26Terms; */
  /* L26Terms.push_back(Term("lambda^2*(a_26)*BB")); */
  /* L26Terms.push_back(Term("lambda^2*(-1*a_26)*AA")); */
  /* Polynomial L26(L26Terms); */


  /* vector<Term> xTerms; */
  /* xTerms.push_back(Term("(a_0)")); */
  /* xTerms.push_back(Term("(a_1)*BA")); */

  /* xTerms.push_back(Term("lambda*(a_2)")); */
  /* xTerms.push_back(Term("lambda*(a_3)*BA")); */
  /* xTerms.push_back(Term("lambda*(a_4)*BBAA")); */

  /* xTerms.push_back(Term("lambda*(a_5)*BBBB")); */
  /* xTerms.push_back(Term("lambda*(a_5)*AAAA")); */
  /* xTerms.push_back(Term("lambda*(a_6)*BBBA")); */
  /* xTerms.push_back(Term("lambda*(a_6)*BAAA")); */
  /* xTerms.push_back(Term("lambda*(a_7)*BB")); */
  /* xTerms.push_back(Term("lambda*(a_7)*AA")); */
  /* xTerms.push_back(Term("lambda*(a_8)*BBBB")); */
  /* xTerms.push_back(Term("lambda*(-1*a_8)*AAAA")); */
  /* xTerms.push_back(Term("lambda*(a_9)*BBBA")); */
  /* xTerms.push_back(Term("lambda*(-1*a_9)*BAAA")); */
  /* xTerms.push_back(Term("lambda*(a_10)*BB")); */
  /* xTerms.push_back(Term("lambda*(-1*a_10)*AA")); */

  /* xTerms.push_back(Term("lambda^2*(a_11)")); */
  /* xTerms.push_back(Term("lambda^2*(a_12)*BA")); */
  /* xTerms.push_back(Term("lambda^2*(a_13)*BBAA")); */
  /* xTerms.push_back(Term("lambda^2*(a_14)*BBBAAA")); */

  /* xTerms.push_back(Term("lambda^2*(a_15)*BBBBBB")); */
  /* xTerms.push_back(Term("lambda^2*(a_15)*AAAAAA")); */
  /* xTerms.push_back(Term("lambda^2*(a_16)*BBBBBA")); */
  /* xTerms.push_back(Term("lambda^2*(a_16)*BAAAAA")); */
  /* xTerms.push_back(Term("lambda^2*(a_17)*BBBBAA")); */
  /* xTerms.push_back(Term("lambda^2*(a_17)*BBAAAA")); */
  /* xTerms.push_back(Term("lambda^2*(a_18)*BBBB")); */
  /* xTerms.push_back(Term("lambda^2*(a_18)*AAAA")); */
  /* xTerms.push_back(Term("lambda^2*(a_19)*BBBA")); */
  /* xTerms.push_back(Term("lambda^2*(a_19)*BAAA")); */
  /* xTerms.push_back(Term("lambda^2*(a_20)*BB")); */
  /* xTerms.push_back(Term("lambda^2*(a_20)*AA")); */
  /* xTerms.push_back(Term("lambda^2*(a_21)*BBBBBB")); */
  /* xTerms.push_back(Term("lambda^2*(-1*a_21)*AAAAAA")); */
  /* xTerms.push_back(Term("lambda^2*(a_22)*BBBBBA")); */
  /* xTerms.push_back(Term("lambda^2*(-1*a_22)*BAAAAA")); */
  /* xTerms.push_back(Term("lambda^2*(a_23)*BBBBAA")); */
  /* xTerms.push_back(Term("lambda^2*(-1*a_23)*BBAAAA")); */
  /* xTerms.push_back(Term("lambda^2*(a_24)*BBBB")); */
  /* xTerms.push_back(Term("lambda^2*(-1*a_24)*AAAA")); */
  /* xTerms.push_back(Term("lambda^2*(a_25)*BBBA")); */
  /* xTerms.push_back(Term("lambda^2*(-1*a_25)*BAAA")); */
  /* xTerms.push_back(Term("lambda^2*(a_26)*BB")); */
  /* xTerms.push_back(Term("lambda^2*(-1*a_26)*AA")); */
  /* Polynomial x(xTerms); */

  vector<Polynomial> AlgebraElements;
  AlgebraElements.push_back(L0);
  AlgebraElements.push_back(L1);
  AlgebraElements.push_back(L2);
  AlgebraElements.push_back(L3);
  AlgebraElements.push_back(L4);
  AlgebraElements.push_back(L5);
  AlgebraElements.push_back(L6);
  AlgebraElements.push_back(L7);
  AlgebraElements.push_back(L8);
  AlgebraElements.push_back(L9);
  AlgebraElements.push_back(L10);
  /* AlgebraElements.push_back(L11); */
  /* AlgebraElements.push_back(L12); */
  /* AlgebraElements.push_back(L13); */
  /* AlgebraElements.push_back(L14); */
  /* AlgebraElements.push_back(L15); */
  /* AlgebraElements.push_back(L16); */
  /* AlgebraElements.push_back(L17); */
  /* AlgebraElements.push_back(L18); */
  /* AlgebraElements.push_back(L19); */
  /* AlgebraElements.push_back(L20); */
  /* AlgebraElements.push_back(L21); */
  /* AlgebraElements.push_back(L22); */
  /* AlgebraElements.push_back(L23); */
  /* AlgebraElements.push_back(L24); */
  /* AlgebraElements.push_back(L25); */
  /* AlgebraElements.push_back(L26); */

  int FirstTerm = 0;
  for (vector<Polynomial>::iterator it1 = AlgebraElements.begin();
       it1 < AlgebraElements.end()-1; it1++)
    {
      int SecondTerm = FirstTerm+1;
      for (vector<Polynomial>::iterator it2 = it1+1;
	   it2 < AlgebraElements.end(); it2++)
	{
	  Polynomial CommutatorResult = it1->commutedWith(*it2);
	  CommutatorResult.groupTerms();
	  if (CommutatorResult.getTerms().size()+CommutatorResult.getDoubleTerms().size() > 0)
	    {
	      texFile << "$[L" << FirstTerm << ",L" << SecondTerm << "]$ = $";
	      CommutatorResult.printTex(texFile);
	      texFile << "$ \\\\" << endl;
	      texFile << "\\hline" << endl;
	    }
	  SecondTerm++;
	}
      FirstTerm++;
    }



  /* vector<Term> h0Terms; */
  /* h0Terms.push_back(Term("BA")); */
  /* Polynomial h0(h0Terms); */

  /* Polynomial CommutatorResult = h0.commutedWith(x); */

  /* int termsAtATime = 1; */
  /* int linesPrinted = 0; */
  
  /* CommutatorResult.groupTerms(); */
  /* texFile << "$[-X,H_{0}]$ & = & $"; */
  /* CommutatorResult.printTex(texFile,termsAtATime,linesPrinted++); */
  /* texFile << "$ \\\\" << endl; */
  
  /* int termsToPrint = CommutatorResult.getTerms().size()+CommutatorResult.getDoubleTerms().size(); */
  /* int totalLinesToPrint = termsToPrint/termsAtATime; */
  /* if (termsToPrint%termsAtATime != 0) totalLinesToPrint++; */
  /* while (linesPrinted < totalLinesToPrint) */
  /*   { */
  /*     texFile << " & & $"; */
  /*     CommutatorResult.printTex(texFile,termsAtATime,linesPrinted++); */
  /*     texFile << "$"; */
  /*     texFile << " \\\\" << endl; */
  /*   } */

  /* texFile << "\\end{tabular}"                                              << endl; */
  /* texFile << "\\end{center}"                                               << endl; */
  /* texFile << "\\end{table}"                                                << endl << endl;; */


  /* texFile << "\\begin{table}[!hp]"                                                << endl; */
  /* texFile << "\\begin{center}"                                                    << endl; */
  /* texFile << "\\begin{tabular}{rcl}"                                              << endl; */

  /* Polynomial SecondCommutatorResult  = CommutatorResult.commutedWith(x); */

  /* termsAtATime = 1; */
  /* linesPrinted = 0; */
  
  /* SecondCommutatorResult.groupTerms(); */
  /* texFile << "$[-X,[-X,H_{0}]]$ & = & $"; */
  /* SecondCommutatorResult.printTex(texFile,termsAtATime,linesPrinted++); */
  /* texFile << "$ \\\\" << endl; */
  
  /* termsToPrint = SecondCommutatorResult.getTerms().size()+SecondCommutatorResult.getDoubleTerms().size(); */
  /* totalLinesToPrint = termsToPrint/termsAtATime; */
  /* if (termsToPrint%termsAtATime != 0) totalLinesToPrint++; */
  /* while (linesPrinted < totalLinesToPrint) */
  /*   { */
  /*     texFile << " & & $"; */
  /*     SecondCommutatorResult.printTex(texFile,termsAtATime,linesPrinted++); */
  /*     texFile << "$"; */
  /*     texFile << " \\\\" << endl; */
  /*   } */

  texFile << "\\end{tabular}"                                              << endl;
  texFile << "\\end{center}"                                               << endl;
  texFile << "\\end{table}"                                                << endl << endl;;

  texFile << "\\end{document}" << endl;

  return 0;
}
