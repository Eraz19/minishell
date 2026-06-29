#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"
# include <assert.h>	// DEBUG

static inline t_error	add_and_or(
							const t_parser *parser,
							const t_cst_node *node,
							t_ast_list *out)
{
	t_ast_and_or	and_or;
	t_error			err;
	bool			default_async;

	err = convert_and_or(parser, node, &and_or);
	if (err.type)
		return (err);
	if (!vector_push(&out->and_ors, &and_or))
		return (err = error_sys(), ast_and_or_free(&and_or), err);
	default_async = false;
	if (!vector_push(&out->asyncs, &default_async))
		return (error_sys());
	return (error(ERR_NO));
}

static inline void	set_last_async(bool async, const t_ast_list *out)
{
	bool	*raw_asyncs;

	if (async == false)
		return ;
	raw_asyncs = (bool *)out->asyncs.data;
	raw_asyncs[out->and_ors.len - 1] = async;
}

// input = compound_list / complete_command / list
static inline t_error	parse_rec(
							const t_parser *parser,
							const t_cst_node *node,
							t_ast_list *out)
{
	const t_cst_node	*child;
	size_t				i;
	t_error				err;

	err = error(ERR_NO);
	i = 0;
	while (i < node->child_count && err.type == ERR_NO)
	{
		child = node->children[i];
		if (child->symbol == SYM_list
			|| child->symbol == SYM_term
			|| child->symbol == SYM_separator)
			err = parse_rec(parser, child, out);
		else if (child->symbol == SYM_and_or)
			err = add_and_or(parser, child, out);
		else if (child->symbol == SYM_separator_op)
			set_last_async(child->children[0]->symbol == SYM_AMPERSAND, out);
		i++;
	}
	return (err);
}

t_error	convert_list_add(
			const t_parser *parser,
			const t_cst_node *node,
			t_ast_list *out)
{
	t_error		err;

	assert(parser != NULL);
	assert(node != NULL);
	assert(out != NULL);
	if (node->symbol == SYM_subshell)
	{
		out->subshell = true;
		err = parse_rec(parser, node->children[1], out);
	}
	else
		err = parse_rec(parser, node, out);
	if (err.type)
		ast_list_free(out);
	return (err);
}

/*
subshell         : '(' compound_list ')'
                 ;
compound_list    : linebreak term
                 | linebreak term separator
                 ;
term             : term separator and_or
                 |                and_or
                 ;
complete_command : list separator_op
                 | list
                 ;
list             : list separator_op and_or
                 |                   and_or
                 ;
separator        : separator_op linebreak
                 | newline_list
                 ;
separator_op     : '&'
                 | ';'
                 ;
*/
// input = subshell / compound_list / complete_command
t_error	convert_list(
			const t_parser *parser,
			const t_cst_node *node,
			t_ast_list *out)
{
	assert(parser != NULL);
	assert(node != NULL);
	assert(out != NULL);
	ast_list_init(out);
	return (convert_list_add(parser, node, out));
}
