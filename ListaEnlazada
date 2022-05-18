#include <stdio.h>
#include <stdlib.h>

struct Nodo{
    int dato;
    struct Nodo* siguiente;
};

int main() {

    struct Nodo* primero = NULL;
    struct Nodo* segundo = NULL;
    struct Nodo* tercero = NULL;

    primero = (struct Nodo*)malloc(sizeof(struct Nodo));
    segundo = (struct Nodo*)malloc(sizeof(struct Nodo));
    tercero = (struct Nodo*)malloc(sizeof(struct Nodo));

    primero->dato = 1;
    primero->siguiente = segundo;

    segundo->dato = 6;
    segundo->siguiente = tercero;

    tercero->data = 4;
    tercero->siguiente = NULL;

    printf("Hello, World!\n");
    return 0;
}
