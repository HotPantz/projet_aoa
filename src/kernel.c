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
        for (j = 0; j < n; j++) {
            x[i] += z[i][j] / y[i];
        }
    }
#elif defined DIVOPTI

void kernel (unsigned n, double x[n], const double y[n], const double z[n][n]) {
   unsigned i, j;

   for (i = 0; i < n; i++) {
        y[i] = 1 / y[i];
    }

   for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            x[i] += z[i][j] / y[i];
        }
   }
}
#elif defined ALLOPTI

void kernel (unsigned n, float x[n], float y[n], float z[n][n]) {

    unsigned i, j, ii, jj;
    unsigned tile_size = 16; // adjust the tile size as needed

    for (i = 0; i < n; i++) {
        y[i] = 1 / y[i];
    }

    unsigned n_max = n - (n % tile_size);
    for (ii = 0; ii < n_max; ii += tile_size) {
        for (jj = 0; jj < n_max; jj += tile_size) {
            for (i = ii; i < ii + tile_size; i++) {
                for (j = jj; j < jj + tile_size; j++) {
                    x[i] += z[i][j] * y[i];
                }
            }
        }
    }

    // Boucle pour les éléments restants qui ne rentrent pas dans le bloc
    for (i = n_max; i < n; i++) {
        for (j = 0; j < n; j++) {
            x[i] += z[i][j] * y[i];
        }
    }
}

#elif defined ALLOPTI2_INTRINSICS

#include <immintrin.h>

void kernel (unsigned n, float x[n], float y[n], float z[n][n]) {

    unsigned i, j, ii, jj;
    unsigned tile_size = 16; // adjust the tile size as needed

    for (i = 0; i < n; i++) {
        y[i] = 1 / y[i];
    }

    unsigned n_max = n - (n % tile_size);
    for (ii = 0; ii < n_max; ii += tile_size) {
        for (jj = 0; jj < n_max; jj += tile_size) {
            for (i = ii; i < ii + tile_size; i++) {
                for (j = jj; j < jj + tile_size; j+=4) {
                    __m128 z_vec = _mm_loadu_ps(&z[i][j]);
                    __m128 y_vec = _mm_set1_ps(y[i]);
                    __m128 x_vec = _mm_loadu_ps(&x[i]);
                    __m128 result = _mm_mul_ps(z_vec, y_vec);
                    x_vec = _mm_add_ps(x_vec, result);
                    _mm_storeu_ps(&x[i], x_vec);
                }
            }
        }
    }

    // Boucle pour les éléments restants qui ne rentrent pas dans le bloc
    for (i = n_max; i < n; i++) {
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
void kernel(unsigned n, double x[n], const double y[n], const double z[n][n]) {
    unsigned i, j, ii, jj;
    unsigned tile_size = 16; // ajustez la taille du bloc au besoin

    unsigned n_max = n - (n % tile_size);
    for (ii = 0; ii < n_max; ii += tile_size) {
        for (jj = 0; jj < n_max; jj += tile_size) {
            for (i = ii; i < ii + tile_size; i++) {
                for (j = jj; j < jj + tile_size; j++) {
                    x[i] += z[i][j] / y[i];
                }
            }
        }
    }

    // Boucle pour les éléments restants qui ne rentrent pas dans le bloc
    for (i = n_max; i < n; i++) {
        for (j = 0; j < n; j++) {
            x[i] += z[i][j] / y[i];
        }
    }
}


#elif defined OPT_INTRINSICS

#include <immintrin.h>

void kernel(unsigned n, double x[n], const double y[n], const double z[n][n]) {
    unsigned i, j;

    int n_max = n - (n % 4);
    for (i = 0; i < n_max; i+=4) {
        for (j = 0; j < n; j++) {
            __m256d z_vec = _mm256_loadu_pd(&z[i][j]);
            __m256d y_vec = _mm256_set1_pd(y[i]);
            __m256d x_vec = _mm256_loadu_pd(&x[i]);
            __m256d result = _mm256_div_pd(z_vec, y_vec);
            x_vec = _mm256_add_pd(x_vec, result);
            _mm256_storeu_pd(&x[i], x_vec);
        }
    }

    for (i = n_max; i < n; i++) {
        for (j = 0; j < n; j++) {
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
