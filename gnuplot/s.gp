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

# with filledcurve to get that fill effect
# I'll explain the graphing here.
# Simmilarly to AWK, we use 1-n to refer to the 1-nth field of a line.
# the plot command takes in a file, then you specify how you want it to work with "using"
# 1:2:3... are the data arguments of the plot. we can then add :xtic and :ytic to specify
# which fields will be used for the axis.
# plot 1:2 will plot field 1 against field 2.
# in the case of a filledcurve, we plot 5 on X, and the two Y values are 2 and 3, then 1 as the tic value.
# In this specific case, our X values are just 0-50 to have evened out spaces between each data point
# then we print the data points on X with xtic(1). This means that even if we have 1, 100 and 101 as our
# points, they will be printed out evenly as they're mapped to 1, 2, 3 !
# 2 and 3 are the args for the top and bottom part of the filledcurve plot type. they're the top and bottom parts
# of the area that will be filled. fc just specifies the fill color.
# The next one is just a smooth cubic spline made from the data points of field 4, evened out by being mapped to
# field 5 (which is 1-50 as written above) and we put 1 as the xtic. lc means line color. linewidth is explicit.
# That's just a general idea, there's plenty of plot types. The default types are histograms for strings against numbers,
# and typical graphs for numbers against numbers.
plot "temp/OUTPUT.txt" using 5:2:3:xtic(1) with filledcurve title "Distances Max/Min (Km)" fc rgb "#A349A4",\
     "temp/OUTPUT.txt" using 5:4:xtic(1) with lines title "Distances Average" lc rgb "#732E73" linewidth 3