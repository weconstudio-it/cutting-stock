#!/bin/sh
# Usage: ./batch-execute.sh {strategy} {backtracking} {start} {end}
# Example: ./batch-execute.sh exact depth-search 1 20


## Input parameters
strategy=$1
backtracking=$2
range_start=$3
range_end=$4


echo "# number\t instances\t feasibility\t total allocation\t generated patterns\t execution time"

for i in `seq ${range_start} ${range_end}`
do
    data_file=data/instance${i}.dat
    output=$(./cutting-stock -a -s ${strategy} -b ${backtracking} ${data_file})

    instances=$(echo ${output} | awk -F'|' '{ print $1 }')
    feasible=$(echo ${output} | awk -F'|' '{ print $2 }')
    total_allocation=$(echo ${output} | awk -F'|' '{ print $3 }')
    generated_patterns=$(echo ${output} | awk -F'|' '{ print $4 }')
    execution_time=$(echo ${output} | awk -F'|' '{ print $5 }')

    echo "${i}\t ${instances}\t ${feasible}\t ${total_allocation}\t ${generated_patterns}\t ${execution_time}"
done
