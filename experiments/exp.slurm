#!/bin/bash
#SBATCH --time=72:00:00
#SBATCH --chdir=$SCRATCH
#SBATCH --partition=draco
#SBATCH --nodes=1
#SBATCH --output=$HOME/slurm_outputs/%x_%j.out
#SBATCH --error=$HOME/slurm_outputs/%x_%j.err
#BATCH --mail-type=END,FAIL
#BATCH --mail-user=hcpsilva@inf.ufrgs.br

# parameters:
MACHINE="draco_32"
# the experiment ID, defined in the lab-book
EXP_ID=${@[0]}
# the experiment directory
EXP_DIR=${@[1]}

# experiment name (which is the ID and the machine and its core count)
EXP_NAME=${EXP_ID}_${MACHINE}

# not sure if I can trust the sbatch variable
cd $SCRATCH

# prepare our directory
mkdir $EXP_NAME
pushd $EXP_NAME

# copy the code folder
cp -r $EXP_DIR/.. code
pushd code

# execute the experiment
while read -r id otm1 otm2 otm3 counter comp; do
    echo "-> Parameters set to: $id $otm1 $otm2 $otm3 $comp"
    echo

    iteration_output=../results/${OTM1}_${OTM2}_${OTM3}_${counter}_${comp}_${id}

    # alocacao contigua
    if [[ $otm1 == "y" ]]; then
        OPT1="-DOTM_1"
    else
        OPT1=
    fi

    # matriz b transposta
    if [[ $otm2 == "y" ]]; then
        OPT2="-DOTM_2"
    else
        OPT2=
    fi

    # simd
    if [[ $otm3 == "y" ]]; then
        OPT3="-DOTM_3 -fopenmp -fopenmp-simd"
    else
        OPT3=
    fi

    make redo USED_OPT="$OPT1 $OPT2 $OPT3" COMP_OPT="$comp"

    ./build/mult_new 1024 1024 > $iteration_output.raw

    # stress the memory to prevent cache influence between runs
    stress-ng --vm 3 --vm-bytes 75% -t 5s &> /dev/null

    perf stat -o $iteration_output.perf -e $counter ./build/mult_new 1024 1024

    # stress the memory to prevent cache influence between runs
    stress-ng --vm 3 --vm-bytes 75% -t 5s &> /dev/null

    echo
done < $EXP_DIR/runs.plan

popd

tar czf $EXP_DIR/$EXP_NAME.tar.gz *

popd
rm -rf $SCRATCH/*
