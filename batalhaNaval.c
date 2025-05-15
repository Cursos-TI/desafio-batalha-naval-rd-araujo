#include <stdio.h>
#include <stdlib.h>

#define TAM 10         // Tamanho do tabuleiro
#define HAB 5          // Tamanho da matriz de habilidade (5x5)
#define CENTRO 2       // Centro da matriz de habilidade (posição [2][2])

// Exibe o tabuleiro no terminal
void mostrarTabuleiro(int mapa[TAM][TAM]) {
    for (int linha = 0; linha < TAM; linha++) {
        for (int coluna = 0; coluna < TAM; coluna++) {
            if (mapa[linha][coluna] == 0) printf("~ ");      // água
            else if (mapa[linha][coluna] == 3) printf("N ");  // navio
            else if (mapa[linha][coluna] == 5) printf("* ");  // atingido
        }
        printf("\n");
    }
}

// Aplica uma matriz de habilidade sobre o tabuleiro
void aplicarEfeito(int mapa[TAM][TAM], int area[HAB][HAB], int alvoX, int alvoY) {
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            int linhaTab = alvoX + (i - CENTRO);
            int colTab   = alvoY + (j - CENTRO);

            if (linhaTab >= 0 && linhaTab < TAM && colTab >= 0 && colTab < TAM) {
                if (area[i][j] == 1) {
                    mapa[linhaTab][colTab] = 5; // marca como atingido
                }
            }
        }
    }
}

// Cria forma de cone voltado para baixo
void criarCone(int cone[HAB][HAB]) {
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (i >= j - CENTRO && i >= CENTRO - j) cone[i][j] = 1;
            else cone[i][j] = 0;
        }
    }
}

// Cria forma de cruz (linha + coluna centrais)
void criarCruz(int cruz[HAB][HAB]) {
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (i == CENTRO || j == CENTRO) cruz[i][j] = 1;
            else cruz[i][j] = 0;
        }
    }
}

// Cria forma de octaedro 
void criarOctaedro(int losango[HAB][HAB]) {
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (abs(i - CENTRO) + abs(j - CENTRO) <= CENTRO) losango[i][j] = 1;
            else losango[i][j] = 0;
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0}; // tudo água

    // Insere navios no tabuleiro
    tabuleiro[2][2] = 3;
    tabuleiro[2][3] = 3;
    tabuleiro[3][2] = 3;

    // Matrizes de habilidades
    int matrizCone[HAB][HAB];
    int matrizCruz[HAB][HAB];
    int matrizOctaedro[HAB][HAB];

    // Geração das formas
    criarCone(matrizCone);
    criarCruz(matrizCruz);
    criarOctaedro(matrizOctaedro);

    // Coordenadas da origem da habilidade
    int origemX = 3, origemY = 3;

    aplicarEfeito(tabuleiro, matrizCone, origemX, origemY);
    // aplicarEfeito(tabuleiro, matrizCruz, origemX, origemY);
    // aplicarEfeito(tabuleiro, matrizOctaedro, origemX, origemY);

    mostrarTabuleiro(tabuleiro);

    return 0;
}










