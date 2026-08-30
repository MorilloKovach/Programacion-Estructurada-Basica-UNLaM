#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define TAM 11

char *validarContrasenia();

int main()
{
    char *contra1, *contra2;
    int flag = 0;
    do
    {
        if(flag)
        {
            printf("\nError. No coinciden las contrasenias. ");
        }
        printf("\n\nINGRESAR PRIMERA CONTRASEÑA\n\n");
        system("clear");
        contra1 = validarContrasenia();
        printf("\n\nINGRESANDO SEGUNDA CONTRASEÑA\n\n");
        contra2 = validarContrasenia();
        system("clear");
        flag = 1;
    }while(strcmp(contra1, contra2) != 0);
    free(contra1);
    free(contra2);
    return 0;
}
char *validarContrasenia()
{
    char *contrasenia;
    int digitos=0,letras=0,esp=0,i;
    contrasenia = calloc(TAM, sizeof(char));
    do
    {
        digitos=0;
        letras=0;
        esp=0;
        printf("\nIngrese la contrasenia: ");
        scanf("%10s",contrasenia);
        for(i=0;i<strlen(contrasenia);i++)
        {
            if(isalpha(contrasenia[i]))
            {
                letras++;
            }
            else
            {
                if(isdigit(contrasenia[i]))
                {
                    digitos++;
                }
                else
                {
                    if(ispunct(contrasenia[i]))
                    {
                        esp++;
                    }
                }
            }
        }
    }while(digitos != 2 || esp != 1 || letras != 7);
    return contrasenia;
}

