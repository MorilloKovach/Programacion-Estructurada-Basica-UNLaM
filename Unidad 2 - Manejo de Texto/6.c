/*
Realizar el juego del ahorcado. Primero se debe ingresar la palabra a adivinar de hasta 10 caracteres. Luego
se muestra por cada letra un guion bajo para que el jugador sepa la cantidad de letras a adivinar. Se irá
ingresando una a una las letras y si estas se encuentran en la palabra las deberá ir mostrando en el lugar
correspondiente. Por cada letra que no se encuentre en la palabra perderá una vida. El jugador dispondrá de
5 vidas para intentar ganar el juego.
Complemento:
• Ir completando el dibujo del muñeco del ahorcado cada vez que se comete un error.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void DibujarPersona(int);
char *OtorgarPalabra();
int main()
{
    char *palabra, *adivino, palabraAct;
    int i = 0, j, flag = 0, tam;
    palabra = OtorgarPalabra();
    tam = strlen(palabra);
    adivino = calloc(tam + 1, sizeof(char));
    for (j = 0; j < tam; j++)
    {
        adivino[j] = '_';
    }
    while (i < 5 && strcmp(palabra, adivino) != 0)
    {
        flag = 0;
        system("clear");
        if (i > 0)
        {
            DibujarPersona(i);
        }
        printf("\n%s\n", adivino);
        printf("\nIngrese la letra: ");
        scanf(" %c", &palabraAct);
        for (j = 0; j < tam; j++)
        {
            if (palabra[j] == palabraAct)
            {
                adivino[j] = palabra[j];
                flag = 1;
            }
        }
        if (!flag)
            i++;
    }
    if (i == 5)
    {
        DibujarPersona(i);
        printf("\nPerdiste!");
    }
    else
    {
        printf("Acertaste! La palabra era %s\n", adivino);
    }
    free(palabra);
    free(adivino);
    return 0;
}

char *OtorgarPalabra()
{
    char *pal;
    pal = calloc(11, sizeof(char));
    printf("\nEscriba la palabra de 10 caracteres: \n");
    scanf("%10s", pal);
    return pal;
}

void DibujarPersona(int error)
{
    printf("\n");
    switch (error)
    {
    case 1:
        printf(" | \n");
        printf(" O ");
        break;
    case 2:
        printf(" | \n");
        printf(" O \n");
        printf(" | ");
        break;
    case 3:
        printf(" | \n");
        printf(" O \n");
        printf(" | \n");
        printf(" | \n");
        break;
    case 4:
        printf(" | \n");
        printf(" O \n");
        printf("/|\\ \n");
        printf(" |\n");
        break;
    case 5:
        printf(" | \n");
        printf(" O \n");
        printf("/|\\ \n");
        printf(" | \n");
        printf("/ \\ \n");
        break;
    }
}