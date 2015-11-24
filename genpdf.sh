#!/bin/sh

cat genpdf/header > genpdf/src.tex
find src/ -name "*.cpp" -exec genpdf/add_code_to_tex.sh \{\} genpdf/src.tex \;
cat genpdf/footer >> genpdf/src.tex
pdflatex genpdf/src.tex
pdflatex genpdf/src.tex
rm src.aux src.log src.toc