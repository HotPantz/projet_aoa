#include <stdio.h>
#include <stdlib.h> // atoi, qsort
#include <stdint.h>

extern uint64_t rdtsc ();

extern void kernel (unsigned n, double x[n], const double y[n], const double z[n][n]);

static void init_array_2D (int n, double a[n][n]) {
   int i, j;
   for (i=0; i<n; i++)
      for (j=0; j<n; j++)
         a[i][j] = (double) rand() / RAND_MAX;
}

static void init_array_1D (int n, double a[n]) {
   int i;
   for (i=0; i<n; i++)
      a[i] = (double) rand() / RAND_MAX;
}

static void print_array (int n, double a[n], const char *output_file_name) {
   int i;

   FILE *fp = fopen (output_file_name, "w");
   if (fp == NULL) {
      fprintf (stderr, "Cannot write to %s\n", output_file_name);
      return;
   }

   for (i=0; i<n; i++) //1D vector
         fprintf (fp, "%f\n", a[i]);

   fclose (fp);
}

int main (int argc, char *argv[]) {
   /* check command line arguments */
   if (argc != 3) {
      fprintf (stderr, "Usage: %s <size> <output file name>\n", argv[0]);
      return 1;
   }

   /* get command line arguments */
   const unsigned size = atoi (argv[1]); /* problem size */
   const char *output_file_name = argv[2];

   /* allocate arrays
       * x : 1D, size 
       * y : 1D, size
       * z : 2D, array size*size*/
   double (*x) = malloc (size * sizeof x[0]);
   double (*y) = malloc (size * sizeof y[0]);
   double (*z)[size] = malloc (size * size * sizeof z[0][0]);

   /* init arrays */
   srand(0);
   init_array_1D (size, x);
   init_array_1D (size, y);
   init_array_2D (size, z);

   /* print output */
   kernel (size, x, y, z);
   print_array (size, x, output_file_name);

   /* free arrays */
   free (x);
   free (y);
   free (z); //no need for a loop since we're allocating inline

   return EXIT_SUCCESS;
}
