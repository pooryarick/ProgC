#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#define RESIZE 10

Stack *create_stack(int start_size) {
  Stack *stack = malloc(sizeof(Stack));
  stack->size = start_size;
  stack->data = malloc(stack->size * sizeof(int));
  stack->top = 0;
  return stack;
}

void push(Stack *stack, int v) {
  if (stack->top == stack->size) {
    stack->size += RESIZE;
    stack->data = realloc(stack->data, stack->size * sizeof(int));
  }
  stack->data[stack->top] = v;
  stack->top++;
}
int is_empty(Stack *stack) { return !stack->top; }

int pop(Stack *stack, int *out) {
  if (is_empty(stack)) {
    return STACK_IS_EMPTY;
  }
  stack->top--;
  *out = stack->data[stack->top];
  if (stack->top == stack->size - RESIZE) {
    stack->size -= RESIZE;
    stack->data = realloc(stack->data, stack->size * sizeof(int));
  }
  return 0;
}

void clean_memory(Stack *stack) {
  free(stack->data);
  free(stack);
}
