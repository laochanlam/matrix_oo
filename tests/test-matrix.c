#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

MatrixAlgo *matrix_providers[] = {
    &NaiveMatrixProvider,
};

int main()
{
    MatrixAlgo *algo = matrix_providers[0];
    Matrix dst, m, n, fixed;
    float **data = (float **)malloc(8 * sizeof(float *));
    float *data_ptr = (float *)malloc(8 * 8 * sizeof(float));
    for (int i = 0; i < 8; i++, data_ptr += 8)
        data[i] = data_ptr;

    float data1[8][8]
    = {
        { 0,  1,  2,  3,   0,  1,  2,  3, },
        { 4,  5,  6,  7,   4,  5,  6,  7, },
        { 8,  9, 10, 11,   8,  9, 10, 11, },
        { 12, 13, 14, 15, 12, 13, 14, 15, },
        { 0,  1,  2,  3,   0,  1,  2,  3, },
        { 4,  5,  6,  7,   4,  5,  6,  7, },
        { 8,  9, 10, 11,   8,  9, 10, 11, },
        { 12, 13, 14, 15, 12, 13, 14, 15, },
    };


    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            data[i] = data1[i];
    algo->assign(&m, data, 8, 8);

    float data2[8][8]
    = {
        {  16, 17, 18, 19, 16, 17, 18, 19, },
        {  20, 21, 22, 23, 20, 21, 22, 23, },
        {  24, 25, 26, 27, 24, 25, 26, 27, },
        {  28, 29, 30, 31, 28, 29, 30, 31, },
        {  16, 17, 18, 19, 16, 17, 18, 19, },
        {  20, 21, 22, 23, 20, 21, 22, 23, },
        {  24, 25, 26, 27, 24, 25, 26, 27, },
        {  28, 29, 30, 31, 28, 29, 30, 31, },
    };

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            data[i] = data2[i];
    algo->assign(&n, data, 8, 8);

    algo->mul(&dst, &m, &n);

    float ans[8][8]
    = {
        {  304,  316,  328,  340,  304,  316,  328,  340,  },
        {  1008, 1052, 1096, 1140, 1008, 1052, 1096, 1140, },
        {  1712, 1788, 1864, 1940, 1712, 1788, 1864, 1940, },
        {  2416, 2524, 2632, 2740, 2416, 2524, 2632, 2740, },
        {  304,  316,  328,  340,  304,  316,  328,  340,  },
        {  1008, 1052, 1096, 1140, 1008, 1052, 1096, 1140, },
        {  1712, 1788, 1864, 1940, 1712, 1788, 1864, 1940, },
        {  2416, 2524, 2632, 2740, 2416, 2524, 2632, 2740  },
    };

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            data[i] = ans[i];

    algo->assign(&fixed, data, 8, 8);

    if (algo->equal(&dst, &fixed))
        return 0;
    return -1;
}
