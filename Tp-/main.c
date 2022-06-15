#include <stdio.h>
#import "Alumno.c"
#import "Utilidades.c"
#import "Materia.c"

void realizarOperacionSolicitada(int eleccionUsuario , ListaMaterias* listaDeMaterias , ListaDeAlumnos* listaDeAlumnos){
    ///TODO: Switch Case para cara opcion del Menu
    if(eleccionUsuario == 1){ ///Opcion Inscribir Alumno
        printf("Ingrese nombre del Alumno \n");
        char nombreIngresado[30] = {0};
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
    if(eleccionUsuario == 4){///Buscar Por Nombre
        char nombreABuscar[30];
        printf("que nombre desea buscar en los alumnos? \n");
        printf("(INGRESE EL NOMBRE EXACTO A COMO ESTA REGISTRADO)\n");
        scanf("%s",&nombreABuscar);
        /*for(int i = 0; nombreABuscar[i]; i++){///Cambia el string ingresado a Lowcase
            nombreABuscar[i] = tolower(nombreABuscar[i]);
        }
        printf("LOWCASE: %s \n",nombreABuscar);*/
        buscarAlumnoPorNombre(listaDeAlumnos,nombreABuscar);
    }
    if(eleccionUsuario == 5){///Promedio de alumno
        long int idAlumnoABuscar;
        printf("ID del alumno que desea obtener el promedio: \n");
        scanf("%li",&idAlumnoABuscar);
        getPromedioAlumno(listaDeAlumnos,idAlumnoABuscar);
    }
    if(eleccionUsuario == 6){///Rendir Materia
        printf("Id Del Alumno que desea ingresar la nota \n");
        long int idAlumno;
        scanf("%li",&idAlumno);
        if(idAlumno > 0 && idAlumno <= listaDeAlumnos->cantidadAlumnos){
            Alumno* alumno = getAlumno(listaDeAlumnos,idAlumno);
            printearAlumno(alumno);
            if(puedeRendirMaterias(alumno) != 0){
                int idMateria;
                printf("Que Materia quiere rendir? \n");
                scanf("%i",&idMateria);
                CargarNota(alumno, getMateria(listaDeMaterias,idMateria));
            }
        } else{
            printf("No existe Alumno con esa ID , pruebe entre 1 y %i \n",listaDeAlumnos->cantidadAlumnos);
        }
    }
    if(eleccionUsuario == 7){///Ingresar nueva materia
        printf("Nombre de la materia que desea ingresar \n");
        char nombreMateria[30];
        scanf("%s",&nombreMateria);
        agregarMateriaAListaDeMaterias(listaDeMaterias,nombreMateria);
    }
    if(eleccionUsuario == 8){///Buscar por id hacerlo mas lindo y con las validaciones
        int eleccionDeBuscador = 2;
        int ID = 0;
        printf("Opcion 1-Materias , Opcion 2-Alumnos \n");
        do{
            if(eleccionDeBuscador != 1 && eleccionDeBuscador != 2){
                printf("Opcion No Valida 1-Materias , 2-Alumnos , vuelva a ingresar la opcion \n");
            }
            scanf("%i",&eleccionDeBuscador);
        }while(eleccionDeBuscador < 1 || eleccionDeBuscador > 2);
        printf("Que ID desea Buscar? \n");
        scanf("%i",&ID);
        if(eleccionDeBuscador == 1){
            if(ID > 0 && ID <= listaDeMaterias->cantidadMaterias){
                printearMateria(listaDeMaterias,ID);
            }else{
                printf("No existe Materia con esa ID, tiene que ser entre 1 y %i \n",listaDeMaterias->cantidadMaterias);
            }
        }
        if(eleccionDeBuscador == 2){
            if(ID > 0 && ID <= listaDeAlumnos->cantidadAlumnos){
                printearAlumno(getAlumno(listaDeAlumnos,ID));
            } else{
                printf("No existe Alumno con es ID , tiene que ser entre 1 y %i \n",listaDeAlumnos->cantidadAlumnos);
            }
        }
    }
    if(eleccionUsuario == 99){ /// TODO: DEJAR ESO PARA DEMOSTRAR LA CARGA MASIVA DE ALUMNOS Y OTROS METODOS PARA LOS PUNTOS OPCIONALES
        int eleccionDesarrollador;
        printf("Modo desarrollador \n");
        printf("1)generar 100 alumnos aleatorios \n");
        printf("2)generar 100 materias aleatorias \n");
        printf("3)printear Lista Alumnos \n");
        printf("4)printear Lista Materias \n");
        scanf("%i",&eleccionDesarrollador);
        if(eleccionDesarrollador == 1){
            int maximaCantidad = 0;
            printf("Cantidad de alumnos a crear\n");
            scanf("%i",&maximaCantidad);
            generarAlumnosAleatorios(listaDeAlumnos, maximaCantidad);}
        if(eleccionDesarrollador == 2){
            int maximaCantidad2 = 0;
            printf("Cantidad de materias a crear\n");
            scanf("%i",&maximaCantidad2);
            generarMateriasAleatorias(listaDeMaterias,maximaCantidad2);}
        if(eleccionDesarrollador == 3){ printearListaDeAlumnos(listaDeAlumnos);}
        if(eleccionDesarrollador == 4){ printearListaDeMaterias(listaDeMaterias);}
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
        printf("5)Mostrar Promedio del alumno \n");
        printf("6)Ingresar Resultado de examen \n");
        printf("7)Ingresar Nueva Materia \n");
        printf("8)Mostrar Alumno o Materia por ID\n");
        printf("0)Salir\n");
        printf("99)Modo Desarrollador \n");
        scanf("%i", &eleccionUsuario);
        realizarOperacionSolicitada(eleccionUsuario,listaDeMaterias,listaDeAlumnos);
    }
    guardarEnBdd(listaDeMaterias,listaDeAlumnos);
}


int main() {
    ListaMaterias* listaMaterias = inicializarListaMaterias();
    ListaDeAlumnos* listaAlumnos = inicializarListaAlumnos();
    InicializarBdd(listaAlumnos,listaMaterias);
    Menu(listaMaterias,listaAlumnos);
    return 0;
}
