/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lexer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:24:03 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/03 14:53:13 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LEXER_H
# define _LEXER_H

# include "error.h"
# include "libft.h"
# include "./heredoc/_heredoc.h"
# include "../ctx_stack/_ctx_stack.h"

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
}	t_token;

typedef struct s_lexer_backup
{
    size_t          i;
    size_t          ctx_len;
    t_token_type    token_type;
    size_t          token_value_len;
}   t_lexer_backup;

typedef struct s_lexer
{
	size_t				i;
	t_error				err;
	t_scanner_ctx_stack	ctx;
	t_token				token;
	char				*input;
	bool				is_tty;
	t_here_queue		queue;
	bool				reached_EOI;
	bool				emited_token;
}	t_lexer;

void			lexer_free(t_lexer *state);
void			lexer_init(t_lexer *state);
t_error			lexer_reset(t_lexer *state);
void			lexer_load(t_lexer *state, bool is_tty);

bool			lexer_is_operator_char(t_lexer *state);
void			lexer_char_into_token_operator(t_lexer *state);

bool			lexer_context(t_lexer *state, t_scanner_ctx ctx);

void			lexer_token_recognition(t_token *res, t_lexer *state);

bool			lexer_heredoc_queue_consume(t_lexer *state);
t_error			lexer_heredoc_create_tmp_file(t_file_path *res);

t_lexer_backup	lexer_backup(t_lexer *state);
void			lexer_advance(t_lexer *state, size_t offset);
void			lexer_delimit_token(t_token *res, t_lexer *state);
void			lexer_restore(t_lexer *state, t_lexer_backup backup);
t_error			lexer_consume(t_lexer *state, t_token_type type, size_t iter);

#endif
