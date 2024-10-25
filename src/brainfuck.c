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

void destroy_machine(EffMachine* machine) {
    free(machine->tape);
    destroy_instr_array(machine->instructs);

    free(machine);
}

void read_from_file(EffMachine *machine, FILE *file, char end_char) {
    char temp;
    
    while ((temp = fgetc(file)) != end_char) {
        if (strchr("<>+-[],.", temp)) // strchr returns a non-NULL pointer if temp is in the given string.
            insert(machine->instructs, temp);
    }
    insert(machine->instructs, '\0');
    machine->instructs->current_instruction = 0;

    fclose(file);
}

void read_input(EffMachine *machine) {
    *machine->pointer = getchar();
    
    // char aux;
    // while ((aux = getchar()) != '\n' && aux != EOF);
}

void move_right(unsigned char *tape, unsigned char **pointer) {
    if (*pointer - tape == TAPE_SIZE - 1)
        *pointer = tape;
    else
        (*pointer)++;
}

void move_left(unsigned char *tape, unsigned char **pointer) {
    if (*pointer == tape)
        *pointer = tape+TAPE_SIZE-1;
    else
        (*pointer)--;
}

// BUG: it jumps to the first closing bracket it finds, not to the corresponding bracket.
void read_until_closing_bracket(Instructions *instructs) {
    char c;
    int bracket_counter = 0;

    for (;(c = instructs->instructs_array[instructs->current_instruction]) != '\0'; instructs->current_instruction++){
        if (strchr("[]", c)){
            (c == BEGIN_LOOP) ? bracket_counter++ : bracket_counter--;
            if (bracket_counter < 0)
                break;
        }
    }

    if (c == END_LOOP)
        instructs->current_instruction++;
}

void begin_loop(EffMachine *machine) {
    if (!*machine->pointer) // Jumps past the corresponding ] if the value at the current cell is 0.
        read_until_closing_bracket(machine->instructs);
    else
        push(&machine->stack, machine->instructs->current_instruction);
        // Since current_instruction is increment inside the function read_instruction,
        // what is pushed into the stack is the index of the instruction that comes after the '['.
}

/* 
 * If the value of the current cell is not 0, goes back to the start of the loop. If it's zero,
 * leaves the loop.
 */
//BUG: the program tries to move to the start of the loop, but the call stack is null.
//The programs tries to close the loop, but the stack is null.
// Suggestion: Create a function that prints the entire stack.
void end_loop(EffMachine *machine) {
    if (*machine->pointer)
        move(machine->instructs, machine->stack->start);
    else
        pop(&machine->stack);
}

/*
    Executes the next instruction. Returns false if the program has ended.
*/
bool execute(EffMachine *machine) {
    char c;
    switch ((c = read_instruction(machine->instructs))) {
        case INCREMENT: (*machine->pointer)++; break;
        case DECREMENT: (*machine->pointer)--; break;
        case RIGHT_MOVE: move_right(machine->tape, &machine->pointer); break;
        case LEFT_MOVE: move_left(machine->tape, &machine->pointer); break;
        case BEGIN_LOOP: begin_loop(machine); break;
        case END_LOOP: end_loop(machine); break;
        case PRINT_CHARACTER: putchar(*machine->pointer); break;
        case READ_CHARACTER: read_input(machine); break;
        default: return false;
    }
    return true;
}