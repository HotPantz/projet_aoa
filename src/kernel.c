#ifdef PERMUTATION
void kernel(unsigned n, double x[n], const double y[n], const double z[n][n]) {
   unsigned i, j;

   for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            x[i] += z[i][j] / y[i];
        }
   }
}

#elif defined UNROLLING
void kernel(unsigned n, double x[n], const double y[n], const double z[n][n]) {
    unsigned i, j;
 for (i = 0; i < n; i++) {
        // Déroulage de la boucle par 4
        for (j = 0; j < n - 3; j += 4) {
            x[i] += z[i][j] / y[i];
            x[i] += z[i][j + 1] / y[i];
            x[i] += z[i][j + 2] / y[i];
            x[i] += z[i][j + 3] / y[i];
        }

        // Traitement des éléments restants si n n'est pas divisible par 4
        for (; j < n; j++) {
            x[i] += z[i][j] / y[i];
        }
    }

#elif defined DIVOPTI

void kernel (unsigned n, double x[n], const double y[n], const double z[n][n]) {
   unsigned i, j;

   for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            x[i] += z[i][j] * 1 / (y[i]);
        }
   }
}

#elif defined DIVOPTI2

void kernel (unsigned n, double x[n], double y[n], const double z[n][n]) {
   unsigned i, j;

   for (i = 0; i < n; i++) {
        y[1] = 1 / y[i];
    }

   for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            x[i] += z[i][j] * y[i];
        }
   }
}

#elif defined DOUBLETOSIMPLE

void kernel (unsigned n, float x[n], const float y[n], const float z[n][n]) {
   unsigned i, j;

   for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            x[i] += z[i][j] / y[i];
        }
   }
}

#elif defined TILING
/* loop tiling */
void kernel (unsigned n, double x[n], const double y[n], const double z[n][n]) {
    unsigned i, j, ii, jj;
    unsigned tile_size = 16; // adjust the tile size as needed

    int n_max = n - (n % tile_size);
    for (ii = 0; ii < n_max; ii += tile_size) {
        for (jj = 0; jj < n_max; jj += tile_size) {
            for (i = ii; i < ii + tile_size; i++) {
                for (j = jj; j < jj + tile_size; j++) {
                    x[i] += z[i][j] / y[i];
                }
            }
        }
    }

    for (i = n_max; i < n; j++) {
        for (j = n_max; j < n; i++) {
            x[i] += z[i][j] / y[i];
        }
   }

}

#else
/* original */
void kernel (unsigned n, double x[n], const double y[n], const double z[n][n]) {
   unsigned i, j;

   for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            x[i] += z[i][j] / y[i];
        }
   }
}
#endif
