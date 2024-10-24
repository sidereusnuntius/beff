typedef struct {
    char *start;
    CallStack* next;
} CallStack;

typedef struct {
    char* index;
    unsigned int capacity;
    unsigned int current_instruction;
} Instructions;

Instructions create();
void insert(Instructions*);
void move(Instructions*, int);
void destroy(Instructions*);