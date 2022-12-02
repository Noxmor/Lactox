#include "lexer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

Token* token_create(size_t type, char* value)
{
	Token* token = malloc(1 * sizeof(Token));
	token->type = type;
	token->value = value;
	return token;
}

Lexer* lexer_create(const char* src)
{
	Lexer* lexer = malloc(1* sizeof(Lexer));
	lexer->src = src;
	lexer->size = strlen(src);
	lexer->index = 0;
	lexer->current = lexer->src[lexer->index];
	return lexer;
}

void lexer_advance(Lexer* lexer)
{	
	if (lexer->index < lexer->size && lexer->current != '\0')
		lexer->current = lexer->src[++lexer->index];
}

void lexer_skip(Lexer* lexer)
{
	while (lexer->current == ' ' || lexer->current == '\r' || lexer->current == '\n' || lexer->current == '\t')
		lexer_advance(lexer);
}

Token* lexer_advance_with_token(Lexer* lexer, Token* token)
{
	lexer_advance(lexer);
	return token;
}

Token* lexer_advance_with_current(Lexer* lexer, size_t type)
{
	char* value = malloc(2 * sizeof(char));
	value[0] = lexer->current;
	value[1] = '\0';

	return lexer_advance_with_token(lexer, token_create(type, value));
}

char lexer_peek(Lexer* lexer, size_t offset)
{
	return lexer->index + offset < lexer->size ? lexer->src[lexer->index + offset] : '\0';
}

Token* lexer_parse_identifier(Lexer* lexer)
{
	char* value = calloc(1, sizeof(char));

	while (isalnum(lexer->current))
	{
		value = realloc(value, (strlen(value) + 2) * sizeof(char));
		strcat(value, (char[]) { lexer->current, '\0' });
		lexer_advance(lexer);
	}

	return token_create(TOKEN_IDENTIFIER, value);
}

Token* lexer_parse_number(Lexer* lexer)
{
	char* value = calloc(1, sizeof(char));

	while (isdigit(lexer->current))
	{
		value = realloc(value, (strlen(value) + 2) * sizeof(char));
		strcat(value, (char[]) { lexer->current, '\0' });
		lexer_advance(lexer);
	}

	return token_create(TOKEN_NUMBER, value);
}

Token* lexer_get_next_token(Lexer* lexer)
{
	while (lexer->current != '\0')
	{
		lexer_skip(lexer);

		if (isalpha(lexer->current))
			return lexer_parse_identifier(lexer);

		if (isdigit(lexer->current))
			return lexer_parse_number(lexer);

		switch (lexer->current)
		{
			case '=': return lexer_advance_with_current(lexer, TOKEN_EQUALS);
			case '+': return lexer_advance_with_current(lexer, TOKEN_PLUS);
			case '-': return lexer_advance_with_current(lexer, TOKEN_MINUS);
			case '*': return lexer_advance_with_current(lexer, TOKEN_MULTIPLY);
			case '/': return lexer_advance_with_current(lexer, TOKEN_DIVIDE);
			case '(': return lexer_advance_with_current(lexer, TOKEN_LEFT_PARANTHESIS);
			case ')': return lexer_advance_with_current(lexer, TOKEN_RIGHT_PARANTHESIS);
			case '[': return lexer_advance_with_current(lexer, TOKEN_LEFT_BRACKET);
			case ']': return lexer_advance_with_current(lexer, TOKEN_RIGHT_BRACKET);
			case '{': return lexer_advance_with_current(lexer, TOKEN_LEFT_BRACE);
			case '}': return lexer_advance_with_current(lexer, TOKEN_RIGHT_BRACE);
			case ',': return lexer_advance_with_current(lexer, TOKEN_COMMA);
			case ':': return lexer_advance_with_current(lexer, TOKEN_COLON);
			case ';': return lexer_advance_with_current(lexer, TOKEN_SEMICOLON);
			case '\'': return lexer_advance_with_current(lexer, TOKEN_SINGLE_QUOTES);
			case '\"': return lexer_advance_with_current(lexer, TOKEN_DOUBLE_QUOTES); //TODO: Parse string token!

			case '\0': break;

			default: printf("[Lexer]: Encountered unexpected character '%c'!\n", lexer->current); exit(1); break;
		}

		return lexer_advance_with_token(lexer, token_create(TOKEN_NONE, NULL));
	}

	return token_create(TOKEN_EOF, NULL);
}