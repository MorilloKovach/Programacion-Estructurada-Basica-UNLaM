#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *LeerTexto();
int Buscar(char *, char *);

int main()
{
    char *texto, *palabras;
    printf("\nIngrese el texto a usar: ");
    texto = LeerTexto();
    palabras = calloc(200, sizeof(char));
    printf("\nEscriba la palabra a buscar: ");
    scanf("%s", palabras);
    while (strcmp(palabras, "FINBUSCAR") != 0)
    {
        printf("%d\n", Buscar(texto, palabras));
        printf("\nEscriba la palabra a buscar: ");
        scanf("%s", palabras);
    }
    free(texto);
    free(palabras);
    return 0;
}

char *LeerTexto()
{
    char *texto;
    int i = 0, flag = 0;
    texto = calloc(200, sizeof(char));
    fgets(texto, 200, stdin);
    while (i < strlen(texto) && flag == 0)
    {
        if (*(texto + i) == '\n')
        {
            *(texto + i) = '\0';
            flag = 1;
        }
        else
            i++;
    }
    return texto;
}

int Buscar(char *texto, char *palabra)
{
    int i = 0, flag = 0, j = 0;
    char *aux;
    aux = calloc(200, sizeof(char));
    while (i < strlen(texto) && flag == 0)
    {
        if (*(texto + i) != ' ')
        {
            *(aux + j) = *(texto + i);
            j++;
        }
        else
        {
            if (strcmp(aux, palabra) == 0)
            {
                flag = 1;
            }
            for(;j>0;j--)
            {
                *(aux+j-1) = 0;
            }
            j = 0;

        }
        i++;
    }
    if (strcmp(aux, palabra) == 0)
    {
        flag = 1;
        printf("%s %s\n", aux, palabra);
    }
    free(aux);
    return flag;
}