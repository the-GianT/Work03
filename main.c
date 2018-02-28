#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color c;
  int i, j, k;
  struct matrix *edges;
  struct matrix *ident_m;

  edges = new_matrix(4, 4);
  ident_m = new_matrix(4, 4);
  
  k = 0;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      edges->m[i][j] = k;
      k++;
    }
  }
  edges->rows = 4;
  edges->cols = 4;
  edges->lastcol = 3;

  printf("Test ident and print_matrix:\n\n");
  ident(ident_m);
  print_matrix(ident_m);
  printf("\n...should be identity matrix.\n\n");
  print_matrix(edges);
  printf("\n...should be integers 0 through 15.\n");

  printf("\nTest matrix_mult:\n");
  printf("Multiplying identity matrix with edge matrix...\n");
  matrix_mult(ident_m, edges);
  print_matrix(edges);
  printf("\n... should be unchanged.\n");
  

  /*
  draw_lines(edges, s, c);
  display(s);
  */
  free_matrix( edges );
}
