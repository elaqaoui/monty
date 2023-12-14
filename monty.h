#ifndef MONTY_H
#define MONTY_H
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <ctype.h>

/**
 * struct stack_q - doubly linked list representation of a stack (or queue)
 * @value: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_q
{
        int value;
        struct stack_q *prev;
        struct stack_q *next;
} stack_q_t;

extern stack_q_t *top;

/**
 * struct operation_s - opcode and its function
 * @opcode: the opcode
 * @func: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct operation_s
{
        char *op_code;
        void (*func)(stack_q_t **stack, unsigned int lineNum);
} operation_t;

typedef void (*operation_func)(stack_q_t **, unsigned int);

/* All the file operations */
void openFile(char *file);
unsigned int process_line(char *,unsigned int, int);
void readFile(FILE *);
int lenChars(FILE *);
void findFunc(char *, char *,unsigned int, int);
void call_func(operation_func , char *, char *, unsigned int, int);

/*Various Operations*/
stack_q_t *createNode(int);
void freeNodes(void);
void printStack(stack_q_t **, unsigned int lineNum);
void push_to_stack(stack_q_t **,unsigned int lineNum);
void add_to_queue(stack_q_t **new_node, __attribute__((unused))unsigned int lineNum);
void print_top(stack_q_t **stack, unsigned int line_number);
void pop_top(stack_q_t **stack, unsigned int line_number);
void nop(stack_q_t **stack, unsigned int line_number);
void swap_nodes(stack_q_t **stack, unsigned int line_number);
void add_nodes(stack_q_t **stack, unsigned int line_number);
void sub_nodes(stack_q_t **stack, unsigned int line_number);
void div_nodes(stack_q_t **stack, unsigned int line_number);
void mul_nodes(stack_q_t **stack, unsigned int line_number);
void mod_nodes(stack_q_t **stack, unsigned int line_number);
void print_char(stack_q_t **stack, unsigned int line_number);
void print_str(stack_q_t **stack, unsigned int line_number);
void rotl(stack_q_t **stack, unsigned int line_number);
void rotr(stack_q_t **stack, unsigned int line_number);

#endif