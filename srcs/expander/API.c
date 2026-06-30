#include "error.h"
#include "heredoc.h"
#include "expander.h"
#include "expander_.h"
#include "expander_expansion_.h"

t_error	expander_expand_word(const t_token *word, t_expansion *out)
{
	t_expander_args	args;

	args.value = word->value;
	args.role = EXPANDER_ASSIGNMENT;
	args.contexts = &(word->contexts);
	args.assignment_offset = word->assignment_offset;
	return (expander_expand(out, &args));
}

t_error	expander_expand_filename(const t_token *filename, t_expansion *out)
{
	t_expander_args	args;

	args.value = filename->value;
	args.contexts = &(filename->contexts);
	args.role = EXPANDER_REDIRECT_FILENAME;
	args.assignment_offset = filename->assignment_offset;
	return (expander_expand(out, &args));
}

t_error	expander_expand_heredoc_delim(
			const t_string *heredoc_delim,
			t_string *out)
{
	t_error			err;
	t_string		src;
	t_expander_args	args;
	t_expansion		expansion;

	args.contexts = NULL;
	args.value = *heredoc_delim;
	args.assignment_offset = -1;
	args.role = EXPANDER_HEREDOC_DELIMITER;
	err = expander_expand(&expansion, &args);
	if (err.type)
		return (err);
	if (expansion.len == 1)
	{
		expansion_get(&expansion, 0, &src);
		if (!string_init(out, 0, src.data, -1))
			err = error_sys();
	}
	else
		return (err = error(ERR_EXP_TOO_MANY_FIELDS));
	return (expansion_free(&expansion), err);
}

t_error	expander_expand_heredoc_body(const t_string *heredoc_file_path)
{
	t_error			err;
	t_expander_args	args;
	t_expansion		expansion;
	t_string		heredoc_body;
	t_context_stack	stack;

	err = read_heredoc_body(heredoc_file_path, &heredoc_body);
	if (err.type)
		return (err);
	args.value = heredoc_body;
	context_stack_init(&stack);
	err = heredoc_track_body_context(&heredoc_body, &stack);
	if (err.type)
		return (string_free(&heredoc_body), err);
	args.assignment_offset = -1;
	args.role = EXPANDER_HEREDOC_BODY;
	err = expander_expand(&expansion, &args);
	if (err.type)
		return (string_free(&heredoc_body), err);
	err = store_expansion_result_in_heredoc_file(heredoc_file_path, &expansion);
	context_stack_free(&stack);
	return (expansion_free(&expansion), string_free(&heredoc_body), err);
}

t_error	expander_expand_assignment(const t_token *assignment, t_string *out)
{
	t_error			err;
	t_string		src;
	t_expander_args	args;
	t_expansion		expansion;

	args.value = assignment->value;
	args.role = EXPANDER_ASSIGNMENT;
	args.contexts = &(assignment->contexts);
	args.assignment_offset = assignment->assignment_offset;
	err = expander_expand(&expansion, &args);
	if (err.type)
		return (err);
	if (expansion.len == 1)
	{
		expansion_get(&expansion, 0, &src);
		if (!string_init(out, 0, src.data, (long)src.len))
			err = error_sys();
	}
	else
		return (err = error(ERR_EXP_TOO_MANY_FIELDS));
	return (expansion_free(&expansion), err);
}
