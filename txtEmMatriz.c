#include<stdio.h>
#include <stdlib.h>

//fazer com alocação dinâmica depois;
#define LINHAS 17
#define COLUNAS 100

int main () {
    int M[LINHAS][COLUNAS];
    int i, j,n;
    char arq[] = "mapa1.txt";

    //printf("Lendo o arquivo...\n");
    le (M, arq);
    printf("\n\nAqui esta o seu arquivo: \n");
    imprime (M);
    return(0);
}

void le (int mat[][COLUNAS], char arq[]) {
    FILE *fp;
    int i, j, n=0;
    char c;

    //abre o arquivo
    fp = fopen(arq,"r");

    //se arquivo estiver vazio, deu erro, finaliza execução
    if(fp == NULL) {
        perror("Erro na leitura do arquivo.");
        return(-1);
    }

    //le o txt e salva em uma matriz de ponteiros
    for (i = 0; i < LINHAS; i++){
        for (j = 0; j < COLUNAS; j++) {
            c = fgetc(fp);
            *(mat[0] + i * COLUNAS + j) = c;
            //printf("%c", c);
        }
    }
    //fecha o arquivo.
    fclose(fp);
}


void imprime (int mat[][COLUNAS]) {
    int i, j;
    for (i = 0; i < LINHAS; i++){
        for (j = 0; j < COLUNAS; j++) {
            printf("%c", mat[i][j]);
        }
    }
}
