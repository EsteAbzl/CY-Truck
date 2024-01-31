#!/bin/bash

data=$1
time cat $data | sed -e 1d | cut -f1,6 -d";" | sort -S 25% --parallel=8 | uniq | cut -f2 -d";" | sort -S 25% --parallel=8 | uniq -c | sort -S 25% -nr --parallel=8 | head -n10 | sed -e 's/^[ \t]*//'
# cat : get output
# sed -e 1d : deletes the first line
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
#          SPACE\t expands SPACE until next character is found. \t specifically means tab.
#                   note : that's not EXACTLY what it is but it's how I always used it.
#                          I don't really have a rigorous understanding of sed, I just used
#                          neovim as my editor of choice for years now so I'm used to doing that
#                          kind of stuff in my scripts...
#          * is any character
#       thus ^[ \t]* means "Any number of spaces before a character"
#   b : nothing.
#   c : nothing
#   this expression thus means :
#   execute a replacement (s) of any ammount of spaces before a character (a) by nothing (b) only doing it once (c)
#   All of this just to remove leading white spaces btw 