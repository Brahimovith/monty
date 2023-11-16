#include "monty.h"
char *arg;

void fct(FILE *fichier, stack_t **ss)
{
	
	char ligne[100];
	char *opcode;
	unsigned int nline = 0;
	while(fgets(ligne, sizeof(ligne), fichier))
	{
		nline++;
		opcode = strtok(ligne, " \t\n");
		executer(opcode, ss, nline);
	}

}

void executer(char *opcode, stack_t **ss,unsigned int nline)
{
	instruction_t i[] = {{"push", fpush}, {"pall", fpall},{"pint",fpint},{"pop", fpop}
	,{"swap", fswap},{"add", fadd},{"nop",fnop},{NULL, NULL}};
	int j = 0;

	for(j = 0; i[j].opcode; j++ )
		{
			
			if(strcmp(i[j].opcode, opcode) == 0)
			{
				i[j].f(ss, nline);
				return;
			}
			
		}
		fprintf(stderr, "L%d: unknown instruction %s\n" ,nline,opcode);
		exit(EXIT_FAILURE);
			

   


}







void fpush(stack_t **stack, unsigned int line_number)
{
char *arg = strtok(NULL, " \t\n");
	stack_t *new_node = malloc(sizeof(stack_t));

	if (arg == NULL || !is_integer(arg))
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->n = atoi(arg);
	new_node->prev = *stack;
	*stack = new_node;


}

void fpall(stack_t **stack, unsigned int line_number)
{
stack_t *current = *stack;

	(void)line_number;
	while (current)
	{
		printf("%d\n", current->n);
		current = current->prev;
	}

}

void fpint(stack_t **stack, unsigned int line_number)
{
	if (!stack || !*stack)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*stack)->n);

}
void fpop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	*stack = (*stack)->prev;
	free(temp);

}
void fswap(stack_t **stack, unsigned int line_number)
{
	int temp;

	if (!stack || !(*stack) || !(*stack)->prev)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->n;
	(*stack)->n = (*stack)->prev->n;
	(*stack)->prev->n = temp;
}
void fnop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
void fadd(stack_t **stack, unsigned int line_number)
{
		int result;
	stack_t *temp;

	if (!stack || !*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	result = (*stack)->n + (*stack)->next->n;

	(*stack)->next->n = result;
	*stack = (*stack)->next;
	free(temp);
}
int is_integer(char *str)
{
	int i;
	if(str == NULL || *str == '\0')
	{
		return(0);
	}
	for( i = 0; str[i] != '\0'; i++)
	{
		if(str[i] == '-' && i == 0)
		{
			continue;
		}
		if(str[i] < '0' || str[i] > '9')
		{
			return 0;
		}
	}
	return 1;
}
