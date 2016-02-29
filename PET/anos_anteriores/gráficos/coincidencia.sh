#!/usr/bin/gnuplot

set format y "%.f"
set grid
set xrange [-25:25]
set yrange [-10:50]
set xtics 5
#set ytics 0.5E-4
set mxtics 5
set mytics 5
set samples 10000
set title "Distribuiçao angular"
set xlabel "Angulo(º)"
set ylabel "Taxa de Contagem"
set key top left
set key spacing 1.25
set key box
set key maxrows 2
#set key width 2


set terminal pdf
set output "coincidencia.pdf"

FIT_LIMIT=1.E-14
f1(x)=x/(4*2)
C=340

#fit f1(x) "velocidade.dat" u 1:3:4 via c, b


#fit f1(x) "Apar.dat" u 1:2 via eta



plot "angulo-contagens.dat" u 1:6:7 w yerrorbars lc 3 pt 2 title "Coincidencias"
