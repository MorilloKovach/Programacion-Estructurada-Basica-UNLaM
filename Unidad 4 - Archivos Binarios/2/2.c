/*
Se supone que tiene que existir el archivo ALUMNOS.dat para hacer este proceso.
Pero la realidad es que aca nos da igual. Abrazo.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int DNI;
    char nombre_ap[81];
    int nota1, nota2;
    float promedio;
}ALUMNO;

void GenerarPromocionados(ALUMNO*, int);
void GenerarCursados(ALUMNO*, int);
void GenerarReprobados(ALUMNO*, int);
void LeerDatos(FILE*);

int main()
{
    FILE *fp = fopen("ALUMNOS.dat", "rb");
    ALUMNO *a, *aux;
    int i=1;
    a = (ALUMNO*)malloc(1*sizeof(ALUMNO));
    fread(a, sizeof(ALUMNO), 1, fp);
    while(!feof(fp))
    {
        aux = (ALUMNO*)realloc(a, (i+1)*sizeof(ALUMNO));
        if(aux==NULL)
        {
            printf("\nError en el asignamiento de memoria");
            getchar();
            exit(1);
        }
        a = aux;
        fread((a+i), sizeof(ALUMNO), 1, fp);
        i++;
    }
    GenerarPromocionados(a, i);
    GenerarCursados(a, i);
    GenerarReprobados(a, i);
    fclose(fp);
    printf("\nLOS PROMOCIONADOS SON: ");
    fp = fopen("PROMOCIONADOS.dat", "rb");
    LeerDatos(fp);
    fclose(fp);
    printf("\nLOS CURSADOS SON: ");
    fp = fopen("CURSADOS.dat", "rb");
    LeerDatos(fp);
    fclose(fp);
    printf("\nLOS REPROBADOS SON: ");
    fp = fopen("REPROBADOS.dat","rb");
    LeerDatos(fp);
    fclose(fp);

    free(a);
    return 0;
}

void LeerDatos(FILE *fp)
{
    ALUMNO a;
    fread(&a, sizeof(ALUMNO), 1, fp);
    while(!feof(fp))
    {
        printf("\nEl dato es %s %d %d %d %.2f",a.nombre_ap,a.DNI,a.nota1,a.nota2,a.promedio);
        fread(&a, sizeof(ALUMNO), 1, fp);
    }
}

void GenerarPromocionados(ALUMNO* a, int tam)
{
    int i;
    FILE *fp = fopen("PROMOCIONADOS.dat", "wb");
    for(i=0;i<tam;i++)
    {
        if((a+i)->nota1 >= 7 && (a+i)->nota2 >= 7)
        {
            fwrite((a+i), sizeof(ALUMNO), 1, fp);
        }
    }
    fclose(fp);
}

void GenerarCursados(ALUMNO* a, int tam)
{
    int i;
    FILE *fp = fopen("CURSADOS.dat", "wb");
    for(i=0;i<tam;i++)
    {
        if((a+i)->nota1 >= 4 && (a+i)->nota2 >= 4 && !((a+i)->nota1 >= 7 && (a+i)->nota2 >= 7))
        {
            fwrite((a+i), sizeof(ALUMNO), 1, fp);
        }
    }
    fclose(fp);
}

void GenerarReprobados(ALUMNO* a, int tam)
{
    int i;
    FILE *fp = fopen("REPROBADOS.dat", "wb");
    for(i=0;i<tam;i++)
    {
        if((a+i)->nota1 < 4 || (a+i)->nota2 < 4)
        {
            fwrite((a+i), sizeof(ALUMNO), 1, fp);
        }
    }
    fclose(fp);
}
