#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "fila.h"
#include <time.h>
// #include <conio2.h>
#include <string.h>
#include <conio.h>

#define LINHAS 20
#define COLUNAS 40
#define ESPACOUP 8 //numero de linhas que vai ficar em branco antes do tabuleiro
#define ESPACOLF 4 //numero de colunas que vai ficar em braco na esquerda do tabuleiro

#define BLACK 0
#define RED 1
#define GREEN 2
#define BROWN 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define LIGHTGRAY 7
#define DARKGRAY 0
#define LIGHTRED 1
#define LIGHTGREEN 2
#define YELLOW 3
#define LIGHTBLUE 4
#define PINK 5
#define LIGHTCYAN 6
#define WHITE 7

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void iniciaTabuleiro(char matriz[LINHAS][COLUNAS], fila *cobra, fila *posix, fila *posiy, int vetaux[])
{
    int x, y;
    int i, j;

    system("cls");

    gotoxy(ESPACOLF + 3, 2);
    printf(" SSSSS  NN   N     A     K   K EEEE\n");
    gotoxy(ESPACOLF + 3, 3);
    printf("SS      N N  N    A A    K  K  E\n");
    gotoxy(ESPACOLF + 3, 4);
    printf(" SSS    N  N N   A   A   KKK   EE\n");
    gotoxy(ESPACOLF + 3, 5);
    printf("    SS  N   NN  AAAAAAA  K  K  E\n");
    gotoxy(ESPACOLF + 3, 6);
    printf("SSSS    N    N A       A K   K EEEE");

    gotoxy(ESPACOLF + 1, ESPACOUP - 1 + 1);
    printf("SCORE:                         ");
    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COLUNAS; j++)
        {
            matriz[i][j] = ' ';
        }
    }
    for (i = 0; i < LINHAS; i++)
    {
        matriz[i][0] = '|';
        matriz[i][COLUNAS - 1] = '|';
    }
    for (j = 0; j < COLUNAS; j++)
    {
        matriz[0][j] = '-';
        matriz[LINHAS - 1][j] = '-';
    }

    //linhas = y
    //colunas = x

    for (i = 0; i < LINHAS; i++)
    {
        gotoxy(0 + ESPACOLF + 1, i + ESPACOUP + 1);
        printf("%c", matriz[i][0]);

        gotoxy(COLUNAS - 1 + ESPACOLF + 1, i + ESPACOUP + 1);
        printf("%c", matriz[i][COLUNAS - 1]);
    }

    for (j = 0; j < COLUNAS; j++)
    {
        gotoxy(j + ESPACOLF + 1, ESPACOUP + 1);
        printf("%c", matriz[0][j]);

        gotoxy(j + ESPACOLF + 1, LINHAS - 1 + ESPACOUP + 1);
        printf("%c", matriz[LINHAS - 1][j]);
    }

    // textcolor(LIGHTGREEN);
    // textbackground(BLACK);
    i = 0;
    while (filaVazia(cobra) == 0)
    {
        char a;
        int x, y;
        pop(cobra, &vetaux[i]);
        a = vetaux[i];
        i++;
        pop(posix, &vetaux[i]);
        x = vetaux[i];
        i++;
        pop(posiy, &vetaux[i]);
        y = vetaux[i];
        i++;

        matriz[y][x] = a;
        gotoxy(x + ESPACOLF + 1, y + ESPACOUP + 1);
        printf("%c", a);
    }
    // textcolor(WHITE);
    // textbackground(BLACK);
    j = 0;
    while (j < i)
    {
        push(cobra, vetaux[j]);
        j++;
        push(posix, vetaux[j]);
        j++;
        push(posiy, vetaux[j]);
        j++;
    }
    gotoxy(0 + 1, LINHAS + ESPACOUP + 1 + 1);
}

void comida(char matriz[LINHAS][COLUNAS])
{
    srand(time(NULL));
    int a, x, y;
    a = rand() % 4;
    switch (a)
    {
    case 0:
        a = 43;
        break;
    case 1:
        a = 120;
        break;
    case 2:
        a = 111;
        break;
    case 3:
        a = 99;
        break;
    }

    do
    {
        x = rand() % COLUNAS;
        y = rand() % LINHAS;
    } while (matriz[y][x] != ' ');

    matriz[y][x] = a;
    gotoxy(x + ESPACOLF + 1, y + ESPACOUP + 1);
    printf("%c", a);
}

int move(int direcao, fila *cobra, fila *posix, fila *posiy, char matriz[LINHAS][COLUNAS], int vetAux[])
{
    int auxX, auxY, x, y, gameover = 0, i, j, comeu = 0, qualComida, lixo, cabeca;
    switch (direcao)
    {
    case 72: //seta p/ cima
        pop(posix, &x);
        pop(posiy, &y);
        auxX = x;
        auxY = y;
        y--;
        cabeca = 'A';

        break;
    case 77: //seta p/ direita
        pop(posix, &x);
        pop(posiy, &y);
        auxX = x;
        auxY = y;
        x++;
        cabeca = '>';
        break;
    case 80: //seta p/ baixo
        pop(posix, &x);
        pop(posiy, &y);
        auxX = x;
        auxY = y;
        y++;
        cabeca = 'V';
        break;
    case 75: //seta p/ esquerda
        pop(posix, &x);
        pop(posiy, &y);
        auxX = x;
        auxY = y;
        x--;
        cabeca = '<';
        break;
    }

    if (matriz[y][x] == 43 || matriz[y][x] == 120 || matriz[y][x] == 111 || matriz[y][x] == 99) //verifica se comeu a comidinha
    {
        //chamar função de sortear nova comida e colocar ela na fila da cobra
        qualComida = matriz[y][x];
        comida(matriz);
        comeu = 1;
    }
    else
    {
        if (matriz[y][x] != ' ') // verifica se bateu na parede ou no corpo
        {
            gameover = 1;
        }
    }

    // textcolor(LIGHTGREEN);
    // textbackground(BLACK);

    i = 0;
    if (gameover == 1)
    {
        // textcolor(RED);
        // textbackground(BLACK);
    }
    pop(cobra, &lixo);
    vetAux[i] = cabeca;
    gotoxy(x + ESPACOLF + 1, y + ESPACOUP + 1);
    printf("%c", vetAux[i]);
    matriz[y][x] = vetAux[i];
    i++;
    vetAux[i] = x;
    i++;
    vetAux[i] = y;
    i++;

    if (gameover == 1)
    {
        // textcolor(LIGHTGREEN);
        // textbackground(BLACK);
        Beep(250, 75);
    }

    pop(cobra, &vetAux[i]);
    i++;
    vetAux[i] = auxX;
    i++;
    vetAux[i] = auxY;
    i++;
    while (filaVazia(cobra) == 0)
    {
        pop(cobra, &vetAux[i]);
        i++;
        pop(posix, &vetAux[i]);
        i++;
        pop(posiy, &vetAux[i]);
        i++;
    }

    pop(posix, &x);
    pop(posiy, &y);
    gotoxy(x + ESPACOLF + 1, y + ESPACOUP + 1);
    printf(" ");
    matriz[y][x] = ' ';
    j = 0;
    while (j < i)
    {
        push(cobra, vetAux[j]);
        j++;
        push(posix, vetAux[j]);
        j++;
        push(posiy, vetAux[j]);

        if (j > 3)
        {
            gotoxy(vetAux[j - 1] + ESPACOLF + 1, vetAux[j] + ESPACOUP + 1);
            printf("%c", vetAux[j - 2]);
        }
        j++;
    }

    if (comeu == 1)
    {
        Beep(1800, 75);
        push(cobra, qualComida);
        i++;
        push(posix, x);
        i++;
        push(posiy, y);
        i++;
        gotoxy(x + ESPACOLF + 1, y + ESPACOUP + 1);
        printf("%c", qualComida);
        matriz[y][x] = qualComida;
        gameover = 2;
    }
    // textcolor(WHITE);
    // textbackground(BLACK);
    return gameover;
}
void criaArquivo(int pontos[6], char nomes[][15])
{
    char str[] = "AAAA.txt";
    FILE *arquivo = fopen(str, "w"); // cria o arquivo

    fputs("177960 Volmir\n", arquivo);
    fputs("108310 Moacir\n", arquivo);
    fputs("30000 jogador3\n", arquivo);
    fputs("20000 jogador4\n", arquivo);
    fputs("10000 jogador5\n", arquivo);

    pontos[0] = 177960;
    pontos[1] = 108310;
    pontos[2] = 30000;
    pontos[3] = 20000;
    pontos[4] = 10000;

    fclose(arquivo);
}

void valorRecordes(int pontos[6], char nomes[][15])
{
    char str[] = "AAAA.txt";
    FILE *arquivo = fopen(str, "r"); // somente abre o arquivo

    if (arquivo == NULL) // testa se o arquivo foi aberto com sucesso
    {
        //printf("\n\nImpossivel abrir o arquivo!\n\n");
        criaArquivo(pontos, nomes); //cria o arquivo que não existe com umas pontuações base
        arquivo = fopen(str, "r");
        if (arquivo == NULL)
        {
            //alguma coisa deu muito errado nessa brincadeira
        }
    }

    int i, j;
    for (i = 0; i < 5; i++)
    {
        fscanf(arquivo, "%d", &pontos[i]);
        fscanf(arquivo, "%s", &nomes[i]);
    }
    fclose(arquivo);
}

void recorde(int pontos[6], char nomes[][15])
{
    char str[] = "AAAA.txt";
    FILE *arquivo = fopen(str, "w");

    if (arquivo == NULL) // testa se o arquivo foi aberto com sucesso
    {
        printf("\nImpossivel salvar recorde!\n");
        return;
    }
    int i;
    char string[15];
    for (i = 0; i < 5; i++)
    {
        sprintf(string, "%d", pontos[i]);
        fputs(string, arquivo);
        fputs(" ", arquivo);
        fputs(nomes[i], arquivo);
        fputs("\n", arquivo);
    }

    //sprintf(strng, "%d",pop[0]->makespan);

    fclose(arquivo);
}

void mostraRecordes(int pontos[6], char nomes[][15])
{
    gotoxy(ESPACOLF + 1, ESPACOUP + LINHAS + 6);
    printf("          RECORDES\n");
    int i;
    for (i = 0; i < 5; i++)
    {
        printf("%d:  %d   ", i + 1, pontos[i]);
        puts(nomes[i]);
    }
}

int main()
{

    int i, j;
    int vetAux[MAX * 3];
    int pontomax;
    int pontos[6];
    char nomes[6][15];
    system("Title SNAKE");

    while (true)
    {
        system("MODE 50,42");
        int score = 0;
        char matriz[LINHAS][COLUNAS];
        valorRecordes(pontos, nomes);
        fila cobra;
        iniFila(&cobra);
        fila posix;
        iniFila(&posix);
        fila posiy;
        iniFila(&posiy);

        push(&cobra, 42);
        push(&cobra, 42);
        push(&cobra, 42);

        push(&posix, COLUNAS / 2);
        push(&posix, (COLUNAS / 2) - 1);
        push(&posix, (COLUNAS / 2) - 2);

        push(&posiy, (LINHAS / 2));
        push(&posiy, (LINHAS / 2));
        push(&posiy, (LINHAS / 2));
        iniciaTabuleiro(matriz, &cobra, &posix, &posiy, vetAux);

        hidecursor();

        char c;
        char caux = 77;

        int gameover = 0, comeu = 0;
        pontomax = 1000;

        comida(matriz);

        gotoxy(ESPACOLF + 1, ESPACOUP + LINHAS + 2);
        printf("Precione qualquer tecla pra comecar a jogar!");
        getch();
        gotoxy(ESPACOLF + 1, ESPACOUP + LINHAS + 2);
        printf("                                                     ");

        int sleep;
        sleep = 200;
        while (true)
        {
            if (caux == 77 || caux == 75)
            {
                if (sleep > 40 && comeu > 0)
                {
                    Sleep(sleep);
                }
                else
                {
                    Sleep(sleep);
                }
            }
            else
            {
                if (sleep > 80 && comeu > 0)
                {
                    Sleep(sleep * 2);
                }
                else
                {
                    Sleep(sleep * 2);
                }
            }

            /*
            gotoxy(ESPACOLF,ESPACOUP-1);
            printf("                ");
            gotoxy(ESPACOLF,ESPACOUP-1);
            printf("sleep = %d",sleep);
            */

            if (kbhit())
            {
                c = getch();
                if (c == -32)
                {
                    c = getch();
                    switch (c)
                    {
                    case 72:
                        //printf("tecla pra cima\n");
                        if (caux != 80)
                        {
                            gameover = move(c, &cobra, &posix, &posiy, matriz, vetAux);
                            caux = c;
                        }
                        else
                        {
                            gameover = move(caux, &cobra, &posix, &posiy, matriz, vetAux);
                        }
                        break;
                    case 77:
                        //printf("tecla pra direita\n");
                        if (caux != 75)
                        {
                            gameover = move(c, &cobra, &posix, &posiy, matriz, vetAux);
                            caux = c;
                        }
                        else
                        {
                            gameover = move(caux, &cobra, &posix, &posiy, matriz, vetAux);
                        }
                        break;
                    case 80:
                        //printf("tecla pra baixo\n");
                        if (caux != 72)
                        {
                            gameover = move(c, &cobra, &posix, &posiy, matriz, vetAux);
                            caux = c;
                        }
                        else
                        {
                            gameover = move(caux, &cobra, &posix, &posiy, matriz, vetAux);
                        }
                        break;
                    case 75:
                        //printf("tecla pra esquerda\n");
                        if (caux != 77)
                        {
                            gameover = move(c, &cobra, &posix, &posiy, matriz, vetAux);
                            caux = c;
                        }
                        else
                        {
                            gameover = move(caux, &cobra, &posix, &posiy, matriz, vetAux);
                        }
                        break;
                    }
                }
                else
                {
                    if (c == 80 || c == 112 || c == 'R' || c == 'r')
                    {
                        if (c == 'R' || c == 'r')
                        {
                            gotoxy(ESPACOLF + 1, ESPACOUP + LINHAS + 2);
                            printf("RESTART");
                            getch();
                            break;
                        }
                        gotoxy(ESPACOLF + 1, ESPACOUP + LINHAS + 2);
                        printf("PAUSE");
                        getch();
                        gotoxy(ESPACOLF + 1, ESPACOUP + LINHAS + 2);
                        printf("                 ");
                    }
                    else
                    {
                        gameover = move(caux, &cobra, &posix, &posiy, matriz, vetAux);
                    }
                }
            }
            else
            {
                gameover = move(caux, &cobra, &posix, &posiy, matriz, vetAux);
            }
            if (gameover == 1)
            {
                gotoxy(ESPACOLF + 1, ESPACOUP + LINHAS + 2);
                printf("         Voce perdeu!!!");
                getch();
                if (score > pontos[4])
                {
                    pontos[4] = score;
                    gotoxy(ESPACOLF + 1, ESPACOUP + LINHAS + 2);
                    printf("         RECORDE!!!              ");
                    getch();
                    gotoxy(ESPACOLF + 1, ESPACOUP + LINHAS + 3);
                    printf("Digite seu nome:        ");
                    scanf("%s", nomes[4]);
                    gotoxy(ESPACOLF + 1, ESPACOUP + LINHAS + 3);
                    printf("                                 ");
                    int m = 3;
                    while (m >= 0 && pontos[m + 1] > pontos[m])
                    {
                        pontos[5] = pontos[m];
                        pontos[m] = pontos[m + 1];
                        pontos[m + 1] = pontos[5];

                        strcpy(nomes[5], nomes[m]);
                        strcpy(nomes[m], nomes[m + 1]);
                        strcpy(nomes[m + 1], nomes[5]);
                        m--;
                    }
                    recorde(pontos, nomes);
                }

                gotoxy(ESPACOLF + 1, ESPACOUP + LINHAS + 2);
                printf("                                                     ");
                gotoxy(ESPACOLF + 1, ESPACOUP + LINHAS + 2);
                printf("Pressione:\n    ->Esc para sair do jogo \n    ->Enter para tentar outra vez\n");

                mostraRecordes(pontos, nomes);

                char a = 0;
                while (a != 27 && a != 13)
                {
                    a = getch();
                }
                if (a == 27)
                {
                    system("cls");
                    exit(0);
                }
                break;
            }
            if (gameover == 2)
            {
                comeu++;
                score = score + pontomax;
                if (sleep > 50)
                {
                    sleep = sleep - (40 / comeu);
                    pontomax = 1000 + 100 * comeu;
                }
                else
                {
                    pontomax = 1000 + 100 * 24;
                }
            }
            else
            {
                if (pontomax > 50)
                    pontomax = pontomax - 30;
            }
            gotoxy(ESPACOLF + 7 + 1, ESPACOUP - 1 + 1);
            printf("%d     EAT: %d", score, comeu);
            gotoxy(COLUNAS + ESPACOLF - 7 + 1, ESPACOUP - 1 + 1);
            printf("MAX: %d       ", pontomax);
            /*
            while(kbhit()) //loop pra tentar limpar buffer do teclado
            {
                c = getch();
            }
            */
        }
    }
    return 0;
}

// tentar deixar simetrico
// velocidade da vertical x horizontal
// função e tempo
