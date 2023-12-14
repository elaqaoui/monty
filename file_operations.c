#include "monty.h"

/**
 * openFile - Opens the Monty Byte Code file and reads its content
 * @file: The name of the Monty Byte Code file
 */
void openFile(char *file)
{
        FILE *r_file;

	    if (file == NULL)
	    {
		        fprintf(stderr, "USAGE: monty %s\n", file);
		        exit(EXIT_FAILURE);
	    }

	    r_file = fopen(file, "r");

	    if (r_file == NULL)
	    {
		        fprintf(stderr, "Error: Can't open the file %s\n", file);
		        exit(EXIT_FAILURE);
    	}

	    readFile(r_file);

	    if (fclose(r_file) != 0)
	    {
		        perror("Error closing file");
		        exit(EXIT_FAILURE);
    	}
}


/**
 * readFile - Reads the content of a file
 * @r_file: The file to read
 */
void readFile(FILE *r_file)
{
        char *line = NULL;
        size_t len = 0;
        unsigned int lineNum = 1, format = 0;

        while (getline(&line, &len, r_file) != -1)
        {
                format = process_line(line, lineNum, format);
                lineNum++;
        }

        if (line != NULL)
        {
                free(line);
        }
}

/**
 * process_line - Processes a line from the file
 * @line: The line to process
 * @lineNum: The line number
 * @format: The format to use
 *
 * Return: The format
 */
unsigned int process_line(char *line, unsigned int lineNum, int format)
{
        char *op_code, *value;
        const char *delimiter = "\n ";

        if (line == NULL)
        {
                fprintf(stderr, "Error: malloc failed\n");
                exit(EXIT_FAILURE);
        }

        op_code = strtok(line, delimiter);
        if (op_code == NULL)
                return format;
        value = strtok(NULL, delimiter);

        if (strcmp(op_code, "stack") == 0)
                return 0;
        if (strcmp(op_code, "queue") == 0)
                return 1;

        findFunc(op_code, value, lineNum, format);
        return format;
}

/**
 * findFunc - Finds the function associated with the opcode
 * @op_code: The opcode
 * @value: The value
 * @lineNum: The line number
 * @format: The format to use
 */
void findFunc(char * op_code, char * value, unsigned int lineNum, int format) 
{
        int i;
        int flag;

        operation_t functionList[] = {
                {"push", push_to_stack},
                {"pall", printStack},
                {"pint", print_top},
                {"pop", pop_top},
                {"nop", nop},
                {"swap", swap_nodes},
                {"add", add_nodes},
                {"sub", sub_nodes},
                {"div", div_nodes},
                {"mul", mul_nodes},
                {"mod", mod_nodes},
                {"pchar", print_char},
                {"pstr", print_str},
                {"rotl", rotl},
                {"rotr", rotr},
                {NULL, NULL}
        };

        if (op_code[0] == '#')
                return;

        for (flag = 1, i = 0; functionList[i].op_code != NULL; i++) 
        {
                if (strcmp(op_code, functionList[i].op_code) == 0) 
                {
                        call_func(functionList[i].func, op_code, value, lineNum, format);
                        flag = 0;
                }
        }

        if (flag == 1) 
        {
                fprintf(stderr, "L%d: unknown instruction %s\n", lineNum, op_code);
                freeNodes();
                exit(EXIT_FAILURE);
        }
}

/**
 * call_func - Calls the appropriate function based on the Monty Byte Code instruction
 * @func: Pointer to the function to be called
 * @op_code: The Monty Byte Code instruction
 * @value: The value associated with the instruction
 * @lineNum: Line number in the Monty Byte Code file
 * @format: Format flag (0 for stack, 1 for queue)
 */
void call_func(operation_func func, char * op_code, char * value, unsigned int lineNum, int format)
{
        int flag = 1, i;
        stack_q_t * node;

        if (strcmp(op_code, "push") == 0) {
                if (value != NULL && value[0] == '-') 
                {
                        value++;
                        flag = -1;
                }
                if (value == NULL) 
                {
                        fprintf(stderr, "L%d: usage: push integer\n", lineNum);
                        freeNodes();
                        exit(EXIT_FAILURE);
                }

                for (i = 0; value[i] != '\0'; i++) 
                {
                        if (!isdigit(value[i])) 
                        {
                                fprintf(stderr, "L%d: usage: push integer\n", lineNum);
                                freeNodes();
                                exit(EXIT_FAILURE);
                        }
                }
                node = createNode(atoi(value) * flag);
                if (format == 0)
                        func(&node, lineNum);
                if (format == 1)
                        add_to_queue(&node, lineNum);
        } else {
                func(&top, lineNum);
        }
}