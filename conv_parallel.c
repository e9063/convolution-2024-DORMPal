#include<stdio.h>
#include<stdlib.h>

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
    int *R = malloc(sizeof(int) * NR);

    omp_set_num_threads(8);
    #pragma omp parallel for schedule(static)
    for(int i = 0; i < NR; i++){
        int sum = 0;
        for(int j = 0; j < NF; j++){
            sum += A[j + i] * F[j];
        }
        R[i] = sum;
    }

    for (int i = 0; i < NR; i++) {
        printf("%d\n", R[i]);
    }

    free(R);

    // implement here

    // ---- free memory ----
    free(F);
    free(A);
    // ---- end free ----
    return 0;
}

