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

void InsertarAlPrincipio(Lista* lista, Nodo* nodo){
    nodo->siguiente = lista->cabeza;
    lista->cabeza = nodo;
    lista->largo++;
}

void DestruirNodo(Nodo* nodo){
    free(nodo);
}

void insertarNodo(Nodo* puntero,Nodo* nuevoNodo){
    if(puntero->siguiente){
        if(puntero->siguiente->dato < nuevoNodo->dato){
            puntero = puntero->siguiente;
            puntero->siguiente = nuevoNodo;
        }else{
            nuevoNodo->siguiente = puntero->siguiente;
        }
    }
    puntero->siguiente = nuevoNodo;
}

void printearLista (struct Nodo* n){
    printf("[");
    while (n != NULL){
        printf("%i,", n->dato);
        n = n->siguiente;
    }
    printf("]\n");
}

int insertarOrdenado(int valor ,Lista* lista){
    Nodo* nodo = CrearNodo(valor);
    if(lista->cabeza == NULL){
        lista->cabeza = nodo;
    }else{
        Nodo* puntero = lista->cabeza;
        if(puntero->dato >= valor){
            InsertarAlPrincipio(lista , nodo);
        }else if(!puntero->siguiente){
            insertarNodo(puntero,nodo);
            lista->largo++;
        }else{
            for(int i = 0; i <= lista->largo-1 ; i++){
                if(puntero->siguiente->dato > valor){
                    insertarNodo(puntero,nodo);
                    lista->largo++;
                    i = lista->largo +2;
                }else if(i==lista->largo-1){
                    insertarNodo(puntero,nodo);
                    lista->largo++;
                    i= lista->largo +2;
                }
                puntero = puntero->siguiente;

            }
        }
    }
}

Lista* InicializarLista(int array[], int largoDelArray){
    Lista* lista = (struct Lista*)malloc(sizeof(struct Lista));
    lista->cabeza = NULL;
    lista->largo = 0;
    for(int i = 0; i < largoDelArray; i++){
        insertarOrdenado(array[i],lista);
    }
    return lista;
}

Nodo* ObtenerNodo(int entero, Lista* lista){
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
            return puntero;
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
    return lista->largo +1;
}

int main() {

    int valoresLista[] = {1, 3, 2, 4, 1, 2, 41, 5, 12};
    Lista* linkedList = InicializarLista(valoresLista, sizeof (valoresLista) / sizeof valoresLista[0]);

    int eleccionUsuario = 1;
    int valorIngresado = NULL;

    // Menu De Usuario
    while (eleccionUsuario != 0){
        valorIngresado=NULL;
        printf("-------Menu------ \n");
        printf("elija la accion que quiera realizar \n");
        printf("1- aniadir elemento a la lista \n");
        printf("2- eliminar elemento de la lista \n");
        printf("3- obtener elemento \n");
        printf("4- Mostrar Lista \n");
        printf("5- Largo de la Lista \n");
        printf("0- salir del sistema\n");
        printf("que accion quiere realizar?\n");
        scanf("%i", &eleccionUsuario);
        switch (eleccionUsuario){
            //Switch Case con la opcion elegida por el Usuario
            case 1:
                printf("Que Elemento desea agregar a la lista? \n");
                scanf("%i",&valorIngresado);
                insertarOrdenado(valorIngresado,linkedList);
                break;
            case 2:
                printf("Que Elemento desea eliminar de la lista? \n");
                scanf("%i",&valorIngresado);
                while(valorIngresado -1 < 1 || valorIngresado > linkedList->largo){
                    printf("Elemento invalido , este pertenece a una posicion no existente en la lista \n");
                    scanf("%i",&valorIngresado);
                }
                EliminarElemento(valorIngresado-1,linkedList);
                break;
            case 3:
                printf("De Que elemento desea obtener el valor? \n");
                scanf("%i",&valorIngresado);
                while(valorIngresado -1 < 1 || valorIngresado > linkedList->largo){
                    printf("Elemento invalido , este pertenece a una posicion no existente en la lista \n");
                    scanf("%i",&valorIngresado);
                }
                printf("El Valor de ese elemento es: %i \n", ObtenerNodo(valorIngresado-1,linkedList)->dato);
                break;
            case 4:
                printearLista(linkedList->cabeza);
                break;
            case 5:
                printf("El Largo de la Lista es: %i \n",linkedList->largo);
                break;
            case 0:
                printf("Hasta la Proxima \n");
                break;
            default: //esto ocurre unicamente cuando el usuario pone una opcion invalida;
                printf("La Opcion elegida no existe, Vuelva a elegir nuevamente \n");
                break;
        }
    }


    /*printf("creacion lista: \n");
    printearLista(linkedList->cabeza);
    printf("El LARGO FINAL ES: %i\n",LargoDeLista(linkedList));
    EliminarElemento(3,linkedList);
    printf("Post Eliminar Elemento: \n");
    printearLista(linkedList->cabeza);
    printf("El ObtenerNodo da: %i \n", ObtenerNodo(4, linkedList)->dato);
    printf("El LARGO FINAL ES: %i\n",LargoDeLista(linkedList));
    printearLista(linkedList->cabeza);*/


    return 0;
}
