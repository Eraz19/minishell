#include <stdlib.h>
#include "heredoc.h"
#include "expander.h"
#include "expander_.h"

t_error	expander_expand_word(t_token *word, t_vector *out)
{
	size_t			i;
	t_error			err;
	t_expander_args	args;
	t_string		buff;
	char			**expansion;

	args.value = word->value;
	args.role = EXPANDER_ASSIGNMENT;
	args.contexts = &(word->contexts);
	args.assignment_offset = word->assignment_offset;
	err = expander_expand(&expansion, &args);
	if (err.type)
		return (err);
	i = 0;
	while (expansion[i])
	{
		if (!string_init(&buff, 0, expansion[i], -1))
			return (err = error_sys(), str_array_free(&expansion), err);
		if (!vector_push(out, &buff))
			return (err = error_sys(), string_free(&buff),
				str_array_free(&expansion), err);
		i++;
	}
	return (str_array_free(&expansion), err);
}

t_error	expander_expand_filename(t_token *filename, t_vector *out)
{
	size_t			i;
	t_error			err;
	t_expander_args	args;
	t_string		buff;
	char			**expansion;

	args.value = filename->value;
	args.contexts = &(filename->contexts);
	args.role = EXPANDER_REDIRECT_FILENAME;
	args.assignment_offset = filename->assignment_offset;
	err = expander_expand(&expansion, &args);
	if (err.type)
		return (err);
	i = 0;
	while (expansion[i])
	{
		if (!string_init(&buff, 0, expansion[i], -1))
			return (err = error_sys(), str_array_free(&expansion), err);
		if (!vector_push(out, &buff))
			return (err = error_sys(), string_free(&buff),
				str_array_free(&expansion), err);
		i++;
	}
	return (str_array_free(&expansion), err);
}

t_error	expander_expand_heredoc_delim(t_string *heredoc_delim, t_string *out)
{
	t_error			err;
	t_expander_args	args;
	char			**expansion;

	args.contexts = NULL;
	args.value = *heredoc_delim;
	args.assignment_offset = -1;
	args.role = EXPANDER_HEREDOC_DELIMITER;
	err = expander_expand(&expansion, &args);
	if (err.type)
		return (err);
	if (expansion[0] != NULL)
	{
		if (!string_init(out, 0, expansion[0], -1))
			return (err = error_sys(), str_array_free(&expansion), err);
	}
	return (str_array_free(&expansion), err);
}

t_error	expander_expand_heredoc_body(t_string *heredoc_file_path)
{
	t_error			err;
	t_expander_args	args;
	char			**expansion;
	t_string		heredoc_body;

	err = read_heredoc_body(heredoc_file_path, &heredoc_body);
	if (err.type)
		return (err);
	args.value = heredoc_body;
	context_stack_init(args.contexts);
	err = heredoc_track_body_context(&heredoc_body, args.contexts);
	if (err.type)
		return (string_free(&heredoc_body), err);
	args.assignment_offset = -1;
	args.role = EXPANDER_HEREDOC_BODY;
	err = expander_expand(&expansion, &args);
	if (err.type)
		return (string_free(&heredoc_body), err);
	if (expansion[0] != NULL)
	{
		heredoc_body.len = 0;
		if (!string_append_n(&heredoc_body, expansion[0], -1))
			return (err = error_sys(), str_array_free(&expansion), string_free(&heredoc_body), err);
		if (heredoc_body_save_content(heredoc_file_path, &heredoc_body).type)
			return (err = error_sys(), str_array_free(&expansion), string_free(&heredoc_body), err);
	}
	return (str_array_free(&expansion), string_free(&heredoc_body), err);
}

t_error	expander_expand_assignment(t_token *assignment, t_string *out)
{
	t_error			err;
	t_expander_args	args;
	char			**expansion;

	args.value = assignment->value;
	args.role = EXPANDER_ASSIGNMENT;
	args.contexts = &(assignment->contexts);
	args.assignment_offset = assignment->assignment_offset;
	err = expander_expand(&expansion, &args);
	if (err.type)
		return (err);
	if (expansion[0] != NULL)
	{
		if (!string_init(out, 0, expansion[0], (long)str_len(expansion[0])))
			return (err = error_sys(), str_array_free(&expansion), err);
	}
	return (str_array_free(&expansion), err);
}
