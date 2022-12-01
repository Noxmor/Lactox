#include "lexer.h"

#include <stdio.h>

int main(void)
{
	const char* program = "int main() { print(\"Hello World\"); return 0; }";
	
	Lexer* lexer = lexer_create(program);
	Token* token = NULL;
	while ((token = lexer_get_next_token(lexer))->type != TOKEN_EOF)
	{
		printf("[Lexer]: \"%s\"\n", token->value);
	}

	printf("[Lexer]: Done!\n");

	return 0;
}