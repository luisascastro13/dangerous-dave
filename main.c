/*
    UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL
    INF01202 - ALGORITMOS E PROGRAMAÇÃO
    TRABALHO FINAL
    ALUNOS: ARTHUR LOPES SAUER E LUÍSA SCHMITZ DE CASTRO
    MATRÍCULAS: 00333033 E 333766
    Jogo de plataforma inspirado no clássico Dangerous Dave.
    O objetivo do jogo é mover-se através de plataformas dispostas pelo mundo,
    coletando bens e um troféu. Após coletar o troféu, o jogador poderá mover-se até a porta,
    que o levará para a próxima fase do jogo.
*/

#include <stdio.h>
#include <conio.h>
#include <conio2.h>


//definicao de constantes
//tamanho máximo da matriz que vai guardar o mapa
#define LINHAS 16
#define COLUNAS 97

#define MAPA1 "mapa1.txt"
#define MAPA2 "mapa2.txt"
#define MAPA3 "mapa3.txt"

typedef struct Estado_Atual
{
    char mapa[LINHAS][COLUNAS];      //matriz do mapa
    int pontuacao;                   //pontuacao do jogador
    char bens[20];                   //itens
    char nome[40];                   //nome do jogador
    int vidas;                       //quantida de vidas
    int nivel;                      //nivel que o jogador parou
} Estado_Atual;

//prototipos das funcoes utilizadas
void desenha_mapa(char mapa[]);

//void verifica_tecla();
void le(int mat[][COLUNAS], char arq[]);
void imprime (int mat[][COLUNAS], int *posX, int *posY);
void desenha_barrainfo(int mat[][COLUNAS]);
void define_cores(char c);
//void verifica_tecla();
void imprime_menu();
void imprime_ranking();
int novo_jogo(char mapa[], int m);

int main(void)
{
    imprime_menu();

    getch();
    return 0;
}

//funcao exibe_menu();
//Arthur
void imprime_menu() {
    int t, mapa;
    clrscr();
    do
    {
        printf("1.Novo Jogo\n2.Carregar Jogo Salvo\n3.Melhores pontuacoes\n4.Sair\n");
        printf("Escolha uma opcao:\n");
        scanf ("%d", &t);
        switch (t)
        {
            case 1://inicia um novo jogo
            //printf("Iniciando...\n");
            //se retornou algo diferente de 0, é porque acabou de uma forma diferente
                clrscr();
                mapa= novo_jogo(MAPA1, 1);
                if(mapa == 2){
                    novo_jogo(MAPA2, 2);
                }
                else if(mapa == 3){
                    novo_jogo (MAPA3, 3);
                }
                else if(mapa == -1){
                    clrscr();
                    printf("Você morreu.");
                }
            break;

            case 2://carrega um jogo salvo
            printf("Carregando...\n");
            break;

            case 3://mostra o ranking das melhores pontuacoes
            printf("Ranking...\n");
            imprime_ranking();
            break;

            case 4://encerra o jogo
            printf("Encerrando... Pressione ESC\n");
            break;

            default://opcao inválida
            printf("Opcao Invalida, digite novamente\n");
            break;

        }
    } while (t != 4);
}

//funcao le(matriz, arquivo)
//dada uma matriz de ponteiros e
//dada uma string com o nome do arquivo txt
//salva o arquivo na matriz
//Luísa
void le (int mat[][COLUNAS], char arq[]) {
    FILE *fp;
    int i, j, n=0;
    char c;

    //abre o arquivo
    fp = fopen(arq,"r");

    //se arquivo estiver vazio, deu erro, finaliza execução
    if(fp == NULL) {
        perror("Erro na leitura do arquivo.");
        return -1;
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
//altera a posicao (posx posy) do dave
//Luísa
void imprime (int mat[][COLUNAS], int *posX, int *posY) {
    int i, j;
    for (i = 0; i < LINHAS; i++){
        for (j = 0; j < COLUNAS; j++) {
            define_cores(mat[i][j]);
            printf("%c", mat[i][j]);
            if(mat[i][j] == 'D'){
                *posX = i;
                *posY = j;
            }
        }
    }
}

//funcao desenha_barrainfo(matriz)
//recebe a matriz que contem os dados da barra de informacoes
//imprime os dados com formatacao
//Luísa
void desenha_barrainfo(int mat[][COLUNAS]){
    int i,j;
    for (i = 0; i < 1; i++){
        for (j = 0; j < 100; j++) {
            //ao inves de quebrar a linha com \n, da um espaçamento entre as linhas de tamanho \t
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
//Luísa
void define_cores(char c){
//verifica qual tipo de caractere é, para mudar a cor do fundo naquele caractere.
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

//Luísa
//inspiracao para a criacao da funcao:
//stackoverflow.com/a/49408013
int retorna_tecla(void) {
    int key, movimento;
    if (kbhit()) {
        key=getch();
        if (key == 224) {
            do {
                key=getch();
            } while(key==224);

            switch (key) {
                case 72:
                    movimento = 2;
                    //printf("up");
                    break;
                case 75:
                    movimento = 1;
                    //printf("left");
                    break;
                case 77:
                    movimento = 3;
                    //printf("right");
                    break;
                case 80:
                    movimento = 4;
                    //printf("down");
                    break;
            }
        }
        //esc
        else if(key == 27){
            movimento = 27;
        }
        //n ou N
        else if(key == 78 || key == 110){
            movimento = 0;
        }
        //todos outros caracteres
        else{
            movimento = -1;
        }
        return movimento;
    }
}

//Luísa
//abre o jogo e movimenta o boneco no mapa.
int novo_jogo(char mapa[], int m){
    //texto que contem o arquivo mapa txt que vai ser guardado na matriz
    char info[] = "info.txt";
    int tecla;

    //matriz do mapa
    int M[LINHAS][COLUNAS];
    //matriz da barra de informações
    int B[2][100];
    int posX, posY;
    int *dx = &posX;
    int *dy = &posY;
    char proximo;
    int pontos=0;
    int vidas = 5;
    char bens;
    int mapinha = m;

    le (B, info);
    le (M, mapa);

    desenha_barrainfo(B);
    printf("\n");
    imprime(M, dx, dy);

    while (1) {
        if (kbhit()) {
            tecla = retorna_tecla();
            //printf("%d", tecla);
            clrscr();

            switch(tecla){
                //esc
                case 27:
                    return 0;
                    break;

                //esquerda
                case 1:
                    proximo = M[posX][posY - 1];
                    switch(proximo){
                        //casos em que morre;
                        case 'A':
                        case 'F':
                        case 'f':
                            if(vidas > 0){
                                vidas --;
                                pontos = 0;
                                le (M, mapinha);
                            }
                            else{
                                return -1;
                            }
                            //morre
                            break;

                        //parede
                        case 'x':
                        case 'o':
                            break;

                        //vazio
                        case ' ':
                        case 'J':
                        case 'T':
                            M[posX][posY] = ' ';
                            posY -= 1;
                            M[posX][posY] = 'D';
                            break;

                        case 'P':
                            if(m == 2){
                                return 3;
                            }
                            else{
                                return 2;
                            }
                           break;

                        //SOMA PONTOS E ANDA
                        //coroa
                        case '%':
                            pontos+=100;
                        //anel
                        case '$':
                            pontos+=50;
                        //rubi
                        case '#':
                            pontos+=50;
                        //safira
                        case '@':
                            pontos+=50;
                        //ametista
                        case '!':
                            pontos += 50;
                            M[posX][posY] = ' ';
                            posY -= 1;
                            M[posX][posY] = 'D';
                            break;
                    }
                    break;

                //cima
                case 2:
                    proximo = M[posX-1][posY];
                    switch(proximo){
                        //casos em que morre;
                        case 'A':
                        case 'F':
                        case 'f':
                            if(vidas > 0){
                                vidas --;
                                pontos = 0;
                                le (M, mapinha);
                            }
                            else{
                                return -1;
                            }
                            //morre
                            break;

                        //parede
                        case 'x':
                        case '_':
                        case 'o':
                            break;

                        //vazio
                        case ' ':
                        case 'J':
                        case 'T':
                            M[posX][posY] = ' ';
                            posX -= 1;
                            M[posX][posY] = 'D';
                            break;

                        case 'P':
                            if(m == 2){
                                return 3;
                            }
                            else{
                                return 2;
                            }
                           break;

                        //SOMA PONTOS E ANDA
                        //coroa
                        case '%':
                            pontos+=100;
                        //anel
                        case '$':
                            pontos+=50;
                        //rubi
                        case '#':
                            pontos+=50;
                        //safira
                        case '@':
                            pontos+=50;
                        //ametista
                        case '!':
                            pontos += 50;
                            M[posX][posY] = ' ';
                            posX -= 1;
                            M[posX][posY] = 'D';
                            break;
                    }
                    break;

                //direita
                case 3:
                    proximo = M[posX][posY + 1];
                    switch(proximo){
                        //casos em que morre;
                        case 'A':
                        case 'F':
                        case 'f':
                            if(vidas > 0){
                                vidas --;
                                pontos = 0;
                                le (M, mapinha);
                            }
                            else{
                                return -1;
                            }
                            //morre
                            break;

                        //parede
                        case 'x':
                        case 'o':
                            break;

                        //vazio
                        case ' ':
                        case 'J':
                        case 'T':
                            M[posX][posY] = ' ';
                            posY += 1;
                            M[posX][posY] = 'D';
                            break;

                       case 'P':
                            if(m == 2){
                                return 3;
                            }
                            else{
                                return 2;
                            }
                           break;

                        //SOMA PONTOS E ANDA
                        //coroa
                        case '%':
                            pontos+=100;
                        //anel
                        case '$':
                            pontos+=50;
                        //rubi
                        case '#':
                            pontos+=50;
                        //safira
                        case '@':
                            pontos+=50;
                        //ametista
                        case '!':
                            pontos += 50;
                            M[posX][posY] = ' ';
                            posY += 1;
                            M[posX][posY] = 'D';
                            break;
                    }
                    break;

                //baixo
                case 4:
                    proximo = M[posX+1][posY];
                    switch(proximo){
                        //casos em que morre;
                        case 'A':
                        case 'F':
                            if(vidas > 0){
                                vidas --;
                                pontos = 0;
                                le (M, mapinha);
                            }
                            else{
                                return -1;
                            }
                            //morre
                            break;

                        //parede
                        case 'x':
                        case '_':
                        case 'o':
                            break;

                        //vazio
                        case ' ':
                        case 'J':
                        case 'T':
                            M[posX][posY] = ' ';
                            posX += 1;
                            M[posX][posY] = 'D';
                            break;
                        case 'P':
                            if(m == 2){
                                return 3;
                            }
                            else{
                                return 2;
                            }
                           break;

                        //SOMA PONTOS E ANDA
                        //coroa
                        case '%':
                            pontos+=100;
                        //anel
                        case '$':
                            pontos+=50;
                        //rubi
                        case '#':
                            pontos+=50;
                        //safira
                        case '@':
                            pontos+=50;
                        //ametista
                        case '!':
                            pontos += 50;
                            M[posX][posY] = ' ';
                            posX += 1;
                            M[posX][posY] = 'D';
                            break;
                    }
                    break;

                case -1:

                    break;
            }
            //desenha_barrainfo(B);
            //printf("\n");

            printf("SCORE: %d", pontos);
            printf("\tVIDAS: %d", vidas);
            imprime(M, dx, dy);

        }
    }
   // printf("%d", pontos);
}

void imprime_ranking(){
//texto que contem o arquivo ranking txt que vai ser guardado na matriz
    char mapa[] = "ranking.txt";
    //matriz do ranking
    int M[LINHAS][COLUNAS];
    //matriz da barra de informações
    int B[2][100];
    clrscr();
    //printf("Lendo o mapa...\n");
    le (M, mapa);
    //printf("\n\nAqui esta o seu arquivo: \n");
    printf("\n");
    imprime (M, 0,0);
}
