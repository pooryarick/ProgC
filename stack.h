typedef struct Stack {
  int *data;
  unsigned int size;
  unsigned int top;
} Stack;

Stack *create_stack(int start_size);
void push(Stack *stack, int v);
int is_empty(Stack *stack);
int pop(Stack *stack, int *out);
void clean_memory(Stack *);
#define STACK_IS_EMPTY -1
