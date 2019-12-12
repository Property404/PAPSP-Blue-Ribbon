OUTPUT=data.js
FIRST_RUN=../first_run/

SERIAL_FILE=${FIRST_RUN}/serial_out
PARALLEL_FILE=${FIRST_RUN}/parallel_out

mkdir -p parallel_parsed

echo "const SERIAL_TIMES_BY_SIZE = {" > $OUTPUT

cat ${FIRST_RUN}/serial_out | grep -v Size | grep -v DONE | awk '{ print "\""$1"\":"$2"," }' >> $OUTPUT

echo "}" >> $OUTPUT

echo "const PARALLEL_TIMES_BY_SIZE = {" >> $OUTPUT

cat ${PARALLEL_FILE} | grep -v DONE | grep -v Size | awk '{print $2" "$1" "$3 }' | grep "^1 " --color=no | awk '{print $2}' > parallel_parsed/sizes

for i in  1 2 4 8 16
do
cat ${PARALLEL_FILE} | grep -v DONE | grep -v Size | awk '{print $2" "$1" "$3 }' | grep "^$i " --color=no | awk '{print $3}' > parallel_parsed/$i
done
pushd parallel_parsed
paste sizes 1 2 4 8 16 | awk '{ print "\""$1"\":["$2","$3","$4","$5", "$6"],"}' >> ../$OUTPUT
popd
echo "}" >> $OUTPUT;
