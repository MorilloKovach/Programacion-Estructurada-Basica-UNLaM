#include<stdio.h>

int main()
{
    int i, cont=0, flag=0;
    char pal[500];

    printf("\nIngrese: ");
    fgets(pal, 500, stdin);

    i=0;
    while(i<500 && pal[i] != '\n')
    {
        if(pal[i] == ' ' && !flag)
        {
            flag = 1;
            cont++;
        }
        else{
            if(pal[i] != ' ')
            {
                flag = 0;
            }
        }
        i++;
    }
    if(pal[i] == '\n')
    {
        cont++;
    }
    printf("\nLa cantidad de palabras es: %d\n",cont);
    return 0;
}