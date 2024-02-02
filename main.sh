#!/bin/bash  

# Memorise the value of the last useful comand ('$?')
# when we need to test it.
exitNumber=0 

# Look for the '-h' option
for entry in $* ; do
  if [ $entry = "-h" ] ; then
    man ./help
    exit 0
  fi
done

# Check option number
if (( $# < 2 )) ; then
  man ./help
  exit 1
fi

# Shortcut to the target file
data=$1

# Check if $data is a file
if [ ! -f $data ] ; then
  man ./help
  exit 2
fi


# Create directories. -v option print the creation of the folders
mkdir -p temp
mkdir -p images
mkdir -p data

# Copy the data into data/
cp $data data/data.csv
data=data/data.csv

# Compile C code in the "progc" directory
 make -s -C progc/
 exitNumber=$?
 if (( $exitNumber != 0 )) ; then
  echo
  echo "$0: Make didn't work as expected and ended with: $exitNumber"
  exit 3
fi

echo Compiled C code

# Setting output format of time command
TIMEFORMAT="Program ran in %E seconds."

case $2 in
  '-d1')
    echo "Starting D1 process.."
    time cat $data | sed -e 1d | cut -f1,6 -d";" | sort -S 25% --parallel=8 | uniq | cut -f2 -d";" | sort -S 25% --parallel=8 | uniq -c | sort -S 25% -nr --parallel=8 | head -n10 | sed -e 's/^[ ]*//' | awk '{printf "%s %s;%i\n", $2, $3, $1}' > temp/OUTPUT.txt
    #
    # EXPLAINING D1 :
    #
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
#   a : ^[ ]*
#       ^[ ] is a special expression
#           ^ means "start of the line"
#           [ABC] means any of A, B, or C and in any ammount
#           * is any character
#       thus ^[ ]* means "Any number of spaces before a character that isn't a whitespace"
#   b : nothing.
#   c : nothing
#   this expression thus means :
#   execute a replacement (s) of any ammount of spaces before a character (a) by nothing (b) only doing it once (c)
#   All of this just to remove leading white spaces btw  
    
    gnuplot gnuplot/d1.gp
    exit
    # Hash is a built-in bash command that checks if a command exists
    # just redirect both stdout and stderr to null, we just want the exit code
    # if we don't have Imagemagick installed... eh, tough luck. It's a standard
    # on most common distributions. I mean my Arch install didn't have it, but
    # the alternative would be to manually draw every box to simmulate an
    # horizontal histogram since GNUPlot can't make them natively. So y'know what,
    # rotating with imagemagick and just not doing it if it fails is A-Okay by me.
    hash convert >/dev/null 2>/dev/null
    EXIT_CODE=$?
    if (($? == 0)); then
      convert images/d1.png -rotate 90 images/d1.png
    fi
    if (($? != 0)); then
      # What ? You don't have imagemagick ? Okay SURELY you have FFMPEG installed then !
      # I mean, come on, it's on most distros too, and it came preinstalled with Arch,
      # surely that means that you have it !
      hash ffmpeg >/dev/null 2>/dev/null
      EXIT_CODE=$?
      if ($? == 0); then
        # This applies the ffmpeg "transpose" filter, which effectively rotates stuff
        ffmpeg -i images/d1.png -vf "transpose=1" images/d1.png
      fi
    fi
  ;;
  '-d2')
    echo "Starting D2 process.."
    time cat $data | sed -e 1d | cut -f5,6 -d";" | awk -F';' '{dist[$2] += $1} END{for (name in dist) printf "%s;%.6f\n", name, dist[name]}' | sort -nr -t";" -k2 -S 25% --parallel=8 | head -n10 > temp/OUTPUT.txt

#
# EXPLAINING D2 :   
#
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
    
    gnuplot gnuplot/d2.gp
    hash convert >/dev/null 2>/dev/null
    EXIT_CODE=$?
    if (($? == 0)); then
      convert images/d2.png -rotate 90 images/d2.png
    fi
    if (($? != 0)); then
      hash ffmpeg >/dev/null 2>/dev/null
      EXIT_CODE=$?
      if (($? == 0)); then
        ffmpeg -i images/d2.png -vf "transpose=1" images/d2.png
      fi
    fi
  ;;
  '-l')
    echo "Starting L process.."
    time cat $data | sed -e 1d | cut -f1,5 -d";" | awk -F';' '{dist[$1] += $2} END{for (id in dist) printf "%s %.6f\n", id, dist[id]}' | sort -nr -k2 | head -n10 | sort -nr -k1 > temp/OUTPUT.txt
    # If you understood the explainations for D2 and D1, this one should be trivial :)
    gnuplot gnuplot/l.gp  
  ;;
  '-t')
  echo "Starting T process.."
    time ./progc/bin/cy-trucks.exe $data -t > temp/OUTPUT.txt
    gnuplot gnuplot/t.gp
  ;;
  '-s')
  echo "Starting S process.."
    time ./progc/bin/cy-trucks.exe $data -s | head -n50 > temp/OUTPUT.txt
    gnuplot gnuplot/s.gp
  ;;
  *)
    man ./help
  esac