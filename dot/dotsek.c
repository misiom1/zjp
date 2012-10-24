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
	long int i, n;
	long long int wynik = 0;
	if(argc <= 1) n = 1000000; 
	else n = atoi(argv[1]);
	long int tab1[n], tab2[n], cz;
	srand(time(NULL));
	for(i = 0; i < n; i++) {
		tab1[i] = rand()%1000;
		tab2[i] = rand()%1000;
	}
	cz = czas();
	for(i = 0; i < n; i++) {
		wynik += tab1[i] * tab2[i];
	}
	if(n < 5) {
		for(i = 0; i < n; i++) {
			printf("%ld * %ld\n", tab1[i], tab2[i]);
		}
	}
	printf("Wynik: %lld\n", wynik);
	printf("Czas: %lf\n", (double)(czas() - cz)/(double)TIMER_SCALE);
	return 0;
}
