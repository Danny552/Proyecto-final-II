#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_Votantes 150

struct Votante
{
    char codigo[12]; //Documento identidad
    char nombre[60]; //Nombre
    char clave[10]; //clave establecida por el programa
    bool voto; //Si ya votó o no
    int tipo; //Tipo de votante (1.Estudiante, 2.Egresado, 3.Docentes, 4.Administrativos)
};

struct Votante Votantes[MAX_Votantes];

bool ConfirmarCedula(int contador, char cd[10]) //Función auxiliar que sirve para verificar que la misma cedula no esté dos veces
{
    int i;
    for(i=0;i<contador;i++)
    {
        if(Votantes[i].codigo == cd)
        {
            printf("Usuario ya registrado.\n");
            return false;
        }
    }
    return true;
}

struct Admin
{
    char codigo[12]; //Documento identidad
    char nombre[60]; //Nombre
    char clave[100]; //clave establecida
};

struct Votos
{
    int votosEstudiantes; //Cantidad de votos por parte de estudiantes
    int votosDocentes; //Cantidad de votos por parte de docentes
    int votosEgresados; //Cantidad de votos por parte de egresados
    int votosAdministrativos; //Cantidad de votos por parte de administrativos
    int totales;
};

struct Candidato
{
    char nombre[60]; //Nombre
    char codigo[12]; //Documento identidad
    char nTarjetón; //Número en el tarjetón
    struct Votos votos; //Cantidad de votos a favor
};

void registrarArchivoCodigos() //Se registra un archivo donde se almacenarán los codigos
{
    struct Votante votante;
    FILE *archdisco;
    archdisco = fopen("files//Votantes//cedulas.txt", "at+");
    printf("Ingrese código del votante a registrar: ");
    gets(votante.codigo);
    fwrite(&votante,sizeof(votante),1,archdisco);
    fclose(archdisco);
}

void registrarArchivoNombres() //Se registra un archivo donde se almacenarán los nombres
{
    struct Votante votante;
    FILE *archdisco;
    archdisco = fopen("files//Votantes//nombres.txt", "at+");
    printf("Ingrese nombre del votante a registrar: ");
    gets(votante.nombre);
    fwrite(&votante,sizeof(votante),1,archdisco);
    fclose(archdisco);
}

void registrarArchivoClaves() //Se registra un archivo donde se almacenarán las claves
{
    struct Votante votante;
    FILE *archdisco;
    archdisco = fopen("files//Votantes//claves.txt", "at+");
    char c;
    int i, a;
    for(i=0;i<10;i++)
    {
        do
        {
            a = rand() % 123;
        }while( (a<33) || (a==123) || (a>90 && a<97) || (a>58 && a<63));
        c = a;
        votante.clave[i];
    }
    printf("Clave generada exitosamente.\n");
    fwrite(&votante,sizeof(votante),1,archdisco);
    fclose(archdisco);
}

void registrarArchivoCodigos() //Se registra un archivo donde se almacenarán los codigos
{
    struct Votante votante;
    FILE *archdisco;
    archdisco = fopen("files//Votantes//tipos.txt", "at+");
    printf("Ingrese tipo del votante a registrar: ");
    scanf("%d", votante.tipo);
    fwrite(&votante,sizeof(votante),1,archdisco);
    fclose(archdisco);
}

void registrarVotante() //Opción para el administrativo para registrar un votante
{
    
}

void ElimiarVotante()
{
    //Opción del Admin para eliminar un votante
}

void EditarVotante()
{
    //Opción del Admin para editar un votante
}

void ConsultarVotantes()
{
    //Opción del administrador para consultar los datos de los votantes
}

void AñadirCandidato()
{
    //Opción del administrador para registrar un candidato
}

void EliminarCandidato()
{
    //Opción del administrador para eiminar un candidato
}

void ConsultarCandidatos()
{
    //Opción del administrador para consultar los datos de los candidatos
}

void ConsultarVotosESpecificos()
{
    //Opción del administrador para consultar cuantos votos lleva un candidato especifico
}

void ConsultarVotos()
{
    //Opción del administrador para consultar como van las votaciones
}

int menuVotante(){
    int id;
    printf ("Ingrese su número de identificación: ");
    scanf ("%d", &id);
    printf ("Ingrese su clave (Dada por el administrador):");
    scanf ("%d", &id);
    printf ("Ingrese su candidato a votar:");
    printf ("1)-----------\n2)-----------\n3)-----------\n4)-----------\n5)-----------\n6)-----------");
}

int menuConsultas(){
    do{
    printf("Ingrese lo que desee ver: ");
    printf("1)Votos netos\n2)Porcentaje neto de votos\n2)Porcentaje de votos ponderados\n3)Histograma de frecuencia de votos");
    int opc;
    scanf ("%d", &opc);
    switch (opc)
    {
        case 1:
    votoNeto();
    break;
        case 2:
    votoNetoPor();
    break;
        case 3:
    votoPonderadoPor();
    break;
        case 4:
    histograma();
    break;
        case 5:
        break;
    default:
    printf("Opción no válida");
        break;
    }
    } while (0);
}

int menuAdmin(char usuario[100]){
    printf("BIENVENIDO %d\n", cupper(usuario[100]));
    printf("Ingrese lo que desea realizar:\n");
    int opc;
    printf("1) Registrar votante\n2)Eliminar datos de votante\n3)Modificar datos de votante\n4)Registrar candidato\n5)Eliminar candidato\n6)Finalizar y ver consultas (ESTO CIERRA LOS VOTOS)\n6)\n7)Salir.");
    scanf("%d", &opc);
    switch (opc)
    {
    case 1:
    registrarVotante();
        break;
    case 2:
    eliminarVotante();
    case 3:
    modificarVotante();
    break;
    case 4:
    registrarCandidato();
    case 5:
    menuConsultas();
    case 6: 
    menu();
    default:
    printf ("opción no válida");
    sleep(100);
    system("Clear");
    menuAdmin(usuario);
        break;
    }
}

int ingresarAdministrador(){
    char usuario[100];
    int contra;
    printf("Ingrese su usuario:");
    scanf("%d", &usuario);
    printf("Ingrese su clave: ");
    scanf("%d", &contra);
    menuAdmin(usuario);
}

int menu(){
    int opc;
    scanf ("%d", &opc);
    switch(opc){
        printf ("1) Votante\n2) Administrador");
        case 1:
        registrarVotante();
        break;
        case 2:
        ingresarAdministrador();
        break;
        }
    }

