#include <stdio.h> 
#include <stdlib.h> 
#include <io.h>
#include <conio.h>
#include <string.h>

// Define una estructura para almacenar información de estudiantes
struct Alumno {
    int matricula;
};

// Función para crear un nuevo archivo para almacenar registros de estudiantes
void Crear() {
    system("CLS");
    FILE *archdisco;

    archdisco = fopen("files\\cedulas.txt", "w");
    
    if (archdisco == NULL) {
        printf("Error al crear el archivo.\n");
        return;
    }
    
    fclose(archdisco);
    printf("Archivo creado.\n");
}

// Función para agregar un nuevo registro de estudiante al archivo
void Llenar() {
    system("CLS");
    FILE *archdisco;
    struct Alumno alumno;

    archdisco = fopen("files\\cedulas.txt", "ab");
    
    if (archdisco == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    printf("Ingrese matrícula: ");
    scanf("%d", &alumno.matricula);
    fwrite(&alumno, sizeof(alumno), 1, archdisco);
    fclose(archdisco);
    printf("Estudiante insertado.\n");
}

// Función para mostrar todos los registros de estudiantes en el archivo
void Mostrar() {
    system("CLS");
    FILE *archdisco;
    struct Alumno alumno;

    archdisco = fopen("files\\cedulas.txt", "rb");
    
    if (archdisco == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    while (fread(&alumno, sizeof(alumno), 1, archdisco) == 1) {
        printf("Matrícula: %d\n", alumno.matricula);
        printf("\n");
    }

    fclose(archdisco);
}

// Función para buscar un registro de estudiante por matrícula
void Buscar() {
    FILE *archdisco;
    struct Alumno alumno;
    int a, c = 0;

    archdisco = fopen("files\\cedulas.txt", "rb");

    if (archdisco == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    printf("Ingrese la matrícula a buscar: ");
    scanf("%d", &a);

    while (fread(&alumno, sizeof(alumno), 1, archdisco) == 1) {
        if (alumno.matricula == a) {
            printf("Matrícula: %d\n", alumno.matricula);
            printf("\n");
            c++;
        }
    }

    fclose(archdisco);

    if (c == 0) {
        printf("No se encontraron registros coincidentes.\n");
    }
}

//función para borrar registros de estudiantes
void borrarRegistro() {
struct Alumno alumno;
int clave;
printf ("Ingrese la matrícula del alumno que desee eliminar");
scanf("%d",&clave); getchar();
FILE *arch1; FILE *arch2;
arch1 = fopen("files\\cedulas.txt","r+"); arch2 = fopen("C:\\Users\\danie\\Desktop\\UNI\\SEMESTRE II\\Progra II\\progra-2\\Trabajos\\archivo\\temp.txt","at+");
// aqui siempre debe empezar el ciclo de lectura // y fread() regresa siempre cuantas estructuras leyo
while(fread(&alumno,sizeof(alumno),1,arch1)==1)
{
if (clave != alumno.matricula)
fwrite(& alumno,sizeof(alumno),1,arch2);
}; // aqui termina while
//cerrando archivos
fclose(arch1);
fclose(arch2);
//removiendo y renombrando archivos
// recordar que directorios y archivos de datos no // mas de 8.3 letras
remove("files\\cedulas.txt");
rename("C:\\Users\\danie\\Desktop\\UNI\\SEMESTRE II\\Progra II\\progra-2\\Trabajos\\archivo\\temp.txt", "files\\cedulas.txt");
//avisando
puts("registro eliminado");
};

int main() {
    int op;

    do {
        printf("\n\t\tMenú\n");
        printf("0. Salir\n1. Crear Archivo\n2. Llenar Datos\n3. Mostrar\n4. Buscar por Matrícula\n5. Mostrar Estudiantes Mayores\n6. Eliminar registro\n");
        printf("Ingrese opción: ");
        scanf("%d", &op);
        printf("\n");

        switch (op) {
            case 1:
                Crear();
                break;
            case 2:
                Llenar();
                break;
            case 3:
                Mostrar();
                break;
            case 4:
                Buscar();
                break;
            case 6:
                borrarRegistro();
                break;
        }
    } while (op != 0);

    return 0;
}
