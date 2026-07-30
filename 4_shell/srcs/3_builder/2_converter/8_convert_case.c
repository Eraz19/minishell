#include "error.h"
#include "parser_type.h"
#include "ast.h"
#include "converter_priv.h"
# include <assert.h>	// DEBUG

/*
pattern_list     :                  WORD
                 |              '(' WORD
                 | pattern_list '|' WORD
                 ;
*/
static inline t_error	convert_pattern_list(
							t_parser *parser,
							const t_cst_node *pattern_list,
							t_token_pool *pool)
{
	const t_cst_node	*word;
	t_error				err;

	if (pattern_list->child_count == 3)
	{
		err = convert_pattern_list(parser, pattern_list->children[0], pool);
		if (err.type)
			return (err);
	}
	word = pattern_list->children[pattern_list->child_count - 1];
	return (converter_transfer_token(parser, word, 0, pool));
}

/*
case_item_ns     : pattern_list ')' linebreak
                 | pattern_list ')' compound_list
                 ;
case_item        : pattern_list ')' linebreak     DSEMI linebreak
                 | pattern_list ')' compound_list DSEMI linebreak
                 | pattern_list ')' linebreak     SEMI_AND linebreak
                 | pattern_list ')' compound_list SEMI_AND linebreak
                 ;
*/
static inline t_error	convert_case_item(
							t_parser *parser,
							const t_cst_node *case_item,
							t_ast_case *out)
{
	t_token_pool	pool;
	t_ast_list		list;
	bool			fallthrough;
	t_error			err;

	token_pool_init(&pool);
	err = convert_pattern_list(parser, case_item->children[0], &pool);
	if (err.type)
		return (token_pool_free(&pool), err);
	if (!vector_push(&out->patterns, &pool))
		return (err = error_sys(), token_pool_free(&pool), err);
	if (case_item->children[2]->symbol == SYM_compound_list)
		err = convert_list(parser, case_item->children[2], &list);
	else
		ast_list_init(&list);
	if (err.type)
		return (err);
	if (!vector_push(&out->bodies, &list))
		return (err = error_sys(), ast_list_free(&list), err);
	fallthrough = case_item->child_count >= 4
		&& case_item->children[3]->symbol == SYM_SEMI_AND;
	if (!vector_push(&out->fallthrough, &fallthrough))
		return (err = error_sys(), err);
	return (err);
}

/*
case_list_ns     : case_list case_item_ns
                 |           case_item_ns
                 ;
case_list        : case_list case_item
                 |           case_item
                 ;
*/
static inline t_error	convert_case_list(
							t_parser *parser,
							const t_cst_node *case_list,
							t_ast_case *out)
{
	t_error	err;

	if (case_list->child_count > 1)
	{
		err = convert_case_list(parser, case_list->children[0], out);
		if (err.type == ERR_NO)
			err = convert_case_item(parser, case_list->children[1], out);
		return (err);
	}
	return (convert_case_item(parser, case_list->children[0], out));
}

/*
case_clause      : Case WORD linebreak in linebreak case_list    Esac
                 | Case WORD linebreak in linebreak case_list_ns Esac
                 | Case WORD linebreak in linebreak              Esac
                 ;
*/
t_error	convert_case(
			t_parser *parser,
			const t_cst_node *case_clause,
			t_ast_case *out)
{
	t_error		err;

	assert(parser != NULL);
	assert(case_clause != NULL);
	assert(out != NULL);
	ast_case_init(out);
	converter_take_token(parser, case_clause->children[1], 0, &out->word);
	if (case_clause->child_count == 7)
	{
		err = convert_case_list(parser, case_clause->children[5], out);
		if (err.type)
			ast_case_free(out);
		return (err);
	}
	return (error(ERR_NO));
}
