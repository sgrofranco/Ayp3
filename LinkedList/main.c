#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{
    int dato;
    struct Nodo* siguiente;
} Nodo;

typedef struct Lista{
    Nodo* cabeza;
    int largo;
} Lista;

Nodo* CrearNodo(int dato){
    Nodo* nodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nodo->siguiente = NULL;
    nodo->dato = dato;;
    return nodo;
}


void DestruirNodo(Nodo* nodo){
    free(nodo);
}

void PrintearNodo(Nodo* nodo){
    printf("%i\n", nodo->dato);
}

void InsertarAlPrincipio(Lista* lista, int* entero){
    Nodo* nodo = CrearNodo(entero);
    nodo->siguiente = lista->cabeza;
    lista->cabeza = nodo;
    lista->largo++;
}

void InsertarAlFinal(Lista* lista, int* entero){
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
    lista->largo++;
}

Lista* InicializarLista(int array[], int largoDelArray){
    Lista* lista = (struct Lista*)malloc(sizeof(struct Lista));
    lista->cabeza = NULL;
    lista->largo = 0;
    for(int i = 0; i < largoDelArray; i++){
        InsertarAlFinal(lista,array[i]);
    }
    return lista;
}


void printearLista (struct Nodo* n){

   while (n != NULL){
       printf("%i\n", n->dato);
       n = n->siguiente;
   }
}

int Obtener(int entero, Lista* lista){
    if(lista->cabeza == NULL){
        return NULL;
    } else {
        Nodo* puntero = lista->cabeza;
        int posicion = 0;
        while (posicion < entero && puntero->siguiente){
            puntero = puntero->siguiente;
            posicion++;
        }
        if (posicion != entero){
            return NULL;
        } else {
            return puntero->dato;
        }
    }
}

void EliminarElemento(int posicion, Lista* lista){
    if (lista->cabeza){
        if (posicion==0) {
            Nodo *eliminado = lista->cabeza;
            lista->cabeza = lista->cabeza->siguiente;
            DestruirNodo(eliminado);
            lista->largo--;
        } else if (posicion < lista->largo){
            Nodo* puntero = lista->cabeza;
            int posicionActual =0;
            while (posicionActual < (posicion-1) && puntero->siguiente){
                puntero = puntero->siguiente;
                PrintearNodo(puntero);
                posicionActual++;
            }
            Nodo* eliminado = puntero->siguiente;
            puntero->siguiente = eliminado->siguiente;
            DestruirNodo(eliminado);
            lista->largo--;
        }
    }
}

int LargoDeLista(Lista* lista){
    return lista->largo;
}

Lista OrdenarLista(Lista* lista){

    int minimo = 0;
    Nodo* Auxiliar = CrearNodo(0);

    for (int i = 0; i < lista->largo; i++){

        minimo=i;

        for(int j = 0; j < lista->largo-i; j++){
            if(Obtener(j, lista)< Obtener(minimo, lista)){
                minimo=j;
            }
        }
        Auxiliar = 
    }


}

int main() {

    int pepe[] = {1,3,2,4,1,2,41,5,12};
    Lista* pepelista = InicializarLista(pepe, sizeof (pepe)/sizeof pepe[0]);
    printearLista(pepelista->cabeza);
    printf("El LARGO FINAL ES: %i\n",LargoDeLista(pepelista));
    EliminarElemento(3,pepelista);
    printearLista(pepelista->cabeza);
    printf("El LARGO FINAL ES: %i\n",LargoDeLista(pepelista));

    return 0;
}


