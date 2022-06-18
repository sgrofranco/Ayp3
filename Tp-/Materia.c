#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Materia{
    int idMateria;
    char nombreMateria[30];
    struct Materia* siguiente;
    struct Materia* arrayCorrelativas[5];
} Materia;

///PRE: if nota == Null esta anotado , if nota != Null Rindo bien; si rinde mal se borra.
typedef struct HistorialDeLaMateria{
    int nota;
    Materia* infoMateria;
    struct HistorialDeLaMateria* siguiente;
} HistorialDeLaMateria;

typedef struct ListaMaterias{
    int cantidadMaterias;
    Materia* cabeza;
}ListaMaterias;

typedef struct ListaDeHistorialDeMaterias{
    HistorialDeLaMateria* cabeza;
} ListaDeHistorialDeMaterias;

Materia* crearMateria(char nombre[]){
    Materia* nuevaMateria = (struct Materia*) malloc(sizeof (struct Materia));
    strcpy(nuevaMateria->nombreMateria, nombre);
    nuevaMateria->siguiente = NULL;
    for (int i = 0; i < 5; i++){
        nuevaMateria->arrayCorrelativas[i] = malloc(sizeof (struct Materia));
        nuevaMateria->arrayCorrelativas[i]->idMateria = 0;
    }
    return nuevaMateria;
}

ListaMaterias* inicializarListaMaterias(){
    ListaMaterias* listaMaterias = (struct ListaMaterias*)malloc(sizeof(struct ListaMaterias));
    listaMaterias->cabeza = NULL;
    listaMaterias->cantidadMaterias = 0;
    return listaMaterias;
}

Materia* getMateria(ListaMaterias* lista, int idMateriaABuscar){
    Materia* materia = lista->cabeza;
    while(idMateriaABuscar != materia->idMateria && materia->siguiente){
        materia = materia->siguiente;
    }
    if(idMateriaABuscar == materia->idMateria){
        return materia;
    }else{
        printf("No Existe Materia con esa Id \n");
    }
}

void printearNombreDeMaterias(Materia* arrayDeMaterias[]){
    for(int i = 0; i < 5 ; i++){
        if(arrayDeMaterias[i]->idMateria != 0){
            printf("%s \n" , arrayDeMaterias[i]->nombreMateria);
        }else{
            break;
        }
    }
}

void printearMateria(ListaMaterias* listaMaterias,int idMateria){
    Materia* materia = getMateria(listaMaterias,idMateria);
    printf("-----------------------\n");
    printf("Materia: %s \n",materia->nombreMateria );
    printf("ID de Materia: %i\n", materia->idMateria);
    printf("Lista de Correlativas: \n");
    printearNombreDeMaterias(materia->arrayCorrelativas);
}

void printearListaDeMaterias(ListaMaterias* lista){
    Materia* materia = lista->cabeza;
    printf("-----LISTA DE MATERIAS----\n");
    do{
        printearMateria(lista,materia->idMateria);
        materia = materia->siguiente;
    } while (materia != NULL);
    printf("\n-----==============----\n");
}

void AsignarCorrelativas(ListaMaterias* lista , Materia* materia){
    int eleccion = 0;
    printf("¿Esta Posee alguna correlativa? 1-Si 0-No \n");

    scanf("%i",&eleccion);
    if(eleccion == 1){
        int contadorCorrelativas = 0;
        while (eleccion != 0 && contadorCorrelativas<5){
            printearListaDeMaterias(lista);
            printf("Ingrese la ID de la correlativa que desea agregar?: \n");
            printf("(Ingrese 0 para dejar de agregar correlativas) \n");

            scanf("%i",&eleccion);

            int yaEsCorrelatva = 0;
            int i = 0;
            while (materia->arrayCorrelativas[i]->idMateria != 0){
                if (materia->idMateria == eleccion){
                    printf("Una materia no puede ser correlativa de ella misma\n");
                    yaEsCorrelatva++;
                }
                if (materia->arrayCorrelativas[i]->idMateria == eleccion){
                    printf("Esa materia ya es correlativa\n");
                    yaEsCorrelatva++;
                }
                i++;
            }
            if(eleccion != 0 && (eleccion > 0 && eleccion < lista->cantidadMaterias) && yaEsCorrelatva == 0){
                materia->arrayCorrelativas[i] = getMateria(lista, eleccion);
                contadorCorrelativas++;
            } else if (eleccion != 0){
                printf("Ingrese una ID valida\n");
            }
        }
        if (contadorCorrelativas == 5){
            printf("Se alcanzo el maximo de correlativas posibles\n");
        }
    }
}


void agregarMateriaAListaDeMaterias(ListaMaterias* lista , char nombre[]){
    if(lista->cabeza == NULL){
        lista->cantidadMaterias++;
        Materia* nuevaMateria = crearMateria(nombre);
        nuevaMateria->idMateria = lista->cantidadMaterias;
        lista->cabeza = nuevaMateria;
    }else{
        Materia* materia = lista->cabeza;
        while(materia->siguiente){
            materia = materia->siguiente;
        }
        lista->cantidadMaterias++;
        Materia* nuevaMateria = crearMateria(nombre);
        nuevaMateria->idMateria = lista->cantidadMaterias;
        materia->siguiente = nuevaMateria;
        AsignarCorrelativas(lista,nuevaMateria);
        printf("se agrego la materia %s , con ID: %i \n",nuevaMateria->nombreMateria,nuevaMateria->idMateria);
    }
}

void agregarMateriaAListaDeMateriasSinCorrelativas(ListaMaterias* lista , char nombre[]){
    if(lista->cabeza == NULL){
        lista->cantidadMaterias++;
        Materia* nuevaMateria = crearMateria(nombre);
        nuevaMateria->idMateria = lista->cantidadMaterias;
        lista->cabeza = nuevaMateria;
    }else{
        Materia* materia = lista->cabeza;
        while(materia->siguiente){
            materia = materia->siguiente;
        }
        lista->cantidadMaterias++;
        Materia* nuevaMateria = crearMateria(nombre);
        nuevaMateria->idMateria = lista->cantidadMaterias;
        materia->siguiente = nuevaMateria;
    }
}


HistorialDeLaMateria* CrearHsitorialDeLaMaateria(Materia* materia){
    HistorialDeLaMateria* historialDeLaMateria = (struct HistorialDeLaMateria*) malloc (sizeof (struct HistorialDeLaMateria));
    historialDeLaMateria->nota = NULL;
    historialDeLaMateria->infoMateria = materia;
    historialDeLaMateria->siguiente = NULL;
    return historialDeLaMateria;
}

void destruirHistorialMateria(ListaDeHistorialDeMaterias* listaDeHistorialDeMaterias,int idAeliminar){
    if(listaDeHistorialDeMaterias->cabeza->infoMateria->idMateria == idAeliminar){
        HistorialDeLaMateria* HistorialAEliminar = listaDeHistorialDeMaterias->cabeza;
        listaDeHistorialDeMaterias->cabeza = HistorialAEliminar->siguiente;
        free(HistorialAEliminar);
    }else{
        HistorialDeLaMateria* historialDelaMateria = listaDeHistorialDeMaterias->cabeza;
        while(historialDelaMateria->siguiente->infoMateria->idMateria != idAeliminar){
            historialDelaMateria = historialDelaMateria->siguiente;
        }
        HistorialDeLaMateria* historialAElminiar = historialDelaMateria->siguiente;
        if(historialAElminiar->siguiente){
            historialDelaMateria->siguiente = historialAElminiar->siguiente;
        }else{
            historialDelaMateria->siguiente = NULL;
        }
        free(historialAElminiar);
    }
}
