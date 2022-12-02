#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

enum
{
	AST_COMPOUND,
	AST_NOOP
};

typedef struct AST
{
	size_t type;
	struct AST* child;
} AST;

typedef struct Parser
{
	Lexer* lexer;
	Token* token;
} Parser;

Parser* parser_create(Lexer* lexer);
AST* parser_parse(Parser* parser);

#endif