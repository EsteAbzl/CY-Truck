# image size
set terminal png size 863, 863
# creates a slight offset to the right for the future title
set size 0.975,1
set origin 0.025,0
# sets the output
set output "images/d1.png"
# fills the bars
set style fill solid
# data processing stuff
set datafile separator ';'
# make the bars thinner
set boxwidth 0.75
# explicit
set xlabel "DRIVER NAMES" rotate by 180
# removes the left Y axis, replaces it with the right one
unset ytics
set y2label "NB ROUTES"
# rotates the tics to make them look good when we'll rotate the whole thing
set y2tics mirror rotate by 90 center
# adding a title won't work because we want it rotated, so we just
# add it centered relative to the graph's left side and rotated. 
set label "Option -d1 : Nb routes = f(Driver)" rotate by 90 at graph -0.025,0.5 center
# rotates the x tics
set xtics right rotate by 90

# Because [0:*] doesn't work here for SOME reason we need to use the stats command
# I guess it barely matters, but it does feel less elegant.
# stats reads a data file, you specify the field with 2 here, and nooutput prevents spitting data to console or the graph.
stats 'temp/OUTPUT.txt' using 2 nooutput
# it stores a bunch of variables, here we use STATS_max. I'll let you guess what it does.
max_value = STATS_max
set y2range[0:max_value + max_value/16]
# extremely simple boxes graph. axes specifies that we use the x1 and y2 axes for graphing.
plot 'temp/OUTPUT.txt' using 2:xtic(1) axes x1y2 with boxes notitle lc rgb "#A349A4"