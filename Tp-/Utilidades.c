///TODO: aca va a estar la bdd, el generador masivo de alumnos
#include <stdio.h>

void generar100AlumnosAleatorios(ListaDeAlumnos* listaDeAlumnos){
    char *listaNombres[]= {"Adel","Adonis","Ajaz","Akos","Aldo","Amets","Amaro","Aquiles","Algimantas","Alpidio","Amrane","Anish","Arián","Ayun","Azariel","Bagrat"
                        ,"Bencomo","Bertino","Candi","Cesc","Cirino","Crisólogo","Cruz","Danilo","Dareck","Dariel","Darin","Delmiro","Damen","Dilan","Dipa"
                        ,"Doménico","Drago","Edivaldo","Elvis","Elyan","Emeric","Engracio","Ensa","Eñaut","Eleazar","Eros","Eufemio","Feiyang"
                        ,"Fiorenzo","Foudil","Galo","Gastón","Giulio","Gautam","Gentil","Gianni","Gianluca","Giorgio","Gourav","Grober","Guido"
                        ,"Guifre","Guim","Hermes","Inge","Irai","Iraitz","Iyad","Iyán","Jeremías","Joao","Jun","Khaled","Leónidas","Lier","Lionel"
                        ,"Lisandro","Lucián","Mael","Misael","Moad","Munir","Nael"};

    char *listaDeApellidos[]={"González","Rodríguez","Gómez","Fernández","López","Martínez","Diaz","Pérez","Sánchez"
                              ,"Romero","García","Sosa","Benítez","Ramírez","Torres","Ruiz","Flores","Álvarez","Acosta","Rojas"};

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
        ///TODO: CONCATENAR NOMBRE Y APELLIDO
        agregarAlumno(listaDeAlumnos,nombreAlumno,edad);
        printf("alumno: %s , edad: %i \n",nombreAlumno,edad);
    }
}
