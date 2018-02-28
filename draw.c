#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  if (points->lastcol == points->cols -1) {
    grow_matrix(points, points->cols + 1);
  }

  points->lastcol += 1;
  
  points->m[0][points->lastcol] = x;
  points->m[1][points->lastcol] = y;
  points->m[2][points->lastcol] = z;
  points->m[3][points->lastcol] = 1;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  add_point(points, x0, y0, z0);
  add_point(points, x1, y1, z1);
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
  int i;

  for (i = 0; i < points->lastcol; i += 2) {
    draw_line(points->m[0][i], points->m[1][i], points->m[0][i+1], points->m[1][i+1], s, c);
  }
}





void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {

  // terms of line function f(x, y) = Ax + By + C
  int a;
  int b;
  
  int x;
  int y;
  int d;

  // Always draw from left to right.
  if (x0 > x1) { // perform swap
    int tmpx;
    int tmpy;

    tmpx = x0;
    x0 = x1;
    x1 = tmpx;

    tmpy = y0;
    y0 = y1;
    y1 = tmpy;
  }

  a = y1 - y0; // delta y
  b = x0 - x1; // negative delta x
  x = x0;
  y = y0;

  if (a >= 0) { // positive slope (or slope of zero)
    
    if (a < -b) { // octant 1
      
      d = 2 * a + b; // equivalent to f(x0+1, y0+1/2)
      while (x < x1) {
	plot(s, c, x, y);
	if (d > 0) { // if midpoint between the two pixels is below the line
	  y++;
	  d += 2 * b;
	}
	x++;
	d += 2 * a;
      }
      plot(s, c, x1, y1);
      
    } else { // octant 2
      
      d = a + 2 * b; // equivalent to f(x0+1/2, y0+1)
      while (y < y1) {
	plot(s, c, x, y);
	if (d < 0) {
	  // if midpoint between the two pixels is to the left of the line
	  x++;
	  d += 2 * a;
	}
	y++;
	d += 2 * b;
      }
      plot(s, c, x1, y1);
    }
    
  } else { // negative slope

    if (a < b) { // octant 7
      
      d = a - 2 * b; // equivalent to f(x0+1/2, y0-1)
      while (y > y1) {
	plot(s, c, x, y);
	if (d > 0) {
	  // if midpoint between the two pixels is to the left of the line
	  x++;
	  d += 2 * a;
	}
	y--;
	d -= 2 * b;
      }
      plot(s, c, x1, y1);
      
    } else { // octant 8
      
      d = 2 * a - b; // equivalent to f(x0+1, y0-1/2)
      while (x < x1) {
	plot(s, c, x, y);
	if (d < 0) { // if midpoint between the two pixels is above the line
	  y--;
	  d -= 2 * b;
	}
	x++;
	d += 2 * a;
      }
      plot(s, c, x1, y1);
    } // end inner else statement
  } // end outer else statement
} // end void draw_line()
