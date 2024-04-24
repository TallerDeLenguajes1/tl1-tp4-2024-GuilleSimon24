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

    char *buff=malloc(100*sizeof(char));                    //Reservo memoria
    nueva->tareaID = (*i)++;                                //Con esto hago que el i se vaya autoincrementando
    printf("\nIngrese la descripcion de la tarea: \n");
    fflush(stdin);
    gets(buff);
    
    nueva->Descripcion = malloc((strlen(buff)+1) * sizeof(char));
    strcpy(nueva->Descripcion, buff);                       //Guardo lo ingresado en la tarea

    free(buff);

    printf("Duracion: %d\n", (10+rand()%91));
    nueva->Duracion = (10+rand()%91);

    return *nueva;

}


Nodo* crearNodo(int *i){

    Nodo* nuevoNodo =(Nodo *)malloc(sizeof(Nodo));      //Creo el nodo

    nuevoNodo->T = crearTarea(i);                       //Llamo a la otra funcion para ingresar la tarea
    nuevoNodo->siguiente=NULL;                          //Inicializo en NULL, otra funcion se encarga de enlazar
    
    return nuevoNodo;
    
}

void insertarNodo(Nodo **start, Nodo *nuevo){
    nuevo->siguiente = *start;                          //Enlazo la parte de atras del nodo
    *start = nuevo;                                     //Enlazo la parte de adelante del nodo

}

void mostrarLista(Nodo **start){
   Nodo *aux = *start;
    while (aux != NULL)                                 //Recorre y va mostrando
    {
        printf("\nId: %d\n", aux->T.tareaID);
        printf("Descripcion: ");
        puts(aux->T.Descripcion);
        printf("Duracion: %d\n", aux->T.Duracion);
        aux = aux->siguiente;
    }
    
}

Nodo buscarTarea(Nodo** start, int ID){
    Nodo* buscada = *start;
    while (buscada->T.tareaID != ID)                    //Mientras no sea igual al ID que quiero buscar
    {
        buscada = buscada->siguiente;
    }

    return *buscada;
}

void quitarTarea(Nodo**start, int ID){
    Nodo** aux = &(*start);                             //Guardo en un auxiliar
    while (*aux!=NULL && ((*aux)->T.tareaID != ID))
    {
        aux = &(*aux)->siguiente;
    }
    
    if (aux)
    {   
        Nodo* temp= *aux;                               //uso otro auxiliar
        *aux = (*aux)->siguiente;                       //enlazo para borrar
        free(temp);                                     //Libero memoria
    }
    
}

void buscarPorId(Nodo** startPend, Nodo** startReal, int ID){
    
    Nodo* buscarPend = *startPend;                      //Guardo auxiliares para recorrer
    Nodo* buscarReal = *startReal;
    int bandera = 0;                                    //Uso bandera, mas facil
    while (buscarPend != NULL && bandera == 0)
    {
        if (buscarPend->T.tareaID == ID)                //Basicamente si se encuentra la tarea, la muestra
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
        while (buscarReal != NULL && bandera ==0)           //Lo mismo pero en la otra lista y solo si en la primera lista no lo encontro
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
        if (strstr(buscarPend->T.Descripcion, frase))               //Funcion que me permite bsucar una subcadena en una cadena ya existente
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
    char *Buff =malloc(100*sizeof(char));   
    int seguir = 1;
    int IDBuscado;
    
    //Menu
    int opcion = 0;
    puts("Ingrese una opcion: ");
    puts("1_ Cargar tarea pendiente");
    puts("2_ Mostrar tareas pendientes");
    puts("3_ Marcar como realizada");
    puts("4_ Mostrar tareas realizadas");
    puts("5_ Buscar tarea por ID");
    puts("6_ Buscar tarea por palabra clave");
    puts("7_ Salir");
    fflush(stdin);
    scanf("%d", &opcion);
    while (opcion != 7)                                 //Mientras no seleccione salir
    {
        switch (opcion)
        {
        case 1:
                
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
        break;

        case 2:
            puts("Lista de pendientes:");
            mostrarLista(&startPendientes);
            puts("-----------");
        break;

        case 3:
            
            printf("\nSeleccionar el ID a mover: ");
            fflush(stdin);
            scanf("%d", &IDBuscado);
            Nodo auxiNodo =buscarTarea(&startPendientes, IDBuscado);
            quitarTarea(&startPendientes, IDBuscado);
            insertarNodo(&startRealizadas, &auxiNodo);
        break;

        case 4:
            puts("Lista de realizadas"); 
            mostrarLista(&startRealizadas);
            puts("------------");
        break;

        case 5:
            
            puts("Ingrese el ID a buscar: ");
            fflush(stdin);
            scanf("%d", &IDBuscado);
            buscarPorId(&startPendientes, &startRealizadas, IDBuscado);
        break;

        case 6:
            puts("Ingrese una palabra clave");
            fflush(stdin);
            gets(Buff);
            buscarPorPalabra(&startPendientes, &startRealizadas, Buff);
        break;

        case 7:
        break;
        }
        puts("Ingrese una opcion: ");
        puts("1_ Cargar tarea pendiente");
        puts("2_ Mostrar tareas pendientes");
        puts("3_ Marcar como realizada");
        puts("4_ Mostrar tareas realizadas");
        puts("5_ Buscar tarea por ID");
        puts("6_ Buscar tarea por palabra clave");
        puts("7_ Salir");
        fflush(stdin);
        scanf("%d", &opcion);
    }
    
    puts("FIN DEL PROGRAMA");
    
    
  
    

    return 0;
}
