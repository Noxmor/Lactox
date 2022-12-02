#include "parser.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

AST* parser_parse_compound(Parser* parser);
AST* parser_parse_expression(Parser* parser);

AST* ast_create(size_t type)
{
	AST* ast = malloc(1 * sizeof(AST));
	ast->type = type;
	ast->name = NULL;
	ast->data_type = 0;
	ast->value = NULL;
	ast->children = ast->type == AST_COMPOUND ? list_create(sizeof(AST)) : NULL;
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
		printf("[Parser]: Unexpected token type: Expected \"%s\" but got \"%s\"!\n", token_type_to_str(type), token_type_to_str(parser->token->type));
		exit(1);
	}

	parser->token = lexer_get_next_token(parser->lexer);
	return parser->token;
}

AST* parser_parse(Parser* parser)
{
	return parser_parse_compound(parser);
}

AST* parser_parse_identifier(Parser* parser)
{
	char* value = calloc(strlen(parser->token->value) + 1, sizeof(char));
	strcpy(value, parser->token->value);
	parser_eat(parser, TOKEN_IDENTIFIER);

	if (strcmp(value, "return") == 0)
	{
		AST* ast = ast_create(AST_STATEMENT);
		ast->name = value;
		//ast->value = parser_parse_expression(parser);
		ast->value = ast_create(AST_NOOP);
		ast->value->name = "0"; //TODO: Remove
		parser_eat(parser, TOKEN_NUMBER);
		parser_eat(parser, TOKEN_SEMICOLON);
		return ast;
	}

	if (parser->token->type == TOKEN_EQUALS)
	{
		parser_eat(parser, TOKEN_EQUALS);

		AST* ast = ast_create(AST_ASSIGNMENT);
		ast->name = parser->token->value;
		ast->value = parser_parse_expression(parser);
		return ast;
	}

	AST* ast = ast_create(AST_VARIABLE);
	ast->name = parser->token->value;
	ast->data_type = 0; //TODO: Convert char* value into data_type!
	parser_eat(parser, TOKEN_IDENTIFIER);
	return ast;
}

AST* parser_parse_scope(Parser* parser)
{
	parser_eat(parser, TOKEN_LEFT_BRACE);

	AST* compound = ast_create(AST_COMPOUND);

	while (parser->token->type != TOKEN_RIGHT_BRACE)
		list_add(compound->children, parser_parse_expression(parser));

	parser_eat(parser, TOKEN_RIGHT_BRACE);

	return compound;
}

AST* parser_parse_list(Parser* parser)
{
	parser_eat(parser, TOKEN_LEFT_PARANTHESIS);
	
	AST* ast = ast_create(AST_COMPOUND);

	if (parser->token->type != TOKEN_RIGHT_PARANTHESIS)
	{
		list_add(ast->children, parser_parse_expression(parser)); 
		
		while (parser->token->type == TOKEN_COMMA)
		{
			parser_eat(parser, TOKEN_COMMA);
			list_add(ast->children, parser_parse_expression(parser));
		}
	}

	parser_eat(parser, TOKEN_RIGHT_PARANTHESIS);

	if (parser->token->type == TOKEN_LEFT_BRACE)
	{
		ast->type = AST_FUNCTION;
		ast->value = parser_parse_scope(parser);
	}

	return ast;
}

AST* parser_parse_expression(Parser* parser)
{
	switch (parser->token->type)
	{
		case TOKEN_IDENTIFIER: return parser_parse_identifier(parser);
		case TOKEN_LEFT_PARANTHESIS: return parser_parse_list(parser);
		default: printf("[Parser]: Encountered unknown token type \"%s\"!\n", token_type_to_str(parser->token->type)); exit(1); break;
	}

	return ast_create(AST_NOOP);
}

AST* parser_parse_compound(Parser* parser)
{
	AST* compound = ast_create(AST_COMPOUND);
	
	while (parser->token->type != TOKEN_EOF)
	{
		list_add(compound->children, parser_parse_expression(parser));
	}

	return compound;
}

void ast_print(AST* root, size_t offset)
{
	for (size_t i = 0; i < offset; i++)
		printf(" ");

	printf("AST: Type: \"%zu\"\n", root->type);

	if (root->value != NULL)
		ast_print(root->value, offset + 3);

	if (root->children == NULL)
		return;

	for (size_t i = 0; i < root->children->size; i++)
		ast_print(root->children->items[i], offset + 3);
}