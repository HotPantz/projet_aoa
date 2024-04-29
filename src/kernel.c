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

   for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
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

   for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            x[i] += z[i][j] * y[i];
        }
   }
}

#elif defined DOUBLETOSIMPLE

void kernel (unsigned n, float x[n], const float y[n], const float z[n][n]) {
   unsigned i, j;

   for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            x[i] += z[i][j] / y[i];
        }
   }
}

#elif defined OPT2

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
