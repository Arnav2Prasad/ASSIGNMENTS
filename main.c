#include<stdio.h>
#include <stdlib.h>
#include "List.c"

int main() {
    int row = 0;
    int col = 0;
    int** matrix1 = read_file("Matrix1.txt", &row, &col);
    int** matrix2 = read_file("Matrix2.txt", &row, &col);

    struct node* head1;
    init(&head1);
    struct node* head2;
    init(&head2);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix1[i][j] != 0) {
                append(&head1, i, j, matrix1[i][j]);
            }
            if (matrix2[i][j] != 0) {
                append(&head2, i, j, matrix2[i][j]);
            }
        }
    }

    printf("Matrix 1:\n");
    display(head1);
    printf("Matrix 2:\n");
    display(head2);

    struct node* add = addsparsematrix(head1, head2);
    printf("Addition Result:\n");
    display(add);
    to_file(add, "MatrixSum.txt", row, col);

    struct node* sub = subtractsparsematrix(head1, head2);
    printf("Subtraction Result:\n");
    display(sub);
    to_file(sub, "MatrixDiff.txt", row, col);

    // Free allocated memory
    for (int i = 0; i < row; i++) {
        free(matrix1[i]);
        free(matrix2[i]);
    }
    free(matrix1);
    free(matrix2);

    free_list(head1);
    free_list(head2);
    free_list(add);
    free_list(sub);

    return 0;
}


