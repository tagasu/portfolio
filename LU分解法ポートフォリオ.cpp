

# include <stdio.h>

#define MMAX 20
#define NMAX 30

void main(void)
{
    float a[NMAX][NMAX + MMAX];
    int n, m;
    int i, j, k, l;

    /* Read Data */
    printf("Input Matrix Size: n, m ? ");         
    scanf_s("%d%d", &n, &m);                     
    printf("\nInput Coefficient Matrix A\n");     
    for (i = 0; i < n; i++) {
        printf("? A(%2d, j), j=1,%2d : ", i + 1, n);
        for (j = 0; j < n; j++)
            scanf_s("%g", &a[i][j]);
    }
    printf("\nInput R.H.S. Vectors B\n");           
    for (i = 0; i < n; i++) {
        printf("? B(%2d, j), j=1,%2d : ", i + 1, m);
        for (j = 0; j < m; j++)
            scanf_s("%g", &a[i][n + j]);
    }

    /* Write Data */
    printf("\nLinear Equation System: AX=B\n");
    printf("* Size of Matrix: n,m=%d,%d\n", n, m);
    printf("* A'=[A|B]\n");  
    for (i = 0; i < n; i++) {
        for (j = 0; j < n + m; j++)
            printf("%6.2g", a[i][j]);
        printf("\n");
    }

    
    for (j = 1; j < n + m; j++)
        a[0][j] /= a[0][0];
    for (k = 1; k < n; k++) {
        for (i = k; i < n; i++)
            for (l = 0; l < k; l++)
                a[i][k] -= a[i][l] * a[l][k];
        for (j = k + 1; j < n + m; j++) {
            for (l = 0; l < k; l++)
                a[k][j] -= a[k][l] * a[l][j];
            a[k][j] /= a[k][k];
        }
    }

    printf("\nMatrix A' after LU decomposition and Forward reduction\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n + m; j++)
            printf("%15.6e", a[i][j]);
        printf("\n");
    }

    
    for (k = n - 1; k >= 0; --k) {
        for (j = 0; j < m; j++) {
            for (l = k + 1; l < n; l++) {
                a[k][n + j] -= a[k][l] * a[l][n + j];
            }
        }
    }

    
    printf("\nSolutions\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            printf("%15.6e", a[i][n + j]);
        printf("\n");
    }
}

