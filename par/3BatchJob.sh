#!/bin/bash
#PBS -m abe
#PBS -V
#PBS -l nodes=3:ppn=1:cluster-Grad,walltime=01:00:00
#PBS -M daniel.gery@acad.pucrs.br
#PBS -r n
#PBS -j oe
#PBS -d /home/pp12725/T2_Paralelo/par
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
echo "-----------3------------"
time mpirun -np 3 ./paralelo1
echo "-----------6------------"
time mpirun -np 6 ./paralelo1
echo "-----------12------------"
time mpirun -np 12 ./paralelo1
echo "-----------24------------"
time mpirun -np 24 ./paralelo1
echo "-----------48------------"
time mpirun -np 48 ./paralelo1
echo Final Time is 'date'言
