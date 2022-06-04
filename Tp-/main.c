#include <stdio.h>
#import "Alumno.c"
#import "Utilidades.c"
#import "Materia.c"

void realizarOperacionSolicitada(int eleccionUsuario , ListaMaterias* listaDeMaterias , ListaDeAlumnos* listaDeAlumnos){
    ///TODO: Switch Case para cara opcion del Menu
    if(eleccionUsuario == 1){ ///Opcion Inscribir Alumno
        printf("Ingrese nombre del Alumno \n");
        char nombreIngresado[30];
        scanf("%s",&nombreIngresado);
        printf("%s\n",nombreIngresado);
        printf("Edad del Alumno? \n");
        int edadIngresada;
        scanf("%i",&edadIngresada);
        ///TODO: Validacion de edad y nombre que no sea vacio
        agregarAlumno(listaDeAlumnos,nombreIngresado,edadIngresada);
        printf("El alumno %s fue agregado con Numero de Registro: %li \n",nombreIngresado,listaDeAlumnos->cantidadAlumnos);
    }
    if(eleccionUsuario == 2){ ///Opcion Inscribir alumno a una materia
        int idAlumno = 0;
        printf("Id Del alumno que desea ingresar a una materia:\n");
        scanf("%i",&idAlumno);
        printf("Id de la Materia a la que desea inscribirlo:\n");
        int idMateria = 0;
        scanf("%i",&idMateria);
        ///TODO: Comprobar existencias de Alumno y Materia;
        AnotarseAMateria(listaDeMaterias,listaDeAlumnos,idMateria,idAlumno);
    }
    if(eleccionUsuario == 3){///Buscar Por rango de edad
        int edadMinima;
        int edadMaxima;
        printf("Indique El Rango de edad en el que desea Buscar\n");
        printf("Edad Minima");
        scanf("%i",&edadMinima);
        printf("edad Maxima");
        scanf("%i",&edadMaxima);
        MostrarAlumnosPorRangoDeEdad(listaDeAlumnos,edadMinima,edadMaxima);
    }
    if(eleccionUsuario == 5){///Rendir Materia
        printf("Id Del Alumno que desea ingresar la nota \n");
        long int idAlumno;
        scanf("%li",&idAlumno);
        ///TODO: Verificaciones
        Alumno* alumno = getAlumno(listaDeAlumnos,idAlumno);
        printearAlumno(alumno);
        if(puedeRendirMaterias(alumno) != 0){
            int idMateria;
            printf("Que Materia quiere rendir? \n");
            scanf("%i",&idMateria);
            CargarNota(alumno, getMateria(listaDeMaterias,idMateria));
        }
    }
}

void Menu(ListaMaterias* listaDeMaterias,ListaDeAlumnos* listaDeAlumnos){
    int eleccionUsuario = 1;
    while(eleccionUsuario != 0){
        printf("-------=============-------\n");
        printf("Bienvenido Al Sistema universitario de P.E.P.E, Personas Especialmente Para Estudiar \n");
        printf("----Que Opcion Desea Realizar?----\n");
        printf("1)Inscribir Alumno \n");
        printf("2)Inscribir Alumno a una Materia \n");
        printf("3)Mostrar Alumnos por rango de edad \n");
        printf("4)Buscar Alumno por nombre \n");
        printf("5)Ingresar Resultado de examen \n");
        printf("6)Ingresar Nueva Materia \n");
        printf("0)Salir\n");
        scanf("%i", &eleccionUsuario);
        realizarOperacionSolicitada(eleccionUsuario,listaDeMaterias,listaDeAlumnos);
    }
    ///TODO: Verificacion de que lo ingresado por el usuario este en el menu
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


    /// ACA ROMPE
    printearListaDeAlumnos(listaAlumnos);

    Menu(listaMaterias,listaAlumnos);

    printearListaDeMaterias(listaMaterias);

    /*
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
    */

    //printearListaDeMaterias(listaMaterias);

    //printf("%i \n", listaAlumnos->cabeza->listaDeHistorialDeMaterias->cabeza->nota);
    //printf("%s \n", listaAlumnos->cabeza->listaDeHistorialDeMaterias->cabeza->infoMateria->nombreMateria);
    //printf("%s \n", listaAlumnos->cabeza->siguiente->listaDeHistorialDeMaterias->cabeza->infoMateria->nombreMateria);

    return 0;

}
