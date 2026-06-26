#include "parser_priv.h"
#include "scanner.h"

static inline t_error	sym_conv2(t_token_type token_type, t_symbol *dst_symbol)
{
	if (token_type == TOKEN_TOKEN)
		*dst_symbol = SYM_TOKEN;
	else if (token_type == TOKEN_NEWLINE)
		*dst_symbol = SYM_NEWLINE;
	else if (token_type == TOKEN_SCOLON)
		*dst_symbol = SYM_SEMI;
	else if (token_type == TOKEN_AMPERSAND)
		*dst_symbol = SYM_AMPERSAND;
	else if (token_type == TOKEN_DSEMI)
		*dst_symbol = SYM_DSEMI;
	else if (token_type == TOKEN_SEMI_AND)
		*dst_symbol = SYM_SEMI_AND;
	else if (token_type == TOKEN_AND_IF)
		*dst_symbol = SYM_AND_IF;
	else if (token_type == TOKEN_OR_IF)
		*dst_symbol = SYM_OR_IF;
	else if (token_type == TOKEN_PIPE)
		*dst_symbol = SYM_PIPE;
	else if (token_type == TOKEN_LPARENTHESIS)
		*dst_symbol = SYM_LPARENTHESIS;
	else if (token_type == TOKEN_RPARENTHESIS)
		*dst_symbol = SYM_RPARENTHESIS;
	else
		return (error(ERR_INVALID_SYNTAX));
	return (error(ERR_NO));
}

static inline t_error	sym_conv(t_token_type token_type, t_symbol *dst_symbol)
{
	if (token_type == TOKEN_LESSAND)
		*dst_symbol = SYM_LESSAND;
	else if (token_type == TOKEN_GREATAND)
		*dst_symbol = SYM_GREATAND;
	else if (token_type == TOKEN_LESS)
		*dst_symbol = SYM_LESS;
	else if (token_type == TOKEN_GREAT)
		*dst_symbol = SYM_GREAT;
	else if (token_type == TOKEN_CLOBBER)
		*dst_symbol = SYM_CLOBBER;
	else if (token_type == TOKEN_LESSGREAT)
		*dst_symbol = SYM_LESSGREAT;
	else if (token_type == TOKEN_DGREAT)
		*dst_symbol = SYM_DGREAT;
	else if (token_type == TOKEN_DLESS)
		*dst_symbol = SYM_DLESS;
	else if (token_type == TOKEN_DLESSDASH)
		*dst_symbol = SYM_DLESSDASH;
	else if (token_type == TOKEN_IO_NUMBER)
		*dst_symbol = SYM_IO_NUMBER;
	else if (token_type == TOKEN_EOF)
		*dst_symbol = SYM_EOF;
	else
		return (sym_conv2(token_type, dst_symbol));
	return (error(ERR_NO));
}

static t_error	symbol_convert(t_token *src_token, t_symbol *dst_symbol)
{
	t_error			err;
	t_token_type	token_type;

	token_type = src_token->type;
	err = sym_conv(token_type, dst_symbol);
	if (err.type != ERR_NO)
	{
		*dst_symbol = SYM_error;
		return (error_print(
			error(ERR_INVALID_SYNTAX),
			"parser",
			"unkown token type",
			NULL,
			"%i", token_type));
	}
	return (err);
}

# include <stdio.h>		// DEBUG
# include "logs.h"		// DEBUG
# include <stdlib.h>	// DEBUG
t_error	parser_read_next_symbol(t_parser *parser)
{
	t_token	token;
	t_error	err;

	err = scanner_get_next_token(&token);
	if (err.type != ERR_NO)
		return (err);
	if (!vector_push(&parser->tokens, &token))
		return (token_free(&token), parser_internal_error());
	err = symbol_convert(&token, &parser->lookahead_raw_symbol);
	if (err.type != ERR_NO)
		return (err);
	parser->lookahead_symbol = parser->lookahead_raw_symbol;
	parser->lookahead_id = parser->tokens.len - 1;
	// fprintf(stderr, "\n--------------------------------------------------\n");
	char *token_value = buff_get_string(&token.value);
	fprintf(stderr, "[PARSER] READ   => [%3zu] %s%s%s",
		parser->lookahead_id, RED, token_type_to_string(token.type), NC);
	if (token.type == TOKEN_TOKEN)
		fprintf(stderr, " (%s%s%s)", BLUE, token_value, NC);
	fprintf(stderr, "\n");
	free(token_value);
	// fprintf(stderr, "[PARSER] READ index=%zu token=%s symbol=%s value=%s\n",
	// 	parser->lookahead_id,
	// 	token_type_to_string(token.type),
	// 	symbol_to_string(parser->lookahead_raw_symbol),
	// 	buff_get_string(&token.value));
	// fprintf(stderr, "--------------------------------------------------\n");
	return (error(ERR_NO));
}
