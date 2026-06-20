#include "parser_priv.h"
#include "scanner.h"
# include <stdio.h>	// TODO: TMP DEBUG

static inline t_error	sym_conv1(t_token_type token_type, t_symbol *dst_symbol)
{
	if (token_type == TOKEN)
		*dst_symbol = SYM_TOKEN;
	else if (token_type == NEWLINE_)
		*dst_symbol = SYM_NEWLINE;
	else if (token_type == SCOLON)
		*dst_symbol = SYM_SEMI;
	else if (token_type == AMPERSAND)
		*dst_symbol = SYM_AMPERSAND;
	else if (token_type == DSEMI)
		*dst_symbol = SYM_DSEMI;
	else if (token_type == SEMI_AND)
		*dst_symbol = SYM_SEMI_AND;
	else if (token_type == AND_IF)
		*dst_symbol = SYM_AND_IF;
	else if (token_type == OR_IF)
		*dst_symbol = SYM_OR_IF;
	else if (token_type == PIPE)
		*dst_symbol = SYM_PIPE;
	else if (token_type == LPARENTHESIS)
		*dst_symbol = SYM_LPARENTHESIS;
	else if (token_type == RPARENTHESIS)
		*dst_symbol = SYM_RPARENTHESIS;
	else
		return (error(ERR_INVALID_SYNTAX));
	return (error(ERR_NO));
}

static inline t_error	sym_conv2(t_token_type token_type, t_symbol *dst_symbol)
{
	if (token_type == LESSAND)
		*dst_symbol = SYM_LESSAND;
	else if (token_type == GREATAND)
		*dst_symbol = SYM_GREATAND;
	else if (token_type == LESS)
		*dst_symbol = SYM_LESS;
	else if (token_type == GREAT)
		*dst_symbol = SYM_GREAT;
	else if (token_type == CLOBBER)
		*dst_symbol = SYM_CLOBBER;
	else if (token_type == LESSGREAT)
		*dst_symbol = SYM_LESSGREAT;
	else if (token_type == DGREAT)
		*dst_symbol = SYM_DGREAT;
	else if (token_type == DLESS)
		*dst_symbol = SYM_DLESS;
	else if (token_type == DLESSDASH)
		*dst_symbol = SYM_DLESSDASH;
	else if (token_type == IO_NUMBER)
		*dst_symbol = SYM_IO_NUMBER;
	else if (token_type == EOF_)
		*dst_symbol = SYM_EOF;
	else
		return (error(ERR_INVALID_SYNTAX));
	return (error(ERR_NO));
}

static t_error	symbol_convert(t_token *src_token, t_symbol *dst_symbol)
{
	t_error			err;
	t_token_type	token_type;

	token_type = src_token->type;
	err = sym_conv1(token_type, dst_symbol);
	if (err.type != ERR_NO)
		err = sym_conv2(token_type, dst_symbol);
	if (err.type != ERR_NO)
	{
		*dst_symbol = SYM_error;
		return (error_print(
			error(ERR_INVALID_SYNTAX),
			"Parser",
			"Invalid syntax: unkown token type",
			NULL,
			"%i", token_type));
	}
	return (err);
}

t_error	parser_read_next_symbol(t_parser *parser)
{
	t_token	token;
	t_error	err;

	token_init(&token);
	err = scanner_next_token(&token);
	printf("====> scanner_next_token() returned %i\n", (int)err.type);
	if (err.type != ERR_NO)
		return (err);
	if (!vector_push(&parser->tokens, &token))
	{
		token_free(&token);
		return (parser_internal_error());
	}
	err = symbol_convert(&token, &parser->lookahead_symbol);
	if (err.type != ERR_NO)
		return (err);
	parser->lookahead_id = parser->tokens.len - 1;
	printf("\n--------------------------------------------------\n");
	printf("[PARSER] READ index=%zu token=%s symbol=%s value=%s\n",
		parser->lookahead_id,
		token_type_to_string(token.type),
		symbol_to_string(parser->lookahead_symbol),
		buff_get_string(&token.value));
	return (error(ERR_NO));
}
