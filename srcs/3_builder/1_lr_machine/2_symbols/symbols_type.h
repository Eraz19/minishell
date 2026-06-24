#ifndef SYMBOLS_TYPE_H
# define SYMBOLS_TYPE_H

// ⚠️ custom symbol SYM_function_header to allow easy computing of rule 9
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
	SYM_NEWLINE,		// \n		// AST transparent
	SYM_SEMI,			// ;		// AST transparent
	SYM_DSEMI,			// ;;		// AST transparent
	SYM_SEMI_AND,		// ;&
	SYM_AMPERSAND,		// &
	SYM_AND_IF,			// &&
	SYM_OR_IF,			// ||
	SYM_PIPE,			// |		// AST transparent
	SYM_LPARENTHESIS,	// (		// AST transparent
	SYM_RPARENTHESIS,	// )		// AST transparent
	//		- Redirection
	SYM_IO_NUMBER,		// [0-9]+
	SYM_IO_LOCATION,	// 3+ char, begins with '{', ends with '}', and the delimiter character is '<' or '>'
	SYM_LESS,			// <
	SYM_DLESS,			// <<		// AST transparent
	SYM_DLESSDASH,		// <<-		// AST transparent
	SYM_LESSAND,		// <&
	SYM_GREAT,			// >
	SYM_DGREAT,			// >>
	SYM_GREATAND,		// >&
	SYM_CLOBBER,		// >|
	SYM_LESSGREAT,		// <>
	//		- Reserved words
	SYM_Bang,			// !
	SYM_Lbrace,			// {		// AST transparent
	SYM_Rbrace,			// }		// AST transparent
	SYM_Case,			// case		// AST transparent
	SYM_Esac,			// esac		// AST transparent
	SYM_Do,				// do		// AST transparent
	SYM_Done,			// done		// AST transparent
	SYM_If,				// if		// AST transparent
	SYM_Then,			// then		// AST transparent
	SYM_Elif,			// elif		// AST transparent
	SYM_Else,			// else		// AST transparent
	SYM_Fi,				// fi		// AST transparent
	SYM_For,			// for		// AST transparent
	SYM_In,				// in		// AST transparent
	SYM_Until,			// until	// AST transparent
	SYM_While,			// while	// AST transparent
	//		- End of input
	SYM_EOF,
	// ----------------------------------------------------
	// NON_TERMINALS (GOTO table entries)
	//		- Transparent (irrelevant for AST nodes)
	SYM_start,
	SYM_program,
	SYM_cmd_name,
	SYM_cmd_word,
	SYM_filename,
	SYM_name,
	SYM_fname,
	SYM_in,
	SYM_sequential_sep,
	SYM_separator,
	SYM_linebreak,
	SYM_newline_list,
	//		- Relevant (used to build AST nodes)
	SYM_compound_command,	// [if/for/list/case/...]	(dispatcher)
	SYM_complete_commands,	// [t_ast_list]				(recursive wrapper)
	SYM_complete_command,	// [t_ast_list]				(wrapper)
	SYM_separator_op,		// [t_ast_list]				async ('&' = true | ';' = false)
	SYM_list,				// [t_ast_list]				(recursive wrapper)
	SYM_compound_list,		// [t_ast_list]				(recursive wrapper)
	SYM_term,				// [t_ast_list]				content
	SYM_subshell,			// [t_ast_list]				subshell = true
	SYM_brace_group,		// [t_ast_list]				subshell = false
	SYM_cmd_prefix,			// [t_ast_simple_command]	assignments/redirs
	SYM_cmd_suffix,			// [t_ast_simple_command]	words/redirs
	SYM_simple_command,		// [t_ast_simple_command]	content + redirs
	SYM_command,			// [t_ast_command]			dispatcher
	SYM_pipeline,			// [t_ast_pipeline]			negated
	SYM_pipe_sequence,		// [t_ast_pipeline]			commands
	SYM_and_or,				// [t_ast_and_or]			pipelines + operators
	SYM_redirect_list,		// [t_ast_redirection]		(recursive wrapper)
	SYM_io_redirect,		// [t_ast_redirection]		(wrapper)
	SYM_io_file,			// [t_ast_redirection]		operation
	SYM_io_here,			// [t_ast_redirection]		heredoc (mode)
	SYM_here_end,			// [t_ast_redirection]		heredoc (delimiter + metadata)
	SYM_if_clause,			// [t_ast_if]				conditions + bodies
	SYM_else_part,			// [t_ast_if]				else_body
	SYM_for_clause,			// [t_ast_for]				words
	SYM_wordlist,			// [t_ast_for]				words
	SYM_while_clause,		// [t_ast_loop]				condition_must_be_true = true
	SYM_until_clause,		// [t_ast_loop]				condition_must_be_true = false
	SYM_do_group,			// [for/while/until]		body
	SYM_case_clause,		// [t_ast_case]				word
	SYM_case_list_ns,		// [t_ast_case]				(wrapper)
	SYM_case_list,			// [t_ast_case]				(wrapper)
	SYM_case_item_ns,		// [t_ast_case]				(wrapper)
	SYM_case_item,			// [t_ast_case]				fallthrough
	SYM_pattern_list,		// [t_ast_case]				patterns
	SYM_function_definition,// [t_ast_function_def]		(wrapper)
	SYM_function_body,		// [t_ast_function_def]		body
	// ----------------------------------------------------
	SYM_COUNT,
	SYM_NONE,
	SYM_error
}	t_symbol;

# define SYM_RESERVED_MIN				SYM_Bang
# define SYM_RESERVED_MAX				SYM_While
# define SYM_TERMINAL_MAX				SYM_EOF
# define SYM_NON_TERMINAL_MIN			SYM_start
# define SYM_NON_TERMINAL_MAX			SYM_function_body
# define SYM_TERMINAL_RELEVANT_MAX		SYM_Bang
# define SYM_NON_TERMINAL_RELEVANT_MIN	SYM_compound_command
# define SYM_NON_TERMINAL_RELEVANT_MAX	SYM_function_body

#endif
