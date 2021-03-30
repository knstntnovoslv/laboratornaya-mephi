#ifndef MATRIX_H
#define MATRIX_H
#define copy_matrix_int(a, b) copy(a, b, sizeof(int), &print_integer, vector_product_int, data_sum_int, scalar_product_int)
#define copy_matrix_float(a, b) copy(a, b, sizeof(float), &print_float, vector_product_float, data_sum_float, scalar_product_float)
#define copy_matrix_complex(a, b) copy(a, b, sizeof(double _Complex), &print_complex, vector_product_complex, data_sum_complex, scalar_product_complex)
struct Matrix {
    void*** arr;
    int dimension; // число строк, либо столбцов
    void* (*sum)(void*, void*);
    void* (*mult)(void*, void*, int);
    void* (*multscalar)(void*, void*);
    void* (*printvalue)(void*);
};
typedef struct Matrix Matrix;
typedef double _Complex _Dcomplex;
void* createval(int dimension); // создает матрицу
void* copy(void*, int, int, void*, void*, void*, void*); // копирует матрицу
void print(void* a); //выводит матрицу
void print_integer(void* a); // выводит целое число
void print_float(void* a);
void print_complex(void* a); // выводит комплексное число
int check_dim(void* a, void* b); // проверяет можно ли суммировать матрицы и перемножать матрицы
void* data_sum_int(void*, void*);
void* data_sum_float(void*, void*);
void* data_sum_complex(void*, void*);
void* vector_product_int(void** a, void** b, int N);
void* vector_product_float(void** a, void** b, int N);
void* vector_product_complex(void** a, void** b, int N);
void* scalar_product_int(void* a, void* b);
void* scalar_product_float(void* a, void* b);
void* scalar_product_complex(void** a, void* b, int N);
//основные функции
void* sumM(void* a, void* b); //суммирует матрицы
void* multiM(void* a, void* b); //перемножает матрицы
void* multscalarM(void* a, void* b, int x, int dimension);// умножает матрицы на скаляр
void* transpon(void* a); //транспонирует матрицу(необходимо для умножения матриц)
void* scalarType(void* a, int x); // определяет тип скаляра
void clean(void* a); //освобождает память

#endif
