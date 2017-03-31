#include "matrix.h"
#include "stopwatch.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

MatrixAlgo *matrix_providers[] = {
    &NaiveMatrixProvider,
};

int main()
{
    MatrixAlgo *algo = matrix_providers[0];
    srand(time(NULL));
    Matrix dst, m, n;

    watch_p ctx = Stopwatch.create();

    int row_m = 512;
    int col_m = 512;
    int row_n = 512;
    int col_n = 512;

    /* Using dynamic allocation */
    float **data1 = (float **)malloc(row_m * sizeof(float *));
    float *data_ptr = (float *)malloc(col_m * row_m * sizeof(float));
    for (int i = 0; i < row_m; i++, data_ptr += col_m)
        data1[i] = data_ptr;

    float **data2 = (float **)malloc(row_n * sizeof(float *));
    data_ptr = (float *)malloc(col_n * row_m * sizeof(float));
    for (int i = 0; i < row_n; i++, data_ptr += col_n)
        data2[i] = data_ptr;

    for (int i = 0; i < row_m; i++)
        for (int j = 0; j < col_m; j++)
            data1[i][j] = 1.0  + (rand() / ( RAND_MAX / (20.0-1.0) ) );

    for (int i = 0; i < row_n; i++)
        for (int j = 0; j < col_n; j++)
            data2[i][j] = 1.0  + (rand() / ( RAND_MAX / (20.0-1.0) ) );

    algo->assign(&m, data1, row_m, col_m);
    algo->assign(&n, data2, row_m, col_m);


    Stopwatch.start(ctx);
    algo->mul(&dst, &m, &n);
    double now = Stopwatch.read(ctx);
    Stopwatch.destroy(ctx);
    printf("\n%f",now);
}
