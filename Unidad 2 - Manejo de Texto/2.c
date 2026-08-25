#include<stdio.h>
#include<string.h>
int main()
{
    char nombre[20], apellido[20], nombreComa[22], nombreApellido[50];

    printf("\nIngrese su nombre: ");
    scanf("%s",nombre);
    printf("\nIngrese su apellido: ");
    scanf("%s",apellido);
    strcat(nombreComa, nombre);
    strcat(nombreComa, ", ");
    strcat(nombreApellido, nombreComa);
    strcat(nombreApellido, apellido);
    printf("%s\n",nombreApellido);

    return 0;
}