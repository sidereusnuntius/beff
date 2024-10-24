#include <string.h>
#include <stdlib.h>
#include "../include/structures.h"

void double_capacity(Instructions*);

Instructions* create() {
    Instructions* instruct = (Instructions*) malloc(sizeof(Instructions));
    instruct->instructs_array = (char*) malloc(sizeof(char) * 2);
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

void destroy(Instructions *instructs) {
    free(instructs->instructs_array);
    free(instructs);
}

void move(Instructions *instructs, int index) {
    instructs->current_instruction = index;
}

void push(CallStack **stack, int index) {
    CallStack *temp = (CallStack*) malloc(sizeof(CallStack));

    temp->start = index;
    temp->next = *stack;

    *stack = temp;
}

void pop(CallStack **stack) {
    if (*stack == NULL)
        return;
    
    CallStack *temp = (*stack)->next;

    free(*stack);
    *stack = temp;
}