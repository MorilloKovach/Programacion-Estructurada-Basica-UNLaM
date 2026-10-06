#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int DNI;
    char nombre_ap[81];
    int nota1, nota2;
    float promedio;
}ALUMNO;
void leer(char[], int);
int LeerYValidarNota();
int LeerYValidarDni();
int Buscar(ALUMNO*, int, int);
void Lectura();
ALUMNO CargarIndividual(int);

int main()
{
    ALUMNO *a=NULL, *aux;
    int dni, i=0;
    FILE *fp = fopen("ALUMNOS.dat", "wb");
    if(fp==NULL)
    {
        printf("\nError al abrir!");
        getchar();
        exit(1);
    }
    dni = LeerYValidarDni();
    while(dni != 0)
    {
        aux = (ALUMNO*)realloc(a,(i+1)*sizeof(ALUMNO));
        if(aux==NULL)
        {
            printf("\nNo se puede asignar memoria");
            exit(1);
        }
        a = aux;
        *(a+i) = CargarIndividual(dni);
        fwrite((a+i), sizeof(ALUMNO), 1, fp);
        i++;
        do
        {
            dni = LeerYValidarDni();
        }while(Buscar(a,i,dni) != -1);
    }
    fclose(fp);
    Lectura();
    free(a);
    return 0;
}

int Buscar(ALUMNO *a, int tam, int dni)
{
    int i = 0, idx = -1;
    while(i<tam && idx == -1)
    {
        if((a+i)->DNI == dni)
        {
            idx = i;
        }
        i++;
    }
    return idx;
}

void leer(char str[], int tam)
{
    int i = 0;
    while(getchar() != '\n');
    fgets(str, tam, stdin);
    while(i<tam && str[i] != '\0')
    {
        if(str[i] == '\n')
        {
            str[i] = '\0';
        }
        else
        {
            i++;
        }
    }
}

int LeerYValidarNota()
{
    int nota;
    do
    {
        printf("\nIngrese la nota (entre 1 a 10): ");
        scanf("%d",&nota);
    }while(nota < 1 || nota > 10);
    return nota;
}

int LeerYValidarDni()
{
    int dni;
    do
    {
        printf("\nIngrese dni (mayor o igual a 0): ");
        scanf("%d",&dni);
    }while(dni<0);
    return dni;
}
ALUMNO CargarIndividual(int dni)
{
    ALUMNO a;
    a.DNI = dni;
    printf("\nIngrese su nombre: ");
    leer(a.nombre_ap, 81);
    a.nota1 = LeerYValidarNota();
    a.nota2 = LeerYValidarNota();
    a.promedio = (float)(a.nota1+a.nota2)/2.0;
    return a;
}

void Lectura()
{
    FILE *fp = fopen("ALUMNOS.dat", "rb");
    ALUMNO aux;
    fread(&aux, sizeof(ALUMNO), 1, fp);
    while(!feof(fp))
    {
        printf("\nSe guardo. %s %d %d %d %.2f\n", aux.nombre_ap, aux.DNI, aux.nota1, aux.nota2, aux.promedio);
        fread(&aux, sizeof(ALUMNO), 1, fp);
    }
    fclose(fp);
}