#include <stdio.h>

#define ARCHIVO          "input.txt"
#define TAMANIO_LINEA    ((116) + 2) // 116
#define CANT_MY_NUM      (25) // 25
#define CANT_WINNING_NUM (10) // 10
#define CANT_TARJETAS    (212) // 212

typedef struct Tarjeta {
    int numero;
    int mis_numeros[CANT_MY_NUM];
    int ganadores[CANT_WINNING_NUM];
} Tarjeta;

int my_numbers[CANT_MY_NUM];
int winning_numbers[CANT_WINNING_NUM];
Tarjeta tarjetas[CANT_TARJETAS];
int cant_todo = 0;
int todo[9800000];

void mostrar_tarjeta(Tarjeta t) {
    printf("Tarjeta: %d\n", t.numero);
    
    printf("GAN: [ ");
    for (int i = 0; i < CANT_WINNING_NUM; i++) {
        printf("%d ", t.ganadores[i]);
    }

    printf("]\n");
    
    printf("MIS: [ ");
    for (int i = 0; i < CANT_MY_NUM; i++) {
        printf("%d ", t.mis_numeros[i]);
    }
    printf("]\n");
}

void mostrar_numeros() {
    printf("GAN: [ ");
    for (int i = 0; i < CANT_WINNING_NUM; i++) {
        printf("%d ", winning_numbers[i]);
    }

    printf("]\n");
    
    printf("MIS: [ ");
    for (int i = 0; i < CANT_MY_NUM; i++) {
        printf("%d ", my_numbers[i]);
    }
    printf("]\n");
}

void copiar() {
    for (int i = 0; i < CANT_TARJETAS; i++) {
        int cantidad = 0;
        for (int j = 0; j < CANT_MY_NUM; j++) {
            for (int k = 0; k < CANT_WINNING_NUM; k++) {
                if (tarjetas[i].mis_numeros[j] == tarjetas[i].ganadores[k]) {
                    cantidad++;
                    break;
                }
            }
        }
        for (int j = 1; j <= cantidad; j++) {
            todo[j - 1] = i + 1 + j;
        }
    }
}

// Calcula la cantidad de matches que hay entre my_numbers
// y winning_numbers
int match(int my_numbers[], int winning_numbers[]) {
    int cantidad = 0;

    for (int i = 0; i < CANT_MY_NUM; i++) {
        for (int j = 0; j < CANT_WINNING_NUM; j++) {
            if (my_numbers[i] == winning_numbers[j]) {
                cantidad++;
                break;
            }
        }
    }
    return cantidad;
}

// Crea dos arreglos: my_numbers y winning_numbers
// con los datos leídos del archivo de entrada
void get_numbers(char* linea) {
    int columna = 8;
    int numero = -1;
    int cant_digitos = 0;
    int winning_number = 1; // true
    int winning_num_index = 0;
    int my_num_index = 0;

    while (columna < TAMANIO_LINEA) {
        if (linea[columna] - 48 >= 0 && linea[columna] - 48 <= 9) {
            // es un número
            cant_digitos++;
            switch (cant_digitos) {
                case 1:
                    numero = linea[columna] - 48;
                    break;
                case 2:
                case 3:
                    numero *= 10;
                    numero += linea[columna] - 48;
                    break;
            }
        } else if (linea[columna] == ' ') {
            if (numero != -1) {
                // encontró un número
                cant_digitos = 0;
                if (winning_number) {
                    // es winning number
                    winning_numbers[winning_num_index] = numero;
                    winning_num_index++;
                } else {
                    // es my number
                    my_numbers[my_num_index] = numero;
                    my_num_index++;
                }
                numero = -1;
            }
        } else if (linea[columna] == '|' ) {
            winning_number = 0; // false
        }
        columna++;
     }
    my_numbers[my_num_index] = numero;
}

void parte_1(int* suma) {
    int cantidad = match(my_numbers, winning_numbers);
    int puntuacion = 0;

    for (int i = 0; i < cantidad; i++) {
        if (i == 0) {
            puntuacion++;
        } else {
            puntuacion *= 2;
        }
    }
    *suma += puntuacion;
}

void guardar_tarjetas(int* fila) {
    for (int i = 0; i < CANT_MY_NUM; i++) {
        tarjetas[*fila].mis_numeros[i] = my_numbers[i];
    }
    for (int i = 0; i < CANT_WINNING_NUM; i++) {
        tarjetas[*fila].ganadores[i] = winning_numbers[i];
    }
}

void parte_2() {
    for (int i = 0; i < CANT_TARJETAS; i++) {
        todo[i] = i + 1;
        cant_todo++;
    }
    for (int i = 0; i < cant_todo; i++) {
        int card = todo[i];
        int cantidad = match(
                tarjetas[card - 1].mis_numeros,
                tarjetas[card - 1].ganadores);
        for (int j = 0; j < cantidad; j++) {
            todo[cant_todo + j] = tarjetas[card - 1].numero + (j + 1);
        }
        cant_todo += cantidad;
    }
}

int main() {
    int suma = 0;
    int fila = 0;

    FILE *fptr;
    fptr = fopen(ARCHIVO, "r");
    char linea[TAMANIO_LINEA];

    while (fgets(linea, TAMANIO_LINEA, fptr)) {
        get_numbers(linea);
        parte_1(&suma);
        tarjetas[fila].numero = fila + 1;
        guardar_tarjetas(&fila);
        fila++;
    }

    parte_2();

    printf("Respuesta - Parte I: %d\n", suma);
    printf("Respuesta - Parte II: %d\n", cant_todo);

    fclose(fptr);

    return 0;
}
