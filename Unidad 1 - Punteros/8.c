#include<stdio.h>
#include<stdlib.h>

int main()
{
    int *v=NULL, *ptr, N=0, dni,i;
    do{
        printf("\nIngrese un DNI valido: ");
        scanf("%d",&dni);
        if(dni > 0)
        {
            if(N%5==0)
            {
                v = (int*)realloc(v, (N+5)*sizeof(int));
                ptr = v + N;
            }
            *ptr = dni;
            ptr++;
            N++;
        }
    }while(dni != 0);
    printf("\nLa cantidad de dnis existentes es: %d",N);
    ptr = v;
    for(i=0;i<N;i++)
    {
        printf("\n%d",*ptr);
        ptr++;
    }   
    free(v);

    return 0;
}