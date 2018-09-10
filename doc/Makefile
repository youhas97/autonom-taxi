TEXARGS=--shell-escape

krav: kravspec/krav.tex kravspec/sections/*.tex
	pdflatex ${TEXARGS} kravspec/krav.tex
	pdflatex ${TEXARGS} kravspec/krav.tex
	make clean

clean:
	rm -f *.blg *.dvi *.xml *.log *.aux *.out *.toc
	rm -f img/*converted*
