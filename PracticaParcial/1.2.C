/*
Una clínica veterinaria requiere un programa en C para gestionar su inventario. 
El sistema debe reservar memoria dinámica inicialmente para 40 artículos. 
De cada producto se registra la siguiente información:
Código: Formato alfanumérico "XXX/000" (tres letras, una barra y tres números).
Nombre completo: Cadena de caracteres.
Tipo: Carácter validado ('A' Alimentos, 'V' Vacunas, 'C' Cuidados).
Inventario: Cantidad en stock (número real).
Luego de preparar el sistema, se comenzarán a registrar las compras de reposición. 
Por cada compra se ingresará el Código del artículo y la Cantidad comprada (validar que sea un real mayor a 0). 
El ingreso de compras finalizará al introducir el código "FFF/000".
Durante este proceso de compras, se debe contemplar lo siguiente:
Si el código ya existe en el arreglo, se debe actualizar su inventario sumando la cantidad comprada.
Si el código no existe, se debe dar de alta como un artículo nuevo, solicitando al usuario el nombre y el tipo, 
y redimensionando la memoria del arreglo para agregarlo.
Al finalizar el programa, se debe informar por pantalla:
La cantidad total acumulada en el inventario por cada Tipo de artículo.
La cantidad exacta de artículos nuevos que fueron añadidos al catálogo original.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct
{
    char codigo[8];
    char nombre[50];
    char tipo;
    int stock;
} Articulo;

int Buscar(Articulo *, int, char[]);
void leer(char[], int);
Articulo CargaIndividual(char[], int);
int ComprobarCodigo(char[], int);
void MostrarCantidad(Articulo *, int);
void CargaSegura(Articulo*, int);
int MayorCero();

int main()
{
    Articulo *Art, *aux;
    int i=5,band=1,stock,idx;
    char cod[8];
    Art = (Articulo*)malloc(i*sizeof(Articulo));
    if(!Art)
    {
        printf("\nNo se pudo asignar memoria");
        exit(1);
    }
    CargaSegura(Art, i);
    printf("\nInicia la compra: ");
    aux = Art;
    while(ComprobarCodigo(cod, 8) != -1)
    {
        idx = Buscar(Art, i, cod);
        if(idx==-1 && band == 1)
        {
            aux = (Articulo*)realloc(Art, (i+1)*sizeof(Articulo));
            if(aux==NULL)
            {
                printf("\nNo se pueden agregar mas articulos.");
                band = 0;
            }
            else
            {
                Art = aux;
                *(Art+i) = CargaIndividual(cod, 50);
                i++;
            }
        }
        else
        {
            if(band==0 && idx==-1)
            {
                printf("\nNo se permiten cargar mas articulos nuevos.");
            }
            else
            {
                printf("\nIngrese la cantidad: ");
                stock = MayorCero();
                (Art+idx)->stock+=stock;
            }
        }
    }
    MostrarCantidad(Art, i);
    printf("\nLa cantidad de elementos añadidos post carga es: %d",i-5);
    free(Art);
    return 0;
}

int Buscar(Articulo *v, int tam, char cod[])
{
    int i=0,idx=-1;
    while(i<tam && idx==-1)
    {
        if(strcmp((v+i)->codigo, cod)==0)
            idx=i;
        else 
            i++;
    }
    return idx;
}

void leer(char cod[], int tam)
{
    int i=0;
    getchar();
    fgets(cod,tam,stdin);
    while(i<tam && cod[i] != '\0')
    {
        if(cod[i] == '\n')
        {
            cod[i] = '\0';
        }
        else
        {
            i++;
        }
    }
}

int ComprobarCodigo(char cod[], int tam)
{
    int flag=0,flag2=1,i;
    leer(cod, tam);
    while(flag==0)
    {
        flag2 = 1;
        i=0;
        while(i<3 && flag2)
        {
            if(!isalpha(cod[i]))
            {
                flag2=0;
            }
            i++;
        }
        if(flag2)
        {
            if(cod[i] == '/')
            {
                i++;
            }
            else
            {
                flag2 = 0;
            }
            if(flag2)
            {
                while(i<7 && flag2)
                {
                    if(!isdigit(cod[i]))
                    {
                        flag2 = 0;
                    }
                    i++;
                }
            }
        }
        if(flag2)
        {
            flag = 1;
        }
        else leer(cod,tam);
    }
    if(strcmp("FFF/000",cod)==0)
    {
        flag = -1;
    }
    return flag;
}

int MayorCero()
{
    int stock;
    printf("\nIngrese stock: ");
    scanf("%d",&stock);
    while(stock < 0)
    {
        printf("\nIngrese stock valido: ");
        scanf("%d",&stock);
    }
    return stock;
}

Articulo CargaIndividual(char cod[], int tamNom)
{
    char nombre[50], tipo;
    int stock;
    Articulo aux;
    strcpy(aux.codigo, cod);
    printf("\nIngrese un nombre: ");
    leer(nombre, tamNom);
    getchar();
    printf("\nIngrese el tipo: ");
    scanf("%c",&tipo);
    while(tipo != 'C' && tipo != 'V' && tipo != 'A')
    {
        printf("\nIngrese un tipo valido: ");
        scanf("%c",&tipo);
    }
    stock = MayorCero();
    strcpy(aux.nombre, nombre);
    aux.tipo = tipo;
    aux.stock = stock;
    return aux;
}

void CargaSegura(Articulo *Art, int tam)
{
    int i;
    char cod[8];

    for(i=0;i<tam;i++)
    {
        ComprobarCodigo(cod, 8);
        while(Buscar(Art, i, cod) != -1)
        {
            ComprobarCodigo(cod, 8);
        }
        *(Art+i) = CargaIndividual(cod, 50);
    }
}

void MostrarCantidad(Articulo *v, int tam)
{
    int cntA=0, cntV=0, cntC=0, i;
    for(i=0;i<tam;i++)
    {
        switch((v+i)->tipo)
        {
            case 'V':
                cntV+=(v+i)->stock;
                break;
            case 'A':
                cntA+=(v+i)->stock;
                break;
            case 'C':
                cntC+=(v+i)->stock;
                break;
        }
    }
    printf("\nLa cantidad de tipos V fueron %d, los de A %d y los de C %d\n",cntV, cntA, cntC);
}