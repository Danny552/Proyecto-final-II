#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h>

// Define a structure to store student information
struct Alumno {
    int matricula;
};

// Function to create a new file to store student records
// Function to add multiple student records to the file
void Llenar() {
    system("CLS");
    FILE *archdisco;
    struct Alumno alumno;
    int i;

    // Use "ab" mode to open the file for appending in binary mode
    archdisco = fopen("files\\cedulas.txt", "ab");
    
    if (archdisco == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    for (i = 0; i < 5; i++) {
        printf("Enter matricula #%d: ", i + 1);
        scanf("%d", &alumno.matricula);

        // Use sizeof(int) instead of 1 in fwrite
        fwrite(&alumno, sizeof(int), 1, archdisco);
    }

    fclose(archdisco);
    printf("Students inserted.\n");
}

// Function to visualize all matriculas stored in the file
void Visualizar() {
    system("CLS");
    FILE *archdisco;
    struct Alumno alumno;

    // Use "rb" mode to open the file for reading in binary mode
    archdisco = fopen("files\\cedulas.txt", "rb");
    
    if (archdisco == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    printf("Matriculas stored in the file:\n");

    while (fread(&alumno, sizeof(int), 1, archdisco) == 1) {
        printf("%d\n", alumno.matricula);
    }

    fclose(archdisco);
}

int main() {
    Llenar();
    Visualizar();

    return 0;
}
