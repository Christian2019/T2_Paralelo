#!/bin/bash
#PBS -m abe
#PBS -V
#PBS -l nodes=grad05:ppn=16:cluster-Grad,walltime=00:30:00
#PBS -M daniel.gery@acad.pucrs.br
#PBS -r n
#PBS -j oe
#PBS -d /home/pp12725/T2_Paralelo/seq
################
echo Running on host 'hostname'
echo
echo Initial Time is 'date'
echo
echo Directory is 'pwd'
echo
echo This jobs runs of the following nodes:
echo 'cat $PBS_NODEFILE | uniq'
echo
echo JOB_ID:
echo 'echo $PBS_JOBID'
echo #################
echo "-----------NPOINTS-500------------"
mpirun -np 1 ./sequencial
echo Final Time is 'date'言
