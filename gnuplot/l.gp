set terminal png size 863, 863
set output "images/l.png"
set style fill solid
set datafile separator ' '
set yrange [0:*]
set boxwidth 0.75
set xlabel "ROUTE ID"
set ylabel "DISTANCE (Km)"
set title "Option -l : Distance = f(Route)"
plot 'temp/OUTPUT.txt' using 2:xtic(1) with boxes notitle lc rgb "#A349A4"