filename=assignment1writeup

pdf: ps
	ps2pdf ${filename}.ps

ps:	dvi
	dvips -t letter ${filename}.dvi

dvi:
	latex ${filename}
	bibtex ${filename}||true
	latex ${filename}
	latex ${filename}

clean:
	rm -f ${filename}.{ps,toc,aux,aux,out,log,dvi,bbl,blg}
