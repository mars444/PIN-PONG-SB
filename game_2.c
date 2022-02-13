#include <stdio.h>
#include <math.h>
#include <time.h>
#define space_x 25
#define space_y 80

const int a = space_x - 2;
const int b = space_y - 2;

int check(int i, int j);

void generate_matrix(int matrix [a][b]);
void print_matrix(int matrix[a][b]);
void write_null_matrix(int matrix[a][b]);

int main() {
    int space [a][b];

    write_null_matrix(space);
    print_matrix(space);
    generate_matrix(space);
    print_matrix(space);
            return 0;
}

void write_null_matrix(int matrix[a][b]) {
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            matrix[i][j] = 3;
        }

    }
}

void print_matrix(int matrix[a][b]) {
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            printf("%d  ", matrix[i][j]);
        }
        printf("\n");
    }
}

void generate_matrix(int matrix [a][b]) {
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            matrix[i][j] = 6;
        }
    }
}
