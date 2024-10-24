#include <stdio.h>
#include "structures.h"

#define TAPE_SIZE           4096

#define INCREMENT           '+'
#define DECREMENT           '-'
#define RIGHT_MOVE          '>'
#define LEFT_MOVE           '<'
#define BEGIN_LOOP          '['
#define END_LOOP            ']'
#define PRINT_CHARACTER     '.'
#define READ_CHARACTER      ','

typedef struct {
    unsigned char *tape;
    unsigned char *pointer;
    Instructions *instructs;
} EffMachine;

EffMachine *init();
void read_from_file(EffMachine*, FILE, char);
bool execute(EffMachine*);