#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<complex.h>
#include"matrix.h"
int main() {
    int k = 5;
    int* pk = &k;
    float y = 7.4f;
    float* py =&y;
    int nums1[] = {
            9, 7, 3,
            4, 5, 6,
            7, 8, 9
    };
    int nums2[] = {
            -1, -2, -3,
            -4, -5, -6,
            -7, -8, -9
    };
    int nums3[] = {
            100, 101, 102,
            103, 104, 105,
            106, 107, 108
    };
    float nums4[] = {
            1.0f, 3.0f, 5.0f,
            7.0f, 9.4f, 11.2f,
            13.9f, 15.6f, 17.1f
    };
    float nums5[] = {
            94.21f, 34.6f, 41.55f,
            10.7f, 56.0f, 39.8f,
            190.64f, 1.23f, 71.8f

    };
    _Dcomplex nums6[] = {
            5.0 + 2.0 * I, 1.0 + 3.4 * I,
            25.0 + 0.8 * I, 41.3 + 9,7 * I
    };
    _Dcomplex nums7[] = {
            1.0 + 6.0 * I, 2.0 + 7.0 * I,
            3.2 + 7.3 * I, 5.0 + 1.0 * I
    };
    Matrix* m1 = copy_matrix_int(nums1, 3);
    Matrix* m2 = copy_matrix_int(nums2, 3);
    Matrix* m3 = copy_matrix_int(nums3, 3);
    Matrix* m4 = copy_matrix_float(nums4, 3);
    Matrix* m5 = copy_matrix_float(nums5, 3);
    Matrix* m6 = copy_matrix_complex(nums6, 2);
    Matrix* m7 = copy_matrix_complex(nums7, 2);
    print(m1);
    print(m2);
    print(m3);
    print(m4);
    print(m5);
    print(sumM(m1, m2));
    print(sumM(m4, m5));
    print(multiM(m1,m2));
    print(multiM(m4,m5));
    print(sumM(m6, m7));
    print(multiM(m6,m7));
    print(multscalarM(m2, pk, 1, 3));
    print(multscalarM(m4, py, 2, 3));
    return 0;
}
