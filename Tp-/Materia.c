#include <stdio.h>
#include <stdlib.h>

typedef struct Materia{
    int idMateria;
    char *nombreMateria;
    struct Materia* siguiente;
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
    nuevaMateria->nombreMateria = nombre;
    return nuevaMateria;
};

ListaMaterias* inicializarListaMaterias(){
    ListaMaterias* listaMaterias = (struct ListaMaterias*)malloc(sizeof(struct ListaMaterias));
    listaMaterias->cabeza = NULL;
    listaMaterias->cantidadMaterias = 0;
    return listaMaterias;
}

void agregarMateriaAListaDeMaterias(ListaMaterias* lista , char nombre[]){
    if(lista->cabeza == NULL){
        lista->cantidadMaterias++;
        Materia* nuevaMateria = crearMateria(nombre);
        nuevaMateria->idMateria = lista->cantidadMaterias;
        lista->cabeza = nuevaMateria;
    }else{
        printf("profe te lo corrijo en la prioxima semana \n att la banda de los millones \n");
    }
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

HistorialDeLaMateria* CrearHsitorialDeLaMaateria(Materia* materia){
    HistorialDeLaMateria* historialDeLaMateria = (struct HistorialDeLaMateria*) malloc (sizeof (struct HistorialDeLaMateria));
    historialDeLaMateria->nota = NULL;
    historialDeLaMateria->infoMateria = materia;
    historialDeLaMateria->siguiente = NULL;
    return historialDeLaMateria;
}
