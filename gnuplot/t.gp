# Just a histogram. Move along I suppose.
set terminal png size 863, 863
set output "images/t.png"
set style fill solid
set datafile separator ';'
set yrange [0:*]
set boxwidth 0.75
set xtics right
set xtics rotate by 45
set xlabel "TOWN NAMES"
set ylabel "DISTANCE (Km)"
set title "Option -t : Nb routes = f(Towns)"
plot "temp/OUTPUT.txt" using 2:xtic(1) title "Total routes" with boxes lc rgb "#A349A4",\
     "temp/OUTPUT.txt" using 3:xtic(1) title "First town" with boxes lc rgb "#732E73"