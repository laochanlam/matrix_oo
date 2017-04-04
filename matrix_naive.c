#include "matrix.h"
#include <stdlib.h>
#include <assert.h>

#define PRIV(x) \
    ((float **) ((x)->priv))

static bool init(Matrix *mat, const int row, const int col)
{
    mat->priv = (float **)malloc(row * sizeof(float *));
    float *data_ptr = (float *)malloc(col * row * sizeof(float));
    for (int i = 0; i < row; i++, data_ptr += col)
        mat->priv[i] = data_ptr;
    mat->row = row;
    mat->col = col;

    if (!mat) return false;
    return true;
}

static bool assign(Matrix *thiz, float** data, int row, int col)
{
    if ( !init(thiz, row, col) ) return false;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            PRIV(thiz)[i][j] = data[i][j];
    return true;
}

static const float epsilon = 1 / 10000.0;

static bool equal(const Matrix *l, const Matrix *r)
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (PRIV(l)[i][j] + epsilon < PRIV(r)[i][j] ||
                    PRIV(r)[i][j] + epsilon < PRIV(l)[i][j])
                return false;
    return true;
}

bool mul(Matrix *dst, const Matrix *l, const Matrix *r)
{
    assert( l->col == r->row && "These 2 matrix cannot be multiplied!");
    if ( !init(dst,l->row,r->col) ) return false;

    for (int i = 0; i < l->row; i++)
        for (int j = 0; j < r->col; j++)
            for (int k = 0; k < l->col; k++)
                PRIV(dst)[i][j] += PRIV(l)[i][k] *
                                   PRIV(r)[k][j];
    return true;
}


MatrixAlgo NaiveMatrixProvider = {
    .assign = assign,
    .equal = equal,
    .mul = mul,
    .init = init,
};
