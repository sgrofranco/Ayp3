///TODO: aca va a estar la bdd, el generador masivo de alumnos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generarAlumnosAleatorios(ListaDeAlumnos* listaDeAlumnos, int maximo){
    char *listaNombres[]= {"Adel","Adonis","Ajaz","Akos","Aldo","Amets","Amaro","Aquiles","Algimantas","Alpidio","Amrane","Anish","Arian","Ayun","Azariel","Bagrat"
            ,"Bencomo","Bertino","Candi","Cesc","Cirino","Crisologo","Cruz","Danilo","Dareck","Dariel","Darin","Delmiro","Damen","Dilan","Dipa"
            ,"Domenico","Drago","Edivaldo","Elvis","Elyan","Emeric","Engracio","Ensa","Enaut","Eleazar","Eros","Eufemio","Feiyang"
            ,"Fiorenzo","Foudil","Galo","Gaston","Giulio","Gautam","Gentil","Gianni","Gianluca","Giorgio","Gourav","Grober","Guido"
            ,"Guifre","Guim","Hermes","Inge","Irai","Iraitz","Iyad","Iyan","Jeremias","Joao","Jun","Khaled","Leonidas","Lier","Lionel"
            ,"Lisandro","Lucian","Mael","Misael","Moad","Munir","Nael"};

    char *listaDeApellidos[]={"Gonzalez","Rodriguez","Gomez","Fernandez","Lopez","Martinez","Diaz","Perez","Sanchez"
            ,"Romero","Garcia","Sosa","Benitez","Ramirez","Torres","Ruiz","Flores","Alvarez","Acosta","Rojas"};

    for(int i = 0 ; i < maximo ; i++){
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

void generarMateriasAleatorias(ListaMaterias* listaMaterias, int maximo){

    char* listaNombres[]={ "Algoritmos y programacion","Estructura de datos", "Base de datos", "Analisis matematico",
                           "Algebra","Fisica","Sistemas de representacion","Arquitectura de computadoras",
                           "minecraft tecnico", "Electronica", "Historia", "Filosofia", "Diseño grafico",
                           "Quimica","Teoria de la organizacion", "Finanzas", "Impuestos","Derecho", "Defensa oral y escrita",
                           "Robotica", "Probabilidad y estadistica", "Matematica discreta", "Sistema monetario",
                           "Teoria de juegos"};

    char* listaDeNivel[]={ "1","2","3","4","5","6"};

    for (int i = 0; i < maximo; i++){
        int nombre = 0;
        int nivel = -1;

        while(nombre <= 0 || nombre > (sizeof listaNombres/sizeof listaNombres[0])){
            nombre = rand() % sizeof listaNombres/sizeof  listaNombres[0];
        }
        char* nombreDeMateria = listaNombres[nombre];

        while (nivel < 0 || nivel > 5){
            nivel = rand() %5;
        }
        char* nivelDefinitivo = listaDeNivel[nivel];


        char nombreCompleto[50];

        strcpy(nombreCompleto, nombreDeMateria);
        strcat(nombreCompleto, " ");
        strcat(nombreCompleto, nivelDefinitivo);

        agregarMateriaAListaDeMateriasSinCorrelativas(listaMaterias,nombreCompleto);
        printf("materia: %s \n",nombreCompleto);

    }
}

void cargarHistorialAlAlumno(ListaMaterias* listaMaterias,ListaDeAlumnos* listaDeAlumnos,long int idalumno , int idMateria , int nota){
    Alumno* alumno = getAlumno(listaDeAlumnos,idalumno);
    Materia* materia = getMateria(listaMaterias,idMateria);
    agregarMateriaAAlumno(alumno,materia);
    HistorialDeLaMateria* historialDeLaMateria = alumno->listaDeHistorialDeMaterias->cabeza;
    ///TODO:Ver DE cambiar el metodo cambiarNota o dejarlo asi
    if(nota != 0){
        do {
            if(historialDeLaMateria->infoMateria->idMateria == materia->idMateria){
                break;
            }
            else if(historialDeLaMateria->siguiente){
                historialDeLaMateria = historialDeLaMateria->siguiente;
            }
        } while (historialDeLaMateria);
        historialDeLaMateria->nota = nota;
    }else{
        historialDeLaMateria->nota = NULL;
    }
};

void InicializarBdd(ListaDeAlumnos* listaDeAlumnos, ListaMaterias* listaMaterias){
    ///bdd Materia
    FILE* fileBddMaterias;
    fileBddMaterias = fopen("../bddMaterias.txt","r");
    char lineBddMateria [128] = {0};
    int lineaActualMateria = 0;
    if(!fileBddMaterias){
        printf("No cargo la bdd llame a su tecnico mas cercano \n");
    }
    while (fgets(lineBddMateria , 128 , fileBddMaterias)){
        lineaActualMateria++;
        char* lineaSplitMateria = strtok(lineBddMateria,",");
        char nombreMateria[30];
        strcpy(nombreMateria,lineaSplitMateria);
        lineaSplitMateria = strtok(NULL,",");
        if(listaMaterias->cabeza == NULL){///Esto es lo mismo que agregar materia a lista de materia
            listaMaterias->cantidadMaterias++;
            Materia* nuevaMateria = crearMateria(nombreMateria);
            nuevaMateria->idMateria = listaMaterias->cantidadMaterias;
            listaMaterias->cabeza = nuevaMateria;
        }else{
            Materia* materia = listaMaterias->cabeza;
            while(materia->siguiente){
                materia = materia->siguiente;
            }
            listaMaterias->cantidadMaterias++;
            Materia* nuevaMateria = crearMateria(nombreMateria);
            nuevaMateria->idMateria = listaMaterias->cantidadMaterias;
            materia->siguiente = nuevaMateria;
        }
        while(lineaSplitMateria != NULL){
            char correlativas[11];
            char *puntero;
            ///TODO: MEJORAR ESTO
            Materia* materia = getMateria(listaMaterias,lineaActualMateria);
            strcpy(correlativas,lineaSplitMateria);
            puntero = strtok(correlativas,":");
            while(puntero != NULL){
                int idMateriaCorrelativa;
                idMateriaCorrelativa = atoi(puntero);
                //TODO: METODO ASIGNAR CORRELATIVA TIENE SCAN F
                if(idMateriaCorrelativa != 0){
                    if(puntero){
                        int i = 0;
                        while (materia->arrayCorrelativas[i]->idMateria != 0) {
                            i++;
                        }
                        materia->arrayCorrelativas[i] = getMateria(listaMaterias, idMateriaCorrelativa);
                    }
                }
                puntero = strtok(NULL,":");
            }
            lineaSplitMateria = strtok(NULL,",");
        }
    }
    fclose(fileBddMaterias);
    ///bdd alumno
    FILE* fileBddAlumno;
    fileBddAlumno = fopen("../bddAlumnos.txt", "r");
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
        /////// id de alumno es id de linea
        lineaSplit = strtok(NULL,",");
        if(lineaSplit != NULL) { /// aca cargamos todas las notas de alumno.
            char materia[250];
            char *puntero;
            strcpy(materia, lineaSplit);
            puntero = strtok(materia,"!:");
            while(puntero != NULL){
                int id = 0;
                int nota = 0;
                id = atoi(puntero);
                puntero = strtok(NULL,"!:");
                nota = atoi(puntero);
                cargarHistorialAlAlumno(listaMaterias,listaDeAlumnos,lineaActual,id,nota);
                puntero = strtok(NULL,"!:");
            }
        }
    }
    fclose(fileBddAlumno);
}
void guardarEnBdd(ListaMaterias* listaMaterias, ListaDeAlumnos* listaDeAlumnos){
    FILE* fileBddMateria;
    fileBddMateria = fopen("../bddMaterias.txt","w");
    Materia* materia = listaMaterias->cabeza;
    int lineaActual = 0;
    while(materia){
        lineaActual++;
        char correlativas[11] = {0};
        char lineaAEscribir[40]= {0};
        int tieneCorrelativas = 0;
        strcat(lineaAEscribir,materia->nombreMateria);
        for(int i = 0 ; i < 5 ; i++){
            if(materia->arrayCorrelativas[i]->idMateria != 0){
                if(i != 0){ strcat(correlativas,":");}
                char idmateria[3] = {0};
                itoa(materia->arrayCorrelativas[i]->idMateria,idmateria,10);
                strcat(correlativas,idmateria);
                printf("guarda correlativa : %s \n " , idmateria);
                tieneCorrelativas++;
            }
        }
        if(tieneCorrelativas != 0){
            strcat(lineaAEscribir,",");
            strcat(lineaAEscribir,correlativas);
        }else{
            strcat(lineaAEscribir,",0");
        }
        printf("linea: %s \n",lineaAEscribir);
        fprintf(fileBddMateria,"%s\n",lineaAEscribir);
        materia = materia->siguiente;
    }
    fclose(fileBddMateria);
    ///Guardar Alumnos
    FILE* fileBddAlumno;
    fileBddAlumno = fopen("../bddAlumnos.txt","w");
    Alumno* alumno = listaDeAlumnos->cabeza;
    if(!fileBddAlumno){
        printf("no cargo la bdd llame a su tecnico mas cercano \n");
    }
    lineaActual = 0;
    while(alumno){
        lineaActual++;
        char lineaAEscribir[60] = {0};
        strcpy(lineaAEscribir,alumno->Nombre);
        strcat(lineaAEscribir,",");
        char edad[3] = {0};
        itoa(alumno->edad,edad,10);
        strcat(lineaAEscribir,edad);
        printf(" linea a escribir alumno : %s \n",lineaAEscribir);
        HistorialDeLaMateria* historialDeLaMateria = alumno->listaDeHistorialDeMaterias->cabeza;
        while(historialDeLaMateria){
            char historialDeLaMateriaACargar[6] = {0};
            if(historialDeLaMateria == alumno->listaDeHistorialDeMaterias->cabeza){
                strcat(historialDeLaMateriaACargar,",");
            }else{
                strcat(historialDeLaMateriaACargar,":");
            }
            char idmateria[10];
            itoa(historialDeLaMateria->infoMateria->idMateria,idmateria,10);
            strcat(historialDeLaMateriaACargar,idmateria);
            strcat(historialDeLaMateriaACargar,"!");
            printf(" linea a escribir alumno : %s \n",historialDeLaMateriaACargar);
            if(historialDeLaMateria->nota != NULL){
                char nota[2] = {0};
                itoa(historialDeLaMateria->nota,nota,10);
                strcat(historialDeLaMateriaACargar,nota);
            } else{
                strcat(historialDeLaMateriaACargar,"0");
            }
            strcat(lineaAEscribir,historialDeLaMateriaACargar);
            historialDeLaMateria = historialDeLaMateria->siguiente;
        }
        printf(" linea definitiva a escribir %s \n",lineaAEscribir);
        fprintf(fileBddAlumno,"%s\n",lineaAEscribir);
        alumno = alumno->siguiente;
    }
    fclose(fileBddAlumno);
}

///ESTE METEDO INDICA SI SE INGERSO UN INT EN EL SCANF, DEVUELE 1 SI ES UN INT Y 0 SI HAY
/// ALGUN CHAR EN LO INGRESADO
int SeIngresoUnIntEnElScan(int integer){
    if(integer == 0){
        printf("0");
        return 0;
    } else {
        printf("1");
        return 1;
    }
}

///ESTE METEDO INDICA SI SE INGERSO UN NUMERO EN EL STRING, DEVUELVE 1 SI NO HAY NUMEROS
/// Y DEUVLE 0 SI HAY ALGUNO
int esUnChar(char character[]){
    int i;
    for (int j = 0; j < 30; j++) {
        i = atoi(&character[j]);
        if(i != 0) {
            return 0;
        }
        return 1;
    }

}

