#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#define TIMER_SCALE  1000000000
long int czas() {
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return ((t.tv_sec * TIMER_SCALE) + t.tv_nsec);
}
main(int argc, char **argv)
{
	int i, j, s, k = 0, n;
	long int cz;
	if(argc <= 1) n = 3; 
	else n = atoi(argv[1]);
	long int *tab1, tab2[n];
	//long int tab1[n][n], tab2[n];
	tab1 = malloc(sizeof(long int) * n * n);
	/*int tab1[3][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	int tab2[3] = {2, 2, 2};*/
	int tab3[n];
	srand(time(NULL));
	for(i = 0; i < n; i++) {
		tab3[i] = 0;
		tab2[i] = rand()%100;
		for(j = 0; j < n; j++) {
			tab1[j*n+i] = rand()%100;
		}
	}
	cz = czas();
	#pragma omp parallel for private(j,i) shared(tab3, tab1, tab2)
	for(i = 0; i < n; i++) {
		#pragma omp parallel for 
		for(j = 0; j < n; j++) {
				tab3[i] += tab1[j*n+i] * tab2[j];
				//tab3[i] += tab1[i][j] * tab2[j];
		}
	}
	printf("Czas wykonania = %lf\n", (double)(czas() - cz)/(double)TIMER_SCALE);
	if(n <= 10) {
		printf("Macierz: \n");
		for(i = 0; i < n; i++) {
			for(j = 0;j < n; j++) {
				printf("%5ld  ", tab1[j*n+i]);
			}
			printf("\n");
		}
		printf("Wektor: \n");
		for(i = 0; i < n; i++) {
			printf("%5ld ", tab2[i]);
		}
		printf("\nWynik: \n");
		for(i = 0; i < n; i++) {
			printf("%d\n", tab3[i]);
		}
		
	}
	return 0;
}
