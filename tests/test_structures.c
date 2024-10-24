#include <stdio.h>
#include "../include/structures.h"

void go_through(CallStack *stack) {
    while (stack != NULL) {
        printf("%d ", stack->start);
        stack = stack->next;
    }
    putchar('\n');
}

int main() {
    Instructions* instructs = create();
    printf("Structure created.\n");

    insert(instructs, 'h');
    insert(instructs, 'e'); 

    insert(instructs, 'l');
    insert(instructs, 'l');
    insert(instructs, 'o');
    insert(instructs, '\0');

    move(instructs, 4);
    insert(instructs, 'f');
    insert(instructs, 'i');
    insert(instructs, 'r');
    insert(instructs, 'e');

    insert(instructs, ',');
    insert(instructs, '\0');

    printf("%s\n", instructs->instructs_array);

    destroy_instr_array(instructs);

    CallStack *stack = NULL;
    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    push(&stack, 200);

    go_through(stack);

    pop(&stack);
    go_through(stack);

    pop(&stack);
    go_through(stack);

    pop(&stack);
    go_through(stack);

    pop(&stack);

    if (stack == NULL)
        printf("Stack is null.\n");

    return 0;
}