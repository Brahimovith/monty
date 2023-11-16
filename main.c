#include "monty.h"

/**
 * main - entry point
 * @argc: arguments count
 * @argv: list of arguments
 * Return: always 0
 */

int main(int argc, char *argv[])
{
	FILE *fichier;
	stack_t *ss = NULL;
	stack_t *temp = ss;
	

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	fichier = fopen(argv[1], "r");
	if(fichier == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	fct(fichier,&ss);
	fclose(fichier);
	
	while (ss)
	{
		ss = ss->prev;
		free(temp);
	}
	return (0);
}

