#include "builder.h"

static void	rules_build_io_file_1(t_rule *rules);
static void	rules_build_io_file_2(t_rule *rules);
static void	rules_build_io_file_3(t_rule *rules);
static void	rules_build_io_file_4(t_rule *rules);

/*
io_file          : '<'       filename
                 | LESSAND   filename
                 | '>'       filename
                 | GREATAND  filename
                 | DGREAT    filename
                 | LESSGREAT filename
                 | CLOBBER   filename
                 ;
*/
void	rules_build_io_file(t_rule *rules)
{
	rules_build_io_file_1(rules);
	rules_build_io_file_2(rules);
	rules_build_io_file_3(rules);
	rules_build_io_file_4(rules);
}

// io_file -> '<' filename
// io_file -> LESSAND filename
static void	rules_build_io_file_1(t_rule *rules)
{
	rules[RULE_IO_FILE_1].lhs = SYM_io_file;
	rules[RULE_IO_FILE_1].rhs[0] = SYM_LESS;
	rules[RULE_IO_FILE_1].rhs[1] = SYM_filename;
	rules[RULE_IO_FILE_1].rhs_len = 2;
	rules[RULE_IO_FILE_2].lhs = SYM_io_file;
	rules[RULE_IO_FILE_2].rhs[0] = SYM_LESSAND;
	rules[RULE_IO_FILE_2].rhs[1] = SYM_filename;
	rules[RULE_IO_FILE_2].rhs_len = 2;
}

// io_file -> '>' filename
// io_file -> GREATAND filename
static void	rules_build_io_file_2(t_rule *rules)
{
	rules[RULE_IO_FILE_3].lhs = SYM_io_file;
	rules[RULE_IO_FILE_3].rhs[0] = SYM_GREAT;
	rules[RULE_IO_FILE_3].rhs[1] = SYM_filename;
	rules[RULE_IO_FILE_3].rhs_len = 2;
	rules[RULE_IO_FILE_4].lhs = SYM_io_file;
	rules[RULE_IO_FILE_4].rhs[0] = SYM_GREATAND;
	rules[RULE_IO_FILE_4].rhs[1] = SYM_filename;
	rules[RULE_IO_FILE_4].rhs_len = 2;
}

// io_file -> DGREAT filename
// io_file -> LESSGREAT filename
static void	rules_build_io_file_3(t_rule *rules)
{
	rules[RULE_IO_FILE_5].lhs = SYM_io_file;
	rules[RULE_IO_FILE_5].rhs[0] = SYM_DGREAT;
	rules[RULE_IO_FILE_5].rhs[1] = SYM_filename;
	rules[RULE_IO_FILE_5].rhs_len = 2;
	rules[RULE_IO_FILE_6].lhs = SYM_io_file;
	rules[RULE_IO_FILE_6].rhs[0] = SYM_LESSGREAT;
	rules[RULE_IO_FILE_6].rhs[1] = SYM_filename;
	rules[RULE_IO_FILE_6].rhs_len = 2;
}

// io_file -> CLOBBER filename
static void	rules_build_io_file_4(t_rule *rules)
{
	rules[RULE_IO_FILE_7].lhs = SYM_io_file;
	rules[RULE_IO_FILE_7].rhs[0] = SYM_CLOBBER;
	rules[RULE_IO_FILE_7].rhs[1] = SYM_filename;
	rules[RULE_IO_FILE_7].rhs_len = 2;
}
