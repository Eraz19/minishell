#ifndef PARSER_H
# define PARSER_H

/*------------- TODO: TMP D.EBUG -------------*/
#include <stdio.h>
typedef struct s_token
{
	// TODO
}	t_token;
/*--------------------------------------------*/

# include "libft.h"
# include <stdbool.h>
# include <stddef.h>

/* ************************************************************************* */
/*                             NAMING CONVENTION                             */
/* ************************************************************************* */
/*
*	t_rule_state				aka item
*	t_rule_state.pos			aka item.dot
*	t_lr_state					aka itemset aka state
*/

/* ************************************************************************* */
/*                                  SYMBOLS                                  */
/* ************************************************************************* */

typedef enum e_symbol
{
	//	TERMINALS (ACTION table entries)
	//		- Unclassified
	SYM_TOKEN,
	//		- Contextual
	SYM_WORD,
	SYM_NAME,
	SYM_ASSIGNMENT_WORD,
	//		- Control
	SYM_NEWLINE,		// \n
	SYM_SEMI,			// ;
	SYM_DSEMI,			// ;;
	SYM_SEMI_AND,		// ;&
	SYM_AMPERSAND,		// &
	SYM_AND_IF,			// &&
	SYM_OR_IF,			// ||
	SYM_PIPE,			// |
	SYM_LPARENTHESIS,	// (
	SYM_RPARENTHESIS,	// )
	//		- Redirection
	SYM_IO_NUMBER,		// [0-9]+
	SYM_IO_LOCATION,	// Not supported (optional POSIX symbol)
	SYM_LESS,			// <
	SYM_DLESS,			// <<
	SYM_DLESSDASH,		// <<-
	SYM_LESSAND,		// <&
	SYM_GREAT,			// >
	SYM_DGREAT,			// >>
	SYM_GREATAND,		// >&
	SYM_CLOBBER,		// >|
	SYM_LESSGREAT,		// <>
	//		- Reserved words
	SYM_Bang,			// !
	SYM_Lbrace,			// {
	SYM_Rbrace,			// }
	SYM_Case,			// case
	SYM_Esac,			// esac
	SYM_Do,				// do
	SYM_Done,			// done
	SYM_If,				// if
	SYM_Then,			// then
	SYM_Elif,			// elif
	SYM_Else,			// else
	SYM_Fi,				// fi
	SYM_For,			// for
	SYM_In,				// in
	SYM_Until,			// until
	SYM_While,			// while
	//		- End of input
	SYM_EOF,
	// ----------------------------------------------------
	// NON_TERMINALS (GOTO table entries)
	SYM_start,
	SYM_program,
	SYM_complete_commands,
	SYM_complete_command,
	SYM_list,
	SYM_and_or,
	SYM_pipeline,
	SYM_pipe_sequence,
	SYM_command,
	SYM_compound_command,
	SYM_subshell,
	SYM_compound_list,
	SYM_term,
	SYM_for_clause,
	SYM_name,
	SYM_in,
	SYM_wordlist,
	SYM_case_clause,
	SYM_case_list_ns,
	SYM_case_list,
	SYM_case_item_ns,
	SYM_case_item,
	SYM_pattern_list,
	SYM_if_clause,
	SYM_else_part,
	SYM_while_clause,
	SYM_until_clause,
	SYM_function_definition,
	SYM_function_body,
	SYM_fname,
	SYM_brace_group,
	SYM_do_group,
	SYM_simple_command,
	SYM_cmd_name,
	SYM_cmd_word,
	SYM_cmd_prefix,
	SYM_cmd_suffix,
	SYM_redirect_list,
	SYM_io_redirect,
	SYM_io_file,
	SYM_filename,
	SYM_io_here,
	SYM_here_end,
	SYM_newline_list,
	SYM_linebreak,
	SYM_separator_op,
	SYM_separator,
	SYM_sequential_sep,
	// ----------------------------------------------------
	SYM_COUNT,
	SYM_error
}	t_symbol;

# define SYM_TERMINAL_MAX		SYM_EOF
# define SYM_NON_TERMINAL_MIN	SYM_start
# define SYM_NON_TERMINAL_MAX	SYM_error

/* ************************************************************************* */
/*                                   CST                                     */
/* ************************************************************************* */

typedef struct s_cst_node
{
	// TODO
}	t_cst_node;

/* ************************************************************************* */
/*                                  STACK                                    */
/* ************************************************************************* */

typedef struct s_stack_item
{
	t_token		*token_first;	// borrowed
	t_token		*token_last;	// borrowed
	t_symbol	symbol;
	size_t		lr_state_id;
	t_cst_node	*cst_node;		// borrowed
}	t_stack_item;

typedef t_vector	t_stack;

/* ************************************************************************* */
/*                                  RULES                                    */
/* ************************************************************************* */

# define RULE_RHS_CAP	7

typedef bool	(*t_reduce_hook)(t_stack_item *rhs, size_t rhs_len, void *ctx);

typedef struct s_rule
{
	t_symbol		lhs;
	t_symbol		rhs[RULE_RHS_CAP];
	size_t			rhs_len;
	t_reduce_hook	hook;
}	t_rule;

typedef enum e_rule_id
{
	RULE_START_1,					// start				-> program
	RULE_PROGRAM_1,					// program				-> linebreak complete_commands linebreak
	RULE_PROGRAM_2,					// program				-> linebreak
	RULE_COMPLETE_COMMANDS_1,		// complete_commands	-> complete_commands newline_list complete_command
	RULE_COMPLETE_COMMANDS_2,		// complete_commands	-> complete_command
	RULE_COMPLETE_COMMAND_1,		// complete_command		-> list separator_op
	RULE_COMPLETE_COMMAND_2,		// complete_command		-> list
	RULE_LIST_1,					// list					-> list separator_op and_or
	RULE_LIST_2,					// list					-> and_or
	RULE_AND_OR_1,					// and_or				-> pipeline
	RULE_AND_OR_2,					// and_or				-> and_or AND_IF linebreak pipeline
	RULE_AND_OR_3,					// and_or				-> and_or OR_IF linebreak pipeline
	RULE_PIPELINE_1,				// pipeline				-> pipe_sequence
	RULE_PIPELINE_2,				// pipeline				-> Bang pipe_sequence
	RULE_PIPE_SEQUENCE_1,			// pipe_sequence		-> command
	RULE_PIPE_SEQUENCE_2,			// pipe_sequence		-> pipe_sequence '|' linebreak command
	RULE_COMMAND_1,					// command				-> simple_command
	RULE_COMMAND_2,					// command				-> compound_command
	RULE_COMMAND_3,					// command				-> compound_command redirect_list
	RULE_COMMAND_4,					// command				-> function_definition
	RULE_COMPOUND_COMMAND_1,		// compound_command		-> brace_group
	RULE_COMPOUND_COMMAND_2,		// compound_command		-> subshell
	RULE_COMPOUND_COMMAND_3,		// compound_command		-> for_clause
	RULE_COMPOUND_COMMAND_4,		// compound_command		-> case_clause
	RULE_COMPOUND_COMMAND_5,		// compound_command		-> if_clause
	RULE_COMPOUND_COMMAND_6,		// compound_command		-> while_clause
	RULE_COMPOUND_COMMAND_7,		// compound_command		-> until_clause
	RULE_SUBSHELL_1,				// subshell				-> '(' compound_list ')'
	RULE_COMPOUND_LIST_1,			// compound_list		-> linebreak term
	RULE_COMPOUND_LIST_2,			// compound_list		-> linebreak term separator
	RULE_TERM_1,					// term					-> term separator and_or
	RULE_TERM_2,					// term					-> and_or
	RULE_FOR_CLAUSE_1,				// for_clause			-> For name do_group
	RULE_FOR_CLAUSE_2,				// for_clause			-> For name sequential_sep do_group
	RULE_FOR_CLAUSE_3,				// for_clause			-> For name linebreak in sequential_sep do_group
	RULE_FOR_CLAUSE_4,				// for_clause			-> For name linebreak in wordlist sequential_sep do_group
	RULE_NAME_1,					// name					-> NAME (apply rule 5)
	RULE_IN_1,						// in					-> In (apply rule 6)
	RULE_WORDLIST_1,				// wordlist				-> wordlist WORD
	RULE_WORDLIST_2,				// wordlist				-> WORD
	RULE_CASE_CLAUSE_1,				// case_clause			-> Case WORD linebreak in linebreak case_list Esac
	RULE_CASE_CLAUSE_2,				// case_clause			-> Case WORD linebreak in linebreak case_list_ns Esac
	RULE_CASE_CLAUSE_3,				// case_clause			-> Case WORD linebreak in linebreak Esac
	RULE_CASE_LIST_NS_1,			// case_list_ns			-> case_list case_item_ns
	RULE_CASE_LIST_NS_2,			// case_list_ns			-> case_item_ns
	RULE_CASE_LIST_1,				// case_list			-> case_list case_item
	RULE_CASE_LIST_2,				// case_list			-> case_item
	RULE_CASE_ITEM_NS_1,			// case_item_ns			-> pattern_list ')' linebreak
	RULE_CASE_ITEM_NS_2,			// case_item_ns			-> pattern_list ')' compound_list
	RULE_CASE_ITEM_1,				// case_item			-> pattern_list ')' linebreak DSEMI linebreak
	RULE_CASE_ITEM_2,				// case_item			-> pattern_list ')' compound_list DSEMI linebreak
	RULE_CASE_ITEM_3,				// case_item			-> pattern_list ')' linebreak SEMI_AND linebreak
	RULE_CASE_ITEM_4,				// case_item			-> pattern_list ')' compound_list SEMI_AND linebreak
	RULE_PATTERN_LIST_1,			// pattern_list			-> WORD (apply rule 4)
	RULE_PATTERN_LIST_2,			// pattern_list			-> '(' WORD (do NOT apply rule 4)
	RULE_PATTERN_LIST_3,			// pattern_list			-> pattern_list '|' WORD (do NOT apply rule 4)
	RULE_IF_CLAUSE_1,				// if_clause			-> If compound_list Then compound_list else_part Fi
	RULE_IF_CLAUSE_2,				// if_clause			-> If compound_list Then compound_list Fi
	RULE_ELSE_PART_1,				// else_part			-> Elif compound_list Then compound_list
	RULE_ELSE_PART_2,				// else_part			-> Elif compound_list Then compound_list else_part
	RULE_ELSE_PART_3,				// else_part			-> Else compound_list
	RULE_WHILE_CLAUSE_1,			// while_clause			-> While compound_list do_group
	RULE_UNTIL_CLAUSE_1,			// until_clause			-> Until compound_list do_group
	RULE_FUNCTION_DEFINITION_1,		// function_definition	-> fname '(' ')' linebreak function_body
	RULE_FUNCTION_BODY_1,			// function_body		-> compound_command (apply rule 9)
	RULE_FUNCTION_BODY_2,			// function_body		-> compound_command redirect_list (apply rule 9)
	RULE_FNAME_1,					// fname				-> NAME (apply rule 8)
	RULE_BRACE_GROUP_1,				// brace_group			-> Lbrace compound_list Rbrace
	RULE_DO_GROUP_1,				// do_group				-> Do compound_list Done (apply rule 6)
	RULE_SIMPLE_COMMAND_1,			// simple_command		-> cmd_prefix cmd_word cmd_suffix
	RULE_SIMPLE_COMMAND_2,			// simple_command		-> cmd_prefix cmd_word
	RULE_SIMPLE_COMMAND_3,			// simple_command		-> cmd_prefix
	RULE_SIMPLE_COMMAND_4,			// simple_command		-> cmd_name cmd_suffix
	RULE_SIMPLE_COMMAND_5,			// simple_command		-> cmd_name
	RULE_CMD_NAME_1,				// cmd_name				-> WORD (apply rule 7a)
	RULE_CMD_WORD_1,				// cmd_word				-> WORD (apply rule 7b)
	RULE_CMD_PREFIX_1,				// cmd_prefix			-> io_redirect
	RULE_CMD_PREFIX_2,				// cmd_prefix			-> cmd_prefix io_redirect
	RULE_CMD_PREFIX_3,				// cmd_prefix			-> ASSIGNMENT_WORD
	RULE_CMD_PREFIX_4,				// cmd_prefix			-> cmd_prefix ASSIGNMENT_WORD
	RULE_CMD_SUFFIX_1,				// cmd_suffix			-> io_redirect
	RULE_CMD_SUFFIX_2,				// cmd_suffix			-> cmd_suffix io_redirect
	RULE_CMD_SUFFIX_3,				// cmd_suffix			-> WORD
	RULE_CMD_SUFFIX_4,				// cmd_suffix			-> cmd_suffix WORD
	RULE_REDIRECT_LIST_1,			// redirect_list		-> io_redirect
	RULE_REDIRECT_LIST_2,			// redirect_list		-> redirect_list io_redirect
	RULE_IO_REDIRECT_1,				// io_redirect			-> io_file
	RULE_IO_REDIRECT_2,				// io_redirect			-> IO_NUMBER io_file
	RULE_IO_REDIRECT_3,				// io_redirect			-> IO_LOCATION io_file (optionally supported)
	RULE_IO_REDIRECT_4,				// io_redirect			-> io_here
	RULE_IO_REDIRECT_5,				// io_redirect			-> IO_NUMBER io_here
	RULE_IO_REDIRECT_6,				// io_redirect			-> IO_LOCATION io_here (optionally supported)
	RULE_IO_FILE_1,					// io_file				-> '<' filename
	RULE_IO_FILE_2,					// io_file				-> LESSAND filename
	RULE_IO_FILE_3,					// io_file				-> '>' filename
	RULE_IO_FILE_4,					// io_file				-> GREATAND filename
	RULE_IO_FILE_5,					// io_file				-> DGREAT filename
	RULE_IO_FILE_6,					// io_file				-> LESSGREAT filename
	RULE_IO_FILE_7,					// io_file				-> CLOBBER filename
	RULE_FILENAME_1,				// filename				-> WORD (apply rule 2)
	RULE_IO_HERE_1,					// io_here				-> DLESS here_end
	RULE_IO_HERE_2,					// io_here				-> DLESSDASH here_end
	RULE_HERE_END_1,				// here_end				-> WORD (apply rule 3)
	RULE_NEWLINE_LIST_1,			// newline_list			-> NEWLINE
	RULE_NEWLINE_LIST_2,			// newline_list			-> newline_list NEWLINE
	RULE_LINEBREAK_1,				// linebreak			-> newline_list
	RULE_LINEBREAK_2,				// linebreak			-> <empty>
	RULE_SEPARATOR_OP_1,			// separator_op			-> '&'
	RULE_SEPARATOR_OP_2,			// separator_op			-> ';'
	RULE_SEPARATOR_1,				// separator			-> separator_op linebreak
	RULE_SEPARATOR_2,				// separator			-> newline_list
	RULE_SEQUENTIAL_SEP_1,			// sequential_sep		-> ';' linebreak
	RULE_SEQUENTIAL_SEP_2,			// sequential_sep		-> newline_list
	RULE_COUNT						// rule_count			-> <sentinel>
}	t_rule_id;

typedef struct s_rule_state
{
	size_t	rule_id;
	size_t	pos;
}	t_rule_state;

/* ************************************************************************* */
/*                                LR_MACHINE                                 */
/* ************************************************************************* */

typedef t_vector	t_lr_state;

typedef struct s_transition
{
	size_t		from_lr_state_id;
	t_symbol	symbol;
	size_t		to_lr_state_id;
}	t_transition;

typedef enum e_action_type
{
	ACTION_SHIFT,
	ACTION_REDUCE,
	ACTION_ACCEPT,
	ACTION_ERROR
}	t_action_type;

/*
action.payload can be:
- SHIFT: to_lr_state_id
- REDUCE: rule_id
- ACCEPT: none (ACTION_PAYLOAD_EMPTY)
- ERROR: none (ACTION_PAYLOAD_EMPTY)
*/
typedef struct s_action
{
	t_action_type	type;
	size_t			payload;
}	t_action;

typedef struct s_goto
{
	size_t		from_lr_state_id;
	t_symbol	symbol;
	size_t		to_lr_state_id;
}	t_goto;

typedef struct s_lr_machine
{
	t_rule		rules[RULE_COUNT];
	t_vector	lr_states;
	t_vector	transitions;
	t_action	**actions;
	size_t		**gotos;
}	t_lr_machine;

/* ************************************************************************* */
/*                                  PARSER                                   */
/* ************************************************************************* */

typedef struct s_parser
{
	t_stack	stack;
	// TODO: CST
}	t_parser;

/* ************************************************************************* */
/*                                 CONVERTER                                 */
/* ************************************************************************* */

typedef struct s_converter
{
	// TODO: AST
}	t_converter;

/* ************************************************************************* */
/*                                  BUILDER                                  */
/* ************************************************************************* */

typedef struct s_builder
{
	t_lr_machine	lr_machine;
	t_parser		parser;
	t_converter		converter;
}	t_builder;

#endif
