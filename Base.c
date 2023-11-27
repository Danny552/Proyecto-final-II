#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <wchar.h>

#define RESET_COLOR     "\x1b[0m"
#define NEGRO_T         "\x1b[30m"
#define NEGRO_F         "\x1b[40m"
#define ROJO_T          "\x1b[31m"
#define ROJO_F          "\x1b[41m"
#define VERDE_T         "\x1b[32m"
#define VERDE_F         "\x1b[42m"
#define AMARILLO_T      "\x1b[33m"
#define AMARILLO_F      "\x1b[43m"
#define AZUL_T          "\x1b[34m"
#define AZUL_F          "\x1b[44m"
#define MAGENTA_T       "\x1b[35m"
#define MAGENTA_F       "\x1b[45m"
#define CYAN_T          "\x1b[36m"
#define CYAN_F          "\x1b[46m"
#define BLANCO_T        "\x1b[37m"
#define BLANCO_F        "\x1b[47m"
#define MAX_Votantes 150

int registro()
{
    FILE *archivo;
    int n;
    archivo = fopen("files//contador.txt","r");
    fscanf(archivo,"%d",&n);
    fclose(archivo);
    return n;
}

int registros;
void Menu();

void modificarCantidadRegistros(int n)
{
    FILE *archivo;
    archivo = fopen("files//contador.txt","w");
    fprintf(archivo,"%d",n);
    fclose(archivo);
}

void MenuAdmin(int admin);
void MenuConsultas();

struct Votante
{
    char codigo[12]; //Documento identidad
    char nombre[60]; //Nombre
    char clave[10]; //clave establecida por el programa
    int voto; //Si ya votó o no
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

struct Admin admins[2] = { {"1114150552", "Daniel Alejandro Henao", "odioracket23"} , {"1137059546", "Juan Camilo Cano", "clave"} };

struct Votos
{
    int votosEstudiantes; //Cantidad de votos por parte de estudiantes
    int votosDocentes; //Cantidad de votos por parte de docentes
    int votosEgresados; //Cantidad de votos por parte de egresados
    int votosAdministrativos; //Cantidad de votos por parte de administrativos
};

struct Candidato
{
    char nombre[60]; //Nombre
    char nTar; //Número en el tarjetón
    struct Votos votos; //Cantidad de votos a favor
};

struct Candidato Candidatos[6];

void RegistrarVotante() //Opción para el administrativo para registrar un votante
{
    system("CLS");
    int i = 0;
    bool repite;
    fflush(stdin);
    struct Votante VR[registros];
    FILE *archdisco;
    archdisco = fopen("files//Votantes.txt", "r");
    fread(VR,sizeof(struct Votante), registros, archdisco);

    fread(VR, sizeof(struct Votante), 1, archdisco);

    do{
        repite = false;
        printf("Ingrese c%cdigo del votante a registrar: ", 162);
        gets(Votantes[registros].codigo);

        for(i=0;i<registros;i++)
        {
            if(strcmp(VR[i].codigo, Votantes[registros].codigo) != 0)
            {
            }
            else{
                repite = true;
                printf(ROJO_T "C%cdigo ya registrado, intente de nuevo.\n", 162);
                printf(". ");
                Sleep(1000);
                printf(". ");
                Sleep(1000);
                printf("." RESET_COLOR);
                Sleep(1000);
                system("CLS");
            }
        }
    }while(repite);

    printf("Ingrese nombre del votante a registrar: ");
    gets(Votantes[registros].nombre);

    char c;
    int a;
    for(i=0;i<10;i++)
    {
        do
        {
            a = rand() % 123;
        }while( (a<48) || (a>57 && a<65) || (a>90 && a<97) || (a>122));
        c = a;
        Votantes[registros].clave[i] = c;
    }
    printf("Clave generada exitosamente.\n");

    printf( AZUL_T "1)Estudiante\n" ROJO_T "2)Docente\n" NEGRO_T "3)Egresado\n" VERDE_T "4)Administrativo\n"RESET_COLOR"Ingrese tipo del votante a registrar: ");
    scanf("%d", &Votantes[registros].tipo);

    Votantes[registros].voto = 0;
    fclose(archdisco);
    archdisco = fopen("files//Votantes.txt", "at+");
    fwrite(&Votantes[registros],sizeof(struct Votante),1,archdisco);
    fclose(archdisco);

    registros++;

    modificarCantidadRegistros(registros);
}

void EliminarVotante() //Opción del Admin para eliminar un votante
{
    int i = 0, j = 0;
    FILE *archivo = fopen("files//Votantes.txt", "r"); //Entradas
    FILE *temporal = fopen("files//temporal.txt", "w"); //Temporales

    struct Votante Votantes[registros];
    struct Votante VotantesT[registros];
    
    char cedulaElim[12];
    fflush(stdin);
    printf("Ingrese el c%cdigo del votante que desea eliminar: ", 162);
    gets(cedulaElim);

    while(fread(&Votantes[i], sizeof(struct Votante), 1, archivo) == 1 && i<=registros)
    {
        if(strcmp(Votantes[i].codigo, cedulaElim) != 0)
        {
            strcpy(VotantesT[j].codigo, Votantes[i].codigo);
            strcpy(VotantesT[j].nombre, Votantes[i].nombre);
            strcpy(VotantesT[j].clave, Votantes[i].clave);
            VotantesT[j].tipo = Votantes[i].tipo;
            VotantesT[j].voto = Votantes[i].voto;
            fwrite(&VotantesT[j], sizeof(struct Votante), 1, temporal);
            j++;
        }
        else{
            registros--;
            modificarCantidadRegistros(registros);
        }
        i++;
    }

    fclose(archivo);
    fclose(temporal);
    remove("files//Votantes.txt");
    rename("files//temporal.txt", "files//Votantes.txt");
}

void ConsultarVotantes() //Opción del administrador para consultar los datos de los votantes
{
    system("CLS");
    int i=0;
    FILE *archivo = fopen("files//Votantes.txt", "r");
    struct Votante Votantes;
    if(registros==0){
        printf("No hay ning%cn votante registrado\n", 163);
    }
    else{
    while(fread(&Votantes, sizeof(struct Votante), 1, archivo) == 1 && i<registros)
    {
        printf("Nombre: %s\n", Votantes.nombre);
        printf("C%cdigo: %s\n", 162, Votantes.codigo);
        printf("Clave: %s\n", Votantes.clave);
        printf("Tipo: ");
        switch(Votantes.tipo)
        {
            case 1:
                printf(AZUL_T "1 - Estudiante\n" RESET_COLOR);
            break;

            case 2:
                printf(ROJO_T "2 - Egresado\n" RESET_COLOR);
            break;

            case 3:
                printf(NEGRO_T "3 - Docente\n" RESET_COLOR);
            break;
            
            case 4:
                printf(VERDE_T "4 - Administrativo\n" RESET_COLOR);
            break;
        }
        if(Votantes.voto)
        {
            printf("Ya vot%c.\n", 162);
        }
        else{
            printf("No ha votado.\n");
        }
        i++;
        printf("\n");
    }
    }
    fclose(archivo);
}

void Votacion(int tipo)
{
    FILE *archivo = fopen("Candidatos.txt", "r+");
    struct Candidato Candidatos[6];
    int n = fread(Candidatos, sizeof(struct Candidato), 6, archivo);
    int op;
    printf("Bienvenido ");
    switch(tipo)
    {
        case 1:
            printf(AZUL_T "Estudiante\n" RESET_COLOR);
        break;

        case 2:
            printf(ROJO_T "Egresado\n" RESET_COLOR);
        break;

        case 3:
            printf(NEGRO_T "Docente\n" RESET_COLOR);
        break;

        case 4:
            printf(VERDE_T "Administrativo\n" RESET_COLOR);
        break;
    }
    do{
    printf ("Ingrese su candidato a votar:\n");
    printf (NEGRO_T "1)LUIS FERNANDO GAVIRIA TRUJILLO\n" VERDE_T "2)CARLOS ALFONSO VICTORIA MENA\n" AMARILLO_T "3)GIOVANNI ARIAS\n" MAGENTA_T "4)JUAN CARLOS GUTIERREZ ARIAS\n" CYAN_T "5)ALEXANDER MOLINA CABRERA\n" BLANCO_T "6)VOTO EN BLANCO\n" RESET_COLOR);
    scanf("%d", &op);
    if(op<1 || op>6)
    {
        printf(ROJO_T "Opci%cn inv%clida.\n", 162, 160);
    };
    }while(op<1 || op>6);
    printf(ROJO_T "Si desea cancelar ingrese '0'. Para confirmar presione cualquier otra tecla\n" RESET_COLOR);
    getchar();
    char c = getchar();
    if(c == '0')
    {
        printf(ROJO_T "Cancelado.\n" RESET_COLOR);
        printf(". ");
        Sleep(1000);
        printf(". ");
        Sleep(1000);
        printf(".");
        Sleep(1000);
        system("CLS");
        Menu();
    }
    else
    {
        switch(tipo)
        {
            case 1:
                Candidatos[op-1].votos.votosEstudiantes = Candidatos[op-1].votos.votosEstudiantes + 1;
            break;

            case 2:
                Candidatos[op-1].votos.votosEgresados = Candidatos[op-1].votos.votosEgresados + 1;
            break;

            case 3:
                Candidatos[op-1].votos.votosDocentes = Candidatos[op-1].votos.votosDocentes + 1;
            break;

            case 4:
                Candidatos[op-1].votos.votosAdministrativos = Candidatos[op-1].votos.votosAdministrativos + 1;
            break;
        }
    }

    FILE *archivoS = fopen("CandidatosNuevo.txt", "w");
    fwrite(Candidatos, sizeof(struct Candidato), n, archivoS);
    fclose(archivoS);
    fclose(archivo);

    if(remove("Candidatos.txt") != 0)
    {
        printf(ROJO_T "ErrorE.\n" RESET_COLOR);
    };
    Sleep(1);
    if(rename("CandidatosNuevo.txt", "Candidatos.txt") != 0)
    {
        printf(ROJO_T "ErrorR.\n" RESET_COLOR);
    };
}

void InicioVotante()
{
    system("CLS");
    fflush(stdin);
    printf(AZUL_T "Inicio como Votante\n" RESET_COLOR);
    bool credencia = false;
    int i;
    char codigo[12], clave[11];    
    printf(RESET_COLOR "Ingrese su c%cdigo: ", 162);
    gets(codigo);
    printf("Ingrese su clave: ");
    gets(clave);

    struct Votante Votantes[registros];
    FILE *archivo = fopen("files//Votantes.txt", "r");
    
    if(fread(&Votantes, sizeof(struct Votante), registros, archivo) == registros)
    {
    for(i=0;i<registros;i++)
    {
        if(strcmp(codigo, Votantes[i].codigo)==0 && strcmp(clave, Votantes[i].clave)==0)
        {
            if(Votantes[i].voto)
            {
                printf(ROJO_T "Ya has votado.\n");
                printf(". ");
                Sleep(1000);
                printf(". ");
                Sleep(1000);
                printf("." RESET_COLOR);
                Sleep(1000);
                break;
            }
            else{
                system("CLS");
                Votacion(Votantes[i].tipo);
                credencia = true;
                break;
            }
        };
    }
    fclose(archivo);
    if(!credencia)
    {
        printf(ROJO_T "Clave o c%cdigo incorrectos.\n", 162);
        printf(". ");
        Sleep(1000);
        printf(". ");
        Sleep(1000);
        printf("." RESET_COLOR);
        Sleep(1000);
        system("CLS");
        Menu();
    }
    };
}

void ConsultarVotosESpecificos()
{
    //Opción del administrador para consultar cuantos votos lleva un candidato especifico
}

void HistogramaEstudiantes(){
    float votos1 = 1378;
    float votos2 = 1086;
    float votos3 = 33;
    float votos4 = 5541;
    float votos5 = 52;
    float votos6 = 453;
    float votosTOT = votos1 + votos2 + votos3 + votos4 + votos5 + votos6;

    printf ("\nLUIS FERNANDO GAVIRIA TRUJILLO: ");
    for (int i = 1; i < votos1; i++){
        if (i % 50 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos1 / votosTOT) * 100);
    printf ("\nCARLOS ALFONSO VICTORIA MENA:   ");
    for (int i = 1; i < votos2; i++){
        if (i % 50 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos2 / votosTOT) * 100);
    printf ("\nGIOVANNI ARIAS:                 ");
    for (int i = 1; i < votos3; i++){
        if (i % 50 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos3 / votosTOT) * 100);
    printf ("\nALEXANDER MOLINA CABRERA:       ");
    for (int i = 1; i < votos4; i++){
        if (i % 50 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos4 / votosTOT) * 100);
    printf ("\nJUAN CARLOS GUTIERREZ ARIAS:    ");
    for (int i = 1; i < votos5; i++){
        if (i % 50 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos5 / votosTOT) * 100);
    printf ("\nVOTO EN BLANCO:                 ");
    for (int i = 1; i < votos6; i++){
        if (i % 50 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos6 / votosTOT) * 100);
    printf ("\nVOTOS TOTALES: %.0f\n", votosTOT);
}

void HistogramaEgresados(){
    float votos1 = 1913;
    float votos2 = 493;
    float votos3 = 26;
    float votos4 = 3371;
    float votos5 = 40;
    float votos6 = 105;
    float votosTOT = votos1 + votos2 + votos3 + votos4 + votos5 + votos6;

    printf ("\nLUIS FERNANDO GAVIRIA TRUJILLO: ");
    for (int i = 1; i < votos1; i++){
        if (i % 50 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos1 / votosTOT) * 100);
    printf ("\nCARLOS ALFONSO VICTORIA MENA:   ");
    for (int i = 1; i < votos2; i++){
        if (i % 50 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos2 / votosTOT) * 100);
    printf ("\nGIOVANNI ARIAS:                 ");
    for (int i = 1; i < votos3; i++){
        if (i % 50 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos3 / votosTOT) * 100);
    printf ("\nALEXANDER MOLINA CABRERA:       ");
    for (int i = 1; i < votos4; i++){
        if (i % 50 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos4 / votosTOT) * 100);
    printf ("\nJUAN CARLOS GUTIERREZ ARIAS:    ");
    for (int i = 1; i < votos5; i++){
        if (i % 50 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos5 / votosTOT) * 100);
    printf ("\nVOTO EN BLANCO:                 ");
    for (int i = 1; i < votos6; i++){
        if (i % 50 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos6 / votosTOT) * 100);
    printf ("\nVOTOS TOTALES: %.0f\n", votosTOT);
}

void HistogramaAdministrativos(){
    float votos1 = 235;
    float votos2 = 13;
    float votos3 = 3;
    float votos4 = 156;
    float votos5 = 0;
    float votos6 = 6;
    float votosTOT = votos1 + votos2 + votos3 + votos4 + votos5 + votos6;

    printf ("\nLUIS FERNANDO GAVIRIA TRUJILLO: ");
    for (int i = 1; i < votos1; i++){
        if (i % 10 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos1 / votosTOT) * 100);
    printf ("\nCARLOS ALFONSO VICTORIA MENA:   ");
    for (int i = 1; i < votos2; i++){
        if (i % 10 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos2 / votosTOT) * 100);
    printf ("\nGIOVANNI ARIAS:                 ");
    for (int i = 1; i < votos3; i++){
        if (i % 10 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos3 / votosTOT) * 100);
    printf ("\nALEXANDER MOLINA CABRERA:       ");
    for (int i = 1; i < votos4; i++){
        if (i % 10 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos4 / votosTOT) * 100);
    printf ("\nJUAN CARLOS GUTIERREZ ARIAS:    ");
    for (int i = 1; i < votos5; i++){
        if (i % 10 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos5 / votosTOT) * 100);
    printf ("\nVOTO EN BLANCO:                 ");
    for (int i = 1; i < votos6; i++){
        if (i % 10 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos6 / votosTOT) * 100);
    printf ("\nVOTOS TOTALES: %.0f\n", votosTOT);
}

void HistogramaDocentes(){
    float votos1 = 254;
    float votos2 = 29;
    float votos3 = 0;
    float votos4 = 179;
    float votos5 = 0;
    float votos6 = 13;
    float votosTOT = votos1 + votos2 + votos3 + votos4 + votos5 + votos6;

    printf ("\nLUIS FERNANDO GAVIRIA TRUJILLO: ");
    for (int i = 1; i < votos1; i++){
        if (i % 10 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos1 / votosTOT) * 100);
    printf ("\nCARLOS ALFONSO VICTORIA MENA:   ");
    for (int i = 1; i < votos2; i++){
        if (i % 10 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos2 / votosTOT) * 100);
    printf ("\nGIOVANNI ARIAS:                 ");
    for (int i = 1; i < votos3; i++){
        if (i % 10 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos3 / votosTOT) * 100);
    printf ("\nALEXANDER MOLINA CABRERA:       ");
    for (int i = 1; i < votos4; i++){
        if (i % 10 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos4 / votosTOT) * 100);
    printf ("\nJUAN CARLOS GUTIERREZ ARIAS:    ");
    for (int i = 1; i < votos5; i++){
        if (i % 10 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos5 / votosTOT) * 100);
    printf ("\nVOTO EN BLANCO:                 ");
    for (int i = 1; i < votos6; i++){
        if (i % 10 == 0){
            printf ("=");
        }
    }
    printf("| %.2f%%", (votos6 / votosTOT) * 100);
    printf ("\nVOTOS TOTALES: %.0f\n", votosTOT);
}

void Tabla(){
    float votos1D = 254;
    float votos2D = 29;
    float votos3D = 0;
    float votos4D = 179;
    float votos5D = 0;
    float votos6D = 13;
    float votosTOTD = votos1D + votos2D + votos3D + votos4D + votos5D + votos6D;  

    
    float votos1ES = 1378;
    float votos2ES = 1086;
    float votos3ES = 33;
    float votos4ES = 5541;
    float votos5ES = 52;
    float votos6ES = 453;
    float votosTOTES = votos1ES + votos2ES + votos3ES + votos4ES + votos5ES + votos6ES;


    float votos1EG = 1913;
    float votos2EG = 493;
    float votos3EG = 26;
    float votos4EG = 3371;
    float votos5EG = 40;
    float votos6EG = 105;
    float votosTOTEG = votos1EG + votos2EG + votos3EG + votos4EG + votos5EG + votos6EG;


    float votos1A = 235;
    float votos2A = 13;
    float votos3A = 3;
    float votos4A = 156;
    float votos5A = 0;
    float votos6A = 6;
    float votosTOTA = votos1A + votos2A + votos3A + votos4A + votos5A + votos6A;

// valores: docentes 40%, estudiantes 35%, admin 10%, egresados 15%
 //GAVIRIA
    float porcentajeGAD = (votos1D / votosTOTD) * 100;
    float porcentajeGAES = (votos1ES / votosTOTES) * 100;
    float porcentajeGAEG = (votos1EG / votosTOTEG) * 100;
    float porcentajeGAA = (votos1A / votosTOTA) * 100;

    float ponderadoGA = (porcentajeGAD * 0.4) + (porcentajeGAES * 0.35) + (porcentajeGAEG * 0.15) + (porcentajeGAA * 0.1);
 //VICTORIA
    float porcentajeVID = (votos2D / votosTOTD) * 100;
    float porcentajeVIES = (votos2ES / votosTOTES) * 100;
    float porcentajeVIEG = (votos2EG / votosTOTEG) * 100;
    float porcentajeVIA = (votos2A / votosTOTA) * 100;

    float ponderadoVI = (porcentajeVID * 0.4) + (porcentajeVIES * 0.35) + (porcentajeVIEG * 0.15) + (porcentajeVIA * 0.1);
 //GIOVANNI
    float porcentajeGID = (votos3D / votosTOTD) * 100;
    float porcentajeGIES = (votos3ES / votosTOTES) * 100;
    float porcentajeGIEG = (votos3EG / votosTOTEG) * 100;
    float porcentajeGIA = (votos3A / votosTOTA) * 100;

    float ponderadoGI = (porcentajeGID * 0.4) + (porcentajeGIES * 0.35) + (porcentajeGIEG * 0.15) + (porcentajeGIA * 0.1);
 //MOLINA
    float porcentajeMOD = (votos4D / votosTOTD) * 100;
    float porcentajeMOES = (votos4ES / votosTOTES) * 100;
    float porcentajeMOEG = (votos4EG / votosTOTEG) * 100;
    float porcentajeMOA = (votos4A / votosTOTA) * 100;

    float ponderadoMO = (porcentajeMOD * 0.4) + (porcentajeMOES * 0.35) + (porcentajeMOEG * 0.15) + (porcentajeMOA * 0.1);
 //GUTIERREZ
    float porcentajeGUD = (votos5D / votosTOTD) * 100;
    float porcentajeGUES = (votos5ES / votosTOTES) * 100;
    float porcentajeGUEG = (votos5EG / votosTOTEG) * 100;
    float porcentajeGUA = (votos5A / votosTOTA) * 100;

    float ponderadoGU = (porcentajeGUD * 0.4) + (porcentajeGUES * 0.35) + (porcentajeGUEG * 0.15) + (porcentajeGUA * 0.1);
 //BLANCO
    float porcentajeBLAD = (votos6D / votosTOTD) * 100;
    float porcentajeBLAES = (votos6ES / votosTOTES) * 100;
    float porcentajeBLAEG = (votos6EG / votosTOTEG) * 100;
    float porcentajeBLAA = (votos6A / votosTOTA) * 100;

    float ponderadoBLA = (porcentajeBLAD * 0.4) + (porcentajeBLAES * 0.35) + (porcentajeBLAEG * 0.15) + (porcentajeBLAA * 0.1);

    printf(" -----------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf ("|            CANDIDATOS            |   DOCENTES   |   ESTUDIANTES   |   EGRESADOS   |   ADMINISTRATIVOS   |   TOTAL  NETO   | TOTAL  PONDERADO |\n");
    printf(" -----------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf ("|1. LUIS FERNANDO GAVIRIA TRUJILLO |    %6.0f    |      %6.0f     |     %6.0f    |        %6.0f       |      %6.0f     |      %6.2f%%     |\n", votos1D, votos1ES, votos1EG, votos1A, (votos1A + votos1D + votos1EG + votos1ES), ponderadoGA);
    printf(" -----------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf ("|2. CARLOS ALFONSO VICTORIA MENA   |    %6.0f    |      %6.0f     |     %6.0f    |        %6.0f       |      %6.0f     |      %6.2f%%     |\n", votos2D, votos2ES, votos2EG, votos2A, (votos2A + votos2D + votos2EG + votos2ES), ponderadoVI);
   printf(" -----------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf ("|3. GIOVANNI ARIAS                 |    %6.0f    |      %6.0f     |     %6.0f    |        %6.0f       |      %6.0f     |      %6.2f%%     |\n", votos3D, votos3ES, votos3EG, votos3A, (votos3A + votos3D + votos3EG + votos3ES), ponderadoGI);
   printf(" -----------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf ("|5. ALEXANDER MOLINA CABRERA       |    %6.0f    |      %6.0f     |     %6.0f    |        %6.0f       |      %6.0f     |      %6.2f%%     |\n", votos4D, votos4ES, votos4EG, votos4A, (votos4A + votos4D + votos4EG + votos4ES), ponderadoMO);
   printf(" -----------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf ("|6. JUAN CARLOS GUTIERREZ ARIAS    |    %6.0f    |      %6.0f     |     %6.0f    |        %6.0f       |      %6.0f     |      %6.2f%%     |\n", votos5D, votos5ES, votos5EG, votos5A, (votos5A + votos5D + votos5EG + votos5ES), ponderadoGU);
   printf(" -----------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf ("|6. VOTO EN BLANCO                 |    %6.0f    |      %6.0f     |     %6.0f    |        %6.0f       |      %6.0f     |      %6.2f%%     |\n", votos6D, votos6ES, votos6EG, votos6A, (votos6A + votos6D + votos6EG + votos6ES), ponderadoBLA);
   printf(" -----------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf ("|   TOTAL VOTOS ESTAMENTO          |    %6.0f    |      %6.0f     |     %6.0f    |        %6.0f       |      %6.0f     |      %6.f%%     |\n", votosTOTD, votosTOTES, votosTOTEG, votosTOTA, (votosTOTA + votosTOTD + votosTOTEG + votosTOTES), 100.0);
   printf(" -----------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void InicioAdministrador(){
    system("CLS");
    fflush(stdin);
    printf(ROJO_T "Inicio como Administrador\n" RESET_COLOR);
    bool credencia = false;
    int i;
    char codigo[12], clave[100];    
    printf("Ingrese su c%cdigo: ", 162);
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
        printf("Clave o c%cdigo incorrectos.\n", 162);
        printf(". ");
        Sleep(1000);
        printf(". ");
        Sleep(1000);
        printf(".");
        Sleep(1000);
        system("CLS");
        Menu();
    }
}
void Instrucciones(){
    printf ("Inicio de Sesi%cn:\nIngresa tu n%cmero de identificaci%cn personal cuando se te solicite.\n\nContrase%ca:\nUtiliza la contrase%ca que te ha proporcionado el administrador. Si no la tienes, ponte en contacto con el administrador antes de continuar.\n\nSelecciona tus Opciones:\nLee cuidadosamente las opciones de voto en la pantalla y elige a tu candidato favorito.\n\nConfirma tu Voto:\nAntes de confirmar, verifica que tus selecciones sean correctas. Una vez confirmado, no se pueden realizar cambios.\n\nFinaliza el Proceso:\nDespu%cs de confirmar tu voto, el sistema registrar%c tu elecci%cn.\n", 162, 163, 162, 164, 164, 130, 160, 162);
    system("PAUSE");
    system("CLS");
    Menu();
}
void Menu(){
    int opci;
    printf(RESET_COLOR "BIENVENIDO AL SISTEMA DE VOTACI%cN PARA CONSULTA SOBRE " ROJO_T "NUEVO RECTOR UTP\n", 162);
    printf (AZUL_T "1)Iniciar como Votante\n" AMARILLO_T "2) Revisar Instrucciones de votaci%cn\n" ROJO_T "3)Iniciar como Administrador\n" NEGRO_T "0)Salir\n" RESET_COLOR "Su opci%cn: ", 162, 162);
    scanf ("%d", &opci);
    switch(opci){
        case 1:
        InicioVotante(); 
        break;
        case 2:
        Instrucciones();
        break;
        case 3:
        InicioAdministrador();
        break;
    }
}
    
void MenuAdmin(int admin){
    system("CLS");
    printf(RESET_COLOR "BIENVENIDO " ROJO_T "%s\n" RESET_COLOR, admins[admin].nombre);
    printf("Ingrese lo que desea realizar:\n");
    int opc;
    printf("1) Registrar votante\n2) Eliminar datos de votante\n3) Consultar datos de los votantes\n4) Consultas\n5) Finalizar (ESTO CIERRA LOS VOTOS)\n" ROJO_T "6) Salir.\n" RESET_COLOR "Su opci%cn: ", 162);
    scanf("%d", &opc);
    switch (opc)
    {
    case 1:
    RegistrarVotante();
    system("CLS");
    printf(VERDE_T "Registrado con Exito.\n");
    printf(". ");
    Sleep(1000);
    printf(". ");
    Sleep(1000);
    printf(".");
    Sleep(1000);
    MenuAdmin(admin);
        break;
    case 2:
    EliminarVotante();
    system("CLS");
    printf(VERDE_T "Finalizado con Exito.\n");
    printf(". ");
    Sleep(1000);
    printf(". ");
    Sleep(1000);
    printf(".");
    Sleep(1000);
    MenuAdmin(admin);
        break;
    case 3:
    ConsultarVotantes();
    fflush(stdin);
    printf("\nPulse una tecla para continuar.");
    getchar();
    system("CLS");
    MenuAdmin(admin);
        break;
    case 4:
    MenuConsultas();
    MenuAdmin(admin);
        break;
    case 6: 
    system("CLS");
    Menu();
        break;
    default:
    printf(ROJO_T "opci%cn no v%clida", 162, 160);
    Sleep(3000);
    system("Clear");
    MenuAdmin(admin);
        break;
    }
}

void MenuHistograma(){
    int opc;
    printf ("Ingrese el histograma que desee ver:\n");
    printf ("1) Estudiantes\n2) Egresados\n3) Docentes\n4) Administrativos\nSu opci%cn: ",162);
    scanf ("%d", &opc);
    switch (opc)
    {
    case 1:
        system("CLS");
        HistogramaEstudiantes();
        fflush(stdin);
        printf("\nPulse una tecla para continuar.");
        getchar();
        break;
    case 2:
        system("CLS");
        HistogramaEgresados();
        fflush(stdin);
        printf("\nPulse una tecla para continuar.");
        getchar();
        break;
    case 3:
        system("CLS");
        HistogramaDocentes();
        fflush(stdin);
        printf("\nPulse una tecla para continuar.");
        getchar();
        break;
    case 4:
        system("CLS");
        HistogramaAdministrativos();
        fflush(stdin);
        printf("\nPulse una tecla para continuar.");
        getchar();
        break;
    default:
    printf ("opci%cn no valida.", 162);
    Sleep(3000);
    system("CLS");
        break;
    }
}

void MenuConsultas(){
    system("CLS");
    do{
    printf(RESET_COLOR "Ingrese lo que desee ver: ");
    printf("\n1) Tabla de datos\n2) Histograma de frecuencia de votos\n3) Salir\nSu opci%cn: ", 162);
    int opc;
    scanf ("%d", &opc);
    switch (opc)
    {
        case 1:
        system("CLS");
        Tabla();
        fflush(stdin);
        printf("\nPulse una tecla para continuar.");
        getchar();
        break;

        case 2:
        system("CLS");
        MenuHistograma();        
        break;

        case 3:
        system("CLS");
        break;

        default:
        printf("Opci%cn no v%clida.\n", 162, 160);
        break;
    }
    } while (0);
}

int main(){
    srand(time(NULL));
    registros = registro();
    system("CLS");
    //printf("%d\n", registros);
    Instrucciones();
}