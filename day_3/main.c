#include <stdio.h>

#define ARCHIVO       "input.txt"
#define TAMANIO_LINEA ((140) + 2)
#define FILAS         (140)
#define COLUMNAS      (140)
#define MAX_NUMEROS   (1500)

typedef struct Numero {
    int valor;
    int fila;
    int columna_inicial;
    int columna_final;
    int cantidad_digitos;
} Numero;

char tabla[FILAS + 2][COLUMNAS + 2];
int cantidad_numeros = 0;
Numero numeros[MAX_NUMEROS];
int suma = 0;

void mostrar_tabla() {
    for (int i = 0; i < FILAS + 2; i++) {
        for (int j = 0; j < COLUMNAS + 2; j++) {
            printf("%c", tabla[i][j]);
        }
        printf("\n");
    }
}

void mostrar_numeros() {
    printf("Cantidad de números: %d\n", cantidad_numeros);
    printf("[\n");
    for (int i = 0; i < cantidad_numeros; i++) {
        printf("{%d, %d, %d, %d, %d}\n", numeros[i].valor, numeros[i].fila, 
            numeros[i].columna_inicial, numeros[i].columna_final, 
            numeros[i].cantidad_digitos);
    }
    printf("]\n");
}

Numero* buscar_numero(int fila, int columna) {
    Numero* n;

    for (int i = 0; i < cantidad_numeros; i++) {
        if ((numeros[i].fila == fila) && 
            (columna >= numeros[i].columna_inicial && 
             columna <= numeros[i].columna_final)) {
            n = &numeros[i];
            break;
        }
    }
    return n;
}

int es_numero(char c) {
    int es_numero = 0;

    if ((c - 48 >= 0 && c - 48 <= 9)) {
        es_numero = 1;
    }
    return es_numero;
}

int adyacencia(int fila, int columna) {
    int cantidad = 0;
    int ratio = -1;
    Numero* n1 = NULL;
    Numero* n2 = NULL;

    // los costados
    if (es_numero(tabla[fila][columna - 1])) {
        cantidad++;
        n1 = buscar_numero(fila, columna - 1);
    }
    if (es_numero(tabla[fila][columna + 1])) {
        cantidad++;
        if (n1 == NULL) {
            n1 = buscar_numero(fila, columna + 1);
        } else {
            n2 = buscar_numero(fila, columna + 1);
        }
    }
    // arriba
    if (es_numero(tabla[fila - 1][columna])) {
        cantidad++;
        if (n1 == NULL) {
            n1 = buscar_numero(fila - 1, columna);
        } else {
            n2 = buscar_numero(fila - 1, columna);
        }
    } else {
        if (es_numero(tabla[fila - 1][columna - 1])) {
            cantidad++;
            if (n1 == NULL) {
                n1 = buscar_numero(fila - 1, columna - 1);
            } else {
                n2 = buscar_numero(fila - 1, columna - 1);
            }
        }
        if (es_numero(tabla[fila - 1][columna + 1])) {
            cantidad++;
            if (n1 == NULL) {
                n1 = buscar_numero(fila - 1, columna + 1);
            } else {
                n2 = buscar_numero(fila - 1, columna + 1);
            }
        }
    }
    // abajo
    if (es_numero(tabla[fila + 1][columna])) {
        cantidad++;
        if (n1 == NULL) {
            n1 = buscar_numero(fila + 1, columna);
        } else {
            n2 = buscar_numero(fila + 1, columna);
        }
    } else {
        if (es_numero(tabla[fila + 1][columna - 1])) {
            cantidad++;
            if (n1 == NULL) {
                n1 = buscar_numero(fila + 1, columna - 1);
            } else {
                n2 = buscar_numero(fila + 1, columna - 1);
            }
        }
        if (es_numero(tabla[fila + 1][columna + 1])){
            cantidad++;
            if (n1 == NULL) {
                n1 = buscar_numero(fila + 1, columna + 1);
            } else {
                n2 = buscar_numero(fila + 1, columna + 1);
            }
        }
    }

    if (cantidad == 2) {
        //printf("[%d, %d]\n", fila, columna);
        //printf("[%d, %d]\n", n1->valor, n2->valor);
        ratio = n1->valor * n2->valor;
        //printf("Ratio = %d\n", ratio);
    }
    return ratio;
}

int calcular_engines() {
    int suma_ratio = 0;
    int ratio = -1;

    for (int i = 1; i < FILAS + 1; i++) {
        for (int j = 1; j < COLUMNAS + 1; j++) {
            if (tabla[i][j] == '*') {
                // es engine
                ratio = adyacencia(i, j);
                if (ratio != -1) {
                    suma_ratio += ratio;
                }
            }
        }
    }
    return suma_ratio;
}

int es_simbolo(char c) {
    int es_simbolo = 1;

    if ((c - 48 >= 0 && c - 48 <= 9) || c == '.' || c == 'A') {
        es_simbolo = 0;
    }
    return es_simbolo;
}

void verificar_numeros() {
    int es_parte = 0;

    for (int i = 0; i < cantidad_numeros; i++) {
        Numero n = numeros[i];
        es_parte = 0;
        
        if (es_simbolo(tabla[n.fila][n.columna_inicial - 1])) {
            es_parte = 1;
        } else if (es_simbolo(tabla[n.fila - 1][n.columna_inicial - 1])) {
            es_parte = 1;
        } else if (es_simbolo(tabla[n.fila + 1][n.columna_inicial - 1])) {
            es_parte = 1;
        } else if (es_simbolo(tabla[n.fila][n.columna_final + 1])) {
            es_parte = 1;
        } else if (es_simbolo(tabla[n.fila - 1][n.columna_final + 1])) {
            es_parte = 1;
        } else if (es_simbolo(tabla[n.fila + 1][n.columna_final + 1])) {
            es_parte = 1;
        } else {
            for (int j = 0; j < n.cantidad_digitos; j++) {
                if (es_simbolo(tabla[n.fila - 1][n.columna_inicial + j])) {
                    es_parte = 1;
                    break;
                }
            }
            for (int j = 0; j < n.cantidad_digitos; j++) {
                if (es_simbolo(tabla[n.fila + 1][n.columna_inicial + j])) {
                    es_parte = 1;
                    break;
                }
            }
        }
        if (es_parte) {
            suma += n.valor;
        }
    }
}

void guardar_numeros(char* linea, int fila) {
    int columna = 0;
    int cantidad_digitos = 0;
    int valor = -1;
    int columna_inicial = 1;

    while (linea[columna]) {
        if (linea[columna] - 48 >= 0 && linea[columna] - 48 <= 9) {
            cantidad_digitos++;
            switch (cantidad_digitos) {
                case 1:
                    valor = linea[columna] - 48;
                    columna_inicial = columna + 1;
                    break;
                default:
                    valor *= 10;
                    valor += linea[columna] - 48;
            }
        } else {
            if (valor != -1) {
                Numero n;
                n.valor = valor;
                n.fila = fila; 
                n.columna_inicial = columna_inicial;
                n.columna_final = columna;
                n.cantidad_digitos = cantidad_digitos;
                numeros[cantidad_numeros] = n;
                cantidad_numeros++;
            }
            cantidad_digitos = 0;
            valor = -1;
            columna_inicial = 0;
        }
        columna++;
    }
}

void guardar_tabla(char* linea, int fila) {
    int columna = 1;

    tabla[fila][0] = 'A';

    while (linea[columna - 1]) {
        tabla[fila][columna] = linea[columna - 1];
        columna++;
    }

    tabla[fila][columna - 1] = 'A';

    guardar_numeros(linea, fila);
}

int main() {
    FILE *fptr;
    fptr = fopen(ARCHIVO, "r");

    char linea[TAMANIO_LINEA];
    int fila = 1;

    // rellena la primer fila con un caracter aleatorio
    for (int i = 0; i < COLUMNAS + 2; i++) {
        tabla[0][i] = 'A';
    }
    while (fgets(linea, TAMANIO_LINEA, fptr)) {
        guardar_tabla(linea, fila);
        fila++;
    }
    
    // rellena la ultima fila con un caracter aleatorio
    for (int i = 0; i < COLUMNAS + 2; i++) {
        tabla[FILAS + 1][i] = 'A';
    }

    //mostrar_tabla();
    //mostrar_numeros();
    
    verificar_numeros();
    int suma_ratio =  calcular_engines();

    printf("Resultado final - Parte 1: %d\n", suma);
    printf("Resultado final - Parte 2: %d\n", suma_ratio);

    fclose(fptr);

    return 0;
}
