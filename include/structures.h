#include <stdlib.h>

#define INITIAL_ARRAY_SIZE 128

typedef struct CallStack {
    int start;
    struct CallStack* next;
} CallStack;

void push(CallStack**, int);
void pop(CallStack**);

typedef struct {
    char *instructs_array;
    unsigned int current_instruction;
    unsigned int capacity;
} Instructions;

Instructions* create();
void insert(Instructions*, char);
void move(Instructions*, int);
void destroy_instr_array(Instructions*);