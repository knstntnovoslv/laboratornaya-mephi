#include<stdio.h>
#include<stdlib.h>
#include<complex.h>
#include"matrix.h"
void* createval(int dimension) {
    Matrix* matrix = malloc(sizeof(Matrix));
    void*** data = malloc(sizeof(void**) * dimension);
    for (int i = 0; i < dimension; i++) {
        data[i] = malloc(sizeof(void**)); //поменять int** на void**
        for (int j = 0; j < dimension; j++) {
            data[i][j] = malloc(sizeof(void*));
        }
    }
    matrix->dimension = dimension;
    matrix->arr = data;
    matrix->sum = NULL;
    matrix->mult = NULL;
    matrix->multscalar = NULL;
    matrix->printvalue = NULL;
    return matrix;
}
void* copy(void* a, int dimension, int size, void* printvalue, void* mult, void* sum, void* multscalar) {
    Matrix* matrix = createval(dimension);
    matrix->printvalue = printvalue;
    matrix->mult = mult;
    matrix->sum = sum;
    matrix->multscalar = multscalar;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            matrix->arr[i][j] = a + (i * dimension + j)*size;
        }
    }
    return matrix;
}
void print(void* a) {
    if (a != NULL) {
        Matrix* A = (Matrix*)a;
        for (int i = 0; i < A->dimension; i += 1) {
            printf("\n");
            for (int j = 0; j < A->dimension; j += 1) {
                A->printvalue(A->arr[i][j]);
            }
        }
        printf("\n");
    }
}

void print_integer(void* a) {
    printf("%d\t", *(int*)a);
}
void print_float(void* a) {
    printf("%.1f\t", *(float*)a);
}
void print_complex(void* a) {
    printf("%.1f %.1f*i\t", creal(*(_Dcomplex*)a), cimag(*(_Dcomplex*)a));
}
int check_dim(void* a, void* b) {
    Matrix* A = (Matrix*)a;
    Matrix* B = (Matrix*)b;
    if (A->dimension == B->dimension) { return 1; }
    else { return 0; }
}
void* sumM(void* a, void* b) {
    Matrix* A = (Matrix*)a;
    Matrix* B = (Matrix*)b;
    int dimension = A->dimension;
    if (check_dim(A, B)) {
        Matrix* matrix = createval(dimension);
        matrix->printvalue = A->printvalue;
        matrix->mult = A->mult;
        matrix->multscalar = A->multscalar;
        matrix->sum = A->sum;
        for (int i = 0; i < dimension; i += 1) {
            for (int j = 0; j < dimension; j += 1) {
                matrix->arr[i][j] = A->sum(A->arr[i][j], B->arr[i][j]);
            }
        }
        return matrix;
    }
    else {
        char check[] = "matrix no sum";
        printf("%s\n", check);
        return NULL;
    }
}
void* vector_product_int(void** a, void** b, int n) {
    int* value = malloc(sizeof(int));
    for (int i = 0; i < n; i += 1) {
        *value += *(int*)(*(a + i)) * *(int*)(*(b + i));
    }
    return value;
}
void* vector_product_float(void** a, void** b, int n) {
    float* value = malloc(sizeof(float));
    for (int i = 0; i < n; i += 1) {
        *value += *(float*)(*(a + i)) * *(float*)(*(b + i));
    }
    return value;
}
void* vector_product_complex(void** a, void** b, int n) {
    _Dcomplex* value = malloc(sizeof(_Dcomplex));
    for (int k = 0; k < n; k += 1) {
        *value += *(_Dcomplex*)(*(a + k)) * *(_Dcomplex*)(*(b + k));
    }
    return value;
}
void* scalar_product_int(void* a, void* b) {
    int* k = malloc(sizeof(int));
    *k = *(int*)a * *(int*)b;
    return k;
}
void* scalar_product_float(void* a, void* b) {
    float* k = malloc(sizeof(float));
    *k = *(float*)a * *(float*)b;
    return k;
}
void* scalar_product_complex(void** a, void* b, int n) {
    _Dcomplex* value = malloc(sizeof(_Dcomplex));
    for (int i = 0; i < n; i += 1) {
        *value += *(_Dcomplex*)(*(a + i)) * *(_Dcomplex*)b;
    }
    return value;
}
void* transpon(void* a) {
    Matrix* A = (Matrix*)a;
    int dimension = A->dimension;
    Matrix* matrix = createval(dimension);
    matrix->printvalue = A->printvalue;
    matrix->mult = A->mult;
    matrix->sum = A->sum;
    matrix->multscalar = A->multscalar;;
    for (int i = 0; i < dimension; i += 1) {
        for (int j = 0; j < dimension; j += 1) {
            matrix->arr[i][j] = A->arr[j][i];
        }
    }
    return matrix;
}
void* multiM(void* a, void* b) {
    Matrix* A = (Matrix*)a;
    Matrix* B = (Matrix*)b;
    if (check_dim(A, B)) {
        int dimension = A->dimension;
        Matrix* matrix = createval(dimension);
        matrix->printvalue = A->printvalue;
        matrix->mult = A->mult;
        matrix->sum = A->sum;
        matrix->multscalar = A->multscalar;
        Matrix* C = transpon(B);
        for (int i = 0; i < A->dimension; i += 1) {
            for (int j = 0; j < B->dimension; j += 1) {
                matrix->arr[i][j] = A->mult(A->arr[i], C->arr[j],C->dimension);
            }
        }
        return matrix;
    }
    char check[] = "Matrix no mult";
    printf("%s\n", check);
    return NULL;

}
void* scalarType(void* a, int x) {
    if (x == 1) {
        int* scalar = (int*)a;
        return scalar;
    }
    else if (x == 2) {
        float* scalar = (float*)a;
        return scalar;
    }
    else if (x == 3) {
        double* scalar = (double*)a;
        return scalar;
    }
}
void* multscalarM(void* a, void* b, int x, int dimension) {
    Matrix *A = (Matrix *) a;
    if (x == 1) {
        int *scalar = scalarType(b, 1);
        Matrix *matrix = createval(dimension);
        matrix->printvalue = A->printvalue;
        matrix->mult = A->mult;
        matrix->sum = A->sum;
        matrix->multscalar = A->multscalar;
        for (int i = 0; i < dimension; i += 1) {
            for (int j = 0; j < dimension; j += 1) {
                matrix->arr[i][j] = A->multscalar(A->arr[i][j], scalar);
            }
        }
        return matrix;

    }
    else if (x == 2) {
        float *scalar = scalarType(b, 2);
        Matrix *matrix = createval(dimension);
        matrix->printvalue = A->printvalue;
        matrix->mult = A->mult;
        matrix->sum = A->sum;
        matrix->multscalar = A->multscalar;
        for (int i = 0; i < dimension; i += 1) {
            for (int j = 0; j < dimension; j += 1) {
                matrix->arr[i][j] = A->multscalar(A->arr[i][j], scalar);
            }
        }
        return matrix;

    }
    else if (x == 3) {
        double *scalar = scalarType(b, 3);
        Matrix *matrix = createval(dimension);
        matrix->printvalue = A->printvalue;
        matrix->mult = A->mult;
        matrix->sum = A->sum;
        matrix->multscalar = A->multscalar;
        for (int i = 0; i < dimension; i += 1) {
            for (int j = 0; j < dimension; j += 1) {
                matrix->arr[i][j] = A->multscalar(A->arr[i][j], scalar);
            }
        }
        return matrix;
    }
}
void* data_sum_int(void* a, void* b) {
    void* k = malloc(sizeof(int));
    *(int*)k = *(int*)b + *(int*)a;
    return k;
}
void* data_sum_float(void* a, void* b) {
    void* k = malloc(sizeof(float));
    *(float*)k = *(float*)b + *(float*)a;
    return k;
}
void* data_sum_complex(void* a, void* b) {
    void* k = malloc(sizeof(_Dcomplex));
    *(_Dcomplex*)k = *(_Dcomplex*)b + *(_Dcomplex*)a;
    return k;
}
void clean(void* a) {
    Matrix* A = (Matrix*)a;
    free(A->arr);
    free(A);
}

