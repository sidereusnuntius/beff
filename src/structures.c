#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/structures.h"

void double_capacity(Instructions*);

Instructions* create() {
    Instructions* instruct = (Instructions*) malloc(sizeof(Instructions));
    instruct->instructs_array = (char*) malloc(sizeof(char) * INITIAL_ARRAY_SIZE);
    instruct->capacity = INITIAL_ARRAY_SIZE;
    instruct->current_instruction = 0;

    return instruct;
}

void insert(Instructions *instructs, char c) {
    if (instructs->current_instruction == instructs->capacity-1)
        double_capacity(instructs);

    instructs->instructs_array[instructs->current_instruction++] = c;
}

void double_capacity(Instructions *instructs) {
    char *new_array = (char*) malloc(instructs->capacity * 2 * sizeof(char));
    memcpy(new_array, instructs->instructs_array, instructs->capacity);
    
    free(instructs->instructs_array);
    instructs->instructs_array = new_array;
    instructs->capacity *= 2;
}

char read_instruction(Instructions* instructs) {
    char c = instructs->instructs_array[instructs->current_instruction++];
    // putchar(c);
    return c;
}


void destroy_instr_array(Instructions *instructs) {
    free(instructs->instructs_array);
    free(instructs);
}

void move(Instructions *instructs, int index) {
    printf("Moving to %d\n", index);
    instructs->current_instruction = index;
}

// =====================
// |  STACK FUNCTIONS  | 
// =====================

void push(CallStack **stack, int index) {
    CallStack *temp = (CallStack*) malloc(sizeof(CallStack));

    temp->start = index;
    temp->next = *stack;

    *stack = temp;
}

void pop(CallStack **stack) {
    if (*stack == NULL) {
        printf("Tried to pop the stack, but it's NULL.\n");
        exit(EXIT_FAILURE);
    }

    printf("POP: %d\n", (*stack)->start);
    
    CallStack *temp = (*stack)->next;

    free(*stack);
    *stack = temp;
}