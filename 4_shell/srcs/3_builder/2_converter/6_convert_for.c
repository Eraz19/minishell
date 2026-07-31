#include "error.h"
#include "parser_type.h"
#include "ast.h"
#include "converter_priv.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

static inline t_error	convert_for_transfer(
							t_parser *parser,
							const t_cst_node *wordlist,
							size_t child_id,
							t_ast_for *out)
{
	const t_cst_node	*child;

	child = wordlist->children[child_id];
	return (converter_transfer_token(parser, child, 0, &out->words));
}

/*
wordlist         : wordlist WORD
                 |          WORD
                 ;
*/
static inline t_error	convert_for_wordlist(
							t_parser *parser,
							const t_cst_node *wordlist,
							t_ast_for *out)
{
	t_error	err;

	if (wordlist->child_count == 1)
		return (convert_for_transfer(parser, wordlist, 0, out));
	err = convert_for_wordlist(parser, wordlist->children[0], out);
	if (err.type)
		return (err);
	return (convert_for_transfer(parser, wordlist, 1, out));
}

/*
do_group         : Do compound_list Done
                 ;
*/
static inline t_error	convert_for_clause(
							t_parser *parser,
							const t_cst_node *for_clause,
							t_ast_for *out)
{
	const t_cst_node	*do_group;
	t_error				err;

	converter_take_token(parser, for_clause->children[1], 0, &out->var_name);
	out->has_in = for_clause->child_count >= 6;
	if (for_clause->child_count == 7)
	{
		err = convert_for_wordlist(parser, for_clause->children[4], out);
		if (err.type)
			return (err);
	}
	do_group = for_clause->children[for_clause->child_count - 1];
	return (convert_list(parser, do_group->children[1], &out->body));
}

/*
for_clause       : For name                                      do_group
                 | For name                       sequential_sep do_group
                 | For name linebreak in          sequential_sep do_group
                 | For name linebreak in wordlist sequential_sep do_group
                 ;
name             : NAME
                 ;
in               : In
                 ;
*/
t_error	convert_for(
			t_parser *parser,
			const t_cst_node *for_clause,
			t_ast_for *out)
{
	t_error		err;

	assert(parser != NULL);
	assert(for_clause != NULL);
	assert(out != NULL);
	ast_for_init(out);
	err = convert_for_clause(parser, for_clause, out);
	if (err.type)
		ast_for_free(out);
	return (err);
}
