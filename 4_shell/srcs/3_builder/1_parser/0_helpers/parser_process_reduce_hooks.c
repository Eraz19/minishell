#include "parser_priv.h"
#include "parser.h"
#include "utils.h"
#include <assert.h>	// DEBUG
#ifdef DEBUG_PARSING
# include "logs.h"	// DEBUG
#endif

static inline t_error	parser_check_fname(
							const t_parser *parser,
							const t_parser_item *rhs)
{
	const t_token	*token;

	token = parser_get_token(parser, rhs[0].tokens_start_id);
	if (!name_is_valid_str(&token->value))
		return (error_print(error(ERR_POSIX_SYNTAX),
			"parser", "invalid function name", NULL, "%s", token->value.data));
#ifdef DEBUG_PARSING
	else
		fprintf(stderr, "[PARSER] %sfunction name is valid%s\n", YELLOW, NC);
#endif
	return (error(ERR_NO));
}

static inline t_error	parser_register_heredoc(
							t_parser *parser,
							t_parser_item *lhs,
							t_parser_item *rhs)
{
	if (!vector_push(&parser->here_stack, &lhs->cst_node))
		return (error_sys());
#ifdef DEBUG_PARSING
	fprintf(stderr, YELLOW "[PARSER] heredoc registered (%s%s%s)\n" NC,
		BLUE,
		parser_get_token(parser, rhs[1].tokens_start_id)->value.data,
		YELLOW);
#else
	(void)rhs;
#endif
	return (error(ERR_NO));
}

t_error	parser_process_reduce_hooks(
			t_parser *parser,
			size_t rule_id,
			t_parser_item *lhs,
			t_parser_item *rhs)
{
	if (rule_id == RULE_FNAME_1)
		return (parser_check_fname(parser, rhs));
	else if (rule_id == RULE_IO_HERE_1 || rule_id == RULE_IO_HERE_2)
		return (parser_register_heredoc(parser, lhs, rhs));
	else if (parser->search_cmd_sub_end == false
		&& (rule_id == RULE_COMPLETE_COMMAND_1
			|| rule_id == RULE_COMPLETE_COMMAND_2))
		return (parser_store_cst(parser, lhs));
	return (error(ERR_NO));
}
