#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 50
#define V 20

void cargarDatos(char[][TAM], int);
char *LeerTexto();
int contarCantidad(char[][TAM], char[], int);
int main()
{
    char nombres[V][TAM], nombre[TAM], *aux;
    int tam = V;
    cargarDatos(nombres, tam);
    aux = calloc(TAM, sizeof(char));
    aux = LeerTexto();
    strcpy(nombre, aux);
    printf("%d\n", contarCantidad(nombres, nombre, tam));
    free(aux);
    return 0;
}

void cargarDatos(char nombres[][TAM], int tam)
{
    int i;
    char *aux;
    aux = calloc(TAM, sizeof(char));
    for (i = 0; i < tam; i++)
    {
        printf("\nIngrese el apellido y nombre: ");
        aux = LeerTexto();
        strcpy(nombres[i], aux);
    }
}

int contarCantidad(char nombres[][TAM], char nombre[], int tam)
{
    int i = 0, j = 0, k = 0, flag = 0, cnt = 0;
    char aux[TAM] = {0};
    for (j = 0; j < tam; j++)
    {
        i = 0;
        flag = 0;
        k = 0;
        while (i < strlen(nombres[j]) && flag == 0)
        {
            if (nombres[j][i] == ' ' && flag == 0)
            {
                flag = 1;
            }
            i++;
        }
        flag = 0;
        while (i < strlen(nombres[j]) && flag == 0)
        {
            if (nombres[j][i] == ' ' || nombres[j][i] == '\n')
            {
                flag = 1;
            }
            else
            {
                aux[k] = nombres[j][i];
                k++;
            }
            i++;
        }
        if (strcmp(aux, nombre) == 0)
        {
            cnt++;
        }
        for(i=0;i<strlen(nombres[j]); i++)
        {
            aux[i] = 0;
        }
    }
    return cnt;
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