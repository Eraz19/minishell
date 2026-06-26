#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"
#include <stdlib.h>

static inline t_error	convert_for_add_word(
	t_parser *parser,
	t_cst_node *word,
	t_ast_for *out)
{
	t_token	*token;
	t_error	err;

	err = converter_get_token(parser, word, 0, &token);
	if (err.type)
		return (err);
	if (!vector_push(&out->words, &token))
		return (error_sys());
	return (err);
}

/*
wordlist         : wordlist WORD
                 |          WORD
                 ;
*/
static inline t_error	convert_for_wordlist(
	t_parser *parser,
	t_cst_node *wordlist,
	t_ast_for *out)
{
	t_error	err;

	if (wordlist->child_count == 1)
		return (convert_for_add_word(parser, wordlist->children[0], out));
	err = convert_for_wordlist(parser, wordlist->children[0], out);
	if (err.type)
		return (err);
	return (convert_for_add_word(parser, wordlist->children[1], out));
}


static inline t_error	convert_for_build_default_word(t_ast_for *out)
{
	t_token	*default_word;
	t_error	err;

	default_word = malloc(sizeof(*default_word));
	if (default_word)
		return (error_sys());
	token_init(default_word);
	if (!buff_append(&default_word->value, "\"$@\"", -1))
	{
		err = error_sys();
		free(default_word);
		return (err);
	}
	if (!vector_push(&out->words, &default_word))
	{
		err = error_sys();
		token_free(default_word);
		free(default_word);
		return (err);
	}
	return (error(ERR_NO));
}

/*
do_group         : Do compound_list Done
                 ;
*/
static inline t_error	convert_for_clause(
	t_parser *parser,
	t_cst_node *for_clause,
	t_ast_for *out)
{
	t_cst_node	*do_group;
	t_error		err;

	err = converter_get_token(
		parser, for_clause->children[1], 0, &out->var_name);
	if (err.type)
		return (err);
	if (for_clause->child_count <= 4)
		err = convert_for_build_default_word(out);
	else if (for_clause->child_count == 7)
		err = convert_for_wordlist(parser, for_clause->children[5], out);
	if (err.type)
		return (err);
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
