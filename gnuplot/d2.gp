# Copy-paste of D1.gp with some data tweaks.

set terminal png size 863, 863
set size 0.975,1
set origin 0.025,0
set output "images/d2.png"
set style fill solid
set datafile separator ';'
set boxwidth 0.75
set xlabel "DRIVER NAMES" rotate by 180
unset ytics
set y2label "DISTANCE (Km)"
set y2tics mirror rotate by 90 center
set label "Option -d1 : Nb routes = f(Driver)" rotate by 90 at graph -0.025,0.5 center
set xtics right rotate by 90

# Because [0:*] doesn't work here for SOME reason we need to use the stats command
# I guess it barely matters, but it does feel less elegant.
stats 'temp/OUTPUT.txt' using 2 nooutput
max_value = STATS_max
set y2range[0:max_value + max_value/16]
plot 'temp/OUTPUT.txt' using 2:xtic(1) axes x1y2 with boxes notitle lc rgb "#A349A4" 