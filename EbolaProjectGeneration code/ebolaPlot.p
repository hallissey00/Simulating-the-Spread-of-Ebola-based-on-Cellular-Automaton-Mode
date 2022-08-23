
set terminal png size 500,500

set output 'ebolaPlot.png'

set title 'Spread of Ebola Virus over generations'

plot "gnuplot.dat" using 1:2 title "Sus" with lines, \
"gnuplot.dat" using 1:3 title "Exposed" with lines, \
"gnuplot.dat" using 1:4 title "Infected" with lines, \
"gnuplot.dat" using 1:5 title "Recovered" with lines, \
"gnuplot.dat" using 1:6 title "Dead" with lines ;
