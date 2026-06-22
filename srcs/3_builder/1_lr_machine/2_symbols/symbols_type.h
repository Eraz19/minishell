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
	SYM_function_body,
	SYM_function_definition,
	SYM_function_header,	// ⚠️ custom
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
	SYM_NONE,
	SYM_error
}	t_symbol;

# define SYM_RESERVED_MIN		SYM_Bang
# define SYM_RESERVED_MAX		SYM_While
# define SYM_TERMINAL_MAX		SYM_EOF
# define SYM_NON_TERMINAL_MIN	SYM_start
# define SYM_NON_TERMINAL_MAX	SYM_sequential_sep

#endif
