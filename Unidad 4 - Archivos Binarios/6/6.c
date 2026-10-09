/*
Dado el archivo productos.dat con la siguiente estructura:
• Código (entero)
• Precio (float)
• Descripción (de hasta 50 caracteres)
Realizar un programa que permita eliminar productos dado su código 
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int codigo;
    float precio;
    char descripcion[51];
} PRODUCTOS;
int LeerYValidarCodigo();
int BuscarEnArchivo(FILE *, PRODUCTOS *, int);
int BuscarEnMemoria(PRODUCTOS *, int, int);
PRODUCTOS *QuitarCodigos(FILE *, int *);
void AgregarEnAux(FILE *, FILE *, PRODUCTOS *, int);

int main()
{
    FILE *fp = fopen("PRODUCTOS.dat", "rb");
    FILE *fpMod = fopen("PRODUCTOS-aux.dat", "wb");
    PRODUCTOS *vP;
    int tam = 0;
    if (fpMod == NULL || fp == NULL)
    {
        printf("\nNO SE PUEDEN ABRIR LOS ARCHIVOS");
        exit(1);
    }
    vP = QuitarCodigos(fp, &tam);
    if (tam > 0)
    {
        AgregarEnAux(fp, fpMod, vP, tam);
        printf("\n...Eliminando registros...");
        fclose(fp);
        fclose(fpMod);
        remove("PRODUCTOS.dat");
        rename("PRODUCTOS-aux.dat", "PRODUCTOS.dat");
        free(vP);
        printf("\nLimpieza de archivos hecha con exito.");
    }
    else
    {
        printf("\nNo se hace nada, no se borro ningun registro.");
        fclose(fp);
        fclose(fpMod);
        remove("PRODUCTOS-aux.dat");
        free(vP);
    }
    return 0;
}

PRODUCTOS *QuitarCodigos(FILE *fp, int *tam)
{
    PRODUCTOS *auxP, *vP;
    PRODUCTOS p;
    int cod, band, i = *tam;
    vP = NULL;
    cod = LeerYValidarCodigo();
    while (cod != 0)
    {
        band = BuscarEnArchivo(fp, &p, cod); // Busco en la lista de PRODUCTOS.dat
        if (band)
        {
            if (BuscarEnMemoria(vP, i, cod)) // Busco en la lista de PRODUCTOS-aux los que fui borrando
            {
                printf("\nEse codigo ya esta guardado...");
            }
            else
            {
                auxP = (PRODUCTOS *)realloc(vP, (i + 1) * sizeof(PRODUCTOS));
                if (auxP == NULL)
                {
                    printf("\nNo se pudo asignar memoria");
                    exit(1);
                }
                else
                {
                    printf("\nTomado con exito.");
                    vP = auxP;
                    *(vP + i) = p;
                    i++;
                }
            }
        }
        cod = LeerYValidarCodigo();
    }
    *tam = i;
    return vP;
}

int BuscarEnMemoria(PRODUCTOS *p, int tam, int cod)
{
    int band = 0, i = 0;
    while (!band && i < tam)
    {
        if ((p + i)->codigo == cod)
        {
            band = 1;
        }
        else
        {
            i++;
        }
    }
    return band;
}
int LeerYValidarCodigo()
{
    int cod;
    do
    {
        printf("\nIngrese codigo: ");
        scanf("%d", &cod);
    } while ((cod < 1000 || cod > 9999) && cod != 0);
    return cod;
}
int BuscarEnArchivo(FILE *fp, PRODUCTOS *p, int cod)
{
    int band = 0;
    rewind(fp);
    fread(p, sizeof(PRODUCTOS), 1, fp);
    while (!feof(fp) && !band)
    {
        if (p->codigo == cod)
        {
            band = 1;
        }
        else
        {
            fread(p, sizeof(PRODUCTOS), 1, fp);
        }
    }
    return band;
}

void AgregarEnAux(FILE *fp, FILE *fpMod, PRODUCTOS *vP, int tam)
{
    PRODUCTOS p;
    rewind(fp);
    fread(&p, sizeof(PRODUCTOS), 1, fp);
    while (!feof(fp))
    {
        if (!BuscarEnMemoria(vP, tam, p.codigo)) // Si no encuentro en faltantes
        {
            fwrite(&p, sizeof(PRODUCTOS), 1, fpMod);
        }
        else
        {
            printf("\nBorrado con exito! %d", p.codigo);
        }
        fread(&p, sizeof(PRODUCTOS), 1, fp);
    }
}