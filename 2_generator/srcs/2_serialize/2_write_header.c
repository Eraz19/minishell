#include "generator_serialize_priv.h"

#define GUARD				"#ifndef LR_TABLES_H\n# define LR_TABLES_H\n\n"
#define INCLUDE_1			"# include \"grammar_symbols.h\"\n"
#define INCLUDE_2			"# include \"grammar_actions.h\"\n"
#define INCLUDE_3			"# include \"grammar_qualifiers.h\"\n"
#define INCLUDE_4			"# include <stdbool.h>\n"
#define INCLUDE_5			"# include <stddef.h>\n\n"
#define _LR_STATE_COUNT		"# define LR_STATE_COUNT\t\t"	// + value
#define _ACTION_COL_COUNT	"\n# define ACTION_COL_COUNT\t"	// + value
#define _ACTION_COUNT		"\n# define ACTION_COUNT\t\t"	// + value
#define _GOTO_COL_COUNT		"\n# define GOTO_COL_COUNT\t\t"	// + value
#define _GOTO_COUNT			"\n# define GOTO_COUNT\t\t\t"	// + value
#define T_LR_RULE_1			"\n\ntypedef struct s_lr_rule\n{\n"
#define T_LR_RULE_2			"\tt_symbol\tlhs;\n\tsize_t\t\trhs_len;\n"
#define T_LR_RULE_3			"}\tt_lr_rule;\n\n"
#define T_LR_TABLE_1		"typedef struct s_lr_tables\n{\n"
#define T_LR_TABLE_2		"\t// rules[rule_id]\n"
#define T_LR_TABLE_3		"\tconst t_lr_rule\t\t*rules;\n"
#define T_LR_TABLE_4		"\t// actions[lr_state_id * ACTION_COL_COUNT + "
#define T_LR_TABLE_5		"terminal_symbol]\n"
#define T_LR_TABLE_6		"\tconst t_action\t\t*actions;\n"
#define T_LR_TABLE_7		"\t// gotos[lr_state_id * GOTO_COL_COUNT + symbol "
#define T_LR_TABLE_8		"- SYM_NON_TERMINAL_MIN]\n"
#define T_LR_TABLE_9		"\tconst size_t\t\t*gotos;\n"
#define T_LR_TABLE_10		"\t// qualifiers[lr_state_id]\n"
#define T_LR_TABLE_11		"\tconst t_qualifier\t*qualifiers;\n"
#define T_LR_TABLE_12		"\t// expects_cmd_name_or_word[lr_state_id]\n"
#define T_LR_TABLE_13		"\tconst bool\t\t\t*expects_cmd_name_or_word;\n"
#define T_LR_TABLE_14		"}	t_lr_tables;\n\n"
#define PROTO				"void\tlr_tables_load(t_lr_tables *tables);\n\n"
#define END_GUARD			"#endif\n\n"

bool	generator_write_header(int h_fd, const t_lr_generator *gen)
{
	const char	*content;

	content = GUARD INCLUDE_1 INCLUDE_2 INCLUDE_3 INCLUDE_4 INCLUDE_5;
	if (!generator_write(h_fd, content))
		return (false);
	if (!generator_write_zu(h_fd, _LR_STATE_COUNT, gen->lr_states.len))
		return (false);
	if (!generator_write_zu(h_fd, _ACTION_COL_COUNT, SYM_TERMINAL_MAX + 1))
		return (false);
	if (!generator_write_zu(h_fd, _ACTION_COUNT,
			gen->lr_states.len * (SYM_TERMINAL_MAX + 1)))
		return (false);
	if (!generator_write_zu(h_fd, _GOTO_COL_COUNT,
			SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1))
		return (false);
	if (!generator_write_zu(h_fd, _GOTO_COUNT, gen->lr_states.len
			* (SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1)))
		return (false);
	content = T_LR_RULE_1 T_LR_RULE_2 T_LR_RULE_3
		T_LR_TABLE_1 T_LR_TABLE_2 T_LR_TABLE_3 T_LR_TABLE_4 T_LR_TABLE_5
		T_LR_TABLE_6 T_LR_TABLE_7 T_LR_TABLE_8 T_LR_TABLE_9 T_LR_TABLE_10
		T_LR_TABLE_11 T_LR_TABLE_12 T_LR_TABLE_13 T_LR_TABLE_14
		PROTO END_GUARD;
	return (generator_write(h_fd, content));
}
