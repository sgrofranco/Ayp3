#include <stdio.h>
#include <stdlib.h>
#import "Alumno.c"
#import "Materia.c"

void Menu(){
    int eleccionUsuario = 1;
    while(eleccionUsuario != 0){
        printf("-------=============-------\n");
        printf("Bienvenido Al Sistema universitario de P.E.P.E, Personas Especialmente Para Estudiar \n");
        printf("----Que Opcion Desea Realizar?----\n");
        printf("1)Inscribir Alumno \n");
        printf("2)Inscribir Alumno a una Materia \n");
        printf("3)Mostrar Alumnos por rango de edad \n");
        printf("4)Buscar Alumno por nombre \n");
        printf("4)Ingresar Resultado de examen \n");
        printf("5)Ingresar Nueva Materia \n");
        printf("0)Salir\n");
        scanf("%i", &eleccionUsuario);
    }
    ///TODO: Verificacion de que lo ingresado por el usuario este en el menu
}


void realizarOperacionSolicitada(int eleccionUsuario){
    ///TODO: Switch Case para cara opcion del Menu
    if(eleccionUsuario == 1){ ///Opcion Inscribir Alumno
        printf("");
    }
}

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
    agregarMateriaAListaDeMaterias(listaMaterias, "Materia de Langdom");



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
    printf("Materia Correlativa: %s \n", listaMaterias->cabeza->siguiente->siguiente->arrayCorrelativas[2]->nombreMateria);
    printf("Materia Correlativa: %s \n", listaMaterias->cabeza->siguiente->siguiente->arrayCorrelativas[3]->nombreMateria);
    printf("Materia Correlativa: %s \n", listaMaterias->cabeza->siguiente->siguiente->arrayCorrelativas[4]->nombreMateria);

    printearListaDeMaterias(listaMaterias);

    //printf("%i \n", listaAlumnos->cabeza->listaDeHistorialDeMaterias->cabeza->nota);
    //printf("%s \n", listaAlumnos->cabeza->listaDeHistorialDeMaterias->cabeza->infoMateria->nombreMateria);
    //printf("%s \n", listaAlumnos->cabeza->siguiente->listaDeHistorialDeMaterias->cabeza->infoMateria->nombreMateria);

    return 0;

}
