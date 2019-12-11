#!/usr/bin/env bash
set -e

USAGE="$0 serial|parallel"
SIZES_ARRAY=( 8 50 100 500 )
SERIAL_ADDITIONAL_SIZES_ARRAY=( $(seq 4 1 100) $(seq 100 10 500) $(seq 500 100 1000) $(seq 1000 200 2000) )
TOTAL_THREADS_MAX=8
SEED=3141592

if [ $# -lt 1 ]
then
	echo "$USAGE"
	exit 1
fi

if [ "$1" = "serial" ]
then
	SIZES_ARRAY=( "${SIZES_ARRAY[@]}" "${SERIAL_ADDITIONAL_SIZES_ARRAY[@]}" )
	IFS=$'\n' SIZES_ARRAY=($(sort -h <<<"${SIZES_ARRAY[*]}"))
	IFS=$'\n' SIZES_ARRAY=($(uniq <<<"${SIZES_ARRAY[*]}"))
	unset IFS

	echo -e "Size\tTime"
elif [ $1 = "parallel" ]
then
	echo -e "Size\tThds\tSubthds\tTime"
else
	echo "$USAGE"
	exit 1
fi


for size in "${SIZES_ARRAY[@]}"
do
	if [ $1 = "parallel" ] 
	then
		for (( threads=1; threads <= TOTAL_THREADS_MAX; threads*=2 ))
		do
			for (( subthreads=1; subthreads <= $(( $TOTAL_THREADS_MAX/$threads )); subthreads*=2 ))
			do
				echo -ne "$size\t"
				echo -ne "$threads\t"
				echo -ne "$subthreads\t"

				./src/apsp -Pq --nodes=$size --seed=$SEED -t $threads -j $subthreads | grep time | awk '{ print $NF }'
			done
		done
	else
		echo -ne "$size\t"
		./src/apsp -Sq --nodes=$size --seed=$SEED | grep time | awk '{ print $NF }'
	fi
done
echo "DONE"
