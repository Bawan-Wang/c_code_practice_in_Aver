/**
 * Author: Shiuh-Sheng Yu
 * Department of Information  Management
 * National Chi Nan University
 * Subject: �x�}�ۥ[�P�ۭ�
 * Toolkit: gcc
 * Modified Date:2002/08/20
 */
#include <stdio.h>
// �H����(macro)�w�q�x�}�����M�ʺA���t�Ŷ����������Y
// �ҿץ��������O�g��preprocessor(�e�m�B�z��)���N��l�ɤ����r��
#define M(x,i,j) *(x->data + i*x->col + j)

// �w�qMATRIX�� struct matrix *
// �]�N�O��MATRIX�����A�� a pointer to struct matrix
// �ܩ�struct�h�OC�y�����ϥΪ� "�ۭq���A" ������r
typedef struct matrix {
    int row, col;
    double* data;
} *MATRIX;

/**
 * ���ɮ�Ū�J�@�ӯx�}
 */
MATRIX readMatrix(FILE* f) {
    int x, y, i, j;
    char keyword[256];
    MATRIX m;
    /* read in keyword "matrix" */
    fscanf(f, "%255s", keyword);
    if (strcmp(keyword,"matrix")!=0) {
        printf("keyword error: %s",keyword);
        return NULL;
    }
    // �ʺA���t�@��struct matrix�j�p���Ŷ�
    m =  (MATRIX) malloc(sizeof(struct matrix));
    /* read in matrix dimension to x y */
    fscanf(f,"%d", &x);
    fscanf(f,"%d", &y);
    m->row = x;
    m->col = y;
    m->data = (double*)malloc(x * y * sizeof(double));
    /* read in x*y double and store them to m->data */
    for (i = 0; i < x; i++) {
        for (j = 0; j < y; j++) {
            fscanf(f,"%lf",m->data + i*y + j);
        }
    }
    return m;
}

/**
 * �L�X�x�}�����e 
 */
void printMatrix(MATRIX x) {
    int i, j;
    for (i = 0; i < x->row; i++) {
        for ( j= 0; j < x->col; j++) {
            printf("%lf", M(x,i,j));
        }
        printf("\n");
    }
}
/**
 * �x�}�ۥ[
 * �Ǧ^�@�s�x�}��x,y���M
 */
MATRIX addMatrix(MATRIX x, MATRIX y) {
    int i, j;
    MATRIX m;
    // �ˬd��x�}���j�p�O�_��ۥ[
    if ((x->row != y->row) || (x->col != y->col)) {
        printf("Matrix dimension mismatch.\n");
        return NULL;
    }
    // ���ͷs�x�}�һݪ��O����Ŷ�
    m = (MATRIX) malloc(sizeof(struct matrix));
    m->row = x->row;
    m->col = x->col;
    //���ͦs���Ʃһݪ��Ŷ�
    m->data = (double*)malloc(m->row * m->col * sizeof(double));
    // �i��x�}���[�k�B��
    for (i =  0; i < m->row; i++) {
        for (j =  0; j < m->col; j++) {
            M(m,i,j) =  M(x,i,j) + M(y,i,j); // �ϥ�macro
        }
    }
    return m;
}
MATRIX multiplyMatrix(MATRIX x, MATRIX y) {
    /* �ۤv�m�߬ݬݧa */

}
/**
 * �N�ʺA���t�x�}���Ŷ��ٵ��t��
 */
void freeMatrix(MATRIX x) {
    free(x->data);
    free(x);
}

int main() {
    char buf[100];
    MATRIX a, b, c;
    // ����Ū�J�B��Ÿ�
    // stdin�w�q��stdio.h, �N��standard input. �b�S���z�L�@�~�t�έ��s���w
    // �����ΤU, �@�묰��L
    for (; fscanf(stdin,"%99s",buf) != EOF;) {
        if (buf[0] == '+') {
            if ((a = readMatrix(stdin)) == NULL) {
                break; // �����~�h�����}�̱��񪺰j���switch�ԭz(���B��for�j��)
            }
            printMatrix(a);
            if ((b = readMatrix(stdin)) == NULL) {
                break;
            }
            printf("+\n");
            printMatrix(b);
            printf("=\n");
            if ((c = addMatrix(a, b)) == NULL) {
                break;
            }
            printMatrix(c);
            printf("\n");
            freeMatrix(a); // ����ʺA���t���x�}�Ŷ�
            freeMatrix(b);
            freeMatrix(c);
        } else if (buf[0]=='*') {
            /* �m�߬ݬݧa */
        } else {
            printf("Operator error\n");
            break;
        }
    }
}

