#include <stdio.h>
// #include "../include/structures.h"
#include "../include/brainfuck.h"
#include <limits.h>

FILE *open_file(char *file_name) {
    FILE *file_pointer = fopen(file_name, "r");

    if (file_pointer == NULL){
         fprintf(stderr, "Couldn't open file.\n");
         exit(EXIT_FAILURE);
    }
    return file_pointer;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "No file given.\n");
        exit(EXIT_FAILURE);
    }

    EffMachine *machine = init();

    read_from_file(machine, open_file(argv[1]), EOF);

    while (execute(machine)) {
        
    }

    destroy_machine(machine);    
    return 0;
}