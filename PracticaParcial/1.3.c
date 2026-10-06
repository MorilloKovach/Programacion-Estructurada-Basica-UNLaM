/*
Un centro odontológico administra la agenda de turnos para un día determinado. 
Cada turno se representa mediante una estructura con los siguientes datos:

DNI del Paciente (entero).
Nombre del Paciente (cadena de hasta 50 caracteres).
Estado del Turno (entero: 1 para "Pendiente", 2 para "Atendido", 3 para "Cancelado").

Se deben ingresar los datos de los turnos en un vector de estructuras asignado dinámicamente en memoria.
El arreglo debe comenzar con una capacidad inicial de 10 turnos.
Cada vez que el arreglo se llene, su capacidad debe aumentarse dinámicamente de 10 en 10.
Al ingresar el DNI se debe validar que el paciente no tenga ya un turno asignado en el vector. La carga finaliza con DNI = 0.

Finalizada la carga, se ingresará una secuencia de DNI de pacientes que van llegando a la recepción, terminando con DNI = 0.
Si el DNI existe, se debe cambiar el estado del turno a 2: "Atendido".
Si el DNI no existe, se lo contabilizará como "Paciente No Registrado".
Informar:
a) La cantidad total de pacientes que asistieron, pero no tenían turno.
b) El listado completo de la agenda ordenado de forma ascendente por DNI, mostrando DNI, Nombre y estado.
Implementar al menos dos funciones: Una para la búsqueda del DNI en el vector de estructuras, y otra para el ordenamiento.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dni;
    char nombre[50];
    int tipo;
} Paciente;

int Buscar(Paciente *, int, int);
void Ordenar(Paciente *, int);
Paciente CargaIndividual(int);
int AsistenClinica(Paciente *, int);
int validarDni();
void leer(char[], int);
int validarTipo();

int main()
{
    Paciente *p, *aux, paciente;
    int cant = 0, cap = 10, band = 1, dni, sinturno,i=0;
    p = (Paciente *)malloc(cap * sizeof(Paciente));
    aux = p;
    dni = validarDni();
    while (dni != 0 && band)
    {
        if (cant == cap)
        {
            aux = (Paciente *)realloc(p, cap * sizeof(Paciente));
            if (!aux)
            {
                printf("\nNo se puede seguir la carga, no hay memoria.");
                band = 0;
            }
            else
            {
                cap += 10;
                p = aux;
            }
        }
        if (band)
        {
            while (Buscar(p, cant, dni) != -1)
            {
                dni = validarDni();
            }
            if (dni != 0)
            {
                paciente = CargaIndividual(dni);
                *(p+cant) = paciente;
                cant++; 
                dni = validarDni();
            }
        }
    }
    printf("\nInicia la carga de los atendidos: ");
    sinturno = AsistenClinica(p, cant);
    printf("\nLa cantidad de pacientes sin turno fue %d ",sinturno);
    Ordenar(p, cant);
    printf("\nDNI\tNOMBRE\tESTADO");
    for(i=0;i<cant;i++)
    {
        printf("\n%d \t %s \t %d\n", (p+i)->dni, (p+i)->nombre, (p+i)->tipo);
    }
}
int Buscar(Paciente *p, int tam, int dni)
{
    int i=0, idx=-1;
    while(i<tam && idx == -1)
    {
        if((p+i)->dni == dni)
        {
            idx = i;
        }
        else i++;
    }
    return idx;
}
int AsistenClinica(Paciente *p, int tam)
{
    int dni, idx, SinTurno=0;
    dni = validarDni();
    while(dni != 0)
    {
        idx = Buscar(p, tam, dni);
        if(idx==-1)
        {
            SinTurno++;
        }
        else
        {
            if((p+idx)->tipo==2)
            {
                printf("\nEste usuario ya fue atendido!");
            }
            else{
                (p+idx)->tipo = 2;
            }
        }
        dni = validarDni();
    }
    return SinTurno;

}
void Ordenar(Paciente *p, int tam)
{
    int i,j;
    Paciente aux;
    for(i=0;i<tam-1;i++)
    {
        for(j=0;j<tam-i-1;j++)
        {
            if((p+j)->dni > (p+j+1)->dni)
            {
                aux = *(p+j);
                *(p+j) = *(p+j+1);
                *(p+j+1) = aux;
            }
        }
    }
}
int validarDni()
{
    int DNI;
    printf("Ingrese dni: ");
    scanf("%d", &DNI);
    while (DNI < 0)
    {
        printf("\nIngrese otro DNI: ");
        scanf("%d", &DNI);
    }
    return DNI;
}
void leer(char stri[], int tam)
{
    int i = 0;
    getchar();
    fgets(stri, tam, stdin);
    while(i<tam && stri[i] != '\0')
    {
        if(stri[i] == '\n')
        {
            stri[i] = '\0';
        }
        else i++;
    }
}

Paciente CargaIndividual(int dni)
{
    int tipo;
    char nombre[50];
    Paciente aux;
    leer(nombre, 50);
    tipo = validarTipo();

    aux.dni = dni;
    strcpy(aux.nombre, nombre);
    aux.tipo = tipo;
    return aux;
}
int validarTipo()
{
    int tipo;
    printf("Ingrese el tipo: ");
    scanf("%d", &tipo);
    while (tipo < 1 || tipo > 3)
    {
        printf("\nIngrese tipo valido: ");
        scanf("%d", &tipo);
    }
    return tipo;
}