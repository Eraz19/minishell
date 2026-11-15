/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:15:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:59:45 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner_priv.h"

/*
**
** VEOF only means "interactive input ended between tokens" (CTRL+D at
** PS1 / ignored-EOF budget): a continuation impossible in FILE/STRING
** mode is produced as POSIX_SYNTAX (read_and_propagate_ps2,
** reader_read_ps2), and any end-of-continuation mid-construct — CTRL+D
** at PS2 included — is converted into the named unterminated diagnostic
** (on_context_scan_eoi) or into NO_DELIM (heredoc, read_body_ps2).
** CTX_END_NOT_FOUND never reaches this point: absorbed by the $((
** cmd_sub rescan (expansion_context_rule.c).
**
** MODULE-EXTERNAL PRODUCERS whose errors can flow through the scanner —
** pass through untouched for now; each gets its contract row when its
** module is refactored:
**	- params		options_get / option_is_active / env_get_from_const
**					/ env_set_last_status (reader gates, prompts,
**					signal recording)
**	- shell			shell_get_* instance lookups (prompt history index,
**					heredoc_lex_body throwaway instance)
**	- history		sticky state via reader_read_ps1 / reader_read_ps2
**	- sig			sig_process / pending-trap lanes around readline
**	- expander		prompt expansion (absorbed to ERR_NO after printing),
**					heredoc delimiter expansion (POSIX_EXPANSION /
**					POSIX_ASSIGNMENT, printed there)
**	- posix helpers	posix_write (EOF newline echo); posix_open / read are
**					requalified inside the reader before exiting
**	- token/context	context_stack_item_init / context_stack_push / token ops
**	- builder		parser_can_next_token_be_a_cmd_name_or_word (alias
**					position check), LR machine + parser via the embedded
**					command-substitution parse
**	- cmd_sub		cmd_sub_find_end (embedded parse driver)
**	- env/alias		env_get_alias (post-merge: VAR_NOT_FOUND absorbed at
**					expand_alias, anything else passes)
*/
t_error	requalify_scanner_error(t_scanner *scanner)
{
	if (scanner->err.type == ERR_NO_DELIM)
		scanner->err.type = ERR_POSIX_SYNTAX;
	else if (scanner->err.type == ERR_NO
		|| scanner->err.type == ERR_VEOF
		|| scanner->err.type == ERR_LIBC)
		return (scanner->err);
	return (scanner->err = error_print(scanner->err, "scanner", NULL, NULL));
}
