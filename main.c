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
  struct matrix *m1;

  c.red = 0;
  c.green = MAX_COLOR;
  c.blue = 0;

  clear_screen(s);

  edges = new_matrix(4, 4);
  m0 = new_matrix(4, 4);
  m1 = new_matrix(4, 4);

  printf("Testing ident and print_matrix:\n\n");
  printf("Turning m0 into identity matrix...\n");
  ident(m0);
  print_matrix(m0);
  printf("\n...should be identity matrix.\n\n\n");

  printf("Populating m1 with numbers...\n");
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      m1->m[i][j] = j;
      // k++;
    }
  }
  m1->rows = 4;
  m1->cols = 4;
  m1->lastcol = 3;
  
  print_matrix(m1);
  printf("\n...should be integers 0 through 3 in each row.\n\n");

  printf("\nTesting matrix_mult:\n");
  
  printf("\nMultiplying m0 (identity matrix) with m1...\n");
  matrix_mult(m0, m1);
  print_matrix(m1);
  printf("\n... should be unchanged.\n\n\n");

  printf("Populating m0 with actual numbers, not just 1 and 0...\n");
  for (i = 0; i < 4; i++) {
    k = 3;
    for (j = 0; j < 4; j++) {
      m0->m[i][j] = k;
      k--;
    }
  }
  
  print_matrix(m0);
  printf("\n...should be integers 0-3 in /descending/ order in each row.\n\n\n");
  printf("Multiplying m0 with m1...\n");
  matrix_mult(m0, m1);
  print_matrix(m1);
  printf("\n...should be 0, 6, 12, 18 in each row.\n\n");

  printf("\nTest add_point and add_edge:\n\n");
  add_edge(edges, 40, 40, 0, 140, 200, 0);
  add_edge(edges, 140, 200, 0, 300, 40, 0);
  add_edge(edges, 300, 40, 0, 40, 40, 0);
  print_matrix(edges);
  printf("\n...should be\n40 140 140 300 300 40\n40 200 200 40 40 40\n0 0 0 0 0 0\n1 1 1 1 1 1\n");

  
  draw_lines(edges, s, c);
  display(s);
  free_matrix( edges );
  free_matrix( m0 );
  free_matrix( m1 );
  // printf("matrix size: %lu\n", sizeof(struct matrix));

  return 0;
}
