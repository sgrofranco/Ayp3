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

    agregarAlumno(listaAlumnos,nombre,18);
    agregarAlumno(listaAlumnos,evilnombre,81);
    agregarMateriaAListaDeMaterias(listaMaterias, nombreMateria);

    AnotarseAMateria(listaMaterias,listaAlumnos,1,1);
    AnotarseAMateria(listaMaterias,listaAlumnos,1,1);
    AnotarseAMateria(listaMaterias,listaAlumnos,1,2);
    AnotarseAMateria(listaMaterias,listaAlumnos,1,2);

    printearListaDeAlumnos(listaAlumnos);
    printf("%s \n", listaAlumnos->cabeza->listaDeHistorialDeMaterias->cabeza->infoMateria->nombreMateria);
    printf("%s \n", listaAlumnos->cabeza->siguiente->listaDeHistorialDeMaterias->cabeza->infoMateria->nombreMateria);
    RendirMateria(listaAlumnos,listaMaterias,1,1);

    printf("%i \n", listaAlumnos->cabeza->listaDeHistorialDeMaterias->cabeza->nota);

    return 0;

}
