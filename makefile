# Makefile

Anharmonics : main.c Polynomial.c DoubleTerm.c Term.c Coefficient.c \
		     Polynomial.h DoubleTerm.h Term.h Coefficient.h
	g++ -o main main.c Polynomial.c DoubleTerm.c Term.c Coefficient.c

tex : Anharmonic.tex
	rm -f Anharmonic.dvi Anharmonic.aux Anharmonic.log Anharmonic.pdf
	latex Anharmonic.tex
	dvipdf Anharmonic.dvi
