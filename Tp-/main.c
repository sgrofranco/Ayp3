#include <stdio.h>
#include <stdlib.h>
#import "Alumno.c"
#import "Materia.c"

///---------------------------------------------------------
/// Esto Unicamente funciona para que cada materia tenga como maximo 2 roots

typedef struct RootMateria{
    Materia* materia;
    struct RootMateria* materiaIzquierda;
    struct RootMateria* materiaDerecha;

}RootMateria;

typedef struct Arbol{
    RootMateria* cabeza;
}Arbol;



///---------------------------------------------------------

ListaMaterias* inicializarListaMaterias(){
    ListaMaterias* listaMaterias = (struct ListaMaterias*)malloc(sizeof(struct ListaMaterias));
    listaMaterias->cabeza = NULL;
    listaMaterias->cantidadMaterias = 0;
    return listaMaterias;
}

ListaAlumnos* inicializarListaAlumnos(){
    ListaAlumnos* listaAlumnos = (struct ListaAlumnos*) malloc(sizeof (struct ListaAlumnos));
    listaAlumnos->cantidadAlumnos = 0;
    listaAlumnos->cabeza = NULL;
    return listaAlumnos;
}

Materia* crearMateria(char nombre[]){

    Materia* nuevaMateria = (struct Materia*) malloc(sizeof (struct Materia));
    nuevaMateria->nombreMateria = nombre;
    return nuevaMateria;
};

void agregarMateria(ListaMaterias* lista , char nombre[]){
    if(lista->cabeza == NULL){
        lista->cantidadMaterias++;
        Materia* nuevaMateria = crearMateria(nombre);
        nuevaMateria->idMateria = lista->cantidadMaterias;
        lista->cabeza = nuevaMateria;
    }else{
        printf("profe te lo corrijo en la prioxima semana \n att la banda de los millones \n");
    }
}

void agregarMateriaAAlumno(Alumno* alumno,Materia* matra){

}

int main() {
    ListaMaterias* listaMaterias = inicializarListaMaterias();
    ListaAlumnos* listaAlumnos = inicializarListaAlumnos();
    char nombre[] = "pepe";
    char nombreMateria[] = "pepe en ayp3";
    agregarAlumno(listaAlumnos,nombre,18);
    agregarMateria(listaMaterias,nombreMateria);


    char evilnombre[] = "EvilPepe";
    agregarAlumno(listaAlumnos,evilnombre,81);
    printearLista(listaAlumnos);
    return 0;

}
