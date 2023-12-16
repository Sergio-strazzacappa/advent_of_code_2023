#include <stdio.h>
#include <stdbool.h>

/*
 * example.txt
 * LINE_SIZE = 28
 * NUM_SEEDS = 4
 * MAX_NUM_RULES = 4
 *
 * input.txt
 * LINE_SIZE = 208
 * NUM_SEED = 20
 * MAX_NUM_RULES = 50
 */ 

#define INPUT         "input.txt"
#define LINE_SIZE     ((208) + 2)
#define NUM_SEEDS     (20)
#define NUM_MAPS      (7)
#define MAX_NUM_RULES (47)

struct map {
    long dest;
    long src;
    long range;
};

long seeds[NUM_SEEDS];
int rules_per_header[NUM_MAPS] = {0, 0, 0, 0, 0, 0, 0};
struct map maps[NUM_MAPS][MAX_NUM_RULES];

void print_seeds() {
    printf("Seeds: [ ");
    for(int i = 0; i < NUM_SEEDS; i++) {
        if (i != NUM_SEEDS - 1) {
            printf("%ld - ", seeds[i]);
        } else {
            printf("%ld ]\n", seeds[i]);
        }
    }
}

void print_maps() {
    for (int i = 0; i < NUM_MAPS; i++) {
        printf("Map N°%d\n", (i + 1));
        for (int j = 0; j < MAX_NUM_RULES; j++) {
            printf("%ld - %ld - %ld\n", maps[i][j].dest, maps[i][j].src, maps[i][j].range);
        }
        printf("\n");
    }
}

void read_seeds(char *line) {
    long value = -1;
    int digits = 0;
    int seed_index = 0;

    for (int i = 0; i < LINE_SIZE; i++) {
        if (line[i] - 48 >= 0 && line[i] - 48 <= 9) {
            // number
            digits++;
            
            switch (digits) {
                case 1:
                    value = line[i] - 48;
                    break;
                default:
                    value *= 10;
                    value += line[i] - 48;
                    break;
            }
        } else if (value != -1) {
            seeds[seed_index] = value;
            value = -1;
            digits = 0;
            seed_index++;
        }
    }
}

void save_map(char *line, int header_num, int *map_num) {
    long value = -1;
    int digits = 0;
    long dest = -1;
    long src = -1;
    long range = -1;

    for (int i = 0; i < LINE_SIZE; i++) {
        if (line[i] - 48 >= 0 && line[i] - 48 <= 9) {
            // number
            digits++;

            switch (digits) {
                case 1:
                    value = line[i] - 48;
                    break;
                default:
                    value *= 10;
                    value += line[i] - 48;
                    break;
            }
        } else if (value != -1) {
            if (dest == -1) {
                dest = value;
            } else if (src == -1) {
                src = value;
            } else if(range == -1) {
                //printf("RANGE: %ld\n", value);
                range = value;
            }
            value = -1;
            digits = 0;
        }
    }

    struct map map;

    map.dest = dest;
    map.src = src;
    map.range = range;
    
    maps[header_num - 1][*map_num - 1] = map;
    *map_num = *map_num + 1;
}

void read_input(FILE *fptr) {
    char line[LINE_SIZE];
    int i = 0;
    bool in_header = false;
    int header_num = 0;
    int map_num = 1;

    while (fgets(line, LINE_SIZE, fptr)) {
        if (i == 0) {
            // seeds
            read_seeds(line);
           //print_seeds();
            i++;
        } else if (line[0] == 10) {
                // line feed
                in_header = false;
                i++;
        } else if (line[0] >= 97 && line[0] <= 122) {
                // header
                in_header = true;
                header_num++;
                map_num = 1;
                i++;
                continue;
        } 
        if (in_header) {
            rules_per_header[header_num - 1]++;
            save_map(line, header_num, &map_num);
            i++;
        }
    }
   // print_maps();
}

long solve(long seed) {
    for (int i = 0; i < NUM_MAPS; i++) {
        for (int j = 0; j < rules_per_header[i]; j++) {
            if (seed >= maps[i][j].src &&
                seed <= maps[i][j].src + maps[i][j].range - 1) {
                //printf("%d - %d + %d\n",seed, maps[i][j].src, maps[i][j].dest);
                seed = seed - maps[i][j].src + maps[i][j].dest;
                break;
            }
        }
        //printf("Seeds: %ld\n", seed);
    }
    return seed;
}

int main() {
    FILE *fptr;
    fptr = fopen(INPUT, "r");

    read_input(fptr);

    long min = 9999999999999;

    for (int i = 0; i < NUM_SEEDS; i += 2) {
        for (int j = 0; j < seeds[i + 1]; j++) {
            //printf("Solving %ld\n", seeds[i] + j);
            long location = solve(seeds[i] + j);
            if (location < min) {
                min = location;
            }
        }
    }

    printf("MIN LOCATION: %ld\n", min);

    return 0;
}
