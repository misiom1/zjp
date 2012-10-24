#include <stdio.h>
#include "mpi.h"
#include <time.h>
#include <stdlib.h>
#define TIMER_SCALE  1000000000
long int czas() {
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return ((t.tv_sec * TIMER_SCALE) + t.tv_nsec);
}
main(int argc, char **argv)
{
	int np, rank, i, n, res;
	long int cz;
	if(argc <= 1) n = 1000; /* Pobieramy ilosc liczb do wygenerowania, przykladowo */
	else n = atoi(argv[1]); /* mpirun -np 4 ./montecarlo.out 10000                */
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	srand(time(NULL));
	int nk = 0;
	double x,y,s;
	cz = czas();
	for(i = rank*n/np; i < (rank+1)*n/np; i++) {
		x = ((double)rand() / (RAND_MAX)); // generujemy punkty mniejsze od 1 (dlatego dzielimy przez RAND_MAX)
		y = ((double)rand() / (RAND_MAX));
		if(x*x + y*y <= 1) 
			nk++; // jezeli zalozenia sie zgadzaja to zwiekszamy liczbe pasujacych punktow
	}
	MPI_Reduce(&nk, &res, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); // pobieramy liczbe pasujacych punktow z procesow i sumujemy 
	if(rank == 0) {
		printf("Liczba pkt w kole = %d\n", res);
		printf("Liczba pi = %lf\n", (double)4*res/n);
		printf("Czas wykonania = %lf\n", (double)(czas() - cz)/(double)TIMER_SCALE);
	}
	
	MPI_Finalize();
	return 0;
}
