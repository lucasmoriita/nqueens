#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define OCCUPIED 0
#define FREE -1


typedef struct ChessTable {
    int dimension;
    int **table;
    int *occupied;
} ChessTable;

int hasConflict(ChessTable *chessTable, int row, int column) {

    /*
     * checa todas as linhas anteriores com mesma coluna
     */
    printf("\n\nlinha: [%d] coluna: [%d] -> %d\n", row, column, chessTable->table[row][column]);
    printf("verificando coluna... \t");
    for (int c = column, r = row; r > 0; --r) {
        if (chessTable->table[r - 1][c] != FREE) {
            printf("conflito com rainha [%d][%d]\n", r - 1, c);
            return true;
        }
    }
    printf("sem conflito\n");
    printf("----------------------------------------------------\n");

    /*
     * diagonal superior esquerda
     */
    printf("verificando diagonal superior esquerda...\t");
    for (int c = column, r = row; c < chessTable->dimension && r > 0; ++c, --r) {
        if (chessTable->table[r - 1][c + 1] != FREE) {
            printf("conflito com rainha [%d][%d]\n", r - 1, c + 1);
            return true;
        }
    }
    printf("sem conflito\n");
    printf("-----------------------------------------------------\n");

    /*
     * verify left diagonal
     */
    printf("verificando diagonal superior direita...\t");
    for (int c = column, r = row; c > 0 && r > 0; --c, --r) {
        if (chessTable->table[r - 1][c - 1] != FREE) {
            printf("em conflito com rainha [%d][%d]\n", r - 1, c - 1);
            return true;
        }
    }
    printf("sem conflito\n");
    printf("-----------------------------------------------------\n");

    return false;

}

void printTable(ChessTable *chessTable) {
    for (int i = 0; i < chessTable->dimension; ++i) {
        for (int j = 0; j < chessTable->dimension; ++j) {
            printf(" [%d] ", chessTable->table[i][j]);
        }
        printf("\n");
    }
}

void printOccupied(ChessTable *chessTable) {
    printf("\nColunas ocupadas -> ");
    for (int i = 0; i < chessTable->dimension; ++i) {
        printf("[%d]", chessTable->occupied[i]);
    }
    printf("\n");
}

void nqueens(ChessTable *chessTable) {

    int row = 0;
    while (row < chessTable->dimension) {
        int column = 0;
        // para o backtracking
        if (chessTable->occupied[row] != FREE) {
            column = ++chessTable->occupied[row];
            chessTable->table[row][column - 1] = FREE;
            chessTable->occupied[row] = FREE;
            while (column < chessTable->dimension) {
                if (!hasConflict(chessTable, row, column)) {
                    chessTable->table[row][column] = OCCUPIED;
                    printf("\n\nmarcando [%d][%d] casa como ocupada\n\n", row, column);
                    chessTable->occupied[row] = column;
                    printTable(chessTable);
                    break;
                }
                column++;
            }
        } else {
            while (column < chessTable->dimension) {
                if (!hasConflict(chessTable, row, column)) {
                    chessTable->table[row][column] = OCCUPIED;
                    printf("\n\nmarcando casa [%d][%d] como ocupada\n\n", row, column);
                    chessTable->occupied[row] = column;
                    printTable(chessTable);
                    break;
                }
                column++;
            }
        }
        if (column == chessTable->dimension) {
            chessTable->occupied[row] = FREE;
            row--;
            printf("\n\nvoltando pra linha [%d]\n\n", row);
        }
        else {
            row++;
        }

    }
}



/*
 * chessTable->table contém um array com n index, todos inicializados com -1
 */
ChessTable* createTableGivenN(int n) {
    ChessTable *chessTable = malloc(sizeof(ChessTable));
    chessTable->table = malloc(n * sizeof(int*));
    chessTable->dimension = n;
    chessTable->occupied = malloc(n * sizeof(int));

    for (int k = 0; k < n; ++k) {
        chessTable->table[k] = malloc(n * sizeof(int));
    }

    for (int i = 0; i <= n - 1; ++i) {
        for (int j = 0; j <= chessTable->dimension; ++j) {
            chessTable->table[i][j] = FREE;
        }
        chessTable->occupied[i] = FREE;
    }
    return chessTable;
}

void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int n = 8;
    ChessTable *chessTable = createTableGivenN(n);
    nqueens(chessTable);
    printf("\n\n\n\n\n RESULTADO \n\n\n\n\n");
    printTable(chessTable);
    printOccupied(chessTable);
    freeMatrix(chessTable->table, n);
    return 0;
}
