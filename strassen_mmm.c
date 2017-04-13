#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef int data_t;
/* Create abstract data type for matrix */
typedef struct {
  long int len;
  data_t *data;
} matrix_rec, *matrix_ptr;

/*****************************************************************************/

/* Create matrix of specified length */
matrix_ptr new_matrix(long int len)
{
  long int i;

  // Allocate and declare header structure 
  matrix_ptr result = (matrix_ptr) malloc(sizeof(matrix_rec));
  if (!result) return NULL;  // Couldn't allocate storage 
  result->len = len;

  // Allocate and declare array 
  if (len > 0) {
    data_t *data = (data_t *) calloc(len*len, sizeof(data_t));
    if (!data) {
	  free((void *) result);
	  printf("\n COULDN'T ALLOCATE STORAGE \n", result->len);
	  return NULL;  // Couldn't allocate storage
	}
	result->data = data;
  }
  else result->data = NULL;

  return result;
}

/* Set length of matrix */
int set_matrix_length(matrix_ptr m, long int index)
{
  m->len = index;
  return 1;
}


/* Return length of matrix */
long int get_matrix_length(matrix_ptr m)
{
  return m->len;
}

/* initialize matrix */
int init_matrix(matrix_ptr m, long int len)
{
  long int i;

  if (len > 0) {
    m->len = len;
    for (i = 0; i < len*len; i++)
      m->data[i] = (data_t)(i);
    return 1;
  }
  else return 0;
}

/* initialize matrix */
int zero_matrix(matrix_ptr m, long int len)
{
  long int i,j;

  if (len > 0) {
    m->len = len;
    for (i = 0; i < len*len; i++)
      m->data[i] = (data_t)(IDENT);
    return 1;
  }
  else return 0;
}

data_t *get_matrix_start(matrix_ptr m)
{
  return m->data;
}

// Russian ***************************************************************************************
matrix_ptr matrix_new(int n) {
  //Создание новой матрицы

  int i;
  matrix_ptr m = (matrix_ptr)malloc(sizeof(int*)*n);
  for(i = 0;i < n;i++) {
    m[i] = (int*)malloc(sizeof(int)*n);
  }
  return m;
}

void matrix_fill(matrix_ptr a, int n) {
  //Заполнение матрицы рандомными значениями

  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      a[i*n +j] = 0;
    }
  }
}

matrix_ptr matrix_mult(matrix_ptr a, matrix_ptr b, int n) {
  //Умножение матриц

  int i, j, k;
  matrix_ptr c = matrix_new(n);
  //long int i, j, k;
  long int get_matrix_length(matrix_ptr m);
  data_t *get_matrix_start(matrix_ptr m);
  //long int length = get_matrix_length(a);
  data_t *a0 = get_matrix_start(a);
  data_t *b0 = get_matrix_start(b);
  data_t *c0 = get_matrix_start(c);
  data_t r;
  
  for (k = 0; k < n; k++)
  {
    for (i = 0; i < n; i++) 
    {
      r = a0[i*n+k];
      for (j = 0; j < n; j++)
      {
		c0[i*n+j] += r*b0[k*n+j];
      }
    }
  }
  return c;
}

matrix_ptr matrix_add(matrix_ptr a, matrix_ptr b, int n) {
  //Сложение матриц

  int i, j, k;
  matrix_ptr c = matrix_new(n);
  //long int i, j, k;
  long int get_matrix_length(matrix_ptr m);
  data_t *get_matrix_start(matrix_ptr m);
  //long int length = get_matrix_length(a);
  data_t *a0 = get_matrix_start(a);
  data_t *b0 = get_matrix_start(b);
  data_t *c0 = get_matrix_start(c);
  data_t r;
  
 
    for (i = 0; i < n; i++) 
    {
      //r = a0[i*n+k];
      for (j = 0; j < n; j++)
      {
		c0[i*n+j] = a0[i*n +j] + b0[i*n + j];
      }
    }
  
  return c;
}
matrix_ptr matrix_sub(matrix_ptr a, matrix_ptr b, int n) {
  //Вычитание матриц

  int i, j, k;
  matrix_ptr c = matrix_new(n);
  //long int i, j, k;
  long int get_matrix_length(matrix_ptr m);
  data_t *get_matrix_start(matrix_ptr m);
  //long int length = get_matrix_length(a);
  data_t *a0 = get_matrix_start(a);
  data_t *b0 = get_matrix_start(b);
  data_t *c0 = get_matrix_start(c);
  data_t r;
  
 
    for (i = 0; i < n; i++) 
    {
      //r = a0[i*n+k];
      for (j = 0; j < n; j++)
      {
		c0[i*n+j] = a0[i*n +j] - b0[i*n + j];
      }
    }
  
  return c;
}

void freememory(matrix_ptr a, int n){
	//Очистка памяти

  int i;
	for (i = 0; i < n; i++){
		free(a[i]);
	}
	free(a);
}

matrix_ptr strassen(matrix_ptr a, matrix_ptr b, int n, int k){
  //Алгоритм штрассена

  int i, j;
  
  //Проверка на размерность текущей матрицы
  if (n <= k){
   matrix_ptr c= matrix_mult(a, b ,n);
    return c;
  }

  int half = n/2;
  matrix_ptr a11, a12, a21, a22, b11, b12, b21, b22;

  a11 = matrix_new(half);
  a12 = matrix_new(half);
  a21 = matrix_new(half);
  a22 = matrix_new(half);
  b11 = matrix_new(half);
  b12 = matrix_new(half);
  b21 = matrix_new(half);
  b22 = matrix_new(half);

  //Создание 4 подматриц для матриц А и В
  for (i = 0; i < half; i++) {
    for(j = 0; j < half; j++) {
      a11[i][j] = a[i][j];
      a12[i][j] = a[i][j+half];
      a21[i][j] = a[i+half][j];
      a22[i][j] = a[i+half][j+half];

      b11[i][j] = b[i][j];
      b12[i][j] = b[i][j+half];
      b21[i][j] = b[i+half][j];
      b22[i][j] = b[i+half][j+half];
    }
  }


  matrix_ptr p1, p2, p3, p4, p5, p6, p7;

  p1 = matrix_new(half);
  p2 = matrix_new(half);
  p3 = matrix_new(half);
  p4 = matrix_new(half);
  p5 = matrix_new(half);
  p6 = matrix_new(half);
  p7 = matrix_new(half);
  p1 = strassen(matrix_add(a11, a22, half), matrix_add(b11, b22, half), half, k);
  p2 = strassen(matrix_add(a21, a22, half), b11, half, k);
  p3 = strassen(a11, matrix_sub(b12, b22, half), half, k);
  p4 = strassen(a22, matrix_sub(b21, b11, half), half, k);
  p5 = strassen(matrix_add(a11, a12, half), b22, half, k);
  p6 = strassen(matrix_sub(a21, a11, half), matrix_add(b11, b12, half), half, k);
  p7 = strassen(matrix_sub(a12, a22, half), matrix_add(b21, b22, half), half, k);


  matrix_ptr c11, c12, c21, c22;

  c11 = matrix_add(matrix_sub(matrix_add(p1, p4, half), p5, half), p7, half);
  c12 = matrix_add(p3, p5, half);
  c21 = matrix_add(p2, p4, half);
  c22 = matrix_add(matrix_add(matrix_sub(p1, p2, half), p3, half), p6, half);
  

  
  matrix_ptr c;

  c = matrix_new(n);
  for (i = 0; i < half; i++) {
    for(j = 0; j < half; j++) {
      c[i][j] = c11[i][j];
      c[i][j+half] = c12[i][j];
      c[i+half][j] = c21[i][j];
      c[i+half][j+half] = c22[i][j];
    }
  }

  freememory(a11, half);
  freememory(a12, half);
  freememory(a21, half);
  freememory(a22, half);
  freememory(b11, half);
  freememory(b12, half);
  freememory(b21, half);
  freememory(b22, half);
  freememory(p1, half);
  freememory(p2, half);
  freememory(p3, half);
  freememory(p4, half);
  freememory(p5, half);
  freememory(p6, half);
  freememory(p7, half);
  freememory(c11, half);
  freememory(c12, half);
  freememory(c21, half);
  freememory(c22, half);

  return c;
}

int main() {

  /*

  Перемножение матриц 1024*1024

    Переход к обычному уумножению при разных значениях k:

      k = 16  : 3.532507
      k = 32  : 3.174222
      k = 64  : 3.139104
      k = 128 : 3.255240
      k = 256 : 3.902180
      k = 512 : 5.226510

  */

  matrix_ptr a, b, c, d;
  int n = 1024, k = 16;
  a = matrix_new(n);
  b = matrix_new(n);
  matrix_fill(a, n);
  matrix_fill(b, n);
  

  printf("Starting:\n");

  clock_t t = clock();
  c = matrix_mult(a, b, n);
  t = clock()-t;
  printf("Обычное умножение - %f\n", ((double)t/CLOCKS_PER_SEC));

  printf("Начало перемножения методом Штрассена \n");

  t = clock();
  d = strassen(a, b, n, k);
  t = clock()-t;

  printf("Умножение методом Штрассена - %f\n", ((double)t/CLOCKS_PER_SEC));
  
  return 0;
}

