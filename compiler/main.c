#include "lexer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* read_file(const char* filename)
{
	FILE* f;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	f = fopen(filename, "rb");
	if (f == NULL)
	{
		printf("Could not open file \"%s\"!\n", filename);
		return NULL;
	}

	char* buffer = calloc(1, sizeof(char));

	while ((read = getline(&line, &len, f)) != -1)
	{
		buffer = realloc(buffer, (strlen(buffer) + strlen(line) + 1) * sizeof(char));
		strcat(buffer, line);
	}

	fclose(f);
	if (line)
		free(line);

	return buffer;
}

int main(void)
{
	Lexer* lexer = lexer_create(read_file("example.lctx"));
	Token* token = NULL;
	while ((token = lexer_get_next_token(lexer))->type != TOKEN_EOF)
	{
		printf("[Lexer]: \"%s\"\n", token->value);
	}

	return 0;
}