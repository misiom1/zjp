#include <stdio.h>
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
	srand(time(NULL));
	int nk = 0;
	double x,y,s;
	cz = czas();
	for(i = 0; i < n; i++) {
		x = ((double)rand() / (RAND_MAX)); // generujemy punkty mniejsze od 1 (dlatego dzielimy przez RAND_MAX)
		y = ((double)rand() / (RAND_MAX));
		if(x*x + y*y <= 1) 
			nk++; // jezeli zalozenia sie zgadzaja to zwiekszamy liczbe pasujacych punktow
	}
	printf("Liczba pkt w kole = %d\n", nk);
	printf("Liczba pi = %lf\n", (double)4*nk/n);
	printf("Czas wykonania = %lf\n", (double)(czas() - cz)/(double)TIMER_SCALE);
	
	return 0;
}
