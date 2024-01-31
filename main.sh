#!/bin/bash  

# Memorise the value of the last useful comand ('$?')
# when we need to test it.
exitNumber=0 

printHelpFile(){
  show=`man ./help`
  echo "$show"
}


echoHelp(){
   echo "Try 'bash $0 -h' for more information."
   echo
}


# Look for the '-h' option
for entry in $* ; do
	if [ $entry = "-h" ] ; then
		printHelpFile
		exit 0
	fi
done

# Check option number
if (( $# < 2 )) ; then
	echo "$0: Too few arguments"
  echoHelp
	exit 1
fi

# Shortcut to the target file
data=$1

# Check if $data is a file
if [ ! -f $data ] ; then
  echo "$0: The data file hasn't been found, it must be the first argument."
  echoHelp
	exit 2
fi

# Flags to prevent doing the same option multiple time
# Using binary comparison, with a singular '&':
#       0x001 & 0x010 = 0 (false)           (= 1 & 2)
#   but 0x001 & 0x011 = 1 (true)            (= 1 & 3)
#   and 0x001 & 0x001 = 1. Note that it only work with ones.
#
# Thus a variable can carry the flags all at once
activeFlags=0x00000
oldActiveFlags=0x00000

FLAG_d1=0x00001 
FLAG_d2=0x00010
FLAG_l=0x00100
FLAG_t=0x01000
FLAG_s=0x10000


# Create directories. -v option print the creation of the folders
mkdir -v temp
mkdir -v images
echo ---

# Compile C code in the "progc" directory
make -C progc/
exitNumber=$?
if (( $exitNumber != 0 )) ; then
  echo
  echo "$0: Make didn't work as expected and ended with: $exitNumber"
  exit 3
fi

echo ---

# Go througt all the given option
for(( i=2 ; i<=$# && ! (( $activeFlags == 0x11111 )) ; i++)) ; do
	option=${!i}
  UseShellInstead=0 # Set to 1 if we use Bash process instead of C process

  # Activating the Flags for the curent option
	case $option in
    '-d1')
      if ! (( $activeFlags & $FLAG_d1)) ; then
        activeFlags=$(( activeFlags + FLAG_d1 ))

        bash progc/d1.sh $data
        #exitNumber=$?
        UseShellInstead=1
      fi
    ;;
    '-d2')
      if ! (( $activeFlags & $FLAG_d2)) ; then
        activeFlags=$(( activeFlags + FLAG_d2 ))

        bash progc/d2.sh $data
        #exitNumber=$?
        UseShellInstead=1
      fi
    ;;
    '-l')
      if ! (( $activeFlags & $FLAG_l)) ; then
        activeFlags=$(( activeFlags + FLAG_l ))

        bash progc/l.sh $data
        #exitNumber=$?
        UseShellInstead=1
      fi
    ;;
    '-t')
      if ! (( $activeFlags & $FLAG_t)) ; then
        activeFlags=$(( activeFlags + FLAG_t ))
      fi
    ;;
    '-s')
      if ! (( $activeFlags & $FLAG_s)) ; then
        activeFlags=$(( activeFlags + FLAG_s ))
      fi
    ;;
    *) #DEFAULT
      echo "$0: Invalid option '$option'"
      echoHelp
      # Program doesn't stop there in case other options work
    ;;
	esac # End of the case

  # If the Flags are uptaded:
  if (( $oldActiveFlags != $activeFlags)) ; then

    if (( ! $UseShellInstead )) ; then
      # We give the curent option to the process
      ./progc/bin/cy-trucks.exe $data $option > OUTPUT.TXT
      exitNumber=$?
    fi

    if (( exitNumber != 0)) ; then
      echo
      echo "$0: The process for $option didn't work as expected and ended with: $exitNumber"
    fi
  fi
  
  oldActiveFlags=$activeFlags
  
done
echo ---

# Chec if at least one process started
if (( $activeFlags == 0 )) ; then
  echo "$0: We did not find any correct option."
  echoHelp
  exit 4
fi


# Next is to print the results
