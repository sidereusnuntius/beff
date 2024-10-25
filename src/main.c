#include <stdio.h>
// #include "../include/structures.h"
#include "../include/brainfuck.h"
#include <limits.h>

int main() {
    EffMachine *machine = init();

    FILE *f = fopen("test.txt", "r");

    if (f == NULL){
         printf("Couldn't open file.");
         exit(EXIT_FAILURE);
    }

    read_from_file(machine, f, EOF);

    fclose(f);

    while (execute(machine)) {
        
    }

    destroy_machine(machine);    
    return 0;
}