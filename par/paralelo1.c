#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define MAXITER 2000

struct complex
{
    double real;
    double imag;
};

int main(int argc, char *argv[])
{
    int NPOINTS;
    int i, j, iter;
    double area, error, ztemp;
    double start, finish;
    struct complex z, c;

    int id, p, total, hs;
    char h[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv);
    MPI_Get_processor_name(h, &hs);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    for (NPOINTS = 500; NPOINTS <= 5000; NPOINTS += 500)
    {

        int total = 0;
        int numoutside = 0;
        start = MPI_Wtime();
        for (i = 0; i < NPOINTS; i++)
        {
            if (i % p == id)
            {
                for (j = 0; j < NPOINTS; j++)
                {
                    c.real = -2.0 + 2.5 * (double)(i) / (double)(NPOINTS) + 1.0e-7;
                    c.imag = 1.125 * (double)(j) / (double)(NPOINTS) + 1.0e-7;
                    z = c;
                    for (iter = 0; iter < MAXITER; iter++)
                    {
                        ztemp = (z.real * z.real) - (z.imag * z.imag) + c.real;
                        z.imag = z.real * z.imag * 2 + c.imag;
                        z.real = ztemp;
                        if ((z.real * z.real + z.imag * z.imag) > 4.0e0)
                        {
                            numoutside++;
                            fflush(stdout);
                            break;
                        }
                    }
                }
                fflush(stdout);
            }
        }
        MPI_Reduce(&numoutside, &total, 1, MPI_INT,
                   MPI_SUM, 0, MPI_COMM_WORLD);
        finish = MPI_Wtime();

        /*
   *  Calculate area and error and output the results
   */

        if (id == 0)
        {
            area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS - total) / (double)(NPOINTS * NPOINTS);
            error = area / (double)NPOINTS;

             printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n", area, error);
             printf("%d = %12.8f seconds\n", NPOINTS, finish - start);
        }
    }
    MPI_Finalize();

    return 0;
}
