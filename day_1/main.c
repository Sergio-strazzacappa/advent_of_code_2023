#include <stdio.h>
#define ARCHIVO "input.txt"

int guardar_digito(int digito, int* primer_digito, int* ultimo_digito) {
    if (*primer_digito == -1) {
        *primer_digito = digito;
    }
    *ultimo_digito = digito;
    
    return 0;
}

int solve(char* linea, int* suma) {
    int primer_digito = -1;
    int ultimo_digito = -1;
    int i = 0;
    int digito = -1;
    
    while (linea[i]) {
        // ONE
        if ((linea[i] == 'o') && (linea[i + 1] == 'n')  &&
            (linea[i + 2] == 'e')) {
            digito = 1;
            guardar_digito(digito, &primer_digito, &ultimo_digito);
            i++;
            continue;
        }

        // TWO
        if ((linea[i] == 't') && (linea[i + 1] == 'w') &&
            (linea[i + 2] == 'o')) {
            digito = 2;
            guardar_digito(digito, &primer_digito, &ultimo_digito);
            i++;
            continue;
        }

        // THREE
        if ((linea[i] == 't') && (linea[i + 1] == 'h') &&
            (linea[i + 2] == 'r') && (linea[i + 3] == 'e' &&
            linea[i + 4] == 'e')) {
            digito = 3;
            guardar_digito(digito, &primer_digito, &ultimo_digito);
            i++;
            continue;
        }

        // FOUR
        if ((linea[i] == 'f') && (linea[i + 1] == 'o') &&
            (linea[i + 2] == 'u') && (linea[i + 3] == 'r')) {
            digito = 4;
            guardar_digito(digito, &primer_digito, &ultimo_digito);
            i++;
            continue;
        }

        // FIVE
        if ((linea[i] == 'f') && (linea[i + 1] == 'i') &&
            (linea[i + 2] == 'v') && (linea[i + 3] == 'e')) {
            digito = 5;
            guardar_digito(digito, &primer_digito, &ultimo_digito);
            i++;
            continue;
        }
        
        // SIX
        if ((linea[i] == 's') && (linea[i + 1] == 'i') &&
            (linea[i + 2] == 'x')) {
            digito = 6;
            guardar_digito(digito, &primer_digito, &ultimo_digito);
            i++;
            continue;
        }

        // SEVEN
        if ((linea[i] == 's') && (linea[i + 1] == 'e') &&
            (linea[i + 2] == 'v') && (linea[i + 3] == 'e' &&
            linea[i + 4] == 'n')) {
            digito = 7;
            guardar_digito(digito, &primer_digito, &ultimo_digito);
            i++;
            continue;
        }

        // EIGHT
        if ((linea[i] == 'e') && (linea[i + 1] == 'i') &&
            (linea[i + 2] == 'g') && (linea[i + 3] == 'h' &&
            linea[i + 4] == 't')) {
            digito = 8;
            guardar_digito(digito, &primer_digito, &ultimo_digito);
            i++;
            continue;
        }

        // NINE
        if ((linea[i] == 'n') && (linea[i + 1] == 'i') &&
            (linea[i + 2] == 'n') && (linea[i + 3] == 'e')) {
            digito = 9;
            guardar_digito(digito, &primer_digito, &ultimo_digito);
            i++;
            continue;
        }

        digito = linea[i] - '0';
          
        if (digito >= 0 && digito <= 9) {
            guardar_digito(digito, &primer_digito, &ultimo_digito);
        }
        i++;
    }
    
    *suma = *suma + primer_digito * 10 + ultimo_digito;

    return 0;
}

int main() {
    int suma = 0;

    FILE *fptr;
    fptr = fopen(ARCHIVO, "r");

    char linea[100];
    while (fgets(linea, 100, fptr)) {
        solve(linea, &suma);
    }

    printf("%s%i\n", "Respuesta final = ", suma);

    fclose(fptr);

    return 0;
}
