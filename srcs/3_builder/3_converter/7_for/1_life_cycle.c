#include "converter_priv.h"
#include <stdlib.h>

void	ast_for_init(t_ast_for *for_node)
{
	for_node->var_name = NULL;
	vector_init(&for_node->words, sizeof(t_token *), 0);
	ast_list_init(&for_node->body);
	for_node->word_token_is_owned = false;
}

void	ast_for_free(t_ast_for *for_node)
{
	t_token	*default_word_token;

	for_node->var_name = NULL;
	if (for_node->word_token_is_owned)
	{
		default_word_token = ((t_token **)for_node->words.data)[0];
		token_free(default_word_token);
		free(default_word_token);
		((t_token **)for_node->words.data)[0] = NULL;
		vector_free(&for_node->words, NULL);
	}
	else
		vector_free(&for_node->words, NULL);
	ast_list_free(&for_node->body);
	for_node->word_token_is_owned = false;
}
