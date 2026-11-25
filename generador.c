#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para generar un archivo con características específicas
void generar_archivo(const char* nombre, int cantidad, int tipo) {
    FILE *archivo = fopen(nombre, "w");
    if (archivo == NULL) {
        printf("Error al crear %s\n", nombre);
        return;
    }

    // Escribir la cantidad total de registros en la primera línea
    fprintf(archivo, "%d\n", cantidad);

    int *valores = (int*)malloc(cantidad * sizeof(int));
    
    for (int i = 0; i < cantidad; i++) {
        if (tipo == 0 || tipo == 2) {
            valores[i] = i * 10; // Ya ordenado (rango amplio)
        } else if (tipo == 1) {
            valores[i] = (cantidad - i) * 10; // Orden inverso
        } else {
            valores[i] = rand() % 50; // Duplicados asegurados (rango estrecho 0-49)
        }
    }

    // Si es "casi ordenado", intercambiamos el 5% de los elementos
    if (tipo == 2) {
        int intercambios = cantidad * 0.05;
        for (int i = 0; i < intercambios; i++) {
            int idx1 = rand() % cantidad;
            int idx2 = rand() % cantidad;
            int temp = valores[idx1];
            valores[idx1] = valores[idx2];
            valores[idx2] = temp;
        }
    }

    // Escribir al archivo: "original_id value"
    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%d %d\n", i, valores[i]);
    }

    free(valores);
    fclose(archivo);
    printf("Generado exitosamente: %s\n", nombre);
}

int main() {
    // 1. "Documented seed": Semilla fija en 42 para entradas reproducibles
    srand(42); 

    // 2. "Required dataset sizes"
    int tamanos[] = {50, 5000, 50000, 500000};
    const char* nombres[] = {"small", "medium", "large", "very_large"};

    printf("Iniciando generacion de datasets...\n");

    for (int i = 0; i < 4; i++) {
        char nombre_archivo[100];
        
        // 3. "already sorted file"
        sprintf(nombre_archivo, "dataset_%s_sorted.txt", nombres[i]);
        generar_archivo(nombre_archivo, tamanos[i], 0);

        // 4. "reverse-ordered file"
        sprintf(nombre_archivo, "dataset_%s_reverse.txt", nombres[i]);
        generar_archivo(nombre_archivo, tamanos[i], 1);

        // 5. "nearly sorted file"
        sprintf(nombre_archivo, "dataset_%s_nearly.txt", nombres[i]);
        generar_archivo(nombre_archivo, tamanos[i], 2);

        // 6. "file with duplicates (narrow range)"
        sprintf(nombre_archivo, "dataset_%s_duplicates.txt", nombres[i]);
        generar_archivo(nombre_archivo, tamanos[i], 3);
    }

    // 7. "Use a file containing 0 as a separate correctness test"
    FILE *vacio = fopen("dataset_empty.txt", "w");
    if (vacio != NULL) {
        fprintf(vacio, "0\n");
        fclose(vacio);
        printf("Generado exitosamente: dataset_empty.txt\n");
    }

    printf("Todos los archivos fueron creados!\n");
    return 0;
}