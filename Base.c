#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

#define MAX_Votantes 150

void MenuAdmin();
void MenuConsultas();

struct Votante
{
    char codigo[12]; //Documento identidad
    char nombre[60]; //Nombre
    char contra[100]; //Contraseña establecida por el programa
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
    char contra[100]; //Contraseña establecida
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
    char nTar; //Número en el tarjetón
    struct Votos votos; //Cantidad de votos a favor
};

void crearArchivo()
{
    //Se crea un archivo donde se almacenarán los codigos
}

void RegistrarVotante()
{
    //Opción para el administrativo para registrar un votante
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
    char usuario[100];
    int contra;
    printf("Ingrese su usuario:");
    gets(usuario);
    printf("Ingrese su contra: ");
    scanf("%d", &contra);
    MenuAdmin(usuario);
}
void Menu(){
    int opc;
    printf ("1) Votante\n2) Administrador");
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

void MenuAdmin(char usuario[100]){
    printf("BIENVENIDO %d\n", usuario[100]);
    printf("Ingrese lo que desea realizar:\n");
    int opc;
    printf("1) Registrar votante\n2)Eliminar datos de votante\n3)Registrar candidato\n4)Eliminar candidato\n5)Finalizar y ver consultas (ESTO CIERRA LOS VOTOS)\n6)Salir.");
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
    MenuAdmin(usuario);
        break;
    }
}

void MenuVotante(){
    int id;
    printf ("Ingrese su número de identificación: ");
    scanf ("%d", &id);
    printf ("Ingrese su contra (Dada por el administrador):");
    scanf ("%d", &id);
    printf ("Ingrese su candidato a votar:");
    printf ("1)-----------\n2)-----------\n3)-----------\n4)-----------\n5)-----------\n6)-----------");
}
void MenuConsultas(){
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
    printf("Opción no válida");
        break;
    }
    } while (0);
}

int main(){
    Menu();
}