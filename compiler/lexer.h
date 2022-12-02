#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

enum
{
	TOKEN_NONE = 0,
	TOKEN_IDENTIFIER,
	TOKEN_NUMBER,
	TOKEN_EQUALS,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MULTIPLY,
	TOKEN_DIVIDE,
	TOKEN_LEFT_PARANTHESIS,
	TOKEN_RIGHT_PARANTHESIS,
	TOKEN_LEFT_BRACKET,
	TOKEN_RIGHT_BRACKET,
	TOKEN_LEFT_BRACE,
	TOKEN_RIGHT_BRACE,
	TOKEN_COMMA,
	TOKEN_COLON,
	TOKEN_SEMICOLON,
	TOKEN_SINGLE_QUOTES,
	TOKEN_DOUBLE_QUOTES,
	TOKEN_EOF
};

typedef struct Token
{
	size_t type;
	char* value;
} Token;

typedef struct Lexer
{
	const char* src;
	size_t size;
	char current;
	size_t index;
} Lexer;

Lexer* lexer_create(const char* src);
void lexer_advance(Lexer* lexer);
Token* lexer_get_next_token(Lexer* lexer);

const char* token_type_to_str(size_t type);

#endif