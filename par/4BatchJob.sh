#!/bin/bash
#PBS -m abe
#PBS -V
#PBS -l nodes=4:ppn=1:cluster-Grad,walltime=00:30:00
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
echo "-----------4------------"
time mpirun -np 4 ./paralelo1
echo "-----------8------------"
time mpirun -np 8 ./paralelo1
echo "-----------16------------"
time mpirun -np 16 ./paralelo1
echo "-----------32------------"
time mpirun -np 32 ./paralelo1
echo "-----------64------------"
time mpirun -np 64 ./paralelo1
echo Final Time is 'date'言
