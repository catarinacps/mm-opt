#!/bin/bash
#SBATCH --time=72:00:00
#SBATCH --chdir=.
#SBATCH --partition=draco
#SBATCH --nodes=1
#SBATCH --output=%x_%j.out
#SBATCH --error=%x_%j.err
#BATCH --mail-type=END,FAIL
#BATCH --mail-user=hcpsilva@inf.ufrgs.br

# machine:
MACHINE=${SLURMD_HOSTNAME}_${SLURM_CPUS_ON_NODE}

# parameters:
# the experiment ID, defined in the lab-book
EXP_ID=$1
# the experiment directory
EXP_DIR=$2
# hardware counters
COUNTER_LIST=(cycles L1-dcache-load-misses instructions l1d.replacement)

# experiment name (which is the ID and the machine and its core count)
EXP_NAME=${EXP_ID}_${MACHINE}

# go to the scratch dir
cd $SCRATCH

# and clean everything
rm -rf *

# prepare our directory
mkdir $EXP_NAME
pushd $EXP_NAME

# copy the code folder
cp -r $(dirname $EXP_DIR) code
mkdir results
output_csv=$(pwd)/results/$EXP_NAME.csv
pushd code

# init the csv results file
echo "rep_id,time,$(IFS=, echo $COUNTER_LIST),optm_1,optm_2,optm_3,comp" > $output_csv

# execute the experiment
while read -r id otm1 otm2 otm3 comp; do
    echo "-> Parameters set to: $id $otm1 $otm2 $otm3 $comp"
    echo

    # alocacao contigua
    OPT1=$([ $otm1 = "y" ] && echo "-DOTM_1")
    # matriz b transposta
    OPT2=$([ $otm2 = "y" ] && echo "-DOTM_2")
    # simd
    OPT3=$([ $otm3 = "y" ] && echo "-DOTM_3 -fopenmp -fopenmp-simd")

    # compilação
    make redo USED_OPT="$OPT1 $OPT2 $OPT3" COMP_OPT="$comp"

    # init the line with the exec id
    csv_line=${id}

    # get the time obs
    time_obs=$(./build/mult 1024 1024)

    # add the time
    csv_line=${csv_line},${time_obs}

    # stress the memory to prevent cache influence between runs
    stress-ng --vm 3 --vm-bytes 75% -t 5s &> /dev/null

    for counter in $COUNTER_LIST; do
        perf stat -o temp.perf -e $counter ./build/mult 1024 1024

        # get the observation
        perf_obs=$(grep -w $counter temp.perf | awk '{print $1}' | tr -d ,)

        # add the metric to the line
        csv_line=${csv_line},${perf_obs}

        # stress the memory to prevent cache influence between runs
        stress-ng --vm 3 --vm-bytes 75% -t 5s &> /dev/null
    done

    # commit the line
    echo $csv_line >> $output_csv

    echo
done < $EXP_DIR/runs.plan

popd

# pack everything and send to the exp dir
tar czf $EXP_DIR/$EXP_NAME.tar.gz *

popd
rm -rf $SCRATCH/*
