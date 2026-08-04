/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_rules.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 14:50:52 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 15:12:02 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAMMAR_RULES_H
# define GRAMMAR_RULES_H

# include "grammar_symbols.h"
# include <stddef.h>

# define RULE_RHS_CAP	7

typedef enum e_rule_id
{
	RULE_ACCEPT,				// start (⚠️ custom)
	RULE_START_1,				// program
	RULE_START_2,				// cmd_sub	(⚠️ custom)
	RULE_CMD_SUB,				// DOLPAREN coumpound_list ')' (⚠️ custom)
	RULE_PROGRAM_1,				// linebreak complete_commands linebreak
	RULE_PROGRAM_2,				// linebreak
	RULE_COMPLETE_COMMANDS_1,	// complete_cmds newline_list complete_command
	RULE_COMPLETE_COMMANDS_2,	// complete_command
	RULE_COMPLETE_COMMAND_1,	// list separator_op
	RULE_COMPLETE_COMMAND_2,	// list
	RULE_LIST_1,				// list separator_op and_or
	RULE_LIST_2,				// and_or
	RULE_AND_OR_1,				// pipeline
	RULE_AND_OR_2,				// and_or AND_IF linebreak pipeline
	RULE_AND_OR_3,				// and_or OR_IF linebreak pipeline
	RULE_PIPELINE_1,			// pipe_sequence
	RULE_PIPELINE_2,			// Bang pipe_sequence
	RULE_PIPE_SEQUENCE_1,		// command
	RULE_PIPE_SEQUENCE_2,		// pipe_sequence '|' linebreak command
	RULE_COMMAND_1,				// simple_command
	RULE_COMMAND_2,				// compound_command
	RULE_COMMAND_3,				// compound_command redirect_list
	RULE_COMMAND_4,				// function_definition
	RULE_COMPOUND_COMMAND_1,	// brace_group
	RULE_COMPOUND_COMMAND_2,	// subshell
	RULE_COMPOUND_COMMAND_3,	// for_clause
	RULE_COMPOUND_COMMAND_4,	// case_clause
	RULE_COMPOUND_COMMAND_5,	// if_clause
	RULE_COMPOUND_COMMAND_6,	// while_clause
	RULE_COMPOUND_COMMAND_7,	// until_clause
	RULE_SUBSHELL_1,			// '(' compound_list ')'
	RULE_COMPOUND_LIST_1,		// linebreak term
	RULE_COMPOUND_LIST_2,		// linebreak term separator
	RULE_TERM_1,				// term separator and_or
	RULE_TERM_2,				// and_or
	RULE_FOR_CLAUSE_1,			// For name do_group
	RULE_FOR_CLAUSE_2,			// For name sequential_sep do_group
	RULE_FOR_CLAUSE_3,			// For name linebreak in sequential_sep do_group
	RULE_FOR_CLAUSE_4,			// For name linebreak in wordlist seq_sep do_grp
	RULE_NAME_1,				// NAME (apply rule 5)
	RULE_IN_1,					// In (apply rule 6)
	RULE_WORDLIST_1,			// wordlist WORD
	RULE_WORDLIST_2,			// WORD
	RULE_CASE_CLAUSE_1,			// Case WORD linebk in linebk case_list Esac
	RULE_CASE_CLAUSE_2,			// Case WORD linebk in linebk case_list_ns Esac
	RULE_CASE_CLAUSE_3,			// Case WORD linebk in linebk Esac
	RULE_CASE_LIST_NS_1,		// case_list case_item_ns
	RULE_CASE_LIST_NS_2,		// case_item_ns
	RULE_CASE_LIST_1,			// case_list case_item
	RULE_CASE_LIST_2,			// case_item
	RULE_CASE_ITEM_NS_1,		// pattern_list ')' linebreak
	RULE_CASE_ITEM_NS_2,		// pattern_list ')' compound_list
	RULE_CASE_ITEM_1,			// pattern_list ')' linebreak DSEMI linebreak
	RULE_CASE_ITEM_2,			// pattern_list ')' compound_list DSEMI linebk
	RULE_CASE_ITEM_3,			// pattern_list ')' linebreak SEMI_AND linebk
	RULE_CASE_ITEM_4,			// pattern_list ')' compound_lst SEMI_AND linebk
	RULE_PATTERN_LIST_1,		// WORD (apply rule 4)
	RULE_PATTERN_LIST_2,		// '(' WORD (do NOT apply rule 4)
	RULE_PATTERN_LIST_3,		// pattern_list '|' WORD (do NOT apply rule 4)
	RULE_IF_CLAUSE_1,			// If cmpnd_list Then cmpnd_list else_part Fi
	RULE_IF_CLAUSE_2,			// If cmpnd_list Then cmpnd_list Fi
	RULE_ELSE_PART_1,			// Elif cmpnd_list Then cmpnd_list
	RULE_ELSE_PART_2,			// Elif cmpnd_list Then cmpnd_list else_part
	RULE_ELSE_PART_3,			// Else cmpnd_list
	RULE_WHILE_CLAUSE_1,		// While cmpnd_list do_group
	RULE_UNTIL_CLAUSE_1,		// Until cmpnd_list do_group
	RULE_FUNCTION_BODY_1,		// compound_command (apply rule 9)
	RULE_FUNCTION_BODY_2,		// compound_command redirect_list (apply rule 9)
	RULE_FUNCTION_DEFINITION_1,	// fname '(' ')' linebreak function_body
	RULE_FNAME_1,				// NAME (apply rule 8)
	RULE_BRACE_GROUP_1,			// Lbrace compound_list Rbrace
	RULE_DO_GROUP_1,			// Do compound_list Done (apply rule 6)
	RULE_SIMPLE_COMMAND_1,		// cmd_prefix cmd_word cmd_suffix
	RULE_SIMPLE_COMMAND_2,		// cmd_prefix cmd_word
	RULE_SIMPLE_COMMAND_3,		// cmd_prefix
	RULE_SIMPLE_COMMAND_4,		// cmd_name cmd_suffix
	RULE_SIMPLE_COMMAND_5,		// cmd_name
	RULE_CMD_NAME_1,			// WORD (apply rule 7a)
	RULE_CMD_WORD_1,			// WORD (apply rule 7b)
	RULE_CMD_PREFIX_1,			// io_redirect
	RULE_CMD_PREFIX_2,			// cmd_prefix io_redirect
	RULE_CMD_PREFIX_3,			// ASSIGNMENT_WORD
	RULE_CMD_PREFIX_4,			// cmd_prefix ASSIGNMENT_WORD
	RULE_CMD_SUFFIX_1,			// io_redirect
	RULE_CMD_SUFFIX_2,			// cmd_suffix io_redirect
	RULE_CMD_SUFFIX_3,			// WORD
	RULE_CMD_SUFFIX_4,			// cmd_suffix WORD
	RULE_REDIRECT_LIST_1,		// io_redirect
	RULE_REDIRECT_LIST_2,		// redirect_list io_redirect
	RULE_IO_REDIRECT_1,			// io_file
	RULE_IO_REDIRECT_2,			// IO_NUMBER io_file
	RULE_IO_REDIRECT_3,			// IO_LOCATION io_file (optionally supported)
	RULE_IO_REDIRECT_4,			// io_here
	RULE_IO_REDIRECT_5,			// IO_NUMBER io_here
	RULE_IO_REDIRECT_6,			// IO_LOCATION io_here (optionally supported)
	RULE_IO_FILE_1,				// '<' filename
	RULE_IO_FILE_2,				// LESSAND filename
	RULE_IO_FILE_3,				// '>' filename
	RULE_IO_FILE_4,				// GREATAND filename
	RULE_IO_FILE_5,				// DGREAT filename
	RULE_IO_FILE_6,				// LESSGREAT filename
	RULE_IO_FILE_7,				// CLOBBER filename
	RULE_FILENAME_1,			// WORD (apply rule 2)
	RULE_IO_HERE_1,				// DLESS here_end
	RULE_IO_HERE_2,				// DLESSDASH here_end
	RULE_HERE_END_1,			// WORD (apply rule 3)
	RULE_NEWLINE_LIST_1,		// NEWLINE
	RULE_NEWLINE_LIST_2,		// newline_list NEWLINE
	RULE_LINEBREAK_1,			// newline_list
	RULE_LINEBREAK_2,			// <empty>
	RULE_SEPARATOR_OP_1,		// '&'
	RULE_SEPARATOR_OP_2,		// ';'
	RULE_SEPARATOR_1,			// separator_op linebreak
	RULE_SEPARATOR_2,			// newline_list
	RULE_SEQUENTIAL_SEP_1,		// ';' linebreak
	RULE_SEQUENTIAL_SEP_2,		// newline_list
	RULE_COUNT,					// <sentinel>
	RULE_NONE,					// <sentinel>
}	t_rule_id;

typedef struct s_rule
{
	t_symbol		lhs;
	t_symbol		rhs[RULE_RHS_CAP];
	size_t			rhs_len;
}	t_rule;

#endif
