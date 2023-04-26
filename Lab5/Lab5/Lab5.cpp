#include<iostream>
#include"omp.h"

using namespace std;

const long long arr_size = 10000;

long long arr_2d[arr_size][arr_size];

void init_2d_arr();
long long sum_2d(int, int, int);
long long min_2d(int, int, int);

int main() {

	init_2d_arr();

	omp_set_nested(1);
	double t1 = omp_get_wtime();

#pragma omp parallel sections
	{

#pragma omp section
		{
			min_2d(1, 1, arr_size);
			min_2d(1, 2, arr_size);
			min_2d(2, 1, arr_size);
			min_2d(5, 1, arr_size);
			min_2d(1, 5, arr_size);
			min_2d(5, 5, arr_size);

			/*min_2d(1, 2, arr_size);
			min_2d(1, 3, arr_size);
			min_2d(1, 4, arr_size);
			min_2d(2, 1, arr_size);
			min_2d(3, 1, arr_size);
			min_2d(4, 1, arr_size);
			min_2d(2, 2, arr_size);
			min_2d(3, 3, arr_size);
			min_2d(4, 4, arr_size);
			min_2d(5, 5, arr_size);
			min_2d(6, 6, arr_size);*/
		}

#pragma omp section
		{
			sum_2d(1, 1, arr_size);
			sum_2d(1, 2, arr_size);
			sum_2d(2, 1, arr_size);
			sum_2d(5, 1, arr_size);
			sum_2d(1, 5, arr_size);
			sum_2d(5, 5, arr_size);



			/*sum_2d(1, 2, arr_size);
			sum_2d(1, 3, arr_size);
			sum_2d(1, 4, arr_size);
			sum_2d(2, 1, arr_size);
			sum_2d(3, 1, arr_size);
			sum_2d(4, 1, arr_size);
			sum_2d(2, 2, arr_size);
			sum_2d(3, 3, arr_size);
			sum_2d(4, 4, arr_size);
			sum_2d(5, 5, arr_size);
			sum_2d(6, 6, arr_size);*/
		}
	}
	double t2 = omp_get_wtime();

	cout << "Total time - " << t2 - t1 << " seconds" << endl;
	return 0;
}

void init_2d_arr() {
	long long c = arr_size * arr_size;

	for (long long i = 0; i < arr_size; i++) {
		for (long long j = 0; j < arr_size; j++) {
			arr_2d[i][j] = c;
			c--;
			//arr_2d[i][j] = arr_size * arr_size - (i * arr_size + (j));
		}
	}


	for (long long j = 0; j < arr_size; j++) {
		arr_2d[100][j] = -99999;
	}
}

long long sum_2d(int num_threads, int num_internal_threads, int arr_lenght) {
	long long sum = 0;
	double t1 = omp_get_wtime();

#pragma omp parallel for reduction(+:sum) num_threads(num_threads)	
	for (int i = 0; i < arr_lenght; i++) {
#pragma omp parallel for reduction(+:sum) num_threads(num_internal_threads)
		for (int j = 0; j < arr_lenght; j++) {
			sum += arr_2d[i][j];
		}
	}

	double t2 = omp_get_wtime();

	//printf("sum: %d num_thread: %d threads worked - %f seconds\n", sum, num_threads, t2 - t1);

	cout << "sum: " << sum << " num_thread: " << num_threads << " threads worked - " << t2 - t1 << " seconds" << endl;

	return sum;
}

long long min_2d(int num_thread, int num_internal_threads, int arr_len) {
	long long min = arr_2d[0][0];
	long long min_index = 0;
	double t1 = omp_get_wtime();



#pragma omp parallel for num_threads(num_thread)
	for (long long i = 0; i < arr_len; i++)
	{
		long long sum_row = 0;

#pragma omp parallel for reduction(+:sum_row)
		for (long long j = 0; j < arr_len; j++)
		{
			sum_row = sum_row + arr_2d[i][j];
		}

		if (min > sum_row)
		{
#pragma omp critical
			if (min > sum_row) {
				min = sum_row;
				min_index = i;
			}
		}
	}


	double t2 = omp_get_wtime();

	//printf("min: %d row index: %d num_thread: %d num_internal_threads: %d threads worked - %f seconds\n", min, min_index, num_thread, num_internal_threads, t2 - t1);
	cout << "min: " << min << " row index: " << min_index << " num_thread: " << num_thread << " num_internal_threads: " << num_internal_threads << " threads worked - " << t2 - t1 << " seconds" << endl;

	return min;
}