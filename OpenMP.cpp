#include <stdio.h> 
#include <omp.h> 

using namespace std;

#define N 1000 
long a[N][N], b[N][N], c[N][N];

void multiplication(int threads) {
    double start_time, end_time;
    int i, j, k;
    printf("Threads: %d ", threads);
    start_time = omp_get_wtime();
    #pragma omp parallel for shared(a, b, c) private(i, j, k) num_threads(threads)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            c[i][j] = 0.0;
            for (k = 0; k < N; k++) c[i][j] += a[i][k] * b[k][j];
        }
    }
    end_time = omp_get_wtime();
    printf("Time: %lf\n", end_time - start_time);
}

int main() {
    #ifdef _OPENMP 
        printf("OpenMP is supported\n");
    #endif 
    int i, j;

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            a[i][j] = b[i][j] = i * j;

    for (i = 1; i <= 8; i++)
         multiplication(i);
}



