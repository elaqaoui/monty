#include "monty.h"

/**
 * createNode - Creates a new node for the stack or queue
 * @value: The value to be stored in the new node
 *
 * Return: A pointer to the newly created node
 */
stack_q_t *createNode(int value) {
        stack_q_t *new_node = malloc(sizeof(stack_q_t));

        if (new_node == NULL) {
                fprintf(stderr, "Error: malloc failed\n");
                exit(EXIT_FAILURE);
        }

        new_node->value = value;
        new_node->prev = NULL;
        new_node->next = NULL;

        return new_node;
}

/**
 * freeNodes - Frees the memory allocated for nodes in the stack or queue
 */
void freeNodes() {
        stack_q_t *current = top;
        stack_q_t *next_node;

        while (current != NULL) {
                next_node = current->next;
                free(current);
                current = next_node;
        }
}

/**
 * printStack - Prints the values of the stack
 * @head: Pointer to the top of the stack
 * @lineNum: Line number (unused)
 */
void printStack(stack_q_t **head, __attribute__((unused)) unsigned int lineNum) {
        stack_q_t *current;
        if (head == NULL)
                exit(EXIT_FAILURE);
        current = *head;

        while (current) {
                printf("%d\n", current->value);
                current = current->next;
        }
}

/**
 * push_to_stack - Pushes a value onto the stack
 * @stack: Pointer to the new node to be pushed onto the stack
 * @lineNum: Line number (unused)
 */
void push_to_stack(stack_q_t **stack, __attribute__((unused)) unsigned int lineNum) {
        stack_q_t *temp;

        if (stack == NULL || *stack == NULL) {
                fprintf(stderr, "Error: malloc failed\n");
                exit(EXIT_FAILURE);
        }

        if (top == NULL) {
                top = *stack;
                return;
        }

        temp = top;
        top = *stack;
        top->next = temp;
        temp->prev = top;
}

/**
 * add_to_queue - Enqueues a value into the queue
 * @new_node: Pointer to the new node to be enqueued
 * @lineNum: Line number (unused)
 */
void add_to_queue(stack_q_t **new_node, __attribute__((unused)) unsigned int lineNum) {
        stack_q_t *temp;

        if (new_node == NULL || *new_node == NULL)
                exit(EXIT_FAILURE);
        if (top == NULL) {
                top = *new_node;
                return;
        }

        temp = top;
        while (temp->next != NULL)
                temp = temp->next;

        temp->next = *new_node;
        (*new_node)->prev = temp;
}

/**
 * print_top - Prints the value at the top of the stack
 * @stack: Pointer to the stack
 * @line_number: Line number
 */
void print_top(stack_q_t **stack, unsigned int line_number) {
        if (stack == NULL || *stack == NULL) {
                fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
                freeNodes();
                exit(EXIT_FAILURE);
        }
        printf("%d\n", (*stack)->value);
}

/**
 * pop_top - Pops the top element off the stack
 * @stack: Pointer to the stack
 * @line_number: Line number
 */
void pop_top(stack_q_t **stack, unsigned int line_number) {
        stack_q_t *temp;

        if (stack == NULL || *stack == NULL) {
                fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
                freeNodes();
                exit(EXIT_FAILURE);
        }

        temp = *stack;
        *stack = temp->next;
        if (*stack != NULL)
                (*stack)->prev = NULL;
        free(temp);
}
/**
 * nop - Does nothing
 * @stack: Pointer to the stack (unused)
 * @line_number: Line number (unused)
 */
void nop(stack_q_t **stack, unsigned int line_number) {
        (void) stack;
        (void) line_number;
}

/**
 * swap_nodes - Swaps the top two elements of the stack
 * @stack: Pointer to the stack
 * @line_number: Line number
 */
void swap_nodes(stack_q_t **stack, unsigned int line_number) {
        stack_q_t *temp;
        if (stack == NULL || *stack == NULL || (*stack) -> next == NULL) {
                fprintf(stderr, "L%d: can't %s, stack too short\n", line_number, "swap");
                freeNodes();
                exit(EXIT_FAILURE);
        }

        temp = (*stack)->next;
        (*stack)->next = temp->next;

        if (temp->next != NULL) {
                temp->next->prev = *stack;
        }

        temp->next = *stack;
        (*stack)->prev = temp;
        temp->prev = NULL;
        *stack = temp;
}

/**
 * add_nodes - Adds the top two elements of the stack
 * @stack: Pointer to the stack
 * @line_number: Line number
 */
void add_nodes(stack_q_t **stack, unsigned int line_number) {
        int sum;
        stack_q_t *temp;

        if (stack == NULL || *stack == NULL || (*stack)->next == NULL) {
                fprintf(stderr, "L%d: can't %s, stack too short\n", line_number, "add");
                freeNodes();
                exit(EXIT_FAILURE);
        }

        temp = (*stack)->next;
        sum = temp->value + temp->prev->value;
        temp->value = sum;
        free(temp->prev);
        temp->prev = NULL;
        *stack = temp;
}

/**
 * sub_nodes - Subtracts the top element from the second top element of the stack
 * @stack: Pointer to the stack
 * @line_number: Line number
 */
void sub_nodes(stack_q_t **stack, unsigned int line_number) {
        int sub;
        stack_q_t *temp;

        if (stack == NULL || *stack == NULL || (*stack)->next == NULL) {
                fprintf(stderr, "L%d: can't %s, stack too short\n", line_number, "sub");
                freeNodes();
                exit(EXIT_FAILURE);
        }

        temp = (*stack)->next;
        sub = temp->value - temp->prev->value;
        temp->value = sub;
        free(temp->prev);
        temp->prev = NULL;
        *stack = temp;
}

/**
 * div_nodes - Divides the second top element by the top element of the stack
 * @stack: Pointer to the stack
 * @line_number: Line number
 */
void div_nodes(stack_q_t **stack, unsigned int line_number) {
        int div;
        stack_q_t *temp;

        if (stack == NULL || *stack == NULL || (*stack)->next == NULL) {
                fprintf(stderr, "L%d: can't %s, stack too short\n", line_number, "div");
                freeNodes();
                exit(EXIT_FAILURE);
        }

        if ((*stack)->value == 0) {
                fprintf(stderr, "L%d: division by zero\n", line_number);
                freeNodes();
                exit(EXIT_FAILURE);
        }

        temp = (*stack)->next;
        div = temp->value / temp->prev->value;
        temp->value = div;
        free(temp->prev);
        temp->prev = NULL;
        *stack = temp;
}

/**
 * mul_nodes - Multiplies the top two elements of the stack
 * @stack: Pointer to the stack
 * @line_number: Line number
 */
void mul_nodes(stack_q_t **stack, unsigned int line_number) {
        int mul;
        stack_q_t *temp;

        if (stack == NULL || *stack == NULL || (*stack)->next == NULL) {
                fprintf(stderr, "L%d: can't %s, stack too short\n", line_number, "mul");
                freeNodes();
                exit(EXIT_FAILURE);
        }

        temp = (*stack)->next;
        mul = temp->value * temp->prev->value;
        temp->value = mul;
        free(temp->prev);
        temp->prev = NULL;
        *stack = temp;
}

void mod_nodes(stack_q_t **stack, unsigned int line_number) {
        int mod;
        stack_q_t *temp;

        if (stack == NULL || *stack == NULL || (*stack)->next == NULL) {
                fprintf(stderr, "L%d: can't %s, stack too short\n", line_number, "mod");
                freeNodes();
                exit(EXIT_FAILURE);
        }

        if ((*stack)->value == 0) {
                fprintf(stderr, "L%d: division by zero\n", line_number);
                freeNodes();
                exit(EXIT_FAILURE);
        }

        temp = (*stack)->next;
        mod = temp->value % temp->prev->value;
        temp->value = mod;
        free(temp->prev);
        temp->prev = NULL;
        *stack = temp;
}

/**
 * print_char - Prints the character at the top of the stack
 * @stack: Pointer to the stack
 * @line_number: Line number
 */
void print_char(stack_q_t **stack, unsigned int line_number) {
        int ascii;
        stack_q_t *temp;

        if (stack == NULL || *stack == NULL) {
                fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
                freeNodes();
                exit(EXIT_FAILURE);
        }

        temp = *stack;
        ascii = temp->value;
        if (ascii < 0 || ascii > 127) {
                fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
                freeNodes();
                exit(EXIT_FAILURE);
        }
        printf("%c\n", ascii);
}

void print_str(stack_q_t **stack, __attribute__((unused)) unsigned int line_number) {
        int ascii;
        stack_q_t *temp;

        if (stack == NULL || *stack == NULL) {
                printf("\n");
                return;
        }

        temp = *stack;
        while (temp != NULL) {
                ascii = temp->value;
                if (ascii <= 0 || ascii > 127)
                        break;
                printf("%c", ascii);
                temp = temp->next;
        }
        printf("\n");
}

/**
 * rotl - Rotates the stack to the top
 * @stack: Pointer to the stack
 * @line_number: Line number
 */
void rotl(stack_q_t **stack, __attribute__((unused)) unsigned int line_number) {
        stack_q_t *temp;

        if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
                return;

        temp = *stack;
        while (temp->next != NULL)
                temp = temp->next;

        temp->next = *stack;
        (*stack)->prev = temp;
        *stack = (*stack)->next;
        (*stack)->prev->next = NULL;
        (*stack)->prev = NULL;
}

/**
 * rotr - Rotates the stack to the bottom
 * @stack: Pointer to the stack
 * @line_number: Line number
 */
void rotr(stack_q_t **stack, __attribute__((unused)) unsigned int line_number) {
        stack_q_t *temp;

        if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
                return;

        temp = *stack;
        while (temp->next != NULL)
                temp = temp->next;

        temp->next = *stack;
        temp->prev->next = NULL;
        temp->prev = NULL;
        (*stack)->prev = temp;
        *stack = temp;
}