#!/usr/bin/gnuplot -persist
set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2
plot "output.dat" using 1:2 with lines linestyle 1
