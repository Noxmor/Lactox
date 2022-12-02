#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "util/list.h"

enum
{
	AST_COMPOUND = 0,
	AST_STATEMENT,
	AST_VARIABLE,
	AST_ASSIGNMENT,
	AST_FUNCTION,
	AST_FUNCTION_CALL,
	AST_NOOP
};

typedef struct AST
{
	size_t type;
	char* name;
	size_t data_type;
	struct AST* value;
	List* children;
} AST;

typedef struct Parser
{
	Lexer* lexer;
	Token* token;
} Parser;

Parser* parser_create(Lexer* lexer);
AST* parser_parse(Parser* parser);

void ast_print(AST* root, size_t offset);

#endif