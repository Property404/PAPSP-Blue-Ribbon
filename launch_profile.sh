module load gcc/7.2.0
echo "Result of lscpu command:"
lscpu
echo
echo "Result of numactl command:"
numactl --hardware


echo "Starting serial profile (auto)"
./profile.sh serial -1 | tee result_serial

for i in -1 2 4 8
do
	echo "Starting parallel profile ($i)"
	./profile.sh parallel $i | tee result_parallel_${i}
done
