# alice.chizhova.lab
#include <stdio.h>
#include <stdlib.h>

void free_matrix(int **matrix, size_t n) {
    if (matrix == NULL) return;
    for (size_t i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int **concat_rows(
    const int * const * lhs, size_t n1, size_t m1,
    const int * const * rhs, size_t n2, size_t m2
) {
    if ((n1 > 0 && lhs == NULL) || (n2 > 0 && rhs == NULL)) {
        return NULL;
    }
    size_t max_rows = (n1 > n2) ? n1 : n2;
    int **result = (int **)malloc(max_rows * sizeof(int *));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < max_rows; ++i) {
        size_t current_cols = 0;
        if (i < n1) current_cols += m1;
        if (i < n2) current_cols += m2;

        result[i] = (int *)malloc(current_cols * sizeof(int));
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        size_t idx = 0;
        if (i < n1) {
            for (size_t j = 0; j < m1; ++j) {
                result[i][idx++] = lhs[i][j];
            }
        }
        if (i < n2) {
            for (size_t j = 0; j < m2; ++j) {
                result[i][idx++] = rhs[i][j];
            }
        }
    }
    return result;
}

int read_matrix(int ***matrix, size_t n, size_t m) {
    *matrix = (int **)malloc(n * sizeof(int *));
    if (*matrix == NULL) return 2;
    
    for (size_t i = 0; i < n; ++i) {
        (*matrix)[i] = (int *)malloc(m * sizeof(int));
        if ((*matrix)[i] == NULL) {
            free_matrix(*matrix, i);
            return 2;
        }
        for (size_t j = 0; j < m; ++j) {
            if (scanf("%d", &(*matrix)[i][j]) != 1) {
                free_matrix(*matrix, i + 1);
                return 1;
            }
        }
    }
    return 0;
}

int main(void) {
    size_t n1, m1, n2, m2;
    int **lhs = NULL;
    int **rhs = NULL;
    int **result = NULL;

    printf("Enter size of matrix 1 (n1 m1): ");
    if (scanf("%zu %zu", &n1, &m1) != 2 || n1 == 0 || m1 == 0) {
        return 1;
    }

    printf("Enter elements of matrix 1:\n");
    int status = read_matrix(&lhs, n1, m1);
    if (status == 1) return 1;
    if (status == 2) return 2;

    printf("Enter size of matrix 2 (n2 m2): ");
    if (scanf("%zu %zu", &n2, &m2) != 2 || n2 == 0 || m2 == 0) {
        free_matrix(lhs, n1);
        return 1;
    }

    printf("Enter elements of matrix 2:\n");
    status = read_matrix(&rhs, n2, m2);
    if (status == 1) {
        free_matrix(lhs, n1);
        return 1;
    }
    if (status == 2) {
        free_matrix(lhs, n1);
        return 2;
    }

    result = concat_rows((const int * const *)lhs, n1, m1, 
                         (const int * const *)rhs, n2, m2);

    if (result == NULL) {
        free_matrix(lhs, n1);
        free_matrix(rhs, n2);
        return 2;
    }

    size_t max_rows = (n1 > n2) ? n1 : n2;
    printf("\nResult:\n");
    for (size_t i = 0; i < max_rows; ++i) {
        size_t current_cols = 0;
        if (i < n1) current_cols += m1;
        if (i < n2) current_cols += m2;

        for (size_t j = 0; j < current_cols; ++j) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    free_matrix(result, max_rows);
    free_matrix(lhs, n1);
    free_matrix(rhs, n2);

    return 0;
}
