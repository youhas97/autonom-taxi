TEXARGS=--shell-escape

krav: kravspec/krav.tex kravspec/sections/*.tex
	pdflatex ${TEXARGS} kravspec/krav.tex
	bibtex krav
	pdflatex ${TEXARGS} kravspec/krav.tex
	pdflatex ${TEXARGS} kravspec/krav.tex
	make clean

plan: projektplan/plan.tex projektplan/sections/*.tex
	pdflatex ${TEXARGS} projektplan/plan.tex
	pdflatex ${TEXARGS} projektplan/plan.tex
	pdflatex ${TEXARGS} projektplan/plan.tex
	make clean

skiss: systemskiss/skiss.tex systemskiss/sections/*.tex
	pdflatex ${TEXARGS} systemskiss/skiss.tex
	pdflatex ${TEXARGS} systemskiss/skiss.tex
	pdflatex ${TEXARGS} systemskiss/skiss.tex
	make clean
clean:
	rm -f **.blg *.dvi *.xml *.log *.aux *.out *.toc *.bbl
	rm -f img/*converted*
