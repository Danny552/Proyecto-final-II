#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

#define MAX_Votantes 150

void MenuAdmin(int admin);
void MenuConsultas();

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

struct Admin admins[2] = { {"1114150552", "Daniel Alejandro Henao", "odioracket23"} , {"1137059546", "Juan Camilo Cano", "teamoracket32"} };

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
    char nTar; //Número en el tarjetón
    struct Votos votos; //Cantidad de votos a favor
};

void registrarCodigos() //Se registra un archivo donde se almacenarán los codigos
{
    getchar();
    struct Votante votante;
    FILE *archdisco;
    archdisco = fopen("files//Votantes//cedulas.txt", "at+");
    printf("Ingrese código del votante a registrar: ");
    gets(votante.codigo);
    fwrite(&votante,sizeof(votante),1,archdisco);
    fclose(archdisco);
}

void registrarNombres() //Se registra un archivo donde se almacenarán los nombres
{
    struct Votante votante;
    FILE *archdisco;
    archdisco = fopen("files//Votantes//nombres.txt", "at+");
    printf("Ingrese nombre del votante a registrar: ");
    gets(votante.nombre);
    fwrite(&votante,sizeof(votante),1,archdisco);
    fclose(archdisco);
}

void registrarClaves() //Se registra un archivo donde se almacenarán las claves
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
        votante.clave[i] = c;
    }
    printf("Clave generada exitosamente.\n");
    fwrite(&votante,sizeof(votante),1,archdisco);
    fclose(archdisco);
}

void registrarTipos() //Se registra un archivo donde se almacenarán los codigos
{
    struct Votante votante;
    FILE *archdisco;
    archdisco = fopen("files//Votantes//tipos.txt", "at+");
    printf("Ingrese tipo del votante a registrar: ");
    scanf("%d", &votante.tipo);
    fwrite(&votante,sizeof(votante),1,archdisco);
    fclose(archdisco);
}

void RegistrarVotante() //Opción para el administrativo para registrar un votante
{
    registrarCodigos();
    registrarNombres();
    registrarClaves();
    registrarTipos();
}

void EliminarVotante()
{
    //Opción del Admin para eliminar un votante
}

void ConsultarVotantes()
{
    //Opción del administrador para consultar los datos de los votantes
}

void AnadirCandidato()
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

void votoNeto(){
    //para ver el la cantidad total 
}

void VotoNetoTipo(){
    //La cantidad total por tipo de votante
}

void VotoPonderadoTipo(){
    //los votos después de hacer la ponderación
}

void Histograma(){
    //Histograma
}

void IngresarAdministrador(){
    getchar();
    bool credencia = false;
    int i;
    char codigo[12], clave[100];    
    printf("Ingrese su código: ");
    gets(codigo);
    printf("Ingrese su clave: ");
    gets(clave);
    for(i=0;i<2;i++)
    {
        if(strcmp(codigo, admins[i].codigo)==0 && strcmp(clave, admins[i].clave)==0)
        {
            MenuAdmin(i);
            credencia = true;
        };
    }
    if(!credencia)
    {
        printf("Clave o código incorrectos.\n");
    }
}

void Menu(){
    int opc;
    printf ("1) Votante\n2) Administrador\nSu opción: ");
    scanf ("%d", &opc);
    switch(opc){
        case 1:
        RegistrarVotante();
        break;
        case 2:
        IngresarAdministrador();
        break;
        }
    }

void MenuAdmin(int admin){
    printf("BIENVENIDO %s\n", admins[admin].nombre); //Xd
    printf("Ingrese lo que desea realizar:\n");
    int opc;
    printf("1) Registrar votante\n2)Eliminar datos de votante\n3)Registrar candidato\n4)Eliminar candidato\n5)Finalizar y ver consultas (ESTO CIERRA LOS VOTOS)\n6)Salir.\n");
    scanf("%d", &opc);
    switch (opc)
    {
    case 1:
    RegistrarVotante();
        break;
    case 2:
    EliminarVotante();
        break;
    case 3:
    AnadirCandidato();
        break;
    case 5:
    MenuConsultas();
        break;
    case 6: 
    Menu();
        break;
    default:
    printf ("opción no válida");
    Sleep(100);
    system("Clear");
    MenuAdmin(admin);
        break;
    }
}

void MenuVotante(){
    int id;
    printf ("Ingrese su número de identificación: ");
    scanf ("%d", &id);
    printf ("Ingrese su clave (Dada por el administrador):");
    scanf ("%d", &id);
    printf ("Ingrese su candidato a votar:");
    printf ("1)-----------\n2)-----------\n3)-----------\n4)-----------\n5)-----------\n6)-----------\n");
}
void MenuConsultas(){
    do{
    printf("Ingrese lo que desee ver: ");
    printf("1)Votos netos\n2)Porcentaje neto de votos\n2)Porcentaje de votos ponderados\n3)Histograma de frecuencia de votos\n");
    int opc;
    scanf ("%d", &opc);
    switch (opc)
    {
        case 1:
    votoNeto();
    break;
        case 2:
    VotoNetoTipo();
    break;
        case 3:
    VotoPonderadoTipo();
    break;
        case 4:
    Histograma();
    break;
        case 5:
        break;
    default:
    printf("Opción no válida.\n");
        break;
    }
    } while (0);
}

int main(){
    system("CLS");
    Menu();
}