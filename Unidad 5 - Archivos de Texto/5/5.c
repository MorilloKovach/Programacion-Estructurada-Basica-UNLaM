/*
Se dispone del archivo “sepadaroresVarios.txt” cuyas cadenas se encuentran separadas por punto, espacios
o comas. Realizar un programa para obtener e imprimir por pantalla cada cadena. 
*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main()
{
    FILE *fp = fopen("sepadaroresVarios.txt", "r");
    char *parte;
    char linea[300];
    while(fgets(linea, 300, fp))
    {
        parte = strtok(linea, ";");
        while(parte != NULL)
        {
            parte = strtok(NULL, ";");
            printf("\n%s\n", parte);
        }
    }
    fclose(fp);

    return 0;
}