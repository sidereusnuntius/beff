#include <string.h>
#include <stdlib.h>
#include "../include/brainfuck.h"

EffMachine *init() {
    EffMachine *machine = (EffMachine*) malloc(sizeof(EffMachine));
    machine->tape = (unsigned char*) malloc(sizeof(unsigned char) * TAPE_SIZE);
    machine->pointer = machine->tape;
    machine->stack = NULL;
    machine->instructs = create();

    return machine;
}

void read_from_file(EffMachine *machine, FILE *file, char end_char) {
    char temp;
    
    while ((temp = fgetc(file)) != end_char) {
        if (strchr("<>+-[],.", temp)) // strchr returns a non-NULL pointer if temp is in the given string.
            insert(machine->instructs, temp);
    }
    insert(machine->instructs, '\0');
}

void destroy_machine(EffMachine* machine) {
    free(machine->tape);
    destroy_instr_array(machine->instructs);

    free(machine);
}