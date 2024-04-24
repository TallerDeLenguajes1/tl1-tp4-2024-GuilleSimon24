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

    
    
  


    return 0;
}
