#!/bin/sh

cat genpdf/header > src.tex
find src/ -name "*.cpp" -exec genpdf/add_code_to_tex.sh \{\} src.tex \;
cat genpdf/footer >> src.tex
pdflatex src.tex
pdflatex src.tex