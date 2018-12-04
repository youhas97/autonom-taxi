TEXARGS=--shell-escape

design: designspec/*.tex designspec/sections/*.tex
	pdflatex ${TEXARGS} designspec/spec.tex
	pdflatex ${TEXARGS} designspec/spec.tex
	make clean

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

studie: efterstudie/studie.tex efterstudie/sections/*.tex
	pdflatex ${TEXARGS} efterstudie/studie.tex
	pdflatex ${TEXARGS} efterstudie/studie.tex
	pdflatex ${TEXARGS} efterstudie/studie.tex
	make clean

tech:	tekniskrapport/tech.tex tekniskrapport/sections/*.tex
	pdflatex ${TEXARGS} tekniskrapport/tech.tex
	bibtex tech
	pdflatex ${TEXARGS} tekniskrapport/tech.tex
	pdflatex ${TEXARGS} tekniskrapport/tech.tex
	make clean
manual: manual/manual.tex manual/sections/*.tex
	pdflatex ${TEXARGS} manual/manual.tex
	pdflatex ${TEXARGS} manual/manual.tex
	pdflatex ${TEXARGS} manual/manual.tex
	make clean
clean:
	rm -f **.blg *.dvi *.xml *.log *.aux *.out *.toc *.bbl
	rm -f common/img/*converted*
