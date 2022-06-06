#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * SETUP:
 *  Settings:
 *      1) Una materia no puede tener mas de 5 correlativas;
 */
typedef struct Materia{
    int idMateria;
    char nombreMateria[30];
    struct Materia* siguiente;
    struct Materia* arrayCorrelativas[5];
} Materia;

typedef struct HistorialDeLaMateria{
    int nota; // if nota == Null esta anotado , if nota != Null Rindo bien; si rinde mal se borra.
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
    printf("materia: %s \n",nombre);
    printf("materia: %s \n",nuevaMateria->nombreMateria);
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

//TODO: HACER ESTO MAS LINDO
void printearListaDeMaterias(ListaMaterias* lista){
    Materia* materia = lista->cabeza;
    printf("-----LISTA DE MATERIAS----\n");
    do{
        printf("--------------\n");
        printf("Materia: %s \n",materia->nombreMateria );
        printf("ID de Materia: %i\n", materia->idMateria);
        printf("Lista de Correlativas: \n");
        printearNombreDeMaterias(materia->arrayCorrelativas);
        materia = materia->siguiente;
    } while (materia != NULL);
    printf("\n-----==============----\n");
}

/// TODO: TAMPOCO QUE PUEDAN EXISTIR CORRELATIVAS CIRCULARES
void AsignarCorrelativas(ListaMaterias* lista , Materia* materia){
    int eleccionUsuario = 0;
    printf("¿Esta Posee alguna correlativa? 1-Si 0-No \n");

    scanf("%i",&eleccionUsuario);
    if(eleccionUsuario == 1){
        while (eleccionUsuario != 0){
            printearListaDeMaterias(lista);
            printf("Que Correlativa desea agregar?: \n");
            printf("(Ingrese 0 para dejar de agregar correlativas) \n");

            scanf("%i",&eleccionUsuario);
            int i = 0;
            while (materia->arrayCorrelativas[i]->idMateria != 0){
                i++;
            }
            if(eleccionUsuario != 0){
                materia->arrayCorrelativas[i] = getMateria(lista, eleccionUsuario);
            }
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
    }
}


HistorialDeLaMateria* CrearHsitorialDeLaMaateria(Materia* materia){
    HistorialDeLaMateria* historialDeLaMateria = (struct HistorialDeLaMateria*) malloc (sizeof (struct HistorialDeLaMateria));
    historialDeLaMateria->nota = NULL;
    historialDeLaMateria->infoMateria = materia;
    historialDeLaMateria->siguiente = NULL;
    return historialDeLaMateria;
}

void destruirHistorialMateria(HistorialDeLaMateria* historialDeLaMateria){
    free(historialDeLaMateria);
}
