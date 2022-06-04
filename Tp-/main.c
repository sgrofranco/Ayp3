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





int main() {
    ListaMaterias* listaMaterias = inicializarListaMaterias();
    ListaDeAlumnos* listaAlumnos = inicializarListaAlumnos();
    char nombre[] = "pepe";
    char nombreMateria[] = "pepe en ayp3";
    char evilnombre[] = "EvilPepe";
    char nombre2[] = "MateriaDeMierda";
    char evilMateria[] = "pya4 ne epep";
    agregarAlumno(listaAlumnos,nombre,18);
    agregarAlumno(listaAlumnos,evilnombre,81);
    agregarMateriaAListaDeMaterias(listaMaterias, nombreMateria);
    agregarMateriaAListaDeMaterias(listaMaterias, nombre2);
    agregarMateriaAListaDeMaterias(listaMaterias, evilMateria);


    printearListaDeAlumnos(listaAlumnos);
    printearListaDeMaterias(listaMaterias);

    AnotarseAMateria(listaMaterias,listaAlumnos,1,1);
    AnotarseAMateria(listaMaterias,listaAlumnos,1,1);
    AnotarseAMateria(listaMaterias,listaAlumnos,1,2);
    AnotarseAMateria(listaMaterias,listaAlumnos,1,2);

    AnotarseAMateria(listaMaterias,listaAlumnos,2,2);
    AnotarseAMateria(listaMaterias,listaAlumnos,2,2);


    RendirMateria(listaAlumnos,listaMaterias,1,1);
    RendirMateria(listaAlumnos,listaMaterias,1,1);
    ///TODO:ARREGLAR ESTO ( Maximo de correlativas)
    printf("Materia Correlativa: %s \n", listaMaterias->cabeza->siguiente->siguiente->arrayCorrelativas[0]->nombreMateria);
    printf("Materia Correlativa: %s \n", listaMaterias->cabeza->siguiente->siguiente->arrayCorrelativas[1]->nombreMateria);

    //printf("%i \n", listaAlumnos->cabeza->listaDeHistorialDeMaterias->cabeza->nota);
    //printf("%s \n", listaAlumnos->cabeza->listaDeHistorialDeMaterias->cabeza->infoMateria->nombreMateria);
    //printf("%s \n", listaAlumnos->cabeza->siguiente->listaDeHistorialDeMaterias->cabeza->infoMateria->nombreMateria);

    return 0;

}
