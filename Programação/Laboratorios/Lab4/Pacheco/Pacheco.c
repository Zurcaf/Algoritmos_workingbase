#include <stdio.h>
#include <stdlib.h>

void printtab(int i, char tab[15][15], char numeros[15], char letras[15]);
void inittab(int i, int max, char tab[15][15]);
void initjogada(int i, char tab[15][15], char jogada[15][15]);
void fazerjogada(int i, char tab[15][15], char jogada[15][15], int n);
void initpontos(int i, char tab[15][15], int pontostab[15][15]);
void pontuacao(int i, char tab[15][15], char jogada[15][15], int pontostab[15][15]);

int main()
{
    int i = 0, max = 0, fim = 0, n = 1, pontostab[15][15], pontos[1];
    char tab[15][15], jogada[15][15], numeros[15], letras[15];

    do
    {
        printf("Insira as dimensões do tabuleiro: ");
        if (scanf("%d", &i) != 1)
        {
            printf("Erro, tente novamente. \n");
            scanf("%*s");
        }
    } while (i < 7 || i > 15 || i % 2 == 0);

    max = i - 1;
    inittab(i, max, tab);
    initjogada(i, tab, jogada);
    initpontos(i, tab, pontostab);
    printtab(i, jogada, numeros, letras);

    do
    {
        fazerjogada(i, tab, jogada, n);
        pontuacao(i, tab, jogada, pontostab);
        n++;
    } while (fim == 0);

    return 0;
}

void printtab(int i, char tab[15][15], char numeros[15], char letras[15])
{
    int r = 0, r2 = 0, l = 0;

    for (r = 0; r < i; r++)
    {
        numeros[r] = r + 1;
        if (r < 9)
        {
            printf(" %d", numeros[r]);
        }
        else
        {
            printf("%d", numeros[r]);
        }
        for (r2 = 0; r2 < i; r2++)
        {
            printf(" %c", tab[r][r2]);
        }

        printf("\n");
    }
    printf("  ");
    for (l = 0; l < i; l++)
    {
        letras[l] = 'A' + l;
        printf(" %c", letras[l]);
    }
    return;
}
void inittab(int i, int max, char tab[15][15])
{
    int r = 0, r2 = 0;

    for (r = 0; r < i; r++)
    {
        for (r2 = 0; r2 < i; r2++)
        {

            if ((r2 == r || r2 == max - r) && r2 != max && r2 != 0)
            {
                tab[r][r2] = '2';
            }
            else if ((r2 == 0 && r == 0) || (r == 0 && r2 == max) || (r == max && r2 == 0) || (r2 == max && r == max))
            {
                tab[r][r2] = '$';
            }
            else if (((r == 0 || r == max) && r2 == max / 2) || ((r2 == 0 || r2 == max) && r == max / 2))
            {
                tab[r][r2] = '3';
            }
            else if (((r == 1 || r == max - 1) && (r2 == max / 2 - 1 || r2 == max / 2 + 1)) || ((r2 == 1 || r2 == max - 1) && (r == max / 2 - 1 || r == max / 2 + 1)))
            {
                tab[r][r2] = '#';
            }
            else
            {
                tab[r][r2] = '.';
            }
        }
    }

    return;
}
void initjogada(int i, char tab[15][15], char jogada[15][15])
{
    int r = 0, r2 = 0;

    for (r = 0; r < i; r++)
    {
        for (r2 = 0; r2 < i; r2++)
        {
            jogada[r][r2] = tab[r][r2];
        }
    }
}
void fazerjogada(int i, char tab[15][15], char jogada[15][15], int n)
{
    char palavra[19] = {}, indicadorc, indicadord, letras[15] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'};
    int numeros[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int r = 0, erron = 0, errol = 0, indcoluna = 30, indlinha = 30, comp = 0, indicadorn, repeticao = 0, ovr = 0;
    char temp;

    printf("\nEscreva a sua jogada : ");
    scanf("%c", &temp);
    scanf("%c%d%c %s", &indicadorc, &indicadorn, &indicadord, palavra);
    if (indicadorc == 'F' && indicadord == 'I' && palavra[0] == 'M')
    {
        printf("Fim do jogo.");
        return EXIT_FAILURE;
    }

    for (r = 0; r < i; r++)
    {
        if (indicadorc == letras[r])
        {
            errol = 1;
            indcoluna = r;
        }
        if (indicadorn == numeros[r])
        {
            erron = 1;
            indlinha = r;
        }
    }
    if (errol != 1 || erron != 1)
    {
        printf("Esses indicadores não são válidos.");
        erron = 0;
        errol = 0;
        return;
    }

    comp = strlen(palavra);
    int r2 = 0, r3, r4 = 0;

    switch (indicadord)
    {
    case 'H':
        for (r3 = indcoluna; r3 < (indcoluna + comp); r3++)
        {
            if (tab[indlinha][r3] == '#')
            {
                printf("A palavra não pode ocupar um espaço com o caracter #.");
                return;
            }
            if (jogada[indlinha][r3] == palavra[r4])
            {
                repeticao++;
            }
            else if ((jogada[indlinha][r3] != tab[indlinha][r3]) && (jogada[indlinha][r3] != palavra[r4]))
            {
                ovr++;
            }
            r4++;
        }
        if ((indcoluna + comp - 1) > (i - 1))
        {
            printf("A Palavra não cabe no tabuleiro.");
            return;
        }
        if (repeticao > 1 || ovr >= 1)
        {
            printf("Jogada inválida: mais do que uma letra repetida ou escreveu por cima de outra palavra. ");
            return;
        }
        for (r3 = indcoluna; r3 < (indcoluna + comp); r3++)
        {
            jogada[indlinha][r3] = palavra[r2];
            r2++;
        }
        break;
    case 'V':
        for (r3 = indlinha; r3 < (indlinha + comp); r3++)
        {
            if (tab[r3][indcoluna] == '#')
            {
                printf("A palavra não pode ocupar um espaço com o caracter #.");
                return;
            }
            if (jogada[r3][indcoluna] == palavra[r4])
            {
                repeticao++;
            }
            else if ((jogada[r3][indcoluna] != tab[r3][indcoluna]) && (jogada[r3][indcoluna] != palavra[r4]))
            {
                ovr++;
            }
            r4++;
        }
        if ((indlinha + comp - 1) > (i - 1))
        {
            printf("A Palavra não cabe no tabuleiro.");
            return;
        }
        if (repeticao > 1 || ovr >= 1)
        {
            printf("Jogada inválida: mais do que uma letra repetida ou escreveu por cima de outra palavra. ");
            return;
        }
        for (r3 = indlinha; r3 < (indlinha + comp); r3++)
        {

            jogada[r3][indcoluna] = palavra[r2];
            r2++;
        }
        break;
    default:
        printf("Tem que escolher no 3o caracter se quer escrever a palavra na vertical (V) ou horizontal(H)");
        return;
        break;
    }

    printf("\n");
    printtab(i, jogada, numeros, letras);
    printf("\n");

    return;
}
void initpontos(int i, char tab[15][15], int pontostab[15][15])
{
    int r = 0, r2 = 0;

    for (r = 0; r < i; r++)
    {
        for (r2 = 0; r2 < i; r2++)
        {
            switch (tab[r][r2])
            {
            case '.':
                pontostab[r][r2] = 1;
                break;
            case '2':
            case '$':
                pontostab[r][r2] = 2;
                break;
            case '3':
                pontostab[r][r2] = 3;
                break;
            default:
                pontostab[r][r2] = 0;
                break;
            }
        }
    }
    return;
}
void pontuacao(int i, char tab[15][15], char jogada[15][15], int pontostab[15][15])
{
    int pontos = 0, r = 0, r2 = 0;

    for (r = 0; r < i; r++)
    {
        for (r2 = 0; r2 < i; r2++)
        {
            switch (jogada[r][r2])
            {
            case 'a':
            case 'A':
            case 'e':
            case 'E':
            case 'i':
            case 'I':
            case 'l':
            case 'L':
            case 'n':
            case 'N':
            case 'o':
            case 'O':
            case 'r':
            case 'R':
            case 's':
            case 'S':
            case 't':
            case 'T':
            case 'u':
            case 'U':
                pontos = pontos + (pontostab[r][r2] * 1);
                break;
            case 'd':
            case 'D':
            case 'g':
            case 'G':
                pontos = pontos + (pontostab[r][r2] * 2);
                break;
            case 'b':
            case 'B':
            case 'c':
            case 'C':
            case 'm':
            case 'M':
            case 'p':
            case 'P':
                pontos = pontos + (pontostab[r][r2] * 3);
                break;
            case 'f':
            case 'F':
            case 'h':
            case 'H':
            case 'v':
            case 'V':
            case 'w':
            case 'W':
            case 'y':
            case 'Y':
                pontos = pontos + (pontostab[r][r2] * 4);
                break;
            case 'k':
            case 'K':
                pontos = pontos + (pontostab[r][r2] * 5);
                break;
            case 'j':
            case 'J':
            case 'x':
            case 'X':
                pontos = pontos + (pontostab[r][r2] * 8);
                break;
            case 'q':
            case 'Q':
            case 'z':
            case 'Z':
                pontos = pontos + (pontostab[r][r2] * 10);
                break;
            }
        }
    }
    printf("\n Os seus pontos: %d \n", pontos);
    return;
}