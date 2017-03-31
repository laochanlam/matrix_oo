#include "matrix.h"
#include <stdlib.h>

struct naive_priv {
    float values[8][8];
};

#define PRIV(x) \
    ((struct naive_priv *) ((x)->priv))

static void assign(Matrix *thiz, Mat8x8 data)
{
    /* FIXME: don't hardcode row & col */
    thiz->row = thiz->col = 8;

    thiz->priv = malloc(8 * 8 * sizeof(float));
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            PRIV(thiz)->values[i][j] = data.values[i][j];
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
    /* FIXME: error hanlding */
    dst->priv = malloc(8 * 8 * sizeof(float));
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 8; k++)
                PRIV(dst)->values[i][j] += PRIV(l)->values[i][k] *
                                           PRIV(r)->values[k][j];
    return true;
}

MatrixAlgo NaiveMatrixProvider = {
    .assign = assign,
    .equal = equal,
    .mul = mul,
};
