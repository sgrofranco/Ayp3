#include <stdio.h>
#import "Alumno.c"
#import "Utilidades.c"
#import "Materia.c"

/*
 * SETUP:
 *  Settings:
 *      1) Una materia no puede tener mas de 5 correlativas;
 *      2) Toda Materia se aprueba con 4
 *      3) Cuando Un Alumno se anota a una materia , la nota existe pero es NULL
 *      4) Cuando Un Alumno Rinde se registra en el HistorialDeLaMateria
 *      4.1) Si el Alumno aprueba se guarda la nota del examen
 *      4.2) Si el Alumno Desaprueba se elimina del historial y es Des-anotado de la materia
 *      5) Un Alumno no puede anotarse a una Materia si no tiene todas sus correlativas aprobadas
 *      6) La carga de Base de datos se Inicia antes de llamar al menu
 *      7) El guardado de la Base de datos de realiza cuando el usuario sale del Menu
 *      8) Lo ingresado no debe de estar separado por Espacios ya que el scanf no los soporta
 *      9) Para entrar en el Modo desarrollador usar la opcion "99"
 */

void realizarOperacionSolicitada(int eleccionUsuario , ListaMaterias* listaDeMaterias , ListaDeAlumnos* listaDeAlumnos){
    if(eleccionUsuario == 1){ ///Opcion Inscribir Alumno
        printf("Ingrese nombre del Alumno \n");
        char nombreIngresado[30] = {0};
        scanf("%s",&nombreIngresado);
        if(esUnChar(nombreIngresado) == 1){
            printf("Edad del Alumno? \n");
            char edadIngresada[4]={0};
            int edadFinal;
            scanf("%s",&edadIngresada);
            edadFinal = verificadorDeValorIngresado(edadIngresada);
            if(edadFinal != -1){
                agregarAlumno(listaDeAlumnos,nombreIngresado,edadFinal);
                printf("El alumno %s fue agregado con Numero de Registro: %li \n",nombreIngresado,listaDeAlumnos->cantidadAlumnos);
            }else{
                printf("la edad ingresada no es valida \n");
            }
        }else{
            printf("Nombre ingresado no es valido \n");
        }
    }
    if(eleccionUsuario == 2){ ///Opcion Inscribir alumno a una materia
        int idAlumno = 0;
        printf("Id Del alumno que desea ingresar a una materia:\n");
        scanf("%i",&idAlumno);
        printf("Id de la Materia a la que desea inscribirlo:\n");
        int idMateria = 0;
        scanf("%i",&idMateria);
        if((idAlumno > 0 && idAlumno <= listaDeAlumnos->cantidadAlumnos) && (idMateria > 0 && idMateria <= listaDeMaterias->cantidadMaterias)){
            AnotarseAMateria(listaDeMaterias,listaDeAlumnos,idMateria,idAlumno);
        } else{
            printf("valores Ingresados invalidos \n");
        }
    }
    if(eleccionUsuario == 3){///Buscar Por rango de edad
        int edadMinima;
        int edadMaxima;
        printf("Indique El Rango de edad en el que desea Buscar\n");
        printf("Edad Minima");
        scanf("%i",&edadMinima);
        printf("edad Maxima");
        scanf("%i",&edadMaxima);
        if(edadMinima <= edadMaxima && (edadMaxima > 0 && edadMinima >0)){
            MostrarAlumnosPorRangoDeEdad(listaDeAlumnos,edadMinima,edadMaxima);
        }else{
            printf("valores Ingresados Invalidos \n");
        }
    }
    if(eleccionUsuario == 4){///Buscar Por Nombre
        char nombreABuscar[30];
        printf("que nombre desea buscar en los alumnos? \n");
        printf("(INGRESE EL NOMBRE EXACTO A COMO ESTA REGISTRADO)\n");
        scanf("%s",&nombreABuscar);
        buscarAlumnoPorNombre(listaDeAlumnos,nombreABuscar);
    }
    if(eleccionUsuario == 5){///Promedio de alumno
        long int idAlumnoABuscar;
        printf("ID del alumno que desea obtener el promedio: \n");
        scanf("%li",&idAlumnoABuscar);
        if(idAlumnoABuscar > 0 && idAlumnoABuscar <= listaDeAlumnos->cantidadAlumnos){
            getPromedioAlumno(listaDeAlumnos,idAlumnoABuscar);
        }else{
            printf("No existe Alumno con esa ID \n");
        }
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
                printf("No existe Alumno con esa ID , tiene que ser entre 1 y %i \n",listaDeAlumnos->cantidadAlumnos);
            }
        }
    }
    if(eleccionUsuario == 9){ pagiandoDeAlumnos(listaDeAlumnos); }
    if(eleccionUsuario == 10){ pagiandoDeMaterias(listaDeMaterias);}
    if(eleccionUsuario == 99){
        int eleccionDesarrollador;
        printf("Modo desarrollador \n");
        printf("1)generar alumnos aleatorios \n");
        printf("2)generar materias aleatorias \n");
        printf("3)printear Lista Alumnos \n");
        printf("4)printear Lista Materias \n");
        scanf("%i",&eleccionDesarrollador);
        if(eleccionDesarrollador == 1){
            int maximaCantidad = 0;
            printf("Cantidad de alumnos a crear\n");
            scanf("%i",&maximaCantidad);
            printf("Desea ver los nombres de las Materias mientras se crea? 0)No 1)Si\n");
            int printear = 0;
            scanf("%i",&printear);
            if(!(printear == 0 || printear == 1)){
                printf("Opcion elegida erronea , por lo tanto entrara en modo default y no los mostrara \n");
            }
            if(maximaCantidad >= 1){
                generarAlumnosAleatorios(listaDeAlumnos, maximaCantidad,printear);
            }else{
                printf("El valor ingresado no puede ser menor a 1 y las opciones 0 o 1\n");
            }
        }
        if(eleccionDesarrollador == 2){
            int maximaCantidad = 0;
            printf("Cantidad de materias a crear\n");
            scanf("%i",&maximaCantidad);
            printf("Desea ver los nombres de las Materias mientras se crea? 0)No 1)Si\n");
            int printear = 0;
            scanf("%i",&printear);
            if(!(printear == 0 || printear == 1)){
                printf("Opcion elegida erronea , por lo tanto entrara en modo default y no los mostrara \n");
            }
            if(maximaCantidad >= 1){
                generarMateriasAleatorias(listaDeMaterias,maximaCantidad,printear);
            } else{
                printf("El valor ingresado no puede ser menor a 1 y las opciones 0 o 1\n");
            }
        }
        if(eleccionDesarrollador == 3){ printearListaDeAlumnos(listaDeAlumnos);}
        if(eleccionDesarrollador == 4){ printearListaDeMaterias(listaDeMaterias);}
    }
}

void Menu(ListaMaterias* listaDeMaterias,ListaDeAlumnos* listaDeAlumnos){
    int eleccionUsuario = 1;
    while(eleccionUsuario != 0){
        printf("-------=============-------\n");
        printf("Bienvenido Al Sistema universitario de P.E.P.E, Personas Especiales Para Estudiar \n");
        printf("----Que Opcion Desea Realizar?----\n");
        printf("1)Inscribir Alumno \n");
        printf("2)Inscribir Alumno a una Materia \n");
        printf("3)Mostrar Alumnos por rango de edad \n");
        printf("4)Buscar Alumno por nombre \n");
        printf("5)Mostrar Promedio del alumno \n");
        printf("6)Ingresar Resultado de examen \n");
        printf("7)Ingresar Nueva Materia \n");
        printf("8)Mostrar Alumno o Materia por ID\n");
        printf("9)Mostar Alumnos Paginados\n");
        printf("10)Mostrar Materias Paginadas \n");
        printf("0)Salir\n");
        scanf("%i", &eleccionUsuario);
        realizarOperacionSolicitada(eleccionUsuario,listaDeMaterias,listaDeAlumnos);
    }
    guardarEnBdd(listaDeMaterias,listaDeAlumnos);
}


int main() {
    ListaMaterias* listaMaterias = inicializarListaMaterias();
    ListaDeAlumnos* listaAlumnos = inicializarListaAlumnos();
    printf("Inicializando Programa, esto puede tardar unos segundos \n");
    InicializarBdd(listaAlumnos,listaMaterias);
    Menu(listaMaterias,listaAlumnos);
    return 0;
}
