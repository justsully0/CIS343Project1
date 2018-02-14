#! /bin/bash

## Author: Patrick McMahon
## Objective: Run The Game of Life.
##			  And show off how much time I have...


rFlagTrue(){
	if [[ $xvar != [0-9]* ]] 
		then
			xvar=$((5 + RANDOM % 15))
	fi
	if [[ $yvar != [0-9]* ]] 
		then
			yvar=$((5 + RANDOM % 15))
	fi
	echo "Board size: $xvar x $yvar"
	make -s 
	./a.out $xvar $yvar
}

hFlagTrue(){
	echo "Usage: ./lifeScript.sh [Options]"
	echo "Action: Run The Game of Life."
	echo ""
	echo "Possible options."
	echo ""
	echo "  -r .... Will use random number to generate the board run the game. If ran"
	echo "	  simultaneously with the -x or -y flags it will use the users values."
	echo ""
	echo "  -x .... Followed by the number desired of rows in the game."
	echo "	  If no number included a random number from 5 - 15 will be chosen"
	echo ""
	echo "  -y .... Followed by the number desired of columns in the game."
	echo "	  If no number included a random number from 5 - 15 will be chosen"
	echo ""
	echo "  -h .... This list."
	echo ""
	echo "Examples: "
	echo "	./lifeScript.sh -x 4 -y 5 	--This will set the game board size to 4 x 5"
	echo "	./lifeScript.sh -r 			--This will set both x & y to a random number"
	echo "	./lifeScript.sh -x 5		--This will set y to a random value and set x to 5."
	echo "	./lifeScript.sh 5 5 		--This will set rows = 5 and columns = 5"
	echo "	./lifeScript.sh 5  			--This will set rows = 5"
	echo "  ./lifeScript.sh -y 5		--This will set rows = 5 due to faulty logic, time constraints, and laziness."

}


if [ $# -eq 0 ]	
	then
		echo "Must provide at least one argument. See -h for help."
		exit 1
fi

hFlag=0
rFlag=0


while getopts xyhr option
do
	case "${option}"
 	in
 	x) xvar=${OPTARG};;
 	y) yvar=${OPTARG};;
 	h) ;;
 	r) ;;
 	esac
done


for i
do
	if [ $i = "-x" ] || [ $i = "-y" ] || [ $i = "-r" ]  
		then
			((rFlag=1))
		elif [ $i = '-h' ]
			then
				((hFlag=1))
		elif [[ $xvar == [0-9]* && $i == [0-9]* ]]
			then 
				((yvar = $i))
				((rFlag=1))
		elif [[ $xvar != [0-9]* && $i == [0-9]* ]]
			then 
				((xvar = $i))
				((rFlag=1))
	fi
done

if [ "$rFlag" -eq 1 ]
	then
		rFlagTrue
fi

if [ "$hFlag" -eq 1 ]
	then
		hFlagTrue
fi

exit 0