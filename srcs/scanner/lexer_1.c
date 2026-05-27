/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 11:05:01 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/27 18:09:14 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* FOR LATER

typedef enum e_esc_sequence
{
	ESC_NONE,
	ESC_DQUOTE,				// \"
	ESC_SQUOTE,				// \'
	ESC_BACKSLASH,			// '\\'
	ESC_ALERT,				// \a
	ESC_BACKSPACE,			// \b
	ESC_ESCAPE,				// \e
	ESC_FORMFEED,			// \f
	ESC_NEWLINE,			// \n
	ESC_CARRIAGE_RETURN,	// \r
	ESC_TAB,				// \t
	ESC_VTAB,				// \v
	ESC_CONTROL_CHAR,		// \cX
	ESC_HEX,				// \xXX
	ESC_OCTAL				// \ddd
}	t_esc_sequence;

void	insert_to_word(t_lexer *lexer, const char *str, size_t offset)
{
	size_t	len;

	len = str_len(str);
	if (buff_append(&lexer->token, str, (long)len) == false)
		return (on_lex_failure(lexer, ERR_LIBC));
	advance(lexer, offset);
}

bool	is_octal_digit(char c)
{
	return (c >= '0' && c <= '7');
}

// ------------ ESC SEQUENCE ------------

void	detect_esc_sequence_quotes(t_esc_sequence *res, t_lexer *lexer)
{
	const char	*input_ptr;	

	input_ptr = lexer->input + lexer->i + 1;
	if (input_ptr[0] == '\'')
		*res = ESC_SQUOTE;
	else if (input_ptr[0] == '\\')
		*res = ESC_BACKSLASH;
	else if (input_ptr[0] == '"')
		*res = ESC_DQUOTE;
}

void	detect_esc_sequence_mnemonics(t_esc_sequence *res, t_lexer *lexer)
{
	const char	*input_ptr;	

	input_ptr = lexer->input + lexer->i + 1;
	if (input_ptr[1] == 'a')
		*res = ESC_ALERT;
	else if (input_ptr[1] == 'b')
		*res = ESC_BACKSPACE;
	else if (input_ptr[1] == 'f')
		*res = ESC_FORMFEED;
	else if (input_ptr[1] == 'n')
		*res = ESC_NEWLINE;
	else if (input_ptr[1] == 'r')
		*res = ESC_CARRIAGE_RETURN;
	else if (input_ptr[1] == 't') 
		*res = ESC_TAB;
	else if (input_ptr[1] == 'v')
		*res = ESC_VTAB;
	else if (input_ptr[1] == 'e')
		*res = ESC_ESCAPE;
}

void	delect_esc_sequence_special(t_esc_sequence *res, t_lexer *lexer)
{
	const char	*input_ptr;	

	input_ptr = lexer->input + lexer->i + 1;
	if (input_ptr[1] == 'c')
		*res = ESC_CONTROL_CHAR;
	else if (input_ptr[1] == 'x')
		*res = ESC_HEX;
	else if (is_octal_digit(input_ptr[1]))
		*res = ESC_OCTAL;
}

t_esc_sequence	detect_esc_sequence(t_lexer *lexer)
{
	t_esc_sequence	esc_seq;
	const char		*input_ptr;

	esc_seq = ESC_NONE;
	input_ptr = lexer->input + lexer->i;
	if (input_ptr[0] == '\\')
	{
		detect_esc_sequence_quotes(&esc_seq, lexer);
		if (esc_seq == ESC_NONE)
			delect_esc_sequence_special(&esc_seq, lexer);
		if (esc_seq == ESC_NONE)
			detect_esc_sequence_mnemonics(&esc_seq, lexer);
	}
	return (esc_seq);
}


void	consume_esc_sequence_quote(t_lexer *lexer, t_esc_sequence *esc_seq)
{
	if (*esc_seq == ESC_DQUOTE)
		insert_to_word(lexer, "\"", 2);
	else if (*esc_seq == ESC_SQUOTE)
		insert_to_word(lexer, "\'", 2);
	else if (*esc_seq == ESC_BACKSLASH)
		insert_to_word(lexer, "\\", 2);
}

void	consume_esc_sequence_mnemonics(t_lexer *lexer, t_esc_sequence *esc_seq)
{
	if (*esc_seq == ESC_ALERT)
		insert_to_word(lexer, "\a", 2);
	else if (*esc_seq == ESC_BACKSPACE)
		insert_to_word(lexer, "\b", 2);
	else if (*esc_seq == ESC_ESCAPE)
		insert_to_word(lexer, "\e", 2);
	else if (*esc_seq == ESC_FORMFEED)
		insert_to_word(lexer, "\f", 2);
	else if (*esc_seq == ESC_NEWLINE)
		insert_to_word(lexer, "\n", 2);
	else if (*esc_seq == ESC_CARRIAGE_RETURN)
		insert_to_word(lexer, "\r", 2);
	else if (*esc_seq == ESC_TAB)
		insert_to_word(lexer, "\t", 2);
	else if (*esc_seq == ESC_VTAB)
		insert_to_word(lexer, "\v", 2);
}

void	consume_esc_sequence_special(t_lexer *lexer, t_esc_sequence *esc_seq)
{
	if (*esc_seq == ESC_CONTROL_CHAR)
		
	else if (*esc_seq == ESC_HEX)
		
	else if (*esc_seq == ESC_OCTAL)
}

void	consume_esc_sequence(t_lexer *lexer, t_esc_sequence *esc_seq)
{
	if (*esc_seq == ESC_DQUOTE ||
		*esc_seq == ESC_SQUOTE ||
		*esc_seq == ESC_BACKSLASH)
		consume_esc_sequence_quote(lexer, esc_seq);
	else if (*esc_seq == ESC_HEX ||
		*esc_seq == ESC_CONTROL_CHAR ||
		*esc_seq == ESC_OCTAL)
		consume_esc_sequence_special(lexer, esc_seq);
	else
		consume_esc_sequence_mnemonics(lexer, esc_seq);
}
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include "libft.h"
#include "error.h"

// >>>>>>>>>>>>>>>>>>>>>>>>> Expander <<<<<<<<<<<<<<<<<<<<<<<<

// ================== Quote Removal Header ==================

typedef struct s_quote_removal
{
	size_t	i;
	t_error	err;
	t_buff	input;
	t_buff	expanded;
	bool	is_escaping;
	bool	(*is_ending)(char, bool);
	bool	(*is_in_whitelist)(char, bool);
}	t_quote_removal;

// ================== Quote Removal Code ==================

// ::::::::::::::::::: UTILS :::::::::::::::::::

void	keep(t_quote_removal *state)
{
    if (!buff_append(&state->expanded, &state->input.data[state->i], 1))
    {
        state->err = ERR_LIBC;
        return ;
    }
}

void	advance_(t_quote_removal *state, size_t offset)
{
	state->i += offset;
}

void	consume_(t_quote_removal *state)
{
	keep(state);
	advance_(state, 1);
}

// ::::::::::::::::::: API :::::::::::::::::::

// ----------- UTILS -----------

bool	quote_removal(t_quote_removal *state)
{
	if (state->input.data[state->i] == '\\')
	{
		if (state->i + 1 >= state->input.len)
			return (consume_(state), true);
		else
		{
			if (!state->is_in_whitelist(state->input.data[state->i + 1], false))
				keep(state);
			if (state->err != ERR_NO)
				return (true);
			advance_(state, 1);
			if (state->is_escaping)
				return (consume_(state), true);
		}
	}
	else
	{
		if (state->is_ending != NULL &&
			state->is_ending(state->input.data[state->i], false))
			return (advance_(state, 1), false);
		return (consume_(state), true);
	}
}

// ----------- SQUOTE -----------

void	quote_removal_squote(t_quote_removal *state)
{
	advance_(state, 1);
	state->is_escaping = false;
	state->is_ending = is_squote_ending;
	state->is_in_whitelist = is_squote_whitelist;
	while (state->i < state->input.len)
	{
		if (state->err != ERR_NO || !quote_removal(state))
			return ;
	}
}

// ----------- DQUOTE -----------

void	quote_removal_dquote(t_quote_removal *state)
{
	advance_(state, 1);
	state->is_escaping = true;
	state->is_ending = is_dquote_ending;
	state->is_in_whitelist = is_dquote_whitelist;
	while (state->i < state->input.len)
	{
		if (state->err != ERR_NO || !quote_removal(state))
			return ;
	}
}

// ----------- DOLLAR SQUOTE -----------

void	quote_removal_dollar_squote(t_quote_removal *state)
{
	advance_(state, 2);
	state->is_escaping = true;
	state->is_ending = is_dollar_squote_ending;
	state->is_in_whitelist = is_dollar_squote_whitelist;
	while (state->i < state->input.len)
	{
		if (state->err != ERR_NO || !quote_removal(state))
			return ;
	}
}

// ----------- TOP LEVEL -----------

void	quote_removal_top_level(t_quote_removal *state)
{
	state->is_ending = NULL;
	state->is_escaping = true;
	state->is_in_whitelist = is_top_level_whitelist;
	quote_removal(state), true;
}

// ----------- API -----------

t_error	expander_quote_removal(t_quote_removal *state)
{
	state->i = 0;
    state->err = ERR_NO;
	if (!buff_init(&state->expanded, state->input.len, NULL, 0))
		return (ERR_LIBC);
	while (state->i < state->input.len)
	{
		if (state->err != ERR_NO)
			return (state->err);
		if (state->input.data[state->i] == '\'') 
			quote_removal_squote(state);
		else if (state->i + 1 < state->input.len &&
			state->input.data[state->i] == '$' &&
			state->input.data[state->i + 1] == '\'')
			quote_removal_dollar_squote(state);
		else if (state->input.data[state->i] == '\"')
			quote_removal_dquote(state);
		else
			quote_removal_top_level(state);
	}
	return (state->err);
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>*<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// >>>>>>>>>>>>>>>>>>>>>>>>> Scanner <<<<<<<<<<<<<<<<<<<<<<<<

// ================== Context Stack Header ==================

typedef enum e_scanner_ctx
{
	NONE_,
	SQUOTE,			// '
	DQUOTE,			// "
	DOLLAR_SQUOTE, 	// $'
	BACKTICK,		// `
	CMD_SUB,  		// $(
	ARITH,     		// $((
	PARAM,     		// ${
}   t_scanner_ctx;

typedef t_vector	t_scanner_ctx_stack;
	
// ================== Token Header ==================

typedef struct s_lexer	t_lexer;

typedef enum e_token_type
{
	NONE,
	TOKEN,			// - Non-specific token (WORD, NAME, ASSIGNMENT_WORD, ...) that doesn't fit into other categories
	// control
	NEWLINE_,		// `\n` - command separator
	SCOLON,			// `;`- command separator
	AMPERSAND,		// `&` - background command separator
	DSEMI,			// `;;` - case separator
	SEMI_AND,		// `;&` - case fallthrough
	AND_IF,			// `&&` - logical AND operator
	OR_IF,			// `||` - logical OR operator
	PIPE,			// `|` - pipeline operator
	LPARENTHESIS,	// `(` - subshell start
	RPARENTHESIS,	// `)` - subshell end
	// redirection
	LESSAND,		// `<&` - duplicate input file descriptor
	GREATAND,		// `>&` - duplicate output file descriptor
	LESS,			// `<` - input redirection
	GREAT,			// `>` - output redirection
	CLOBBER,		// `>|` - output redirection with clobbering (force overwrite)
	LESSGREAT,		// `<>` - input/output redirection
	DGREAT,			// `>>` - append redirection
	DLESS,			// `<<` - here document
	DLESSDASH		// `<<-` - here document with tab stripping
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	t_buff			value;
//	const char		*input_ptr;
}	t_token;

t_token	create_token(t_lexer *lexer);

// ================== Reader Header ==================

typedef struct stat	t_file_stat;

typedef struct s_reader
{
	t_scanner_ctx_stack	*ctx;
}	t_reader;

t_error	reader_continuation(char **input);

// ================== Lexer Header ==================

typedef struct s_escape_handler
{
	bool	(*is_in_context)(t_lexer *);
	bool	(*is_in_whitelist)(char, bool);
	bool	(*is_line_continuation)(t_lexer *, bool);
}	t_escape_handler;

typedef struct s_unescape_handler
{
	void	*special_args;
	bool	(*is_in_context)(t_lexer *);
	bool	(*special_handler)(t_lexer *, void *);
}	t_unescape_handler;

typedef struct s_ctx_handler
{
	void	*unescaped_args;
	bool	(*start)(t_lexer *);
	bool	(*escape)(t_lexer *);
	bool	(*quoting)(t_lexer *);
	bool	(*is_ending)(char, bool);
	bool	(*substitution)(t_lexer *);
	bool	(*is_in_context)(t_lexer *);
	bool	(*unescaped)(t_lexer *, void *);
}	t_ctx_handler;

typedef struct s_lexer
{
	size_t				i;
	t_error				err;
	t_scanner_ctx_stack	*ctx;
	t_token				token;
	char				*input;
	bool				reached_EOI;
	bool				emited_token;
}	t_lexer;

typedef struct s_lexer_backup
{
    size_t          ctx_len;
    size_t          token_value_len;
    size_t          i;
    t_token_type    token_type;
}   t_lexer_backup;

void	free_lexer(t_lexer *lexer);
void	init_lexer(t_lexer *lexer, char *input);

bool	lex_substitution(t_lexer *lexer);
bool	lex_quoting_char(t_lexer *lexer);
bool	dquote_quoting(t_lexer *lexer, size_t *nesting_depth);

// ================== Lexer Heredoc Header ==================

typedef t_buff		t_heredoc_delim;
typedef t_vector	t_heredoc_stack;

typedef struct s_lexer_heredoc
{
	t_heredoc_stack	*heredocs;
}	t_lexer_heredoc;

// ================== Scanner Header ==================

typedef enum e_scanner_mode
{
	SCAN_NONE,
	SCAN_MODE_FILE,
	SCAN_MODE_STDIN,
	SCAN_MODE_STRING
}	t_scanner_mode;

typedef char*	t_scanner_path;
typedef char*	t_scanner_command;

typedef union u_scanner_input
{
	t_scanner_path		path;
	t_scanner_command	command;
}	t_scanner_input;

typedef struct s_scanner
{
	t_scanner_mode	mode;
	t_scanner_input	input;
	t_lexer			lexer;
	t_reader		reader;
	t_lexer_heredoc	heredoc;
}	t_scanner;

// ================== Ctx Stack Code ==================

void	ctx_stack_init(t_scanner_ctx_stack *res)
{
	vector_init(res, sizeof(t_scanner_ctx), 0);
}

void	ctx_stack_free(t_scanner_ctx_stack *stack)
{
	vector_free(stack);
}

t_error	ctx_stack_push(t_scanner_ctx_stack *stack, t_scanner_ctx value)
{
	if (stack == NULL)
		return (ERR_NULL_ARGS);
	if (!vector_push(stack, &value))
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	ctx_stack_pop(t_scanner_ctx_stack *stack)
{
	if (stack == NULL)
		return (ERR_NULL_ARGS);
	if (!vector_pop(stack, NULL))
		return (ERR_EMPTY_STACK);
	return (ERR_NO);
}

t_error	ctx_stack_get(t_scanner_ctx *res, t_scanner_ctx_stack *stack)
{
	if (stack == NULL || res == NULL)
		return (ERR_NULL_ARGS);
	else if (stack->len == 0)
		return (ERR_EMPTY_STACK);
	*res = ((t_scanner_ctx *)stack->data)[stack->len - 1];
	return (ERR_NO);
}

// ================== Heredoc Stack Code ==================

void	heredoc_stack_init(t_heredoc_stack *res)
{
	vector_init(res, sizeof(t_heredoc_delim), 0);
}

void	heredoc_stack_free(t_heredoc_stack *stack)
{
	vector_free(stack);
}

t_error	heredoc_stack_push(t_heredoc_stack *stack, t_heredoc_delim value)
{
	if (stack == NULL)
		return (ERR_NULL_ARGS);
	if (!vector_push(stack, &value))
		return (ERR_LIBC);
	return (ERR_NO);
}

void	heredoc_stack_clean(t_heredoc_stack *stack)
{
	stack->len = 0;
}

t_error	heredoc_stack_get(t_heredoc_delim *res, t_heredoc_stack *stack, ulong i)
{
	if (stack == NULL || res == NULL)
		return (ERR_NULL_ARGS);
	else if (stack->len == 0)
		return (ERR_EMPTY_STACK);
	else if (i >= stack->len)
		return (ERR_INDEX_OUT_OF_BOUND);
	*res = ((t_heredoc_delim *)stack->data)[i];
	return (ERR_NO);
}

// ================== Lexer Code ==================

// ::::::::::::::::::: INIT :::::::::::::::::::

void	init_lexer(t_lexer *lexer, char *input)
{
	size_t	input_len;

	input_len = str_len(input);
	if (lexer == NULL)
		return ;
	*lexer = (t_lexer){0};
	ctx_stack_init(lexer->ctx);
	if (input != NULL)
	{
		lexer->input = input;
		if (!buff_init(&lexer->token.value, input_len, NULL, 0))
			lexer->err = ERR_LIBC;
	}
}

void	free_lexer(t_lexer *lexer)
{
	if (lexer == NULL)
		return ;
	ctx_stack_free(lexer->ctx);
	buff_free(&lexer->token.value);
	*lexer = (t_lexer){0};
}

t_lexer_backup	lexer_backup(t_lexer *lexer)
{
	t_lexer_backup res;

    res.i = lexer->i;
	res.ctx_len = lexer->ctx->len;
    res.token_value_len = lexer->token.value.len;
    res.token_type = lexer->token.type;
	return (res);
}

void	lexer_restore(t_lexer *lexer, t_lexer_backup backup)
{
	while (lexer->ctx->len > backup.ctx_len)
        ctx_stack_pop(lexer->ctx);
    lexer->i = backup.i;
    lexer->token.type = backup.token_type;
    lexer->token.value.len = backup.token_value_len;
}

// ::::::::::::::::::: TOKEN :::::::::::::::::::
   
t_error	token_dup(t_token *res, t_token token)
{
	res->type = token.type;
	if (!buff_dup_n(&res->value, &token.value, token.value.len))
		return (ERR_LIBC);
	return (ERR_NO);
}

// ::::::::::::::::::: UTILS :::::::::::::::::::

void	advance(t_lexer *lexer, size_t offset)
{
	lexer->i += offset;
}

void	consume(t_lexer *lexer, t_token_type type, size_t iter)
{
	size_t	i;

	i = 0;
	while (i < iter)
	{
		if (!buff_append(&lexer->token.value, &lexer->input[lexer->i], 1))
		{
			lexer->err = ERR_LIBC;
			return ;
		}
		lexer->token.type = type;
		advance(lexer, 1);
		i++;
	}
}

void	delimit_token(t_token *res, t_lexer *lexer)
{
    size_t	input_len;
    t_buff	new_buffer;

    input_len = str_len(lexer->input);
    if (!buff_init(&new_buffer, input_len, NULL, 0))
    {
        lexer->err = ERR_LIBC;
        return ;
    }
    *res = (t_token){.type = lexer->token.type, .value = lexer->token.value};
    lexer->token.type = NONE;
    lexer->emited_token = true;
    lexer->token.value = new_buffer;
}

bool	is_blank(t_lexer *lexer)
{
	return (lexer->input[lexer->i] == ' ' || lexer->input[lexer->i] == '\t');
}

void	line_continuation(t_lexer *lexer)
{
	advance(lexer, 2);
}

// ::::::::::::::::::: OPERATOR :::::::::::::::::::

// ----------- UTILS -----------

bool	is_in_middle_of_operator(t_lexer *lexer)
{
	return (lexer->token.type != NONE && lexer->token.type != TOKEN);
}

// ----------- SEMICOLON -----------

bool	is_operator_char_semicolon(t_lexer *lexer)
{
	if (lexer->token.type == SCOLON)
		return (true);
	else if (!is_in_middle_of_operator(lexer))
		return (true);
	return (false);
}

void	add_semicolon_to_operator(t_lexer *lexer)
{
	if (lexer->token.type == SCOLON)
		return (consume(lexer, DSEMI, 1));
	else if (lexer->token.type == NONE)
		return (consume(lexer, SCOLON, 1));
}

// ----------- AMPERSAND -----------

bool	is_operator_char_ampersand(t_lexer *lexer)
{
	if (lexer->token.type == SCOLON)
		return (true);
	else if (lexer->token.type == AMPERSAND)
		return (true);
	else if (lexer->token.type == LESS)
		return (true);
	else if (lexer->token.type == GREAT)
		return (true);
	else if (!is_in_middle_of_operator(lexer))
		return (true);
	return (false);
}

void	add_ampersand_to_operator(t_lexer *lexer)
{
	if (lexer->token.type == SCOLON)
		return (consume(lexer, SEMI_AND, 1));
	else if (lexer->token.type == AMPERSAND)
		return (consume(lexer, AND_IF, 1));
	else if (lexer->token.type == LESS)
		return (consume(lexer, LESSAND, 1));
	else if (lexer->token.type == GREAT)
		return (consume(lexer, GREATAND, 1));
	else if (lexer->token.type == NONE)
		return (consume(lexer, AMPERSAND, 1));
}

// ----------- PIPE -----------

bool	is_operator_char_pipe(t_lexer *lexer)
{
	if (lexer->token.type == PIPE)
		return (true);
	else if (lexer->token.type == GREAT)
		return (true);
	else if (!is_in_middle_of_operator(lexer))
		return (true);
	return (false);
}

void	add_pipe_to_operator(t_lexer *lexer)
{
	if (lexer->token.type == PIPE)
		return (consume(lexer, OR_IF, 1));
	else if (lexer->token.type == GREAT)
		return (consume(lexer, CLOBBER, 1));
	else if (lexer->token.type == NONE)
		return (consume(lexer, PIPE, 1));
}

// ----------- LESS -----------

bool	is_operator_char_less(t_lexer *lexer)
{
	if (lexer->token.type == LESS)
		return (true);
	else if (!is_in_middle_of_operator(lexer))
		return (true);
	return (false);
}

void	add_less_to_operator(t_lexer *lexer)
{
	if (lexer->token.type == LESS)
		return (consume(lexer, DLESS, 1));
	else if (lexer->token.type == NONE)
		return (consume(lexer, LESS, 1));
}

// ----------- GREAT -----------

bool	is_operator_char_great(t_lexer *lexer)
{
	if (lexer->token.type == LESS)
		return (true);
	else if (lexer->token.type == GREAT)
		return (true);
	else if (!is_in_middle_of_operator(lexer))
		return (true);
	return (false);
}

void	add_great_to_operator(t_lexer *lexer)
{
	if (lexer->token.type == LESS)
		return (consume(lexer, LESSGREAT, 1));
	else if (lexer->token.type == GREAT)
		return (consume(lexer, DGREAT, 1));
	else if (lexer->token.type == NONE)
		return (consume(lexer, GREAT, 1));
}

// ----------- API -----------

bool	is_operator_char(t_lexer *lexer)
{
	const char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	if (input_ptr[0] == '\n' && !is_in_middle_of_operator(lexer))
		return (true);
	else if (input_ptr[0] == '(' && !is_in_middle_of_operator(lexer))
		return (true);
	else if (input_ptr[0] == ')' && !is_in_middle_of_operator(lexer))
		return (true);
	else if (input_ptr[0] == ';')
		return (is_operator_char_semicolon(lexer));
	else if (input_ptr[0] == '&')
		return (is_operator_char_ampersand(lexer));
	else if (input_ptr[0] == '|')
		return (is_operator_char_pipe(lexer));
	else if (input_ptr[0] == '<')
		return (is_operator_char_less(lexer));
	else if (input_ptr[0] == '>')
		return (is_operator_char_great(lexer));
	else if (input_ptr[0] == '-' && lexer->token.type == DLESS)
		return (true);
	return (false);
}

void	char_into_token_operator(t_lexer *lexer)
{
	const char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	if (input_ptr[0] == '\n')
		return (consume(lexer, NEWLINE_, 1));
	else if (input_ptr[0] == '(')
		return (consume(lexer, LPARENTHESIS, 1));
	else if (input_ptr[0] == ')')
		return (consume(lexer, RPARENTHESIS, 1));
	else if (input_ptr[0] == ';')
		return (add_semicolon_to_operator(lexer));
	else if (input_ptr[0] == '&')
		return (add_ampersand_to_operator(lexer));
	else if (input_ptr[0] == '|')
		return (add_pipe_to_operator(lexer));
	else if (input_ptr[0] == '<')
		return (add_less_to_operator(lexer));
	else if (input_ptr[0] == '>')
		return (add_great_to_operator(lexer));
	else if (input_ptr[0] == '-')
		return (consume(lexer, DLESSDASH, 1));
}

// ::::::::::::::::::: ESCAPE :::::::::::::::::::

// ----------- UTILS -----------

bool	handle_escape(t_lexer *lexer, t_escape_handler args)
{
	bool	is_in_context;

	is_in_context = false;
	if (args.is_in_context != NULL)
		is_in_context = args.is_in_context(lexer);
	if (args.is_line_continuation != NULL &&
		args.is_line_continuation(lexer, is_in_context))
	{
		line_continuation(lexer);
		if (lexer->input[lexer->i] == '\0')
			lexer->err = reader_continuation(&lexer->input);
		return (true);
	}
	else if (lexer->input[lexer->i] == '\0')
		return (lexer->err = reader_continuation(&lexer->input), true);
	else
	{
		consume(lexer, lexer->token.type, 1);
		if (lexer->err != ERR_NO)
			return (true);
		if (args.is_in_whitelist(lexer->input[lexer->i], is_in_context))
			return (consume(lexer, lexer->token.type, 1), true);
		return (true);
	}
}

bool	is_line_continuation_context(t_lexer *lexer, bool is_in_special_context)
{
	return (is_in_special_context && lexer->input[lexer->i + 1] == '\n');
}

bool	is_line_continuation_std(t_lexer *lexer, bool _)
{
	return (lexer->input[lexer->i + 1] == '\n');
}

// ----------- BACKTICK -----------

bool	is_backtick_squote_surrounded(t_lexer *lexer)
{
    t_scanner_ctx	*ctx;

    if (lexer->ctx->len < 2)
        return (false);
    ctx = (t_scanner_ctx *)lexer->ctx->data;
    return (ctx[lexer->ctx->len - 2] == DQUOTE ||
		ctx[lexer->ctx->len - 2] == ARITH);
}

bool	is_in_backtick_whitelist(char c, bool is_in_dquote)
{
    if (is_in_dquote)
        return (c == '$' || c == '`' || c == '"' || c == '\\');
    return (c == '\\' || c == '$' || c == '`');
}

bool	backtick_escape(t_lexer *lexer)
{
	t_escape_handler	args;

	args.is_in_whitelist = is_in_backtick_whitelist;
	args.is_in_context = is_backtick_squote_surrounded;
	args.is_line_continuation = is_line_continuation_context;
	return (handle_escape(lexer, args));
}

// ----------- PARAM -----------

bool	is_param_whitelist(char c, bool _)
{
	return ((void)c, true);
}

bool	param_escape(t_lexer *lexer)
{
	t_escape_handler	args;

	args.is_in_context = NULL;
	args.is_in_whitelist = is_param_whitelist;
	args.is_line_continuation = is_line_continuation_std;
	return (handle_escape(lexer, args));
}

// ----------- SQUOTE -----------

bool	is_squote_whitelist(char c, bool _)
{
	return ((void)c, false);
}

bool	squote_escape(t_lexer *lexer)
{
	t_escape_handler	args;

	args.is_in_context = NULL;
	args.is_line_continuation = NULL;
	args.is_in_whitelist = is_squote_whitelist;
	return (handle_escape(lexer, args));
}

// ----------- DOLLAR_SQUOTE -----------

bool	is_dollar_squote_whitelist(char c, bool _)
{
	return ((void)c, true);
}

bool	dollar_squote_escape(t_lexer *lexer)
{
	t_escape_handler	args;

	args.is_in_context = NULL;
	args.is_line_continuation = NULL;
	args.is_in_whitelist = is_dollar_squote_whitelist;
	return (handle_escape(lexer, args));
}

// ----------- DQUOTE -----------

bool	is_dquote_whitelist(char c, bool _)
{
	return (c == '$' || c == '`' || c == '\\' || c == '\"');
}

bool	dquote_escape(t_lexer *lexer)
{
	t_escape_handler	args;

	args.is_in_context = NULL;
	args.is_in_whitelist = is_dquote_whitelist;
	args.is_line_continuation = is_line_continuation_std;
	return (handle_escape(lexer, args));
}

// ----------- TOP_LEVEL -----------

bool	is_top_level_whitelist(char c, bool _)
{
	return ((void)c, true);
}

bool	top_level_escape(t_lexer *lexer)
{
	t_escape_handler	args;

	args.is_in_context = NULL;
	args.is_in_whitelist = is_top_level_whitelist;
	args.is_line_continuation = is_line_continuation_std;
	return (handle_escape(lexer, args));
}

// ::::::::::::::::::: UNESCAPE :::::::::::::::::::

// ----------- UTILS -----------

bool	handle_substitutions_unescaped(t_lexer *lexer, t_unescape_handler args)
{
	if (lexer->input[lexer->i] == '\0')
		return (lexer->err = reader_continuation(&lexer->input), true);
	else if (args.is_in_context != NULL && args.is_in_context(lexer))
		return (args.special_handler(lexer, args.special_args));
	else
		return (consume(lexer, lexer->token.type, 1), true);
}

// ----------- BACKTICK -----------

bool	backtick_unescaped(t_lexer *lexer, void *_)
{
	t_unescape_handler	args;

	args.special_args = NULL;
	args.is_in_context = NULL;
	args.special_handler = NULL;
	return (handle_substitutions_unescaped(lexer, args));
}

// ----------- PARAM -----------

bool	param_unescaped(t_lexer *lexer, void *_)
{
	t_unescape_handler	args;

	args.special_args = NULL;
	args.is_in_context = NULL;
	args.special_handler = NULL;
	return (handle_substitutions_unescaped(lexer, args));
}

// ----------- ARITH -----------

bool	is_arith_body(t_lexer *lexer)
{
	t_scanner_ctx	current_ctx;
	
	lexer->err = ctx_stack_get(&current_ctx, lexer->ctx);
	if (lexer->err != ERR_NO)
		return (true);
	return (current_ctx == ARITH);
}

bool	arithm_body_special_handler(t_lexer *lexer, void *nesting_depth)
{
	if (lexer->input[lexer->i] == '(')
	{
		consume(lexer, lexer->token.type, 1);
		if (lexer->err != ERR_NO)
			return (true);
		return ((*((size_t *)nesting_depth))++, true);
	}
	else if (lexer->input[lexer->i] == ')')
	{
		consume(lexer, lexer->token.type, 1);
		if (lexer->err != ERR_NO)
			return (true);
		if (*((size_t *)nesting_depth) == 0)
			return (false);
		else
			return ((*((size_t *)nesting_depth))--, true);
	}
	else
		return (consume(lexer, lexer->token.type, 1), true);
}

// ----------- SQUOTE -----------

bool	squote_unescaped(t_lexer *lexer, void *_)
{
	t_unescape_handler	args;

	args.special_args = NULL;
	args.is_in_context = NULL;
	args.special_handler = NULL;
	return (handle_substitutions_unescaped(lexer, args));
}

// ----------- DOLLAR_SQUOTE -----------

static bool	dollar_squote_unescaped(t_lexer *lexer, void *_)
{
	t_unescape_handler	args;

	args.special_args = NULL;
	args.is_in_context = NULL;
	args.special_handler = NULL;
	return (handle_substitutions_unescaped(lexer, args));
}

// ----------- DQUOTE -----------

static bool	dquote_unescaped(t_lexer *lexer, void *nesting_depth)
{
	t_unescape_handler	args;

	args.special_args = nesting_depth;
	args.is_in_context = is_arith_body;
	args.special_handler = arithm_body_special_handler;
	return (handle_substitutions_unescaped(lexer, args));
}

// ::::::::::::::::::: CONTEXT :::::::::::::::::::

// ----------- UTILS -----------

bool	ctx_start(t_lexer *lexer, t_scanner_ctx ctx, size_t offset)
{
	if (lexer->token.type == NONE)
		lexer->token.type = TOKEN;
	lexer->err = ctx_stack_push(lexer->ctx, ctx);
	if (lexer->err != ERR_NO)
		return (true);
	return (consume(lexer, lexer->token.type, offset), true);
}

bool	ctx_end(t_lexer *lexer)
{
	consume(lexer, lexer->token.type, 1);
	if (lexer->err != ERR_NO)
		return (true);
	return (lexer->err = ctx_stack_pop(lexer->ctx), true);
}

bool	ctx_runtime(t_lexer *lexer, t_ctx_handler args)
{
	bool	is_in_context;

	args.start(lexer);
	is_in_context = false;
	if (args.is_in_context != NULL)
		is_in_context = args.is_in_context(lexer);
	if (lexer->err != ERR_NO)
		return (true);
	while (true)
	{
		if (lexer->err != ERR_NO)
			return (true);
		else if (args.is_ending != NULL &&
			args.is_ending(lexer->input[lexer->i], is_in_context))
			return (ctx_end(lexer));
		else if (lexer->input[lexer->i] == '\\' && args.escape(lexer))
			continue ;
		else if (args.quoting != NULL && args.quoting(lexer))
			continue ;
		else if (args.substitution != NULL && args.substitution(lexer))
			continue ;
		else if (!args.unescaped(lexer, args.unescaped_args))
			return (true);
	}
}

// ----------- BACKTICK -----------

bool	backtick_start(t_lexer *lexer)
{
	return (ctx_start(lexer, BACKTICK, 1));
}

bool	is_backtick_ending(char c, bool _)
{
	return (c == '`');
}

bool	lex_backtick(t_lexer *lexer)
{
	t_ctx_handler	args;

	args.is_in_context = NULL;
	args.unescaped_args = NULL;
	args.start = backtick_start;
	args.escape = backtick_escape;
	args.quoting = lex_quoting_char;
	args.unescaped = backtick_unescaped;
	args.is_ending = is_backtick_ending;
	args.substitution = lex_substitution;
	return (ctx_runtime(lexer, args));
}

// ----------- PARAM -----------

bool	param_start(t_lexer *lexer)
{
	return (ctx_start(lexer, PARAM, 2));
}

bool	is_param_ending(char c, bool _)
{
	return (c == '}');
}

bool	lex_param(t_lexer *lexer)
{
	t_ctx_handler	args;

	args.start = param_start;
	args.is_in_context = NULL;
	args.unescaped_args = NULL;
	args.escape = param_escape;
	args.quoting = lex_quoting_char;
	args.is_ending = is_param_ending;
	args.unescaped = param_unescaped;
	args.substitution = lex_substitution;
	return (ctx_runtime(lexer, args));
}

// ----------- ARITH -----------

bool	lex_arith(t_lexer *lexer)
{
	t_lexer_backup	backup;
	size_t			nesting_depth;

	nesting_depth = 0;
	backup = lexer_backup(lexer);
	ctx_start(lexer, ARITH, 3);
	if (lexer->err != ERR_NO)
		return (true);
	dquote_quoting(lexer, &nesting_depth);
	if (lexer->err != ERR_NO)
		return (true);
	if (lexer->input[lexer->i] != ')')
		return (lexer_restore(lexer, backup), false);
	consume(lexer, lexer->token.type, 1);
	if (lexer->err != ERR_NO)
		return (true);
	return (lexer->err = ctx_stack_pop(lexer->ctx), true);
}

// ----------- CMD_SUB -----------

bool	lex_cmd_sub(t_lexer *lexer)
{
	if (lexer->token.type == NONE)
		lexer->token.type = TOKEN;
	(void)lexer;
	return (true);
}

// ----------- SQUOTE -----------

bool	squote_start(t_lexer *lexer)
{
	return (ctx_start(lexer, SQUOTE, 1));
}

bool	is_squote_ending(char c, bool _)
{
	return (c == '\'');
}

bool	squote_quoting(t_lexer *lexer)
{
	t_ctx_handler	args;

	args.quoting = NULL;
	args.substitution = NULL;
	args.is_in_context = NULL;
	args.start = squote_start;
	args.unescaped_args = NULL;
	args.escape = squote_escape;
	args.is_ending = is_squote_ending;
	args.unescaped = squote_unescaped;
	return (ctx_runtime(lexer, args));
}

// ----------- DOLLAR_SQUOTE -----------

bool	dollar_squote_start(t_lexer *lexer)
{
	return (ctx_start(lexer, DOLLAR_SQUOTE, 2));
}

bool	is_dollar_squote_ending(char c, bool _)
{
	return (c == '\'');
}

bool	dollar_squote_quoting(t_lexer *lexer)
{
	t_ctx_handler	args;

	args.quoting = NULL;
	args.is_in_context = NULL;
	args.substitution = NULL;
	args.unescaped_args = NULL;
	args.start = dollar_squote_start;
	args.escape = dollar_squote_escape;
	args.is_ending = is_dollar_squote_ending;
	args.unescaped = dollar_squote_unescaped;
	return (ctx_runtime(lexer, args));
}

// ----------- DQUOTE -----------

bool	dquote_start(t_lexer *lexer)
{
	if (is_arith_body(lexer))
		return (true);
	return (ctx_start(lexer, DQUOTE, 1));
}

bool	is_dquote_ending(char c, bool is_in_arith)
{
	if (is_in_arith)
		return (false);
	return (c == '\"');
}

bool	dquote_quoting(t_lexer *lexer, size_t *nesting_depth)
{
	t_ctx_handler	args;

	args.quoting = NULL;
	args.start = dquote_start;
	args.escape = dquote_escape;
	args.is_ending = is_dquote_ending;
	args.unescaped = dquote_unescaped;
	args.is_in_context = is_arith_body;
	args.unescaped_args = nesting_depth;
	args.substitution = lex_substitution;
	return (ctx_runtime(lexer, args));
}

// ::::::::::::::::::: API :::::::::::::::::::

bool	lex_input_end(t_token *res, t_lexer *lexer) // Rule 1
{
	if (lexer->input[lexer->i] == '\0')
	{
		if (lexer->token.type != NONE)
			return (delimit_token(res, lexer), true);
		else
			return (lexer->reached_EOI = true, true);
	}
	return (false);
}

bool	lex_in_middle_of_operator(t_token *res, t_lexer *lexer) // Rule 2-3
{
	if (is_in_middle_of_operator(lexer))
	{
		if (is_operator_char(lexer)) // Rule 2
			return (char_into_token_operator(lexer), true);
		else
			return (delimit_token(res, lexer), true); // Rule 3
	}
	return (false);
}

bool	lex_quoting_char(t_lexer *lexer) // Rule 4
{
	const char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	if (input_ptr[0] == '\'')
		return (squote_quoting(lexer));
	else if (input_ptr[0] == '$' && input_ptr[1] == '\'')
		return (dollar_squote_quoting(lexer));
	else if (input_ptr[0] == '\"')
		return (dquote_quoting(lexer, NULL));
	return (false);
}

bool	lex_substitution(t_lexer *lexer)  // Rule 5
{
	if (lexer->input[lexer->i] == '$')
	{
		if (lexer->input[lexer->i + 1] == '{')
			return (lex_param(lexer));
		else if (lexer->input[lexer->i + 1] == '(')
		{
			if (lexer->input[lexer->i + 2] == '(')
			{
				if (lex_arith(lexer) || lexer->err != ERR_NO)
					return (true);
			}
			return (lex_cmd_sub(lexer));
		}
	}
	else if (lexer->input[lexer->i] == '`')
		return (lex_backtick(lexer));
	return (false);
}

bool	lex_new_operator(t_token *res, t_lexer *lexer) // Rule 6
{
	if (!is_in_middle_of_operator(lexer) && is_operator_char(lexer))
	{
		if (lexer->token.type != NONE)
			return (delimit_token(res, lexer), true);
		else
			return (char_into_token_operator(lexer), true);
	}
	return (false);
}

bool	lex_blank(t_token *res, t_lexer *lexer) // Rule 7
{
	if (is_blank(lexer))
	{
		if (lexer->token.type != NONE)
			return (delimit_token(res, lexer), true);
		while (is_blank(lexer) && lexer->input[lexer->i] != '\0')
			lexer->i++;
		return (true);
	}
	return (false);
}

bool	lex_in_middle_of_word(t_lexer *lexer)  // Rule 8
{
	if (lexer->token.type == TOKEN)
	{
		if (lexer->input[lexer->i] == '\\')
			return (top_level_escape(lexer));
		else
			return (consume(lexer, TOKEN, 1), true);
	}
	return (false);
}

bool	lex_comment(t_lexer *lexer)  // Rule 9
{
	if (lexer->input[lexer->i] == '#')
	{
		while (lexer->input[lexer->i] != '\0' && lexer->input[lexer->i] != '\n')
			lexer->i++;
		return (true);
	}
	return (false);
}

void	lex_new_word(t_lexer *lexer) // Rule 10
{
	if (lexer->input[lexer->i] == '\\')
		top_level_escape(lexer);
	else
		consume(lexer, TOKEN, 1);
}

void	lexer_token_recognition(t_token *res, t_lexer *lexer)
{
	while (!lexer->emited_token && !lexer->reached_EOI)
	{
		if (lexer->err != ERR_NO)
			return ;
		if (lex_input_end(res, lexer))
			continue ;
		else if (lex_in_middle_of_operator(res, lexer))
			continue ;
		else if (lex_quoting_char(lexer))
			continue ;
		else if (lex_substitution(lexer))
			continue ;
		else if (lex_new_operator(res, lexer))
			continue ;
		else if (lex_blank(res, lexer))
			continue ;
		else if (lex_in_middle_of_word(lexer))
			continue ;
		else if (lex_comment(lexer))
			continue ;
		else
			lex_new_word(lexer);
	}
}

t_error	lexer_tokenize_input(t_token *res, t_lexer *lexer)
{
	if (lexer == NULL || res == NULL || lexer->input == NULL)
		return (ERR_NULL_ARGS);
	lexer->reached_EOI = false;
	lexer->emited_token = false;
	lexer_token_recognition(res, lexer);
	return (lexer->err);
}

// ================== Lexer Heredoc Code ==================

// ::::::::::::::::::: INIT :::::::::::::::::::

void	init_lexer_heredoc(t_lexer_heredoc *lexer_heredoc)
{
	*lexer_heredoc = (t_lexer_heredoc){0};
	heredoc_stack_init(lexer_heredoc->heredocs);
}

void	free_lexer_heredoc(t_lexer_heredoc *lexer_heredoc)
{
	if (lexer_heredoc == NULL)
		return ;
	heredoc_stack_free(lexer_heredoc->heredocs);
	*lexer_heredoc = (t_lexer_heredoc){0};
}

// ::::::::::::::::::: API :::::::::::::::::::

t_error	lexer_heredoc_process(t_heredoc_delim *delim)
{
	
}

t_error	lexer_heredoc(t_heredoc_stack *stack)
{
	size_t 			i;
	t_error			err;
	t_heredoc_delim	*delim;

	i = 0;
	while (i < stack->len)
	{
		err = heredoc_stack_get(delim, stack, i);
		if (err != ERR_NO)
			return (err);
		lexer_heredoc_process(delim);
		i++;  
	}
	return (heredoc_stack_clean(stack), ERR_NO);
}

// ================== Reader Code ==================

// ::::::::::::::::::: INIT :::::::::::::::::::

void	init_reader(t_reader *reader)
{
	reader->ctx = NULL;
}

void	load_reader(t_reader *reader, t_scanner_ctx_stack *ctx)
{
	reader->ctx = ctx;
}

void	free_reader(t_reader *reader)
{
	reader->ctx = NULL;
}
	
// ::::::::::::::::::: TTY :::::::::::::::::::

t_error	readline_(char **res, const char *prompt)
{
	char	*input;

	*res = readline(prompt);
	if (*res == NULL)
		return (shell_exit_on_veof(), readline_(res, prompt));
	if (str_len(*res) == 0)
		return (free(*res), readline_(res, prompt));
	input = str_join(*res, "\n");
	if (input == NULL)
		return (ERR_LIBC);
	return (free(*res), *res = input, ERR_NO);
}

t_error	reader_continuation(char **res)
{
	t_error	err;
	char	*new_input;
	char	*continuation;

	if (res == NULL)
		return (ERR_NULL_ARGS);
	err = readline_(&continuation, "> ");
	if (err != ERR_NO)
		return (err);
	new_input = str_join(*res, continuation);
	if (new_input == NULL)
		return (ERR_LIBC);
	free(*res);
	free(continuation);
	*res = new_input;
	return (ERR_NO);
}

t_error	reader_new_input(char **res)
{
	if (res == NULL)
		return (ERR_NULL_ARGS);
	return (readline_(res, "$ "));
}

// ::::::::::::::::::: FILE :::::::::::::::::::

t_error	reader_file_input(char **res, t_scanner_path path)
{
	int		fd;
	t_buff	buffer;

	if (path == NULL)
		return (ERR_NULL_ARGS);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ERR_OPEN_FILE);
	buff_init(&buffer, 0, NULL, 0);
	if (!buff_read_all(&buffer, fd))
		return (ERR_LIBC);
	*res = buff_get_string(&buffer);
	if (*res == NULL)
		return (ERR_LIBC);
	return (close(fd), buff_free(&buffer), ERR_NO);
}

// ================== Scanner Code ==================

// ::::::::::::::::::: UTILS :::::::::::::::::::

t_scanner	shell_get_scanner(void)
{
	
}

// ::::::::::::::::::: INIT :::::::::::::::::::

void	scanner_init(t_scanner *res)
{
	init_lexer(&res->lexer, NULL);
	init_reader(&res->reader);
	res->mode = SCAN_NONE;
	res->input.command = NULL;
}

void	scanner_free(t_scanner *res)
{
	free_lexer(&res->lexer);
	free_reader(&res->reader);
	free(res->input.command);
	res->mode = SCAN_NONE;
	*res = (t_scanner){0};
}

t_error	scanner_load(t_scanner *res, t_scanner_mode mode, t_scanner_input input)
{
	res->mode = mode;
	load_reader(&res->reader, res->lexer.ctx);
	if (mode == SCAN_MODE_STRING)
		return (res->input.command = input.command, ERR_NO);
	else if (mode == SCAN_MODE_FILE)
		return (res->input.path = input.path, ERR_NO);
	return (ERR_NO);
}

// ::::::::::::::::::: API :::::::::::::::::::

t_error	scanner_next_token(t_token *res)
{
	t_error		err;
	t_scanner	scanner;

	if (res == NULL)
		return (ERR_NULL_ARGS);
	scanner = shell_get_scanner();
	if (scanner.mode == SCAN_MODE_FILE)
		return (reader_file_input(&scanner.lexer.input, scanner.input.path));
	else if (scanner.mode == SCAN_MODE_STRING)
		return (scanner.lexer.input = scanner.input.command, ERR_NO);
	else
	{
		if (scanner.lexer.input == NULL)
			return (reader_new_input(&scanner.lexer.input));
	}
	err = lexer_tokenize_input(res, &scanner.lexer);
	if (err != ERR_NO)
		return (err);
	if (res->type == NEWLINE_)
	{
		lexer_heredoc(scanner.);
	}
}

t_error	scanner_report_io_here(t_buff delim, char **path)
{
	t_scanner	scanner;

	scanner = shell_get_scanner();
	return (heredoc_stack_push(scanner.heredoc.heredocs, delim));
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>*<<<<<<<<<<<<<<<<<<<<<<<<<<<<

