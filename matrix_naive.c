#include "matrix.h"
#include <stdlib.h>
#include <assert.h>

// TODO make it more flexible
struct naive_priv {
    float values[512][512];
};

#define PRIV(x) \
    ((struct naive_priv *) ((x)->priv))

static void assign(Matrix *thiz, float** data, int row, int col)
{
    /* FIXME: don't hardcode row & col */
    thiz->row = row;
    thiz->col = col;

    thiz->priv = malloc(row * col * sizeof(float));
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            PRIV(thiz)->values[i][j] = data[i][j];
}

static const float epsilon = 1 / 10000.0;

static bool equal(const Matrix *l, const Matrix *r)
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (PRIV(l)->values[i][j] + epsilon < PRIV(r)->values[i][j] ||
                    PRIV(r)->values[i][j] + epsilon < PRIV(l)->values[i][j])
                return false;
    return true;
}

bool mul(Matrix *dst, const Matrix *l, const Matrix *r)
{
    assert( l->col == r->row );
    dst->priv = malloc(r->row * l->col * sizeof(float));

    for (int i = 0; i < l->row; i++)
        for (int j = 0; j < r->col; j++)
            for (int k = 0; k < l->col; k++)
                PRIV(dst)->values[i][j] += PRIV(l)->values[i][k] *
                                           PRIV(r)->values[k][j];
    return true;
}

MatrixAlgo NaiveMatrixProvider = {
    .assign = assign,
    .equal = equal,
    .mul = mul,
};
