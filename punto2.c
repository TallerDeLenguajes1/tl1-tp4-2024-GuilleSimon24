#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct Tarea Tarea;
typedef struct Nodo Nodo;

struct Tarea
{
    int tareaID;            //  Numerico autoincremental comenzando en 1000
    char *Descripcion;      //  
    int Duracion;           //  entre 10 - 100

};

struct Nodo
{
    Tarea T;
    Nodo *siguiente;

};

Nodo* crearListaVacia(){

    return NULL;

}

Tarea crearTarea(int *i){
    Tarea *nueva;
    nueva =malloc(sizeof(Tarea));

    char *buff=malloc(100*sizeof(char));
    nueva->tareaID = (*i)++;
    printf("\nIngrese la descripcion de la tarea: \n");
    fflush(stdin);
    gets(buff);
    
    nueva->Descripcion = malloc((strlen(buff)+1) * sizeof(char));
    strcpy(nueva->Descripcion, buff);

    free(buff);

    printf("Duracion: %d\n", (10+rand()%91));
    nueva->Duracion = (10+rand()%91);

    return *nueva;

}


Nodo* crearNodo(int *i){

    Nodo* nuevoNodo =(Nodo *)malloc(sizeof(Nodo));

    nuevoNodo->T = crearTarea(i);
    nuevoNodo->siguiente=NULL;
    
    return nuevoNodo;
    
}

void insertarNodo(Nodo **start, Nodo *nuevo){
    nuevo->siguiente = *start;
    *start = nuevo;

}

void mostrarLista(Nodo **start){
   Nodo *aux = *start;
    while (aux != NULL)
    {
        printf("\nId: %d\n", aux->T.tareaID);
        printf("Descripcion: ");
        puts(aux->T.Descripcion);
        printf("Duracion: %d\n", aux->T.Duracion);
        aux = aux->siguiente;
    }
    
}

Nodo buscarTarea(Nodo** start, int ID){
    Nodo* buscada =malloc(sizeof(Nodo));
    buscada = *start;
    while (buscada->T.tareaID != ID)
    {
        buscada = buscada->siguiente;
    }

    return *buscada;
}

void quitarTarea(Nodo**start, int ID){
    Nodo** aux = &(*start);
    while (*aux!=NULL && ((*aux)->T.tareaID != ID))
    {
        aux = &(*aux)->siguiente;
    }
    
    if (aux)
    {   
        Nodo* temp= *aux;
        *aux = (*aux)->siguiente;
        free(temp);   
    }
    
}

void buscarPorId(Nodo** startPend, Nodo** startReal, int ID){
    //NO ENTIENDO POR QUE REPINGO NO FUNCIONA
    Nodo* buscarPend = *startPend;
    Nodo* buscarReal = *startReal;
    int bandera = 0;
    while (buscarPend != NULL && bandera == 0)
    {
        if (buscarPend->T.tareaID == ID)
        {
            printf("\nID: %d\n", buscarPend->T.tareaID);
            printf("Descripcion: ");
            puts(buscarPend->T.Descripcion);
            printf("Duracion: %d\n", buscarPend->T.Duracion);
            bandera = 1;
        }
        buscarPend = buscarPend->siguiente;
    }
    
    if (bandera==0)
    {
        while (buscarReal != NULL && bandera ==0)
        {
            if (buscarReal->T.tareaID == ID)
            {
                printf("\nID: %d\n", buscarReal->T.tareaID);
                printf("Descripcion: ");
                puts(buscarReal->T.Descripcion);
                printf("Duracion: %d\n", buscarReal->T.Duracion);
                bandera = 1;
            }

            buscarReal = buscarReal->siguiente;
        }
    }else
    {
        puts("No se encontro");
    }
    
}

void buscarPorPalabra(Nodo** startPend, Nodo** startReal, char frase[]){
    Nodo* buscarPend = *startPend;
    Nodo* buscarReal = *startReal;
    int bandera = 0;
    while (buscarPend != NULL && bandera == 0)
    {
        if (strstr(buscarPend->T.Descripcion, frase))
        {
            printf("\nID: %d\n", buscarPend->T.tareaID);
            printf("Descripcion: ");
            puts(buscarPend->T.Descripcion);
            printf("Duracion: %d\n", buscarPend->T.Duracion);
            bandera = 1;
        }
        buscarPend = buscarPend->siguiente;
    }
    if (bandera == 0)
    {
        while (buscarReal != NULL && bandera == 0)
        {
            if (strstr(buscarReal->T.Descripcion, frase))
            {
                printf("\nID: %d\n", buscarReal->T.tareaID);
                printf("Descripcion: ");
                puts(buscarReal->T.Descripcion);
                printf("Duracion: %d\n", buscarReal->T.Duracion);
                bandera = 1;    
            }          
        }
        buscarReal = buscarReal->siguiente;
    }
    
    
}

int main(){

    srand(time(NULL));
    
    Nodo *startPendientes = crearListaVacia();
    Nodo *startRealizadas = crearListaVacia();

    int i=1000;

    int seguir = 1;
    printf("Comienza la carga de datos: \n");
    while (seguir != 0)
    {
        Nodo *aux = crearNodo(&i);
        insertarNodo(&startPendientes, aux);
        puts("Desea seguir insertando pendientes?");
        puts("1_ SI");
        puts("0_ NO");
        scanf("%d", &seguir);

    }

    mostrarLista(&startPendientes);
    int IDBuscado;
    printf("\nSeleccionar el ID a mover: ");
    fflush(stdin);
    scanf("%d", &IDBuscado);
    Nodo auxiNodo =buscarTarea(&startPendientes, IDBuscado);
    quitarTarea(&startPendientes, IDBuscado);
    insertarNodo(&startRealizadas, &auxiNodo);

    puts("Lista de pendientes:");
    mostrarLista(&startPendientes);
    puts("--------------");
    puts("Lista de realizadas"); 
    mostrarLista(&startRealizadas);


    printf("\n");
    puts("Ingrese el ID a buscar: ");
    fflush(stdin);
    scanf("%d", &IDBuscado);
    buscarPorId(&startPendientes, &startRealizadas, IDBuscado);
    
    buscarPorPalabra(&startPendientes, &startRealizadas, "simoca");
    
    
  


    return 0;
}
