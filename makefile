# Makefile

Anharmonics : main.c Polynomial.c Term.c Coefficient.c \
		     Polynomial.h Term.h Coefficient.h
	keychain --nogui /home/ed/.ssh/dd4550; \
	. ${HOME}/.keychain/`hostname`-sh; \
	rsync -avz -e "ssh -p 53704" ${HOME}/CVS/ "ed@192.168.1.67:~/CVS/"
	g++ -o main main.c Polynomial.c Term.c Coefficient.c
