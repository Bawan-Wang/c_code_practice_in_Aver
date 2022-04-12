/**
 * Author: Shiuh-Sheng Yu
 * Department of Information  Management
 * National Chi Nan University
 * Subject: 矩陣相加與相乘
 * Toolkit: gcc
 * Modified Date:2002/08/20
 */
#include <stdio.h>
// 以巨集(macro)定義矩陣元素和動態分配空間的對應關係
// 所謂巨集指的是經由preprocessor(前置處理器)取代原始檔內的字串
#define M(x,i,j) *(x->data + i*x->col + j)

// 定義MATRIX為 struct matrix *
// 也就是說MATRIX之型態為 a pointer to struct matrix
// 至於struct則是C語言讓使用者 "自訂型態" 的關鍵字
typedef struct matrix {
    int row, col;
    double* data;
} *MATRIX;

/**
 * 由檔案讀入一個矩陣
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
    // 動態分配一塊struct matrix大小的空間
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
 * 印出矩陣的內容 
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
 * 矩陣相加
 * 傳回一新矩陣為x,y之和
 */
MATRIX addMatrix(MATRIX x, MATRIX y) {
    int i, j;
    MATRIX m;
    // 檢查兩矩陣的大小是否能相加
    if ((x->row != y->row) || (x->col != y->col)) {
        printf("Matrix dimension mismatch.\n");
        return NULL;
    }
    // 產生新矩陣所需的記憶體空間
    m = (MATRIX) malloc(sizeof(struct matrix));
    m->row = x->row;
    m->col = x->col;
    //產生存放資料所需的空間
    m->data = (double*)malloc(m->row * m->col * sizeof(double));
    // 進行矩陣的加法運算
    for (i =  0; i < m->row; i++) {
        for (j =  0; j < m->col; j++) {
            M(m,i,j) =  M(x,i,j) + M(y,i,j); // 使用macro
        }
    }
    return m;
}
MATRIX multiplyMatrix(MATRIX x, MATRIX y) {
    /* 自己練習看看吧 */

}
/**
 * 將動態分配矩陣的空間還給系統
 */
void freeMatrix(MATRIX x) {
    free(x->data);
    free(x);
}

int main() {
    char buf[100];
    MATRIX a, b, c;
    // 持續讀入運算符號
    // stdin定義於stdio.h, 代表standard input. 在沒有透過作業系統重新指定
    // 的情形下, 一般為鍵盤
    for (; fscanf(stdin,"%99s",buf) != EOF;) {
        if (buf[0] == '+') {
            if ((a = readMatrix(stdin)) == NULL) {
                break; // 有錯誤則跳離開最接近的迴圈或switch敘述(此處為for迴圈)
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
            freeMatrix(a); // 釋放動態分配的矩陣空間
            freeMatrix(b);
            freeMatrix(c);
        } else if (buf[0]=='*') {
            /* 練習看看吧 */
        } else {
            printf("Operator error\n");
            break;
        }
    }
}

