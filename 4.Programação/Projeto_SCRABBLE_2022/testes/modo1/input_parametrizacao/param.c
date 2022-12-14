#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define COMP_MENSAG 100

bool verif_comand(char[], char );
bool verif_dimensoes(char []);
int get_board_side (char []);

int main(int argc, char *argv[])
{
char dimensoes[5];

    if (argc == 1)
    {
        printf("Não inseriu nenhum parametro\n");
        return EXIT_FAILURE;
    }
    if (argc == 2)
    {
        if (verif_comand(argv[1], 'h'))
        {
        //abertura e apresentação da pagina de ajuda 
        FILE *help;
        char linha1[100];
        char *result;
        
        help = fopen("pagina_h.txt", "r");
    if (help == NULL)
    {
        printf("Problemas na abertura do arquivo (pagina_h.txt)\n");
        return EXIT_FAILURE;
    }
    while (!feof(help))
    {
        result = fgets(linha1, 100, help); 
        if (result)                     
            printf("%s", linha1);
    }
    fclose(help);
        }
        else
        {
            printf("Parametro INVALIDO para ver parametros VALIDOS inserir -h para ajuda\n");
            return EXIT_FAILURE;
        }
    }
    if (argc > 2)
    {
        // da a cada parametro o seu respetivo siginificado e aceita os ou rejeita se dorem validos ou não
        for (int i = 1; i < argc; i += 2)
        {
            if (verif_comand(argv[i], 'h'))
                printf("Para abrir a pagina de ajuda apenas coloque -h sem outros comandos\n");
            else if (verif_comand(argv[i], 't'))
            {
                if (argv[i + 1] == NULL)
                {
                    printf("Dimensões do tabuleiro não foram inseridas!\n");
                    return EXIT_FAILURE;
                }

                if (verif_dimensoes(argv[i + 1]))
                {
                    printf("Dimensões do tabuleiro: %s\n", argv[i + 1]);
                    int board_side;
                    board_side= get_board_side(argv[i+1]);
                    printf("%d", board_side);
                }
                else
                {
                    printf("Por favor insira dimensoes validas formato: (lxc), l=c, l>=7, l<=15 e l tem de ser impar\n");
                }
            }
            else if (verif_comand(argv[i], 'd'))
            {
                
                
                printf("nome do ficheiro de dicionário a utilizar (filename)\n");

            }

            else if (verif_comand(argv[i], 'l'))
                printf("nome do ficheiro com letras a usar nas jogadas (filename)\n");
            else if (verif_comand(argv[i], 'm'))
                printf("número de letras que um jogador pode ter na sua mão para jogar (5-20)\n");
            else if (verif_comand(argv[i], 'n'))
                printf("número de jogadas máximo a realizar (nn)\n");
            else if (verif_comand(argv[i], 'i'))
                printf("define ficheiro com o tabuleiro a usar em alternativa a jogar num tabuleiro vazio (filename)\n");
            else if (verif_comand(argv[i], 'j'))
                printf("modo de jogo (1-4)\n");
            else if (verif_comand(argv[i], 'o'))
                printf("define ficheiro onde escrever o tabuleiro final. (filename)\n");
            else if (verif_comand(argv[i], 'r'))
                printf("define ficheiro para registo de todas as jogadas possíveis. (filename)\n");
            else
            {
                printf("O comando %s não existe\nPara ajuda insira -h\n", argv[i]);
                return EXIT_FAILURE;
            }
        }
    }
    return 0;
}

bool verif_comand(char argumento[], char caract)
{
    bool retval = true;

    if (argumento[0] != '-')
        retval = false;
    if (argumento[1] != caract)
        retval = false;

    return retval;
}
bool verif_dimensoes(char arg_dimensoes[])
{
    bool retval = true;

    if (arg_dimensoes[0] != '1')
    {
        if (arg_dimensoes[1] != 'x')
            retval = false;
        if (arg_dimensoes[0] != arg_dimensoes[2])
            retval = false;
        if ((arg_dimensoes[0] != '7') && (arg_dimensoes[0] != '9'))
            retval = false;
    }
    else
    {
        if (arg_dimensoes[2] != 'x')
            retval = false;
        if (arg_dimensoes[0] != arg_dimensoes[3])
            retval = false;
        if (arg_dimensoes[1] != arg_dimensoes[4])
           retval = false;
        if ((arg_dimensoes[4] != '1') && (arg_dimensoes[4] != '3') && (arg_dimensoes[4] != '5'))
            retval = false;
    }
        return retval;
}

int get_board_side (char arg_dimensoes[]){
    if (arg_dimensoes[0] != '1')
    {
    return arg_dimensoes[0];
    }
    else{
    return arg_dimensoes[0] & arg_dimensoes[1];
    }
}