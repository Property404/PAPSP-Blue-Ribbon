module load gcc/7.2.0
echo "Result of lscpu command:"
lscpu
echo
echo "Result of numactl command:"
numactl --hardware

echo "Starting serial profile"
./profile.sh serial | tee serial_out
echo "Starting parallel profile"
./profile.sh parallel | tee parallel_out
