/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:48:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 22:36:34 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_.h"

/*
** Expander error surface — everything that can bubble up to the API
** endpoints (expand_str, expand_str_merged, expand_token,
** expand_token_merged, expand_token_word, word_match_pattern,
** expansion_merge — the complete list of module functions returning a
** t_error to external callers; each routes its result through this
** function).
** Requalification happens IN PLACE at the production sites (printed
** where the context is richest), so this boundary mapping is the
** identity — final, not a placeholder:
**
**	- ERR_NO				success.
**	- ERR_POSIX_EXPANSION	printed and requalified at production:
**							* bad substitution — empty ${}, missing '}'
**							  (braced_expect_close), invalid operator
**							  including ':#'/':%' (parse_braced_op),
**							  invalid parameter name; printed with the
**							  whole construct text by expand_braced, the
**							  diagnostic funnel, along with ${@=w} and a
**							  non-assignable name in ${name=w}.
**							* ${x?word} — braced_error, printed with the
**							  name and the expanded message.
**							* set -u on an unset parameter —
**							  param_nounset_error ('@'/'*' exempt).
**	- ERR_POSIX_ASSIGNMENT	printed and requalified by the env module:
**							${RO:=v} on a readonly variable
**							(env_set_variable).
**	- ERR_POSIX_SYNTAX		printed and requalified by the scanner: the
**							raw-string re-lex of expand_str /
**							expand_str_merged (prepare_str_for_expansion)
**							hit an unterminated construct in string mode.
**	- ERR_INTERNAL			printed and requalified at production:
**							compute_arith_expression, the $((...))
**							evaluation stub (substitutions/arith).
**	- ERR_INTERNAL			also printed and requalified by its other
**							producers: env instance lookups
**							(env_get_struct, option_is_active) and the
**							AST index check of command substitution
**							(ast_vector_get).
**	- ERR_LIBC				raw, unprinted: allocation failures across
**							the pipeline (loader dup, word/field/
**							expansion growth, string building in every
**							substitution, pattern rendering, IFS
**							resolution, field join) and command-
**							substitution process failures (pipe, fork,
**							pipe read, wait — the cmd_sub module);
**							printed once at the runner frontier.
**
** Internal inconsistencies (empty pops, out-of-range item lookups,
** broken construct spans) are caught by ASSERTIONS in the word,
** expansion, fields and path containers: they are bugs, not errors, and
** never produce an error value.
**
** Absorbed before this boundary (never bubble): ERR_QUOTED_TILDE (tilde
** control flow — a quoted tilde stays literal), ERR_VAR_NOT_FOUND
** (mapped to an empty value at every lookup site, or converted by the
** set -u lane). ERR_CTX_END_NOT_FOUND is absorbed by the lexer's
** cmd_sub rescan before expansion. ERR_VEOF exists in the scanner
** surface but only from interactive readers: the throwaway scanners of
** expand_str / heredoc_lex_body run in SCAN_MODE_STRING, where end of
** input mid-construct becomes ERR_POSIX_SYNTAX. The raw
** ERR_SHELL_NOT_FOUND branches left in env/3_get.c are dead (the shell
** instance is static) and pending the same print-and-requalify
** conversion on the env side.
**
** CONSTRAINT (POSIX 2.8.1): ERR_POSIX_EXPANSION / ERR_POSIX_ASSIGNMENT
** exit a non-interactive shell; the runner must recover interactively
** (see the @warning in includes/expander.h — runner scope, open).
*/
t_error	requalify_expander_error(t_error err)
{
	return (err);
}
