tree
```bash
1_lr_machine
├── 1_hooks
│   ├── hooks.h
│   └── TODO_hooks.c
├── 2_rules
│   ├── rules__main.c
│   ├── rules__priv.h
│   ├── rules__pub.h
│   ├── rules_and_or.c
│   ├── rules_brace_group.c
│   ├── rules_case_clause.c
│   ├── rules_case_item_ns.c
│   ├── rules_case_item.c
│   ├── rules_case_list_ns.c
│   ├── rules_case_list.c
│   ├── rules_cmd_name.c
│   ├── rules_cmd_prefix.c
│   ├── rules_cmd_suffix.c
│   ├── rules_cmd_word.c
│   ├── rules_command.c
│   ├── rules_complete_command.c
│   ├── rules_complete_commands.c
│   ├── rules_compound_command.c
│   ├── rules_compound_list.c
│   ├── rules_do_group.c
│   ├── rules_else_part.c
│   ├── rules_filename.c
│   ├── rules_fname.c
│   ├── rules_for_clause.c
│   ├── rules_function_body.c
│   ├── rules_function_definition.c
│   ├── rules_here_end.c
│   ├── rules_if_clause.c
│   ├── rules_in.c
│   ├── rules_io_file.c
│   ├── rules_io_here.c
│   ├── rules_io_redirect.c
│   ├── rules_linebreak.c
│   ├── rules_list.c
│   ├── rules_name.c
│   ├── rules_newline_list.c
│   ├── rules_pattern_list.c
│   ├── rules_pipe_sequence.c
│   ├── rules_pipeline.c
│   ├── rules_program.c
│   ├── rules_redirect_list.c
│   ├── rules_separator_op.c
│   ├── rules_separator.c
│   ├── rules_sequential_sep.c
│   ├── rules_simple_command.c
│   ├── rules_start.c
│   ├── rules_subshell.c
│   ├── rules_term.c
│   ├── rules_until_clause.c
│   ├── rules_while_clause.c
│   └── rules_wordlist.c
├── 3_rule_state
│   ├── rule_state.c
│   └── rule_state.h
├── 4_lr_state
│   ├── 1_life_cycle.c
│   ├── 2_helpers.c
│   ├── 3_core.c
│   └── lr_state.h
├── 5_transition
│   ├── 1_life_cycle.c
│   ├── 2_core.c
│   └── transition.h
├── 6_action
│   ├── 1_life_cycle.c
│   ├── 2_default.c
│   ├── 3_core.c
│   ├── action_priv.h
│   └── action.h
├── 7_goto
│   ├── 1_life_cycle.c
│   ├── 2_core.c
│   └── goto.h
├── lr_machine.c
└── lr_machine.h

8 directories, 72 files
```

./1_hooks/hooks.h
```c
#ifndef HOOKS_H
# define HOOKS_H

# include "parser.h"

bool	hook_2(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_3(t_stack_item *rhs, size_t rhs_len, void *ctx); // trigger le switch en heredoc mode avec le delimiter still quoted
bool	hook_4(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_5(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_6(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_7a(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_7b(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_8(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_9(t_stack_item *rhs, size_t rhs_len, void *ctx);

#endif

```

./1_hooks/TODO_hooks.c
```c
#include "parser.h"

// TODO: tmp placeholders to allow compilation of lr_machine POC

bool	hook_2(t_stack_item *rhs, size_t rhs_len, void *ctx)
{
	(void)rhs;
	(void)rhs_len;
	(void)ctx;
	return (true);
}

bool	hook_3(t_stack_item *rhs, size_t rhs_len, void *ctx)
{
	(void)rhs;
	(void)rhs_len;
	(void)ctx;
	return (true);
}

bool	hook_4(t_stack_item *rhs, size_t rhs_len, void *ctx)
{
	(void)rhs;
	(void)rhs_len;
	(void)ctx;
	return (true);
}

bool	hook_5(t_stack_item *rhs, size_t rhs_len, void *ctx)
{
	(void)rhs;
	(void)rhs_len;
	(void)ctx;
	return (true);
}

bool	hook_6(t_stack_item *rhs, size_t rhs_len, void *ctx)
{
	(void)rhs;
	(void)rhs_len;
	(void)ctx;
	return (true);
}

bool	hook_7a(t_stack_item *rhs, size_t rhs_len, void *ctx)
{
	(void)rhs;
	(void)rhs_len;
	(void)ctx;
	return (true);
}

bool	hook_7b(t_stack_item *rhs, size_t rhs_len, void *ctx)
{
	(void)rhs;
	(void)rhs_len;
	(void)ctx;
	return (true);
}

bool	hook_8(t_stack_item *rhs, size_t rhs_len, void *ctx)
{
	(void)rhs;
	(void)rhs_len;
	(void)ctx;
	return (true);
}

bool	hook_9(t_stack_item *rhs, size_t rhs_len, void *ctx)
{
	(void)rhs;
	(void)rhs_len;
	(void)ctx;
	return (true);
}

```

./2_rules/rules__main.c
```c
#include "rules__priv.h"
#include "libft.h"

static void	build_remaining_rules(t_rule *rules);

void	rules_init(t_rule *rules)
{
	ft_bzero(rules, RULE_COUNT * sizeof(*rules));
}

void	rules_build(t_rule *rules)
{
	rules_build_and_or(rules);
	rules_build_brace_group(rules);
	rules_build_case_clause(rules);
	rules_build_case_item_ns(rules);
	rules_build_case_item(rules);
	rules_build_case_list_ns(rules);
	rules_build_case_list(rules);
	rules_build_cmd_name(rules);
	rules_build_cmd_prefix(rules);
	rules_build_cmd_suffix(rules);
	rules_build_cmd_word(rules);
	rules_build_command(rules);
	rules_build_complete_command(rules);
	rules_build_complete_commands(rules);
	rules_build_compound_command(rules);
	rules_build_compound_list(rules);
	rules_build_do_group(rules);
	rules_build_else_part(rules);
	rules_build_filename(rules);
	rules_build_fname(rules);
	rules_build_for_clause(rules);
	rules_build_function_body(rules);
	rules_build_function_definition(rules);
	build_remaining_rules(rules);
}

static void	build_remaining_rules(t_rule *rules)
{
	rules_build_here_end(rules);
	rules_build_if_clause(rules);
	rules_build_in(rules);
	rules_build_io_file(rules);
	rules_build_io_here(rules);
	rules_build_io_redirect(rules);
	rules_build_linebreak(rules);
	rules_build_list(rules);
	rules_build_name(rules);
	rules_build_newline_list(rules);
	rules_build_pattern_list(rules);
	rules_build_pipe_sequence(rules);
	rules_build_pipeline(rules);
	rules_build_program(rules);
	rules_build_redirect_list(rules);
	rules_build_separator_op(rules);
	rules_build_separator(rules);
	rules_build_sequential_sep(rules);
	rules_build_simple_command(rules);
	rules_build_start(rules);
	rules_build_subshell(rules);
	rules_build_term(rules);
	rules_build_until_clause(rules);
	rules_build_while_clause(rules);
	rules_build_wordlist(rules);
}

```

./2_rules/rules__priv.h
```c
#ifndef RULES__PRIV_H
# define RULES__PRIV_H

# include "parser.h"

void	rules_build_and_or(t_rule *rules);
void	rules_build_brace_group(t_rule *rules);
void	rules_build_case_clause(t_rule *rules);
void	rules_build_case_item(t_rule *rules);
void	rules_build_case_item_ns(t_rule *rules);
void	rules_build_case_list(t_rule *rules);
void	rules_build_case_list_ns(t_rule *rules);
void	rules_build_cmd_name(t_rule *rules);
void	rules_build_cmd_prefix(t_rule *rules);
void	rules_build_cmd_suffix(t_rule *rules);
void	rules_build_cmd_word(t_rule *rules);
void	rules_build_command(t_rule *rules);
void	rules_build_complete_command(t_rule *rules);
void	rules_build_complete_commands(t_rule *rules);
void	rules_build_compound_command(t_rule *rules);
void	rules_build_compound_list(t_rule *rules);
void	rules_build_do_group(t_rule *rules);
void	rules_build_else_part(t_rule *rules);
void	rules_build_filename(t_rule *rules);
void	rules_build_fname(t_rule *rules);
void	rules_build_for_clause(t_rule *rules);
void	rules_build_function_body(t_rule *rules);
void	rules_build_function_definition(t_rule *rules);
void	rules_build_here_end(t_rule *rules);
void	rules_build_if_clause(t_rule *rules);
void	rules_build_in(t_rule *rules);
void	rules_build_io_file(t_rule *rules);
void	rules_build_io_here(t_rule *rules);
void	rules_build_io_redirect(t_rule *rules);
void	rules_build_linebreak(t_rule *rules);
void	rules_build_list(t_rule *rules);
void	rules_build_name(t_rule *rules);
void	rules_build_newline_list(t_rule *rules);
void	rules_build_pattern_list(t_rule *rules);
void	rules_build_pipeline(t_rule *rules);
void	rules_build_pipe_sequence(t_rule *rules);
void	rules_build_program(t_rule *rules);
void	rules_build_redirect_list(t_rule *rules);
void	rules_build_sequential_sep(t_rule *rules);
void	rules_build_separator(t_rule *rules);
void	rules_build_separator_op(t_rule *rules);
void	rules_build_simple_command(t_rule *rules);
void	rules_build_start(t_rule *rules);
void	rules_build_subshell(t_rule *rules);
void	rules_build_term(t_rule *rules);
void	rules_build_until_clause(t_rule *rules);
void	rules_build_while_clause(t_rule *rules);
void	rules_build_wordlist(t_rule *rules);

#endif

```

./2_rules/rules__pub.h
```c
#ifndef RULES_H
# define RULES_H

# include "parser.h"

void	rules_init(t_rule *rules);
void	rules_build(t_rule *rules);

#endif

```

./2_rules/rules_and_or.c
```c
#include "parser.h"

static void	rules_build_and_or_1(t_rule *rules);
static void	rules_build_and_or_2(t_rule *rules);
static void	rules_build_and_or_3(t_rule *rules);

/*
and_or           :                         pipeline
                 | and_or AND_IF linebreak pipeline
                 | and_or OR_IF  linebreak pipeline
                 ;
*/
void	rules_build_and_or(t_rule *rules)
{
	rules_build_and_or_1(rules);
	rules_build_and_or_2(rules);
	rules_build_and_or_3(rules);
}

// and_or -> pipeline
static void	rules_build_and_or_1(t_rule *rules)
{
	rules[RULE_AND_OR_1].lhs = SYM_and_or;
	rules[RULE_AND_OR_1].rhs[0] = SYM_pipeline;
	rules[RULE_AND_OR_1].rhs_len = 1;
}

// and_or -> and_or AND_IF linebreak pipeline
static void	rules_build_and_or_2(t_rule *rules)
{
	rules[RULE_AND_OR_2].lhs = SYM_and_or;
	rules[RULE_AND_OR_2].rhs[0] = SYM_and_or;
	rules[RULE_AND_OR_2].rhs[1] = SYM_AND_IF;
	rules[RULE_AND_OR_2].rhs[2] = SYM_linebreak;
	rules[RULE_AND_OR_2].rhs[3] = SYM_pipeline;
	rules[RULE_AND_OR_2].rhs_len = 4;
}

// and_or -> and_or OR_IF linebreak pipeline
static void	rules_build_and_or_3(t_rule *rules)
{
	rules[RULE_AND_OR_3].lhs = SYM_and_or;
	rules[RULE_AND_OR_3].rhs[0] = SYM_and_or;
	rules[RULE_AND_OR_3].rhs[1] = SYM_OR_IF;
	rules[RULE_AND_OR_3].rhs[2] = SYM_linebreak;
	rules[RULE_AND_OR_3].rhs[3] = SYM_pipeline;
	rules[RULE_AND_OR_3].rhs_len = 4;
}

```

./2_rules/rules_brace_group.c
```c
#include "parser.h"

/*
brace_group      : Lbrace compound_list Rbrace
                 ;
*/
void	rules_build_brace_group(t_rule *rules)
{
	rules[RULE_BRACE_GROUP_1].lhs = SYM_brace_group;
	rules[RULE_BRACE_GROUP_1].rhs[0] = SYM_Lbrace;
	rules[RULE_BRACE_GROUP_1].rhs[1] = SYM_compound_list;
	rules[RULE_BRACE_GROUP_1].rhs[2] = SYM_Rbrace;
	rules[RULE_BRACE_GROUP_1].rhs_len = 3;
}

```

./2_rules/rules_case_clause.c
```c
#include "parser.h"

static void	rules_build_case_clause_1(t_rule *rules);
static void	rules_build_case_clause_2(t_rule *rules);
static void	rules_build_case_clause_3(t_rule *rules);

/*
case_clause      : Case WORD linebreak in linebreak case_list    Esac
                 | Case WORD linebreak in linebreak case_list_ns Esac
                 | Case WORD linebreak in linebreak              Esac
                 ;
*/
void	rules_build_case_clause(t_rule *rules)
{
	rules_build_case_clause_1(rules);
	rules_build_case_clause_2(rules);
	rules_build_case_clause_3(rules);
}

// case_clause -> Case WORD linebreak in linebreak case_list Esac
static void	rules_build_case_clause_1(t_rule *rules)
{
	rules[RULE_CASE_CLAUSE_1].lhs = SYM_case_clause;
	rules[RULE_CASE_CLAUSE_1].rhs[0] = SYM_Case;
	rules[RULE_CASE_CLAUSE_1].rhs[1] = SYM_WORD;
	rules[RULE_CASE_CLAUSE_1].rhs[2] = SYM_linebreak;
	rules[RULE_CASE_CLAUSE_1].rhs[3] = SYM_in;
	rules[RULE_CASE_CLAUSE_1].rhs[4] = SYM_linebreak;
	rules[RULE_CASE_CLAUSE_1].rhs[5] = SYM_case_list;
	rules[RULE_CASE_CLAUSE_1].rhs[6] = SYM_Esac;
	rules[RULE_CASE_CLAUSE_1].rhs_len = 7;
}

// case_clause -> Case WORD linebreak in linebreak case_list_ns Esac
static void	rules_build_case_clause_2(t_rule *rules)
{
	rules[RULE_CASE_CLAUSE_2].lhs = SYM_case_clause;
	rules[RULE_CASE_CLAUSE_2].rhs[0] = SYM_Case;
	rules[RULE_CASE_CLAUSE_2].rhs[1] = SYM_WORD;
	rules[RULE_CASE_CLAUSE_2].rhs[2] = SYM_linebreak;
	rules[RULE_CASE_CLAUSE_2].rhs[3] = SYM_in;
	rules[RULE_CASE_CLAUSE_2].rhs[4] = SYM_linebreak;
	rules[RULE_CASE_CLAUSE_2].rhs[5] = SYM_case_list_ns;
	rules[RULE_CASE_CLAUSE_2].rhs[6] = SYM_Esac;
	rules[RULE_CASE_CLAUSE_2].rhs_len = 7;
}

// case_clause -> Case WORD linebreak in linebreak Esac
static void	rules_build_case_clause_3(t_rule *rules)
{
	rules[RULE_CASE_CLAUSE_3].lhs = SYM_case_clause;
	rules[RULE_CASE_CLAUSE_3].rhs[0] = SYM_Case;
	rules[RULE_CASE_CLAUSE_3].rhs[1] = SYM_WORD;
	rules[RULE_CASE_CLAUSE_3].rhs[2] = SYM_linebreak;
	rules[RULE_CASE_CLAUSE_3].rhs[3] = SYM_in;
	rules[RULE_CASE_CLAUSE_3].rhs[4] = SYM_linebreak;
	rules[RULE_CASE_CLAUSE_3].rhs[5] = SYM_Esac;
	rules[RULE_CASE_CLAUSE_3].rhs_len = 6;
}

```

./2_rules/rules_case_item_ns.c
```c
#include "parser.h"

static void	rules_build_case_item_ns_1(t_rule *rules);
static void	rules_build_case_item_ns_2(t_rule *rules);

/*
case_item_ns     : pattern_list ')' linebreak
                 | pattern_list ')' compound_list
                 ;
*/
void	rules_build_case_item_ns(t_rule *rules)
{
	rules_build_case_item_ns_1(rules);
	rules_build_case_item_ns_2(rules);
}

// case_item_ns -> pattern_list ')' linebreak
static void	rules_build_case_item_ns_1(t_rule *rules)
{
	rules[RULE_CASE_ITEM_NS_1].lhs = SYM_case_item_ns;
	rules[RULE_CASE_ITEM_NS_1].rhs[0] = SYM_pattern_list;
	rules[RULE_CASE_ITEM_NS_1].rhs[1] = SYM_RPARENTHESIS;
	rules[RULE_CASE_ITEM_NS_1].rhs[2] = SYM_linebreak;
	rules[RULE_CASE_ITEM_NS_1].rhs_len = 3;
}

// case_item_ns -> pattern_list ')' compound_list
static void	rules_build_case_item_ns_2(t_rule *rules)
{
	rules[RULE_CASE_ITEM_NS_2].lhs = SYM_case_item_ns;
	rules[RULE_CASE_ITEM_NS_2].rhs[0] = SYM_pattern_list;
	rules[RULE_CASE_ITEM_NS_2].rhs[1] = SYM_RPARENTHESIS;
	rules[RULE_CASE_ITEM_NS_2].rhs[2] = SYM_compound_list;
	rules[RULE_CASE_ITEM_NS_2].rhs_len = 3;
}

```

./2_rules/rules_case_item.c
```c
#include "parser.h"

static void	rules_build_case_item_1(t_rule *rules);
static void	rules_build_case_item_2(t_rule *rules);
static void	rules_build_case_item_3(t_rule *rules);
static void	rules_build_case_item_4(t_rule *rules);

/*
case_item        : pattern_list ')' linebreak     DSEMI linebreak
                 | pattern_list ')' compound_list DSEMI linebreak
                 | pattern_list ')' linebreak     SEMI_AND linebreak
                 | pattern_list ')' compound_list SEMI_AND linebreak
                 ;
*/
void	rules_build_case_item(t_rule *rules)
{
	rules_build_case_item_1(rules);
	rules_build_case_item_2(rules);
	rules_build_case_item_3(rules);
	rules_build_case_item_4(rules);
}

// case_item -> pattern_list ')' linebreak DSEMI linebreak
static void	rules_build_case_item_1(t_rule *rules)
{
	rules[RULE_CASE_ITEM_1].lhs = SYM_case_item;
	rules[RULE_CASE_ITEM_1].rhs[0] = SYM_pattern_list;
	rules[RULE_CASE_ITEM_1].rhs[1] = SYM_RPARENTHESIS;
	rules[RULE_CASE_ITEM_1].rhs[2] = SYM_linebreak;
	rules[RULE_CASE_ITEM_1].rhs[3] = SYM_DSEMI;
	rules[RULE_CASE_ITEM_1].rhs[4] = SYM_linebreak;
	rules[RULE_CASE_ITEM_1].rhs_len = 5;
}

// case_item -> pattern_list ')' compound_list DSEMI linebreak
static void	rules_build_case_item_2(t_rule *rules)
{
	rules[RULE_CASE_ITEM_2].lhs = SYM_case_item;
	rules[RULE_CASE_ITEM_2].rhs[0] = SYM_pattern_list;
	rules[RULE_CASE_ITEM_2].rhs[1] = SYM_RPARENTHESIS;
	rules[RULE_CASE_ITEM_2].rhs[2] = SYM_compound_list;
	rules[RULE_CASE_ITEM_2].rhs[3] = SYM_DSEMI;
	rules[RULE_CASE_ITEM_2].rhs[4] = SYM_linebreak;
	rules[RULE_CASE_ITEM_2].rhs_len = 5;
}

// case_item -> pattern_list ')' linebreak SEMI_AND linebreak
static void	rules_build_case_item_3(t_rule *rules)
{
	rules[RULE_CASE_ITEM_3].lhs = SYM_case_item;
	rules[RULE_CASE_ITEM_3].rhs[0] = SYM_pattern_list;
	rules[RULE_CASE_ITEM_3].rhs[1] = SYM_RPARENTHESIS;
	rules[RULE_CASE_ITEM_3].rhs[2] = SYM_linebreak;
	rules[RULE_CASE_ITEM_3].rhs[3] = SYM_SEMI_AND;
	rules[RULE_CASE_ITEM_3].rhs[4] = SYM_linebreak;
	rules[RULE_CASE_ITEM_3].rhs_len = 5;
}

// case_item -> pattern_list ')' compound_list SEMI_AND linebreak
static void	rules_build_case_item_4(t_rule *rules)
{
	rules[RULE_CASE_ITEM_4].lhs = SYM_case_item;
	rules[RULE_CASE_ITEM_4].rhs[0] = SYM_pattern_list;
	rules[RULE_CASE_ITEM_4].rhs[1] = SYM_RPARENTHESIS;
	rules[RULE_CASE_ITEM_4].rhs[2] = SYM_compound_list;
	rules[RULE_CASE_ITEM_4].rhs[3] = SYM_SEMI_AND;
	rules[RULE_CASE_ITEM_4].rhs[4] = SYM_linebreak;
	rules[RULE_CASE_ITEM_4].rhs_len = 5;
}

```

./2_rules/rules_case_list_ns.c
```c
#include "parser.h"

static void	rules_build_case_list_ns_1(t_rule *rules);
static void	rules_build_case_list_ns_2(t_rule *rules);

/*
case_list_ns     : case_list case_item_ns
                 |           case_item_ns
                 ;
*/
void	rules_build_case_list_ns(t_rule *rules)
{
	rules_build_case_list_ns_1(rules);
	rules_build_case_list_ns_2(rules);
}

// case_list_ns -> case_list case_item_ns
static void	rules_build_case_list_ns_1(t_rule *rules)
{
	rules[RULE_CASE_LIST_NS_1].lhs = SYM_case_list_ns;
	rules[RULE_CASE_LIST_NS_1].rhs[0] = SYM_case_list;
	rules[RULE_CASE_LIST_NS_1].rhs[1] = SYM_case_item_ns;
	rules[RULE_CASE_LIST_NS_1].rhs_len = 2;
}

// case_list_ns -> case_item_ns
static void	rules_build_case_list_ns_2(t_rule *rules)
{
	rules[RULE_CASE_LIST_NS_2].lhs = SYM_case_list_ns;
	rules[RULE_CASE_LIST_NS_2].rhs[0] = SYM_case_item_ns;
	rules[RULE_CASE_LIST_NS_2].rhs_len = 1;
}

```

./2_rules/rules_case_list.c
```c
#include "parser.h"

static void	rules_build_case_list_1(t_rule *rules);
static void	rules_build_case_list_2(t_rule *rules);

/*
case_list        : case_list case_item
                 |           case_item
                 ;
*/
void	rules_build_case_list(t_rule *rules)
{
	rules_build_case_list_1(rules);
	rules_build_case_list_2(rules);
}

// case_list -> case_list case_item
static void	rules_build_case_list_1(t_rule *rules)
{
	rules[RULE_CASE_LIST_1].lhs = SYM_case_list;
	rules[RULE_CASE_LIST_1].rhs[0] = SYM_case_list;
	rules[RULE_CASE_LIST_1].rhs[1] = SYM_case_item;
	rules[RULE_CASE_LIST_1].rhs_len = 2;
}

// case_list -> case_item
static void	rules_build_case_list_2(t_rule *rules)
{
	rules[RULE_CASE_LIST_2].lhs = SYM_case_list;
	rules[RULE_CASE_LIST_2].rhs[0] = SYM_case_item;
	rules[RULE_CASE_LIST_2].rhs_len = 1;
}

```

./2_rules/rules_cmd_name.c
```c
#include "parser.h"
#include "hooks.h"

/*
cmd_name         : WORD (apply rule 7a)
                 ;
*/
void	rules_build_cmd_name(t_rule *rules)
{
	rules[RULE_CMD_NAME_1].lhs = SYM_cmd_name;
	rules[RULE_CMD_NAME_1].rhs[0] = SYM_WORD;
	rules[RULE_CMD_NAME_1].rhs_len = 1;
	rules[RULE_CMD_NAME_1].hook = hook_7a;
}

```

./2_rules/rules_cmd_prefix.c
```c
#include "parser.h"

static void	rules_build_cmd_prefix_1(t_rule *rules);
static void	rules_build_cmd_prefix_2(t_rule *rules);
static void	rules_build_cmd_prefix_3(t_rule *rules);
static void	rules_build_cmd_prefix_4(t_rule *rules);

/*
cmd_prefix       :            io_redirect
                 | cmd_prefix io_redirect
                 |            ASSIGNMENT_WORD
                 | cmd_prefix ASSIGNMENT_WORD
                 ;
*/
void	rules_build_cmd_prefix(t_rule *rules)
{
	rules_build_cmd_prefix_1(rules);
	rules_build_cmd_prefix_2(rules);
	rules_build_cmd_prefix_3(rules);
	rules_build_cmd_prefix_4(rules);
}

// cmd_prefix -> io_redirect
static void	rules_build_cmd_prefix_1(t_rule *rules)
{
	rules[RULE_CMD_PREFIX_1].lhs = SYM_cmd_prefix;
	rules[RULE_CMD_PREFIX_1].rhs[0] = SYM_io_redirect;
	rules[RULE_CMD_PREFIX_1].rhs_len = 1;
}

// cmd_prefix -> cmd_prefix io_redirect
static void	rules_build_cmd_prefix_2(t_rule *rules)
{
	rules[RULE_CMD_PREFIX_2].lhs = SYM_cmd_prefix;
	rules[RULE_CMD_PREFIX_2].rhs[0] = SYM_cmd_prefix;
	rules[RULE_CMD_PREFIX_2].rhs[1] = SYM_io_redirect;
	rules[RULE_CMD_PREFIX_2].rhs_len = 2;
}

// cmd_prefix -> ASSIGNMENT_WORD
static void	rules_build_cmd_prefix_3(t_rule *rules)
{
	rules[RULE_CMD_PREFIX_3].lhs = SYM_cmd_prefix;
	rules[RULE_CMD_PREFIX_3].rhs[0] = SYM_ASSIGNMENT_WORD;
	rules[RULE_CMD_PREFIX_3].rhs_len = 1;
}

// cmd_prefix -> cmd_prefix ASSIGNMENT_WORD
static void	rules_build_cmd_prefix_4(t_rule *rules)
{
	rules[RULE_CMD_PREFIX_4].lhs = SYM_cmd_prefix;
	rules[RULE_CMD_PREFIX_4].rhs[0] = SYM_cmd_prefix;
	rules[RULE_CMD_PREFIX_4].rhs[1] = SYM_ASSIGNMENT_WORD;
	rules[RULE_CMD_PREFIX_4].rhs_len = 2;
}

```

./2_rules/rules_cmd_suffix.c
```c
#include "parser.h"

static void	rules_build_cmd_suffix_1(t_rule *rules);
static void	rules_build_cmd_suffix_2(t_rule *rules);
static void	rules_build_cmd_suffix_3(t_rule *rules);
static void	rules_build_cmd_suffix_4(t_rule *rules);

/*
cmd_suffix       :            io_redirect
                 | cmd_suffix io_redirect
                 |            WORD
                 | cmd_suffix WORD
                 ;
*/
void	rules_build_cmd_suffix(t_rule *rules)
{
	rules_build_cmd_suffix_1(rules);
	rules_build_cmd_suffix_2(rules);
	rules_build_cmd_suffix_3(rules);
	rules_build_cmd_suffix_4(rules);
}

// cmd_suffix -> io_redirect
static void	rules_build_cmd_suffix_1(t_rule *rules)
{
	rules[RULE_CMD_SUFFIX_1].lhs = SYM_cmd_suffix;
	rules[RULE_CMD_SUFFIX_1].rhs[0] = SYM_io_redirect;
	rules[RULE_CMD_SUFFIX_1].rhs_len = 1;
}

// cmd_suffix -> cmd_suffix io_redirect
static void	rules_build_cmd_suffix_2(t_rule *rules)
{
	rules[RULE_CMD_SUFFIX_2].lhs = SYM_cmd_suffix;
	rules[RULE_CMD_SUFFIX_2].rhs[0] = SYM_cmd_suffix;
	rules[RULE_CMD_SUFFIX_2].rhs[1] = SYM_io_redirect;
	rules[RULE_CMD_SUFFIX_2].rhs_len = 2;
}

// cmd_suffix -> WORD
static void	rules_build_cmd_suffix_3(t_rule *rules)
{
	rules[RULE_CMD_SUFFIX_3].lhs = SYM_cmd_suffix;
	rules[RULE_CMD_SUFFIX_3].rhs[0] = SYM_WORD;
	rules[RULE_CMD_SUFFIX_3].rhs_len = 1;
}

// cmd_suffix -> cmd_suffix WORD
static void	rules_build_cmd_suffix_4(t_rule *rules)
{
	rules[RULE_CMD_SUFFIX_4].lhs = SYM_cmd_suffix;
	rules[RULE_CMD_SUFFIX_4].rhs[0] = SYM_cmd_suffix;
	rules[RULE_CMD_SUFFIX_4].rhs[1] = SYM_WORD;
	rules[RULE_CMD_SUFFIX_4].rhs_len = 2;
}

```

./2_rules/rules_cmd_word.c
```c
#include "parser.h"
#include "hooks.h"

/*
cmd_word         : WORD (apply rule 7b)
                 ;
*/
void	rules_build_cmd_word(t_rule *rules)
{
	rules[RULE_CMD_WORD_1].lhs = SYM_cmd_word;
	rules[RULE_CMD_WORD_1].rhs[0] = SYM_WORD;
	rules[RULE_CMD_WORD_1].rhs_len = 1;
	rules[RULE_CMD_WORD_1].hook = hook_7b;
}

```

./2_rules/rules_command.c
```c
#include "parser.h"

static void	rules_build_command_1(t_rule *rules);
static void	rules_build_command_2(t_rule *rules);
static void	rules_build_command_3(t_rule *rules);
static void	rules_build_command_4(t_rule *rules);

/*
command          : simple_command
                 | compound_command
                 | compound_command redirect_list
                 | function_definition
                 ;
*/
void	rules_build_command(t_rule *rules)
{
	rules_build_command_1(rules);
	rules_build_command_2(rules);
	rules_build_command_3(rules);
	rules_build_command_4(rules);
}

// command -> simple_command
static void	rules_build_command_1(t_rule *rules)
{
	rules[RULE_COMMAND_1].lhs = SYM_command;
	rules[RULE_COMMAND_1].rhs[0] = SYM_simple_command;
	rules[RULE_COMMAND_1].rhs_len = 1;
}

// command -> compound_command
static void	rules_build_command_2(t_rule *rules)
{
	rules[RULE_COMMAND_2].lhs = SYM_command;
	rules[RULE_COMMAND_2].rhs[0] = SYM_compound_command;
	rules[RULE_COMMAND_2].rhs_len = 1;
}

// command -> compound_command redirect_list
static void	rules_build_command_3(t_rule *rules)
{
	rules[RULE_COMMAND_3].lhs = SYM_command;
	rules[RULE_COMMAND_3].rhs[0] = SYM_compound_command;
	rules[RULE_COMMAND_3].rhs[1] = SYM_redirect_list;
	rules[RULE_COMMAND_3].rhs_len = 2;
}

// command -> function_definition
static void	rules_build_command_4(t_rule *rules)
{
	rules[RULE_COMMAND_4].lhs = SYM_command;
	rules[RULE_COMMAND_4].rhs[0] = SYM_function_definition;
	rules[RULE_COMMAND_4].rhs_len = 1;
}

```

./2_rules/rules_complete_command.c
```c
#include "parser.h"

static void	rules_build_complete_command_1(t_rule *rules);
static void	rules_build_complete_command_2(t_rule *rules);

/*
complete_command : list separator_op
                 | list
                 ;
*/
void	rules_build_complete_command(t_rule *rules)
{
	rules_build_complete_command_1(rules);
	rules_build_complete_command_2(rules);
}

// complete_command -> list separator_op
static void	rules_build_complete_command_1(t_rule *rules)
{
	rules[RULE_COMPLETE_COMMAND_1].lhs = SYM_complete_command;
	rules[RULE_COMPLETE_COMMAND_1].rhs[0] = SYM_list;
	rules[RULE_COMPLETE_COMMAND_1].rhs[1] = SYM_separator_op;
	rules[RULE_COMPLETE_COMMAND_1].rhs_len = 2;
}

// complete_command -> list
static void	rules_build_complete_command_2(t_rule *rules)
{
	rules[RULE_COMPLETE_COMMAND_2].lhs = SYM_complete_command;
	rules[RULE_COMPLETE_COMMAND_2].rhs[0] = SYM_list;
	rules[RULE_COMPLETE_COMMAND_2].rhs_len = 1;
}

```

./2_rules/rules_complete_commands.c
```c
#include "parser.h"

static void	rules_build_complete_commands_1(t_rule *rules);
static void	rules_build_complete_commands_2(t_rule *rules);

/*
complete_commands: complete_commands newline_list complete_command
                 |                                complete_command
                 ;
*/
void	rules_build_complete_commands(t_rule *rules)
{
	rules_build_complete_commands_1(rules);
	rules_build_complete_commands_2(rules);
}

// complete_commands -> complete_commands newline_list complete_command
static void	rules_build_complete_commands_1(t_rule *rules)
{
	rules[RULE_COMPLETE_COMMANDS_1].lhs = SYM_complete_commands;
	rules[RULE_COMPLETE_COMMANDS_1].rhs[0] = SYM_complete_commands;
	rules[RULE_COMPLETE_COMMANDS_1].rhs[1] = SYM_newline_list;
	rules[RULE_COMPLETE_COMMANDS_1].rhs[2] = SYM_complete_command;
	rules[RULE_COMPLETE_COMMANDS_1].rhs_len = 3;
}

// complete_commands -> complete_command
static void	rules_build_complete_commands_2(t_rule *rules)
{
	rules[RULE_COMPLETE_COMMANDS_2].lhs = SYM_complete_commands;
	rules[RULE_COMPLETE_COMMANDS_2].rhs[0] = SYM_complete_command;
	rules[RULE_COMPLETE_COMMANDS_2].rhs_len = 1;
}

```

./2_rules/rules_compound_command.c
```c
#include "parser.h"

static void	rules_build_compound_command_1(t_rule *rules);
static void	rules_build_compound_command_2(t_rule *rules);
static void	rules_build_compound_command_3(t_rule *rules);
static void	rules_build_compound_command_4(t_rule *rules);

/*
compound_command : brace_group
                 | subshell
                 | for_clause
                 | case_clause
                 | if_clause
                 | while_clause
                 | until_clause
                 ;
*/
void	rules_build_compound_command(t_rule *rules)
{
	rules_build_compound_command_1(rules);
	rules_build_compound_command_2(rules);
	rules_build_compound_command_3(rules);
	rules_build_compound_command_4(rules);
}

// compound_command -> brace_group
static void	rules_build_compound_command_1(t_rule *rules)
{
	rules[RULE_COMPOUND_COMMAND_1].lhs = SYM_compound_command;
	rules[RULE_COMPOUND_COMMAND_1].rhs[0] = SYM_brace_group;
	rules[RULE_COMPOUND_COMMAND_1].rhs_len = 1;
}

// compound_command -> subshell
static void	rules_build_compound_command_2(t_rule *rules)
{
	rules[RULE_COMPOUND_COMMAND_2].lhs = SYM_compound_command;
	rules[RULE_COMPOUND_COMMAND_2].rhs[0] = SYM_subshell;
	rules[RULE_COMPOUND_COMMAND_2].rhs_len = 1;
}

// compound_command -> for_clause
// compound_command -> case_clause
static void	rules_build_compound_command_3(t_rule *rules)
{
	rules[RULE_COMPOUND_COMMAND_3].lhs = SYM_compound_command;
	rules[RULE_COMPOUND_COMMAND_3].rhs[0] = SYM_for_clause;
	rules[RULE_COMPOUND_COMMAND_3].rhs_len = 1;
	rules[RULE_COMPOUND_COMMAND_4].lhs = SYM_compound_command;
	rules[RULE_COMPOUND_COMMAND_4].rhs[0] = SYM_case_clause;
	rules[RULE_COMPOUND_COMMAND_4].rhs_len = 1;
}

// compound_command -> if_clause
// compound_command -> while_clause
// compound_command -> until_clause
static void	rules_build_compound_command_4(t_rule *rules)
{
	rules[RULE_COMPOUND_COMMAND_5].lhs = SYM_compound_command;
	rules[RULE_COMPOUND_COMMAND_5].rhs[0] = SYM_if_clause;
	rules[RULE_COMPOUND_COMMAND_5].rhs_len = 1;
	rules[RULE_COMPOUND_COMMAND_6].lhs = SYM_compound_command;
	rules[RULE_COMPOUND_COMMAND_6].rhs[0] = SYM_while_clause;
	rules[RULE_COMPOUND_COMMAND_6].rhs_len = 1;
	rules[RULE_COMPOUND_COMMAND_7].lhs = SYM_compound_command;
	rules[RULE_COMPOUND_COMMAND_7].rhs[0] = SYM_until_clause;
	rules[RULE_COMPOUND_COMMAND_7].rhs_len = 1;
}

```

./2_rules/rules_compound_list.c
```c
#include "parser.h"

static void	rules_build_compound_list_1(t_rule *rules);
static void	rules_build_compound_list_2(t_rule *rules);

/*
compound_list    : linebreak term
                 | linebreak term separator
                 ;
*/
void	rules_build_compound_list(t_rule *rules)
{
	rules_build_compound_list_1(rules);
	rules_build_compound_list_2(rules);
}

// compound_list -> linebreak term
static void	rules_build_compound_list_1(t_rule *rules)
{
	rules[RULE_COMPOUND_LIST_1].lhs = SYM_compound_list;
	rules[RULE_COMPOUND_LIST_1].rhs[0] = SYM_linebreak;
	rules[RULE_COMPOUND_LIST_1].rhs[1] = SYM_term;
	rules[RULE_COMPOUND_LIST_1].rhs_len = 2;
}

// compound_list -> linebreak term separator
static void	rules_build_compound_list_2(t_rule *rules)
{
	rules[RULE_COMPOUND_LIST_2].lhs = SYM_compound_list;
	rules[RULE_COMPOUND_LIST_2].rhs[0] = SYM_linebreak;
	rules[RULE_COMPOUND_LIST_2].rhs[1] = SYM_term;
	rules[RULE_COMPOUND_LIST_2].rhs[2] = SYM_separator;
	rules[RULE_COMPOUND_LIST_2].rhs_len = 3;
}

```

./2_rules/rules_do_group.c
```c
#include "parser.h"
#include "hooks.h"

/*
do_group         : Do compound_list Done (apply rule 6)
                 ;
*/
void	rules_build_do_group(t_rule *rules)
{
	rules[RULE_DO_GROUP_1].lhs = SYM_do_group;
	rules[RULE_DO_GROUP_1].rhs[0] = SYM_Do;
	rules[RULE_DO_GROUP_1].rhs[1] = SYM_compound_list;
	rules[RULE_DO_GROUP_1].rhs[2] = SYM_Done;
	rules[RULE_DO_GROUP_1].rhs_len = 3;
	rules[RULE_DO_GROUP_1].hook = hook_6;
}

```

./2_rules/rules_else_part.c
```c
#include "parser.h"

static void	rules_build_else_part_1(t_rule *rules);
static void	rules_build_else_part_2(t_rule *rules);
static void	rules_build_else_part_3(t_rule *rules);

/*
else_part        : Elif compound_list Then compound_list
                 | Elif compound_list Then compound_list else_part
                 | Else compound_list
                 ;
*/
void	rules_build_else_part(t_rule *rules)
{
	rules_build_else_part_1(rules);
	rules_build_else_part_2(rules);
	rules_build_else_part_3(rules);
}

// else_part -> Elif compound_list Then compound_list
static void	rules_build_else_part_1(t_rule *rules)
{
	rules[RULE_ELSE_PART_1].lhs = SYM_else_part;
	rules[RULE_ELSE_PART_1].rhs[0] = SYM_Elif;
	rules[RULE_ELSE_PART_1].rhs[1] = SYM_compound_list;
	rules[RULE_ELSE_PART_1].rhs[2] = SYM_Then;
	rules[RULE_ELSE_PART_1].rhs[3] = SYM_compound_list;
	rules[RULE_ELSE_PART_1].rhs_len = 4;
}

// else_part -> Elif compound_list Then compound_list else_part
static void	rules_build_else_part_2(t_rule *rules)
{
	rules[RULE_ELSE_PART_2].lhs = SYM_else_part;
	rules[RULE_ELSE_PART_2].rhs[0] = SYM_Elif;
	rules[RULE_ELSE_PART_2].rhs[1] = SYM_compound_list;
	rules[RULE_ELSE_PART_2].rhs[2] = SYM_Then;
	rules[RULE_ELSE_PART_2].rhs[3] = SYM_compound_list;
	rules[RULE_ELSE_PART_2].rhs[4] = SYM_else_part;
	rules[RULE_ELSE_PART_2].rhs_len = 5;
}

// else_part -> Else compound_list
static void	rules_build_else_part_3(t_rule *rules)
{
	rules[RULE_ELSE_PART_3].lhs = SYM_else_part;
	rules[RULE_ELSE_PART_3].rhs[0] = SYM_Else;
	rules[RULE_ELSE_PART_3].rhs[1] = SYM_compound_list;
	rules[RULE_ELSE_PART_3].rhs_len = 2;
}

```

./2_rules/rules_filename.c
```c
#include "parser.h"
#include "hooks.h"

/*
filename         : WORD (apply rule 2)
                 ;
*/
void	rules_build_filename(t_rule *rules)
{
	rules[RULE_FILENAME_1].lhs = SYM_filename;
	rules[RULE_FILENAME_1].rhs[0] = SYM_WORD;
	rules[RULE_FILENAME_1].rhs_len = 1;
	rules[RULE_FILENAME_1].hook = hook_2;
}

```

./2_rules/rules_fname.c
```c
#include "parser.h"
#include "hooks.h"

/*
fname            : NAME (apply rule 8)
                 ;
*/
void	rules_build_fname(t_rule *rules)
{
	rules[RULE_FNAME_1].lhs = SYM_fname;
	rules[RULE_FNAME_1].rhs[0] = SYM_NAME;
	rules[RULE_FNAME_1].rhs_len = 1;
	rules[RULE_FNAME_1].hook = hook_8;
}

```

./2_rules/rules_for_clause.c
```c
#include "parser.h"

static void	rules_build_for_clause_1(t_rule *rules);
static void	rules_build_for_clause_2(t_rule *rules);
static void	rules_build_for_clause_3(t_rule *rules);
static void	rules_build_for_clause_4(t_rule *rules);

/*
for_clause       : For name                                      do_group
                 | For name                       sequential_sep do_group
                 | For name linebreak in          sequential_sep do_group
                 | For name linebreak in wordlist sequential_sep do_group
                 ;
*/
void	rules_build_for_clause(t_rule *rules)
{
	rules_build_for_clause_1(rules);
	rules_build_for_clause_2(rules);
	rules_build_for_clause_3(rules);
	rules_build_for_clause_4(rules);
}

// for_clause -> For name do_group
static void	rules_build_for_clause_1(t_rule *rules)
{
	rules[RULE_FOR_CLAUSE_1].lhs = SYM_for_clause;
	rules[RULE_FOR_CLAUSE_1].rhs[0] = SYM_For;
	rules[RULE_FOR_CLAUSE_1].rhs[1] = SYM_name;
	rules[RULE_FOR_CLAUSE_1].rhs[2] = SYM_do_group;
	rules[RULE_FOR_CLAUSE_1].rhs_len = 3;
}

// for_clause -> For name sequential_sep do_group
static void	rules_build_for_clause_2(t_rule *rules)
{
	rules[RULE_FOR_CLAUSE_2].lhs = SYM_for_clause;
	rules[RULE_FOR_CLAUSE_2].rhs[0] = SYM_For;
	rules[RULE_FOR_CLAUSE_2].rhs[1] = SYM_name;
	rules[RULE_FOR_CLAUSE_2].rhs[2] = SYM_sequential_sep;
	rules[RULE_FOR_CLAUSE_2].rhs[3] = SYM_do_group;
	rules[RULE_FOR_CLAUSE_2].rhs_len = 4;
}

// for_clause -> For name linebreak in sequential_sep do_group
static void	rules_build_for_clause_3(t_rule *rules)
{
	rules[RULE_FOR_CLAUSE_3].lhs = SYM_for_clause;
	rules[RULE_FOR_CLAUSE_3].rhs[0] = SYM_For;
	rules[RULE_FOR_CLAUSE_3].rhs[1] = SYM_name;
	rules[RULE_FOR_CLAUSE_3].rhs[2] = SYM_linebreak;
	rules[RULE_FOR_CLAUSE_3].rhs[3] = SYM_in;
	rules[RULE_FOR_CLAUSE_3].rhs[4] = SYM_sequential_sep;
	rules[RULE_FOR_CLAUSE_3].rhs[5] = SYM_do_group;
	rules[RULE_FOR_CLAUSE_3].rhs_len = 6;
}

// for_clause -> For name linebreak in wordlist sequential_sep do_group
static void	rules_build_for_clause_4(t_rule *rules)
{
	rules[RULE_FOR_CLAUSE_4].lhs = SYM_for_clause;
	rules[RULE_FOR_CLAUSE_4].rhs[0] = SYM_For;
	rules[RULE_FOR_CLAUSE_4].rhs[1] = SYM_name;
	rules[RULE_FOR_CLAUSE_4].rhs[2] = SYM_linebreak;
	rules[RULE_FOR_CLAUSE_4].rhs[3] = SYM_in;
	rules[RULE_FOR_CLAUSE_4].rhs[4] = SYM_wordlist;
	rules[RULE_FOR_CLAUSE_4].rhs[5] = SYM_sequential_sep;
	rules[RULE_FOR_CLAUSE_4].rhs[6] = SYM_do_group;
	rules[RULE_FOR_CLAUSE_4].rhs_len = 7;
}

```

./2_rules/rules_function_body.c
```c
#include "parser.h"
#include "hooks.h"

static void	rules_build_function_body_1(t_rule *rules);
static void	rules_build_function_body_2(t_rule *rules);

/*
function_body    : compound_command               (apply rule 9)
                 | compound_command redirect_list (apply rule 9)
                 ;
*/
void	rules_build_function_body(t_rule *rules)
{
	rules_build_function_body_1(rules);
	rules_build_function_body_2(rules);
}

// function_body -> compound_command (apply rule 9)
static void	rules_build_function_body_1(t_rule *rules)
{
	rules[RULE_FUNCTION_BODY_1].lhs = SYM_function_body;
	rules[RULE_FUNCTION_BODY_1].rhs[0] = SYM_compound_command;
	rules[RULE_FUNCTION_BODY_1].rhs_len = 1;
	rules[RULE_FUNCTION_BODY_1].hook = hook_9;
}

// function_body -> compound_command redirect_list (apply rule 9)
static void	rules_build_function_body_2(t_rule *rules)
{
	rules[RULE_FUNCTION_BODY_2].lhs = SYM_function_body;
	rules[RULE_FUNCTION_BODY_2].rhs[0] = SYM_compound_command;
	rules[RULE_FUNCTION_BODY_2].rhs[1] = SYM_redirect_list;
	rules[RULE_FUNCTION_BODY_2].rhs_len = 2;
	rules[RULE_FUNCTION_BODY_2].hook = hook_9;
}

```

./2_rules/rules_function_definition.c
```c
#include "parser.h"

/*
function_definition : fname '(' ')' linebreak function_body
                    ;
*/
void	rules_build_function_definition(t_rule *rules)
{
	rules[RULE_FUNCTION_DEFINITION_1].lhs = SYM_function_definition;
	rules[RULE_FUNCTION_DEFINITION_1].rhs[0] = SYM_fname;
	rules[RULE_FUNCTION_DEFINITION_1].rhs[1] = SYM_LPARENTHESIS;
	rules[RULE_FUNCTION_DEFINITION_1].rhs[2] = SYM_RPARENTHESIS;
	rules[RULE_FUNCTION_DEFINITION_1].rhs[3] = SYM_linebreak;
	rules[RULE_FUNCTION_DEFINITION_1].rhs[4] = SYM_function_body;
	rules[RULE_FUNCTION_DEFINITION_1].rhs_len = 5;
}

```

./2_rules/rules_here_end.c
```c
#include "parser.h"
#include "hooks.h"

/*
here_end         : WORD (apply rule 3)
                 ;
*/
void	rules_build_here_end(t_rule *rules)
{
	rules[RULE_HERE_END_1].lhs = SYM_here_end;
	rules[RULE_HERE_END_1].rhs[0] = SYM_WORD;
	rules[RULE_HERE_END_1].rhs_len = 1;
	rules[RULE_HERE_END_1].hook = hook_3;
}

```

./2_rules/rules_if_clause.c
```c
#include "parser.h"

static void	rules_build_if_clause_1(t_rule *rules);
static void	rules_build_if_clause_2(t_rule *rules);

/*
if_clause        : If compound_list Then compound_list else_part Fi
                 | If compound_list Then compound_list           Fi
                 ;
*/
void	rules_build_if_clause(t_rule *rules)
{
	rules_build_if_clause_1(rules);
	rules_build_if_clause_2(rules);
}

// if_clause -> If compound_list Then compound_list else_part Fi
static void	rules_build_if_clause_1(t_rule *rules)
{
	rules[RULE_IF_CLAUSE_1].lhs = SYM_if_clause;
	rules[RULE_IF_CLAUSE_1].rhs[0] = SYM_If;
	rules[RULE_IF_CLAUSE_1].rhs[1] = SYM_compound_list;
	rules[RULE_IF_CLAUSE_1].rhs[2] = SYM_Then;
	rules[RULE_IF_CLAUSE_1].rhs[3] = SYM_compound_list;
	rules[RULE_IF_CLAUSE_1].rhs[4] = SYM_else_part;
	rules[RULE_IF_CLAUSE_1].rhs[5] = SYM_Fi;
	rules[RULE_IF_CLAUSE_1].rhs_len = 6;
}

// if_clause -> If compound_list Then compound_list Fi
static void	rules_build_if_clause_2(t_rule *rules)
{
	rules[RULE_IF_CLAUSE_2].lhs = SYM_if_clause;
	rules[RULE_IF_CLAUSE_2].rhs[0] = SYM_If;
	rules[RULE_IF_CLAUSE_2].rhs[1] = SYM_compound_list;
	rules[RULE_IF_CLAUSE_2].rhs[2] = SYM_Then;
	rules[RULE_IF_CLAUSE_2].rhs[3] = SYM_compound_list;
	rules[RULE_IF_CLAUSE_2].rhs[4] = SYM_Fi;
	rules[RULE_IF_CLAUSE_2].rhs_len = 5;
}

```

./2_rules/rules_in.c
```c
#include "parser.h"
#include "hooks.h"

/*
in               : In (apply rule 6)
                 ;
*/
void	rules_build_in(t_rule *rules)
{
	rules[RULE_IN_1].lhs = SYM_in;
	rules[RULE_IN_1].rhs[0] = SYM_In;
	rules[RULE_IN_1].rhs_len = 1;
	rules[RULE_IN_1].hook = hook_6;
}

```

./2_rules/rules_io_file.c
```c
#include "parser.h"

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

```

./2_rules/rules_io_here.c
```c
#include "parser.h"

static void	rules_build_io_here_1(t_rule *rules);
static void	rules_build_io_here_2(t_rule *rules);

/*
io_here          : DLESS here_end
                 | DLESSDASH here_end
                 ;
*/
void	rules_build_io_here(t_rule *rules)
{
	rules_build_io_here_1(rules);
	rules_build_io_here_2(rules);
}

// io_here -> DLESS here_end
static void	rules_build_io_here_1(t_rule *rules)
{
	rules[RULE_IO_HERE_1].lhs = SYM_io_here;
	rules[RULE_IO_HERE_1].rhs[0] = SYM_DLESS;
	rules[RULE_IO_HERE_1].rhs[1] = SYM_here_end;
	rules[RULE_IO_HERE_1].rhs_len = 2;
}

// io_here -> DLESSDASH here_end
static void	rules_build_io_here_2(t_rule *rules)
{
	rules[RULE_IO_HERE_2].lhs = SYM_io_here;
	rules[RULE_IO_HERE_2].rhs[0] = SYM_DLESSDASH;
	rules[RULE_IO_HERE_2].rhs[1] = SYM_here_end;
	rules[RULE_IO_HERE_2].rhs_len = 2;
}

```

./2_rules/rules_io_redirect.c
```c
#include "parser.h"

static void	rules_build_io_redirect_1(t_rule *rules);
static void	rules_build_io_redirect_2(t_rule *rules);
static void	rules_build_io_redirect_3(t_rule *rules);
static void	rules_build_io_redirect_4(t_rule *rules);

/*
io_redirect      :             io_file
                 | IO_NUMBER   io_file
                 | IO_LOCATION io_file (optionally supported)
                 |             io_here
                 | IO_NUMBER   io_here
                 | IO_LOCATION io_here (optionally supported)
                 ;
*/
void	rules_build_io_redirect(t_rule *rules)
{
	rules_build_io_redirect_1(rules);
	rules_build_io_redirect_2(rules);
	rules_build_io_redirect_3(rules);
	rules_build_io_redirect_4(rules);
}

// io_redirect -> io_file
// io_redirect -> IO_NUMBER io_file
static void	rules_build_io_redirect_1(t_rule *rules)
{
	rules[RULE_IO_REDIRECT_1].lhs = SYM_io_redirect;
	rules[RULE_IO_REDIRECT_1].rhs[0] = SYM_io_file;
	rules[RULE_IO_REDIRECT_1].rhs_len = 1;
	rules[RULE_IO_REDIRECT_2].lhs = SYM_io_redirect;
	rules[RULE_IO_REDIRECT_2].rhs[0] = SYM_IO_NUMBER;
	rules[RULE_IO_REDIRECT_2].rhs[1] = SYM_io_file;
	rules[RULE_IO_REDIRECT_2].rhs_len = 2;
}

// io_redirect -> IO_LOCATION io_file (optionally supported)
// io_redirect -> io_here
static void	rules_build_io_redirect_2(t_rule *rules)
{
	rules[RULE_IO_REDIRECT_3].lhs = SYM_io_redirect;
	rules[RULE_IO_REDIRECT_3].rhs[0] = SYM_IO_LOCATION;
	rules[RULE_IO_REDIRECT_3].rhs[1] = SYM_io_file;
	rules[RULE_IO_REDIRECT_3].rhs_len = 2;
	rules[RULE_IO_REDIRECT_4].lhs = SYM_io_redirect;
	rules[RULE_IO_REDIRECT_4].rhs[0] = SYM_io_here;
	rules[RULE_IO_REDIRECT_4].rhs_len = 1;
}

// io_redirect -> IO_NUMBER io_here
static void	rules_build_io_redirect_3(t_rule *rules)
{
	rules[RULE_IO_REDIRECT_5].lhs = SYM_io_redirect;
	rules[RULE_IO_REDIRECT_5].rhs[0] = SYM_IO_NUMBER;
	rules[RULE_IO_REDIRECT_5].rhs[1] = SYM_io_here;
	rules[RULE_IO_REDIRECT_5].rhs_len = 2;
}

// io_redirect -> IO_LOCATION io_here (optionally supported)
static void	rules_build_io_redirect_4(t_rule *rules)
{
	rules[RULE_IO_REDIRECT_6].lhs = SYM_io_redirect;
	rules[RULE_IO_REDIRECT_6].rhs[0] = SYM_IO_LOCATION;
	rules[RULE_IO_REDIRECT_6].rhs[1] = SYM_io_here;
	rules[RULE_IO_REDIRECT_6].rhs_len = 2;
}

```

./2_rules/rules_linebreak.c
```c
#include "parser.h"

static void	rules_build_linebreak_1(t_rule *rules);
static void	rules_build_linebreak_2(t_rule *rules);

/*
linebreak        : newline_list
                 | <empty>
                 ;
*/
void	rules_build_linebreak(t_rule *rules)
{
	rules_build_linebreak_1(rules);
	rules_build_linebreak_2(rules);
}

// linebreak -> newline_list
static void	rules_build_linebreak_1(t_rule *rules)
{
	rules[RULE_LINEBREAK_1].lhs = SYM_linebreak;
	rules[RULE_LINEBREAK_1].rhs[0] = SYM_newline_list;
	rules[RULE_LINEBREAK_1].rhs_len = 1;
}

// linebreak -> <empty>
static void	rules_build_linebreak_2(t_rule *rules)
{
	rules[RULE_LINEBREAK_2].lhs = SYM_linebreak;
	rules[RULE_LINEBREAK_2].rhs_len = 0;
}

```

./2_rules/rules_list.c
```c
#include "parser.h"

static void	rules_build_list_1(t_rule *rules);
static void	rules_build_list_2(t_rule *rules);

/*
list             : list separator_op and_or
                 |                   and_or
                 ;
*/
void	rules_build_list(t_rule *rules)
{
	rules_build_list_1(rules);
	rules_build_list_2(rules);
}

// list -> list separator_op and_or
static void	rules_build_list_1(t_rule *rules)
{
	rules[RULE_LIST_1].lhs = SYM_list;
	rules[RULE_LIST_1].rhs[0] = SYM_list;
	rules[RULE_LIST_1].rhs[1] = SYM_separator_op;
	rules[RULE_LIST_1].rhs[2] = SYM_and_or;
	rules[RULE_LIST_1].rhs_len = 3;
}

// list -> and_or
static void	rules_build_list_2(t_rule *rules)
{
	rules[RULE_LIST_2].lhs = SYM_list;
	rules[RULE_LIST_2].rhs[0] = SYM_and_or;
	rules[RULE_LIST_2].rhs_len = 1;
}

```

./2_rules/rules_name.c
```c
#include "parser.h"
#include "hooks.h"

/*
name             : NAME (apply rule 5)
                 ;
*/
void	rules_build_name(t_rule *rules)
{
	rules[RULE_NAME_1].lhs = SYM_name;
	rules[RULE_NAME_1].rhs[0] = SYM_NAME;
	rules[RULE_NAME_1].rhs_len = 1;
	rules[RULE_NAME_1].hook = hook_5;
}

```

./2_rules/rules_newline_list.c
```c
#include "parser.h"

static void	rules_build_newline_list_1(t_rule *rules);
static void	rules_build_newline_list_2(t_rule *rules);

/*
newline_list     :              NEWLINE
                 | newline_list NEWLINE
                 ;
*/
void	rules_build_newline_list(t_rule *rules)
{
	rules_build_newline_list_1(rules);
	rules_build_newline_list_2(rules);
}

// newline_list -> NEWLINE
static void	rules_build_newline_list_1(t_rule *rules)
{
	rules[RULE_NEWLINE_LIST_1].lhs = SYM_newline_list;
	rules[RULE_NEWLINE_LIST_1].rhs[0] = SYM_NEWLINE;
	rules[RULE_NEWLINE_LIST_1].rhs_len = 1;
}

// newline_list -> newline_list NEWLINE
static void	rules_build_newline_list_2(t_rule *rules)
{
	rules[RULE_NEWLINE_LIST_2].lhs = SYM_newline_list;
	rules[RULE_NEWLINE_LIST_2].rhs[0] = SYM_newline_list;
	rules[RULE_NEWLINE_LIST_2].rhs[1] = SYM_NEWLINE;
	rules[RULE_NEWLINE_LIST_2].rhs_len = 2;
}

```

./2_rules/rules_pattern_list.c
```c
#include "parser.h"
#include "hooks.h"

static void	rules_build_pattern_list_1(t_rule *rules);
static void	rules_build_pattern_list_2(t_rule *rules);
static void	rules_build_pattern_list_3(t_rule *rules);

/*
pattern_list     :                  WORD (apply rule 4)
                 |              '(' WORD (do NOT apply rule 4)
                 | pattern_list '|' WORD (do NOT apply rule 4)
                 ;
*/
void	rules_build_pattern_list(t_rule *rules)
{
	rules_build_pattern_list_1(rules);
	rules_build_pattern_list_2(rules);
	rules_build_pattern_list_3(rules);
}

// pattern_list -> WORD (apply rule 4)
static void	rules_build_pattern_list_1(t_rule *rules)
{
	rules[RULE_PATTERN_LIST_1].lhs = SYM_pattern_list;
	rules[RULE_PATTERN_LIST_1].rhs[0] = SYM_WORD;
	rules[RULE_PATTERN_LIST_1].rhs_len = 1;
	rules[RULE_PATTERN_LIST_1].hook = hook_4;
}

// pattern_list -> '(' WORD (do NOT apply rule 4)
static void	rules_build_pattern_list_2(t_rule *rules)
{
	rules[RULE_PATTERN_LIST_2].lhs = SYM_pattern_list;
	rules[RULE_PATTERN_LIST_2].rhs[0] = SYM_LPARENTHESIS;
	rules[RULE_PATTERN_LIST_2].rhs[1] = SYM_WORD;
	rules[RULE_PATTERN_LIST_2].rhs_len = 2;
}

// pattern_list -> pattern_list '|' WORD (do NOT apply rule 4)
static void	rules_build_pattern_list_3(t_rule *rules)
{
	rules[RULE_PATTERN_LIST_3].lhs = SYM_pattern_list;
	rules[RULE_PATTERN_LIST_3].rhs[0] = SYM_pattern_list;
	rules[RULE_PATTERN_LIST_3].rhs[1] = SYM_PIPE;
	rules[RULE_PATTERN_LIST_3].rhs[2] = SYM_WORD;
	rules[RULE_PATTERN_LIST_3].rhs_len = 3;
}

```

./2_rules/rules_pipe_sequence.c
```c
#include "parser.h"

static void	rules_build_pipe_sequence_1(t_rule *rules);
static void	rules_build_pipe_sequence_2(t_rule *rules);

/*
pipe_sequence    :                             command
                 | pipe_sequence '|' linebreak command
                 ;
*/
void	rules_build_pipe_sequence(t_rule *rules)
{
	rules_build_pipe_sequence_1(rules);
	rules_build_pipe_sequence_2(rules);
}

// pipe_sequence -> command
static void	rules_build_pipe_sequence_1(t_rule *rules)
{
	rules[RULE_PIPE_SEQUENCE_1].lhs = SYM_pipe_sequence;
	rules[RULE_PIPE_SEQUENCE_1].rhs[0] = SYM_command;
	rules[RULE_PIPE_SEQUENCE_1].rhs_len = 1;
}

// pipe_sequence -> '|' linebreak command
static void	rules_build_pipe_sequence_2(t_rule *rules)
{
	rules[RULE_PIPE_SEQUENCE_2].lhs = SYM_pipe_sequence;
	rules[RULE_PIPE_SEQUENCE_2].rhs[0] = SYM_pipe_sequence;
	rules[RULE_PIPE_SEQUENCE_2].rhs[1] = SYM_PIPE;
	rules[RULE_PIPE_SEQUENCE_2].rhs[2] = SYM_linebreak;
	rules[RULE_PIPE_SEQUENCE_2].rhs[3] = SYM_command;
	rules[RULE_PIPE_SEQUENCE_2].rhs_len = 4;
}

```

./2_rules/rules_pipeline.c
```c
#include "parser.h"

static void	rules_build_pipeline_1(t_rule *rules);
static void	rules_build_pipeline_2(t_rule *rules);

/*
pipeline         :      pipe_sequence
                 | Bang pipe_sequence
                 ;
*/
void	rules_build_pipeline(t_rule *rules)
{
	rules_build_pipeline_1(rules);
	rules_build_pipeline_2(rules);
}

// pipeline -> pipe_sequence
static void	rules_build_pipeline_1(t_rule *rules)
{
	rules[RULE_PIPELINE_1].lhs = SYM_pipeline;
	rules[RULE_PIPELINE_1].rhs[0] = SYM_pipe_sequence;
	rules[RULE_PIPELINE_1].rhs_len = 1;
}

// pipeline -> Bang pipe_sequence
static void	rules_build_pipeline_2(t_rule *rules)
{
	rules[RULE_PIPELINE_2].lhs = SYM_pipeline;
	rules[RULE_PIPELINE_2].rhs[0] = SYM_Bang;
	rules[RULE_PIPELINE_2].rhs[1] = SYM_pipe_sequence;
	rules[RULE_PIPELINE_2].rhs_len = 2;
}

```

./2_rules/rules_program.c
```c
#include "parser.h"

static void	rules_build_program_1(t_rule *rules);
static void	rules_build_program_2(t_rule *rules);

/*
program          : linebreak complete_commands linebreak
                 | linebreak
                 ;
*/
void	rules_build_program(t_rule *rules)
{
	rules_build_program_1(rules);
	rules_build_program_2(rules);
}

// program -> linebreak complete_commands linebreak
static void	rules_build_program_1(t_rule *rules)
{
	rules[RULE_PROGRAM_1].lhs = SYM_program;
	rules[RULE_PROGRAM_1].rhs[0] = SYM_linebreak;
	rules[RULE_PROGRAM_1].rhs[1] = SYM_complete_commands;
	rules[RULE_PROGRAM_1].rhs[2] = SYM_linebreak;
	rules[RULE_PROGRAM_1].rhs_len = 3;
}

// program -> linebreak
static void	rules_build_program_2(t_rule *rules)
{
	rules[RULE_PROGRAM_2].lhs = SYM_program;
	rules[RULE_PROGRAM_2].rhs[0] = SYM_linebreak;
	rules[RULE_PROGRAM_2].rhs_len = 1;
}

```

./2_rules/rules_redirect_list.c
```c
#include "parser.h"

static void	rules_build_redirect_list_1(t_rule *rules);
static void	rules_build_redirect_list_2(t_rule *rules);

/*
redirect_list    :               io_redirect
                 | redirect_list io_redirect
                 ;
*/
void	rules_build_redirect_list(t_rule *rules)
{
	rules_build_redirect_list_1(rules);
	rules_build_redirect_list_2(rules);
}

// redirect_list -> io_redirect
static void	rules_build_redirect_list_1(t_rule *rules)
{
	rules[RULE_REDIRECT_LIST_1].lhs = SYM_redirect_list;
	rules[RULE_REDIRECT_LIST_1].rhs[0] = SYM_io_redirect;
	rules[RULE_REDIRECT_LIST_1].rhs_len = 1;
}

// redirect_list -> redirect_list io_redirect
static void	rules_build_redirect_list_2(t_rule *rules)
{
	rules[RULE_REDIRECT_LIST_2].lhs = SYM_redirect_list;
	rules[RULE_REDIRECT_LIST_2].rhs[0] = SYM_redirect_list;
	rules[RULE_REDIRECT_LIST_2].rhs[1] = SYM_io_redirect;
	rules[RULE_REDIRECT_LIST_2].rhs_len = 2;
}

```

./2_rules/rules_separator_op.c
```c
#include "parser.h"

static void	rules_build_separator_op_1(t_rule *rules);
static void	rules_build_separator_op_2(t_rule *rules);

/*
separator_op     : '&'
                 | ';'
                 ;
*/
void	rules_build_separator_op(t_rule *rules)
{
	rules_build_separator_op_1(rules);
	rules_build_separator_op_2(rules);
}

// separator_op -> '&'
static void	rules_build_separator_op_1(t_rule *rules)
{
	rules[RULE_SEPARATOR_OP_1].lhs = SYM_separator_op;
	rules[RULE_SEPARATOR_OP_1].rhs[0] = SYM_AMPERSAND;
	rules[RULE_SEPARATOR_OP_1].rhs_len = 1;
}

// separator_op -> ';'
static void	rules_build_separator_op_2(t_rule *rules)
{
	rules[RULE_SEPARATOR_OP_2].lhs = SYM_separator_op;
	rules[RULE_SEPARATOR_OP_2].rhs[0] = SYM_SEMI;
	rules[RULE_SEPARATOR_OP_2].rhs_len = 1;
}

```

./2_rules/rules_separator.c
```c
#include "parser.h"

static void	rules_build_separator_1(t_rule *rules);
static void	rules_build_separator_2(t_rule *rules);

/*
separator        : separator_op linebreak
                 | newline_list
                 ;
*/
void	rules_build_separator(t_rule *rules)
{
	rules_build_separator_1(rules);
	rules_build_separator_2(rules);
}

// separator -> separator_op linebreak
static void	rules_build_separator_1(t_rule *rules)
{
	rules[RULE_SEPARATOR_1].lhs = SYM_separator;
	rules[RULE_SEPARATOR_1].rhs[0] = SYM_separator_op;
	rules[RULE_SEPARATOR_1].rhs[1] = SYM_linebreak;
	rules[RULE_SEPARATOR_1].rhs_len = 2;
}

// separator -> newline_list
static void	rules_build_separator_2(t_rule *rules)
{
	rules[RULE_SEPARATOR_2].lhs = SYM_separator;
	rules[RULE_SEPARATOR_2].rhs[0] = SYM_newline_list;
	rules[RULE_SEPARATOR_2].rhs_len = 1;
}

```

./2_rules/rules_sequential_sep.c
```c
#include "parser.h"

static void	rules_build_sequential_sep_1(t_rule *rules);
static void	rules_build_sequential_sep_2(t_rule *rules);

/*
sequential_sep   : ';' linebreak
                 | newline_list
                 ;
*/
void	rules_build_sequential_sep(t_rule *rules)
{
	rules_build_sequential_sep_1(rules);
	rules_build_sequential_sep_2(rules);
}

// sequential_sep -> ';' linebreak
static void	rules_build_sequential_sep_1(t_rule *rules)
{
	rules[RULE_SEQUENTIAL_SEP_1].lhs = SYM_sequential_sep;
	rules[RULE_SEQUENTIAL_SEP_1].rhs[0] = SYM_SEMI;
	rules[RULE_SEQUENTIAL_SEP_1].rhs[1] = SYM_linebreak;
	rules[RULE_SEQUENTIAL_SEP_1].rhs_len = 2;
}

// sequential_sep -> newline_list
static void	rules_build_sequential_sep_2(t_rule *rules)
{
	rules[RULE_SEQUENTIAL_SEP_2].lhs = SYM_sequential_sep;
	rules[RULE_SEQUENTIAL_SEP_2].rhs[0] = SYM_newline_list;
	rules[RULE_SEQUENTIAL_SEP_2].rhs_len = 1;
}

```

./2_rules/rules_simple_command.c
```c
#include "parser.h"

static void	rules_build_simple_command_1(t_rule *rules);
static void	rules_build_simple_command_2(t_rule *rules);
static void	rules_build_simple_command_3(t_rule *rules);
static void	rules_build_simple_command_4(t_rule *rules);

/*
simple_command   : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
                 ;
*/
void	rules_build_simple_command(t_rule *rules)
{
	rules_build_simple_command_1(rules);
	rules_build_simple_command_2(rules);
	rules_build_simple_command_3(rules);
	rules_build_simple_command_4(rules);
}

// simple_command -> cmd_prefix cmd_word cmd_suffix
static void	rules_build_simple_command_1(t_rule *rules)
{
	rules[RULE_SIMPLE_COMMAND_1].lhs = SYM_simple_command;
	rules[RULE_SIMPLE_COMMAND_1].rhs[0] = SYM_cmd_prefix;
	rules[RULE_SIMPLE_COMMAND_1].rhs[1] = SYM_cmd_word;
	rules[RULE_SIMPLE_COMMAND_1].rhs[2] = SYM_cmd_suffix;
	rules[RULE_SIMPLE_COMMAND_1].rhs_len = 3;
}

// simple_command -> cmd_prefix cmd_word
static void	rules_build_simple_command_2(t_rule *rules)
{
	rules[RULE_SIMPLE_COMMAND_2].lhs = SYM_simple_command;
	rules[RULE_SIMPLE_COMMAND_2].rhs[0] = SYM_cmd_prefix;
	rules[RULE_SIMPLE_COMMAND_2].rhs[1] = SYM_cmd_word;
	rules[RULE_SIMPLE_COMMAND_2].rhs_len = 2;
}

// simple_command -> cmd_prefix
// simple_command -> cmd_name cmd_suffix
static void	rules_build_simple_command_3(t_rule *rules)
{
	rules[RULE_SIMPLE_COMMAND_3].lhs = SYM_simple_command;
	rules[RULE_SIMPLE_COMMAND_3].rhs[0] = SYM_cmd_prefix;
	rules[RULE_SIMPLE_COMMAND_3].rhs_len = 1;
	rules[RULE_SIMPLE_COMMAND_4].lhs = SYM_simple_command;
	rules[RULE_SIMPLE_COMMAND_4].rhs[0] = SYM_cmd_name;
	rules[RULE_SIMPLE_COMMAND_4].rhs[1] = SYM_cmd_suffix;
	rules[RULE_SIMPLE_COMMAND_4].rhs_len = 2;
}

// simple_command -> cmd_name
static void	rules_build_simple_command_4(t_rule *rules)
{
	rules[RULE_SIMPLE_COMMAND_5].lhs = SYM_simple_command;
	rules[RULE_SIMPLE_COMMAND_5].rhs[0] = SYM_cmd_name;
	rules[RULE_SIMPLE_COMMAND_5].rhs_len = 1;
}

```

./2_rules/rules_start.c
```c
#include "parser.h"

/*
start            : program
                 ;
*/
void	rules_build_start(t_rule *rules)
{
	rules[RULE_START_1].lhs = SYM_start;
	rules[RULE_START_1].rhs[0] = SYM_program;
	rules[RULE_START_1].rhs_len = 1;
}

```

./2_rules/rules_subshell.c
```c
#include "parser.h"

/*
subshell         : '(' compound_list ')'
                 ;
*/
void	rules_build_subshell(t_rule *rules)
{
	rules[RULE_SUBSHELL_1].lhs = SYM_subshell;
	rules[RULE_SUBSHELL_1].rhs[0] = SYM_LPARENTHESIS;
	rules[RULE_SUBSHELL_1].rhs[1] = SYM_compound_list;
	rules[RULE_SUBSHELL_1].rhs[2] = SYM_RPARENTHESIS;
	rules[RULE_SUBSHELL_1].rhs_len = 3;
}

```

./2_rules/rules_term.c
```c
#include "parser.h"

static void	rules_build_term_1(t_rule *rules);
static void	rules_build_term_2(t_rule *rules);

/*
term             : term separator and_or
                 |                and_or
                 ;
*/
void	rules_build_term(t_rule *rules)
{
	rules_build_term_1(rules);
	rules_build_term_2(rules);
}

// term -> term separator and_or
static void	rules_build_term_1(t_rule *rules)
{
	rules[RULE_TERM_1].lhs = SYM_term;
	rules[RULE_TERM_1].rhs[0] = SYM_term;
	rules[RULE_TERM_1].rhs[1] = SYM_separator;
	rules[RULE_TERM_1].rhs[2] = SYM_and_or;
	rules[RULE_TERM_1].rhs_len = 3;
}

// term -> and_or
static void	rules_build_term_2(t_rule *rules)
{
	rules[RULE_TERM_2].lhs = SYM_term;
	rules[RULE_TERM_2].rhs[0] = SYM_and_or;
	rules[RULE_TERM_2].rhs_len = 1;
}

```

./2_rules/rules_until_clause.c
```c
#include "parser.h"

/*
until_clause     : Until compound_list do_group
                 ;
*/
void	rules_build_until_clause(t_rule *rules)
{
	rules[RULE_UNTIL_CLAUSE_1].lhs = SYM_until_clause;
	rules[RULE_UNTIL_CLAUSE_1].rhs[0] = SYM_Until;
	rules[RULE_UNTIL_CLAUSE_1].rhs[1] = SYM_compound_list;
	rules[RULE_UNTIL_CLAUSE_1].rhs[2] = SYM_do_group;
	rules[RULE_UNTIL_CLAUSE_1].rhs_len = 3;
}

```

./2_rules/rules_while_clause.c
```c
#include "parser.h"

/*
while_clause     : While compound_list do_group
                 ;
*/
void	rules_build_while_clause(t_rule *rules)
{
	rules[RULE_WHILE_CLAUSE_1].lhs = SYM_while_clause;
	rules[RULE_WHILE_CLAUSE_1].rhs[0] = SYM_While;
	rules[RULE_WHILE_CLAUSE_1].rhs[1] = SYM_compound_list;
	rules[RULE_WHILE_CLAUSE_1].rhs[2] = SYM_do_group;
	rules[RULE_WHILE_CLAUSE_1].rhs_len = 3;
}

```

./2_rules/rules_wordlist.c
```c
#include "parser.h"

static void	rules_build_wordlist_1(t_rule *rules);
static void	rules_build_wordlist_2(t_rule *rules);

/*
wordlist         : wordlist WORD
                 |          WORD
                 ;
*/
void	rules_build_wordlist(t_rule *rules)
{
	rules_build_wordlist_1(rules);
	rules_build_wordlist_2(rules);
}

// wordlist -> wordlist WORD
static void	rules_build_wordlist_1(t_rule *rules)
{
	rules[RULE_WORDLIST_1].lhs = SYM_wordlist;
	rules[RULE_WORDLIST_1].rhs[0] = SYM_wordlist;
	rules[RULE_WORDLIST_1].rhs[1] = SYM_WORD;
	rules[RULE_WORDLIST_1].rhs_len = 2;
}

// wordlist -> WORD
static void	rules_build_wordlist_2(t_rule *rules)
{
	rules[RULE_WORDLIST_2].lhs = SYM_wordlist;
	rules[RULE_WORDLIST_2].rhs[0] = SYM_WORD;
	rules[RULE_WORDLIST_2].rhs_len = 1;
}

```

./3_rule_state/rule_state.c
```c
#include "parser.h"

bool	rule_state_equal(t_rule_state a, t_rule_state b)
{
	return (a.rule_id == b.rule_id && a.pos == b.pos);
}

bool	rule_state_is_complete(t_rule *rules, t_rule_state rule_state)
{
	return (rule_state.pos >= rules[rule_state.rule_id].rhs_len);
}

t_symbol	rule_state_next_symbol(t_rule *rules, t_rule_state rule_state)
{
	if (rule_state_is_complete(rules, rule_state))
		return (SYM_error);
	return (rules[rule_state.rule_id].rhs[rule_state.pos]);
}

```

./3_rule_state/rule_state.h
```c
#ifndef RULE_STATE_H
# define RULE_STATE_H

# include "parser.h"

bool		rule_state_equal(t_rule_state a, t_rule_state b);
bool		rule_state_is_complete(t_rule *rules, t_rule_state rule_state);
t_symbol	rule_state_next_symbol(t_rule *rules, t_rule_state rule_state);

#endif

```

./4_lr_state/1_life_cycle.c
```c
#include "lr_state.h"
#include <stdlib.h>

void	lr_state_init(t_lr_state *lr_state)
{
	vector_init(lr_state, sizeof(t_rule_state), 0);
}

void	lr_state_table_init(t_lr_state *lr_states)
{
	vector_init(lr_states, sizeof(t_lr_state), 0);
}

void	lr_state_free(t_lr_state *lr_state)
{
	vector_free(lr_state);
}

void	lr_state_table_free(t_lr_state *lr_states)
{
	size_t	i;

	i = 0;
	while (i < lr_states->len)
	{
		lr_state_free(&((t_lr_state *)lr_states->data)[i]);
		i++;
	}
	vector_free(lr_states);
}

```

./4_lr_state/2_helpers.c
```c
#include "lr_state.h"
#include "rule_state.h"

static bool	lr_state_contains_rule_state(t_lr_state *lr_state, t_rule_state rule_state)
{
	size_t			i;
	t_rule_state	*items;

	i = 0;
	items = (t_rule_state *)lr_state->data;
	while (i < lr_state->len)
	{
		if (rule_state_equal(items[i], rule_state))
			return (true);
		i++;
	}
	return (false);
}

bool	lr_state_equal(t_lr_state *a, t_lr_state *b)
{
	size_t			i;
	t_rule_state	*items;

	if (a->len != b->len)
		return (false);
	items = (t_rule_state *)a->data;
	i = 0;
	while (i < a->len)
	{
		if (!lr_state_contains_rule_state(b, items[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	lr_state_add_rule_state(t_lr_state *lr_state, t_rule_state rule_state, bool *did_add)
{
	if (lr_state_contains_rule_state(lr_state, rule_state))
		return (true);
	if (!vector_push(lr_state, &rule_state))
		return (false);
	if (did_add)
		*did_add = true;
	return (true);
}

bool	lr_state_find_id(t_vector *lr_states, t_lr_state *lr_state, size_t *id)
{
	size_t		i;
	t_lr_state	*current_lr_state;

	i = 0;
	while (i < lr_states->len)
	{
		current_lr_state = &((t_lr_state *)lr_states->data)[i];
		if (lr_state_equal(current_lr_state, lr_state))
		{
			if (id)
				*id = i;
			return (true);
		}
		i++;
	}
	return (false);
}

bool	lr_state_add(t_vector *lr_states, t_lr_state *lr_state, bool *did_add)
{
	if (lr_state_find_id(lr_states, lr_state, NULL))
		return (true);
	if (!vector_push(lr_states, lr_state))
		return (false);
	if (did_add)
		*did_add = true;
	return (true);
}

```

./4_lr_state/3_core.c
```c
#include "lr_state.h"
#include "rule_state.h"

static bool	symbol_is_non_terminal(t_symbol symbol)
{
	return (symbol >= SYM_NON_TERMINAL_MIN && symbol < SYM_NON_TERMINAL_MAX);
}

static bool	add_rules(t_rule *rules, t_lr_state *lr_state, t_symbol symbol, bool *did_add)
{
	size_t			i;
	t_rule			rule;
	t_rule_state	rule_state;

	i = 0;
	while (i < RULE_COUNT)
	{
		rule = rules[i];
		if (rule.lhs == symbol)
		{
			rule_state.rule_id = i;
			rule_state.pos = 0;
			if (!lr_state_add_rule_state(lr_state, rule_state, did_add))
				return (false);
		}
		i++;
	}
	return (true);
}

bool	lr_state_complete(t_rule *rules, t_lr_state *lr_state)
{
	t_rule_state	rule_state;
	t_symbol		next_symbol;
	bool			did_add;
	size_t			i;

	did_add = true;
	while (did_add)
	{
		did_add = false;
		i = 0;
		while (i < lr_state->len)
		{
			rule_state = ((t_rule_state *)lr_state->data)[i];
			next_symbol = rule_state_next_symbol(rules, rule_state);
			if (symbol_is_non_terminal(next_symbol))
				if (!add_rules(rules, lr_state, next_symbol, &did_add))
					return (false);
			i++;
		}
	}
	return (true);
}

bool	lr_state_next(t_rule *rules, t_lr_state *dst, t_lr_state *src, t_symbol symbol)
{
	size_t			i;
	t_rule_state	rule_state;
	t_symbol		next_symbol;

	lr_state_init(dst);
	i = 0;
	while (i < src->len)
	{
		rule_state = ((t_rule_state *)src->data)[i];
		next_symbol = rule_state_next_symbol(rules, rule_state);
		if (next_symbol == symbol)
		{
			rule_state.pos++;
			if (!lr_state_add_rule_state(dst, rule_state, NULL))
				return (lr_state_free(dst), false);
		}
		i++;
	}
	if (dst->len > 0)
		if (!lr_state_complete(rules, dst))
			return (lr_state_free(dst), false);
	return (true);
}

```

./4_lr_state/lr_state.h
```c
#ifndef LR_STATE_H
# define LR_STATE_H

# include "parser.h"

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	lr_state_init(t_lr_state *lr_state);
void	lr_state_table_init(t_lr_state *lr_states);
void	lr_state_free(t_lr_state *lr_state);
void	lr_state_table_free(t_lr_state *lr_states);

/* ************************************************************************* */
/*                                  HELPERS                                  */
/* ************************************************************************* */

bool	lr_state_equal(t_lr_state *a, t_lr_state *b);
// did_add can be NULL, if not, it must already be initialized by caller
bool	lr_state_add_rule_state(t_lr_state *lr_state, t_rule_state rule_state, bool *did_add);
bool	lr_state_find_id(t_vector *lr_states, t_lr_state *lr_state, size_t *id);
bool	lr_state_add(t_vector *lr_states, t_lr_state *lr_state, bool *did_add);

/* ************************************************************************* */
/*                                    CORE                                   */
/* ************************************************************************* */

// Completes an lr_state by adding all implied rule_states (aka closure() in LR parsing theory)
bool	lr_state_complete(t_rule *rules, t_lr_state *lr_state);
// Computes the next lr_state reached from `src` by consuming `symbol` (aka goto_set() in LR parsing theory)
bool	lr_state_next(t_rule *rules, t_lr_state *dst, t_lr_state *src, t_symbol symbol);

#endif

```

./5_transition/1_life_cycle.c
```c
#include "parser.h"

void	transition_init(t_vector *transitions)
{
	vector_init(transitions, sizeof(t_transition), 0);
}

void	transition_free(t_vector *transitions)
{
	vector_free(transitions);
}

```

./5_transition/2_core.c
```c
#include "lr_state.h"

static bool	build_initial_lr_state(t_rule *rules, t_lr_state *lr_states)
{
	t_rule_state	rule_state;
	t_lr_state		lr_state;

	lr_state_init(&lr_state);
	rule_state.rule_id = RULE_START_1;
	rule_state.pos = 0;
	if (!lr_state_add_rule_state(&lr_state, rule_state, NULL))
		return (lr_state_free(&lr_state), false);
	if (!lr_state_complete(rules, &lr_state))
		return (lr_state_free(&lr_state), false);
	if (!lr_state_add(lr_states, &lr_state, NULL))
		return (lr_state_free(&lr_state), false);
	return (true);
}

static bool	add_transition(t_lr_machine *machine, t_lr_state *from_lr_state, t_symbol symbol, t_lr_state *to_lr_state)
{
	t_transition	transition;
	size_t			from_id;
	size_t			to_id;

	if (!lr_state_find_id(&machine->lr_states, from_lr_state, &from_id))
		return (false);
	if (!lr_state_find_id(&machine->lr_states, to_lr_state, &to_id))
		return (false);
	transition.from_lr_state_id = from_id;
	transition.symbol = symbol;
	transition.to_lr_state_id = to_id;
	return (vector_push(&machine->transitions, &transition));
}

static bool	build_lr_state_and_transition(t_lr_machine *machine, t_lr_state *lr_state_from, t_symbol symbol)
{
	t_lr_state	lr_state_new;
	bool		did_add;

	if (!lr_state_next(machine->rules, &lr_state_new, lr_state_from, symbol))
		return (false);
	if (lr_state_new.len > 0)
	{
		did_add = false;
		if (!lr_state_add(&machine->lr_states, &lr_state_new, &did_add))
			return (lr_state_free(&lr_state_new), false);
		if (!add_transition(machine, lr_state_from, symbol, &lr_state_new))
		{
			if (!did_add)
				lr_state_free(&lr_state_new);
			return (false);
		}
		if (!did_add)
			lr_state_free(&lr_state_new);
	}
	return (true);
}

bool	transition_build_table(t_lr_machine *machine)
{
	size_t		i;
	t_symbol	symbol;
	t_lr_state	lr_state;

	if (!build_initial_lr_state(machine->rules, &machine->lr_states))
		return (false);
	i = 0;
	while (i < machine->lr_states.len)
	{
		lr_state = ((t_lr_state *)machine->lr_states.data)[i];
		symbol = 0;
		while (symbol < SYM_COUNT)
		{
			if (!build_lr_state_and_transition(machine, &lr_state, symbol))
				return (false);
			symbol++;
		}
		i++;
	}
	return (true);
}

```

./5_transition/transition.h
```c
#ifndef TRANSITION_H
# define TRANSITION_H

# include "parser.h"

void	transition_init(t_vector *transitions);
bool	transition_build_table(t_lr_machine *machine);
void	transition_free(t_vector *transitions);

#endif

```

./6_action/1_life_cycle.c
```c
#include "parser.h"
#include <stdlib.h>

void	action_init(t_action ***actions)
{
	*actions = NULL;
}

void	action_free(size_t lr_states_count, size_t ***actions)
{
	size_t	i;

	i = 0;
	while (i < lr_states_count)
	{
		free((*actions)[i]);
		i++;
	}
	free(*actions);
	*actions = NULL;
}

```

./6_action/2_default.c
```c
#include "parser.h"
#include "action.h"
#include <stdlib.h>

static bool	malloc_action_table(t_lr_machine *machine)
{
	size_t	rows;
	size_t	cols;
	size_t	i;
	size_t	j;

	rows = machine->lr_states.len;
	cols = SYM_TERMINAL_MAX + 1;
	machine->actions = malloc(rows * sizeof(*machine->actions));
	if (!machine->actions)
		return (false);
	i = 0;
	while (i < rows)
	{
		machine->actions[i] = malloc(cols * sizeof(**machine->actions));
		if (!machine->actions[i])
		{
			j = 0;
			while (j < i)
				free(machine->actions[j++]);
			free(machine->actions);
			return (machine->actions = NULL, false);
		}
		i++;
	}
	return (true);
}

static void	action_set_error(t_lr_machine *machine)
{
	size_t		row;
	size_t		col;
	size_t		col_count;
	t_action	action;

	action.type = ACTION_ERROR;
	action.payload = ACTION_PAYLOAD_EMPTY;
	col_count = SYM_TERMINAL_MAX + 1;
	row = 0;
	while (row < machine->lr_states.len)
	{
		col = 0;
		while (col < col_count)
		{
			machine->actions[row][col] = action;
			col++;
		}
		row++;
	}
}

bool	action_build_default_table(t_lr_machine *machine)
{
	if (!malloc_action_table(machine))
		return (false);
	action_set_error(machine);
	return (true);
}

```

./6_action/3_core.c
```c
#include "parser.h"
#include "action_priv.h"

static bool	print_conflict(t_action *action, size_t lr_state_id, t_symbol symbol, t_action_type target_type, size_t target_payload)
{
	if (action->type == ACTION_SHIFT)
		print_err(false, "SHIFT-");
	else if (action->type == ACTION_REDUCE)
		print_err(false, "REDUCE-");
	else if (action->type == ACTION_ACCEPT)
		print_err(false, "ACCEPT-");
	if (target_type == ACTION_SHIFT)
		print_err(false, "SHIFT ");
	else if (target_type == ACTION_REDUCE)
		print_err(false, "REDUCE ");
	else if (target_type == ACTION_ACCEPT)
		print_err(false, "ACCEPT ");
	fprint_err(false, "conflict",
		" for lr_state %i and symbol %i (current payload = %i vs target = %i)",
		(int)lr_state_id, (int)symbol,
		(int)action->payload, (int)target_payload);
	return (false);
}

static bool	add_shifts(t_lr_machine *machine)
{
	size_t			i;
	t_transition	transition;
	size_t			lr_state_id;
	t_symbol		symbol;
	t_action		*action;

	i = 0;
	while (i < machine->transitions.len)
	{
		transition = ((t_transition *)machine->transitions.data)[i];
		lr_state_id = transition.from_lr_state_id;
		symbol = transition.symbol;
		if (symbol <= SYM_TERMINAL_MAX)
		{
			action = &machine->actions[lr_state_id][symbol];
			if (action->type != ACTION_ERROR)
				return (print_conflict(action, lr_state_id, symbol,
					ACTION_SHIFT, transition.to_lr_state_id));
			action->type = ACTION_SHIFT;
			action->payload = transition.to_lr_state_id;
		}
		i++;
	}
	return (true);
}

static bool	add_reduces_to_all_sym(t_lr_machine *machine, size_t lr_state_id, size_t rule_id)
{
	t_symbol	symbol;
	t_action	*action;

	symbol = 0;
	while (symbol <= SYM_TERMINAL_MAX)
	{
		action = &machine->actions[lr_state_id][symbol];
		if (action->type != ACTION_ERROR)
			return (print_conflict(action, lr_state_id, symbol, ACTION_REDUCE, rule_id));
		action->type = ACTION_REDUCE;
		action->payload = rule_id;
		symbol++;
	}
	return (true);
}

static bool	add_reduces_and_accept(t_lr_machine *machine, size_t lr_state_id, t_rule_state rule_state)
{
	t_rule		rule;
	t_action	*action;

	rule = machine->rules[rule_state.rule_id];
	if (rule_state.pos < rule.rhs_len)
		return (true);
	if (rule_state.rule_id == RULE_START_1)
	{
		action = &machine->actions[lr_state_id][SYM_EOF];
		if (action->type != ACTION_ERROR)
			return (print_conflict(action, lr_state_id, SYM_EOF, ACTION_ACCEPT, rule_state.rule_id));
		action->type = ACTION_ACCEPT;
		action->payload = rule_state.rule_id;
		return (true);
	}
	return (add_reduces_to_all_sym(machine, lr_state_id, rule_state.rule_id));
}

bool	action_build_table(t_lr_machine *machine)
{
	size_t			lr_state_id;
	t_lr_state		lr_state;
	size_t			rule_state_id;
	t_rule_state	rule_state;

	if (!action_build_default_table(machine))
		return (false);
	if (!add_shifts(machine))
		return (false);
	lr_state_id = 0;
	while (lr_state_id < machine->lr_states.len)
	{
		lr_state = ((t_lr_state *)machine->lr_states.data)[lr_state_id];
		rule_state_id = 0;
		while (rule_state_id < lr_state.len)
		{
			rule_state = ((t_rule_state *)lr_state.data)[rule_state_id];
			if (!add_reduces_and_accept(machine, lr_state_id, rule_state))
				return (false);
			rule_state_id++;
		}
		lr_state_id++;
	}
	return (true);
}

```

./6_action/action_priv.h
```c
#ifndef ACTION_PRIV_H
# define ACTION_PRIV_H

# include "parser.h"

bool	action_build_default_table(t_lr_machine *machine);

# endif

```

./6_action/action.h
```c
#ifndef ACTION_H
# define ACTION_H

# include "parser.h"
# include "limits.h"

# define ACTION_PAYLOAD_EMPTY	SIZE_T_MAX

void	action_init(t_action ***actions);
bool	action_build_table(t_lr_machine *machine);
void	action_free(size_t lr_states_count, t_action ***actions);

#endif

```

./7_goto/1_life_cycle.c
```c
#include <stdlib.h>

void	goto_init(size_t ***gotos)
{
	*gotos = NULL;
}

void	goto_free(size_t lr_states_count, size_t ***gotos)
{
	size_t	i;

	i = 0;
	while (i < lr_states_count)
	{
		free((*gotos)[i]);
		i++;
	}
	free(*gotos);
	*gotos = NULL;
}

```

./7_goto/2_core.c
```c
#include "parser.h"
#include "goto.h"
#include <stdlib.h>

static bool	malloc_goto_table(t_lr_machine *machine)
{
	size_t	rows;
	size_t	cols;
	size_t	i;
	size_t	j;

	rows = machine->lr_states.len;
	cols = SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1;
	machine->gotos = malloc(rows * sizeof(*machine->gotos));
	if (!machine->gotos)
		return (false);
	i = 0;
	while (i < rows)
	{
		machine->gotos[i] = malloc(cols * sizeof(**machine->gotos));
		if (!machine->gotos[i])
		{
			j = 0;
			while (j < i)
				free(machine->gotos[j++]);
			free(machine->gotos);
			return (machine->gotos = NULL, false);
		}
		i++;
	}
	return (true);
}

static void	goto_set_empty(t_lr_machine *machine)
{
	size_t	row;
	size_t	col;
	size_t	col_count;

	col_count = SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1;
	row = 0;
	while (row < machine->lr_states.len)
	{
		col = 0;
		while (col < col_count)
		{
			machine->gotos[row][col] = GOTO_EMPTY;
			col++;
		}
		row++;
	}
}

bool	goto_build_table(t_lr_machine *machine)
{
	size_t			i;
	t_transition	transition;
	t_symbol		symbol;
	size_t			row;
	size_t			col;

	if (!malloc_goto_table(machine))
		return (false);
	goto_set_empty(machine);
	i = 0;
	while (i < machine->transitions.len)
	{
		transition = ((t_transition *)machine->transitions.data)[i];
		symbol = transition.symbol;
		if (symbol >= SYM_NON_TERMINAL_MIN && symbol <= SYM_NON_TERMINAL_MAX)
		{
			row = transition.from_lr_state_id;
			col = symbol - SYM_NON_TERMINAL_MIN;
			machine->gotos[row][col] = transition.to_lr_state_id;
		}
		i++;
	}
	return (true);
}

bool	go_to(size_t **gotos, size_t current_lr_state_id, t_symbol symbol, size_t *new_lr_state_id)
{
	size_t	symbol_offset;
	size_t	tmp_lr_state_id;

	if (symbol < SYM_NON_TERMINAL_MIN || symbol > SYM_NON_TERMINAL_MAX)
		return (false);
	symbol_offset = symbol - SYM_NON_TERMINAL_MIN;
	tmp_lr_state_id = gotos[current_lr_state_id][symbol_offset];
	if (tmp_lr_state_id == GOTO_EMPTY)
		return (false);
	*new_lr_state_id = tmp_lr_state_id;
	return (true);
}

```

./7_goto/goto.h
```c
#ifndef GOTO_H
# define GOTO_H

# include "parser.h"
# include <limits.h>

# define GOTO_EMPTY	SIZE_T_MAX

void	goto_init(size_t ***gotos);
bool	goto_build_table(t_lr_machine *machine);
bool	go_to(size_t **gotos, size_t current_lr_state_id, t_symbol symbol, size_t *new_lr_state_id);
void	goto_free(size_t lr_states_count, size_t ***gotos);

#endif

```

./lr_machine.c
```c
#include "parser.h"
#include "rules__pub.h"
#include "lr_state.h"
#include "transition.h"
#include "action.h"
#include "goto.h"
#include <stdlib.h>

void	lr_machine_init(t_lr_machine *machine)
{
	rules_init(machine->rules);
	lr_state_table_init(&machine->lr_states);
	transition_init(&machine->transitions);
	action_init(&machine->actions);
	goto_init(&machine->gotos);
}

bool	lr_machine_build(t_lr_machine *machine)
{
	rules_build(machine->rules);
	if (!transition_build_table(machine))
		return (false);
	if (!action_build_table(machine))
		return (false);
	if (!goto_build_table(machine))
		return (false);
	return (true);
}

void	lr_machine_free(t_lr_machine *machine)
{
	transition_free(&machine->transitions);
	action_free(machine->lr_states.len, &machine->actions);
	goto_free(machine->lr_states.len, &machine->gotos);
	lr_state_table_free(&machine->lr_states);
}

```

./lr_machine.h
```c
#ifndef LR_MACHINE_H
# define LR_MACHINE_H

# include "parser.h"

void	lr_machine_init(t_lr_machine *machine);
bool	lr_machine_build(t_lr_machine *machine);
void	lr_machine_free(t_lr_machine *machine);

#endif

```

