#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"

static inline t_error	add_word(
	t_parser *parser,
	t_cst_node *word,
	t_ast_for *out)
{
	t_buff	token_value;
	t_error	err;

	err = converter_dup_buff(parser, word, 0, &token_value);
	if (err.type)
		return (err);
	if (!vector_push(&out->words, &token_value))
		return (buff_free(&token_value), error_sys());
	return (err);
}

/*
wordlist         : wordlist WORD
                 |          WORD
                 ;
*/
static inline t_error	convert_wordlist(
	t_parser *parser,
	t_cst_node *wordlist,
	t_ast_for *out)
{
	t_error	err;

	if (wordlist->child_count == 1)
		return (add_word(parser, wordlist->children[0], out));
	err = convert_wordlist(parser, wordlist->children[0], out);
	if (err.type)
		return (err);
	return (add_word(parser, wordlist->children[1], out));
}

/*
do_group         : Do compound_list Done
                 ;
*/
static inline t_error	convert_do_group(
	t_parser *parser,
	t_cst_node *do_group,
	t_ast_for *out)
{
	return (convert_list(parser, do_group->children[1], &out->body));
}

static inline t_error	convert_for_clause(
	t_parser *parser,
	t_cst_node *for_clause,
	t_ast_for *out)
{
	t_buff		default_word;
	t_cst_node	*do_group;
	t_error		err;

	err = converter_dup_buff(parser, for_clause->children[1], 0, &out->var_name);
	if (err.type)
		return (err);
	if (for_clause->child_count <= 4)
	{
		if (!buff_init(&default_word, 0, "\"$@\"", -1))
			return (error_sys());
		if (!vector_push(&out->words, &default_word))
			return (buff_free(&default_word), error_sys());
	}
	if (for_clause->child_count == 7)
		err = convert_wordlist(parser, for_clause->children[5], out);
	if (err.type)
		return (err);
	do_group = for_clause->children[for_clause->child_count - 1];
	return (convert_do_group(parser, do_group, out));
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
	t_cst_node *for_clause,
	t_ast_for *out)
{
	t_error		err;

	ast_for_init(out);
	err = convert_for_clause(parser, for_clause, out);
	if (err.type)
		ast_for_free(out);
	return (err);
}
