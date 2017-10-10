filename=assignment1writeup

default: all

pdf: ps
	ps2pdf ${filename}.ps

ps:	dvi
	dvips -t letter ${filename}.dvi

dvi:
	latex ${filename}
	bibtex ${filename}||true
	latex ${filename}
	latex ${filename}

concurrency:
		gcc -pthread -o pc producer_consumer.c mersenne.c rdtester.c

all:
	@$(MAKE) -f Makefile pdf
	@$(MAKE) -f Makefile concurrency

clean:
	rm -f ${filename}.{ps,toc,aux,aux,out,log,dvi,bbl,blg}
	rm -f pc
