///TODO: aca va a estar la bdd, el generador masivo de alumnos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generar100AlumnosAleatorios(ListaDeAlumnos* listaDeAlumnos){
    char *listaNombres[]= {"Adel","Adonis","Ajaz","Akos","Aldo","Amets","Amaro","Aquiles","Algimantas","Alpidio","Amrane","Anish","Arian","Ayun","Azariel","Bagrat"
                        ,"Bencomo","Bertino","Candi","Cesc","Cirino","Crisologo","Cruz","Danilo","Dareck","Dariel","Darin","Delmiro","Damen","Dilan","Dipa"
                        ,"Domenico","Drago","Edivaldo","Elvis","Elyan","Emeric","Engracio","Ensa","Enaut","Eleazar","Eros","Eufemio","Feiyang"
                        ,"Fiorenzo","Foudil","Galo","Gaston","Giulio","Gautam","Gentil","Gianni","Gianluca","Giorgio","Gourav","Grober","Guido"
                        ,"Guifre","Guim","Hermes","Inge","Irai","Iraitz","Iyad","Iyan","Jeremias","Joao","Jun","Khaled","Leonidas","Lier","Lionel"
                        ,"Lisandro","Lucian","Mael","Misael","Moad","Munir","Nael"};

    char *listaDeApellidos[]={"Gonzalez","Rodriguez","Gomez","Fernandez","Lopez","Martinez","Diaz","Perez","Sanchez"
                              ,"Romero","Garcia","Sosa","Benitez","Ramirez","Torres","Ruiz","Flores","Alvarez","Acosta","Rojas"};

    for(int i = 0 ; i < 100 ; i++){
        int nombre = -1;
        int apellido = 0;
        int edad = 10;

        while(nombre<=0 || nombre > (sizeof listaNombres / sizeof listaNombres[0])){
            nombre = rand() % sizeof listaNombres / sizeof listaNombres[0];
        }
        char *nombreAlumno = listaNombres[nombre];
        while(apellido<=0 || apellido > (sizeof listaDeApellidos / sizeof listaDeApellidos[0])){
            apellido = rand() % sizeof listaDeApellidos / sizeof listaDeApellidos[0];
        }
        char *apellidoAlumno = listaDeApellidos[apellido];
        while(edad < 17 || edad > 100){
            edad = rand() % 100;
        }

        char nombreCompleto[50];

        strcpy(nombreCompleto, nombreAlumno);
        strcat(nombreCompleto, " ");
        strcat(nombreCompleto,  apellidoAlumno);

        agregarAlumno(listaDeAlumnos,nombreAlumno,edad);
        printf("alumno: %s , edad: %i \n",nombreCompleto,edad);
    }
}

void generar100MateriasAleatorias(ListaMaterias* listaMaterias){

    char* listaNombres[]={ "Algoritmos y programacion","Estructura de datos", "Base de datos", "Analisis matematico",
                           "Algebra","Fisica","Sistemas de representacion","Arquitectura de computadoras",
                           "minecraft tecnico", "Electronica", "Historia", "Filosofia", "Diseño grafico",
                           "Quimica","Teoria de la organizacion", "Finanzas", "Impuestos","Derecho", "Defensa oral y escrita",
                           "Robotica", "Probabilidad y estadistica", "Matematica discreta", "Sistema monetario",
                           "Teoria de juegos"};

    char* listaDeNivel[]={ "1","2","3","4","5","6"};

    for (int i = 0; i < 100; i++){
        int nombre = 0;
        int nivel = -1;

        while(nombre <= 0 || nombre > (sizeof listaNombres/sizeof listaNombres[0])){
            nombre = rand() % sizeof listaNombres/sizeof  listaNombres[0];
        }
        char* nombreDeMateria = listaNombres[nombre];

        while (nivel < 0 || nivel > 5){
            nivel = rand() %5;
            printf("%i \n",nivel);
        }
        char* nivelDefinitivo = listaDeNivel[nivel];


        char nombreCompleto[50];

        strcpy(nombreCompleto, nombreDeMateria);
        printf("asd");
        strcat(nombreCompleto, " ");
        strcat(nombreCompleto, nivelDefinitivo);

        agregarMateriaAListaDeMaterias(listaMaterias,nombreCompleto);
        printf("materia: %s \n",nombreCompleto);

    }
}

void InicializarBdd(ListaDeAlumnos* listaDeAlumnos, ListaMaterias* listaMaterias){
    ///bdd alumno
    FILE* fileBddAlumno;
    fileBddAlumno = fopen("../bddAlumno.txt", "r");
    char line[128] = {0};
    int lineaActual = 0 ;
    if(!fileBddAlumno){
        printf("no cargo la bdd llame a su tecnico mas cercano \n");
    }
    while (fgets(line, 128, fileBddAlumno)){
        lineaActual++;
        char* lineaSplit = strtok(line,",");
        char nombre[30];
        strcpy(nombre,lineaSplit);
        lineaSplit = strtok(NULL,",");
        int edad = atoi(lineaSplit);
        agregarAlumno(listaDeAlumnos,nombre,edad);
        printearListaDeAlumnos(listaDeAlumnos);
        /////// id de alumno es id de linea
        lineaSplit = strtok(NULL,",");
        while(lineaSplit != NULL) { /// aca llega 1!2
            char materia[6];
            char *puntero;
            strcpy(materia, lineaSplit);
            puntero = strtok(materia, "!");
            int idMateria = atoi(puntero);
            if (idMateria != 0) {
                //AnotarseAMateria(listaMaterias,listaDeAlumnos,idMateria,lineaActual);
                puntero = strtok(NULL, ":");
                int nota = atoi(puntero);
                if (nota != 0) {
                    //CargarNota(getAlumno(listaDeAlumnos,lineaActual), getMateria(listaMaterias,idMateria),nota);
                    printf("valores que quedan =  id %i , nota %i \n", idMateria, nota);
                }
            }
            lineaSplit = strtok(NULL, ":");
            printf(" next line : %s\n", lineaSplit);
        }
    }
}

