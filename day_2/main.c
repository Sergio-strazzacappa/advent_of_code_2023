#include <stdio.h>

#define ARCHIVO       "input.txt"
#define TAMANIO_LINEA 200
#define RED_CUBES     12
#define GREEN_CUBES   13
#define BLUE_CUBES    14

int suma_id = 0;

struct juego {
    int id;
    int cant_red;
    int cant_green;
    int cant_blue;
    int red[10];
    int green[10];
    int blue[10];
    int min_cubes[3];
} juego;

void init() {
    juego.cant_red = 0;
    juego.cant_green = 0;
    juego.cant_blue = 0;
}

void mostrar_juego() {
    printf("ID = %d\n", juego.id);
    
    printf("RED CUBES: { ");
    for (int i = 0; i < juego.cant_red; i++) {
        printf("%d ", juego.red[i]);    
    }
    printf("}\n");

    printf("GREEN CUBES: { ");
    for (int i = 0; i < juego.cant_green; i++) {
        printf("%d ", juego.green[i]);
    }
    printf("}\n");

    printf("BLUE CUBES: { ");
    for (int i = 0; i < juego.cant_blue; i++) {
        printf("%d ", juego.blue[i]);
    }
    printf("}\n");

    printf("MIN_CUBES: { ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", juego.min_cubes[i]);
    }
    printf("}\n");
}

void obtener_id(char* linea, int* indice) {
    int digitos[3];
    int cantidad_digitos = 0;

    while (linea[*indice] != ':') {
        digitos[cantidad_digitos] = linea[*indice] - 48;
        cantidad_digitos++;
        *indice += 1;    
    } 
    
    for (int i = 0; i < cantidad_digitos; i++) {
        switch (i) {
            case 0:
                juego.id = digitos[i];
                break;
            case 1:
            case 2:
                juego.id *= 10;
                juego.id += digitos[i];
                break;
        }
    }
}

void obtener_bolsas(char* linea, int* indice) {
    int cantidad_digitos = 0;
    int valor = 0;

    while (linea[*indice]) {
        if (linea[*indice] == ' ') {
            *indice += 1;
        }
        if (linea[*indice] != ';') {
            if (linea[*indice] != 'r' && linea[*indice] != 'g' && 
                    linea[*indice] != 'b') {
                cantidad_digitos++;
                switch(cantidad_digitos) {
                    case 1:
                        valor = linea[*indice] - 48;
                        break;
                    case 2:
                    case 3:
                        valor *= 10;
                        valor += linea[*indice] - 48;
                        break;
                }
            } else if (linea[*indice] == 'r') {
                juego.red[juego.cant_red] =  valor;
                juego.cant_red++;
                cantidad_digitos = 0;
                valor = 0;
                *indice += 3;
            } else if (linea[*indice] == 'g') {
                juego.green[juego.cant_green] = valor;
                juego.cant_green++;
                cantidad_digitos = 0;
                valor = 0;
                *indice += 5;
            } else if (linea[*indice] == 'b') {
                juego.blue[juego.cant_blue] = valor;
                juego.cant_blue++;
                cantidad_digitos = 0;
                valor = 0;
                *indice += 4;
            }
        } 
        *indice += 1;
    }
}

void verificar_bolsas() {
    int posible = 1;

    for (int i = 0; i < juego.cant_red && posible; i++) {
        if (juego.red[i] > RED_CUBES) {
            posible = 0;
        }
    }
    for (int i = 0; i < juego.cant_green && posible; i++) {
        if (juego.green[i] > GREEN_CUBES) {
            posible = 0;
        }
    }
    for (int i = 0; i < juego.cant_blue && posible; i++) {
        if (juego.blue[i] > BLUE_CUBES) {
            posible = 0;
        }
    }
    if (posible) {
        suma_id += juego.id;
    }
}

void minima_cantidad_de_cubos() {
    int min = 0;
    for (int i = 0; i < juego.cant_red; i++) {
        if (juego.red[i] > min) {
            min = juego.red[i];
        }
    }
    juego.min_cubes[0] = min;
    min = 0;
    for (int i = 0; i < juego.cant_green; i++) {
        if (juego.green[i] > min) {
            min = juego.green[i];
        }
    }
    juego.min_cubes[1] = min;
    min = 0;
    for (int i = 0; i < juego.cant_blue; i++) {
        if (juego.blue[i] > min) {
            min = juego.blue[i];
        }
    }
    juego.min_cubes[2] = min;
}

void solve(char* linea) {
    int indice = 5;
    obtener_id(linea, &indice);
    indice += 2;
    obtener_bolsas(linea, &indice);
    verificar_bolsas();
    minima_cantidad_de_cubos();
}

int main() {
    FILE *fptr;
    fptr = fopen(ARCHIVO, "r");

    char linea[TAMANIO_LINEA];
    int sum_power = 0;

    while (fgets(linea, TAMANIO_LINEA, fptr)) {
        init();
        solve(linea);
        int power = 
            juego.min_cubes[0] * juego.min_cubes[1] * juego.min_cubes[2];
        sum_power += power;
        mostrar_juego();
    }

    printf("Respuesta final: %d\n", sum_power);

    fclose(fptr);

    return 0;
}
