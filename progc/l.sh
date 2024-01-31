#!/bin/bash

data=$1
time cat $data | sed -e 1d | cut -f1,5 -d";" | awk -F';' '{dist[$1] += $2} END{for (id in dist) printf "%s %.6f\n", id, dist[id]}' | sort -nr -k2 | head -n10 | sort -nr -k1

# Nothing new here. Check D2 if you want an explaination for the awk script.
# It's 42 past midnight as I'm writing this. I don't want to copypaste.
#
# Just in case though... sources used : https://www.gnu.org/software/gawk/manual/html_node/Basic-Printf.html explains printf
#                                       https://www.gnu.org/software/gawk/manual/html_node/Array-Intro.html explains arrays
#                                       https://www.gnu.org/software/gawk/manual/html_node/For-Statement.html for loop