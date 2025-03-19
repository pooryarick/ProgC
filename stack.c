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
int is_not_empty(Stack *stack) {
  if (stack->top == 0) {
    return 0;
  } else {
    return 1;
  }
}

int pop(Stack *stack) {
  if (is_not_empty(stack) == 0) {
    printf("Stack is empty, can't pop element\n");
    exit(-1);
  }
  int out = stack->data[stack->top - 1];
  stack->top--;
  if (stack->top == stack->size - RESIZE) {
    stack->size -= RESIZE;
    stack->data = realloc(stack->data, stack->size * sizeof(int));
  }
  return out;
}

void clean_memory(Stack *stack) {
  free(stack->data);
  free(stack);
}
