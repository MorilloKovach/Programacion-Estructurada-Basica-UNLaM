#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX8 99999999
#define MIN8 1
#define MAXTIT 50
#define MAXAUT 40


typedef struct
{
    int codigo;
    char titulo[MAXTIT];
    char autor[MAXTIT];
    int stock;
} Libros;

void MostrarLibros(Libros *, int);
int Buscar(Libros *, int, int);
int CargaStock();
void leer(char[], int);
int ValidarCodigo(int, int, int);
Libros CargaIndividual(Libros *, int);
void CargaVentas(Libros *, int);

int main()
{
    Libros *lib, *aux;
    Libros libro;
    int band = 1;
    int cant = 0, cap = 10;
    lib = calloc(cap, sizeof(Libros));
    if (lib == NULL)
    {
        printf("\nNO SE PUDO ASIGNAR MEMORIA.");
        free(lib);
        exit(1);
    }
    libro = CargaIndividual(lib, cant);
    aux = lib;
    while (libro.codigo != 0 && band == 1)
    {
        *(aux + cant) = libro;
        cant++;
        if (cant == cap)
        {
            aux = (Libros *)realloc(lib, (cap + 10) * sizeof(Libros));
            if (aux == NULL)
            {
                printf("\nNo se pudo asignar memoria.");
                band = 0;
            }
            else
            {
                lib = aux;
            }
            cap += 10;
        }
        if (band)
            libro = CargaIndividual(lib, cant);
    }
    if (cant > 0)
    {
        CargaVentas(lib, cant);
        MostrarLibros(lib, cant);
    }
    else
    {
        printf("\nNo se han asignado libros.");
    }
    free(lib);
    return 0;
}

int Buscar(Libros *lib, int tam, int cod)
{
    int i = 0, idx = -1;
    while (i < tam && idx == -1)
    {
        if ((lib + i)->codigo == cod)
        {
            idx = i;
        }
        i++;
    }
    return idx;
}

int CargaStock()
{
    int stock;
    printf("\nIngrese el valor: ");
    scanf("%d", &stock);
    while (stock < 0)
    {
        printf("\nError. No puede ser numero negativo: ");
        scanf("%d", &stock);
    }
    return stock;
}

int ValidarCodigo(int linf, int lsup, int fin)
{
    int cod;
    printf("\nIngrese el codigo: ");
    scanf("%d", &cod);
    while (!(cod >= linf && cod <= lsup) && cod != fin)
    {
        printf("\nError. Ingrese un codigo nuevamente: ");
        scanf("%d", &cod);
    }
    return cod;
}

void leer(char aux[], int tam)
{
    int i;
    getchar();
    fgets(aux, tam, stdin);
    i = 0;
    while (i < tam && *(aux + i) != '\0')
    {
        if (*(aux + i) == '\n')
        {
            *(aux + i) = '\0';
        }
        else
        {
            i++;
        }
    }
    return aux;
}
Libros CargaIndividual(Libros *lib, int tam)
{
    Libros v;
    char aux[MAXTIT];
    v.codigo = ValidarCodigo(MIN8, MAX8, 0);
    while (v.codigo != 0 && Buscar(lib, tam, v.codigo) != -1)
    {
        printf("\n%d %d\n", tam, v.codigo);
        printf("\nError. Ingrese otro codigo, pues el anterior ya existe.");
        v.codigo = ValidarCodigo(MIN8, MAX8, 0);
    }
    if (v.codigo != 0)
    {
        printf("\nIngrese el titulo: ");
        leer(aux, MAXTIT);
        strcpy(v.titulo, aux);
        printf("\nIngrese el autor: ");
        leer(aux, MAXAUT);
        strcpy(v.autor, aux);
        v.stock = CargaStock();
    }
    return v;
}

void CargaVentas(Libros *lib, int tam)
{
    int cod, idx, unidades;
    cod = ValidarCodigo(MIN8, MAX8, 0);
    idx = Buscar(lib, tam, cod);
    while (idx == -1 && cod != 0)
    {
        cod = ValidarCodigo(MIN8, MAX8, 0);
        idx = Buscar(lib, tam, cod);
    }
    while (cod != 0)
    {
        printf("\nCarga de unidades a vender\n");
        unidades = CargaStock();
        while (unidades > (lib + idx)->stock)
        {
            printf("\nError. Las unidades son inferiores a la cantidad de stock. ");
            unidades = CargaStock();
        }
        (lib + idx)->stock -= unidades;
        cod = ValidarCodigo(MIN8, MAX8, 0);
        idx = Buscar(lib, tam, cod);
        while (idx == -1 && cod != 0)
        {
            cod = ValidarCodigo(MIN8, MAX8, 0);
            idx = Buscar(lib, tam, cod);
        }
    }
}
void MostrarLibros(Libros *lib, int tam)
{
    int i;
    printf("\nCODIGO \t TITULO \t AUTOR \t STOCK ACTUALIZADO");
    for (i = 0; i < tam; i++)
    {
        printf("\n%d \t %s \t %s \t %d", (lib + i)->codigo, (lib + i)->titulo, (lib + i)->autor, (lib + i)->stock);
    }
}