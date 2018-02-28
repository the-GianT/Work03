#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

print the matrix
*/
void print_matrix(struct matrix *m) {
  if (m->lastcol) {
    int r, c;

    for (r=0; r < m->rows; r++) {
      for (c=0; c < m->cols; c++)
	printf("%lf ", m->m[r][c]);
      printf("\n");
    }
  } else {
    printf("Error: Uninitialized matrix\n");
  }
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  if (m->rows == m->cols) { // square matrix
    int r, c;
    
    for (r=0; r < m->rows; r++) {
      for (c=0; c < m->cols; c++) {
	if (r == c) // ones on the diagonal
	  m->m[r][c] = 1;
	else // zeros elsewhere
	  m->m[r][c] = 0;
      }
    }
    m->lastcol = m->cols - 1;
  } else {
    printf("Error: not a square matrix\n");
  }
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
  if (a->lastcol && b->lastcol) {
    if (a->cols == b->rows) {
      // struct matrix * new;
      double **tmp;
      int i, j, k;
      int to_add;

      // new = new_matrix(a->rows, b->cols);
      tmp = (double **)malloc(a->rows * sizeof(double *));
      for (i=0;i<a->rows;i++) {
	tmp[i]=(double *)malloc(b->cols * sizeof(double));
      }

      for (i = 0; i < a->rows; i++) {
	for (j = 0; j < b->cols; j++) {
	  to_add = 0;
	  for (k = 0; k < a->cols; k++) {
	    to_add += a->m[i][k] * b->m[k][j];
	  }
	  tmp[i][j] = to_add;
	}
      }
      // new->lastcol = b->cols - 1;
      // free_matrix(b);
      for (i=0;i<b->rows;i++) {
	free(b->m[i]);
      }
      free(b->m);
      // b = new;
      b->m = tmp;
    } else {
      printf("Error: These matrices are incompatible for multiplication.\n");
    }
  } else {
    printf("Error: One or more of these matrices is uninitialized.\n");
  }
}



/*===============================================
  These Functions do not need to be modified
  ===============================================*/

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols 
Returns: 

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)... 
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {
  
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;

  for (r=0; r < a->rows; r++) 
    for (c=0; c < a->cols; c++)  
      b->m[r][c] = a->m[r][c];  
}
