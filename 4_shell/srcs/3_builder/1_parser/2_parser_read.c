#include "parser_priv.h"
#include "scanner.h"
#ifdef DEBUG_PARSING
#include <stdio.h>		// DEBUG
# include "logs.h"		// DEBUG
#endif
#include <assert.h>	// DEBUG

static inline t_error	sym_conv2(t_token_type token_type, t_symbol *dst_symbol)
{
	if (token_type == TOKEN_NEWLINE)
		return (*dst_symbol = SYM_NEWLINE, error(ERR_NO));
	else if (token_type == TOKEN_SCOLON)
		return (*dst_symbol = SYM_SEMI, error(ERR_NO));
	else if (token_type == TOKEN_AMPERSAND)
		return (*dst_symbol = SYM_AMPERSAND, error(ERR_NO));
	else if (token_type == TOKEN_DSEMI)
		return (*dst_symbol = SYM_DSEMI, error(ERR_NO));
	else if (token_type == TOKEN_SEMI_AND)
		return (*dst_symbol = SYM_SEMI_AND, error(ERR_NO));
	else if (token_type == TOKEN_AND_IF)
		return (*dst_symbol = SYM_AND_IF, error(ERR_NO));
	else if (token_type == TOKEN_OR_IF)
		return (*dst_symbol = SYM_OR_IF, error(ERR_NO));
	else if (token_type == TOKEN_PIPE)
		return (*dst_symbol = SYM_PIPE, error(ERR_NO));
	else if (token_type == TOKEN_LPARENTHESIS)
		return (*dst_symbol = SYM_LPARENTHESIS, error(ERR_NO));
	else if (token_type == TOKEN_RPARENTHESIS)
		return (*dst_symbol = SYM_RPARENTHESIS, error(ERR_NO));
	*dst_symbol = SYM_error;
	return (error_print(error(ERR_POSIX_SYNTAX),
			"parser", "unkown token type", NULL, "%i", token_type));
}

static inline t_error	sym_conv(t_token_type token_type, t_symbol *dst_symbol)
{
	if (token_type == TOKEN_TOKEN)
		return (*dst_symbol = SYM_TOKEN, error(ERR_NO));
	else if (token_type == TOKEN_DOLPAREN)
		return (*dst_symbol = SYM_DOLPAREN, error(ERR_NO));
	else if (token_type == TOKEN_LESSAND)
		return (*dst_symbol = SYM_LESSAND, error(ERR_NO));
	else if (token_type == TOKEN_GREATAND)
		return (*dst_symbol = SYM_GREATAND, error(ERR_NO));
	else if (token_type == TOKEN_LESS)
		return (*dst_symbol = SYM_LESS, error(ERR_NO));
	else if (token_type == TOKEN_GREAT)
		return (*dst_symbol = SYM_GREAT, error(ERR_NO));
	else if (token_type == TOKEN_CLOBBER)
		return (*dst_symbol = SYM_CLOBBER, error(ERR_NO));
	else if (token_type == TOKEN_LESSGREAT)
		return (*dst_symbol = SYM_LESSGREAT, error(ERR_NO));
	else if (token_type == TOKEN_DGREAT)
		return (*dst_symbol = SYM_DGREAT, error(ERR_NO));
	else if (token_type == TOKEN_DLESS)
		return (*dst_symbol = SYM_DLESS, error(ERR_NO));
	else if (token_type == TOKEN_DLESSDASH)
		return (*dst_symbol = SYM_DLESSDASH, error(ERR_NO));
	else if (token_type == TOKEN_IO_NUMBER)
		return (*dst_symbol = SYM_IO_NUMBER, error(ERR_NO));
	else if (token_type == TOKEN_IO_LOCATION)
		return (*dst_symbol = SYM_IO_LOCATION, error(ERR_NO));
	else if (token_type == TOKEN_EOF)
		return (*dst_symbol = SYM_EOF, error(ERR_NO));
	return (sym_conv2(token_type, dst_symbol));
}

t_error	parser_read_next_symbol(t_parser *parser, bool continuation)
{
	t_token	token;
	t_error	err;

	assert(parser != NULL);
	err = scanner_get_next_token(&parser->scanner, &token, continuation);
	if (err.type != ERR_NO)
		return (err);
	err = sym_conv(token.type, &parser->lookahead_raw_symbol);
	if (err.type != ERR_NO)
		return (token_free(&token), err);
	parser->lookahead_symbol = parser->lookahead_raw_symbol;
#ifdef DEBUG_PARSING
	fprintf(stderr, "[PARSER] READ   => [%3zu] [%3zu - %3zu] %s%s%s",
		parser->lookahead_id, token.index.start, token.index.end, RED, token_type_to_string(token.type), NC);
	if (token.type == TOKEN_TOKEN)
		fprintf(stderr, " (%s%s%s)", BLUE, token.value.data, NC);
	if (token.ast_vector.len > 0)
		fprintf(stderr, " => %zu AST", token.ast_vector.len);
	if (token.assignment_offset >= 0)
		fprintf(stderr, " assignment_offset=%zu", token.assignment_offset);
	fprintf(stderr, "\n");
#endif
	if (token.type == TOKEN_NEWLINE)
	{
		err = parser_read_heredoc(parser);
		if (err.type)
			return (token_free(&token), parser_internal_error(err));
	}
	err = token_pool_push(&parser->token_pool, &token);
	if (err.type)
		return (token_free(&token), parser_internal_error(err));
	parser->lookahead_id = parser->token_pool.len - 1;
	return (err);
}
