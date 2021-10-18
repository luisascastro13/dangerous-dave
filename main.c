/*
    UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL
    INF01202 - ALGORITMOS E PROGRAMA��O

    TRABALHO FINAL

    ALUNOS: ARTHUR LOPES SAUER E LU�SA SCHMITZ DE CASTRO
    MATR�CULAS: XXX E 333766

    jogo de plataforma inspirado no cl�ssico Dangerous Dave.
    O objetivo do jogo � mover-se atrav�s de plataformas dispostas pelo mundo,
    coletando bens e um trof�u. Ap�s coletar o trof�u, o jogador poder� mover-se at� a porta,
    que o levar� para a pr�xima fase do jogo.
*/

#include <stdio.h>
#include <conio.h>
#include <conio2.h>

//definicao de constantes
//tamanho m�ximo da matriz que vai guardar o mapa
#define LINHAS 17
#define COLUNAS 100

//prototipos das funcoes utilizadas
void desenha_mapa(char mapa[]);
void movimenta();

//definir prototipo da funcao exibe_menu();

int main(void)
{
    //matriz do mapa
    int M[LINHAS][COLUNAS];
    //contadores uteis para percorrer a matriz do mapa
    int i,j,n;
    //texto que contem o arquivo que vai ser guardado na matriz
    char arq[] = "mapa1.txt";

    //PRIMEIRA COISA QUE ACONTECE NO PROGRAMA � EXIBIR O MENU
    //exibe_menu();

    //printf("Lendo o arquivo...\n");
    le (M, arq);
    printf("\n\nAqui esta o seu arquivo: \n");
    imprime (M);

    movimenta();


    getch();
    return(0);
}

//funcao le
//dada uma matriz de ponteiros e
//dada uma string com o nome do arquivo txt
//salva o arquivo na matriz
//Lu�sa
void le (int mat[][COLUNAS], char arq[]) {
    FILE *fp;
    int i, j, n=0;
    char c;

    //abre o arquivo
    fp = fopen(arq,"r");

    //se arquivo estiver vazio, deu erro, finaliza execu��o
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

//funcao imprime()
//recebe como parametro a matriz
//imprime na tela a matriz que contem o conteudo do arquivo txt
//Lu�sa
void imprime (int mat[][COLUNAS]) {
    int i, j;
    for (i = 0; i < LINHAS; i++){
        for (j = 0; j < COLUNAS; j++) {
            define_cores(mat[i][j]);
            printf("%c", mat[i][j]);
        }
    }
}

//funcao define_cores(char caractere);
//dado um caractere, pinta o fundo da tela de acordo com o mesmo
//Lu�sa
void define_cores(char c){
//verifica qual tipo de caractere �, para mudar a cor do fundo naquele caractere.
        switch(c){
            //parede
            case 'x':
                textbackground(RED);
                c = '_';
                break;
            //agua
            case 'A':
                textbackground(BLUE);
                c = ' ';
                break;
            //fogo
            case 'F':
            case 'f':
                textbackground(LIGHTRED);
                break;
            //dave
            case 'D':
                textbackground(WHITE);
                break;
            //trofeu
            case 'T':
                textbackground(YELLOW);
                break;
            //entrada
            case 'O':
                textbackground(DARKGRAY);
                break;
            //porta
            case 'P':
                textbackground(BROWN);
                break;
            //jetpack
            case 'J':
            case 'j':
                textbackground(GREEN);
                break;
            //bens
            case '!':
            case '@':
            case '#':
            case '$':
            case '%':
                //chamar funcao desenha bens!!!!
                textbackground(LIGHTCYAN);
                textcolor(BLACK);
                break;
            //senao, fundo preto
            default:
                textbackground(BLACK);
                textcolor(WHITE);
                break;
        }
}


//funcao movimenta
//verifica quais teclas estao sendo pressionadas.
//para a execu�ao do while quando for apertado o ESC
//Lu�sa
void movimenta(){
    int ch;
    while ((ch = _getch()) != 27)
    {
        if (ch == 0 || ch == 224){
            switch(_getch ())
            {
                case 75:
                    printf("\nEsquerda");
                    break;
                case 77:
                    printf("\nDireita");
                    break;
                case 72:
                    printf("\nCima");
                    break;
            }
        }
        else if(ch == 32){
                printf("\nBarraEspaco");
            }
        printf("%d\n", ch );
    }
    printf("ESC %d\n", ch);
}

//funcao exibe_menu();
//Arthur
