#!/bin/sh

# echo "\\\\newpage" >> $2
echo "\\\\section{$1}" >> $2
echo "\\\\tt{" >> $2
source-highlight -f latexcolor -i $1 -o STDOUT >> $2
echo "}" >> $2
