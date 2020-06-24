#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h> 

# define NPOINTS 2000
# define MAXITER 2000


struct complex{
  double real;
  double imag;
};

int main(int argc, char *argv[]){
  int i, j, count, iter, numoutside = 0;
  double area, error, ztemp;
  double start, finish;
  struct complex z, c;
  
  int rank, size, root;
  int *sendbuf, *recvbuf;
  int minsize = 2;
  MPI_Comm comm;
  

  /*
   *   
   *
   *     Outer loops run over npoints, initialise z=c
   *
   *     Inner loop has the iteration z=z*z+c, and threshold test
   */

  MPI_Init(&argc,&argv);
  comm = MPI_COMM_WORLD;
    MPI_Comm_rank( comm, &rank );
    MPI_Comm_size( comm, &size );
  start = MPI_Wtime();  
  
  for (i=0; i<NPOINTS; i++) {
    for (j=0; j<NPOINTS; j++) {
      c.real = -2.0+2.5*(double)(i)/(double)(NPOINTS)+1.0e-7;
      c.imag = 1.125*(double)(j)/(double)(NPOINTS)+1.0e-7;
      z=c;
      
        sendbuf = (int *)malloc( i * sizeof(int) );
        recvbuf = (int *)malloc( i * sizeof(int) );
 
 	MPI_Reduce(sendbuf,recvbuf , i, MPI_INT, MPI_SUM, root, comm);
 
      
      for (iter=0; iter<MAXITER; iter++){
        ztemp=(z.real*z.real)-(z.imag*z.imag)+c.real;
        z.imag=z.real*z.imag*2+c.imag; 
        z.real=ztemp; 
        if ((z.real*z.real+z.imag*z.imag)>4.0e0) {
          numoutside++; 
	  count=numoutside;
          break;
        }
      }
    }
    
   
  }

  finish = MPI_Wtime();  

  /*
   *  Calculate area and error and output the results
   */

  area=2.0*2.5*1.125*(double)(NPOINTS*NPOINTS-numoutside)/(double)(NPOINTS*NPOINTS);
  error=area/(double)NPOINTS;

  printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n",area,error);
  printf("Time = %12.8f seconds\n",finish-start);
   
  MPI_Finalize();
  return 0;
}
