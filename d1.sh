#!/bin/bash

time cat data.csv | cut -f1,6 -d";" | sort | uniq | cut -f2 -d";" | sort | uniq -c | sort -nr | head -n10 | sed -e 's/^[ \t]*//'
# cat : get output
# cut -f1,6 -d";" : get the route ID and the name
# sort : group the same route IDs
# uniq : delete non-unique route IDs
# cut -f3 -d";" : only keep names. We now have a sorted list of names where each name is one route taken by the name
# uniq -c : delete duplicate names but count the ammount of times that they appear. We now have a list of the ammount of routes taken by each name
# sort -nr : sort the names by the preceding number of unique routes
# head -n10 : get the ten first names of the sort
# sed : Okay now that's more complex.
#   -e : execute sed script
#   s/a/b/c : selection and replacement operation
#   a : ^[ \t]*
#       ^[] is a special expression
#          SPACE\t expands SPACE until next character is found
#          * is any character
#       thus ^[ \t]* means "Any number of spaces before a character"
#   b : nothing.
#   c : nothing
#   this expression thus means :
#   execute a replacement (s) of any ammount of spaces before a character (a) by nothing (b) only doing it once (c)
#   All of this just to remove leading white spaces btw 