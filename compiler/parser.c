#include "parser.h"

#include <stdlib.h>
#include <stdio.h>

AST* ast_create(size_t type)
{
	AST* ast = malloc(1 * sizeof(AST));
	ast->type = type;
	return ast;
}

Parser* parser_create(Lexer* lexer)
{
	Parser* parser = malloc(1 * sizeof(Parser));
	parser->lexer = lexer;
	parser->token = lexer_get_next_token(parser->lexer);
	return parser;
}

Token* parser_eat(Parser* parser, size_t type)
{
	if (parser->token->type != type)
	{
		printf("[Parser]: Unexpected token type: Expected '%zu' but got '%zu'!\n", type, parser->token->type);
		exit(1);
	}

	parser->token = lexer_get_next_token(parser->lexer);
	return parser->token;
}

AST* parser_parse(Parser* parser)
{
	return ast_create(AST_NOOP);
}

AST* parser_parse_compound(Parser* parser)
{
	AST* compound = ast_create(AST_COMPOUND);
	
	while (parser->token->type != TOKEN_EOF)
	{
		AST* child = parser_parse(parser);
	}

	return ast_create(AST_NOOP);
}

