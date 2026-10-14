#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int DNI;
    int dia, mes, anio;
} Pagos;

typedef struct
{
    int DNI;
    char nombre[41];
} Alumnos;

int Buscar(FILE *, Pagos *, int);
void CargaAlumnosYPagos(FILE *, FILE *);
void LeerTexto(char[], int);
int LeerYValidarEntero(int, int);
int LeerYValidarDNI(int, int, int);
void LeerYValidarFecha(int *, int *, int *, int, int);
FILE *AbrirArchivo(char[], char[]);
void RomperSiFalla(void *);
Alumnos CargaAlumno(int);
Pagos CargaPago(int);

int main()
{
    FILE *fpAlumnos = AbrirArchivo("alumnos.dat", "r+b");
    FILE *fpPagos = AbrirArchivo("pagos.dat", "r+b");
    Alumnos a;
    Pagos p;
    CargaAlumnosYPagos(fpAlumnos, fpPagos);
    printf("\nLos que adeudan la ultima cuota (febrero de 2024) son: ");
    rewind(fpAlumnos);
    fread(&a, sizeof(Alumnos), 1, fpAlumnos);
    while (!feof(fpAlumnos))
    {
        Buscar(fpPagos, &p, a.DNI);
        if (p.mes != 2 || p.anio != 2024)
        {
            printf("\n%d %s\n", a.DNI, a.nombre);
        }
        fread(&a, sizeof(Alumnos), 1, fpAlumnos);
    }
    fclose(fpAlumnos);
    fclose(fpPagos);
    return 0;
}

FILE *AbrirArchivo(char origen[], char mod[])
{
    FILE *fp = fopen(origen, mod);
    RomperSiFalla(fp);
    return fp;
}

void RomperSiFalla(void *ptr)
{
    if (ptr == NULL)
    {
        exit(1);
    }
}

void LeerTexto(char cad[], int tam)
{
    int i = 0;
    while (getchar() != '\n')
        ;
    fgets(cad, tam, stdin);
    while (i < tam && cad[i] != '\0')
    {
        if (cad[i] == '\n')
        {
            cad[i] = '\0';
        }
        else
        {
            i++;
        }
    }
}

int LeerYValidarEntero(int linf, int lsup)
{
    int num;
    do
    {
        printf("\nIngrese un valor entre %d y %d: ", linf, lsup);
        scanf("%d", &num);
    } while (num < linf || num > lsup);
    return num;
}

int Buscar(FILE *fp, Pagos *p, int cod)
{
    int band = 0;
    rewind(fp);
    fread(p, sizeof(Pagos), 1, fp);
    while (!band && !feof(fp))
    {
        if (p->DNI == cod)
        {
            band = 1;
        }
        else
        {
            fread(p, sizeof(Pagos), 1, fp);
        }
    }
    return band;
}

void LeerYValidarFecha(int *dia, int *mes, int *anio, int mesLim, int anioLim)
{
    int band = 1;
    do
    {
        band = 1;
        printf("\nIngrese el dia: ");
        *dia = LeerYValidarEntero(1, 31);
        printf("\nIngrese el mes: ");
        *mes = LeerYValidarEntero(1, 12);
        printf("\nIngrese el anio: ");
        *anio = LeerYValidarEntero(2000, 2024);
        if (*mes > mesLim && *anio >= anioLim)
        {
            band = 0;
        }
    } while (!band);
}
int LeerYValidarDNI(int linf, int lsup, int corte)
{
    int num;
    do
    {
        printf("\nIngrese el numero (entre %d y %d): ", linf, lsup);
        scanf("%d", &num);
    } while ((num < linf || num > lsup) && num != corte);
    return num;
}
void CargaAlumnosYPagos(FILE *fpAlumnos, FILE *fpPagos)
{
    Alumnos a;
    Pagos p;
    int DNI, opc;
    printf("\nIngrese un DNI (o 0 para terminar): ");
    DNI = LeerYValidarDNI(1000000, 99999999, 0);
    while (DNI != 0)
    {
        if (!Buscar(fpPagos, &p, DNI))
        {
            printf("\nNo existe ese DNI. ¿Desea ingresarlo a la plataforma? (1 si, 2 no): ");
            opc = LeerYValidarEntero(1, 2);
            if (opc == 1)
            {
                a = CargaAlumno(DNI);
                fseek(fpAlumnos, (long)0, SEEK_END);
                fwrite(&a, sizeof(Alumnos), 1, fpAlumnos);
                p = CargaPago(DNI);
                fseek(fpPagos, (long)0, SEEK_END);
                fwrite(&p, sizeof(Pagos), 1, fpPagos);
            }
            else
            {
                printf("\nOk.");
            }
        }
        else
        {
            p = CargaPago(DNI);
            fseek(fpPagos, (long)sizeof(Pagos) * -1, SEEK_CUR);
            fwrite(&p, sizeof(Pagos), 1, fpPagos);
            fseek(fpPagos, (long)0, SEEK_END);
        }

        printf("\nIngrese otro DNI (o 0 para terminar): ");
        DNI = LeerYValidarDNI(1000000, 99999999, 0);
    }
}

Alumnos CargaAlumno(int DNI)
{
    Alumnos a;
    a.DNI = DNI;
    printf("\nIngrese el nombre: ");
    LeerTexto(a.nombre, 41);
    return a;
}

Pagos CargaPago(int DNI)
{
    Pagos p;
    p.DNI = DNI;
    LeerYValidarFecha(&p.dia, &p.mes, &p.anio, 2, 2024);
    return p;
}