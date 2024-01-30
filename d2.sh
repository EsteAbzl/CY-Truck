#!/bin/bash

time cat data.csv | sed -e 1d | cut -f5,6 -d";" | awk -F';' '{dist[$2] += $1} END{for (name in dist) printf "%s %.6f\n", name, dist[name]}' | sort -nr -k3 | head -n10

# So, this definitely deserves an explaination. For most of these, see d1.sh. 
# The preceding commands obviously return something of the form "DISTANCE;NAME"
# Now, let's talk about AWK.
# awk is a command line utility that is essentially its own scripting language. It works as follows.
# It has BEGIN{}, normal and END{} statements. The BEGIN {} Statement is ran once at first, then
# the normal {} statements are applied sequencially *once per input line*, and finally, the END {} statement
# is ran. Also, to awk, $n refers to the nth part of the input string (per line), delimited by the delimiter.
# Here, we set it to a semicolon.
# awk also has a very cool feature here, called associated arrays. Essentially, it's like an array in
# any other programming language... except that the type of the contents AND OF THE INDEX (!!!) can be different
# from one another. What this means is that arr[cat] = dog and arr[83] = 94 are both possible with the same array
# when using awk. Here, we use this to our advantage. Also, keep in mind that when doing the += operation on a
# non-initialized variable, it instead acts as =, to prevent undefined behavior.
# awk -F";" : sets the delimiter to be ";".
#   BEGIN {} :      
#               absent here. We don't have a use for it, as arrays don't need to be declared in awk.
#               keep in mind that new variables are always initialized as 0 for the sake of += (or \0 for strings) 
#   {dist[$2] += $1} :
#               this is where the fun begins. We create an array called dist that has for an index $2.
#               remember that our input is of the form DISTANCE;NAME, so $2 is the name of the driver.
#               Also remember that this runs once for every line of input. What this means is that
#               for every line = for every step, we add the value of dist[NAME] with the current
#               $1, so the current distance. So, for example :
#                   10;DRIVER A, we run dist[DRIVER A] += 10
#                   20;DRIVER B         dist[DRIVER B] += 20
#                   40;DRIVER A         dist[DRIVER A] += 40
#                   50;DRIVER C         dist[DRIVER C] += 50
#               and... that's it, that's the hardest part of the processing done. All in 16 characters.
#   END {for (name in dist) printf "%s %.6f\n", name, dist[name]} :
#               Our end statement is simple. awk's for loops are bash/python-styled, so for every known
#               index of dist that has a value that was manually assinged will have the succeeding command
#               ran once. Then, it's a simple printf statement. You may be thinking that this looks just like
#               a C printf statement, and that's because it's exactly the same syntax without parenthesis. In
#               fact, out of curiosity, I checked gAWK's source code, and it literally just takes the printf
#               statement and runs it nearly as-is after some processing in C, fun stuff.
# I mean it's not like ANYONE is going to read all of this. I'm just explaining it all because this is the obvious solution to
# the problem of concat-ing a bunch of values with associated IDs into a single sum with that ID when using awk, so there's 
# bound to be someone on the internet that had the exact same answer as I did. I suppose that this is less of an epxlaination,
# and more of a proof that I came up with this solution on my own rather than just googling it.
#
# Just in case though... sources used : https://www.gnu.org/software/gawk/manual/html_node/Basic-Printf.html explains printf
#                                       https://www.gnu.org/software/gawk/manual/html_node/Array-Intro.html explains arrays
#                                       https://www.gnu.org/software/gawk/manual/html_node/For-Statement.html for loop