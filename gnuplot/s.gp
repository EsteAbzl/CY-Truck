set terminal png size 1380,862
set output "images/s.png"
set datafile separator ';'
set yrange [0:*]
set xrange [*:*]
set xtics right
set xtics rotate by 45
set title "Option -s : Distance = f(Routes)"
set autoscale fix
set xlabel "ROUTE ID"
set ylabel "DISTANCE (Km)"

plot "temp/OUTPUT.txt" using 5:2:3:xtic(1) with filledcurve title "Distances Max/Min (Km)" fc rgb "#A349A4",\
     "temp/OUTPUT.txt" using 5:4:xtic(1) smooth csplines title "Distances Average" lc rgb "#732E73" linewidth 3