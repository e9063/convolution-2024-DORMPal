#include<stdio.h>
#include<stdlib.h>
#include <omp.h>

int main(){
    // ---- input and malloc A, F ----
    int NA, NF;
    scanf("%d %d", &NA, &NF);
    int *A = malloc(sizeof(int) * NA);
    int *F = malloc(sizeof(int) * NF);

    for(int i = 0; i < NA; i++){
        scanf("%d", &A[i]);
    }
    for(int i = 0; i < NF; i++){
        scanf("%d", &F[i]);
    }
    // ---- end input and malloc----

    int NR = NA - NF + 1;
    int *seq = malloc(sizeof(int) * NR);
    int *paral = malloc(sizeof(int) * NR);

    double sseq = omp_get_wtime();
    for(int i = 0; i < NR; i++){
        int sum = 0;
        for(int j = 0; j < NF; j++){
            sum += A[j + i] * F[j];
        }
        seq[i] = sum;
    }
    double eseq = omp_get_wtime() - sseq;

    double sparal = omp_get_wtime();
    omp_set_num_threads(8);
    #pragma omp parallel for schedule(static)
    for(int i = 0; i < NR; i++){
        int sum = 0;
        for(int j = 0; j < NF; j++){
            sum += A[j + i] * F[j];
        }
        paral[i] = sum;
    }
    double eparal = omp_get_wtime() - sparal;


    printf("Sequential time: %.6f\n", eseq);
    printf("Parallel time: %.6f\n", eparal);

    double speed = eseq / eparal;
    printf("Speedup: %.6f\n", speed);

    free(seq);
    free(paral);

    // implement here

    // ---- free memory ----
    free(F);
    free(A);
    // ---- end free ----
    return 0;
}

