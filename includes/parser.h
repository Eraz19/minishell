#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>

/* ************************************************************************* */
/*                                  SYMBOLS                                  */
/* ************************************************************************* */

typedef enum e_symbol_id
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
	SYM_error,
	// ----------------------------------------------------
	SYM_COUNT
}	t_symbol_id;

# define SYM_TERMINAL_MAX		SYM_EOF
# define SYM_NON_TERMINAL_MIN	SYM_program
# define SYM_NON_TERMINAL_MAX	SYM_error

/* ************************************************************************* */
/*                                  RULES                                    */
/* ************************************************************************* */

# define RULE_RHS_CAP	7

typedef struct s_rule
{
	t_symbol_id	lhs;
	t_symbol_id	rhs[RULE_RHS_CAP];
	size_t		rhs_len;
}	t_rule;

typedef enum e_rule_id
{
	RULE_PROGRAM_FROM_COMPLETE_COMMANDS,											// program				-> linebreak complete_commands linebreak
	RULE_PROGRAM_FROM_LINEBREAK,													// program				-> linebreak
	RULE_COMPLETE_COMMANDS_FROM_COMPLETE_COMMANDS,									// complete_commands	-> complete_commands newline_list complete_command
	RULE_COMPLETE_COMMANDS_FROM_COMPLETE_COMMAND,									// complete_commands	-> complete_command
	RULE_COMPLETE_COMMAND_FROM_LIST_SEP_OP,											// complete_command		-> list separator_op
	RULE_COMPLETE_COMMAND_FROM_LIST,												// complete_command		-> list
	RULE_LIST_FROM_LIST_SEPARATOR_OP_AND_OR,										// list					-> list separator_op and_or
	RULE_LIST_FROM_AND_OR,															// list					-> and_or
	RULE_AND_OR_FROM_PIPELINE,														// and_or				-> pipeline
	RULE_AND_OR_FROM_AND_OR_AND_IF_PIPELINE,										// and_or				-> and_or AND_IF linebreak pipeline
	RULE_AND_OR_FROM_AND_OR_OR_IF_PIPELINE,											// and_or				-> and_or OR_IF linebreak pipeline
	RULE_PIPELINE_FROM_PIPE_SEQUENCE,												// pipeline				-> pipe_sequence
	RULE_PIPELINE_FROM_BANG_PIPE_SEQUENCE,											// pipeline				-> Bang pipe_sequence
	RULE_PIPE_SEQUENCE_FROM_COMMAND,												// pipe_sequence		-> command
	RULE_PIPE_SEQUENCE_FROM_PIPE_SEQUENCE_PIPE_COMMAND,								// pipe_sequence		-> pipe_sequence '|' linebreak command
	RULE_COMMAND_FROM_SIMPLE_COMMAND,												// command				-> simple_command
	RULE_COMMAND_FROM_COMPOUND_COMMAND,												// command				-> compound_command
	RULE_COMMAND_FROM_COMPOUND_COMMAND_REDIRECT_LIST,								// command				-> compound_command redirect_list
	RULE_COMMAND_FROM_FUNCTION_DEFINITION,											// command				-> function_definition
	RULE_COMPOUND_COMMAND_FROM_BRACE_GROUP,											// compound_command		-> brace_group
	RULE_COMPOUND_COMMAND_FROM_SUBSHELL,											// compound_command		-> subshell
	RULE_COMPOUND_COMMAND_FROM_FOR_CLAUSE,											// compound_command		-> for_clause
	RULE_COMPOUND_COMMAND_FROM_CASE_CLAUSE,											// compound_command		-> case_clause
	RULE_COMPOUND_COMMAND_FROM_IF_CLAUSE,											// compound_command		-> if_clause
	RULE_COMPOUND_COMMAND_FROM_WHILE_CLAUSE,										// compound_command		-> while_clause
	RULE_COMPOUND_COMMAND_FROM_UNTIL_CLAUSE,										// compound_command		-> until_clause
	RULE_SUBSHELL_FROM_COMPOUND_LIST,												// subshell				-> '(' compound_list ')'
	RULE_COMPOUND_LIST_FROM_LINEBREAK_TERM,											// compound_list		-> linebreak term
	RULE_COMPOUND_LIST_FROM_LINEBREAK_TERM_SEPARATOR,								// compound_list		-> linebreak term separator
	RULE_TERM_FROM_TERM_SEPARATOR_AND_OR,											// term					-> term separator and_or
	RULE_TERM_FROM_AND_OR,															// term					-> and_or
	RULE_FOR_CLAUSE_FROM_FOR_NAME_DO_GROUP,											// for_clause			-> For name do_group
	RULE_FOR_CLAUSE_FROM_FOR_NAME_SEQUENTIAL_SEP_DO_GROUP,							// for_clause			-> For name sequential_sep do_group
	RULE_FOR_CLAUSE_FROM_FOR_NAME_LINEBREAK_IN_SEQUENTIAL_SEP_DO_GROUP,				// for_clause			-> For name linebreak in sequential_sep do_group
	RULE_FOR_CLAUSE_FROM_FOR_NAME_LINEBREAK_IN_WORDLIST_SEQUENTIAL_SEP_DO_GROUP,	// for_clause			-> For name linebreak in wordlist sequential_sep do_group
	RULE_NAME_FROM_NAME,															// name					-> NAME (apply rule 5)
	RULE_IN_FROM_IN,																// in					-> In (apply rule 6)
	RULE_WORDLIST_FROM_WORDLIST_WORD,												// wordlist				-> wordlist WORD
	RULE_WORDLIST_FROM_WORD,														// wordlist				-> WORD
	RULE_CASE_CLAUSE_FROM_CASE_WORD_LINEBREAK_IN_LINEBREAK_CASE_LIST_ESAC,			// case_clause			-> Case WORD linebreak in linebreak case_list Esac
	RULE_CASE_CLAUSE_FROM_CASE_WORD_LINEBREAK_IN_LINEBREAK_CASE_LIST_NS_ESAC,		// case_clause			-> Case WORD linebreak in linebreak case_list_ns Esac
	RULE_CASE_CLAUSE_FROM_CASE_WORD_LINEBREAK_IN_LINEBREAK_ESAC,					// case_clause			-> Case WORD linebreak in linebreak Esac
	RULE_CASE_LIST_NS_FROM_CASE_LIST_CASE_ITEM_NS,									// case_list_ns			-> case_list case_item_ns
	RULE_CASE_LIST_NS_FROM_CASE_ITEM_NS,											// case_list_ns			-> case_item_ns
	RULE_CASE_LIST_FROM_CASE_LIST_CASE_ITEM,										// case_list			-> case_list case_item
	RULE_CASE_LIST_FROM_CASE_ITEM,													// case_list			-> case_item
	RULE_CASE_ITEM_NS_FROM_PATTERN_LIST_RPAREN_LINEBREAK,							// case_item_ns			-> pattern_list ')' linebreak
	RULE_CASE_ITEM_NS_FROM_PATTERN_LIST_RPAREN_COMPOUND_LIST,						// case_item_ns			-> pattern_list ')' compound_list
	RULE_CASE_ITEM_FROM_PATTERN_LIST_RPAREN_LINEBREAK_DSEMI_LINEBREAK,				// case_item			-> pattern_list ')' linebreak DSEMI linebreak
	RULE_CASE_ITEM_FROM_PATTERN_LIST_RPAREN_COMPOUND_LIST_DSEMI_LINEBREAK,			// case_item			-> pattern_list ')' compound_list DSEMI linebreak
	RULE_CASE_ITEM_FROM_PATTERN_LIST_RPAREN_LINEBREAK_SEMI_AND_LINEBREAK,			// case_item			-> pattern_list ')' linebreak SEMI_AND linebreak
	RULE_CASE_ITEM_FROM_PATTERN_LIST_RPAREN_COMPOUND_LIST_SEMI_AND_LINEBREAK,		// case_item			-> pattern_list ')' compound_list SEMI_AND linebreak
	RULE_PATTERN_LIST_FROM_WORD,													// pattern_list			-> WORD (apply rule 4)
	RULE_PATTERN_LIST_FROM_LPAREN_WORD,												// pattern_list			-> '(' WORD (do NOT apply rule 4)
	RULE_PATTERN_LIST_FROM_PATTERN_LIST_PIPE_WORD,									// pattern_list			-> pattern_list '|' WORD (do NOT apply rule 4)
	RULE_IF_CLAUSE_FROM_IF_COMPOUND_LIST_THEN_COMPOUND_LIST_ELSE_PART_FI,			// if_clause			-> If compound_list Then compound_list else_part Fi
	RULE_IF_CLAUSE_FROM_IF_COMPOUND_LIST_THEN_COMPOUND_LIST_FI,						// if_clause			-> If compound_list Then compound_list Fi
	RULE_ELSE_PART_FROM_ELIF_COMPOUND_LIST_THEN_COMPOUND_LIST,						// else_part			-> Elif compound_list Then compound_list
	RULE_ELSE_PART_FROM_ELIF_COMPOUND_LIST_THEN_COMPOUND_LIST_ELSE_PART,			// else_part			-> Elif compound_list Then compound_list else_part
	RULE_ELSE_PART_FROM_ELSE_COMPOUND_LIST,											// else_part			-> Else compound_list
	RULE_WHILE_CLAUSE_FROM_WHILE_COMPOUND_LIST_DO_GROUP,							// while_clause			-> While compound_list do_group
	RULE_UNTIL_CLAUSE_FROM_UNTIL_COMPOUND_LIST_DO_GROUP,							// until_clause			-> Until compound_list do_group
	RULE_FUNCTION_DEFINITION_FROM_FNAME_PARENS_LINEBREAK_FUNCTION_BODY,				// function_definition	-> fname '(' ')' linebreak function_body
	RULE_FUNCTION_BODY_FROM_COMPOUND_COMMAND,										// function_body		-> compound_command (apply rule 9)
	RULE_FUNCTION_BODY_FROM_COMPOUND_COMMAND_REDIRECT_LIST,							// function_body		-> compound_command redirect_list (apply rule 9)
	RULE_FNAME_FROM_NAME,															// fname				-> NAME (apply rule 8)
	RULE_BRACE_GROUP_FROM_LBRACE_COMPOUND_LIST_RBRACE,								// brace_group			-> Lbrace compound_list Rbrace
	RULE_DO_GROUP_FROM_DO_COMPOUND_LIST_DONE,										// do_group				-> Do compound_list Done (apply rule 6)
	RULE_SIMPLE_COMMAND_FROM_CMD_PREFIX_CMD_WORD_CMD_SUFFIX,						// simple_command		-> cmd_prefix cmd_word cmd_suffix
	RULE_SIMPLE_COMMAND_FROM_CMD_PREFIX_CMD_WORD,									// simple_command		-> cmd_prefix cmd_word
	RULE_SIMPLE_COMMAND_FROM_CMD_PREFIX,											// simple_command		-> cmd_prefix
	RULE_SIMPLE_COMMAND_FROM_CMD_NAME_CMD_SUFFIX,									// simple_command		-> cmd_name cmd_suffix
	RULE_SIMPLE_COMMAND_FROM_CMD_NAME,												// simple_command		-> cmd_name
	RULE_CMD_NAME_FROM_WORD,														// cmd_name				-> WORD (apply rule 7a)
	RULE_CMD_WORD_FROM_WORD,														// cmd_word				-> WORD (apply rule 7b)
	RULE_CMD_PREFIX_FROM_IO_REDIRECT,												// cmd_prefix			-> io_redirect
	RULE_CMD_PREFIX_FROM_CMD_PREFIX_IO_REDIRECT,									// cmd_prefix			-> cmd_prefix io_redirect
	RULE_CMD_PREFIX_FROM_ASSIGNMENT_WORD,											// cmd_prefix			-> ASSIGNMENT_WORD
	RULE_CMD_PREFIX_FROM_CMD_PREFIX_ASSIGNMENT_WORD,								// cmd_prefix			-> cmd_prefix ASSIGNMENT_WORD
	RULE_CMD_SUFFIX_FROM_IO_REDIRECT,												// cmd_suffix			-> io_redirect
	RULE_CMD_SUFFIX_FROM_CMD_SUFFIX_IO_REDIRECT,									// cmd_suffix			-> cmd_suffix io_redirect
	RULE_CMD_SUFFIX_FROM_WORD,														// cmd_suffix			-> WORD
	RULE_CMD_SUFFIX_FROM_CMD_SUFFIX_WORD,											// cmd_suffix			-> cmd_suffix WORD
	RULE_REDIRECT_LIST_FROM_IO_REDIRECT,											// redirect_list		-> io_redirect
	RULE_REDIRECT_LIST_FROM_REDIRECT_LIST_IO_REDIRECT,								// redirect_list		-> redirect_list io_redirect
	RULE_IO_REDIRECT_FROM_IO_FILE,													// io_redirect			-> io_file
	RULE_IO_REDIRECT_FROM_IO_NUMBER_IO_FILE,										// io_redirect			-> IO_NUMBER io_file
	RULE_IO_REDIRECT_FROM_IO_LOCATION_IO_FILE,										// io_redirect			-> IO_LOCATION io_file (optionally supported)
	RULE_IO_REDIRECT_FROM_IO_HERE,													// io_redirect			-> io_here
	RULE_IO_REDIRECT_FROM_IO_NUMBER_IO_HERE,										// io_redirect			-> IO_NUMBER io_here
	RULE_IO_REDIRECT_FROM_IO_LOCATION_IO_HERE,										// io_redirect			-> IO_LOCATION io_here (optionally supported)
	RULE_IO_FILE_FROM_LESS_FILENAME,												// io_file				-> '<' filename
	RULE_IO_FILE_FROM_LESSAND_FILENAME,												// io_file				-> LESSAND filename
	RULE_IO_FILE_FROM_GREAT_FILENAME,												// io_file				-> '>' filename
	RULE_IO_FILE_FROM_GREATAND_FILENAME,											// io_file				-> GREATAND filename
	RULE_IO_FILE_FROM_DGREAT_FILENAME,												// io_file				-> DGREAT filename
	RULE_IO_FILE_FROM_LESSGREAT_FILENAME,											// io_file				-> LESSGREAT filename
	RULE_IO_FILE_FROM_CLOBBER_FILENAME,												// io_file				-> CLOBBER filename
	RULE_FILENAME_FROM_WORD,														// filename				-> WORD (apply rule 2)
	RULE_IO_HERE_FROM_DLESS_HERE_END,												// io_here				-> DLESS here_end
	RULE_IO_HERE_FROM_DLESSDASH_HERE_END,											// io_here				-> DLESSDASH here_end
	RULE_HERE_END_FROM_WORD,														// here_end				-> WORD (apply rule 3)
	RULE_NEWLINE_LIST_FROM_NEWLINE,													// newline_list			-> NEWLINE
	RULE_NEWLINE_LIST_FROM_NEWLINE_LIST_NEWLINE,									// newline_list			-> newline_list NEWLINE
	RULE_LINEBREAK_FROM_NEWLINE_LIST,												// linebreak			-> newline_list
	RULE_LINEBREAK_FROM_EMPTY,														// linebreak			-> <empty>
	RULE_SEPARATOR_OP_FROM_AMPERSAND,												// separator_op			-> '&'
	RULE_SEPARATOR_OP_FROM_SEMICOLON,												// separator_op			-> ';'
	RULE_SEPARATOR_FROM_SEPARATOR_OP_LINEBREAK,										// separator			-> separator_op linebreak
	RULE_SEPARATOR_FROM_NEWLINE_LIST,												// separator			-> newline_list
	RULE_SEQUENTIAL_SEP_FROM_SEMICOLON_LINEBREAK,									// sequential_sep		-> ';' linebreak
	RULE_SEQUENTIAL_SEP_FROM_NEWLINE_LIST,											// sequential_sep		-> newline_list
	RULE_COUNT																		// rule_count			-> <sentinel>
}	t_rule_id;

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
	t_symbol_id	symbol;
	int			state;
	t_cst_node	*cst_node;	// borrowed
}	t_stack_item;

typedef struct s_stack
{
	t_stack_item	*items;
	size_t			cap;
	size_t			len;
}	t_stack;

/* ************************************************************************* */
/*                                 PARSER                                    */
/* ************************************************************************* */

typedef struct s_parser
{
	t_stack	stack;
	t_rule	rules[RULE_COUNT];
	// TODO: CST
	// TODO: AST
}	t_parser;

#endif
