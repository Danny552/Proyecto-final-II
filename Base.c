#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

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

struct Admin admins[2] = { {"1114150552", "Daniel Alejandro Henao", "odioracket23"} , {"1137059546", "Juan Camilo Cano", "teamoracket32"} };

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
    char codigo[12]; //Documento identidad
    char nTar; //Número en el tarjetón
    struct Votos votos; //Cantidad de votos a favor
};


void RegistrarVotante() //Opción para el administrativo para registrar un votante
{
    getchar();
    FILE *archdisco;
    archdisco = fopen("files//Votantes.txt", "at+");
    printf("Ingrese código del votante a registrar: ");
    gets(Votantes[registros].codigo);

    printf("Ingrese nombre del votante a registrar: ");
    gets(Votantes[registros].nombre);

    char c;
    int i, a;
    for(i=0;i<10;i++)
    {
        do
        {
            a = rand() % 123;
        }while( (a<33) || (a==123) || (a>90 && a<97) || (a>58 && a<63));
        c = a;
        Votantes[registros].clave[i] = c;
    }
    printf("Clave generada exitosamente.\n");

    printf("Ingrese tipo del votante a registrar: ");
    scanf("%d", &Votantes[registros].tipo);

    Votantes[registros].voto = 0;

    fwrite(&Votantes[registros],sizeof(struct Votante),1,archdisco);
    fclose(archdisco);

    registros++;

    modificarCantidadRegistros(registros);
}

void EliminarVotante() //Opción del Admin para eliminar un votante
{
    FILE *archivo = fopen("files//Votantes.txt", "r"); //Entradas
    FILE *temporal = fopen("files//temporal.txt", "w"); //Temporales
    
    char cedulaElim[12];
    printf("Ingrese el código del votante que desea eliminar: ");
    gets(cedulaElim);

    char linea[500];

    while(fgets(linea, sizeof(linea), archivo) != NULL)
    {
        if(strstr(linea, cedulaElim) == NULL)
        {
            fputs(linea, temporal);
        }
    }

    fclose(archivo);
    fclose(temporal);
    remove("archivo.txt");
    rename("temporal.txt", "Votantes.txt");

    registros--;
    modificarCantidadRegistros(registros);
}

void ConsultarVotantes() //Opción del administrador para consultar los datos de los votantes
{
    int i=0;
    FILE *archivo = fopen("files//Votantes.txt", "r");
    struct Votante Votantes;
    if(registros==0){
        printf("No hay ningún votante registrado\n");
    }
    else{
    while(fread(&Votantes, sizeof(struct Votante), 1, archivo) == 1 && i<registros)
    {
        printf("Nombre: %s\n", Votantes.nombre);
        printf("Código: %s\n", Votantes.codigo);
        printf("Clave: %s\n", Votantes.clave);
        printf("Tipo: %d\n", Votantes.tipo);
        if(Votantes.voto)
        {
            printf("Ya votó.\n");
        }
        else{
            printf("No ha votado.\n");
        }
        i++;
    }
    }
    fclose(archivo);
}

int Votacion(int tipo)
{
    int op;
    printf ("Ingrese su candidato a votar:");
    printf ("1)LUIS FERNANDO GAVIRIA TRUJILLO\n2)CARLOS ALFONSO VICTORIA MENA\n3)GIOVANNI ARIAS\n4)ALEXANDER MOLINA CABRERA\n5)JUAN CARLOS GUTIERREZ ARIAS\n6)VOTO EN BLANCO\n");
    scanf("%d", &op);
    printf("Sí desea cancelar ingrese '0'. Para confirmar presione cualquier otra tecla\n");
    char c = getchar();
    if(c == '0')
    {
        return 0;
    }
    else
    {
        switch(tipo)
        {
            case 1:

            break;

            case 2:

            break;

            case 3:

            break;

            case 4:

            break;
        }
    }
}

void InicioVotante()
{
    getchar();
    bool credencia = false;
    int i;
    char codigo[12], clave[11];    
    printf("Ingrese su código: ");
    gets(codigo);
    printf("Ingrese su clave: ");
    gets(clave);

    struct Votante Votantes;
    FILE *archivo = fopen("files//Votantes.txt", "r");
    
    if(fread(&Votantes, sizeof(struct Votante), 1, archivo) == 1)
    {
    for(i=0;i<registros;i++)
    {
        if(strcmp(codigo, Votantes.codigo)==0 && strcmp(clave, Votantes.clave)==0)
        {
            Votacion(Votantes.tipo);
            credencia = true;
            break;
        };
    }
    if(!credencia)
    {
        printf("Clave o código incorrectos.\n");
        Menu();
    }
    };
}

void ConsultarVotosESpecificos()
{
    //Opción del administrador para consultar cuantos votos lleva un candidato especifico
}

void VotoNetoTipo(){
    //La cantidad total por tipo de votante
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
    printf ("\nVOTOS TOTALES: %.0f", votosTOT);
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
    printf ("\nVOTOS TOTALES: %.0f", votosTOT);
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
    printf ("\nVOTOS TOTALES: %.0f", votosTOT);
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
    printf ("\nVOTOS TOTALES: %.0f", votosTOT);
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
        Menu();
    }
}

void MenuVotante();

void Menu(){
    int opc;
    printf ("1) Votante\n2) Administrador\nSu opción: ");
    scanf ("%d", &opc);
    switch(opc){
        case 1:
        InicioVotante(); 
        break;
        case 2:
        InicioAdministrador();
        break;
        }
    }
    
void MenuAdmin(int admin){
    printf("BIENVENIDO %s\n", admins[admin].nombre); //Xd
    printf("Ingrese lo que desea realizar:\n");
    int opc;
    printf("1) Registrar votante\n2)Eliminar datos de votante\n3)Consultar datos de los votantes\n4)Consultas\n5)Finalizar(ESTO CIERRA LOS VOTOS)\n6)Salir.\n");
    scanf("%d", &opc);
    switch (opc)
    {
    case 1:
    RegistrarVotante();
    MenuAdmin(admin);
        break;
    case 2:
    EliminarVotante();
    MenuAdmin(admin);
        break;
    case 3:
    ConsultarVotantes();
    MenuAdmin(admin);
        break;
    case 4:
    MenuConsultas();
    MenuAdmin(admin);
        break;
    case 6: 
    Menu(admin);
        break;
    default:
    printf ("opción no válida");
    Sleep(100);
    system("Clear");
    MenuAdmin(admin);
        break;
    }
}

void MenuHistograma(){
    int opc;
    printf ("Ingrese el histograma que desee ver:\n");
    printf ("1)Estudiantes \n2)Egresados \n3)Docentes \n4)Administrativos ");
    scanf ("%d", &opc);
    switch (opc)
    {
    case 1:
        HistogramaEstudiantes();
        break;
    case 2:
        HistogramaEgresados();
        break;
    case 3:
        HistogramaDocentes();
        break;
    case 4:
        HistogramaAdministrativos();
        break;
    default:
    printf ("opción no valida");
    system("CLS");
        break;
    }
}

void MenuConsultas(){
    do{
    printf("Ingrese lo que desee ver: ");
    printf("\n1)Votos netos\n2)Porcentaje neto de votos\n3)Porcentaje de votos ponderados\n4)Histograma de frecuencia de votos\n");
    int opc;
    scanf ("%d", &opc);
    switch (opc)
    {
        case 1:
    VotoNetoTipo();
    break;
        case 2:
    break;
        case 3:
    break;
        case 4:
    MenuHistograma();
    break;
    default:
    printf("Opción no válida.\n");
        break;
    }
    } while (0);
}

int main(){
    srand(time(NULL));
    registros = registro();
    system("CLS");
    printf("%d\n", registros);
    //Menu();
    Tabla();
}