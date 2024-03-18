void baseline(unsigned n, double x[n], const double y[n], const double z[n][n]) {
    unsigned i, j;

    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            x[i] += z[i][j] / y[i];
        }
    }
}
