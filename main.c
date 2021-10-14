//Arthur Sauer e Luísa Castro
//Algoritmos e Programação - INF01202 Turma A/B
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <conio2.h>

//prototipos das funcoes utilizadas
void desenha_mapa(char mapa[]);


int main(void)
{
    //chama a funcao desenha_mapa com o mapa que vai ser utilizado.
    //mapa é uma string que identifica o nome do arquivo txt.
    char mapa[] = "mapa1.txt";
    desenha_mapa(mapa);

    getch();
    return(0);
}


//funcao desenha_mapa
//dada uma string mapa com o nome do arquivo txt
// desenha o mapa na tela, de acordo com cada caractere (e sua respectiva cor)
//Luísa
void desenha_mapa(char mapa[]){
    FILE *pont_arq;
    char texto_str[3600];
    char c;

    //abrindo o arquivo_frase em modo "somente leitura"
    pont_arq = fopen(mapa, "r");

    do{

        //faz a leitura do caracter no arquivo apontado por pont_arq
        c = fgetc(pont_arq);

        //verifica qual tipo de caractere é, para mudar a cor do fundo naquele caractere.
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
        //exibe o caracter lido na tela
        printf("%c" , c);

    //faz isso até o final do arquivo
    }while (c != EOF);


  //fechando o arquivo
  fclose(pont_arq);
}


