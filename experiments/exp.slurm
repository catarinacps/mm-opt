#!/bin/bash
#SBATCH --time=72:00:00
#SBATCH --chdir=$SCRATCH
#SBATCH --partition=blaise
#SBATCH --nodes=1
#SBATCH --output=$HOME/slurm_outputs/%x_%j.out
#SBATCH --error=$HOME/slurm_outputs/%x_%j.err
#BATCH --mail-type=END,FAIL
#BATCH --mail-user=hcpsilva@inf.ufrgs.br

# parameters:
MACHINE="blaise_88"
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

# to track each individual config execution
exec_id=0

# execute the experiment
while read -r otm1 otm2 otm3 otm4 otm5 comp; do
    echo "-> Parameters set to: $otm1 $otm2 $otm3 $otm4 $otm5 $comp"
    echo

    iteration_output_file=../results/${OTM1}_${OTM2}_${OTM3}_${OTM4}_${OTM5}_${comp}_${exec_id}

    if [[ $otm1 != "-" ]]; then
        OPT1=-D$otm1
    else
        OPT1=
    fi

    if [[ $otm2 != "-" ]]; then
        OPT2=-D$otm2
    else
        OPT2=
    fi

    if [[ $otm3 != "-" ]]; then
        OPT3=-D$otm3
    else
        OPT3=
    fi

    if [[ $otm4 != "-" ]]; then
        OPT4=-D$otm4
    else
        OPT4=
    fi

    if [[ $otm5 != "-" ]]; then
        OPT5=-D$otm5
    else
        OPT5=
    fi

    make redo USED_OPT="$OPT1 $OPT2 $OPT3 $OPT4 $OPT5" COMP_OPT="$comp"

    ./build/mult_old 1024 1024 >> $iteration_output_file.raw

    ./build/mult_new 1024 1024 >> $iteration_output_file.raw

    # TODO: the same but with perf

    # stress the memory to prevent cache influence between runs
    stress-ng --vm 3 --vm-bytes 75% -t 5s &> /dev/null

    ((exec_id++))
    echo
done < $EXP_DIR/runs.plan

popd

tar czf $HOME/$EXP_NAME.tar.gz *

popd
rm -rf $SCRATCH/*
