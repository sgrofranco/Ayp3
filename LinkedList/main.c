#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{
    int dato;
    struct Nodo* siguiente;
} Nodo;

typedef struct Lista{
    Nodo* cabeza;
} Lista;

Nodo* CrearNodo(int dato){
    Nodo* nodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nodo->siguiente = NULL;
    return nodo;
}

void DestruirNodo(Nodo* nodo){
    free(nodo);
}

void InsertarAlPrincipio(Lista* lista, int* entero){
    Nodo* nodo = CrearNodo(entero);
    nodo->siguiente = lista->cabeza;
    lista->cabeza = nodo;
}

void insertarAlFinal(Lista* lista, int* entero){
    Nodo* nodo = CrearNodo(entero);
    if (lista->cabeza == NULL){
        lista->cabeza = nodo;
    } else {
        Nodo* puntero = lista->cabeza;
        while (puntero->siguiente){
            puntero = puntero->siguiente;
        }
        puntero->siguiente=nodo;
    }

}


void printearLista (struct Nodo* n){

   while (n != NULL){
       printf("%i\n", n->dato);
       n = n->siguiente;
   }
}

int main() {

    struct Nodo* primero = NULL;
    struct Nodo* segundo = NULL;
    struct Nodo* tercero = NULL;

    primero = (struct Nodo*)malloc(sizeof(struct Nodo));
    segundo = (struct Nodo*)malloc(sizeof(struct Nodo));
    tercero = (struct Nodo*)malloc(sizeof(struct Nodo));

    primero->dato = 1;
    primero->siguiente = segundo;

    segundo->dato = 2;
    segundo->siguiente = tercero;

    tercero->dato = 3;
    tercero->siguiente = NULL;

    printearLista(primero);
    int pepe[] = {1,3,2,4,1,2,41,5,12,};
    printf("%i \n", sizeof(pepe)/sizeof(int));

    return 0;
}
