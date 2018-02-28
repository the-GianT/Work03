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
  struct matrix *m0;

  edges = new_matrix(4, 4);
  m0 = new_matrix(4, 4);
  
  // k = 0;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      edges->m[i][j] = j;
      // k++;
    }
  }
  edges->rows = 4;
  edges->cols = 4;
  edges->lastcol = 3;

  printf("Testing ident and print_matrix:\n\n");
  ident(m0);
  print_matrix(m0);
  printf("\n...should be identity matrix.\n\n");
  print_matrix(edges);
  printf("\n...should be integers 0 through 3 in each row.\n");

  printf("\nTesting matrix_mult:\n");
  
  printf("\nMultiplying identity matrix with edge matrix...\n");
  matrix_mult(m0, edges);
  print_matrix(edges);
  printf("\n... should be unchanged.\n\n");

  // Populate m0 with actual numbers, not just 1 and 0
  for (i = 0; i < 4; i++) {
    k = 3;
    for (j = 0; j < 4; j++) {
      m0->m[i][j] = k;
      k--;
    }
  }
  
  print_matrix(m0);
  printf("\n...should be integers 0-3 in /descending/ order in each row.\n\n");
  matrix_mult(m0, edges);
  print_matrix(edges);
  printf("\n...should be 0, 6, 12, 18 in each row.\n");

  /*
  draw_lines(edges, s, c);
  display(s);
  */
  free_matrix( edges );
  free_matrix( m0 );
  // printf("matrix size: %lu\n", sizeof(struct matrix));
}
