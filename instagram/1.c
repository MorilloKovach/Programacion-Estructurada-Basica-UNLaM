//@morillokovac

int Buscar(int[], int, int);

int main()
{
















    
}

int Buscar(int vector[], int ce, int cod)
{
    int i = 0, pos = -1;
    while(i < ce && pos == -1)
    {
        if(vector[i] == cod)
        {
            pos = i;
        }
        else
        {
            i++;
        }
    }
    return pos; //Si devuelve -1, quiere decir que no esta ese elemento.
}