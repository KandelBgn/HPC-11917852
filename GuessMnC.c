#include <stdio.h>

/******************************************************************************
 * This program enables a user to specify a slope and intercept, which are 
 * used to output a series of datapoints that can be plotted in a spreadsheet.
 * This program should be used to visualise your estimate of the solution to
 * your linear regression problem.
 * 
 * To compile:
 *   cc -o GuessMnC GuessMnC.c
 * 
 * To run and direct the output into a file:
 *   ./GuessMnC > BgnKndlGuessMnC_First.csv
 * 	return "request to enter value of m n c"
 *   ./GuessMnC 1.10 24.10 > BgnKndlGuessMnC_First.csv
 *   ./GuessMnC 1.5 25 > BgnKndlGuessMnC_Second.csv
 *   ./GuessMnC 1.75 23 > BgnKndlGuessMnC_Third.csv
 *
 * =============================================================
 *        Name: BIGYAN KANDEL  University ID: "1917852"
 *   =============================================================
 * *****************************************************************************/

int main(int argc, char **argv) {
  int i;
  double m;
  double c;
  double x;
  double y;
  
  printf("x,y\n");
  if(argc != 3) {
    fprintf(stderr, "Please enter slope(m) and y-intercept(c)\n");
    return 1;
  }

  sscanf(argv[1], "%lf", &m);
  sscanf(argv[2], "%lf", &c);

  for(i=0; i<100; i++) {
    x = i;
    y = (m * x) + c;
    printf("%0.2lf,%0.2lf\n", x, y);
  }
  
  return 0;
}

