/*
    UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL
    INF01202 - ALGORITMOS E PROGRAMA��O

    TRABALHO FINAL

    ALUNOS: ARTHUR LOPES SAUER E LU�SA SCHMITZ DE CASTRO
    MATR�CULAS: XXX E 333766

    Jogo de plataforma inspirado no cl�ssico Dangerous Dave.
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
void verifica_tecla();
void le(int mat[][COLUNAS], char arq[]);
void imprime (int mat[][COLUNAS]);
void desenha_barrainfo(int mat[][COLUNAS]);
void define_cores(char c);
void verifica_tecla();

//definir prototipo da funcao exibe_menu();

int main(void)
{
    //matriz do mapa
    int M[LINHAS][COLUNAS];
    //matriz da barra de informa��es
    int B[2][100];

    //contadores uteis para percorrer as matrizes
    int i,j,n;

    //texto que contem o arquivo mapa txt que vai ser guardado na matriz
    char mapa[] = "mapa1.txt";
    char info[] = "info.txt";

    //PRIMEIRA COISA QUE ACONTECE NO PROGRAMA � EXIBIR O MENU
    //exibe_menu();
    //vai ser algo do tipo
    //faz um switch com as opcoes do menu
    //enquanto ele nao escrever nenhuma opcao valida, continua mostrando o menu...
    //1 - Novo Jogo
    //2 - Carregar um jogo salvo
    //3 - Ranking de Melhores Pontua��es
    //4 - Sair

    //printf("Lendo a barra de informa��es...\n");
    le (B, info);
    //printf("\n\nAqui esta a barra de informacoes: \n");
    //imprime (B);
    desenha_barrainfo(B);

    //printf("Lendo o mapa...\n");
    le (M, mapa);
    //printf("\n\nAqui esta o seu arquivo: \n");
    printf("\n");
    imprime (M);

    verifica_tecla();

    /*int ch;
    while ((ch = _getch()) != 27)
    {
        printf("%c\n", verifica_tecla(ch));
    }
    */

    getch();
    return(0);
}

//funcao le(matriz, arquivo)
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

//funcao imprime(matriz)
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

//funcao desenha_barrainfo(matriz)
//recebe a matriz que contem os dados da barra de informacoes
//imprime os dados com formatacao
//Lu�sa
void desenha_barrainfo(int mat[][COLUNAS]){
    int i,j;
    for (i = 0; i < 1; i++){
        for (j = 0; j < 100; j++) {
            //ao inves de quebrar a linha com \n, da um espa�amento entre as linhas de tamanho \t
            if(mat[i][j] == '\n'){
                printf("\t");
            }
            else{
                printf("%c", mat[i][j]);
            }
        }
    }
}

//funcao define_cores(caractere);
//dado um caractere, pinta o fundo da tela de acordo com o mesmo
//Lu�sa
void define_cores(char c){
//verifica qual tipo de caractere �, para mudar a cor do fundo naquele caractere.
        switch(c){
            //parede
            case 'x':
                textbackground(RED);
                textcolor(RED);
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
                textcolor(BLACK);
                break;
            //trofeu
            case 'T':
                textbackground(YELLOW);
                textcolor(BLACK);
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

//funcao verifica_tecla()
//verifica quais teclas estao sendo pressionadas e printa o nome da tecla clicada.
//para a execu�ao do while quando for apertado o ESC
//Lu�sa
void verifica_tecla(){
    int ch;
    //enquanto o usuario nao apertar ESC, continua...
    while ((ch = _getch()) != 27)
    {
        //se apertar as setas
        if (ch == 0 || ch == 224){
            //verifica qual seta �
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
        //verifica se � a barra de espa�o
        else if(ch == 32){
               printf("\nBarraEspaco");
            }
        //informa o n�mero da tecla clicada
        //printf("%d\n", ch );
    }
    //mostra que o usu�rio apertou o ESC
    printf("\nESC. Saindo... \n", ch);
}

//funcao exibe_menu();
//Arthur
