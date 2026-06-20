#include "builder.h"
#include "token.h"

const char	*token_type_to_string(t_token_type token_type)
{
	switch (token_type)
	{
		case NONE: return ("NONE");
		case TOKEN: return ("TOKEN");
		case NEWLINE_: return ("NEWLINE_");
		case SCOLON: return ("SCOLON");
		case AMPERSAND: return ("AMPERSAND");
		case DSEMI: return ("DSEMI");
		case SEMI_AND: return ("SEMI_AND");
		case AND_IF: return ("AND_IF");
		case OR_IF: return ("OR_IF");
		case PIPE: return ("PIPE");
		case LPARENTHESIS: return ("LPARENTHESIS");
		case RPARENTHESIS: return ("RPARENTHESIS");
		case LESSAND: return ("LESSAND");
		case GREATAND: return ("GREATAND");
		case LESS: return ("LESS");
		case GREAT: return ("GREAT");
		case CLOBBER: return ("CLOBBER");
		case LESSGREAT: return ("LESSGREAT");
		case DGREAT: return ("DGREAT");
		case DLESS: return ("DLESS");
		case DLESSDASH: return ("DLESSDASH");
		case IO_NUMBER: return ("IO_NUMBER");
		case EOF_: return ("EOF_");
		default: return ("unknown");
	}
	return ("UNKNOWN_TOKEN_TYPE");
}

const char	*symbol_to_string(t_symbol symbol)
{
	switch (symbol)
	{
		case SYM_TOKEN: return ("SYM_TOKEN");
		case SYM_WORD: return ("SYM_WORD");
		case SYM_NAME: return ("SYM_NAME");
		case SYM_ASSIGNMENT_WORD: return ("SYM_ASSIGNMENT_WORD");
		case SYM_NEWLINE: return ("SYM_NEWLINE");
		case SYM_SEMI: return ("SYM_SEMI");
		case SYM_DSEMI: return ("SYM_DSEMI");
		case SYM_SEMI_AND: return ("SYM_SEMI_AND");
		case SYM_AMPERSAND: return ("SYM_AMPERSAND");
		case SYM_AND_IF: return ("SYM_AND_IF");
		case SYM_OR_IF: return ("SYM_OR_IF");
		case SYM_PIPE: return ("SYM_PIPE");
		case SYM_LPARENTHESIS: return ("SYM_LPARENTHESIS");
		case SYM_RPARENTHESIS: return ("SYM_RPARENTHESIS");
		case SYM_IO_NUMBER: return ("SYM_IO_NUMBER");
		case SYM_IO_LOCATION: return ("SYM_IO_LOCATION");
		case SYM_LESS: return ("SYM_LESS");
		case SYM_DLESS: return ("SYM_DLESS");
		case SYM_DLESSDASH: return ("SYM_DLESSDASH");
		case SYM_LESSAND: return ("SYM_LESSAND");
		case SYM_GREAT: return ("SYM_GREAT");
		case SYM_DGREAT: return ("SYM_DGREAT");
		case SYM_GREATAND: return ("SYM_GREATAND");
		case SYM_CLOBBER: return ("SYM_CLOBBER");
		case SYM_LESSGREAT: return ("SYM_LESSGREAT");
		case SYM_Bang: return ("SYM_Bang");
		case SYM_Lbrace: return ("SYM_Lbrace");
		case SYM_Rbrace: return ("SYM_Rbrace");
		case SYM_Case: return ("SYM_Case");
		case SYM_Esac: return ("SYM_Esac");
		case SYM_Do: return ("SYM_Do");
		case SYM_Done: return ("SYM_Done");
		case SYM_If: return ("SYM_If");
		case SYM_Then: return ("SYM_Then");
		case SYM_Elif: return ("SYM_Elif");
		case SYM_Else: return ("SYM_Else");
		case SYM_Fi: return ("SYM_Fi");
		case SYM_For: return ("SYM_For");
		case SYM_In: return ("SYM_In");
		case SYM_Until: return ("SYM_Until");
		case SYM_While: return ("SYM_While");
		case SYM_EOF: return ("SYM_EOF");
		case SYM_start: return ("SYM_start");
		case SYM_program: return ("SYM_program");
		case SYM_complete_commands: return ("SYM_complete_commands");
		case SYM_complete_command: return ("SYM_complete_command");
		case SYM_list: return ("SYM_list");
		case SYM_and_or: return ("SYM_and_or");
		case SYM_pipeline: return ("SYM_pipeline");
		case SYM_pipe_sequence: return ("SYM_pipe_sequence");
		case SYM_command: return ("SYM_command");
		case SYM_compound_command: return ("SYM_compound_command");
		case SYM_subshell: return ("SYM_subshell");
		case SYM_compound_list: return ("SYM_compound_list");
		case SYM_term: return ("SYM_term");
		case SYM_for_clause: return ("SYM_for_clause");
		case SYM_name: return ("SYM_name");
		case SYM_in: return ("SYM_in");
		case SYM_wordlist: return ("SYM_wordlist");
		case SYM_case_clause: return ("SYM_case_clause");
		case SYM_case_list_ns: return ("SYM_case_list_ns");
		case SYM_case_list: return ("SYM_case_list");
		case SYM_case_item_ns: return ("SYM_case_item_ns");
		case SYM_case_item: return ("SYM_case_item");
		case SYM_pattern_list: return ("SYM_pattern_list");
		case SYM_if_clause: return ("SYM_if_clause");
		case SYM_else_part: return ("SYM_else_part");
		case SYM_while_clause: return ("SYM_while_clause");
		case SYM_until_clause: return ("SYM_until_clause");
		case SYM_function_definition: return ("SYM_function_definition");
		case SYM_function_body: return ("SYM_function_body");
		case SYM_fname: return ("SYM_fname");
		case SYM_brace_group: return ("SYM_brace_group");
		case SYM_do_group: return ("SYM_do_group");
		case SYM_simple_command: return ("SYM_simple_command");
		case SYM_cmd_name: return ("SYM_cmd_name");
		case SYM_cmd_word: return ("SYM_cmd_word");
		case SYM_cmd_prefix: return ("SYM_cmd_prefix");
		case SYM_cmd_suffix: return ("SYM_cmd_suffix");
		case SYM_redirect_list: return ("SYM_redirect_list");
		case SYM_io_redirect: return ("SYM_io_redirect");
		case SYM_io_file: return ("SYM_io_file");
		case SYM_filename: return ("SYM_filename");
		case SYM_io_here: return ("SYM_io_here");
		case SYM_here_end: return ("SYM_here_end");
		case SYM_newline_list: return ("SYM_newline_list");
		case SYM_linebreak: return ("SYM_linebreak");
		case SYM_separator_op: return ("SYM_separator_op");
		case SYM_separator: return ("SYM_separator");
		case SYM_sequential_sep: return ("SYM_sequential_sep");
		case SYM_COUNT: return ("SYM_COUNT");
		case SYM_NONE: return ("SYM_NONE");
		case SYM_error: return ("SYM_error");
		default: return ("unknown");
	}
	return ("UNKNOWN_SYMBOL");
}

const char	*action_type_to_string(t_action_type action_type)
{
	switch (action_type)
	{
		case ACTION_SHIFT: return ("ACTION_SHIFT");
		case ACTION_REDUCE: return ("ACTION_REDUCE");
		case ACTION_ACCEPT: return ("ACTION_ACCEPT");
		case ACTION_ERROR: return ("ACTION_ERROR");
		default: return ("unknown");
	}
	return ("UNKNOWN_ACTION");
}
