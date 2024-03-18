#include <stdio.h>
#include <stdlib.h> // atoi, qsort
#include <stdint.h>

#define NB_METAS 31

extern uint64_t rdtsc ();

// TODO: adjust for each kernel
extern void kernel (unsigned n, double x[n], const double y[n], const double z[n][n]);

// TODO: adjust for each kernel
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

static int cmp_uint64 (const void *a, const void *b) {
   const uint64_t va = *((uint64_t *) a);
   const uint64_t vb = *((uint64_t *) b);

   if (va < vb) return -1;
   if (va > vb) return 1;
   return 0;
}

int main (int argc, char *argv[]) {
   /* check command line arguments */
   if (argc != 4) {
      fprintf (stderr, "Usage: %s <size> <nb warmup repets> <nb measure repets>\n", argv[0]);
      return 1;
   }

   /* get command line arguments */
   const unsigned size = atoi (argv[1]); /* problem size */
   const unsigned repw = atoi (argv[2]); /* number of warmup repetitions */
   const unsigned repm = atoi (argv[3]); /* number of repetitions during measurement */

   uint64_t tdiff [NB_METAS];

   unsigned m;
   for (m=0; m<NB_METAS; m++) {
      printf ("Metarepetition %u/%d: running %u warmup instances and %u measure instances\n", m+1, NB_METAS,
              m == 0 ? repw : 1, repm);

      unsigned i;

      /* allocate arrays. TODO: adjust for each kernel */
      double (*z)[size] = malloc (size * size * sizeof z[0][0]);
      double (*x) = malloc (size * sizeof x[0]);
      double (*y) = malloc (size * sizeof y[0]);

      /* init arrays */
      srand(0);
      init_array_1D (size, x);
      init_array_1D (size, y);
      init_array_2D (size, z);

      /* warmup (repw repetitions in first meta, 1 repet in next metas) */
      if (m == 0) {
         for (i=0; i<repw; i++)
            kernel (size, x, y, z);
      } else {
         kernel (size, x, y, z);
      }

      /* measure repm repetitions */
      const uint64_t t1 = rdtsc();
      for (i=0; i<repm; i++) {
         kernel (size, x, y, z);
      }
      const uint64_t t2 = rdtsc();
      tdiff[m] = t2 - t1;

      /* free arrays. TODO: adjust for each kernel */
      free (x);
      free (y);
      free (z);
   }

   const uint64_t nb_inner_iters = size * size * size * repm; // TODO adjust for each kernel
   qsort (tdiff, NB_METAS, sizeof tdiff[0], cmp_uint64);
   printf ("MIN %lu RDTSC-cycles (%.2f per inner-iter)\n",
           tdiff[0], (float) tdiff[0] / nb_inner_iters);
   printf ("MED %lu RDTSC-cycles (%.2f per inner-iter)\n",
           tdiff[m/2], (float) tdiff[m/2] / nb_inner_iters);
   const float stab = (tdiff[m/2] - tdiff[0]) * 100.0f / tdiff[0];
   if (stab >= 10)
      printf ("BAD STABILITY: %.2f %%\n", stab);
   else if (stab >= 5)
      printf ("AVERAGE STABILITY: %.2f %%\n", stab);
   else
      printf ("GOOD STABILITY: %.2f %%\n", stab);

   return EXIT_SUCCESS;
}
