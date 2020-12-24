#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <omp.h>

#define NUM_STEPS 1000000
#define y_scale 6.0
#define MAX_THREADS 8

void serial(int N) {
	double result_e = 0.0;
	double pt_under_curve = 0;	
	double actual_e = exp(1);
	double diff = 0.0;

	double start = omp_get_wtime();
	int nproc = omp_get_num_threads();

	for (int i = 0; i < N; i++) {
		double x = ((double)rand()/RAND_MAX);
		double y = ((double)rand()/RAND_MAX)*(double)(y_scale);

		if (y <= (2*x*(pow(exp(1), pow(x, 2))))) {
			pt_under_curve += 1;
		}	
	}

	// calculate the result
	result_e = 1 + (pt_under_curve / N) * y_scale;

	// calculate the difference
	diff = actual_e - result_e;

	// print the result
	printf("Number of Threads : %d \n", nproc);
	printf("N: Generated %d points\n", N);
	printf("The actual e is %.6f \n", actual_e);
	printf("The estimated e is %.6f \n", result_e); 
	printf("The difference between the actual e and the estimated e is %.6f \n", diff);
	printf("Time : %f seconds\n", omp_get_wtime() - start);
}

void reduction(int N) {
	size_t i;
	double result_e = 0.0;
	double pt_under_curve = 0;	
	double actual_e = exp(1);
	double diff = 0.0;

	double start = omp_get_wtime();

	int nproc;

	#pragma omp parallel private(i)
	{
		unsigned int _tid = omp_get_thread_num();
	    unsigned int tid = _tid;
	    unsigned int _time = (unsigned int)time(0);
	    unsigned int seed = rand_r(&tid);
	    seed ^= _time;

		#pragma omp parallel for reduction(+:pt_under_curve) firstprivate(N, seed) default(none)
		for (i = 0; i < N; i++) {
	        double x = ((double)rand_r(&seed) / RAND_MAX);
			double y = ((double)rand_r(&seed) / RAND_MAX)*(double)(y_scale);

			if (y <= (2*x*(pow(exp(1), pow(x, 2))))) {
				pt_under_curve += 1;
			}
		}
	}

	#pragma omp parallel shared(nproc) default(none)
	{
		#pragma omp single
		nproc = omp_get_num_threads();
	}

	// calculate the result
	result_e = 1 + (pt_under_curve / N) * y_scale;

	// calculate the difference
	diff = actual_e - result_e;

	// print the result
	printf("Number of Threads : %d \n", nproc);
	printf("N: Generated %d points\n", N);
	printf("The actual e is %.6f \n", actual_e);
	printf("The estimated e is %.6f \n", result_e); 
	printf("The difference between the actual e and the estimated e is %.6f \n", diff);
	printf("Time : %f seconds\n", omp_get_wtime() - start);
}

int main() {
	omp_set_num_threads(MAX_THREADS);
	srand (time(NULL));

	// N0
	printf("For N0 : \n");
	serial(NUM_STEPS);
	reduction(NUM_STEPS);

	printf("\n");

	// 10 N0
	printf("For 10 N0 : \n");
	serial(10 * NUM_STEPS);
	reduction(10 * NUM_STEPS);

	printf("\n");

	// 100 N0
	printf("For 100 N0 : \n");
	serial(100 * NUM_STEPS);
	reduction(100 * NUM_STEPS);
}