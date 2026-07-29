#include "generator_serialize_priv.h"
#include "write_c_file_priv.h"

#define INCLUDE_1		"#include \"lr_tables.h\"\n"
#define INCLUDE_2		"#include \"grammar_rules.h\"\n\n"

#define FUNC_START		"void\tlr_tables_load(t_lr_tables *tables)\n{\n"

#define FUNC_ASSIGN_1	"\n\ttables->rules = rules;\n"
#define FUNC_ASSIGN_2	"\ttables->actions = actions;\n"
#define FUNC_ASSIGN_3	"\ttables->gotos = gotos;\n"
#define FUNC_ASSIGN_4	"\ttables->qualifiers = qualifiers;\n"
#define FUNC_ASSIGN_5	"\ttables->expects_cmd_name_or_word = "
#define FUNC_ASSIGN_6	"expects_cmd_name_or_word;\n"

#define FUNC_END		"}\n"

bool	generator_write_c_file(int c_fd, const t_lr_generator *gen)
{
	const char	*content;

	content = INCLUDE_1 INCLUDE_2 FUNC_START;
	if (!generator_write(c_fd, content))
		return (false);
	if (!generator_write_c_rules(c_fd, gen))
		return (false);
	// TODO
	content = FUNC_ASSIGN_1 FUNC_ASSIGN_2 FUNC_ASSIGN_3 FUNC_ASSIGN_4
		FUNC_ASSIGN_5 FUNC_ASSIGN_6 FUNC_END;
	return (generator_write(c_fd, content));
}
