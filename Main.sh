#!/bin/bash  

#Fonction -h

for entry in `seq 1 $#` do
	if [ $entry == "-h" ] ; then
		echo `cat 'Help.txt'` #le fichier help.txt sera l'explication de ch commande
		exit 0
	fi
done

#verif nombre entrée
if [ $# -lt 2 ] ; then
	echo "mauvais nombre argument"
	exit 1
fi

#raccourci données
data=$1

# faire flag pour empecher le fait qu'une fct tourne en boucle
flag_d1=0
flag_d2=0
flag_l=0
flag_t=0
flag_s=0

#verification que data est un fichier
if [ ! -f "$" ] ; then
	echo "le fichier des données n'est pas mis dans l'appel de fonction"
	exit 2
fi

#verifier quels arguments sont entrée

for i in `seq 2 $#` do
	process=${!i}
	case $process in
			'-d1')
				if [ $flag_d1 -eq 0 ] ; then
					flag_d1=1
				fi
				;;
			'-d2')
				if [ $flag_d2 -eq 0 ] ; then
					flag_d2=1
				fi
				;;
			'-l')
				if [ $flag_l -eq 0 ] ; then
					flag_l=1
				fi
				;;
			'-t')
				if [ $flag_t -eq 0 ] ; then
					flag_t=1
				fi
				;;
			'-s')
				if [ $flag_s -eq 0 ] ; then
					flag_s=1
				fi
				;;
			*) #OUI CECI EST UN DEFAULT
				;;

	esac #CECI EST LA FIN D'UN CASE
done



