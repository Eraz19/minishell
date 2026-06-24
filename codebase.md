tree
```bash
minishell
├── en.subject.pdf
├── includes
│   ├── alias.h
│   ├── asm_stubs.h
│   ├── builder.h
│   ├── builtins.h
│   ├── context.h
│   ├── debug.h
│   ├── error.h
│   ├── expander.h
│   ├── ft_getopt.h
│   ├── heredoc.h
│   ├── history.h
│   ├── params.h
│   ├── posix_helpers.h
│   ├── runner.h
│   ├── scanner.h
│   ├── shell.h
│   ├── token.h
│   ├── types.h
│   └── utils.h
├── libft
│   ├── docs
│   │   └── Doxyfile
│   ├── en.subject.pdf
│   ├── libft.a
│   ├── libft.h
│   ├── Makefile
│   ├── README.md
│   ├── src
│   │   ├── btree
│   │   │   ├── btree_free.c
│   │   │   └── btree.c
│   │   ├── buff
│   │   │   ├── buff_cmp.c
│   │   │   ├── buff_format.c
│   │   │   ├── buff_internal.h
│   │   │   ├── buff_life_cycle.c
│   │   │   ├── buff_ops.c
│   │   │   ├── buff_read.c
│   │   │   ├── buff_utils.c
│   │   │   └── format
│   │   │       ├── append_1.c
│   │   │       ├── append_2.c
│   │   │       ├── buff_format.h
│   │   │       ├── rules_apply.c
│   │   │       └── rules_parse.c
│   │   ├── chr
│   │   │   ├── ft_isalnum.c
│   │   │   ├── ft_isalpha.c
│   │   │   ├── ft_isascii.c
│   │   │   ├── ft_isdigit.c
│   │   │   ├── ft_isincharset.c
│   │   │   ├── ft_isprint.c
│   │   │   ├── ft_isspace.c
│   │   │   ├── ft_tolower.c
│   │   │   └── ft_toupper.c
│   │   ├── conv
│   │   │   ├── ft_atol.c
│   │   │   ├── ft_atopid.c
│   │   │   ├── ft_atozu.c
│   │   │   ├── ft_ltoa.c
│   │   │   ├── ft_pidtoa.c
│   │   │   ├── ft_ultoa_base.c
│   │   │   ├── ft_zutoa.c
│   │   │   ├── parse_int.c
│   │   │   └── variants.c
│   │   ├── error
│   │   │   └── error.c
│   │   ├── hashmap
│   │   │   ├── API.c
│   │   │   ├── buckets
│   │   │   │   ├── buckets.h
│   │   │   │   ├── contains.c
│   │   │   │   ├── detach.c
│   │   │   │   ├── init.c
│   │   │   │   ├── replace.c
│   │   │   │   ├── swap.c
│   │   │   │   └── utils.c
│   │   │   ├── hash_function.c
│   │   │   ├── init.c
│   │   │   ├── insert.c
│   │   │   ├── key_value
│   │   │   │   ├── init.c
│   │   │   │   ├── key_value.h
│   │   │   │   └── utils.c
│   │   │   ├── priv_hashmap.h
│   │   │   └── resize.c
│   │   ├── list
│   │   │   ├── list_apply.c
│   │   │   ├── list_get.c
│   │   │   ├── list_life_cycle.c
│   │   │   ├── list_size.c
│   │   │   └── node.c
│   │   ├── malloc
│   │   │   ├── ft_calloc.c
│   │   │   └── ft_realloc.c
│   │   ├── math
│   │   │   ├── min_max_abs.c
│   │   │   ├── modulo.c
│   │   │   ├── power.c
│   │   │   └── square_root.c
│   │   ├── mem
│   │   │   ├── ft_bzero.c
│   │   │   ├── ft_memchr.c
│   │   │   ├── ft_memcmp.c
│   │   │   ├── ft_memcpy.c
│   │   │   ├── ft_memmove.c
│   │   │   └── ft_memset.c
│   │   ├── print
│   │   │   └── printer.c
│   │   ├── put
│   │   │   ├── ft_putchar_fd.c
│   │   │   ├── ft_putendl_fd.c
│   │   │   ├── ft_putnbr_fd.c
│   │   │   └── ft_putstr_fd.c
│   │   ├── str
│   │   │   ├── str_chr.c
│   │   │   ├── str_cmp.c
│   │   │   ├── str_dup.c
│   │   │   ├── str_iteri.c
│   │   │   ├── str_join.c
│   │   │   ├── str_lcat.c
│   │   │   ├── str_lcpy.c
│   │   │   ├── str_len.c
│   │   │   ├── str_mapi.c
│   │   │   ├── str_ncmp.c
│   │   │   ├── str_ncpy.c
│   │   │   ├── str_ndup.c
│   │   │   ├── str_nstr.c
│   │   │   ├── str_rchr.c
│   │   │   ├── str_split.c
│   │   │   ├── str_str.c
│   │   │   ├── str_sub.c
│   │   │   ├── str_trim_leading.c
│   │   │   └── str_trim.c
│   │   └── vector
│   │       ├── vector_life_cycle.c
│   │       ├── vector_ops_items.c
│   │       └── vector_ops_vectors.c
│   └── tests
│       ├── buff.c
│       ├── isincharset.c
│       ├── ltoa.c
│       ├── realloc.c
│       └── ultoa_base.c
├── logs
│   ├── 0_check.c
│   ├── 1_life_cycle.c
│   ├── 2_blocks.c
│   ├── 3_title.c
│   ├── 4_log.c
│   ├── 5_result.c
│   ├── 6_error.c
│   ├── logs_priv.h
│   └── logs.h
├── logs.txt
├── Makefile
├── minishell
├── readline.supp
├── ressouces
│   ├── documentation.md
│   ├── external
│   │   ├── 1_POSIX_sh.txt
│   │   ├── 2_POSIX_chap_1.txt
│   │   ├── 3_POSIX_chap_2.txt
│   │   ├── C_arithm
│   │   │   └── Norme_C_arithm_in_Annex_A.3
│   │   ├── libc
│   │   │   └── read.txt
│   │   ├── others
│   │   │   ├── 1_CNRS_Parsing_POSIX_[S]hell.pdf
│   │   │   ├── 2_Wikipedia_Canonical_LR_Parser.txt
│   │   │   └── 3_Tribble_Practical_LRK_parser_construction.txt
│   │   └── utilities
│   │       ├── 1_4_Utility_Description_Defaults.txt
│   │       ├── 1_5_Considerations_for_Utilities_in_Support_of_Files_of_Arbitrary_Size.txt
│   │       ├── 1_6_Built-In_Utilities.txt
│   │       ├── 1_7_Intrinsic_Utilities.txt
│   │       ├── 2_15_Special_Built-In_Utilities.txt
│   │       ├── set.txt
│   │       └── XBD_12_utility_conventions.txt
│   ├── flow.md
│   ├── grammar.txt
│   ├── ia_alexander.md
│   ├── ia_guillaume.md
│   ├── lexer_tests.md
│   ├── lr_machine.md
│   ├── pipeline.md
│   ├── Token_types.md
│   ├── z_alias.txt
│   └── z_tokenization.md
├── srcs
│   ├── 0_asm_stubs
│   │   ├── ft_getpid
│   │   │   ├── freebsd.c
│   │   │   ├── linux.c
│   │   │   ├── mac_arm.c
│   │   │   ├── mac_x86.c
│   │   │   └── openbsd.c
│   │   └── ft_getppid
│   │       ├── freebsd.c
│   │       ├── linux.c
│   │       ├── mac_arm.c
│   │       ├── mac_x86.c
│   │       └── openbsd.c
│   ├── 0_context
│   │   ├── expansion
│   │   │   ├── _main.c
│   │   │   ├── arith.c
│   │   │   ├── backtick.c
│   │   │   ├── cmd_sub.c
│   │   │   └── param.c
│   │   ├── none.c
│   │   ├── quoting
│   │   │   ├── _main.c
│   │   │   ├── dollar_squote.c
│   │   │   ├── dquote.c
│   │   │   └── squote.c
│   │   └── stack
│   │       ├── _init.c
│   │       └── _utils.c
│   ├── 0_posix_helpers
│   │   ├── posix_getcwd.c
│   │   └── posix_write.c
│   ├── 0_token
│   │   ├── _init.c
│   │   └── _utils.c
│   ├── 0_utils
│   │   ├── 1_ft_getopt
│   │   │   ├── 0_utils.c
│   │   │   ├── 1_process_arg.c
│   │   │   ├── 2_main.c
│   │   │   ├── 3_dump.c
│   │   │   └── ft_getopt_priv.h
│   │   ├── 2_serializer
│   │   │   ├── 1_serialize.c
│   │   │   ├── 2_deserialize.c
│   │   │   ├── 3_deserialize_all.c
│   │   │   └── serialize_priv.h
│   │   ├── assignment.c
│   │   ├── ft_getpwnam
│   │   │   └── _main.c
│   │   ├── name.c
│   │   └── time.c
│   ├── 1_shell
│   │   ├── 1_life_cycle.c
│   │   ├── 2_helpers.c
│   │   ├── 3_get.c
│   │   ├── 4_load.c
│   │   ├── 5_exec_env.c
│   │   ├── 6_run.c
│   │   └── shell_priv.h
│   ├── 2_scanner
│   │   ├── _init.c
│   │   ├── _utils.c
│   │   ├── API.c
│   │   ├── lexer
│   │   │   ├── _init.c
│   │   │   ├── _main.c
│   │   │   ├── _utils.c
│   │   │   ├── context
│   │   │   │   ├── _main.c
│   │   │   │   ├── _utils_.c
│   │   │   │   ├── _utils.c
│   │   │   │   ├── arith.c
│   │   │   │   ├── backtick.c
│   │   │   │   ├── cmd_sub.c
│   │   │   │   ├── dollar_squote.c
│   │   │   │   ├── dquote.c
│   │   │   │   ├── lexer_context_.h
│   │   │   │   ├── param.c
│   │   │   │   └── squote.c
│   │   │   ├── input_stack
│   │   │   │   ├── _init.c
│   │   │   │   ├── _main.c
│   │   │   │   └── input_stack_.h
│   │   │   ├── lexer_.h
│   │   │   ├── operator
│   │   │   │   ├── _main.c
│   │   │   │   ├── _utils.c
│   │   │   │   ├── ampersand.c
│   │   │   │   ├── great.c
│   │   │   │   ├── less.c
│   │   │   │   ├── lexer_operator_.h
│   │   │   │   ├── pipe.c
│   │   │   │   └── semicolon.c
│   │   │   └── rules
│   │   │       ├── _main.c
│   │   │       ├── blank.c
│   │   │       ├── comment.c
│   │   │       ├── context.c
│   │   │       ├── end.c
│   │   │       ├── lexer_rules_.h
│   │   │       ├── operator.c
│   │   │       └── word.c
│   │   ├── reader
│   │   │   ├── _main.c
│   │   │   ├── _utils.c
│   │   │   └── reader_.h
│   │   └── scanner_.h
│   ├── 3_builder
│   │   ├── 1_lr_machine
│   │   │   ├── 1_hooks
│   │   │   │   ├── hook_3.c
│   │   │   │   ├── hook_9.c
│   │   │   │   ├── hook_fname.c
│   │   │   │   ├── hook_store_cst.c
│   │   │   │   ├── hooks_type.h
│   │   │   │   └── hooks.h
│   │   │   ├── 2_symbols
│   │   │   │   ├── 1_terminal.c
│   │   │   │   ├── 2_nullable.c
│   │   │   │   ├── 3_reserved.c
│   │   │   │   ├── symbols_type.h
│   │   │   │   └── symbols.h
│   │   │   ├── 3_rules
│   │   │   │   ├── rules__main.c
│   │   │   │   ├── rules__priv.h
│   │   │   │   ├── rules__pub.h
│   │   │   │   ├── rules__type.h
│   │   │   │   ├── rules_and_or.c
│   │   │   │   ├── rules_brace_group.c
│   │   │   │   ├── rules_case_clause.c
│   │   │   │   ├── rules_case_item_ns.c
│   │   │   │   ├── rules_case_item.c
│   │   │   │   ├── rules_case_list_ns.c
│   │   │   │   ├── rules_case_list.c
│   │   │   │   ├── rules_cmd_name.c
│   │   │   │   ├── rules_cmd_prefix.c
│   │   │   │   ├── rules_cmd_suffix.c
│   │   │   │   ├── rules_cmd_word.c
│   │   │   │   ├── rules_command.c
│   │   │   │   ├── rules_complete_command.c
│   │   │   │   ├── rules_complete_commands.c
│   │   │   │   ├── rules_compound_command.c
│   │   │   │   ├── rules_compound_list.c
│   │   │   │   ├── rules_do_group.c
│   │   │   │   ├── rules_else_part.c
│   │   │   │   ├── rules_filename.c
│   │   │   │   ├── rules_fname.c
│   │   │   │   ├── rules_for_clause.c
│   │   │   │   ├── rules_function_body.c
│   │   │   │   ├── rules_function_definition.c
│   │   │   │   ├── rules_here_end.c
│   │   │   │   ├── rules_if_clause.c
│   │   │   │   ├── rules_in.c
│   │   │   │   ├── rules_io_file.c
│   │   │   │   ├── rules_io_here.c
│   │   │   │   ├── rules_io_redirect.c
│   │   │   │   ├── rules_linebreak.c
│   │   │   │   ├── rules_list.c
│   │   │   │   ├── rules_name.c
│   │   │   │   ├── rules_newline_list.c
│   │   │   │   ├── rules_pattern_list.c
│   │   │   │   ├── rules_pipe_sequence.c
│   │   │   │   ├── rules_pipeline.c
│   │   │   │   ├── rules_program.c
│   │   │   │   ├── rules_redirect_list.c
│   │   │   │   ├── rules_separator_op.c
│   │   │   │   ├── rules_separator.c
│   │   │   │   ├── rules_sequential_sep.c
│   │   │   │   ├── rules_simple_command.c
│   │   │   │   ├── rules_start.c
│   │   │   │   ├── rules_subshell.c
│   │   │   │   ├── rules_term.c
│   │   │   │   ├── rules_until_clause.c
│   │   │   │   ├── rules_while_clause.c
│   │   │   │   └── rules_wordlist.c
│   │   │   ├── 4_first
│   │   │   │   ├── 1_add.c
│   │   │   │   ├── 2_build.c
│   │   │   │   ├── 3_first.c
│   │   │   │   ├── first_priv.h
│   │   │   │   └── first.h
│   │   │   ├── 5_rule_state
│   │   │   │   ├── rule_state_type.h
│   │   │   │   ├── rule_state.c
│   │   │   │   └── rule_state.h
│   │   │   ├── 6_lr_state
│   │   │   │   ├── 1_life_cycle.c
│   │   │   │   ├── 2_ops.c
│   │   │   │   ├── 3_registry.c
│   │   │   │   ├── 4_core.c
│   │   │   │   ├── lr_state_type.h
│   │   │   │   └── lr_state.h
│   │   │   ├── 7_transition
│   │   │   │   ├── 1_life_cycle.c
│   │   │   │   ├── 2_build.c
│   │   │   │   ├── transition_type.h
│   │   │   │   └── transition.h
│   │   │   ├── 8_goto
│   │   │   │   ├── 1_life_cycle.c
│   │   │   │   ├── 2_build.c
│   │   │   │   ├── 3_core.c
│   │   │   │   ├── goto_types.h
│   │   │   │   └── goto.h
│   │   │   ├── 9_action
│   │   │   │   ├── 1_life_cycle.c
│   │   │   │   ├── 2_default.c
│   │   │   │   ├── 3_core.c
│   │   │   │   ├── action_priv.h
│   │   │   │   ├── action_type.h
│   │   │   │   └── action.h
│   │   │   ├── lr_machine_type.h
│   │   │   ├── lr_machine.h
│   │   │   └── main.c
│   │   ├── 2_parser
│   │   │   ├── 0_error.c
│   │   │   ├── 0_read_heredoc.c
│   │   │   ├── 1_life_cycle.c
│   │   │   ├── 1_qualifiers
│   │   │   │   ├── 0_name.c
│   │   │   │   ├── 0_reserved_words.c
│   │   │   │   ├── 0_word.c
│   │   │   │   ├── 1_qualify.c
│   │   │   │   ├── 2_qualify.c
│   │   │   │   ├── 4_qualify.c
│   │   │   │   ├── 5_qualify.c
│   │   │   │   ├── 6a_qualify.c
│   │   │   │   ├── 6b_qualify.c
│   │   │   │   ├── 7a_qualify.c
│   │   │   │   ├── 7b_qualify.c
│   │   │   │   ├── 8_qualify.c
│   │   │   │   ├── build_table.c
│   │   │   │   ├── qualifiers_priv.h
│   │   │   │   ├── qualifiers_type.h
│   │   │   │   ├── qualifiers.h
│   │   │   │   └── qualify.c
│   │   │   ├── 2_build.c
│   │   │   ├── 2_stack
│   │   │   │   ├── parser_stack_type.h
│   │   │   │   └── parser_stack.c
│   │   │   ├── 3_cst
│   │   │   │   ├── 7_cst.c
│   │   │   │   ├── cst_type.h
│   │   │   │   └── cst.h
│   │   │   ├── 3_read.c
│   │   │   ├── 4_shift.c
│   │   │   ├── 5_reduce.c
│   │   │   ├── 6_cmd_name_word.c
│   │   │   ├── main.c
│   │   │   ├── parser_priv.h
│   │   │   ├── parser_type.h
│   │   │   └── parser.h
│   │   ├── 3_converter
│   │   │   ├── 0_cst_helpers.c
│   │   │   ├── 1_redirection
│   │   │   │   ├── 1_life_cycle.c
│   │   │   │   ├── 2_convert_io_file_or_here.c
│   │   │   │   ├── 3_convert_one.c
│   │   │   │   ├── 4_convert_list.c
│   │   │   │   └── convert_io_priv.h
│   │   │   ├── 10_function
│   │   │   │   ├── 1_life_cycle.c
│   │   │   │   └── 2_convert.c
│   │   │   ├── 11_command
│   │   │   │   ├── 1_life_cycle.c
│   │   │   │   └── 2_convert.c
│   │   │   ├── 2_simple_command
│   │   │   │   ├── 1_life_cycle.c
│   │   │   │   └── 2_convert.c
│   │   │   ├── 3_pipeline
│   │   │   │   ├── 1_life_cycle.c
│   │   │   │   └── 2_convert.c
│   │   │   ├── 4_and_or
│   │   │   │   ├── 1_life_cycle.c
│   │   │   │   └── 2_convert.c
│   │   │   ├── 5_list
│   │   │   │   ├── 1_life_cycle.c
│   │   │   │   └── 2_convert.c
│   │   │   ├── 6_if
│   │   │   │   ├── 1_life_cycle.c
│   │   │   │   └── 2_convert.c
│   │   │   ├── 7_for
│   │   │   │   ├── 1_life_cycle.c
│   │   │   │   └── 2_convert.c
│   │   │   ├── 8_loop
│   │   │   │   ├── 1_life_cycle.c
│   │   │   │   └── 2_convert.c
│   │   │   ├── 9_case
│   │   │   │   ├── 1_life_cycle.c
│   │   │   │   └── 2_convert.c
│   │   │   ├── ast_type.h
│   │   │   ├── converter_priv.h
│   │   │   ├── converter.h
│   │   │   └── main.c
│   │   ├── cmd_name_word.c
│   │   └── main.c
│   ├── 4_runner
│   │   ├── 1_redirector
│   │   ├── 2_executor
│   │   ├── 3_walker
│   │   └── main.c
│   ├── alias
│   │   ├── _init.c
│   │   ├── _utils.c
│   │   ├── alias_.h
│   │   ├── API.c
│   │   └── stack
│   │       ├── _init.c
│   │       ├── _utils.c
│   │       └── alias_stack_.h
│   ├── builtins
│   │   ├── builtins_get.c
│   │   ├── builtins_priv.h
│   │   ├── export.c
│   │   ├── readonly.c
│   │   └── unset.c
│   ├── debug.c
│   ├── error.c
│   ├── expander
│   │   ├── _init.c
│   │   ├── API.c
│   │   ├── expander_.h
│   │   ├── field
│   │   │   ├── _init.c
│   │   │   ├── _utils.c
│   │   │   └── expander_field_.h
│   │   ├── field_splitting
│   │   │   ├── _main.c
│   │   │   └── field_splitting_.h
│   │   ├── loader
│   │   │   ├── _init.c
│   │   │   ├── _main.c
│   │   │   ├── _utils.c
│   │   │   ├── context.c
│   │   │   └── expander_loader_.h
│   │   ├── path_name_expansion
│   │   │   └── path_name_expansion.h
│   │   ├── quote_removal
│   │   │   ├── _main.c
│   │   │   ├── context
│   │   │   │   ├── _utils.c
│   │   │   │   ├── dollar_squote.c
│   │   │   │   ├── dquote.c
│   │   │   │   ├── quote_removal_context_.h
│   │   │   │   └── squote.c
│   │   │   └── quote_removal_.h
│   │   ├── substitutions
│   │   │   ├── _main.c
│   │   │   ├── expander_substitutions.h
│   │   │   └── tilde
│   │   │       ├── _main.c
│   │   │       └── tilde_expansion_.h
│   │   └── word
│   │       ├── _init.c
│   │       ├── _utils_.c
│   │       ├── _utils.c
│   │       └── expander_word_.h
│   ├── heredoc
│   │   ├── _init.c
│   │   ├── _utils.c
│   │   ├── API.c
│   │   ├── body
│   │   │   ├── _init.c
│   │   │   ├── _main.c
│   │   │   ├── _utils.c
│   │   │   └── heredoc_body_.h
│   │   ├── heredoc_.h
│   │   └── queue
│   │       ├── _init.c
│   │       ├── _utils.c
│   │       └── heredoc_queue_.h
│   ├── history
│   │   ├── _init.c
│   │   ├── _utils.c
│   │   ├── API.c
│   │   ├── file
│   │   │   ├── _init.c
│   │   │   ├── _main.c
│   │   │   ├── _utils.c
│   │   │   └── history_file_.h
│   │   ├── history_.h
│   │   ├── list
│   │   │   ├── _init.c
│   │   │   ├── _main.c
│   │   │   └── history_list_.h
│   │   ├── load_env.c
│   │   └── readline
│   │       ├── _init.c
│   │       ├── _main.c
│   │       ├── _utils.c
│   │       └── history_readline_.h
│   ├── main.c
│   ├── params
│   │   ├── 1_life_cycle.c
│   │   ├── 1_options
│   │   │   ├── 1_life_cycle.c
│   │   │   ├── 2_helpers.c
│   │   │   ├── 3_flags.c
│   │   │   ├── 4_named.c
│   │   │   ├── 5_load.c
│   │   │   ├── 6_dump.c
│   │   │   ├── options_priv.h
│   │   │   └── options.h
│   │   ├── 2_load.c
│   │   ├── 2_specials
│   │   │   ├── 1_life_cycle.c
│   │   │   ├── 2_load.c
│   │   │   ├── 3_get_set.c
│   │   │   ├── 4_dump.c
│   │   │   └── specials.h
│   │   ├── 3_get.c
│   │   ├── 3_positionals
│   │   │   ├── 1_life_cycle.c
│   │   │   ├── 2_ops.c
│   │   │   ├── 3_get.c
│   │   │   ├── 4_dump.c
│   │   │   ├── positionals_priv.h
│   │   │   └── positionals.h
│   │   ├── 4_set.c
│   │   ├── 4_variables
│   │   │   ├── 1_life_cycle.c
│   │   │   ├── 2_helpers.c
│   │   │   ├── 3_registry.c
│   │   │   ├── 4_print.c
│   │   │   ├── 5_build_envp.c
│   │   │   ├── 6_dump.c
│   │   │   ├── load
│   │   │   │   ├── 1_envp
│   │   │   │   │   ├── main.c
│   │   │   │   │   └── var_load_envp.h
│   │   │   │   ├── 2_mandatory
│   │   │   │   │   ├── 1_ifs.c
│   │   │   │   │   ├── 2_pwd.c
│   │   │   │   │   ├── 3_ppid.c
│   │   │   │   │   ├── main.c
│   │   │   │   │   ├── var_load_mandatory_priv.h
│   │   │   │   │   └── var_load_mandatory.h
│   │   │   │   └── 3_up
│   │   │   │       ├── main.c
│   │   │   │       └── var_load_up.h
│   │   │   ├── variables_priv.h
│   │   │   └── variables.h
│   │   ├── 5_edit_positionals.c
│   │   ├── 6_print.c
│   │   └── 7_dump.c
│   ├── TODO.c
│   └── ub.c
├── tests
│   └── test_init.zsh
├── TODO_GA.md
└── xav
    ├── 1_raw
    │   ├── blasé.jpeg
    │   ├── chut.webp
    │   ├── coquin.jpg
    │   ├── face_2.jpg
    │   ├── face_3.jpg
    │   ├── face.jpg
    │   ├── lidl.jpeg
    │   ├── melon.jpg
    │   ├── oh.jpg
    │   ├── outré.webp
    │   ├── stoic.jpg
    │   ├── stop.avif
    │   ├── surpris.jpeg
    │   ├── xavier_head_48.png
    │   └── you.jpeg
    ├── 2_transp
    │   ├── blasé.png
    │   ├── chut.png
    │   ├── coquin.png
    │   ├── face_2.png
    │   ├── face_3.png
    │   ├── face.png
    │   ├── lidl.png
    │   ├── melon.png
    │   ├── oh.png
    │   ├── outré.png
    │   ├── stoic.png
    │   ├── stop.avif
    │   ├── stop.png
    │   ├── surpris.png
    │   └── you.png
    ├── 3_ascii
    │   ├── best_face.txt
    │   ├── best_melon.txt
    │   ├── best_oh.txt
    │   ├── best_stop.txt
    │   ├── best_you.txt
    │   ├── blasé.txt
    │   ├── chut.txt
    │   ├── coquin.txt
    │   ├── face_2.txt
    │   ├── face_3.txt
    │   ├── lidl.txt
    │   ├── outré.txt
    │   ├── stoic.txt
    │   └── surpris.txt
    ├── 4_ub
    │   ├── UB_big_money-nw.txt
    │   ├── UB_big.txt
    │   ├── UB_doom.txt
    │   ├── UB_georgia_11.txt
    │   ├── UB_letters.txt
    │   ├── UB_poison.txt
    │   ├── UB_roman.txt
    │   ├── UB_star_wars.txt
    │   └── UB_univers.txt
    └── 5_combo
        └── best_melon+poison.txt

119 directories, 585 files
```

./includes/alias.h
```c
#ifndef ALIAS_H
# define ALIAS_H

# include "error.h"
# include "token.h"

/** @defgroup alias Alias API
 *  @brief Shell command aliases with recursion-guarded expansion.
 *
 *  Maps alias names to their replacement text in a hash map and keeps full
 *  ownership of its data: names and values handed in are deep copied (the
 *  caller keeps its buffers) and the expansion handed out is a deep copy the
 *  caller takes ownership of, so no buffer is shared across the boundary. A
 *  stack of the aliases currently being expanded guards against infinite
 *  recursion.
 */

typedef t_vector	t_alias_stack;

/**
 * @ingroup alias
 * @struct s_alias
 * @brief Aggregate state of the alias module.
 *
 * @var s_alias::err Last error recorded by the module.
 * @var s_alias::map Name-to-value hash map (owns its keys and values).
 * @var s_alias::stack Names of the aliases currently being expanded.
 * @var s_alias::disable_position Whether the next word may expand regardless
 *                                of command position (set when an expansion
 *                                ends with a blank).
 */
typedef struct s_alias
{
	t_error			err;
	t_hashmap		map;
	t_alias_stack	stack;
	bool			disable_position;
}	t_alias;

/**
 * @ingroup alias
 * @brief Initialises an alias state to an empty, ready-to-use value.
 *
 * Zeroes the structure then initialises the expansion stack and the
 * name-to-value map, whose values are released with free() on removal.
 *
 * @param state Pointer to the alias state to initialise (borrowed).
 */
void	alias_init(t_alias *state);

/**
 * @ingroup alias
 * @brief Releases every resource held by an alias state.
 *
 * Frees the expansion stack and the map (keys and values), then resets the
 * structure to zero.
 *
 * @param state Pointer to the alias state to free (borrowed).
 */
void	alias_free(t_alias *state);

/**
 * @ingroup alias
 * @brief Marks the end of the current alias expansion.
 *
 * Pops the most recent name off the recursion-guard stack, allowing that
 * alias to expand again later. Does nothing when the stack is empty.
 * Operates on the global shell alias state.
 *
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell alias state is
 *         unavailable, or the recorded error on failure.
 */
t_error	alias_on_expansion_end(void);

/**
 * @ingroup alias
 * @brief Prints one alias, or every alias, as `name='value'`.
 *
 * Prints the alias named @p name, or all stored aliases when @p name is
 * NULL. A missing name prints nothing. Operates on the global shell alias
 * state.
 *
 * @param name Alias to print (borrowed), or NULL to print them all.
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell alias state is
 *         unavailable, or the recorded error on failure.
 */
t_error	alias_print(const char *name);

/**
 * @ingroup alias
 * @brief Removes an alias by name.
 *
 * Removes the alias named @p name and frees the module's copies of its key
 * and value. Does nothing when @p name is NULL or absent. The caller keeps
 * ownership of @p name. Operates on the global shell alias state.
 *
 * @param name Alias to remove (borrowed).
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell alias state is
 *         unavailable, or the recorded error on failure.
 */
t_error	alias_remove(const char *name);

/**
 * @ingroup alias
 * @brief Adds or replaces an alias.
 *
 * Associates @p name with @p value, replacing any existing entry. The key is
 * duplicated and the value is deep copied (a NULL value is stored as an empty
 * string), so the caller keeps ownership of both arguments. Operates on the
 * global shell alias state.
 *
 * @param name Alias name (borrowed; duplicated internally).
 * @param value Replacement text (borrowed; deep copied, NULL means empty).
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell alias state is
 *         unavailable, or ERR_LIBC on allocation failure.
 */
t_error	alias_add(const char *name, const char *value);

/**
 * @ingroup alias
 * @brief Expands a token to its alias value when eligible.
 *
 * Reads the token text from @p token_value and, when it names an alias
 * eligible for expansion (valid unquoted name, not already being expanded,
 * and in command position unless a previous expansion lifted that rule),
 * pushes the name onto the recursion-guard stack and returns a freshly
 * allocated copy of its value through @p expansion. When the token is not
 * eligible, @p expansion is left untouched.
 *
 * @note On a successful expansion, ownership of *expansion passes to the
 *       caller.
 * @warning *expansion is written only when the token expands; initialise it
 *          to NULL before the call (or test the return value) so the
 *          no-expansion case stays distinguishable.
 *
 * @param expansion Out-parameter receiving the freshly allocated expansion
 *                  string (owned by the caller) on a successful expansion.
 * @param token_value Buffer holding the token text to test (borrowed).
 * @return ERR_NO on success (whether or not the token expanded),
 *         ERR_SHELL_NOT_FOUND if the shell alias state is unavailable, or
 *         ERR_LIBC on allocation failure.
 */
t_error	alias_expand_token(char **expansion, t_buff *token_value);

#endif

```

./includes/asm_stubs.h
```c
#ifndef ASM_STUBS_H
# define ASM_STUBS_H

# include "error.h"
# include <unistd.h>

pid_t	ft_getpid(void);
pid_t	ft_getppid(void);

// ERR_NO / ERR_UNABLE_TO_BLOCK_STDIN
t_error	ft_stdin_set_blocking(void);

#endif

```

./includes/builder.h
```c
#ifndef BUILDER_H
# define BUILDER_H

# include "error.h"
# include "lr_machine_type.h"
# include "parser_type.h"
# include "ast_type.h"

typedef struct s_builder
{
	t_lr_machine	lr_machine;
	t_parser		parser;
}	t_builder;

void	builder_init(t_builder *builder);
t_error	builder_load(t_builder *builder);
t_error	builder_reset(void);
void	builder_free(t_builder *builder);

t_error	builder_get_ast(t_ast_root *dst_ast);
void	ast_root_free(t_ast_root *root);

// @ret ERR_SHELL_NOT_FOUND
t_error	builder_can_next_word_be_a_cmd_name(bool *dst);

#endif

```

./includes/builtins.h
```c
#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>

typedef int (*t_builtin_function)(int argc, char **argv, char **envp);

typedef struct s_builtin
{
	const char			*name;
	t_builtin_function	function;
}	t_builtin;

/* ************************************************************************* */
/*                                   GETTER                                  */
/* ************************************************************************* */

/*
SPECIALS:
	- Searched first during Command Search.
	- Shell exits on error (if invoked directly && shell is non-interactive).
REGULAR / INTRINSICS:
	- Searched right after functions during Command Search.
	- Shell does not exit on error.
*/
t_builtin_function	builtins_get(const char *name, bool special);

#endif

```

./includes/context.h
```c
#ifndef CONTEXT_H
# define CONTEXT_H

# include "error.h"
# include "libft.h"

/** @defgroup context Context API
 *  @brief Quoting and expansion contexts recognised while scanning input.
 *
 *  As the scanner walks the input it tracks the nested constructs currently
 *  open on a context stack (e.g. inside "...", $(...) or $((...))). Each
 *  context type exposes up to three predicates following a shared naming
 *  convention:
 *  - is_context_<x>_start(str): does @p str begin an <x> construct?
 *  - is_context_<x>_ending(c, arg): is @p c the closing delimiter of <x>?
 *  - is_in_context_<x>_whitelist(c): inside <x>, does @p c keep a special
 *    meaning (and therefore still need processing)?
 *
 *  Ending predicates share the signature bool(char, void *) so they can be
 *  held in a single function pointer; the void * carries optional state and
 *  is unused by every context except arithmetic (its nesting depth).
 */

/**
 * @ingroup context
 * @enum e_context
 * @brief A quoting or expansion construct the scanner can be inside of.
 */
typedef enum e_context
{
	CONTEXT_NONE,			/**< Top level, outside any quoting or expansion. */
	CONTEXT_SQUOTE,			/**< Single quotes: '...'. */
	CONTEXT_DQUOTE,			/**< Double quotes: "...". */
	CONTEXT_DOLLAR_SQUOTE,	/**< ANSI-C quoting: $'...'. */
	CONTEXT_BACKTICK,		/**< Backquote command substitution: `...`. */
	CONTEXT_CMD_SUB,		/**< Command substitution: $(...). */
	CONTEXT_ARITH,			/**< Arithmetic expansion: $((...)). */
	CONTEXT_PARAM,			/**< Parameter expansion: ${...}. */
}	t_context;

/**
 * @ingroup context
 * @struct s_context_parser_stack_item
 * @brief One context together with the span it covers in a token's value
 *        buffer.
 *
 * @var s_context_parser_stack_item::end Index one past the construct's last character
 *                                in the token value (filled in when the context
 *                                closes).
 * @var s_context_parser_stack_item::start Index of the construct's first character in
 *                                  the token value (filled in when the context
 *                                  opens).
 * @var s_context_parser_stack_item::context Which construct it is.
 */
typedef struct s_context_parser_stack_item
{
	size_t		end;
	size_t		start;
	t_context	context;
}	t_context_parser_stack_item;

/**
 * @ingroup context
 * @brief Stack of context items (a vector of t_context_parser_stack_item *).
 *
 * Used in two roles: the lexer's live nesting stack (innermost context on top,
 * borrowing its items) and a token's recorded contexts (owning its items). See
 * context_stack_free() for the matching ownership rule.
 */
typedef t_vector	t_context_stack;

/**
 * @ingroup context
 * @brief Initialises an empty context stack.
 *
 * @param stack Pointer to the stack to initialise (borrowed).
 */
void	context_stack_init(t_context_stack *stack);

/**
 * @ingroup context
 * @brief Frees an owning stack: every item pointer it still holds, then its
 *        backing array.
 *
 * Use this for a stack that OWNS its items (a token's recorded contexts). For a
 * stack that only borrows item pointers owned elsewhere (the lexer's live
 * nesting stack), free the backing array alone with vector_free(stack, NULL) so
 * the borrowed items are left intact.
 *
 * @param stack Pointer to the stack to free (borrowed).
 */
void	context_stack_free(t_context_stack *stack);

/**
 * @ingroup context
 * @brief Allocates a context-stack item on the heap.
 *
 * The item's context is set to @p context; its start and end are zeroed and
 * filled in later as the context opens and closes.
 *
 * @param item Out-parameter receiving the newly allocated item (caller owns).
 * @param context Which construct the item represents.
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	context_parser_stack_item_init(t_context_parser_stack_item **item, t_context context);

/**
 * @ingroup context
 * @brief Deep copies a context stack onto an already-initialised one.
 *
 * Allocates an independent item for every entry of @p src and pushes it onto
 * @p dst in order, so the two stacks share no memory. @p dst must already be
 * initialised (context_stack_init); its existing contents are kept and the
 * copies are appended.
 *
 * @param dst Destination stack, initialised by the caller, appended to here
 *            (borrowed).
 * @param src Source stack to copy (borrowed).
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	context_stack_dup(t_context_stack *dst, t_context_stack *src);

/**
 * @ingroup context
 * @brief Pushes an item pointer onto the top (back) of the stack.
 *
 * Only the pointer is stored; ownership of the pointed-to item is not
 * transferred.
 *
 * @param stack Pointer to the stack (borrowed).
 * @param item Item pointer to push.
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	context_stack_push(t_context_stack *stack, t_context_parser_stack_item *item);

/**
 * @ingroup context
 * @brief Removes the item on top (back) of the stack.
 *
 * Regular LIFO pop: yields the most recently pushed (innermost) context.
 *
 * @param stack Pointer to the stack (borrowed).
 * @param item Out-parameter receiving the removed item pointer; may be NULL to
 *             discard it.
 * @return ERR_NO on success, ERR_EMPTY_STACK if the stack is empty.
 */
t_error	context_stack_bpop(t_context_stack *stack, t_context_parser_stack_item **item);

/**
 * @ingroup context
 * @brief Removes the item at the bottom (front) of the stack.
 *
 * FIFO-style removal: yields the oldest (outermost) context.
 *
 * @param stack Pointer to the stack (borrowed).
 * @param item Out-parameter receiving the removed item pointer; may be NULL to
 *             discard it.
 * @return ERR_NO on success, ERR_EMPTY_STACK if the stack is empty.
 */
t_error	context_stack_fpop(t_context_stack *stack, t_context_parser_stack_item **item);

/**
 * @ingroup context
 * @brief Reads the item at @p index without removing it.
 *
 * Index 0 is the bottom (front / outermost) of the stack.
 *
 * @param stack Pointer to the stack (borrowed).
 * @param item Out-parameter receiving the item pointer at @p index.
 * @param index Position to read.
 * @return ERR_NO on success, ERR_EMPTY_STACK if the stack is empty,
 *         ERR_INDEX_OUT_OF_BOUND if @p index is past the last element.
 */
t_error	context_stack_get(t_context_stack *stack, t_context_parser_stack_item **item,
			size_t index);

/**
 * @ingroup context
 * @brief Tests whether a character is a blank (space or tab).
 *
 * @param c Character to test.
 * @return true if @p c is a space or a tab.
 */
bool	is_blank(char c);

/**
 * @ingroup context
 * @brief Whitelist for the top-level context: every character is processed.
 *
 * @param c Character to test (ignored).
 * @return Always true.
 */
bool	is_in_context_none_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether the top-level context ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true at the end of input (NUL).
 */
bool	is_context_none_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Tests whether @p str begins an arithmetic expansion ($((  ).
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with "$((".
 */
bool	is_context_arith_start(char *str);

/**
 * @ingroup context
 * @brief Tests whether an arithmetic expansion ends at @p c.
 *
 * @param c Character to test.
 * @param nesting_depth Pointer to the current parenthesis depth (size_t *);
 *                      the context ends only at the outermost ')'.
 * @return true if @p c is ')' and the nesting depth is zero.
 */
bool	is_context_arith_ending(char c, void *nesting_depth);

/**
 * @ingroup context
 * @brief Tests whether @p str begins a backquote substitution (`).
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with a backquote.
 */
bool	is_context_backtick_start(char *str);

/**
 * @ingroup context
 * @brief Whitelist of characters special inside a backquote substitution.
 *
 * @param c Character to test.
 * @return true for '\\', '$' and '`'.
 */
bool	is_in_context_backtick_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether a backquote substitution ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true if @p c is a backquote.
 */
bool	is_context_backtick_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Extended special set for backquotes nested inside double quotes.
 *
 * @param c Character to test.
 * @return true for '$', '`', '"' and '\\'.
 */
bool	is_in_context_backtick_special_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether @p str begins a command substitution ($(  ).
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with "$(".
 */
bool	is_context_cmd_sub_start(char *str);

/**
 * @ingroup context
 * @brief Tests whether @p str begins a parameter expansion (${  ).
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with "${".
 */
bool	is_context_param_start(char *str);

/**
 * @ingroup context
 * @brief Whitelist for a parameter expansion: every character is processed.
 *
 * @param c Character to test (ignored).
 * @return Always true.
 */
bool	is_in_context_param_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether a parameter expansion ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true if @p c is '}'.
 */
bool	is_context_param_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Detects which expansion construct, if any, @p str begins.
 *
 * Tested in priority order: parameter, arithmetic, command substitution,
 * backquote.
 *
 * @param str Input cursor to test.
 * @param context Out-parameter receiving the detected context on a match.
 * @return true if @p str begins an expansion (and @p context was set).
 */
bool	is_expansion_context(char *str, t_context *context);

/**
 * @ingroup context
 * @brief Tests @p c against the whitelist of the given expansion context.
 *
 * Dispatches to the matching is_in_context_<x>_whitelist() for PARAM, ARITH,
 * CMD_SUB and BACKTICK.
 *
 * @param c Character to test.
 * @param context Expansion context whose whitelist to use.
 * @return true if @p c is special within @p context.
 */
bool	is_in_expansion_whitelist(char c, t_context context);

/**
 * @ingroup context
 * @brief Tests whether @p str begins ANSI-C quoting ($'  ).
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with "$'".
 */
bool	is_context_dollar_squote_start(char *str);

/**
 * @ingroup context
 * @brief Whitelist for ANSI-C quoting: every character is processed.
 *
 * @param c Character to test (ignored).
 * @return Always true.
 */
bool	is_in_context_dollar_squote_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether ANSI-C quoting ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true if @p c is a single quote.
 */
bool	is_context_dollar_squote_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Tests whether @p str begins a double-quoted section (").
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with a double quote.
 */
bool	is_context_dquote_start(char *str);

/**
 * @ingroup context
 * @brief Whitelist of characters special inside double quotes.
 *
 * @param c Character to test.
 * @return true for '$', '`', '\\' and '"'.
 */
bool	is_in_context_dquote_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether a double-quoted section ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true if @p c is a double quote.
 */
bool	is_context_dquote_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Tests whether @p str begins a single-quoted section (').
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with a single quote.
 */
bool	is_context_squote_start(char *str);

/**
 * @ingroup context
 * @brief Whitelist for single quotes: nothing is special inside them.
 *
 * @param c Character to test (ignored).
 * @return Always false.
 */
bool	is_in_context_squote_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether a single-quoted section ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true if @p c is a single quote.
 */
bool	is_context_squote_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Tests whether @p c closes the given quoting context.
 *
 * Dispatches to the matching is_context_<x>_ending() for SQUOTE, DQUOTE and
 * DOLLAR_SQUOTE.
 *
 * @param c Character to test.
 * @param context Quoting context to test against.
 * @return true if @p c closes @p context, false for non-quoting contexts.
 */
bool	is_quoting_ending(char c, t_context context);

/**
 * @ingroup context
 * @brief Detects which quoting construct, if any, @p str begins.
 *
 * Tested in priority order: single quote, ANSI-C quote, double quote.
 *
 * @param str Input cursor to test.
 * @param context Out-parameter receiving the detected context on a match.
 * @return true if @p str begins a quoting context (and @p context was set).
 */
bool	is_quoting_context(char *str, t_context *context);

/**
 * @ingroup context
 * @brief Tests @p c against the whitelist of the given quoting context.
 *
 * Dispatches to the matching is_in_context_<x>_whitelist() for NONE_, SQUOTE,
 * DQUOTE and DOLLAR_SQUOTE.
 *
 * @param c Character to test.
 * @param context Quoting context whose whitelist to use.
 * @return true if @p c is special within @p context.
 */
bool	is_in_quoting_whitelist(char c, t_context context);

#endif

```

./includes/debug.h
```c
#ifndef DEBUG_H
# define DEBUG_H

# include <stdbool.h>
# include "action_type.h"
# include "symbols_type.h"
# include "lr_machine_type.h"
# include "ast_type.h"
# include "logs.h"

const char	*bool_to_string(bool value);
const char	*action_type_to_string(t_action_type type);
const char	*symbol_to_string(t_symbol symbol);
void		debug_dump_rule(t_lr_machine *machine, size_t rule_id);
void		debug_dump_lr_state(t_lr_machine *machine, size_t lr_state_id);
void		debug_dump_cst_node(t_cst_node *node);
void		debug_dump_ast(t_ast_root *root);

#endif

```

./includes/error.h
```c
#ifndef ERROR_H
# define ERROR_H

#include <stdbool.h>

# define error(type) error_priv(type, __func__)
# define error_sys(type) error_sys_priv(__func__)

typedef enum e_error_type
{
	ERR_NO,
	ERR_ASSIGNMENT_MISSING_NAME,
	ERR_BUILTIN_INVALID_USAGE,
	ERR_HOOK_INVALID_RHS_LEN,
	ERR_INDEX_OUT_OF_BOUND,
	ERR_INVALID_FORMAT,
	ERR_LIBC,
	ERR_LR_CONFLICT,
	ERR_LR_STATE_NOT_FOUND,
	ERR_OPT_INVALID,
	ERR_OPT_INVALID_ARG,
	ERR_OPT_MISSING_ARG,
	ERR_PARSER_EMPTY_GOTO,
	ERR_PARSER_INVALID_FUNCTION_NAME,
	ERR_PARSER_INVALID_STATE,
	ERR_SHELL_NOT_FOUND,
	ERR_SHIFT_INVALID_VALUE,
	ERR_SIZE_MAX_REACHED,
	ERR_UNDEFINED_BEHAVIOUR,
	ERR_VAR_INVALID_NAME,
	ERR_VAR_MISSING_EQUAL,
	ERR_VAR_NOT_FOUND,
	ERR_VAR_READ_ONLY,
	// Lexer
	ERR_NULL_ARGS,
	ERR_TOKEN_INIT,
	ERR_CTX_END_NOT_FOUND,
	ERR_VALUE_OUT_OF_RANGE,
	ERR_LEX_INCOMPLETE,
	ERR_INVALID_SYNTAX,
	ERR_EMPTY_STACK,
	ERR_VEOF,
	ERR_EMPTY_CONTINUATION,
	ERR_INVALID_ARGS,
	ERR_FILE_STAT,
	ERR_OPEN_FILE,
	ERR_INCOHERENT_STATE,
	ERR_NOT_IMPLEMENTED,
	ERR_HEREDOC_FILE_LIMIT,
	ERR_UNEXPECTED_EOI,
	ERR_NO_DELIM,
	ERR_COUNT
}	t_error_type;

typedef struct s_error
{
	t_error_type	type;
	int				saved_errno;
	bool			printed;
}	t_error;

/**
 * @brief Builds an error descriptor from an internal error type.
 *
 * The saved errno value is set to 0.
 *
 * @warning Use error_sys() instead when the error comes from a failed libc or
 * POSIX call and errno must be preserved.
 *
 * @param type Error type to store.
 * @return Error descriptor containing type and no saved errno.
 */
t_error	error_priv(t_error_type type, const char *caller);

/**
 * @brief Builds a libc error descriptor and saves the current errno value.
 *
 * This function must be called immediately after a failed libc or POSIX call,
 * before any other call can overwrite errno.
 *
 * @return Error descriptor containing ERR_LIBC and the current errno value.
 */
t_error	error_sys_priv(const char *caller);

/**
 * @brief Prints a formatted shell error message to stderr.
 *
 * The shell name prefix is printed automatically by this function, since its value
 * depends on the current shell context. Additional prefixes passed by the caller
 * are printed after it, in order, and separated with ": ".
 *
 * The variadic argument list must follow this exact layout:
 * prefixes..., NULL, fstring, fstring arguments...
 *
 * The NULL separator marks the end of the caller-provided prefix list. If fstring
 * is not NULL, it is used as a printf-like format string and must be followed by
 * the matching arguments. If fstring is NULL, no format arguments are read.
 *
 * Example:
 * error_print(error(ERR_OPT_INVALID), "export", "-x", NULL, "%i", my_integer);
 *
 * @warning The caller-provided prefix list must always be terminated by NULL.
 * @warning fstring arguments must match the conversion specifiers used by fstring.
 *
 * @param error Error descriptor to print and return.
 * @param ... Additional prefixes, NULL separator, optional format string, optional arguments.
 * @return The error descriptor received as argument.
 */
t_error	error_print(t_error err, ...);

const char	*error_to_string(t_error err);

// @ret ERR_UNDEFINED_BEHAVIOUR
t_error	undefined_behaviour(const char *message);

#endif

```

./includes/expander.h
```c
#ifndef EXPANDER_H
# define EXPANDER_H

# include "error.h"
# include "context.h"

typedef enum e_expander_role
{
	EXPANDER_NORMAL,
	EXPANDER_ASSIGNMENT,
	EXPANDER_REDIRECT_FILENAME,
	EXPANDER_HEREDOC_DELIMITER,
	EXPANDER_HEREDOC_BODY
}	t_expander_role;

t_error	expander_expand_word(char ***expansion, t_buff value,
			t_context_stack *contexts, t_expander_role role);

#endif

```

./includes/ft_getopt.h
```c
#ifndef FT_GETOPT_H
# define FT_GETOPT_H

# include "error.h"
# include "libft.h"
# include <stdbool.h>
# include <stddef.h>

/*
⚠️ TODO: in each builtin (if doc doesn't specifiy anything else): call undefined_behaviour() when "use of conflicting mutually-exclusive arguments" cf 12.1:8.
---
⚠️ XBD 12.2:
	- Guideline 7
	- Guideline 8
*/

/* ************************************************************************* */
/*                                   INPUT                                   */
/* ************************************************************************* */

typedef struct s_option_with_arg
{
	char		sign;								// '+' / '-'
	char		flag;
	const char	**arguments_valids;					// NULL-terminated
	bool		arguments_are_optional;
}	t_getopt_flag_with_arg;

typedef struct s_getopt_in
{
	const char				*builtin_name;			// used to print error logs
	const char				*valid_minus_flags;		// can be NULL
	const char				*valid_plus_flags;		// can be NULL
	t_getopt_flag_with_arg	*options_with_arg;		// multiple options_with_arg can have the same starting flag if they don't have the same sign
	size_t					options_with_arg_count;
	bool					single_delimiter;		// '-' will be treated as end of options
	bool					ub_on_repeated_flags;	// call undefined_behaviour() when "an option that does not have option-arguments is repeated" cf 12.1:3.
}	t_getopt_in;

/* ************************************************************************* */
/*                                  OUTPUT                                   */
/* ************************************************************************* */

typedef struct s_getopt_option
{
	char		sign;		// '-' / '+'
	char		flag;		// 'a'...
	const char	*argument;	// NULL / argument
}	t_getopt_option;

typedef struct s_getopt_out
{
	t_vector	options;
	size_t		first_operand_index;
}	t_getopt_out;

/* ************************************************************************* */
/*                                  FUNCTION                                 */
/* ************************************************************************* */

// @warning: caller must free out->options with vector_free()
// @ret ERR_OPT_INVALID / ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG /
//		ERR_UNDEFINED_BEHAVIOUR / ERR_LIBC
t_error	ft_getopt(int argc, char **argv, t_getopt_in *input, t_getopt_out *out);

/* ************************************************************************* */
/*                                    DEBUG                                  */
/* ************************************************************************* */

void	ft_getopt_dump_in(t_getopt_in *in);
void	ft_getopt_dump_out(t_getopt_out *out);
void	ft_getopt_dump_all(t_getopt_in *in, t_getopt_out *out);

#endif

```

./includes/heredoc.h
```c
#ifndef HEREDOC_H
# define HEREDOC_H

# include "error.h"
# include "libft.h"

/** @defgroup heredoc Heredoc API
 *  @brief POSIX here-documents collected into owned temporary files.
 *
 *  Each `<<` / `<<-` redirection is registered as a pending heredoc, then its
 *  body is read line by line until the delimiter and spilled to a private
 *  temporary file. The module keeps full ownership of its data: the delimiter
 *  handed in is deep copied (the caller keeps its buffer) and the scanned
 *  input is deep copied before use, so no buffer is shared across the
 *  boundary. The single thing handed out is the temporary file path, a deep
 *  copy the caller takes ownership of (the caller is also responsible for
 *  unlinking the file once the command has consumed it). Temporary file names
 *  are made unique with a monotonic per-state counter combined with O_EXCL, so
 *  several heredocs queued in the same instant never clash.
 */

typedef t_vector	t_heredoc_queue;

/**
 * @ingroup heredoc
 * @enum e_heredoc_mode
 * @brief Selects how body lines and the delimiter are matched.
 *
 * @var e_heredoc_mode::NORMAL Plain `<<`: lines are kept verbatim.
 * @var e_heredoc_mode::TAB_STRIP `<<-`: leading tab characters are stripped
 *                                from every body line and from the delimiter
 *                                comparison.
 */
typedef enum e_heredoc_mode
{
	HEREDOC_MODE_NORMAL,
	HEREDOC_MODE_TAB_STRIP
}	t_heredoc_mode;

/**
 * @ingroup heredoc
 * @struct s_heredoc_queue_item
 * @brief One pending heredoc awaiting its body.
 *
 * @var s_heredoc_queue_item::mode Verbatim or tab-stripping behaviour.
 * @var s_heredoc_queue_item::path Temporary file the body is written to
 *                                 (owned; freed with the item).
 * @var s_heredoc_queue_item::delim Delimiter to stop at (owned), stored after
 *                                  quote removal and terminated by a newline so
 *                                  it matches a whole body line exactly.
 */
typedef struct s_heredoc_queue_item
{
	t_heredoc_mode	mode;
	char			*path;
	char			*delim;
}	t_heredoc_queue_item;

/**
 * @ingroup heredoc
 * @struct s_heredoc
 * @brief Aggregate state of the heredoc module.
 *
 * @var s_heredoc::err Last error recorded by the module.
 * @var s_heredoc::queue Pending heredocs, processed in FIFO order (owns every
 *                       item's path and delimiter).
 * @var s_heredoc::is_stdin Whether bodies are streamed line-by-line from stdin
 *                          (true, interactive terminal or pipe) or pulled from
 *                          an already-read input buffer (false).
 * @var s_heredoc::file_id Monotonic counter seeded from the clock, used to
 *                         build unique temporary file names.
 */
typedef struct s_heredoc
{
	t_error			err;
	t_heredoc_queue	queue;
	size_t			file_id;
	bool			is_stdin;
}	t_heredoc;

/**
 * @ingroup heredoc
 * @brief Initialises a heredoc state to an empty, ready-to-use value.
 *
 * Zeroes the structure, initialises the pending-heredoc queue and seeds the
 * temporary-file counter from the current time so distinct shell runs start
 * from different names.
 *
 * @param state Pointer to the heredoc state to initialise (borrowed).
 */
void	heredoc_init(t_heredoc *state);

/**
 * @ingroup heredoc
 * @brief Releases every resource held by a heredoc state.
 *
 * Frees the queue together with each item's path and delimiter, then resets
 * the structure to zero. The temporary files themselves are not unlinked here;
 * that is the responsibility of whoever consumed the handed-out paths.
 *
 * @param state Pointer to the heredoc state to free (borrowed).
 */
void	heredoc_free(t_heredoc *state);

/**
 * @ingroup heredoc
 * @brief Selects the body-reading source for the next store.
 *
 * Records whether subsequent bodies are streamed line-by-line from stdin
 * (@p is_stdin true) or extracted from an already-read input buffer.
 *
 * @param state Pointer to the heredoc state (borrowed).
 * @param is_stdin true to read bodies from stdin, false to read from input.
 */
void	heredoc_load(t_heredoc *state, bool is_stdin);

/**
 * @ingroup heredoc
 * @brief Reads and stores the body of every queued heredoc.
 *
 * Drains the queue in order; for each heredoc it reads body lines until the
 * delimiter and writes them to the heredoc's temporary file. In interactive
 * mode lines are prompted for; otherwise they are scanned from @p input with
 * @p start advanced past the consumed text. The input is deep copied
 * internally, so the caller keeps ownership of its buffer. Operates on the
 * global shell heredoc state.
 *
 * @param input Buffer to scan bodies from in non-interactive mode (borrowed),
 *              unused when reading interactively.
 * @param start In/out cursor into @p input, advanced past the consumed bytes.
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell heredoc state is
 *         unavailable, ERR_NO_DELIM if @p input ends before the delimiter, or
 *         the recorded error on failure.
 */
t_error	heredoc_store_all(char *input, size_t *start);

/**
 * @ingroup heredoc
 * @brief Registers a new pending heredoc and reserves its temporary file.
 *
 * Creates a fresh unique temporary file, returns its path through @p path (the
 * caller takes ownership of *path), and enqueues an item holding the module's
 * own deep copy of that path together with an owned, quote-stripped,
 * newline-terminated copy of @p delim. The caller keeps ownership of @p delim.
 * Operates on the global shell heredoc state.
 *
 * @note On success, ownership of *path passes to the caller, which must
 *       eventually unlink and free it.
 *
 * @param path Out-parameter receiving the freshly created temporary file path
 *             (owned by the caller).
 * @param delim Delimiter word as written on the command line (borrowed; quote
 *              removed and deep copied internally).
 * @param mode Verbatim (NORMAL) or tab-stripping (TAB_STRIP) behaviour.
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell heredoc state is
 *         unavailable, or ERR_LIBC on allocation or file-creation failure.
 */
t_error	heredoc_add_to_queue(char **path, char *delim, t_heredoc_mode mode);

#endif

```

./includes/history.h
```c
#ifndef HISTORY_H
# define HISTORY_H

# include "error.h"
# include "libft.h"
# include "history_list_.h"
# include "history_file_.h"
# include "history_readline_.h"

/** @defgroup history History API
 *  @brief Command history backed by a file, an in-memory list and readline.
 *
 *  Stores the shell command history and keeps full ownership of its data:
 *  every string that enters the module is deep copied, and every string that
 *  leaves it is a deep copy whose ownership passes to the caller, so no
 *  buffer is ever shared with the outside. The on-disk file and readline's
 *  own history are the only two channels through which entries cross the
 *  module boundary.
 */

/**
 * @ingroup history
 * @struct s_history
 * @brief Aggregate state of the history module.
 *
 * Groups the persistent file backing, the in-memory entry list, the readline
 * mirror and the buffer accumulating the line currently being typed.
 *
 * @var s_history::err Last error recorded by the module.
 * @var s_history::file On-disk history file (path and content buffer).
 * @var s_history::list In-memory list of history entries (owned).
 * @var s_history::rl_history Bookkeeping for readline's own history.
 * @var s_history::current_input Buffer holding the line being assembled.
 */
typedef struct s_history
{
	t_error			err;
	t_history_file	file;
	t_history_list	list;
	t_history_rl	rl_history;
	t_buff			current_input;
}	t_history;

/**
 * @ingroup history
 * @brief Initialises a history state to an empty, ready-to-use value.
 *
 * Zeroes the structure then initialises the entry list, the file backing,
 * the readline bookkeeping and the current-input buffer. Does not touch the
 * filesystem or readline; call history_load() to populate it.
 *
 * @param state Pointer to the history state to initialise (borrowed).
 */
void	history_init(t_history *state);

/**
 * @ingroup history
 * @brief Releases every resource held by a history state.
 *
 * Frees the entry list, the file content buffer and the current-input
 * buffer, clears readline's history, then resets the structure to zero.
 *
 * @param state Pointer to the history state to free (borrowed).
 */
void	history_free(t_history *state);

/**
 * @ingroup history
 * @brief Loads the history from its file into memory and readline.
 *
 * Resolves the file path from $HISTFILE (falling back to $HOME/.sh_history)
 * and the cap from $HISTSIZE, reads and parses the file into the entry list
 * (keeping at most $HISTSIZE entries) and mirrors the loaded entries into
 * readline. Each parsed entry is a fresh allocation owned by the module.
 *
 * @param state Pointer to an initialised history state (borrowed).
 * @return ERR_NO on success, or the error recorded in state->err.
 */
t_error	history_load(t_history *state);

/**
 * @ingroup history
 * @brief Appends to the file the entries added since the last load.
 *
 * Serialises every list entry recorded after the loaded prefix and appends
 * them to the history file. Operates on the global shell history.
 *
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell history is
 *         unavailable, or the recorded error on failure.
 */
t_error	history_save(void);

/**
 * @ingroup history
 * @brief Commits the line being assembled as a new history entry.
 *
 * Turns the accumulated current-input buffer into a freshly owned entry,
 * pushes it onto the list, resets the buffer and mirrors the entry into
 * readline. Does nothing when the current input is empty. Operates on the
 * global shell history.
 *
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell history is
 *         unavailable, or the recorded error on failure.
 */
t_error	history_save_entry(void);

/**
 * @ingroup history
 * @brief Appends a fragment to the line currently being assembled.
 *
 * The fragment is deep copied into the current-input buffer, so the caller
 * keeps ownership of @p entry. Call history_save_entry() to commit the
 * assembled line. Operates on the global shell history.
 *
 * @param entry NUL-terminated fragment to append (borrowed; deep copied).
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell history is
 *         unavailable, or ERR_LIBC on allocation failure.
 */
t_error	history_append_to_entry(char *entry);

#endif

```

./includes/params.h
```c
#ifndef PARAMS_H
# define PARAMS_H

# include "variables.h"
# include "options.h"
# include "specials.h"
# include "positionals.h"

typedef struct s_params
{
	const char			*name;			// (internal)
	t_var_list			variables;		// $<var_name>
	t_option			options;		// $-
	t_specials			specials;		// $0 $$ $! $?
	t_positionals_stack	positionals;	// $@ $* $# $<n>
}	t_params;

typedef enum e_params_print_mode
{
	PARAMS_PRINT_EXPORT,
	PARAMS_PRINT_READONLY
}	t_params_print_mode;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	params_init(t_params *params);
t_error	params_load(t_params *params, int argc, char **argv, char **envp);
void	params_free(t_params *params);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// @ret ERR_SHELL_NOT_FOUND / ERR_LIBC
t_error params_print(t_params_print_mode mode);

// @warning: caller owns *dst, he must free it (if not NULL).
// @warning: *dst_val can be NULL if var->value == NULL (error will be ERR_NO).
// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_INVALID_NAME / ERR_VAR_NOT_FOUND
// 		/ ERR_LIBC.
t_error	params_get(const char *name, char **dst);

// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_NOT_FOUND
t_error	params_get_positionals(t_positionals *dst);

// value can be NULL.
// export == false and rdonly == false are ignored if variable already exists.
// if variable doesn't exist yet and option_is_active(OPT_EXPORT_ALL)
// 		=> export will be set to true even if export == false.
// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY
// 		/ ERR_LIBC.
t_error	params_set_variable(
	const char *name,
	const char *value,
	bool export,
	bool readonly);

// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY /
// 		ERR_INDEX_OUT_OF_BOUND
t_error	params_unset_variable(const char *name);

// @ret ERR_SHELL_NOT_FOUND.
t_error	params_set_last_bg_pid(pid_t value);

// @ret ERR_SHELL_NOT_FOUND.
t_error	params_set_last_status(int value);

// @ret ERR_SHELL_NOT_FOUND.
t_error	params_set_option(t_option option, bool on);

// @note src becomes owned by params module (on success only).
// @ret ERR_SHELL_NOT_FOUND / ERR_LIBC.
t_error	params_push_positionals(t_positionals *src);

// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_NOT_FOUND / ERR_SHIFT_INVALID_VALUE.
t_error	params_shift_positionals(size_t n);

// @note src becomes owned by params module (on success only).
// @warning src must not alias any frame already owned by stack.
// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_NOT_FOUND / ERR_LIBC.
t_error	params_replace_positionals(t_positionals *src);

// @ret ERR_SHELL_NOT_FOUND / ERR_LIBC.
t_error	params_pop_positionals(void);

// @ret ERR_SHELL_NOT_FOUND / ERR_LIBC
t_error	params_build_envp(char ***dst_envp);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

void	params_dump(void);

#endif

```

./includes/posix_helpers.h
```c
#ifndef POSIX_HELPERS_H
# define POSIX_HELPERS_H

# include "error.h"
# include <stddef.h>

# define PWD_UNSPECIFIED_VALUE	"undefined (access error)"

// @warning in case of EACCES:
// 			returns ERR_NO and sets *dst to PWD_UNSPECIFIED_VALUE
// @ret ERR_LIBC
t_error	posix_getcwd(char **dst);

// @ret ERR_LIBC
t_error	posix_write(int fd, const char *buff, size_t len);

#endif

```

./includes/runner.h
```c
#ifndef RUNNER_H
# define RUNNER_H

# include "error.h"

typedef struct s_runner
{
	// TODO;
}	t_runner;

void	runner_init(t_runner *runner);
t_error	runner_run(t_runner *runner);
void	runner_free(t_runner *runner);

#endif

```

./includes/scanner.h
```c
#ifndef SCANNER_H
# define SCANNER_H

# include "error.h"
# include "token.h"
# include "heredoc.h"
# include "lexer_.h"

/** @defgroup scanner Scanner API
 *  @brief Turns raw shell input into a POSIX token stream.
 *
 *  The scanner is the front end of the shell: it reads input incrementally
 *  (from a file, a command string or standard input), drives the lexer to
 *  recognise one token at a time following POSIX token recognition rules, and
 *  collects the here-documents the parser reports along the way. It also
 *  triggers alias expansion on word tokens by pushing the expansion back onto
 *  the lexer's input stack.
 *
 *  The lexer is held behind an opaque pointer (@ref t_lexer is incomplete
 *  here), so consumers of this header see only the scanner's public surface;
 *  the lexer internals stay private to the scanner module. The scanner owns
 *  its lexer and here-document state: scanner_init() allocates them and
 *  scanner_free() releases them.
 */

/**
 * @ingroup scanner
 * @enum e_scanner_mode
 * @brief Where the scanner reads its input from.
 */
typedef enum e_scanner_mode
{
	SCAN_NONE,		/**< Unset / not yet loaded. */
	SCAN_FILE,		/**< Read the whole input from a file path. */
	SCAN_STDIN,		/**< Read input line-by-line from standard input. */
	SCAN_STRING		/**< Read the input from an in-memory command string. */
}	t_scanner_mode;

/**
 * @ingroup scanner
 * @struct s_scanner
 * @brief Aggregate state of the scanner module.
 *
 * @var s_scanner::err Last error recorded by the module.
 * @var s_scanner::mode Source the input is read from (file, stdin, string).
 * @var s_scanner::lexer Owned lexer state (opaque; allocated by scanner_init).
 * @var s_scanner::source Borrowed file path or command string for FILE/STRING
 *                        modes; unused for STDIN.
 * @var s_scanner::heredoc Owned here-document collector for the pending queue.
 */
typedef struct s_scanner
{
	t_error			err;
	t_scanner_mode	mode;
	t_lexer			lexer;
	const char		*source;
	t_heredoc		heredoc;
}	t_scanner;

/**
 * @ingroup scanner
 * @brief Initialises a scanner to an empty, ready-to-use value.
 *
 * Zeroes the structure, allocates and initialises the lexer, and initialises
 * the here-document collector. Must be called before scanner_load() or
 * scanner_get_next_token().
 *
 * @param state Pointer to the scanner state to initialise (borrowed).
 * @return ERR_NO on success, ERR_LIBC if the lexer allocation fails.
 */
t_error	scanner_init(t_scanner *state);

/**
 * @ingroup scanner
 * @brief Releases every resource held by a scanner state.
 *
 * Frees the lexer (its contents and the allocation itself) and the
 * here-document collector, then resets the structure to zero.
 *
 * @param state Pointer to the scanner state to free (borrowed).
 */
void	scanner_free(t_scanner *state);

/**
 * @ingroup scanner
 * @brief Selects the input source for the next scan.
 *
 * Records the mode and, for FILE/STRING modes, the borrowed source string,
 * and propagates the interactivity flag to the lexer and the here-document
 * collector (true only for STDIN mode).
 *
 * @param state Pointer to the scanner state (borrowed).
 * @param mode Where to read input from.
 * @param source File path (FILE) or command string (STRING), borrowed; unused
 *               for STDIN.
 * @return The error currently recorded on the scanner.
 */
t_error	scanner_load(t_scanner *state, t_scanner_mode mode, const char *source);

t_error	scanner_reset(t_scanner *state);

/**
 * @ingroup scanner
 * @brief Produces the next token from the input.
 *
 * Reads more input when the current input is exhausted, asks the lexer for one
 * token, and on the way: stores pending here-document bodies after a newline,
 * and expands aliases on word tokens. Yields a token of type EOF_ once the
 * input is fully consumed. Operates on the global shell scanner state.
 *
 * @param token Out-parameter for the next token, is intialized during lexing.
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell scanner state is
 *         unavailable, or the recorded error on failure.
 */
t_error	scanner_get_next_token(t_token *token);

/**
 * @ingroup scanner
 * @brief Queues a here-document read reported by the parser.
 *
 * Enqueues a here-document with its target path, delimiter and mode so its
 * body is collected when the current line's newline is reached. Operates on
 * the global shell scanner state.
 *
 * @param path Out/in-parameter for the here-document target path (borrowed).
 * @param delim Here-document delimiter word (borrowed).
 * @param mode Here-document mode (e.g. tab-stripping for <<-).
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell scanner state is
 *         unavailable, or the recorded error on failure.
 */
t_error	scanner_report_io_here(char **path, char *delim, t_heredoc_mode mode);

t_error	scanner_heredoc_read(void);

#endif

```

./includes/shell.h
```c
#ifndef SHELL_H
# define SHELL_H

# include <stdint.h>
# include "alias.h"
# include "params.h"
# include "runner.h"
# include "history.h"
# include "scanner.h"
# include "heredoc.h"
# include "builder.h"

typedef struct s_shell
{
	t_alias		alias;
	t_builder	builder;
	t_heredoc	heredoc;
	t_history	history;
	t_params	params;
	t_runner	runner;
	t_scanner	scanner;
}	t_shell;

t_error		shell_run(int argc, char **argv, char **envp);
t_shell		*shell_get(void);
const char	*shell_get_name(void);
void		shell_free(void);
void		shell_exit_on_veof(void);	// TODO: remove

// Les fonctions pour les enfaaaaaants

t_alias		*shell_get_alias(void);
t_builder	*shell_get_builder(void);
t_heredoc	*shell_get_heredoc(void);
t_history	*shell_get_history(void);
t_params	*shell_get_params(void);
t_runner	*shell_get_runner(void);
t_scanner	*shell_get_scanner(void);

#endif

```

./includes/token.h
```c
#ifndef TOKEN_H
# define TOKEN_H

# include "error.h"
# include "libft.h"
# include "context.h"

/** @defgroup token Token API
 *  @brief Lexical tokens produced by the scanner.
 *
 *  A token couples a grammar type with the raw text that produced it. The
 *  text lives in an owned, growable buffer, so a token owns its value and
 *  token_dup() hands out an independent deep copy.
 *
 *  A word token also carries the expansion constructs found while scanning it
 *  (${ }, $(( )), ` `), in the left-to-right order their openings appeared, each
 *  marked with its [start, end) range inside the value buffer, so the expansion
 *  phase can locate every construct without rescanning the word.
 */

/**
 * @ingroup token
 * @enum e_token_type
 * @brief Grammar type of a token, using the POSIX shell token names.
 */
typedef enum e_token_type
{
	TOKEN_NONE,			/**< Unset / placeholder type. */
	TOKEN_TOKEN,		/**< A word token (command name, argument, ...). */
	TOKEN_NEWLINE,		/**< A newline. */
	TOKEN_SCOLON,		/**< ';' command separator. */
	TOKEN_AMPERSAND,	/**< '&' background / async operator. */
	TOKEN_DSEMI,		/**< ';;' case-list terminator. */
	TOKEN_SEMI_AND,		/**< ';&' case fall-through terminator. */
	TOKEN_AND_IF,		/**< '&&' logical AND. */
	TOKEN_OR_IF,		/**< '||' logical OR. */
	TOKEN_PIPE,			/**< '|' pipe. */
	TOKEN_LPARENTHESIS,	/**< '(' subshell open. */
	TOKEN_RPARENTHESIS,	/**< ')' subshell close. */
	TOKEN_LESSAND,		/**< '<&' duplicate input descriptor. */
	TOKEN_GREATAND,		/**< '>&' duplicate output descriptor. */
	TOKEN_LESS,			/**< '<' input redirection. */
	TOKEN_GREAT,		/**< '>' output redirection. */
	TOKEN_CLOBBER,		/**< '>|' forced output redirection. */
	TOKEN_LESSGREAT,	/**< '<>' open for reading and writing. */
	TOKEN_DGREAT,		/**< '>>' appending output redirection. */
	TOKEN_DLESS,		/**< '<<' here-document. */
	TOKEN_DLESSDASH,	/**< '<<-' tab-stripped here-document. */
	TOKEN_IO_NUMBER,	/**< Solely digits and the delimiter character is '<' or '>' */
	TOKEN_IO_LOCATION,	/**< At least three characters, begins with '{' and ends '}', and the delimiter character is '<' or '>' */
	TOKEN_EOF			/**< End of input. */
}	t_token_type;

/**
 * @ingroup token
 * @struct s_token
 * @brief A grammar type paired with the raw text it was scanned from.
 *
 * @var s_token::type Grammar type of the token.
 * @var s_token::value Owned, growable buffer holding the token text.
 * @var s_token::contexts Expansion constructs found in the value, in appearance
 *                        order, each with its [start, end) range; owns its
 *                        items.
 */
typedef struct s_token
{
	t_token_type	type;
	t_buff			value;
	t_context_stack	contexts;
}	t_token;

/**
 * @ingroup token
 * @brief Initialises a token to an empty word with an empty value buffer.
 *
 * @param token Pointer to the token to initialise (borrowed).
 */
void	token_init(t_token *token);

/**
 * @ingroup token
 * @brief Frees the token's value buffer and resets it to zero.
 *
 * @param token Pointer to the token to free (borrowed).
 */
void	token_free(t_token *token);

/**
 * @ingroup token
 * @brief Deep copies a token into another.
 *
 * Duplicates @p src's value buffer and deep-copies its context list into
 * @p dst, and copies its type, so @p dst owns an independent copy and @p src is
 * left untouched.
 *
 * @param dst Destination token receiving the copy (borrowed).
 * @param src Source token to copy (borrowed).
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	token_dup(t_token *dst, t_token *src);

#endif

```

./includes/types.h
```c
#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include <sys/stat.h>

typedef char	*t_file_path;

typedef union u_const_cast
{
	const char	*const_input;
	char		*input;
}	t_const_cast;

typedef struct stat	__stat_;

#endif

```

./includes/utils.h
```c
#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "error.h"
# include <pwd.h>
# include <time.h>
# include "error.h"

time_t	get_now_unix_seconds(void);

bool	name_is_valid(const char *name);

// @ret ERR_ASSIGNMENT_MISSING_NAME / ERR_LIBC
t_error assignment_split(const char *src, char **dst_name, char **dst_value);

// @ret ERR_LIBC
t_error serialize(const char *src, char **dst);

// @ret ERR_INVALID_FORMAT / ERR_LIBC
t_error deserialize(const char *src, char **dst);

// @ret ERR_LIBC
t_error	deserialize_all(const char *src, t_vector *dst);

// home/user lookup reimplemented over /etc/passwd (getpwnam is forbidden).
// Returns a pointer to static storage (invalidated by the next call), or NULL
// when name is NULL, the file cannot be read, or no matching entry exists.
struct passwd	*ft_getpwnam(const char *name);

#endif

```

./libft/libft.h
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:34:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/24 05:39:28 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stddef.h>
# include <stdbool.h>
# include <sys/types.h>

# define BUFFER_SIZE		128
# define VECTOR_INIT_CAP	16

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

/**
 * @struct s_buff
 * @brief Dynamic buffer structure for efficient string/data manipulation.
 *
 * @var s_buff::data Pointer to the allocated data (owned by the buffer).
 * @var s_buff::cap Current allocated capacity.
 * @var s_buff::len Current length of data in the buffer.
 */
typedef struct s_buff
{
	/** @brief Pointer to the allocated data (owned by the buffer). */
	char	*data;
	/** @brief Current allocated capacity (in bytes). */
	size_t	cap;
	/** @brief Current length of data in the buffer (in bytes). */
	size_t	len;
}	t_buff;

/**
 * @struct s_node
 * @brief Doubly linked list node structure.
 *
 * @var s_node::content Pointer to the node's content (owned by the node).
 * @var s_node::prev Pointer to the previous node (borrowed, may be NULL).
 * @var s_node::next Pointer to the next node (borrowed, may be NULL).
 */
typedef struct s_node
{
	/** @brief Pointer to the node's content (owned by the node). */
	void			*content;
	/** @brief Pointer to the previous node (borrowed, may be NULL). */
	struct s_node	*prev;
	/** @brief Pointer to the next node (borrowed, may be NULL). */
	struct s_node	*next;
}	t_node;

/**
 * @typedef t_list
 * @brief Type alias for a pointer to a list node (list head).
 */
typedef t_node	*t_list;

/**
 * @struct s_btree_node
 * @brief Binary tree node structure.
 *
 * @var s_btree_node::parent Pointer to the parent node (borrowed, may be NULL).
 * @var s_btree_node::left Pointer to the left child (borrowed, may be NULL).
 * @var s_btree_node::right Pointer to the right child (borrowed, may be NULL).
 * @var s_btree_node::data Pointer to node payload (owned by the node, may be NULL).
 */
typedef struct s_btree_node
{
	/** @brief Pointer to the parent node (borrowed, may be NULL). */
	struct s_btree_node	*parent;
	/** @brief Pointer to the left child (borrowed, may be NULL). */
	struct s_btree_node	*left;
	/** @brief Pointer to the right child (borrowed, may be NULL). */
	struct s_btree_node	*right;
	/** @brief Pointer to node payload (owned by the node, may be NULL). */
	void				*data;
}	t_btree_node;

/**
 * @struct s_vector
 * @brief Dynamic array storing contiguous fixed-size items.
 *
 * The vector owns a single allocated memory block containing items stored
 * contiguously, with no gaps between them.
 *
 * @var s_vector::data Pointer to the allocated contiguous array of items
 *                     (owned by the vector, may be NULL).
 * @var s_vector::cap Current allocated capacity, expressed in items.
 * @var s_vector::len Current number of stored items, expressed in items.
 * @var s_vector::item_size Size of each item, expressed in bytes.
 */
typedef struct s_vector
{
	/** @brief Pointer to the allocated contiguous array of items
	*         (owned by the vector, may be NULL).
	*/
	void	*data;
	/** @brief Current allocated capacity, expressed in items. */
	size_t	cap;
	/** @brief Current number of stored items, expressed in items. */
	size_t	len;
	/** @brief Size of each item, expressed in bytes. */
	size_t	item_size;
}	t_vector;

/** @brief Default number of buckets allocated by hashmap_init(). */
#define HASHMAP_INIT_CAP	50

/**
 * @struct s_key_value
 * @brief Key/value pair stored inside a hashmap bucket.
 *
 * A pair owns a private copy of its key (duplicated on creation) and takes
 * ownership of the value pointer it is given. Both are released when the pair
 * is destroyed (the value through the map's del callback).
 *
 * @var s_key_value::key Heap-allocated copy of the key string (owned by the
 *                       pair).
 * @var s_key_value::value Pointer to the stored value (owned by the pair,
 *                         released through the map's del callback).
 */
typedef struct s_key_value
{
	/** @brief Heap-allocated copy of the key string (owned by the pair). */
	char	*key;
	/** @brief Pointer to the stored value (owned by the pair). */
	void	*value;
}	t_key_value;

/**
 * @struct s_hashmap
 * @brief Separate-chaining hash map keyed by NUL-terminated strings.
 *
 * Collisions are resolved by chaining key/value pairs into doubly linked lists
 * (one list per bucket). The bucket array is stored in a t_vector and grows
 * automatically when the number of stored pairs would exceed its capacity.
 *
 * @var s_hashmap::size Current number of stored key/value pairs.
 * @var s_hashmap::buckets Vector of t_list buckets, each a chain of
 *                         t_key_value pairs (owned by the map).
 * @var s_hashmap::hash Hash function applied to keys (defaults to
 *                      hash_string).
 * @var s_hashmap::del_value Optional destructor for stored values (may be
 *                           NULL, in which case values are never freed).
 */
typedef struct s_hashmap
{
	/** @brief Current number of stored key/value pairs. */
	size_t		size;
	/** @brief Vector of t_list buckets (owned by the map). */
	t_vector	buckets;
	/** @brief Hash function applied to keys (defaults to hash_string). */
	size_t		(*hash)(const char *key);
	/** @brief Optional destructor for stored values (may be NULL). */
	void		(*del_value)(void *);
}	t_hashmap;

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup btree Binary Tree API
 *  @brief Binary tree node utilities.
 *
 *  Functions to create, link, detach and recursively free binary tree nodes.
 */

/** @defgroup buff Buffer API
 *  @brief Dynamic growable buffer utilities.
 *
 *  Functions to initialize, grow, shrink and manipulate dynamic buffers.
 */

/** @defgroup chr Character Functions
 *  @brief Character classification and conversion.
 *
 *  Functions to test and transform individual characters.
 */

/** @defgroup conv Conversion Functions
 *  @brief String/number conversion utilities.
 *
 *  Functions to convert between strings and numeric types.
 */

/** @defgroup error Error Functions
 *  @brief Error reporting utilities.
 *
 *  Functions to print formatted error messages to stderr.
 */

/** @defgroup hashmap Hashmap API
 *  @brief String-keyed hash map with separate chaining.
 *
 *  Functions to create, populate, query and destroy a hash map that maps
 *  NUL-terminated string keys to arbitrary value pointers.
 */

/** @defgroup list Linked List API
 *  @brief Doubly linked list utilities.
 *
 *  Functions to create, manipulate and traverse doubly linked lists.
 */

/** @defgroup malloc Memory Allocation
 *  @brief Memory allocation utilities.
 *
 *  Functions for allocating and reallocating memory.
 */

/** @defgroup math Math Functions
 *  @brief Mathematical utilities.
 *
 *  Functions for common mathematical operations.
 */

/** @defgroup mem Memory Functions
 *  @brief Low-level memory operations.
 *
 *  Functions to manipulate raw memory blocks.
 */

/** @defgroup print Print Functions
 *  @brief Formatted output utilities.
 *
 *  Printf-like functions for formatted output to file descriptors.
 */

/** @defgroup put Put Functions
 *  @brief Basic output functions.
 *
 *  Functions to write characters, strings and numbers to file descriptors.
 */

/** @defgroup str String Functions
 *  @brief String manipulation utilities.
 *
 *  Functions to search, copy, compare and transform strings.
 */

/** @defgroup vector Vector API
 *  @brief Dynamic array utilities for contiguous fixed-size items.
 *
 *  Functions to initialize, grow, shrink, duplicate and manipulate dynamic
 *  arrays storing items contiguously in memory.
 */

/* ************************************************************************* */
/*                                  BTREE                                    */
/* ************************************************************************* */

/**
 * @ingroup btree
 * @brief Creates a new binary tree node.
 *
 * @note Ownership of data is transferred to the new node on success.
 *       On failure, caller retains ownership of data.
 *
 * @param data Payload for the new node (ownership transferred on success).
 * @return Pointer to the new node (owned), or NULL on allocation failure.
 */
t_btree_node	*btree_new(void *data);

/**
 * @ingroup btree
 * @brief Sets the left child of a parent node.
 *
 * Links child under parent and updates child->parent accordingly.
 *
 * @warning parent and child must not be NULL.
 *
 * @param parent Parent node to update (borrowed).
 * @param child Child node to attach as left child (borrowed).
 */
void			btree_set_left(t_btree_node *parent, t_btree_node *child);

/**
 * @ingroup btree
 * @brief Sets the right child of a parent node.
 *
 * Links child under parent and updates child->parent accordingly.
 *
 * @warning parent and child must not be NULL.
 *
 * @param parent Parent node to update (borrowed).
 * @param child Child node to attach as right child (borrowed).
 */
void			btree_set_right(t_btree_node *parent, t_btree_node *child);

/**
 * @ingroup btree
 * @brief Detaches and returns the left child of a parent node.
 *
 * Updates both parent->left and the detached child's parent pointer to NULL.
 *
 * @warning parent and parent->left must not be NULL.
 *
 * @param parent Parent node to detach from (borrowed).
 * @return Detached left child node (owned by caller), or NULL if none.
 */
t_btree_node	*btree_detach_left(t_btree_node *parent);

/**
 * @ingroup btree
 * @brief Detaches and returns the right child of a parent node.
 *
 * Updates both parent->right and the detached child's parent pointer to NULL.
 *
 * @warning parent and parent->right must not be NULL.
 *
 * @param parent Parent node to detach from (borrowed).
 * @return Detached right child node (owned by caller), or NULL if none.
 */
t_btree_node	*btree_detach_right(t_btree_node *parent);

/**
 * @ingroup btree
 * @brief Recursively frees a node and its descendants.
 *
 * Performs a post-order traversal and frees each node. If data_free is
 * provided, it is called for each non-NULL node payload before node free.
 *
 * @param node Pointer to the root node pointer (set to NULL after freeing).
 * @param data_free Optional payload destructor (can be NULL).
 */
void			btree_free(t_btree_node **node, void (*data_free)(void *data));

/* ************************************************************************* */
/*                                   BUFF                                    */
/* ************************************************************************* */

/**
 * @ingroup buff
 * @brief Initializes a buffer with the specified initial capacity.
 *
 * If str is not NULL, it is appended after initialization.
 * If str is NULL, n is ignored.
 *
 * @note Cannot fail only when initial_cap == 0 and str == NULL.
 *
 * @param b Pointer to the buffer structure to initialize (uninitialized).
 * @param initial_cap Initial capacity of the buffer.
 * @param str Optional string to append after initialization (borrowed).
 * @param n Number of bytes to append, or -1 to use str_len(str).
 * @return true on success, false on memory allocation failure.
 */
bool	buff_init(t_buff *b, size_t initial_cap, const char *str, long n);

/**
 * @ingroup buff
 * @brief Shrinks buffer capacity to match its current length.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @return true on success, false on memory allocation failure.
 */
bool	buff_adjust(t_buff *buff);

/**
 * @ingroup buff
 * @brief Frees the buffer's internal data.
 *
 * Sets buff->data to NULL after freeing.
 * Sets buff->len and buff->cap to 0 after freeing.
 *
 * @warning Does not free the t_buff struct itself, only its internal data.
 *
 * @param b Pointer to the buffer (borrowed).
 */
void	buff_free(t_buff *b);

/**
 * @ingroup buff
 * @brief Frees a t_buff item through a generic void* callback signature.
 *
 * Wrapper around buff_free() intended for APIs that expect
 * `void (*)(void *)`, such as vector_free().
 *
 * @warning buff must point to an initialized t_buff.
 * @warning Does not free the t_buff struct itself, only its internal data.
 *
 * @param buff Pointer to a t_buff item passed as void* (borrowed).
 */
void	buff_free_void(void *buff);

/**
 * @ingroup buff
 * @brief Finds the index of a character in the buffer.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @param c Character to find.
 * @return Index of the character, or -1 if not found.
 */
int		buff_get_index(t_buff *buff, char c);

/**
 * @ingroup buff
 * @brief Returns a newly allocated copy of the buffer content.
 *
 * If the buffer data is not null-terminated, a trailing '\0' is added in the
 * returned string.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @note Caller owns the returned string and must free it.
 * @note The caller remains owner of the t_buff.
 * @note The t_buff remains owner of the buff->data.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @return Newly allocated string (owned by caller), or NULL on failure.
 */
char	*buff_get_string(t_buff *buff);

/**
 * @ingroup buff
 * @brief Prepends a string to the beginning of the buffer.
 *
 * Buffer is automatically grown if necessary.
 *
 * @warning b must be initialized before calling this function.
 * @warning UB if n > 0 and str is shorter than n bytes.
 *
 * @param b Pointer to an initialized buffer (borrowed).
 * @param str String to prepend (borrowed, not modified).
 * @param n Number of bytes to prepend, or -1 to use strlen(str).
 * @return true on success, false on memory allocation failure.
 */
bool	buff_prepend(t_buff *b, const char *str, long n);

/**
 * @ingroup buff
 * @brief Inserts a string at a specific index in the buffer.
 *
 * Buffer is automatically grown if necessary.
 *
 * @warning b must be initialized before calling this function.
 * @warning UB if index > b->len.
 * @warning UB if n > 0 and str is shorter than n bytes.
 *
 * @param b Pointer to an initialized buffer (borrowed).
 * @param index Position at which to insert the string.
 * @param str String to insert (borrowed, not modified).
 * @param n Number of bytes to insert, or -1 to use strlen(str).
 * @return true on success, false on memory allocation failure.
 */
bool	buff_insert(t_buff *b, size_t index, const char *str, long n);

/**
 * @ingroup buff
 * @brief Appends a string to the end of the buffer.
 *
 * Buffer is automatically grown if necessary.
 *
 * @warning b must be initialized before calling this function.
 * @warning UB if n > 0 and str is shorter than n bytes.
 *
 * @param b Pointer to an initialized buffer (borrowed).
 * @param str String to append (borrowed, not modified).
 * @param n Number of bytes to append, or -1 to use strlen(str).
 * @return true on success, false on memory allocation failure.
 */
bool	buff_append(t_buff *b, const char *str, long n);

/**
 * @ingroup buff
 * @brief Copies up to n bytes from a source buffer into an existing buffer.
 *
 * @warning dst and src must be initialized before calling this function.
 * @warning The previous logical content of dst is replaced, whether the
 *          function succeeds or fails.
 *
 * @param dst Destination buffer to overwrite (borrowed, initialized).
 * @param src Source buffer to duplicate (borrowed, initialized).
 * @param n Maximum number of bytes to copy.
 * @return true on success, false on memory allocation failure.
 */
bool	buff_dup_n(t_buff *dst, const t_buff *src, size_t n);

/**
 * @ingroup buff
 * @brief Removes a portion of the buffer starting at i_start.
 *
 * @note If len < 0, deletes all buffer content from i_start to end.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @param i_start Starting index for removal.
 * @param len Number of bytes to remove, or negative to remove until end.
 */
void	buff_rm_part(t_buff *buff, size_t i_start, ssize_t len);

/**
 * @ingroup buff
 * @brief Appends formatted string to buffer using variadic arguments.
 *
 * > Supports printf formats: 
 * `%%c` `%%s` `%%d` `%%i` `%%u` `%%x` `%%X` `%%p` `%%`.  
 * > Supports printf-like flags: `-` `0` `.` ` ` `#` `+` and width.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @param fstring Format string (borrowed).
 * @param ... Variadic arguments for format specifiers.
 * @return true on success, false on failure.
 */
bool	buff_append_format(t_buff *buff, const char *fstring, ...)
		__attribute__((format(printf, 2, 3)));

/**
 * @ingroup buff
 * @brief Appends formatted string to buffer using va_list.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @param fstring Format string (borrowed).
 * @param args Variable argument list.
 * @return true on success, false on failure.
 */
bool	buff_append_vformat(t_buff *buff, const char *fstring, va_list args);

/**
 * @ingroup buff
 * @brief Reads from a file descriptor until a specific character is found.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @param fd File descriptor to read from.
 * @param c Character to search for.
 * @return Index of c (>= 0), -1 if EOF reached before c, -2 on error.
 */
int		buff_read_until(t_buff *buff, int fd, char c);

/**
 * @ingroup buff
 * @brief Reads all available data from a file descriptor into buffer.
 *
 * @note On failure, buff->data is NOT automatically freed.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @param fd File descriptor to read from.
 * @return true on success, false if read failed.
 */
bool	buff_read_all(t_buff *buff, int fd);


/* ************************************************************************* */
/*                                 HASHMAP                                   */
/* ************************************************************************* */

/**
 * @ingroup hashmap
 * @brief Initializes an empty hash map.
 *
 * Allocates the initial bucket array (HASHMAP_INIT_CAP buckets) and installs
 * the default string hash function. The del callback is stored as-is and used
 * to release stored values; the map does not own del itself.
 *
 * @note On failure the map is left in a zeroed state and must not be used.
 *
 * @param map Pointer to the map structure to initialize (uninitialized).
 * @param initial_cap Initial capacity of the bucket array.
 * @param del Optional destructor applied to each value on removal/free.
 *            Pass NULL to never free stored values.
 * @return true on success, false on memory allocation failure.
 */
bool	hashmap_init(t_hashmap *map, size_t initial_cap, void (*del)(void *));

/**
 * @ingroup hashmap
 * @brief Frees a hash map and all of its contents.
 *
 * Releases every stored pair: each key copy is freed, each value is passed to
 * the map's del callback (if any), and the bucket array is freed. The map is
 * reset to a zeroed state afterwards.
 *
 * @param map Pointer to the map to free (borrowed; reset to zero on return).
 */
void	hashmap_free(t_hashmap *map);

/**
 * @ingroup hashmap
 * @brief Inserts a key/value pair, replacing any existing value for the key.
 *
 * The key is duplicated internally, so the caller keeps ownership of the key
 * buffer. If the key already exists, its previous value is released through
 * the map's del callback before the new value takes its place. The bucket
 * array grows automatically when needed.
 *
 * @note On success, ownership of value is transferred to the map and is
 *       released through the del callback on removal or on hashmap_free().
 *
 * @note On failure, ownership of value remains with the caller.
 *
 * @note If key already exists and value is the same pointer as the currently
 *       stored value, hashmap_put() is a no-op and returns true.
 *
 * @warning When del is not NULL, each stored value pointer must have unique
 *          ownership. Storing the same owned pointer under several different
 *          keys can cause a double free on removal or hashmap_free().
 *
 * @param map Pointer to an initialized map (borrowed).
 * @param key NUL-terminated key (borrowed; duplicated internally).
 * @param value Value to associate with key (ownership transferred on success).
 * @return true on success, false on memory allocation failure.
 */
bool	hashmap_put(t_hashmap *map, const char *key, void *value);

/**
 * @ingroup hashmap
 * @brief Retrieves the value associated with a key.
 *
 * @param map Pointer to an initialized map (borrowed).
 * @param key NUL-terminated key to look up (borrowed).
 * @return The associated key/value pair (borrowed, still owned by the map),
 *         or NULL if the key is not present.
 */
t_key_value	*hashmap_get(t_hashmap *map, const char *key);

/**
 * @ingroup hashmap
 * @brief Collects every key/value pair stored in the map.
 *
 * Builds a freshly allocated, NULL-terminated array holding a pointer to each
 * of the map's size pairs, in unspecified (bucket) order.
 *
 * @note The returned array is owned by the caller and must be freed with a
 *       single free(). The pairs it points to are borrowed and remain owned by
 *       the map; do not free them and do not use the array after the map (or
 *       any referenced pair) has been modified or freed.
 *
 * @param map Pointer to an initialized map (borrowed).
 * @return A NULL-terminated array of pair pointers (owned by caller), or NULL
 *         on memory allocation failure. The array is empty (only the NULL
 *         terminator) when the map holds no pairs.
 */
t_key_value	**hashmap_get_all(t_hashmap *map);

/**
 * @ingroup hashmap
 * @brief Removes the pair associated with a key.
 *
 * The matching pair is unlinked and freed: its key copy is freed and its value
 * is passed to the map's del callback (if any).
 *
 * @param map Pointer to an initialized map (borrowed).
 * @param key NUL-terminated key to remove (borrowed).
 * @return true if a pair was removed, false if the key was not found.
 */
bool	hashmap_remove(t_hashmap *map, const char *key);

/**
 * @ingroup hashmap
 * @brief Tests whether a key is present in the map.
 *
 * @param map Pointer to an initialized map (borrowed).
 * @param key NUL-terminated key to look for (borrowed).
 * @return true if the key is present, false otherwise.
 */
bool	hashmap_contains(t_hashmap *map, const char *key);


/* ************************************************************************* */
/*                                   CHR                                     */
/* ************************************************************************* */

/**
 * @ingroup chr
 * @brief Checks if a character is alphanumeric.
 *
 * @param c Character to check.
 * @return Non-zero if alphanumeric, 0 otherwise.
 */
int		ft_isalnum(int c);

/**
 * @ingroup chr
 * @brief Checks if a character is alphabetic.
 *
 * @param c Character to check.
 * @return Non-zero if alphabetic, 0 otherwise.
 */
int		ft_isalpha(int c);

/**
 * @ingroup chr
 * @brief Checks if a character is a valid ASCII character (0-127).
 *
 * @param c Character to check.
 * @return Non-zero if ASCII, 0 otherwise.
 */
int		ft_isascii(int c);

/**
 * @ingroup chr
 * @brief Checks if a character is a digit ('0'-'9').
 *
 * @param c Character to check.
 * @return Non-zero if digit, 0 otherwise.
 */
int		ft_isdigit(int c);

/**
 * @ingroup chr
 * @brief Checks if a character is present in a character set.
 *
 * @param c Character to check.
 * @param charset Null-terminated string of characters to match against.
 * @return true if found in charset, false otherwise.
 */
bool	ft_isincharset(char c, const char *charset);

/**
 * @ingroup chr
 * @brief Checks if a character is printable (32-126).
 *
 * @param c Character to check.
 * @return Non-zero if printable, 0 otherwise.
 */
int		ft_isprint(int c);

/**
 * @ingroup chr
 * @brief Checks if a character is whitespace (9-13).
 *
 * @param c Character to check.
 * @return Non-zero if whitespace, 0 otherwise.
 */
int		ft_isspace(char c);

/**
 * @ingroup chr
 * @brief Converts an uppercase letter to lowercase.
 *
 * @param c Character to convert.
 * @return Lowercase equivalent if uppercase, otherwise unchanged.
 */
int		ft_tolower(int c);

/**
 * @ingroup chr
 * @brief Converts a lowercase letter to uppercase.
 *
 * @param c Character to convert.
 * @return Uppercase equivalent if lowercase, otherwise unchanged.
 */
int		ft_toupper(int c);

/* ************************************************************************* */
/*                                   CONV                                    */
/* ************************************************************************* */

/**
 * @ingroup conv
 * @brief Converts a string to an integer.
 *
 * @param str String to convert.
 * @return The converted integer value.
 */
int		ft_atoi(const char *str);

/**
 * @ingroup conv
 * @brief Converts a string to a long integer.
 *
 * @param str String to convert.
 * @return The converted long value.
 */
long	ft_atol(const char *str);

/**
 * @ingroup conv
 * @brief Converts a string to a pid_t.
 *
 * @param str String to convert.
 * @return The converted pid_t value.
 */
pid_t	ft_atopid(const char *str);

/**
 * @ingroup conv
 * @brief Converts a string to a size_t.
 *
 * @note Skips leading whitespace and accepts an optional leading '+'.
 * @warning Returns SIZE_MAX on overflow.
 *
 * @param str String to convert.
 * @return The converted size_t value.
 */
size_t	ft_atozu(const char *str);

/**
 * @ingroup conv
 * @brief Converts an integer to a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param n Integer to convert.
 * @return Newly allocated string (owned), or NULL on failure.
 */
char	*ft_itoa(int n);

/**
 * @ingroup conv
 * @brief Converts an unsigned integer to a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param n Unsigned integer to convert.
 * @return Newly allocated string (owned), or NULL on failure.
 */
char	*ft_utoa(unsigned int n);

/**
 * @ingroup conv
 * @brief Converts a size_t to a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param n Value to convert.
 * @return Newly allocated string (owned), or NULL on failure.
 */
char	*ft_zutoa(size_t n);

/**
 * @ingroup conv
 * @brief Converts a long integer to a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param n Long integer to convert.
 * @return Newly allocated string (owned), or NULL on failure.
 */
char	*ft_ltoa(long n);

/**
 * @ingroup conv
 * @brief Converts a pid_t to a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param n pid_t value to convert.
 * @return Newly allocated string (owned), or NULL on failure.
 */
char	*ft_pidtoa(pid_t n);

/**
 * @ingroup conv
 * @brief Converts an unsigned long to a string in a given base.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param n Number to convert.
 * @param base String representing the base characters (borrowed, >= 2 chars).
 * @return Newly allocated string (owned), or NULL on failure.
 */
char	*ft_ultoa_base(unsigned long n, const char *base);

/**
 * @ingroup conv
 * @brief Parses a string to an integer with overflow detection.
 *
 * Accepts an optional leading '+' or '-' sign followed by digits.
 * Returns false if the string is empty, contains non-digit characters,
 * or the value would overflow an int.
 *
 * @param s String to parse (borrowed).
 * @param out Pointer to store the parsed integer (modified on success).
 * @return true on success, false if parsing failed or value out of range.
 */
bool	parse_int(char *s, int *out);

/* ************************************************************************* */
/*                                  ERROR                                    */
/* ************************************************************************* */

/**
 * @ingroup error
 * @brief Prints "Error\n" to stderr with optional message and errno.
 *
 * If print_errno is false and message is NULL, only "Error\n" is printed.
 * If print_errno is true, uses strerror() to print the errno description.
 * If message is not NULL, prints the message.
 * '\n' is always printed at the end.
 *
 * @param print_errno If true, prints errno description using strerror().
 * @param message Optional message to print (borrowed, can be NULL).
 */
void	print_err(bool print_errno, const char *message);

/**
 * @ingroup error
 * @brief Prints "Error\n" to stderr with safe prefix + formatted suffix.
 *
 * Prints safe prefix always, then attempts to format and append fmt.
 * If formatting fails, only the safe prefix is printed.
 * '\n' is always printed at the end.
 *
 * @warning safe and fmt must NOT be NULL, use print_err() otherwise.
 *
 * @param print_errno If true, prints errno description using strerror().
 * @param safe Safe prefix printed unconditionally (borrowed).
 * @param fmt Format string for suffix (borrowed).
 * @param ... Variadic arguments for format specifiers.
 */
void	fprint_err(bool print_errno, const char *safe, const char *fmt, ...)
		__attribute__((format(printf, 3, 4)));

/* ************************************************************************* */
/*                                   LIST                                    */
/* ************************************************************************* */

/**
 * @ingroup list
 * @brief Creates a new list node.
 *
 * @note Ownership of content is transferred to the node on success.
 *
 * @param content Content for the new node (ownership transferred).
 * @param prev Pointer to the previous node (borrowed, can be NULL).
 * @param next Pointer to the next node (borrowed, can be NULL).
 * @return Pointer to the new node (owned), or NULL on allocation failure.
 */
t_node	*node_new(void *content, t_node *prev, t_node *next);

/**
 * @ingroup list
 * @brief Frees a node and optionally its content.
 *
 * @param node Pointer to the node pointer (set to NULL after freeing).
 * @param del_content Function to delete the content (can be NULL to skip).
 */
void	node_free(t_node **node, void (*del_content)(void*));

/**
 * @ingroup list
 * @brief Adds a new element at the end of the list.
 *
 * @note Ownership of new_content is transferred to the list on success.
 *       On failure, caller retains ownership of new_content.
 *
 * @param list Pointer to the list pointer (borrowed).
 * @param new_content Content for the new node (ownership transferred).
 * @return true on success, false on allocation failure.
 */
bool	list_add_end(t_list *list, void *new_content);

/**
 * @ingroup list
 * @brief Adds a new element at the start of the list.
 *
 * @note Ownership of new_content is transferred to the list on success.
 *       On failure, caller retains ownership of new_content.
 *
 * @param list Pointer to the list pointer (borrowed).
 * @param new_content Content for the new node (ownership transferred).
 * @return true on success, false on allocation failure.
 */
bool	list_add_start(t_list *list, void *new_content);

/**
 * @ingroup list
 * @brief Calculates the number of nodes in the list.
 *
 * @param list List to count.
 * @return Number of nodes in the list.
 */
size_t	list_get_size(t_list list);

/**
 * @ingroup list
 * @brief Finds content in list matching a selection function.
 *
 * @note Returned pointer is borrowed from the list. Do not free it directly;
 *       the list retains ownership. Pointer becomes invalid if node is removed.
 *
 * @param list List to search (borrowed).
 * @param select_function Function returning true for desired content.
 * @return Matching content (borrowed), or NULL if not found.
 */
void	*list_get_content(t_list list, bool (*select_function)(void*));

/**
 * @ingroup list
 * @brief Gets content at a specific index in the list.
 *
 * @note Returned pointer is borrowed from the list. Do not free it directly;
 *       the list retains ownership. Pointer becomes invalid if node is removed.
 *
 * @param list List to search (borrowed).
 * @param index Zero-based index.
 * @return Content at index (borrowed), or NULL if index out of bounds.
 */
void	*list_get_content_n(t_list list, size_t index);

/**
 * @ingroup list
 * @brief Gets the content of the last node in the list.
 *
 * @note Returned pointer is borrowed from the list. Do not free it directly;
 *       the list retains ownership. Pointer becomes invalid if node is removed.
 *
 * @param list List to search (borrowed).
 * @return Content of last node (borrowed), or NULL if list is empty.
 */
void	*list_get_content_last(t_list list);

/**
 * @ingroup list
 * @brief Gets the node at a specific index in the list.
 *
 * @note Returned pointer is borrowed from the list. Do not free it directly;
 *       the list retains ownership. Pointer becomes invalid if node is removed.
 *
 * @param list List to search (borrowed).
 * @param index Zero-based index.
 * @return Node at index (borrowed), or NULL if index out of bounds.
 */
t_node	*list_get_node_n(t_list list, size_t index);

/**
 * @ingroup list
 * @brief Gets the last node in the list.
 *
 * @note Returned pointer is borrowed from the list. Do not free it directly;
 *       the list retains ownership. Pointer becomes invalid if node is removed.
 *
 * @param list List to search (borrowed).
 * @return Last node (borrowed), or NULL if list is empty.
 */
t_node	*list_get_node_last(t_list list);

/**
 * @ingroup list
 * @brief Applies a function to each element of the list.
 *
 * @param lst List to iterate over (borrowed).
 * @param f Function to apply to each element's content.
 */
void	list_iter(t_list lst, void (*f)(void *));

/**
 * @ingroup list
 * @brief Creates a new list by applying a function to each element.
 *
 * @note Caller owns the returned list and must free it with list_rm_all.
 *
 * @param list Source list (borrowed).
 * @param f Function to apply to each element (returns new content, owned).
 * @param del Function to delete content on failure.
 * @return New list (owned), or NULL on failure.
 */
t_list	list_map(t_list list, void *(*f)(void *), void (*del)(void *));

/**
 * @ingroup list
 * @brief Removes a specific node from the list.
 *
 * @param list Pointer to the list pointer (borrowed).
 * @param node Node to remove (ownership taken, will be freed).
 * @param del_content Function to delete the node's content (can be NULL).
 */
void	list_rm(t_list *list, t_node *node, void (*del_content)(void*));

/**
 * @ingroup list
 * @brief Removes all nodes from the list.
 *
 * @param list Pointer to the list pointer (set to NULL after).
 * @param del_content Function to delete each node's content (can be NULL).
 */
void	list_rm_all(t_list *list, void (*del_content)(void*));

/* ************************************************************************* */
/*                                  MALLOC                                   */
/* ************************************************************************* */

/**
 * @ingroup malloc
 * @brief Allocates and zeroes memory for an array.
 *
 * @note Caller owns the returned memory and must free it.
 *
 * @param count Number of elements.
 * @param size Size of each element.
 * @return Pointer to allocated zeroed memory (owned), or NULL on failure.
 */
void	*ft_calloc(size_t count, size_t size);

/**
 * @ingroup malloc
 * @brief Reallocates a buffer to a new capacity.
 *
 * @note If newcap is 0, *buff is freed and set to NULL.
 *
 * @param buff Pointer to the buffer pointer (owned, reallocated in place).
 * @param cap Current capacity.
 * @param newcap New capacity (0 to free the buffer).
 * @return true on success, false on failure (original buffer unchanged).
 */
bool	ft_realloc(char **buff, size_t cap, size_t newcap);

/* ************************************************************************* */
/*                                   MATH                                    */
/* ************************************************************************* */

/**
 * @ingroup math
 * @brief Returns the minimum of two long integers.
 *
 * @param a First long integer.
 * @param b Second long integer.
 * @return The smaller value.
 */
long	min(long a, long b);

/**
 * @ingroup math
 * @brief Returns the maximum of two long integers.
 *
 * @param a First long integer.
 * @param b Second long integer.
 * @return The larger value.
 */
long	max(long a, long b);

/**
 * @ingroup math
 * @brief Returns the absolute value of a long integer.
 *
 * @param nbr Number to get absolute value of.
 * @return Absolute value as size_t (always positive).
 */
size_t	absolute(long nbr);

/**
 * @ingroup math
 * @brief Computes a raised to the power of b.
 *
 * Uses bit shifting optimization when a == 2.
 *
 * @warning UB if the result overflows a long.
 * @warning Returns 0 for negative exponents (cannot represent fractions).
 *
 * @param a Base value.
 * @param b Exponent (must be >= 0 for meaningful result).
 * @return a^b, or 0 if b < 0.
 */
long	power(int a, int b);

/**
 * @ingroup math
 * @brief Computes the modulo of a signed integer with an unsigned modulus.
 *
 * Handles negative values of a by ensuring the result is always positive.
 *
 * @param a Dividend (can be negative).
 * @param b Divisor (must be > 0).
 * @return Remainder in range [0, b-1].
 */
size_t	modulo(long a, size_t b);

/**
 * @ingroup math
 * @brief Calculates the exact integer square root.
 *
 * @param nb Number to find square root of.
 * @return Exact square root if nb is a perfect square, -1 otherwise.
 */
int		square_root_exact(int nb);

/**
 * @ingroup math
 * @brief Calculates the nearest integer square root.
 *
 * @param nb Number to find square root of.
 * @return Nearest integer square root, -1 if nb <= 0.
 */
int		square_root_rounded(int nb);

/* ************************************************************************* */
/*                                   MEM                                     */
/* ************************************************************************* */

/**
 * @ingroup mem
 * @brief Sets n bytes of memory to zero.
 *
 * @param s Pointer to memory area.
 * @param n Number of bytes to set.
 */
void	ft_bzero(void *s, size_t n);

/**
 * @ingroup mem
 * @brief Locates the first occurrence of a byte in memory.
 *
 * @note Returned pointer is borrowed from s. Do not free it directly.
 *
 * @param s Memory area to search (borrowed).
 * @param c Byte to search for (converted to unsigned char).
 * @param n Number of bytes to search.
 * @return Pointer to the byte (borrowed), or NULL if not found.
 */
void	*ft_memchr(const void *s, int c, size_t n);

/**
 * @ingroup mem
 * @brief Compares two memory areas byte by byte.
 *
 * @param s1 First memory area.
 * @param s2 Second memory area.
 * @param n Number of bytes to compare.
 * @return Difference of first differing bytes, or 0 if equal.
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @ingroup mem
 * @brief Copies n bytes from src to dst.
 *
 * @warning Memory areas must not overlap. Use ft_memmove for overlapping.
 *
 * @param dst Destination memory area (borrowed).
 * @param src Source memory area (borrowed).
 * @param n Number of bytes to copy.
 * @return Pointer to dst.
 */
void	*ft_memcpy(void *dst, const void *src, size_t n);

/**
 * @ingroup mem
 * @brief Copies n bytes from src to dst, handling overlapping memory.
 *
 * @param dst Destination memory area.
 * @param src Source memory area.
 * @param len Number of bytes to copy.
 * @return Pointer to dst.
 */
void	*ft_memmove(void *dst, const void *src, size_t len);

/**
 * @ingroup mem
 * @brief Fills memory with a constant byte.
 *
 * @param b Memory area to fill.
 * @param c Byte value to set (converted to unsigned char).
 * @param len Number of bytes to set.
 * @return Pointer to b.
 */
void	*ft_memset(void *b, int c, size_t len);

/* ************************************************************************* */
/*                                  PRINT                                    */
/* ************************************************************************* */

/**
 * @ingroup print
 * @brief Writes formatted output to a file descriptor using va_list.
 *
 * @param fd File descriptor to write to.
 * @param fstring Format string.
 * @param args Variable argument list.
 * @return Number of bytes written, or -1 on error.
 */
int		ft_vdprintf(int fd, const char *fstring, va_list args);

/**
 * @ingroup print
 * @brief Writes formatted output to a file descriptor.
 *
 * > Supports printf formats: 
 * `%%c` `%%s` `%%d` `%%i` `%%u` `%%x` `%%X` `%%p` `%%`.  
 * > Supports printf-like flags: `-` `0` `.` ` ` `#` `+` and width.
 *
 * @param fd File descriptor to write to.
 * @param fstring Format string.
 * @param ... Variadic arguments for format specifiers.
 * @return Number of bytes written, or -1 on error.
 */
int		ft_dprintf(int fd, const char *fstring, ...)
		__attribute__((format(printf, 2, 3)));

/**
 * @ingroup print
 * @brief Writes formatted output to stdout using va_list.
 *
 * @param fstring Format string.
 * @param args Variable argument list.
 * @return Number of bytes written, or -1 on error.
 */
int		ft_vprintf(const char *fstring, va_list args);

/**
 * @ingroup print
 * @brief Writes formatted output to stdout.
 *
 * > Supports printf formats: 
 * `%%c` `%%s` `%%d` `%%i` `%%u` `%%x` `%%X` `%%p` `%%`.  
 * > Supports printf-like flags: `-` `0` `.` ` ` `#` `+` and width.
 *
 * @param fstring Format string.
 * @param ... Variadic arguments for format specifiers.
 * @return Number of bytes written, or -1 on error.
 */
int		ft_printf(const char *fstring, ...)
		__attribute__((format(printf, 1, 2)));

/* ************************************************************************* */
/*                                   PUT                                     */
/* ************************************************************************* */

/**
 * @brief Writes a character to a file descriptor.
 *
 * @param c Character to write.
 * @param fd File descriptor to write to.
 */
void	ft_putchar_fd(char c, int fd);

/**
 * @ingroup put
 * @brief Writes a string followed by newline to a file descriptor.
 *
 * @param s String to write (NULL prints "(null)").
 * @param fd File descriptor to write to.
 */
void	ft_putendl_fd(char *s, int fd);

/**
 * @ingroup put
 * @brief Writes an integer to a file descriptor.
 *
 * @param n Integer to write.
 * @param fd File descriptor to write to.
 */
void	ft_putnbr_fd(int n, int fd);

/**
 * @ingroup put
 * @brief Writes a string to a file descriptor.
 *
 * @param s String to write (NULL prints "(null)").
 * @param fd File descriptor to write to.
 */
void	ft_putstr_fd(char *s, int fd);

/* ************************************************************************* */
/*                                   STR                                     */
/* ************************************************************************* */

/**
 * @brief Frees all strings in a null-terminated array and the tab itself.
 *
 * @note The tab is set at NULL after beeing freed.
 *
 * @param tab Array of strings to free.
 */
void	str_array_free(char ***tab_ptr);

/**
 * @ingroup str
 * @brief Locates the first occurrence of a character in a string.
 *
 * @note Returned pointer is borrowed from s. Do not free it directly.
 * @note If c is '\\0', returns pointer to the terminating null.
 *
 * @param s String to search (borrowed).
 * @param c Character to find.
 * @return Pointer to the character (borrowed), or NULL if not found.
 */
char	*str_chr(const char *s, int c);

/**
 * @ingroup str
 * @brief Compares two strings.
 *
 * @param s1 First string.
 * @param s2 Second string.
 * @return Difference of first differing characters, or 0 if equal.
 */
int		str_cmp(const char *s1, const char *s2);

/**
 * @brief Counts words in a string separated by a delimiter.
 *
 * @param s String to analyze.
 * @param sep Delimiter character.
 * @return Number of words.
 */
size_t	str_count_words(char const *s, char sep);

/**
 * @ingroup str
 * @brief Duplicates a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param s1 String to duplicate (borrowed).
 * @return Newly allocated copy (owned), or NULL on failure.
 */
char	*str_dup(const char *s1);

/**
 * @ingroup str
 * @brief Applies a function to each character of a string with its index.
 *
 * @param s String to iterate (modified in place).
 * @param f Function taking index and character pointer.
 */
void	str_iteri(char *s, void (*f)(unsigned int, char*));

/**
 * @ingroup str
 * @brief Concatenates two strings into a new string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param s1 First string (borrowed).
 * @param s2 Second string (borrowed).
 * @return Newly allocated concatenated string (owned), or NULL on failure.
 */
char	*str_join(char const *s1, char const *s2);

/**
 * @ingroup str
 * @brief Appends src to dst with size limit.
 *
 * @param dst Destination buffer (must be null-terminated).
 * @param src Source string.
 * @param dstsize Total size of destination buffer.
 * @return Total length of string it tried to create.
 */
size_t	str_lcat(char *dst, const char *src, size_t dstsize);

/**
 * @ingroup str
 * @brief Copies src to dst with size limit.
 *
 * @param dst Destination buffer.
 * @param src Source string.
 * @param dstsize Size of destination buffer.
 * @return Length of src.
 */
size_t	str_lcpy(char *dst, const char *src, size_t dstsize);

/**
 * @ingroup str
 * @brief Calculates the length of a string.
 *
 * @param s String to measure.
 * @return Length of the string (not including null terminator).
 */
size_t	str_len(const char *s);

/**
 * @ingroup str
 * @brief Creates a new string by applying a function to each character.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param s String to transform (borrowed).
 * @param f Function taking index and character, returning new character.
 * @return Newly allocated transformed string (owned), or NULL on failure.
 */
char	*str_mapi(char const *s, char (*f)(unsigned int, char));

/**
 * @ingroup str
 * @brief Compares at most n characters of two strings.
 *
 * @param s1 First string.
 * @param s2 Second string.
 * @param n Maximum number of characters to compare.
 * @return Difference of first differing characters, or 0 if equal.
 */
int		str_ncmp(const char *s1, const char *s2, size_t n);

/**
 * @ingroup str
 * @brief Duplicates the first len bytes of a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param src String to duplicate (borrowed).
 * @param len Maximum number of bytes to copy.
 * @return Newly allocated copy (owned), or NULL on failure.
 */
char	*str_ndup(const char *src, size_t len);

/**
 * @ingroup str
 * @brief Locates a substring within a string, limited by length.
 *
 * @note Returned pointer is borrowed from haystack. Do not free it directly.
 *
 * @param haystack String to search in (borrowed).
 * @param needle Substring to find (borrowed).
 * @param len Maximum characters to search.
 * @return Pointer to start of substring (borrowed), or NULL if not found.
 */
char	*str_nstr(const char *haystack, const char *needle, size_t len);

/**
 * @ingroup str
 * @brief Locates the last occurrence of a character in a string.
 *
 * @note Returned pointer is borrowed from s. Do not free it directly.
 * @note If c is '\\0', returns pointer to the terminating null.
 *
 * @param s String to search (borrowed).
 * @param c Character to find.
 * @return Pointer to the character (borrowed), or NULL if not found.
 */
char	*str_rchr(const char *s, int c);

/**
 * @ingroup str
 * @brief Splits a string into an array of strings using a delimiter.
 *
 * @note Caller owns the returned array and each string within it.
 *       Free each string then free the array itself.
 *
 * @param s String to split (borrowed).
 * @param c Delimiter character.
 * @return NULL-terminated array of strings (owned), or NULL on failure.
 */
char	**str_split(char const *s, char c);

/**
 * @ingroup str
 * @brief Extracts a substring from a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param s Source string (borrowed).
 * @param start Starting index.
 * @param len Maximum length of substring.
 * @return Newly allocated substring (owned), or NULL on failure.
 */
char	*str_sub(char const *s, unsigned int start, size_t len);

/**
 * @ingroup str
 * @brief Trims characters from the beginning and end of a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param s1 String to trim (borrowed).
 * @param set Characters to trim (borrowed).
 * @return Newly allocated trimmed string (owned), or NULL on failure.
 */
char	*str_trim(char const *s1, char const *set);

char	*str_trim_leading(char const *s1, char const *set);

/* ************************************************************************* */
/*                                  VECTOR                                   */
/* ************************************************************************* */

/**
 * @ingroup vector
 * @brief Initializes a vector with a given item size and initial capacity.
 *
 * @note Cannot fail when cap == 0.
 *
 * @warning vector must NOT already own allocated data. Call vector_free()
 *          first if needed.
 *
 * @param vector Pointer to the vector to initialize (borrowed, uninitialized).
 * @param item_size Size of each item, in bytes (must be > 0).
 * @param cap Initial capacity, expressed in items.
 * @return true on success, false on invalid item_size, overflow, or allocation
 *         failure.
 */
bool	vector_init(t_vector *vector, size_t item_size, size_t cap);

/**
 * @ingroup vector
 * @brief Grows vector capacity, usually by doubling it.
 *
 * Existing items are preserved. If current capacity is 0, grows to
 * VECTOR_INIT_CAP.
 *
 * @warning vector must be initialized before calling this function.
 *
 * @param vector Pointer to an initialized vector (borrowed).
 * @return true on success, false on overflow or allocation failure.
 */
bool	vector_grow(t_vector *vector);

/**
 * @ingroup vector
 * @brief Shrinks vector capacity to match its current length.
 *
 * Existing items are preserved. If vector length is 0, internal storage is
 * freed.
 *
 * @warning vector must be initialized before calling this function.
 *
 * @param vector Pointer to an initialized vector (borrowed).
 * @return true on success, false on allocation failure.
 */
bool	vector_adjust(t_vector *vector);

/**
 * @ingroup vector
 * @brief Duplicates a vector into another one.
 *
 * A new internal storage is allocated for dst. Items are copied byte-for-byte;
 * item payloads themselves are not deep-copied.
 *
 * @note On success, dst is initialized and owns its internal storage.
 *       Caller must later release it with vector_free().
 *
 * @warning dst must NOT be initialized, or must be freed before calling this
 *          function.
 * @warning dst and src must be different.
 *
 * @param dst Destination vector to initialize and fill (borrowed).
 * @param src Source vector to duplicate (borrowed).
 * @return true on success, false on failure.
 */
bool	vector_dup(t_vector *dst, t_vector *src);

/**
 * @ingroup vector
 * @brief Frees the vector's internal storage.
 *
 * Sets vector->data to NULL after freeing.
 * Sets vector->len and vector->cap to 0 after freeing.
 *
 * @warning Does not free the t_vector struct itself, only its internal data.
 *
 * @param vector Pointer to the vector (borrowed).
 * @param item_free Optional callback to free each item (can be NULL).
 */
void	vector_free(t_vector *vector, void (*item_free)(void *item));

/**
 * @ingroup vector
 * @brief Appends one item at the end of the vector.
 *
 * Vector is automatically grown if necessary.
 *
 * @warning vector must be initialized before calling this function.
 * @warning item must NOT point inside vector->data.
 *
 * @param vector Pointer to an initialized vector (borrowed).
 * @param item Item to append (borrowed, not modified).
 * @return true on success, false on allocation failure.
 */
bool	vector_push(t_vector *vector, const void *item);

/**
 * @ingroup vector
 * @brief Removes the last item from the vector.
 *
 * If dst is not NULL, the removed item is copied there before removal.
 *
 * @warning vector must be initialized before calling this function.
 *
 * @param vector Pointer to an initialized vector (borrowed).
 * @param dst Optional destination buffer receiving the removed item (borrowed,
 *            can be NULL).
 * @return true on success, false if the vector is empty.
 */
bool	vector_pop(t_vector *vector, void *dst);

/**
 * @ingroup vector
 * @brief Inserts one item at a specific index.
 *
 * Existing items at and after index are shifted to the right. Vector is
 * automatically grown if necessary.
 *
 * @warning vector must be initialized before calling this function.
 * @warning item must NOT point inside vector->data.
 *
 * @param vector Pointer to an initialized vector (borrowed).
 * @param index Insertion index, in range [0, vector->len].
 * @param item Item to insert (borrowed, not modified).
 * @return true on success, false on invalid index or allocation failure.
 */
bool	vector_insert(t_vector *vector, size_t index, const void *item);

/**
 * @ingroup vector
 * @brief Removes one item at a specific index.
 *
 * Items after index are shifted left to fill the gap. If dst is not NULL, the
 * removed item is copied there before removal.
 *
 * @warning vector must be initialized before calling this function.
 *
 * @param vector Pointer to an initialized vector (borrowed).
 * @param index Index of the item to remove.
 * @param dst Optional destination buffer receiving the removed item (borrowed,
 *            can be NULL).
 * @return true on success, false if index is out of bounds.
 */
bool	vector_remove(t_vector *vector, size_t index, void *dst);

/**
 * @ingroup vector
 * @brief Inserts all items from src into dst at a specific index.
 *
 * Items are copied byte-for-byte from src into dst. Source and destination
 * storages remain independent after the merge.
 *
 * @warning dst and src must be initialized before calling this function.
 * @warning dst and src must be different.
 * @warning dst and src must use the same item_size.
 *
 * @param dst Destination vector receiving the inserted items (borrowed).
 * @param src Source vector providing items to copy (borrowed).
 * @param index Insertion index in dst, in range [0, dst->len].
 * @return true on success, false on invalid input, overflow, or allocation
 *         failure.
 */
bool	vector_merge(t_vector *dst, t_vector *src, size_t index);

#endif

```

./libft/Makefile
```makefile
NAME		= libft.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 # -O2 -DNDEBUG # -fsanitize=address,undefined # -fsanitize=leak # -fsanitize=memory

SRCS		:= \
	$(wildcard src/buff/*.c) \
	$(wildcard src/buff/format/*.c) \
	$(wildcard src/chr/*.c) \
	$(wildcard src/conv/*.c) \
	$(wildcard src/error/*.c) \
	$(wildcard src/hashmap/*.c) \
	$(wildcard src/hashmap/*/*.c) \
	$(wildcard src/list/*.c) \
	$(wildcard src/malloc/*.c) \
	$(wildcard src/math/*.c) \
	$(wildcard src/mem/*.c) \
	$(wildcard src/print/*.c) \
	$(wildcard src/put/*.c) \
	$(wildcard src/str/*.c) \
	$(wildcard src/vector/*.c)

INCLUDES	:= \
	-I. \
	-Isrc/buff/format \
	-Isrc/hashmap \
	-Isrc/hashmap/buckets \
	-Isrc/hashmap/key_value

OBJ_DIR		:= obj
OBJ			:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

TEST_NAME	:= tests/tester
TEST_SRCS	:= $(wildcard tests/*.c)
TEST_CFLAGS	:= $(INCLUDES) -g3 -lfut

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test: re
	$(CC) $(TEST_CFLAGS) $(NAME) $(TEST_SRCS) -o $(TEST_NAME)
	$(TEST_NAME)

doc:
	doxygen docs/Doxyfile

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(TEST_NAME).dSYM

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

re: fclean all

.PHONY: all test doc clean fclean re

```

./libft/src/btree/btree_free.c
```c
#include "libft.h"
#include <stdlib.h>

void	btree_free(t_btree_node **node, void (*data_free)(void *data))
{
	if (!node || !*node)
		return ;
	btree_free(&(*node)->left, data_free);
	btree_free(&(*node)->right, data_free);
	if ((*node)->data && data_free)
		data_free((*node)->data);
	free(*node);
	*node = NULL;
}

```

./libft/src/btree/btree.c
```c
#include "libft.h"
#include <stdlib.h>

t_btree_node	*btree_new(void *data)
{
	t_btree_node	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->data = data;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	btree_set_left(t_btree_node *parent, t_btree_node *child)
{
	parent->left = child;
	child->parent = parent;
}

void	btree_set_right(t_btree_node *parent, t_btree_node *child)
{
	parent->right = child;
	child->parent = parent;
}

t_btree_node	*btree_detach_left(t_btree_node *parent)
{
	t_btree_node	*left;

	left = parent->left;
	parent->left = NULL;
	left->parent = NULL;
	return (left);
}

t_btree_node	*btree_detach_right(t_btree_node *parent)
{
	t_btree_node	*right;

	right = parent->right;
	parent->right = NULL;
	right->parent = NULL;
	return (right);
}

```

./libft/src/buff/buff_cmp.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_cmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 18:27:52 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/28 18:29:55 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	buff_cmp(const t_buff *a, const t_buff *b)
{
	size_t	i;

	if (a->len != b->len)
		return (false);
	i = 0;
	while (i < a->len)
	{
		if (a->data[i] != b->data[i])
			return (false);
		++i;
	}
	return (true);
}

```

./libft/src/buff/buff_format.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/02/05 18:32:42 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buff_format.h"
#include <stdlib.h>

bool	buff_append_format(t_buff *buff, const char *fstring, ...)
{
	va_list	args;
	bool	success;

	va_start(args, fstring);
	success = buff_append_vformat(buff, fstring, args);
	va_end(args);
	return (success);
}

bool	buff_append_vformat(t_buff *buff, const char *fstring, va_list args)
{
	const char	*next_conversion;
	t_rules		rules;
	va_list		args_copy;

	va_copy(args_copy, args);
	next_conversion = str_chr(fstring, '%');
	while (next_conversion)
	{
		if (!buff_append(buff, fstring, next_conversion - fstring))
			return (false);
		fstring = next_conversion + 1;
		rules_parse(&rules, &fstring);
		if (rules.conversion == '%')
		{
			if (!buff_append(buff, "%", 1))
				return (false);
		}
		else if (!append(buff, &rules, &args_copy))
			return (false);
		next_conversion = str_chr(fstring, '%');
	}
	va_end(args_copy);
	return (buff_append(buff, fstring, -1));
}

```

./libft/src/buff/buff_internal.h
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 02:13:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 05:50:55 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFF_INTERNAL_H
# define BUFF_INTERNAL_H

# include "libft.h"
# include <stddef.h>

/**
 * @brief Calculates the required capacity to accommodate a target length.
 *
 * Uses exponential growth strategy (doubles capacity) to amortize
 * multiple growth operations to O(1) on average.
 *
 * @param current_cap Current capacity of the buffer.
 * @param target_len Target length to accommodate.
 * @return The new required capacity.
 */
size_t	buff_get_required_cap(size_t current_cap, size_t target_len);

/**
 * @brief Grows the buffer to accommodate the target length if necessary.
 *
 * No-op if current capacity is already sufficient.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @param target_len The minimum length the buffer should accommodate.
 * @return true on success, false on memory allocation failure.
 */
bool	buff_grow(t_buff *buff, size_t target_len);

#endif

```

./libft/src/buff/buff_life_cycle.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_life_cycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:30:37 by gastesan          #+#    #+#             */
/*   Updated: 2026/05/11 16:23:38 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

#define DEFAULT_BUFF_CAP 128
#define BUFF_GROWTH 2

bool	buff_init(t_buff *b, size_t initial_cap, const char *str, long n)
{
	b->data = NULL;
	b->cap = 0;
	b->len = 0;
	if (initial_cap > 0)
	{
		b->data = malloc(initial_cap);
		if (!b->data)
			return (false);
		b->cap = initial_cap;
	}
	if (str)
		return (buff_append(b, str, n));
	return (true);
}

size_t	buff_get_required_cap(size_t current_cap, size_t target_len)
{
	size_t	new_cap;

	if (target_len == 0)
		return (current_cap);
	if (current_cap == 0)
		new_cap = DEFAULT_BUFF_CAP;
	else
		new_cap = current_cap;
	while (new_cap <= target_len)
		new_cap *= BUFF_GROWTH;
	return (new_cap);
}

bool	buff_grow(t_buff *buff, size_t target_len)
{
	size_t	new_cap;
	char	*new_data;

	new_cap = buff_get_required_cap(buff->cap, target_len);
	if (new_cap == buff->cap)
		return (true);
	new_data = malloc(new_cap);
	if (!new_data)
		return (false);
	ft_memcpy(new_data, buff->data, buff->len);
	free(buff->data);
	buff->data = new_data;
	buff->cap = new_cap;
	return (true);
}

bool	buff_adjust(t_buff *buff)
{
	char	*new_data;

	if (buff->len == 0)
	{
		if (buff->data)
			free(buff->data);
		buff->data = NULL;
		buff->cap = 0;
		return (true);
	}
	new_data = malloc(buff->len);
	if (!new_data)
		return (false);
	ft_memcpy(new_data, buff->data, buff->len);
	free(buff->data);
	buff->data = new_data;
	buff->cap = buff->len;
	return (true);
}

void	buff_free(t_buff *b)
{
	if (b->data)
		free(b->data);
	b->len = 0;
	b->cap = 0;
	b->data = NULL;
}

```

./libft/src/buff/buff_ops.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:30:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/04/28 14:02:37 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buff_internal.h"
#include <stdlib.h>

bool	buff_prepend(t_buff *b, const char *str, long n)
{
	size_t	strlen;
	char	*new_data;
	size_t	new_cap;

	if (n < 0)
		strlen = str_len(str);
	else
		strlen = (size_t)n;
	new_cap = buff_get_required_cap(b->cap, b->len + strlen);
	if (new_cap > b->cap)
	{
		new_data = malloc(new_cap);
		if (!new_data)
			return (false);
		b->cap = new_cap;
		ft_memcpy(new_data + strlen, b->data, b->len);
		free(b->data);
		b->data = new_data;
	}
	else
		ft_memmove(b->data + strlen, b->data, b->len);
	ft_memcpy(b->data, str, strlen);
	b->len = b->len + strlen;
	return (true);
}

bool	buff_insert(t_buff *b, size_t index, const char *str, long n)
{
	size_t	strlen;
	char	*new_data;
	size_t	new_cap;

	if (n < 0)
		strlen = str_len(str);
	else
		strlen = (size_t)n;
	new_cap = buff_get_required_cap(b->cap, b->len + strlen);
	if (new_cap > b->cap)
	{
		new_data = malloc(new_cap);
		if (!new_data)
			return (false);
		b->cap = new_cap;
		ft_memcpy(new_data, b->data, index);
		ft_memcpy(new_data + index + strlen, b->data + index, b->len - index);
		free(b->data);
		b->data = new_data;
	}
	else
		ft_memmove(b->data + index + strlen, b->data + index, b->len - index);
	ft_memcpy(b->data + index, str, strlen);
	b->len = b->len + strlen;
	return (true);
}

bool	buff_append(t_buff *b, const char *str, long n)
{
	size_t	strlen;

	if (n < 0)
		strlen = str_len(str);
	else
		strlen = (size_t)n;
	if (!buff_grow(b, b->len + strlen))
		return (false);
	ft_memcpy(b->data + b->len, str, strlen);
	b->len = b->len + strlen;
	return (true);
}

bool	buff_dup_n(t_buff *dst, const t_buff *src, size_t n)
{
	if (n > src->len)
		n = src->len;
	dst->len = 0;
	if (!buff_append(dst, src->data, (long)n))
	{
		buff_free(dst);
		return (false);
	}
	return (true);
}

void	buff_rm_part(t_buff *buff, size_t i_start, ssize_t len)
{
	char	*dst;
	char	*src;
	size_t	len_to_move;

	if (i_start >= buff->len)
		return ;
	else if (len < 0 || i_start + (size_t)len > buff->len)
	{
		buff->len = i_start;
		return ;
	}
	dst = buff->data + i_start;
	src = buff->data + i_start + (size_t)len;
	len_to_move = buff->len - (i_start + (size_t)len);
	ft_memmove(dst, src, len_to_move);
	buff->len -= (size_t)len;
}

```

./libft/src/buff/buff_read.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:29:29 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:24:30 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buff_internal.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int	buff_read_until(t_buff *buff, int fd, char c)
{
	ssize_t	read_len;
	int		index;

	index = -1;
	while (index == -1)
	{
		if (buff->cap - buff->len == 0 && !buff_grow(buff, buff->len + 1))
			return (-2);
		read_len = read(fd, buff->data + buff->len, buff->cap - buff->len);
		if (read_len == -1 && errno == EINTR)
			continue ;
		else if (read_len == -1)
			return (-2);
		else if (read_len == 0)
			break ;
		buff->len += (size_t)read_len;
		index = buff_get_index(buff, c);
	}
	buff_adjust(buff);
	return (index);
}

bool	buff_read_all(t_buff *buff, int fd)
{
	ssize_t	read_len;

	while (true)
	{
		if (buff->cap - buff->len == 0 && !buff_grow(buff, buff->len + 1))
			return (false);
		read_len = read(fd, buff->data + buff->len, buff->cap - buff->len);
		if (read_len == -1 && errno == EINTR)
			continue ;
		else if (read_len <= 0)
			break ;
		buff->len += (size_t)read_len;
	}
	buff_adjust(buff);
	return (read_len != -1);
}

```

./libft/src/buff/buff_utils.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:29:25 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/24 05:38:37 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	buff_get_index(t_buff *buff, char c)
{
	size_t	i;

	i = 0;
	while (i < buff->len)
	{
		if (buff->data[i] == c)
			return ((int)i);
		i++;
	}
	return (-1);
}

char	*buff_get_string(t_buff *buff)
{
	char		*res;
	size_t		len;

	len = buff->len;
	while (len > 0 && buff->data[len - 1] == '\0')
		len--;
	if (len == 0)
		return (str_dup(""));
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res = ft_memcpy(res, buff->data, len);
	res[len] = '\0';
	return (res);
}

void	buff_free_void(void *buff)
{
	t_buff	*buff_ptr;

	buff_ptr = (t_buff *)buff;
	buff_free(buff_ptr);
}

```

./libft/src/buff/format/append_1.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:37 by gastesan          #+#    #+#             */
/*   Updated: 2026/05/14 20:49:09 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buff_format.h"

static bool	append_str(t_buff *buff, t_rules *rules, const char *str);

bool	append(t_buff *buff, t_rules *rules, va_list *args)
{
	t_buff	tmp_buff;
	bool	success;

	buff_init(&tmp_buff, 0, NULL, -1);
	success = false;
	if (rules->conversion == 'c')
		success = append_char(&tmp_buff, va_arg(*args, int));
	else if (rules->conversion == 's')
		success = append_str(&tmp_buff, rules, va_arg(*args, char *));
	else if (rules->conversion == 'd' || rules->conversion == 'i')
		success = append_int(&tmp_buff, va_arg(*args, int));
	else if (rules->conversion == 'u')
		success = append_uint(&tmp_buff, va_arg(*args, unsigned int));
	else if (rules->conversion == 'x')
		success = append_hex(&tmp_buff, va_arg(*args, unsigned int), false);
	else if (rules->conversion == 'X')
		success = append_hex(&tmp_buff, va_arg(*args, unsigned int), true);
	else if (rules->conversion == 'p')
		success = append_ptr(&tmp_buff, (unsigned long)va_arg(*args, void *));
	if (success)
		success = rules_apply(&tmp_buff, rules);
	if (success)
		success = buff_append(buff, tmp_buff.data, (long)tmp_buff.len);
	buff_free(&tmp_buff);
	return (success);
}

/**
 * @brief Appends a string to the buffer with null handling.
 *
 * @param buff Pointer to the buffer.
 * @param rules Pointer to the formatting rules.
 * @param str String to append (can be NULL).
 * @return true on success, false on failure.
 */
static bool	append_str(t_buff *buff, t_rules *rules, const char *str)
{
	if (!str)
	{
		if (rules->precision != -1 && rules->precision < 6)
			return (true);
		else
			return (buff_append(buff, "(null)", 6));
	}
	else
		return (buff_append(buff, str, -1));
}

```

./libft/src/buff/format/append_2.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:41 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:29:44 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

bool	append_char(t_buff *buff, char c)
{
	return (buff_append(buff, &c, 1));
}

bool	append_int(t_buff *buff, int nb)
{
	char	*tmp;
	bool	success;

	tmp = ft_itoa(nb);
	if (!tmp)
		return (false);
	success = buff_append(buff, tmp, -1);
	free(tmp);
	return (success);
}

bool	append_uint(t_buff *buff, unsigned int nb)
{
	char	*tmp;
	bool	success;

	tmp = ft_utoa(nb);
	if (!tmp)
		return (false);
	success = buff_append(buff, tmp, -1);
	free(tmp);
	return (success);
}

bool	append_hex(t_buff *buff, unsigned long nb, bool uppercase)
{
	char				*tmp;
	bool				success;
	static const char	upperbase[] = "0123456789ABCDEF";
	static const char	lowerbase[] = "0123456789abcdef";

	if (uppercase)
		tmp = ft_ultoa_base(nb, upperbase);
	else
		tmp = ft_ultoa_base(nb, lowerbase);
	if (!tmp)
		return (false);
	success = buff_append(buff, tmp, -1);
	free(tmp);
	return (success);
}

/**
 * @brief Appends a pointer address to the buffer.
 *
 * @param buff Pointer to the buffer.
 * @param nb Pointer value as unsigned long.
 * @return true on success, false on failure.
 */
bool	append_ptr(t_buff *buff, unsigned long nb)
{
	if (nb == 0)
		return (buff_append(buff, "(nil)", 5));
	return (append_hex(buff, nb, false));
}

```

./libft/src/buff/format/buff_format.h
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_format.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:44 by gastesan          #+#    #+#             */
/*   Updated: 2026/02/05 18:02:22 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFF_FORMAT_H
# define BUFF_FORMAT_H

# include "libft.h"

/**
 * @struct s_rules
 * @brief Structure holding format specifier rules for printf-like formatting.
 *
 * @var s_rules::plus Display '+' sign for positive numbers.
 * @var s_rules::space Display space before positive numbers.
 * @var s_rules::hex_prefix Display '0x' or '0X' prefix for hex numbers.
 * @var s_rules::zero_padding Pad with zeros instead of spaces.
 * @var s_rules::right_padding Right-align the output.
 * @var s_rules::precision Precision value, -1 if not set.
 * @var s_rules::width_enabled Width specifier is enabled.
 * @var s_rules::width Minimum field width.
 * @var s_rules::conversion Conversion specifier character.
 * @var s_rules::is_zero Value is zero (used for special cases).
 */
typedef struct s_rules
{
	/** @brief Display '+' sign for positive numbers. */
	bool	plus;
	/** @brief Display space before positive numbers. */
	bool	space;
	/** @brief Display '0x' or '0X' prefix for hex numbers. */
	bool	hex_prefix;
	/** @brief Pad with zeros instead of spaces. */
	bool	zero_padding;
	/** @brief Right-align the output. */
	bool	right_padding;
	/** @brief Precision value, -1 if not set. */
	int		precision;
	/** @brief Width specifier is enabled. */
	bool	width_enabled;
	/** @brief Minimum field width. */
	int		width;
	/** @brief Conversion specifier character. */
	char	conversion;
	/** @brief Value is zero (used for special cases). */
	bool	is_zero;
}	t_rules;

/**
 * @brief Parses format specifiers from a format string.
 *
 * @param rules Pointer to the rules structure to populate.
 * @param fstring Pointer to format string pointer (advanced by parsing).
 */
void	rules_parse(t_rules *rules, const char **fstring);

/**
 * @brief Applies formatting rules to a buffer.
 *
 * @param buff Pointer to the buffer.
 * @param rules Pointer to the rules structure.
 * @return true on success, false on failure.
 */
bool	rules_apply(t_buff *buff, t_rules *rules);

/**
 * @brief Appends formatted argument to buffer based on rules.
 *
 * @param buff Pointer to the buffer.
 * @param rules Pointer to the formatting rules.
 * @param args Pointer to the variable argument list.
 * @return true on success, false on failure.
 */
bool	append(t_buff *buff, t_rules *rules, va_list *args);

/**
 * @brief Appends a character to the buffer.
 *
 * @param buff Pointer to the buffer.
 * @param c Character to append.
 * @return true on success, false on failure.
 */
bool	append_char(t_buff *buff, char c);

/**
 * @brief Appends an integer to the buffer as a string.
 *
 * @param buff Pointer to the buffer.
 * @param nb Integer to append.
 * @return true on success, false on failure.
 */
bool	append_int(t_buff *buff, int nb);

/**
 * @brief Appends an unsigned integer to the buffer as a string.
 *
 * @param buff Pointer to the buffer.
 * @param nb Unsigned integer to append.
 * @return true on success, false on failure.
 */
bool	append_uint(t_buff *buff, unsigned int nb);

/**
 * @brief Appends a number in hexadecimal format to the buffer.
 *
 * @param buff Pointer to the buffer.
 * @param nb Number to convert.
 * @param uppercase Use uppercase letters if true.
 * @return true on success, false on failure.
 */
bool	append_hex(t_buff *buff, unsigned long nb, bool uppercase);

/**
 * @brief Appends a pointer address to the buffer.
 *
 * @param buff Pointer to the buffer.
 * @param nb Pointer value as unsigned long.
 * @return true on success, false on failure.
 */
bool	append_ptr(t_buff *buff, unsigned long nb);

#endif

```

./libft/src/buff/format/rules_apply.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:47 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:29:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buff_format.h"
#include <stdlib.h>

static bool	apply_precision(t_buff *buff, t_rules *rules);
static bool	apply_plus_space(t_buff *buff, t_rules *r);
static bool	apply_hex_prefix(t_buff *buff, t_rules *rules);
static bool	apply_width(t_buff *buff, t_rules *rules);

bool	rules_apply(t_buff *buff, t_rules *rules)
{
	if (buff->len == 1 && buff->data[0] == '0')
		rules->is_zero = true;
	if (rules->precision != -1 && !apply_precision(buff, rules))
		return (false);
	if ((rules->plus || rules->space) && !apply_plus_space(buff, rules))
		return (false);
	if (rules->hex_prefix && !apply_hex_prefix(buff, rules))
		return (false);
	if (rules->width_enabled && !apply_width(buff, rules))
		return (false);
	return (true);
}

/**
 * @brief Applies precision formatting to the buffer.
 *
 * @param buff Pointer to the buffer.
 * @param rules Pointer to the formatting rules.
 * @return true on success, false on failure.
 */
static bool	apply_precision(t_buff *buff, t_rules *rules)
{
	size_t	len_without_sign;
	long	zeros_len;
	char	*zeros;
	bool	success;

	if (rules->conversion == 's')
	{
		if (buff->len > (size_t)rules->precision)
			buff->len = (size_t)rules->precision;
		return (true);
	}
	len_without_sign = buff->len - (buff->data[0] == '-');
	if (rules->precision == 0 && buff->len == 1 && buff->data[0] == '0')
		buff->len = 0;
	else if (len_without_sign < (size_t)rules->precision)
	{
		zeros_len = (long)((size_t)rules->precision - len_without_sign);
		zeros = malloc((size_t)zeros_len);
		if (!zeros)
			return (false);
		ft_memset(zeros, '0', (size_t)zeros_len);
		success = buff_insert(buff, (buff->data[0] == '-'), zeros, zeros_len);
		return (free(zeros), success);
	}
	return (true);
}

/**
 * @brief Applies plus or space sign formatting for positive numbers.
 *
 * @param buff Pointer to the buffer.
 * @param r Pointer to the formatting rules.
 * @return true on success, false on failure.
 */
static bool	apply_plus_space(t_buff *buff, t_rules *r)
{
	char	sign;

	if (buff->data[0] == '-')
		return (true);
	sign = buff->data[0];
	if (r->plus)
	{
		sign = '+';
		return (buff_prepend(buff, &sign, 1));
	}
	else if (r->space)
	{
		sign = ' ';
		return (buff_prepend(buff, &sign, 1));
	}
	return (true);
}

/**
 * @brief Applies hexadecimal prefix (0x or 0X) to the buffer.
 *
 * @param buff Pointer to the buffer.
 * @param rules Pointer to the formatting rules.
 * @return true on success, false on failure.
 */
static bool	apply_hex_prefix(t_buff *buff, t_rules *rules)
{
	char	prefix[2];

	if (buff->data[0] == '(' || rules->is_zero)
		return (true);
	if (buff->len == 0 || (buff->len == 1 && buff->data[0] == '0'))
		return (true);
	prefix[0] = '0';
	if (rules->conversion == 'X')
		prefix[1] = 'X';
	else
		prefix[1] = 'x';
	return (buff_prepend(buff, prefix, 2));
}

/**
 * @brief Applies width padding to the buffer.
 *
 * @param b Pointer to the buffer.
 * @param r Pointer to the formatting rules.
 * @return true on success, false on failure.
 */
static bool	apply_width(t_buff *b, t_rules *r)
{
	char	*padding;
	size_t	padding_len;
	bool	success;

	if (b->len >= (size_t)r->width)
		return (true);
	padding_len = (size_t)r->width - b->len;
	padding = malloc(padding_len);
	if (!padding)
		return (false);
	if (r->zero_padding)
		ft_memset(padding, '0', padding_len);
	else
		ft_memset(padding, ' ', padding_len);
	if (r->right_padding)
		success = buff_append(b, padding, (long)padding_len);
	else if (r->zero_padding && (b->data[0] == '-' || r->plus || r->space))
		success = buff_insert(b, 1, padding, (long)padding_len);
	else if (r->zero_padding && b->len >= 2 && b->data[0] == '0'
		&& (b->data[1] == 'x' || b->data[1] == 'X'))
		success = buff_insert(b, 2, padding, (long)padding_len);
	else
		success = buff_prepend(b, padding, (long)padding_len);
	free(padding);
	return (success);
}

```

./libft/src/buff/format/rules_parse.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:50 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:29:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buff_format.h"

static void	parse_flags(t_rules *rules, const char **fstring);
static void	parse_width(t_rules *rules, const char **fstring);
static void	parse_precision(t_rules *rules, const char **fstring);
static void	normalize(t_rules *rules);

void	rules_parse(t_rules *rules, const char **fstring)
{
	const char	conversion_set[] = "csdiuxXp";

	rules->plus = false;
	rules->space = false;
	rules->hex_prefix = false;
	rules->zero_padding = false;
	rules->right_padding = false;
	rules->precision = -1;
	rules->width_enabled = false;
	rules->width = -1;
	rules->conversion = '\0';
	rules->is_zero = false;
	if (**fstring != '%')
	{
		parse_flags(rules, fstring);
		if (**fstring != '.' && !ft_isincharset(**fstring, conversion_set))
			parse_width(rules, fstring);
		if (**fstring == '.')
			parse_precision(rules, fstring);
	}
	rules->conversion = **fstring;
	normalize(rules);
	(*fstring)++;
}

/**
 * @brief Parses flag characters from the format string.
 *
 * @param rules Pointer to the rules structure.
 * @param fstring Pointer to format string pointer.
 */
static void	parse_flags(t_rules *rules, const char **fstring)
{
	const char	flag_set[] = "-0# +";
	char		c;

	while (ft_isincharset(**fstring, flag_set))
	{
		c = **fstring;
		if (c == '-')
			rules->right_padding = true;
		else if (c == '0')
			rules->zero_padding = true;
		else if (c == '#')
			rules->hex_prefix = true;
		else if (c == ' ')
			rules->space = true;
		else if (c == '+')
			rules->plus = true;
		(*fstring)++;
	}
}

/**
 * @brief Parses width specifier from the format string.
 *
 * @param rules Pointer to the rules structure.
 * @param fstring Pointer to format string pointer.
 */
static void	parse_width(t_rules *rules, const char **fstring)
{
	rules->width_enabled = true;
	rules->width = ft_atoi(*fstring);
	while (ft_isdigit(**fstring))
		(*fstring)++;
}

/**
 * @brief Parses precision specifier from the format string.
 *
 * @param rules Pointer to the rules structure.
 * @param fstring Pointer to format string pointer.
 */
static void	parse_precision(t_rules *rules, const char **fstring)
{
	(*fstring)++;
	rules->precision = ft_atoi(*fstring);
	while (ft_isdigit(**fstring))
		(*fstring)++;
}

/**
 * @brief Normalizes rules based on conversion specifier constraints.
 *
 * @param rules Pointer to the rules structure.
 */
static void	normalize(t_rules *rules)
{
	char	conv;

	conv = rules->conversion;
	if (conv != 'x' && conv != 'X' && conv != 'p')
		rules->hex_prefix = false;
	if (conv == 'p')
	{
		rules->hex_prefix = true;
		rules->precision = -1;
	}
	if (conv == 'c')
		rules->precision = -1;
	if (conv != 'd' && conv != 'i')
		rules->plus = false;
	if ((conv != 'd' && conv != 'i') || rules->plus)
		rules->space = false;
	if (rules->width_enabled && rules->width < 0)
	{
		rules->right_padding = true;
		rules->width = -rules->width;
	}
	if (rules->right_padding || rules->precision != -1)
		rules->zero_padding = false;
}

```

./libft/src/chr/ft_isalnum.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:14 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:24:40 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

```

./libft/src/chr/ft_isalpha.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:17 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:24:41 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

```

./libft/src/chr/ft_isascii.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:21 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:24:42 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

```

./libft/src/chr/ft_isdigit.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:24 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:24:42 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

```

./libft/src/chr/ft_isincharset.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isincharset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 21:30:28 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:24:43 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	ft_isincharset(char c, const char *charset)
{
	while (*charset)
	{
		if (*charset == c)
			return (true);
		charset++;
	}
	return (false);
}

```

./libft/src/chr/ft_isprint.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:27 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:24:44 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (1);
	return (0);
}

```

./libft/src/chr/ft_isspace.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:37:47 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:24:44 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

```

./libft/src/chr/ft_tolower.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:57 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:24:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	unsigned char	uc;

	uc = (unsigned char) c;
	if (uc >= 'A' && uc <= 'Z')
		return (uc + 32);
	return (c);
}

```

./libft/src/chr/ft_toupper.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:21:00 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:24:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	unsigned char	uc;

	uc = (unsigned char) c;
	if (uc >= 'a' && uc <= 'z')
		return (uc - 32);
	return (c);
}

```

./libft/src/conv/ft_atol.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:05 by gastesan          #+#    #+#             */
/*   Updated: 2026/05/19 15:34:21 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	size_t	i;
	int		sign;
	long	result;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

```

./libft/src/conv/ft_atopid.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atopid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:40:21 by gastesan          #+#    #+#             */
/*   Updated: 2026/05/19 15:40:25 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>

pid_t	ft_atopid(const char *str)
{
	size_t	i;
	int		sign;
	pid_t	result;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((pid_t)(result * sign));
}

```

./libft/src/conv/ft_atozu.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atozu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:05 by gastesan          #+#    #+#             */
/*   Updated: 2026/05/19 15:27:14 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

size_t	ft_atozu(const char *str)
{
	size_t	i;
	size_t	result;
	size_t	digit;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = (size_t)(str[i] - '0');
		if (result > (SIZE_MAX - digit) / 10)
			return (SIZE_MAX);
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

```

./libft/src/conv/ft_ltoa.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:29 by gastesan          #+#    #+#             */
/*   Updated: 2026/05/14 21:18:31 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	get_len(long n);
static void		populate(long n, char *str, size_t i);

char	*ft_ltoa(long n)
{
	size_t	len;
	char	*res;

	len = get_len(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (n < 0)
		res[0] = '-';
	populate(n, res, len - 1);
	return (res);
}

/**
 * @brief Calculates the string length needed for a long number.
 *
 * @param n Long number.
 * @return Length including sign if negative.
 */
static size_t	get_len(long n)
{
	size_t	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

/**
 * @brief Recursively populates a string with digits from a long.
 *
 * @param n Long number to convert.
 * @param str Destination string.
 * @param i Current index to write to.
 */
static void	populate(long n, char *str, size_t i)
{
	int	mod;

	if (n >= 10 || n <= -10)
		populate(n / 10, str, i - 1);
	mod = n % 10;
	if (mod < 0)
		mod *= -1;
	str[i] = (char)mod + '0';
}

```

./libft/src/conv/ft_pidtoa.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pidtoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:40:17 by gastesan          #+#    #+#             */
/*   Updated: 2026/05/19 15:40:33 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>

static size_t	get_len(pid_t n);
static void		populate(pid_t n, char *str, size_t i);

char	*ft_pidtoa(pid_t n)
{
	size_t	len;
	char	*res;

	len = get_len(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (n < 0)
		res[0] = '-';
	populate(n, res, len - 1);
	return (res);
}

static size_t	get_len(pid_t n)
{
	size_t	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	populate(pid_t n, char *str, size_t i)
{
	int	mod;

	if (n >= 10 || n <= -10)
		populate(n / 10, str, i - 1);
	mod = n % 10;
	if (mod < 0)
		mod *= -1;
	str[i] = (char)mod + '0';
}

```

./libft/src/conv/ft_ultoa_base.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:38:08 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:25:29 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	get_base_len(const char *base);
static size_t	get_res_len(unsigned long n, size_t base_len);

char	*ft_ultoa_base(unsigned long n, const char *base)
{
	size_t	base_len;
	size_t	res_len;
	char	*res;

	if (!base)
		return (NULL);
	base_len = get_base_len(base);
	if (base_len < 2)
		return (NULL);
	res_len = get_res_len(n, base_len);
	res = malloc(res_len + 1);
	if (!res)
		return (NULL);
	res[res_len] = '\0';
	while (res_len-- > 0)
	{
		res[res_len] = base[n % base_len];
		n /= base_len;
	}
	return (res);
}

/**
 * @brief Calculates the length of a base string.
 *
 * @param base Base string.
 * @return Length of the base.
 */
static size_t	get_base_len(const char *base)
{
	size_t	len;

	len = 0;
	while (base[len])
		len++;
	return (len);
}

/**
 * @brief Calculates the result string length for a number in a given base.
 *
 * @param n Number to convert.
 * @param base_len Length of the base.
 * @return Required string length.
 */
static size_t	get_res_len(unsigned long n, size_t base_len)
{
	size_t	len;

	len = 1;
	while (n >= base_len)
	{
		n /= base_len;
		len++;
	}
	return (len);
}

```

./libft/src/conv/ft_zutoa.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zutoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 21:18:17 by gastesan          #+#    #+#             */
/*   Updated: 2026/05/19 15:27:49 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	get_len(size_t n);
static void		populate(size_t n, char *str, size_t i);

char	*ft_zutoa(size_t n)
{
	size_t	len;
	char	*res;

	len = get_len(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	populate(n, res, len - 1);
	return (res);
}

/**
 * @brief Calculates the string length needed for a size_t number.
 *
 * @param n Size_t number.
 * @return Length of the decimal representation.
 */
static size_t	get_len(size_t n)
{
	size_t	len;

	len = 1;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

/**
 * @brief Recursively populates a string with digits from a size_t.
 *
 * @param n Size_t number to convert.
 * @param str Destination string.
 * @param i Current index to write to.
 */
static void	populate(size_t n, char *str, size_t i)
{
	size_t	mod;

	if (n >= 10)
		populate(n / 10, str, i - 1);
	mod = n % 10;
	str[i] = (char)mod + '0';
}

```

./libft/src/conv/parse_int.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 21:26:28 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/15 21:26:29 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <limits.h>

bool	parse_int(char *s, int *out)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (*s == '\0')
		return (false);
	while (*s)
	{
		if (*s < '0' || *s > '9' || result > (LONG_MAX - (*s - '0')) / 10)
			return (false);
		result = result * 10 + (*s - '0');
		s++;
	}
	result *= sign;
	if (result < INT_MIN || result > INT_MAX)
		return (false);
	*out = (int)result;
	return (true);
}

```

./libft/src/conv/variants.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:37:59 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:25:33 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	return ((int)ft_atol(str));
}

char	*ft_itoa(int n)
{
	return (ft_ltoa((long) n));
}

char	*ft_utoa(unsigned int n)
{
	return (ft_ltoa((long) n));
}

```

./libft/src/error/error.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 23:30:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/05/14 20:48:47 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void	_print(bool print_errno, int errno_val, const char *s, size_t len);

void	fprint_err(bool print_errno, const char *safe, const char *fmt, ...)
{
	va_list	ap;
	t_buff	buff;
	int		errno_backup;

	errno_backup = errno;
	va_start(ap, fmt);
	buff_init(&buff, 0, NULL, -1);
	if (buff_append(&buff, safe, -1) && buff_append_vformat(&buff, fmt, ap))
		_print(print_errno, errno_backup, buff.data, buff.len);
	else
		_print(print_errno, errno_backup, safe, str_len(safe));
	buff_free(&buff);
	va_end(ap);
}

void	print_err(bool print_errno, const char *message)
{
	int		errno_backup;
	size_t	len;

	errno_backup = errno;
	if (message)
		len = str_len(message);
	else
		len = 0;
	_print(print_errno, errno_backup, message, len);
}

static void	_print(bool print_errno, int errno_val, const char *s, size_t len)
{
	const char	*err_string;

	write(STDERR_FILENO, "Error\n", 6);
	if (!print_errno && !s)
		return ;
	write(STDERR_FILENO, "⇢ ", str_len("⇢ "));
	if (s)
		write(STDERR_FILENO, s, len);
	if (s && print_errno)
		write(STDERR_FILENO, ": ", 2);
	if (print_errno)
	{
		err_string = strerror(errno_val);
		write(STDERR_FILENO, err_string, str_len(err_string));
	}
	write(STDERR_FILENO, "\n", 1);
}

```

./libft/src/hashmap/API.c
```c
#include <stdlib.h>
#include "libft.h"
#include "key_value.h"
#include "priv_hashmap.h"

bool	hashmap_put(t_hashmap *map, const char *key, void *value)
{
	t_key_value *existing;
	t_key_value	*pair;

	existing = hashmap_get(map, key);
	if (existing && existing->value == value)
		return (true);
	if (hashmap_need_resize(map, key) && !hashmap_resize(map))
		return (false);
	pair = key_value_new(key, value);
	if (pair == NULL)
		return (false);
	if (!hashmap_insert(map, pair))
		return (key_value_free(&pair, NULL), false);
	return (true);
}

t_key_value	*hashmap_get(t_hashmap *map, const char *key)
{
	t_node	*entry;

	if (map->buckets.cap == 0)
		return (NULL);
	entry = ((t_list*)map->buckets.data)[map->hash(key) % map->buckets.cap];
	while (entry != NULL)
	{
		if (is_matching_key(entry->content, key))
			return ((t_key_value *)entry->content);
		entry = entry->next;
	}
	return (NULL);
}

t_key_value	**hashmap_get_all(t_hashmap *map)
{
	t_key_value	**res;
	size_t		pair_i;
	t_node		*entry;
	size_t		bucket_i;
	
	res = malloc(sizeof(t_key_value *) * (map->size + 1));
	if (res == NULL)
		return (NULL);
	bucket_i = 0;
	pair_i = 0;
	while (bucket_i < map->buckets.len)
	{
		entry = ((t_list*)map->buckets.data)[bucket_i];
		while (entry != NULL)
		{
			res[pair_i++] = entry->content;
			entry = entry->next;
		}		
		++bucket_i;
	}
	res[pair_i] = NULL;
	return (res);
}

bool	hashmap_remove(t_hashmap *map, const char *key)
{
	t_key_value	*pair;
	t_node		*entry;
	t_list		bucket;
	size_t		bucket_i;

	if (map->buckets.cap == 0)
		return (false);
	bucket_i = map->hash(key) % map->buckets.cap;
	bucket = ((t_list*)map->buckets.data)[bucket_i];
	entry = bucket;
	while (entry != NULL)
	{
		if (is_matching_key(entry->content, key))
		{
			pair = entry->content;
			entry->content = NULL;
			list_rm(&bucket, entry, NULL);
			key_value_free(&pair, map->del_value);
			((t_list*)map->buckets.data)[bucket_i] = bucket;
			map->size--;
			return (true);
		}
		entry = entry->next;
	}
	return (false);
}

bool	hashmap_contains(t_hashmap *map, const char *key)
{
	t_node	*entry;

	if (map->buckets.cap == 0)
		return (NULL);
	entry = ((t_list*)map->buckets.data)[map->hash(key) % map->buckets.cap];
	while (entry != NULL)
	{
		if (is_matching_key(entry->content, key))
			return (true);
		entry = entry->next;
	}
	return (false);
}

```

./libft/src/hashmap/buckets/buckets.h
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buckets.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 16:22:55 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 13:50:37 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUCKETS_H
# define BUCKETS_H

#include "libft.h"

/**
 * @brief Initializes the bucket array.
 *
 * Allocates a vector of init_cap t_list slots and zeroes it, so every bucket
 * starts as an empty (NULL) chain.
 *
 * @param buckets Pointer to the vector to initialize (uninitialized).
 * @param init_cap Number of buckets to allocate.
 * @return true on success, false on memory allocation failure.
 */
bool	buckets_init(t_vector *buckets, size_t init_cap);

/**
 * @brief Frees the bucket array and every pair it contains.
 *
 * Frees each bucket chain (every pair's key and, through del, its value) and
 * then frees the underlying vector. The vector is left in a freed state.
 *
 * @param buckets Pointer to the bucket vector to free (borrowed).
 * @param del Optional destructor applied to each stored value (may be NULL).
 */
void	buckets_free(t_vector *buckets, void (*del)(void *));

/**
 * @brief Detaches every pair from the bucket chains without freeing them.
 *
 * Sets each list node's content to NULL across all buckets, severing the link
 * between the chains and their pairs. Used during a resize so the old chains
 * can be freed while the pairs themselves are kept (they have been moved into
 * the new bucket array).
 *
 * @param buckets Pointer to the bucket vector to detach (borrowed).
 */
void	buckets_detach(t_vector *buckets);

/**
 * @brief Swaps the contents of two bucket vectors.
 *
 * Exchanges the two t_vector structures by value; no allocation occurs and no
 * pair is moved in memory.
 *
 * @param buckets1 First bucket vector (borrowed).
 * @param buckets2 Second bucket vector (borrowed).
 */
void	buckets_swap(t_vector *buckets1, t_vector *buckets2);

/**
 * @brief Applies a function to every used bucket slot.
 *
 * Iterates over the first vector->len slots and calls f with the address of
 * each bucket slot and the del callback, allowing f to free or mutate the
 * chain stored there.
 *
 * @param vector Pointer to the bucket vector to iterate (borrowed).
 * @param del Destructor forwarded to f for each slot (may be NULL).
 * @param f Function applied to each bucket slot (borrowed).
 */
void	buckets_foreach(t_vector *vector, void (*del)(void *),
			void (*f)(void *, void (*del)(void *)));

/**
 * @brief Frees a single bucket chain and its pairs.
 *
 * Frees every pair in the chain (key and, through del, value) and removes all
 * list nodes. Shaped to be used as a buckets_foreach() callback.
 *
 * @param bucket_ptr Address of the bucket slot (a t_list *) to free (borrowed).
 * @param del Optional destructor applied to each stored value (may be NULL).
 */
void	bucket_free(void *bucket_ptr, void (*del)(void *));

/**
 * @brief Tests whether a bucket chain holds a pair with the given key.
 *
 * @param bucket Head of the bucket chain to search (borrowed, may be NULL).
 * @param key NUL-terminated key to look for (borrowed).
 * @return true if a matching pair is found, false otherwise.
 */
bool	bucket_contains(t_list bucket, const char *key);

/**
 * @brief Detaches every pair from a single bucket chain without freeing them.
 *
 * Sets each node's content to NULL. Shaped to be used as a buckets_foreach()
 * callback; the destructor parameter is unused.
 *
 * @param bucket Address of the bucket slot (a t_list *) to detach (borrowed).
 * @param _ Unused destructor parameter (required by the callback signature).
 */
void	bucket_detach(void *bucket, void (*_)(void *));

/**
 * @brief Replaces the value of the pair matching new->key within a chain.
 *
 * Walks the chain and, for the node whose key matches new->key, releases the
 * existing pair (its value through del) and stores new in its place.
 *
 * @note Ownership of new is transferred to the matching node. The previously
 *       stored pair is freed.
 *
 * @param bucket Head of the bucket chain to update (borrowed).
 * @param new Replacement pair carrying the matching key (ownership
 *            transferred).
 * @param del Optional destructor applied to the replaced value (may be NULL).
 */
void	bucket_replace(t_list bucket, t_key_value *new, void (*del)(void *));
#endif

```

./libft/src/hashmap/buckets/contains.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contains.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:44:48 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 13:50:41 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "key_value.h"

bool	bucket_contains(t_list bucket, const char *key)
{
	t_key_value	*pair;
	t_node		*entry;

	entry = bucket;
	while (entry != NULL)
	{
		pair = entry->content;
		if (is_matching_key(pair, key))
			return (true);
		entry = entry->next;
	}
	return (false);
}

```

./libft/src/hashmap/buckets/detach.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detach.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:42:01 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 16:26:33 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buckets.h"

void	bucket_detach(void *bucket, void (*_)(void *))
{
	t_node	*entry;

	entry = *(t_node **)bucket;
	while (entry != NULL)
	{
		entry->content = NULL;
		entry = entry->next;
	}
}

void	buckets_detach(t_vector *buckets)
{
	buckets_foreach(buckets, NULL, bucket_detach);
}

```

./libft/src/hashmap/buckets/init.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:33:17 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 15:23:21 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buckets.h"
#include "key_value.h"

void	bucket_free(void *bucket_ptr, void (*del)(void *))
{
	t_node	*entry;

	entry = *(t_node **)bucket_ptr;
	while (entry != NULL)
	{
		key_value_free((t_key_value **)&entry->content, del);
		entry = entry->next;
	}
	list_rm_all((t_list *)bucket_ptr, NULL);
}
bool	buckets_init(t_vector *buckets, size_t init_cap)
{
	if (!vector_init(buckets, sizeof(t_list), init_cap))
		return (false);
	ft_bzero(buckets->data, init_cap * sizeof(t_list));
	return (true);
}

void	buckets_free(t_vector *buckets, void (*del)(void *))
{
	buckets_foreach(buckets, del, bucket_free);
	vector_free(buckets, NULL);
}

```

./libft/src/hashmap/buckets/replace.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:43:08 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 15:15:34 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "key_value.h"

void	bucket_replace(t_list bucket, t_key_value *new, void (*del)(void *))
{
	t_key_value	*pair;
	t_node		*entry;
	
	entry = bucket;
	while (entry != NULL)
	{
		pair = entry->content;
		if (is_matching_key(pair, new->key))
		{
			key_value_free(&pair, del);
			entry->content = new;
			return;
		}
		entry = entry->next;
	}
}

```

./libft/src/hashmap/buckets/swap.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:50:24 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 15:50:35 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	buckets_swap(t_vector *buckets1, t_vector *buckets2)
{
	t_vector	temp;

	temp = *buckets1;
	*buckets1 = *buckets2;
	*buckets2 = temp;
}

```

./libft/src/hashmap/buckets/utils.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:39:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 15:21:49 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	buckets_foreach(
	t_vector *vector,
	void (*del)(void *),
	void (*f)(void *, void (*del)(void *)))
{
	size_t	i;

	i = 0;
	while (i < vector->cap)
		f((char *)vector->data + (vector->item_size * i++), del);
}

```

./libft/src/hashmap/hash_function.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:52:29 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 18:44:23 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	hash_string(const char *key)
{
	size_t	i;
	size_t	hash;

	i = 0;
	hash = 5381;
	while (key[i] != '\0')
		hash = ((hash << 5) + hash) + (unsigned char)key[i++];
	return (hash);
}

```

./libft/src/hashmap/init.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:30:50 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 15:20:43 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "buckets.h"
#include "priv_hashmap.h"

bool	hashmap_init(t_hashmap *map, size_t initial_cap, void (*del)(void *))
{
	*map = (t_hashmap){0};
	if (!buckets_init(&map->buckets, initial_cap))
		return (false);
	map->hash = hash_string;
	map->del_value = del;
	return (true);
}

void	hashmap_free(t_hashmap *map)
{
	buckets_free(&map->buckets, map->del_value);
	*map = (t_hashmap){0};
}

```

./libft/src/hashmap/insert.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:55:28 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 16:28:21 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buckets.h"

bool	hashmap_insert(t_hashmap *map, t_key_value *new)
{
	t_list		bucket;
	size_t		bucket_i;

	bucket_i = map->hash(new->key) % map->buckets.cap;
	bucket = ((t_list*)map->buckets.data)[bucket_i];
	if (bucket != NULL && bucket_contains(bucket, new->key))
		return (bucket_replace(bucket, new, map->del_value), true);
	if (!list_add_end(&bucket, new))
		return (false);
	if (map->buckets.len <= bucket_i)
		map->buckets.len = bucket_i + 1;
	((t_list *)map->buckets.data)[bucket_i] = bucket;
	return (map->size++, true);
}

```

./libft/src/hashmap/key_value/init.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:34:48 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 18:43:53 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_key_value	*key_value_new(const char *key, void *value)
{
	t_key_value	*pair;

	pair = malloc(sizeof(t_key_value));
	if (pair == NULL)
		return (NULL);
	pair->key = str_dup(key);
	if (pair->key == NULL)
		return (free(pair), NULL);
	return (pair->value = value, pair);
}

void	key_value_free(t_key_value **pair, void (*del)(void *))
{
	if (pair == NULL || *pair == NULL)
		return ;	
	if (del)
		del((*pair)->value);
	free((*pair)->key);
	**pair = (t_key_value){0};
	free(*pair);
	*pair = NULL;
}

```

./libft/src/hashmap/key_value/key_value.h
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 16:24:06 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 18:43:43 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_VALUE_H
# define KEY_VALUE_H

# include "libft.h"

/**
 * @brief Allocates a key/value pair.
 *
 * Duplicates key into a private buffer and stores value by reference. The
 * caller therefore keeps ownership of the key buffer, while the new pair takes
 * ownership of value.
 *
 * @note On success, ownership of value is transferred to the pair. On failure,
 *       value is not retained and the caller keeps its ownership.
 *
 * @param key NUL-terminated key to copy (borrowed; duplicated internally).
 * @param value Value to store (ownership transferred on success).
 * @return Pointer to the new pair (owned by caller), or NULL on allocation
 *         failure.
 */
t_key_value	*key_value_new(const char *key, void *value);

/**
 * @brief Frees a key/value pair and its contents.
 *
 * Frees the duplicated key, passes the value to del (if provided) and frees
 * the pair itself. The caller's pointer is set to NULL. Safe to call with a
 * NULL pair pointer or a NULL pair.
 *
 * @param pair Address of the pair pointer to free (set to NULL on return).
 * @param del Optional destructor applied to the stored value (may be NULL).
 */
void		key_value_free(t_key_value **pair, void (*del)(void *));

/**
 * @brief Tests whether a pair's key equals the given key.
 *
 * @warning pair and pair->key must not be NULL.
 *
 * @param pair Pair whose key is compared (borrowed).
 * @param key NUL-terminated key to compare against (borrowed).
 * @return true if the keys are equal, false otherwise.
 */
bool		is_matching_key(t_key_value *pair, const char *key);

#endif

```

./libft/src/hashmap/key_value/utils.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:37:44 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 13:50:11 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_matching_key(t_key_value *pair, const char *key)
{
	return (str_ncmp(pair->key, key, str_len(key) + 1) == 0);
}

```

./libft/src/hashmap/priv_hashmap.h
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priv_hashmap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:36:16 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 14:08:43 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIV_HASHMAP_H
# define PRIV_HASHMAP_H

#include "libft.h"

/**
 * @brief Default string hash function (djb2).
 *
 * Computes a hash over the bytes of a NUL-terminated key. The returned value
 * is reduced modulo the bucket count by the caller.
 *
 * @param key NUL-terminated key to hash (borrowed).
 * @return The computed hash value.
 */
size_t		hash_string(const char *key);

// TODO: doc
bool	hashmap_need_resize(t_hashmap *map, const char *key);

/**
 * @brief Doubles the bucket capacity and rehashes every stored pair.
 *
 * Allocates a new bucket array of twice the current capacity, swaps it in and
 * redistributes the existing pairs into it. The pairs themselves are moved,
 * not reallocated. On failure the previous bucket array is restored, leaving
 * the map unchanged.
 *
 * @note Pairs are transferred between bucket arrays; their keys and values are
 *       never freed by a successful resize.
 *
 * @param map Pointer to an initialized map (borrowed).
 * @return true on success, false on memory allocation failure.
 */
bool		hashmap_resize(t_hashmap *map);

/**
 * @brief Inserts a pair into the map, or replaces an existing one.
 *
 * Appends new to its target bucket chain. If a pair with the same key already
 * exists in that bucket, its value is released through the map's del callback
 * and the existing entry adopts new (see bucket_replace), in which case size
 * is left unchanged.
 *
 * @note On success the map takes ownership of new. On failure new is left
 *       untouched and ownership remains with the caller.
 *
 * @param map Pointer to an initialized map (borrowed).
 * @param new Pair to insert (ownership transferred on success).
 * @return true on success, false on memory allocation failure.
 */
bool		hashmap_insert(t_hashmap *map, t_key_value *new);

#endif

```

./libft/src/hashmap/resize.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:53:40 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 15:20:58 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buckets.h"
#include "priv_hashmap.h"

bool	hashmap_need_resize(t_hashmap *map, const char *key)
{
	if (map->buckets.cap == 0)
		return (true);
	if (hashmap_contains(map, key))
		return (false);
	return (map->size + 1 > map->buckets.cap);
}

static void	hashmap_restore(t_hashmap *map, size_t prev_size, t_vector *backup)
{
	map->size = prev_size;
	buckets_detach(&map->buckets);
	buckets_free(&map->buckets, map->del_value);
	buckets_swap(&map->buckets, backup);
}

static bool	hashmap_redistribution(t_hashmap *map, t_vector *prev_buckets)
{
	t_key_value	*pair;
	t_node		*entry;
	size_t		bucket_i;

	bucket_i = 0;
	while (bucket_i < prev_buckets->len)
	{
		entry = ((t_list*)prev_buckets->data)[bucket_i];
		while (entry != NULL)
		{
			pair = entry->content;
			if (pair == NULL)
				return (false);
			if (!hashmap_insert(map, pair))
				return (false);
			entry = entry->next;
		}
		bucket_i++;
	}	
	return (true);
}

bool	hashmap_resize(t_hashmap *map)
{
	size_t		new_cap;
	size_t		prev_size;
	t_vector 	prev_buckets;
	
	prev_size = map->size;
	if (map->buckets.cap == 0)
		new_cap = HASHMAP_INIT_CAP;
	else
		new_cap = map->buckets.cap * 2;
	if (!buckets_init(&prev_buckets, new_cap))
		return (false);
	map->size = 0;
	buckets_swap(&map->buckets, &prev_buckets);
	if (!hashmap_redistribution(map, &prev_buckets))
		return (hashmap_restore(map, prev_size, &prev_buckets), false);
	buckets_detach(&prev_buckets);
	buckets_free(&prev_buckets, map->del_value);
	return (true);
}

```

./libft/src/list/list_apply.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_apply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:48 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:26:09 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	list_iter(t_list lst, void (*f)(void *))
{
	t_node	*node;

	if (!lst || !f)
		return ;
	node = lst;
	while (node)
	{
		f(node->content);
		node = node->next;
	}
}

t_list	list_map(t_list list, void *(*f)(void *), void (*del)(void *))
{
	t_node	*node;
	t_list	new_list;
	void	*new_content;

	if (!list || !f || !del)
		return (NULL);
	node = list;
	new_list = NULL;
	while (node)
	{
		new_content = f(node->content);
		if (!list_add_end(&new_list, new_content))
		{
			del(new_content);
			list_rm_all(&new_list, del);
			return (NULL);
		}
		node = node->next;
	}
	return (new_list);
}

```

./libft/src/list/list_get.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:45 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:26:13 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*list_get_content(t_list list, bool (*select_function)(void*))
{
	t_node	*node;

	if (!list || !select_function)
		return (NULL);
	node = list;
	while (node)
	{
		if (select_function(node->content))
			return (node->content);
		node = node->next;
	}
	return (NULL);
}

void	*list_get_content_n(t_list list, size_t index)
{
	t_node	*node;

	node = list_get_node_n(list, index);
	if (!node)
		return (NULL);
	return (node->content);
}

void	*list_get_content_last(t_list list)
{
	t_node	*last_node;

	last_node = list_get_node_last(list);
	if (!last_node)
		return (NULL);
	return (last_node->content);
}

t_node	*list_get_node_n(t_list list, size_t index)
{
	t_node	*node;

	if (!list)
		return (NULL);
	node = list;
	while (node && index)
	{
		node = node->next;
		index--;
	}
	if (index > 0)
		return (NULL);
	return (node);
}

t_node	*list_get_node_last(t_list list)
{
	t_node	*last_node;

	if (!list)
		return (NULL);
	last_node = list;
	while (last_node->next)
		last_node = last_node->next;
	return (last_node);
}

```

./libft/src/list/list_life_cycle.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_life_cycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 02:56:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:26:15 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

bool	list_add_start(t_list *list, void *new_content)
{
	t_node	*new_node;

	if (!list)
		return (false);
	new_node = node_new(new_content, NULL, *list);
	if (!new_node)
		return (false);
	if (*list)
		(*list)->prev = new_node;
	*list = new_node;
	return (true);
}

bool	list_add_end(t_list *list, void *new_content)
{
	t_node	*new_node;
	t_node	*last_node;

	if (!list)
		return (false);
	new_node = node_new(new_content, NULL, NULL);
	if (!new_node)
		return (false);
	if (!*list)
	{
		*list = new_node;
		return (true);
	}
	last_node = *list;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = new_node;
	new_node->prev = last_node;
	return (true);
}

void	list_rm(t_list *list, t_node *node, void (*del_content)(void*))
{
	t_node	*prev;
	t_node	*next;

	if (!list || !node)
		return ;
	prev = node->prev;
	next = node->next;
	if (prev)
		prev->next = node->next;
	else
		*list = next;
	if (next)
		next->prev = node->prev;
	if (del_content)
		del_content(node->content);
	free(node);
}

void	list_rm_all(t_list *list, void (*del_content)(void*))
{
	t_node	*node;
	t_node	*next;

	if (!list)
		return ;
	node = *list;
	while (node)
	{
		next = node->next;
		if (del_content)
			del_content(node->content);
		free(node);
		node = next;
	}
	*list = NULL;
	return ;
}

```

./libft/src/list/list_size.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 02:56:37 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:26:15 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	list_get_size(t_list list)
{
	size_t	size;
	t_node	*node;

	node = list;
	size = 0;
	while (node)
	{
		size++;
		node = node->next;
	}
	return (size);
}

```

./libft/src/list/node.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 02:56:41 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:26:16 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_node	*node_new(void *content, t_node *prev, t_node *next)
{
	t_node	*new_node;

	new_node = malloc(sizeof * new_node);
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->prev = prev;
	new_node->next = next;
	return (new_node);
}

void	node_free(t_node **node, void (*del_content)(void*))
{
	if (!node || !*node)
		return ;
	if (del_content)
		del_content((*node)->content);
	free(*node);
	*node = NULL;
}

```

./libft/src/malloc/ft_calloc.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:11 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:26:18 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	res = malloc(count * size);
	if (!res)
		return (NULL);
	ft_bzero(res, count * size);
	return (res);
}

```

./libft/src/malloc/ft_realloc.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:30:51 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:26:18 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

bool	ft_realloc(char **buff, size_t cap, size_t newcap)
{
	char	*new_buff;
	size_t	i;

	if (newcap == 0)
	{
		free(*buff);
		*buff = NULL;
		return (true);
	}
	new_buff = malloc(newcap);
	if (!new_buff)
		return (false);
	i = 0;
	while (i < cap)
	{
		new_buff[i] = (*buff)[i];
		i++;
	}
	free(*buff);
	*buff = new_buff;
	return (true);
}

```

./libft/src/math/min_max_abs.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max_abs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 02:28:23 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/23 03:06:28 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"

long	min(long a, long b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

long	max(long a, long b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

size_t	absolute(long nbr)
{
	if (nbr < 0)
		nbr *= -1;
	return ((size_t)nbr);
}

```

./libft/src/math/modulo.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modulo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 21:26:58 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/15 21:26:59 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	modulo(long a, size_t b)
{
	long	res;

	res = a % (long)b;
	if (res < 0)
		res += (long)b;
	return ((size_t)res);
}

```

./libft/src/math/power.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:21:52 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 20:21:53 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	power(int a, int b)
{
	long	res;

	if (b < 0)
		return (0);
	if (b == 0)
		return (1);
	res = 1;
	if (a == 2)
		return (1L << b);
	while (b-- > 0)
		res *= a;
	return (res);
}

```

./libft/src/math/square_root.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_root.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:35:16 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:26:20 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	square_root_exact(int nb)
{
	int	i;

	if (nb <= 0)
		return (-1);
	i = 1;
	while (i <= nb / i)
	{
		if (i * i == nb)
			return (i);
		i++;
	}
	return (-1);
}

int	square_root_rounded(int nb)
{
	int	low;
	int	high;

	if (nb <= 0)
		return (-1);
	high = 1;
	while (high <= nb / high)
		high++;
	low = high - 1;
	if ((nb / low) - low < high - (nb / high))
		return (low);
	return (high);
}

```

./libft/src/mem/ft_bzero.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:08 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:27:16 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

```

./libft/src/mem/ft_memchr.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:57 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:27:22 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		target;
	const unsigned char	*str;
	size_t				i;

	target = (unsigned char) c;
	str = (const unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)str[i] == target)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}

```

./libft/src/mem/ft_memcmp.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:00 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:27:23 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	str1 = (const unsigned char *) s1;
	str2 = (const unsigned char *) s2;
	i = 0;
	while (i < n && str1[i] == str2[i])
		i++;
	if (i == n)
		return (0);
	return (str1[i] - str2[i]);
}

```

./libft/src/mem/ft_memcpy.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:02 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:27:29 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

```

./libft/src/mem/ft_memmove.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:05 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:27:32 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	if (dst < src)
	{
		i = 0;
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else if (dst > src)
	{
		i = len;
		while (i > 0)
		{
			i--;
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		}
	}
	return (dst);
}

```

./libft/src/mem/ft_memset.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:08 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/13 02:52:24 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

```

./libft/src/print/printer.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:22 by gastesan          #+#    #+#             */
/*   Updated: 2026/05/14 20:50:05 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int	ft_vdprintf(int fd, const char *fstring, va_list args)
{
	t_buff	buff;
	bool	success;
	int		written;

	if (fd == -1)
		return (-1);
	buff_init(&buff, 0, NULL, -1);
	success = buff_append_vformat(&buff, fstring, args);
	written = (int)write(fd, buff.data, buff.len);
	buff_free(&buff);
	if (!success)
		return (-1);
	return (written);
}

int	ft_dprintf(int fd, const char *fstring, ...)
{
	va_list	args;
	int		written;

	if (fd == -1)
		return (-1);
	va_start(args, fstring);
	written = ft_vdprintf(fd, fstring, args);
	va_end(args);
	return (written);
}

int	ft_vprintf(const char *fstring, va_list args)
{
	return (ft_vdprintf(STDOUT_FILENO, fstring, args));
}

int	ft_printf(const char *fstring, ...)
{
	va_list	args;
	int		written;

	va_start(args, fstring);
	written = ft_vprintf(fstring, args);
	va_end(args);
	return (written);
}

```

./libft/src/put/ft_putchar_fd.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:10 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:27:58 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

```

./libft/src/put/ft_putendl_fd.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:13 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/14 03:27:59 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		write(fd, "(null)", sizeof("(null)") - 1);
	else
		write(fd, s, str_len(s));
	write(fd, "\n", 1);
}

```

./libft/src/put/ft_putnbr_fd.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:15 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:28:04 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	write_rec(long nbr, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = (long) n;
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr *= -1;
	}
	write_rec(nbr, fd);
}

/**
 * @brief Recursively writes digits of a number.
 *
 * @param nbr Number to write.
 * @param fd File descriptor to write to.
 */
static void	write_rec(long nbr, int fd)
{
	char	c;

	if (nbr >= 10)
		write_rec(nbr / 10, fd);
	c = nbr % 10 + '0';
	write(fd, &c, 1);
}

```

./libft/src/put/ft_putstr_fd.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:17 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/14 03:28:05 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		write(fd, "(null)", sizeof("(null)") - 1);
	else
		write(fd, s, str_len(s));
}

```

./libft/src/str/str_chr.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_strchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:23 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/13 17:10:08 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*str_chr(const char *s, int c)
{
	char	target;

	target = (char) c;
	while (*s)
	{
		if (*s == target)
			return ((char *) s);
		s++;
	}
	if (target == '\0')
		return ((char *) s);
	return (NULL);
}

```

./libft/src/str/str_cmp.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_cmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:44 by gastesan          #+#    #+#             */
/*   Updated: 2026/05/19 23:50:20 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	str_cmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

```

./libft/src/str/str_dup.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:26 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/12 10:46:48 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*str_dup(const char *s1)
{
	char			*res;
	unsigned int	i;

	if (s1 == NULL)
		return (NULL);
	res = malloc(str_len(s1) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

```

./libft/src/str/str_iteri.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_iteri.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:28 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 23:21:55 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	str_iteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

```

./libft/src/str/str_join.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:31 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 23:21:57 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*str_join(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	len = str_len(s1) + str_len(s2);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		res[i++] = s1[j++];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

```

./libft/src/str/str_lcat.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lcat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 23:22:01 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	str_lcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	src_len = str_len(src);
	if (dstsize == 0)
		return (src_len);
	dst_len = str_len(dst);
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	i = 0;
	while (dst_len + i < dstsize - 1 && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

```

./libft/src/str/str_lcpy.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lcpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:36 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 23:22:03 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	str_lcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = str_len(src);
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

```

./libft/src/str/str_len.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:38 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 23:22:05 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	str_len(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

```

./libft/src/str/str_mapi.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_mapi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:41 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 23:22:07 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*str_mapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	res = malloc(str_len(s) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

```

./libft/src/str/str_ncmp.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_ncmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:44 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 23:22:10 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	str_ncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

```

./libft/src/str/str_ncpy.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_ncpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 14:20:57 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/31 14:20:58 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*str_ncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

```

./libft/src/str/str_ndup.c
```c
#include <stdlib.h>

char	*str_ndup(const char *src, size_t len)
{
	char	*res;
	size_t	i;

	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

```

./libft/src/str/str_nstr.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_nstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:47 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 23:22:12 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*str_nstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[i] == '\0')
		return ((char *) haystack);
	while (i < len && haystack[i])
	{
		j = 0;
		while (i + j < len && needle[j] && haystack[i + j] == needle[j])
			j++;
		if (needle[j] == '\0')
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}

```

./libft/src/str/str_rchr.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_rchr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:49 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 23:22:14 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*str_rchr(const char *s, int c)
{
	char	*last;
	char	target;

	last = NULL;
	target = (char) c;
	while (*s)
	{
		if (*s == target)
			last = (char *)s;
		s++;
	}
	if (target == '\0')
		last = (char *)s;
	return (last);
}

```

./libft/src/str/str_split.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:20 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/14 03:46:41 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char		*get_word(char const *s, char sep);

char	**str_split(char const *s, char c)
{
	size_t	i;
	char	**res;

	if (!s)
		return (NULL);
	res = malloc((str_count_words(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			res[i] = NULL;
			res[i] = get_word(s, c);
			if (!res[i++])
				return (str_array_free(&res), NULL);
			while (*s && *s != c)
				s++;
			continue ;
		}
		s++;
	}
	res[i] = NULL;
	return (res);
}

size_t	str_count_words(char const *s, char sep)
{
	size_t	count;
	char	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (!in_word && *s != sep)
		{
			in_word = 1;
			count++;
		}
		else if (in_word && *s == sep)
			in_word = 0;
		s++;
	}
	return (count);
}

/**
 * @brief Extracts a word from a string until the separator.
 *
 * @param s String to extract from.
 * @param sep Delimiter character.
 * @return Newly allocated word, or NULL on failure.
 *
 * @note Caller is responsible for freeing the returned string.
 */
static char	*get_word(char const *s, char sep)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != sep)
		len++;
	return (str_sub(s, 0, len));
}

void	str_array_free(char ***tab_ptr)
{
	size_t	i;

	i = 0;
	while ((*tab_ptr)[i])
		free((*tab_ptr)[i++]);
	free(*tab_ptr);
	*tab_ptr = NULL;
}

```

./libft/src/str/str_str.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 18:56:08 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 19:01:04 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*str_str(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	union u_const_cast
	{
		const char	*str;
		char		*res;
	}	cast;

	cast.str = haystack;
	if (needle == NULL || haystack == NULL)
		return (NULL);
	else if (needle[0] == '\0')
		return (cast.res);
	i = 0;
	while (cast.str[i] != '\0')
	{
		j = 0;
		while (cast.str[i + j] && needle[j] && cast.str[i + j] == needle[j])
			j++;
		if (needle[j] == '\0')
			return (cast.res + i);
		i++;
	}
	return (NULL);
}

```

./libft/src/str/str_sub.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:55 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/13 17:13:04 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*str_sub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	min_len;
	char	*res;

	if (!s)
		return (NULL);
	if (start > str_len(s))
		return (ft_calloc(1, 1));
	min_len = str_len(s + start);
	if (min_len < len)
		res = malloc(min_len + 1);
	else
		res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

```

./libft/src/str/str_trim_leading.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_trim_leading.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:03:30 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 13:04:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static int	ft_is_in_charset(char const c, char const *set);

char	*str_trim_leading(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_is_in_charset(s1[start], set))
		start++;
	end = str_len(s1);
	return (str_sub(s1, (unsigned int)start, end - start));
}

/**
 * @brief Checks if a character is in a set.
 *
 * @param c Character to check.
 * @param set Character set.
 * @return 1 if found, 0 otherwise.
 */
static int	ft_is_in_charset(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

```

./libft/src/str/str_trim.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_trim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:52 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 23:22:21 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static int	ft_is_in_charset(char const c, char const *set);

char	*str_trim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_is_in_charset(s1[start], set))
		start++;
	end = str_len(s1);
	while (end > start && ft_is_in_charset(s1[end - 1], set))
		end--;
	return (str_sub(s1, (unsigned int)start, end - start));
}

/**
 * @brief Checks if a character is in a set.
 *
 * @param c Character to check.
 * @param set Character set.
 * @return 1 if found, 0 otherwise.
 */
static int	ft_is_in_charset(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

```

./libft/src/vector/vector_life_cycle.c
```c
#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

bool	vector_init(t_vector *vector, size_t item_size, size_t cap)
{
	vector->data = NULL;
	vector->cap = 0;
	vector->len = 0;
	vector->item_size = item_size;
	if (item_size == 0)
		return (false);
	if (cap == 0)
		return (true);
	if (cap > SIZE_MAX / item_size)
		return (false);
	vector->data = malloc(cap * item_size);
	if (!vector->data)
		return (false);
	vector->cap = cap;
	return (true);
}

bool	vector_grow(t_vector *vector)
{
	size_t	new_cap;
	void	*new_data;

	if (vector->cap > SIZE_MAX / 2)
		return (false);
	new_cap = vector->cap * 2;
	if (new_cap == 0)
		new_cap = VECTOR_INIT_CAP;
	if (new_cap > SIZE_MAX / vector->item_size)
		return (false);
	new_data = malloc(new_cap * vector->item_size);
	if (!new_data)
		return (false);
	ft_memcpy(new_data, vector->data, vector->len * vector->item_size);
	free(vector->data);
	vector->data = new_data;
	vector->cap = new_cap;
	return (true);
}

bool	vector_adjust(t_vector *vector)
{
	void	*new_data;

	if (vector->len == 0)
	{
		vector_free(vector, NULL);
		return (true);
	}
	if (vector->cap == vector->len)
		return (true);
	new_data = malloc(vector->len * vector->item_size);
	if (!new_data)
		return (false);
	ft_memcpy(new_data, vector->data, vector->len * vector->item_size);
	free(vector->data);
	vector->data = new_data;
	vector->cap = vector->len;
	return (true);
}

bool	vector_dup(t_vector *dst, t_vector *src)
{
	if (dst == src)
		return (false);
	if (!vector_init(dst, src->item_size, src->cap))
		return (false);
	if (!vector_merge(dst, src, 0))
	{
		vector_free(dst, NULL);
		return (false);
	}
	return (true);
}

void	vector_free(t_vector *vector, void (*item_free)(void *item))
{
	size_t	i;
	char	*data;

	if (item_free)
	{
		data = (char *)vector->data;
		i = 0;
		while (i < vector->len)
		{
			item_free(data + (i * vector->item_size));
			i++;
		}
	}
	free(vector->data);
	vector->data = NULL;
	vector->len = 0;
	vector->cap = 0;
}

```

./libft/src/vector/vector_ops_items.c
```c
#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

static bool	grow_and_insert(t_vector *vector, size_t index, const void *item);

bool	vector_push(t_vector *vector, const void *item)
{
	void	*dst;

	if (vector->len == vector->cap)
		if (!vector_grow(vector))
			return (false);
	dst = vector->data + (vector->len * vector->item_size);
	ft_memcpy(dst, item, vector->item_size);
	vector->len++;
	return (true);
}

bool	vector_pop(t_vector *vector, void *dst)
{
	if (vector->len == 0)
		return (false);
	if (dst)
		ft_memcpy(
			dst,
			vector->data + ((vector->len - 1) * vector->item_size),
			vector->item_size);
	vector->len--;
	return (true);
}

bool	vector_insert(t_vector *vector, size_t index, const void *item)
{
	if (index == vector->len)
		return (vector_push(vector, item));
	else if (index > vector->len)
		return (false);
	else if (vector->len == vector->cap)
		return (grow_and_insert(vector, index, item));
	ft_memmove(
		vector->data + ((index + 1) * vector->item_size),
		vector->data + (index * vector->item_size),
		(vector->len - index) * vector->item_size);
	ft_memcpy(
		vector->data + (index * vector->item_size),
		item,
		vector->item_size);
	vector->len++;
	return (true);
}

static bool	grow_and_insert(t_vector *vector, size_t index, const void *item)
{
	size_t	new_cap;
	void	*new_data;

	if (vector->cap > SIZE_MAX / 2)
		return (false);
	new_cap = vector->cap * 2;
	if (new_cap == 0)
		new_cap = VECTOR_INIT_CAP;
	if (new_cap > SIZE_MAX / vector->item_size)
		return (false);
	new_data = malloc(new_cap * vector->item_size);
	if (!new_data)
		return (false);
	vector->cap = new_cap;
	ft_memcpy(new_data, vector->data, index * vector->item_size);
	ft_memcpy(new_data + (index * vector->item_size), item, vector->item_size);
	ft_memcpy(
		new_data + ((index + 1) * vector->item_size),
		vector->data + (index * vector->item_size),
		(vector->len - index) * vector->item_size);
	free(vector->data);
	vector->data = new_data;
	vector->len++;
	return (true);
}

bool	vector_remove(t_vector *vector, size_t index, void *dst)
{
	if (index >= vector->len)
		return (false);
	if (index == vector->len - 1)
		return (vector_pop(vector, dst));
	if (dst)
		ft_memcpy(
			dst,
			vector->data + (index * vector->item_size),
			vector->item_size);
	ft_memmove(
		vector->data + (index * vector->item_size),
		vector->data + ((index + 1) * vector->item_size),
		(vector->len - index - 1) * vector->item_size);
	vector->len--;
	return (true);
}

```

./libft/src/vector/vector_ops_vectors.c
```c
#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

static bool	grow_and_merge(t_vector *dst, t_vector *src, size_t index);
static bool	compute_new_cap(size_t dst_len, size_t src_len, size_t *new_cap);

bool	vector_merge(t_vector *dst, t_vector *src, size_t index)
{
	size_t	target_len;

	if (dst == src)
		return (false);
	if (index > dst->len)
		return (false);
	if (dst->item_size != src->item_size)
		return (false);
	if (dst->len > SIZE_MAX - src->len)
		return (false);
	target_len = dst->len + src->len;
	if (dst->cap < target_len)
		return (grow_and_merge(dst, src, index));
	ft_memmove(
		dst->data + ((index + src->len) * dst->item_size),
		dst->data + (index * dst->item_size),
		(dst->len - index) * dst->item_size);
	ft_memcpy(
		dst->data + (index * dst->item_size),
		src->data,
		src->len * src->item_size);
	dst->len = target_len;
	return (true);
}

static bool	grow_and_merge(t_vector *dst, t_vector *src, size_t index)
{
	size_t	new_cap;
	void	*new_data;

	new_cap = dst->cap;
	if (new_cap == 0)
		new_cap = VECTOR_INIT_CAP;
	if (!compute_new_cap(dst->len, src->len, &new_cap)
		|| new_cap > SIZE_MAX / dst->item_size)
		return (false);
	new_data = malloc(new_cap * dst->item_size);
	if (!new_data)
		return (false);
	ft_memcpy(new_data, dst->data, index * dst->item_size);
	ft_memcpy(
		new_data + ((index + src->len) * dst->item_size),
		dst->data + (index * dst->item_size),
		(dst->len - index) * dst->item_size);
	ft_memcpy(
		new_data + (index * dst->item_size), src->data,
		src->len * dst->item_size);
	free(dst->data);
	dst->data = new_data;
	dst->cap = new_cap;
	dst->len += src->len;
	return (true);
}

static bool	compute_new_cap(size_t dst_len, size_t src_len, size_t *new_cap)
{
	size_t	target_len;
	size_t	tmp_new_cap;

	if (dst_len > SIZE_MAX - src_len)
		return (false);
	target_len = dst_len + src_len;
	if (!new_cap || *new_cap > SIZE_MAX / 2)
		return (false);
	tmp_new_cap = *new_cap;
	while (tmp_new_cap < target_len)
	{
		if (tmp_new_cap > SIZE_MAX / 2)
			return (false);
		tmp_new_cap *= 2;
	}
	*new_cap = tmp_new_cap;
	return (true);
}

```

./libft/tests/buff.c
```c
#include "fut.h"
#include "libft.h"
#include "../src/buff/buff_internal.h"
#include <stdio.h>

#define MAX_LEN 1000000
static size_t	tested_cap[] = {0, 1, 1024, MAX_LEN};
static size_t	tested_len[] = {0, 1, 1024, MAX_LEN};

/*-------------------- init --------------------*/

Test(test_buff_init, 1)
{
	t_buff	buff;

	for (size_t i = 0; i < sizeof tested_cap / sizeof *tested_cap; i++)
	{
		buff_init(&buff, tested_cap[i], NULL, -1);
		assert(0, buff.cap == tested_cap[i]);
		assert_eq(RET, 0, buff.len, 0);
		if (tested_cap[i] == 0)
			assert_eq(RET, 0, buff.data, NULL);
		else
			assert_neq(RET, 0, buff.data, NULL);
		buff_free(&buff);
	}
}

/*-------------------- get_required_cap --------------------*/

Test(test_buff_get_required_cap, 1)
{
	t_buff	buff;
	size_t	result;

	for (size_t i = 0; i < sizeof tested_cap / sizeof *tested_cap; i++)
	{
		for (size_t j = 0; j < sizeof tested_len / sizeof *tested_len; j++)
		{
			buff_init(&buff, tested_cap[i], NULL, -1);
			result = buff_get_required_cap(buff.cap, tested_len[j]);
			if (buff.cap > tested_len[j] || tested_len[j] == 0)
				assert(0, result == buff.cap);
			else
				assert(0, result > tested_len[j]);
			buff_free(&buff);
		}
	}
}

/*-------------------- prepend --------------------*/

static void	test_prepend_n(const char *s1, const char *s2, size_t cap, size_t len)
{
	t_buff	buff;
	char	expected[MAX_LEN * 2];
	size_t	total_len;

	total_len = len * 2;
	memcpy(expected, s2, len);
	memcpy(expected + len, s1, len);

	buff_init(&buff, cap, NULL, -1);
	buff_append(&buff, s1, (long)len);
	buff_prepend(&buff, s2, (long)len);

	if (total_len > 0)
		assert(0, buff.cap > total_len);
	else
		assert_eq(RET, 0, buff.cap, cap);
	assert_eq(RET, 0, buff.len, total_len);
	assert(0, memcmp(buff.data, expected, total_len) == 0);
	
	buff_free(&buff);
}

static void	test_prepend_auto(const char *s1, char *s2, size_t cap, size_t len)
{
	t_buff	buff;
	char	expected[MAX_LEN * 2];
	size_t	total_len;

	if (len == 0)
		return ;
	s2[len] = '\0';

	total_len = len * 2;
	memcpy(expected, s2, len);
	memcpy(expected + len, s1, len);

	buff_init(&buff, cap, NULL, -1);
	buff_append(&buff, s1, (long)len);
	buff_prepend(&buff, s2, -1);

	if (total_len > 0)
		assert(0, buff.cap > total_len);
	else
		assert_eq(RET, 0, buff.cap, cap);
	assert_eq(RET, 0, buff.len, total_len);
	assert(0, memcmp(buff.data, expected, total_len) == 0);
	
	s2[len] = 'B';
	buff_free(&buff);
}

static void	test_prepend_mem(const char *s1, const char *s2, size_t cap, size_t len)
{
	t_buff	buff;
	char	expected[MAX_LEN * 2];

	memcpy(expected, s2, len);
	memcpy(expected + len, s1, len);

	buff_init(&buff, cap, NULL, -1);
	buff_append(&buff, s1, (long)len);
	buff_prepend(&buff, s2, (long)len);
	buff_free(&buff);
}

Test(test_buff_prepend, 1)
{
	char	s1[MAX_LEN];
	char	s2[MAX_LEN];

	memset(s1, 'A', MAX_LEN);
	memset(s2, 'B', MAX_LEN);

	for (size_t i = 0; i < sizeof tested_cap / sizeof *tested_cap; i++)
	{
		for (size_t j = 0; j < sizeof tested_len / sizeof *tested_len; j++)
		{
			test_prepend_n(s1, s2, tested_cap[i], tested_len[j]);
			test_prepend_auto(s1, s2, tested_cap[i], tested_len[j]);
			memleaks(0, test_prepend_mem(s1, s2, tested_cap[i], tested_len[j]));
			memsafety(0, test_prepend_mem(s1, s2, tested_cap[i], tested_len[j]));
		}
	}
}

/*-------------------- insert --------------------*/

static void	test_insert_n(const char *s1, const char *s2, size_t cap, size_t len, size_t i)
{
	t_buff		buff;
	char		expected[MAX_LEN * 2];
	size_t		total_len;

	total_len = len * 2;
	memcpy(expected, s1, i);
	memcpy(expected + i, s2, len);
	memcpy(expected + i + len, s1, len - i);

	buff_init(&buff, cap, NULL, -1);
	buff_append(&buff, s1, (long)len);
	buff_insert(&buff, i, s2, (long)len);

	if (total_len > 0)
		assert(0, buff.cap > total_len);
	else
		assert_eq(RET, 0, buff.cap, cap);
	assert_eq(RET, 0, buff.len, total_len);
	assert(0, memcmp(buff.data, expected, total_len) == 0);

	buff_free(&buff);
}

static void	test_insert_auto(const char *s1, char *s2, size_t cap, size_t len, size_t i)
{
	t_buff		buff;
	char		expected[MAX_LEN * 2];
	size_t		total_len;

	if (len == 0)
		return ;
	s2[len] = '\0';

	total_len = len * 2;
	memcpy(expected, s1, i);
	memcpy(expected + i, s2, len);
	memcpy(expected + i + len, s1, len - i);

	buff_init(&buff, cap, NULL, -1);
	buff_append(&buff, s1, (long)len);
	buff_insert(&buff, i, s2, -1);

	if (total_len > 0)
		assert(0, buff.cap > total_len);
	else
		assert_eq(RET, 0, buff.cap, cap);
	assert_eq(RET, 0, buff.len, total_len);
	assert(0, memcmp(buff.data, expected, total_len) == 0);
	s2[len] = 'B';
	buff_free(&buff);
}

static void	test_insert_mem(const char *s1, const char *s2, size_t cap, size_t len, size_t i)
{
	t_buff		buff;
	char		expected[MAX_LEN * 2];

	memcpy(expected, s1, i);
	memcpy(expected + i, s2, len);
	memcpy(expected + i + len, s1, len - i);

	buff_init(&buff, cap, NULL, -1);
	buff_append(&buff, s1, (long)len);
	buff_insert(&buff, i, s2, (long)len);
	buff_free(&buff);
}

Test(test_buff_insert, 1)
{
	char	s1[MAX_LEN + 1];
	char	s2[MAX_LEN + 1];

	memset(s1, 'A', MAX_LEN);
	memset(s2, 'B', MAX_LEN);
	for (size_t i = 0; i < sizeof tested_cap / sizeof *tested_cap; i++)
	{
		for (size_t j = 0; j < sizeof tested_len / sizeof *tested_len; j++)
		{
			test_insert_n(s1, s2, tested_cap[i], tested_len[j], 0);
			test_insert_auto(s1, s2, tested_cap[i], tested_len[j], 0);
			memleaks(0, test_insert_mem(s1, s2, tested_cap[i], tested_len[j], 0));
			memsafety(0, test_insert_mem(s1, s2, tested_cap[i], tested_len[j], 0));
			if (tested_len[j] == 0)
				continue ;
			test_insert_n(s1, s2, tested_cap[i], tested_len[j], tested_len[j] / 2);
			test_insert_auto(s1, s2, tested_cap[i], tested_len[j], tested_len[j] / 2);
			memleaks(0, test_insert_mem(s1, s2, tested_cap[i], tested_len[j], tested_len[j] / 2));
			memsafety(0, test_insert_mem(s1, s2, tested_cap[i], tested_len[j], tested_len[j] / 2));
			test_insert_n(s1, s2, tested_cap[i], tested_len[j], tested_len[j]);
			test_insert_auto(s1, s2, tested_cap[i], tested_len[j], tested_len[j]);
			memleaks(0, test_insert_mem(s1, s2, tested_cap[i], tested_len[j], tested_len[j]));
			memsafety(0, test_insert_mem(s1, s2, tested_cap[i], tested_len[j], tested_len[j]));
		}
	}
}

/*-------------------- append --------------------*/

static void test_append_n(const char *s1, char *s2, size_t cap, size_t len)
{
	t_buff	buff;
	char	expected[MAX_LEN * 2];
	size_t	total_len;

	total_len = len * 2;
	memcpy(expected, s1, len);
	memcpy(expected + len, s2, len);

	buff_init(&buff, cap, NULL, -1);
	buff_append(&buff, s1, (long)len);
	buff_append(&buff, s2, (long)len);

	if (total_len > 0)
		assert(0, buff.cap > total_len);
	else
		assert_eq(RET, 0, buff.cap, cap);
	assert_eq(RET, 0, buff.len, total_len);
	assert(0, memcmp(buff.data, expected, total_len) == 0);
	
	buff_free(&buff);
}

static void test_append_auto(const char *s1, char *s2, size_t cap, size_t len)
{
	t_buff	buff;
	char	expected[MAX_LEN * 2];
	size_t	total_len;

	if (len == 0)
		return ;
	s2[len] = '\0';

	total_len = len * 2;
	memcpy(expected, s1, len);
	memcpy(expected + len, s2, len);

	buff_init(&buff, cap, NULL, -1);
	buff_append(&buff, s1, (long)len);
	buff_append(&buff, s2, (long)-1);

	if (total_len > 0)
		assert(0, buff.cap > total_len);
	else
		assert_eq(RET, 0, buff.cap, cap);
	assert_eq(RET, 0, buff.len, total_len);
	assert(0, memcmp(buff.data, expected, total_len) == 0);
	
	s2[len] = 'B';
	buff_free(&buff);
}

static void test_append_mem(const char *s1, char *s2, size_t cap, size_t len)
{
	t_buff	buff;
	char	expected[MAX_LEN * 2];

	memcpy(expected, s1, len);
	memcpy(expected + len, s2, len);

	buff_init(&buff, cap, NULL, -1);
	buff_append(&buff, s1, (long)len);
	buff_append(&buff, s2, (long)len);
	buff_free(&buff);
}

Test(test_buff_append, 1)
{
	char	s1[MAX_LEN];
	char	s2[MAX_LEN];

	memset(s1, 'A', MAX_LEN);
	memset(s2, 'B', MAX_LEN);

	for (size_t i = 0; i < sizeof tested_cap / sizeof *tested_cap; i++)
	{
		for (size_t j = 0; j < sizeof tested_len / sizeof *tested_len; j++)
		{
			test_append_n(s1, s2, tested_cap[i], tested_len[j]);
			test_append_auto(s1, s2, tested_cap[i], tested_len[j]);
			memleaks(0, test_append_mem(s1, s2, tested_cap[i], tested_len[j]));
			memsafety(0, test_append_mem(s1, s2, tested_cap[i], tested_len[j]));
		}
	}
}

```

./libft/tests/isincharset.c
```c
#include "fut.h"
#include "libft.h"

Test(test_isincharset, 0)
{
	static const char	charset[] = "%csdiuxXp";
	size_t				charset_size;
	size_t				i;

	charset_size = sizeof charset / sizeof *charset - 1;
	i = 0;
	while (i < charset_size)
	{
		assert_eq(RET, 1, ft_isincharset(charset[i], charset), true);
		i++;
	}
	assert_eq(RET, 1, ft_isincharset('a', charset), false);
	assert_eq(RET, 1, ft_isincharset('P', charset), false);
	assert_eq(RET, 1, ft_isincharset('\0', charset), false);
}

```

./libft/tests/ltoa.c
```c
#include "fut.h"
#include "libft.h"
#include <limits.h>
#include <stdio.h>

static void	test_ft_itoa(int n, const char *expected)
{
	char	*result;

	result = ft_itoa(n);
	assert_eq(RET, 0, result, expected);
	free(result);
}

static void	test_ft_utoa(unsigned int n, const char *expected)
{
	char	*result;

	result = ft_utoa(n);
	assert_eq(RET, 0, result, expected);
	free(result);
}

static void	test_ft_ltoa(long n, const char *expected)
{
	char	*result;

	result = ft_ltoa(n);
	assert_eq(RET, 0, result, expected);
	free(result);
}

Test(test_itoa, 1)
{
	test_ft_itoa(0, "0");
	test_ft_itoa(-0, "0");
	test_ft_itoa(+0, "0");
	test_ft_itoa(-1, "-1");
	test_ft_itoa(42, "42");
	test_ft_itoa(INT_MIN, "-2147483648");
	test_ft_itoa(INT_MAX, "2147483647");
}

Test(test_utoa, 1)
{
	test_ft_utoa(0, "0");
	test_ft_utoa(-0, "0");
	test_ft_utoa(+0, "0");
	test_ft_utoa(42, "42");
	test_ft_utoa(INT_MAX, "2147483647");
	test_ft_utoa(UINT_MAX, "4294967295");
}

Test(test_ltoa, 1)
{
	test_ft_ltoa(0, "0");
	test_ft_ltoa(-0, "0");
	test_ft_ltoa(+0, "0");
	test_ft_ltoa(-1, "-1");
	test_ft_ltoa(42, "42");
	test_ft_ltoa(LONG_MIN, "-9223372036854775808");
	test_ft_ltoa(INT_MIN, "-2147483648");
	test_ft_ltoa(INT_MAX, "2147483647");
	test_ft_ltoa(UINT_MAX, "4294967295");
	test_ft_ltoa(LONG_MAX, "9223372036854775807");
}

```

./libft/tests/realloc.c
```c
#include "fut.h"
#include "libft.h"

#define MAX_LEN 1000000

static void	_test_realloc(size_t cap, size_t new_cap, char control_string[MAX_LEN])
{
	char	*buff;
	bool	realloc_res;

	if (cap == 0)
		buff = NULL;
	else
		buff = malloc(cap);
	memset(buff, 'A', cap);

	realloc_res = ft_realloc(&buff, cap, new_cap);
	assert_eq(RET, 0, realloc_res, true);
	if (new_cap == 0)
		assert_eq(RET, 0, buff, NULL);
	else
	{
		assert_neq(RET, 0, buff, NULL);
		assert_eq(RET, 0, memcmp(buff, control_string, cap), 0);
	}
	free(buff);
}

static void	_fail_realloc(size_t new_cap)
{
	char	*buff;
	bool	realloc_res;

	buff = NULL;
	realloc_res = ft_realloc(&buff, 0, new_cap);
	if (new_cap == 0)
		assert_eq(RET, 0, realloc_res, true);
	else
		assert_eq(RET, 0, realloc_res, false);
	assert_eq(RET, 0, buff, NULL);
	free(buff);
}

Test(test_realloc, 1)
{
	char	control_string[MAX_LEN];

	memset(control_string, 'A', MAX_LEN);

	_test_realloc(0, 0, control_string);
	_test_realloc(0, MAX_LEN, control_string);
	_test_realloc(MAX_LEN / 2, MAX_LEN, control_string);
	_test_realloc(MAX_LEN, MAX_LEN, control_string);
	_test_realloc(MAX_LEN, MAX_LEN / 2, control_string);
	_test_realloc(MAX_LEN, 0, control_string);

	memleaks(0, _test_realloc(0, 0, control_string));
	memleaks(0, _test_realloc(0, MAX_LEN, control_string));
	memleaks(0, _test_realloc(MAX_LEN / 2, MAX_LEN, control_string));
	memleaks(0, _test_realloc(MAX_LEN, MAX_LEN, control_string));
	memleaks(0, _test_realloc(MAX_LEN, MAX_LEN / 2, control_string));
	memleaks(0, _test_realloc(MAX_LEN, 0, control_string));

	memsafety(0, _fail_realloc(0));
	memsafety(0, _fail_realloc(MAX_LEN / 2));
	memsafety(0, _fail_realloc(MAX_LEN));
}

```

./libft/tests/ultoa_base.c
```c
#include "fut.h"
#include "libft.h"
#include <limits.h>

static void	test_ft_ultoa_base(unsigned long n, const char *base, const char *expected)
{
	char	*result;

	result = ft_ultoa_base(n, base);
	assert_eq(RET, 1, result, expected);
	free(result);
}

Test(test_ultoa_base, 0)
{
	test_ft_ultoa_base(0, "0123456789", "0");
	test_ft_ultoa_base(1, "0123456789", "1");
	test_ft_ultoa_base(42, "0123456789", "42");
	test_ft_ultoa_base(ULONG_MAX, "0123456789", "18446744073709551615");

	test_ft_ultoa_base(0, "0123456789abcdef", "0");
	test_ft_ultoa_base(255, "0123456789abcdef", "ff");
	test_ft_ultoa_base(ULONG_MAX, "0123456789ABCDEF", "FFFFFFFFFFFFFFFF");
	test_ft_ultoa_base(3735928559UL, "0123456789ABCDEF", "DEADBEEF");

	test_ft_ultoa_base(0, "01", "0");
	test_ft_ultoa_base(1, "01", "1");
	test_ft_ultoa_base(5, "01", "101");
	test_ft_ultoa_base(ULONG_MAX, "01", "1111111111111111111111111111111111111111111111111111111111111111");

	assert_eq(RET, 0, ft_ultoa_base(10, ""), NULL);
	assert_eq(RET, 0, ft_ultoa_base(10, "0"), NULL);
	assert_eq(RET, 0, ft_ultoa_base(10, NULL), NULL);
}

```

./logs/0_check.c
```c
#include "logs.h"

t_depth	g_depth = {DEFAULT_DEPTH_CURR, DEFAULT_DEPTH_MIN, DEFAULT_DEPTH_MAX};

bool	should_print(t_style style)
{
	return (should_print_as(style) != HIDDEN);
}

t_style	should_print_as(t_style style)
{
	if (style == FORCED)
		return (style);
	if (g_depth.min < 0 || g_depth.max < 0)
		return (HIDDEN);
	if (g_depth.curr >= g_depth.min && g_depth.curr <= g_depth.max)
		return (style);
	if (style == RESULT && g_depth.curr == g_depth.max + 1)
		return (LOG);
	return (HIDDEN);
}

```

./logs/1_life_cycle.c
```c
#include "logs.h"
#include "logs_priv.h"

void	print_start(size_t layers_count, const char *optional_title)
{
	long	future_min;
	long	future_display_depth;

	if (g_depth.curr < 0)
		g_depth.curr = 0;
	if (g_depth.min <= 0 || g_depth.min > g_depth.curr)
		future_min = g_depth.curr;
	else
		future_min = g_depth.min;
	future_display_depth = DEPTH_OF(g_depth.curr, future_min);
	if (DEPTH > 0 && DEPTH != future_display_depth)
	{
		if (future_display_depth <= 0)
			print_link(-PADDING_LEN, GREY, true);
		else
		{
			_print_padding(DEFAULT_PAD, PADDING_LEN);
			print_link(PADDING_LEN_OF((future_display_depth - DEPTH)), GREY, true);
		}
	}
	g_depth.min = future_min;
	g_depth.max = g_depth.curr + ((long)layers_count - 1);
	if (optional_title)
		print_log("%s⌽%s LOGS STARTED ⇢ %s%s\n", GREEN, BOLD_YELLOW, optional_title, NC);
	else
		print_log("%s⌽%s LOGS STARTED\n", GREEN, BOLD_YELLOW);
}

void	print_reset(void)
{
	long	future_display_depth;

	print_log("%s⍟ LOGS RESETED%s\n", BOLD_YELLOW, NC);
	if (g_depth.curr >= DEFAULT_DEPTH_MIN && g_depth.curr <= DEFAULT_DEPTH_MAX)
		return ;
	future_display_depth = DEPTH_OF(g_depth.curr, DEFAULT_DEPTH_MIN);
	if (future_display_depth <= 0)
		print_link(-PADDING_LEN, GREY, true);
	else if (future_display_depth > 0)
		print_link(PADDING_LEN_OF((future_display_depth - DEPTH)), GREY, true);
	g_depth.min = DEFAULT_DEPTH_MIN;
	g_depth.max = DEFAULT_DEPTH_MAX;
}

void	print_stop(void)
{
	print_log("%s⍉%s LOGS STOPPED%s\n", BOLD_RED, YELLOW, NC);
	if (DEPTH > 0)
		print_link(-(PADDING_LEN + 1), GREY, true);
	g_depth.min = -1;
	g_depth.max = -1;
}

```

./logs/2_blocks.c
```c
#include "logs.h"
#include "logs_priv.h"
#include <stdio.h>

void	print_as(t_style style, bool padding, bool new_line, const char *fmt, ...)
{
	va_list	args;

	if (!should_print(style))
		return ;
	if (padding)
	{
		if (style == RESULT && should_print_as(style) == LOG)
			_print_padding(DEFAULT_PAD, PADDING_LEN_OF(DEPTH - 1));
		else
			_print_padding(DEFAULT_PAD, PADDING_LEN);
	}
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	if (new_line)
		fprintf(stderr, "\n");
}

void	print_link(long len, const char *color, bool new_line)
{
	if (len == 0)
		return ;
	else if (len == 1)
		fprintf(stderr, "%s\\%s", color, NC);
	else if (len == -1)
		fprintf(stderr, "%s/%s", color, NC);
	else if (len > 0)
	{
		fprintf(stderr, "%s╰", color);
		_print_padding("─", len - 2);
		fprintf(stderr, "╮%s", NC);
	}
	else if (len < 0)
	{
		len *= -1;
		fprintf(stderr, "%s╭", color);
		_print_padding("─", len - 2);
		fprintf(stderr, "╯%s", NC);
	}
	if (new_line)
		fprintf(stderr, "\n");
}

void	print_padding(t_style style, const char *pad, long padding_len)
{
	if (should_print(style))
		_print_padding(pad, padding_len);
}

void	_print_padding(const char *pad, long padding_len)
{
	char	res[TITLE_MAX_LEN];
	long	i;
	size_t	j;
	size_t	k;

	if (padding_len <= 0)
		return ;
	res[0] = '\0';
	i = 0;
	j = 0;
	while (i < padding_len && j < TITLE_MAX_LEN - 1)
	{
		k = 0;
		while (pad[k] && j < TITLE_MAX_LEN - 1)
			res[j++] = pad[k++];
		i++;
	}
	res[j] = '\0';
	fprintf(stderr, "%s", res);
}

void	print_array_u(t_style style, uint *array, size_t len, const char *array_color, const char *value_color, uint value, bool nl)
{
	uint	current;
	size_t	i;

	if (!should_print(style))
		return ;
	fprintf(stderr, "%s[", array_color);
	i = 0;
	while (i < len)
	{
		current = array[i];
		if (current == value)
			fprintf(stderr, "%s%u%s", value_color, array[i], array_color);
		else
			fprintf(stderr, "%u", array[i]);
		if (i < len - 1)
			fprintf(stderr, " ");
		i++;
	}
	fprintf(stderr, "]%s", NC);
	if (nl)
		fprintf(stderr, "\n");
}

void	print_array_zu(t_style style, size_t *array, size_t len, const char *array_color, const char *value_color, size_t value, bool nl)
{
	size_t	current;
	size_t	i;

	if (!should_print(style))
		return ;
	fprintf(stderr, "%s[", array_color);
	i = 0;
	while (i < len)
	{
		current = array[i];
		if (current == value)
			fprintf(stderr, "%s%zu%s", value_color, array[i], array_color);
		else
			fprintf(stderr, "%zu", array[i]);
		if (i < len - 1)
			fprintf(stderr, " ");
		i++;
	}
	fprintf(stderr, "]%s", NC);
	if (nl)
		fprintf(stderr, "\n");
}

/* -------------------- OLD -------------------- */

void	log_debug(const char *func_name, size_t depth, const char *message, ...)
{
	va_list args;
	
	va_start(args, message);
	while (depth--)
		fprintf(stderr, "%s>", BOLD_YELLOW);
	fprintf(stderr, "%s> 🔦 %s()%s ", BOLD_YELLOW, func_name, NC);
	vfprintf(stderr, message, args);
	va_end(args);
}

```

./logs/3_title.c
```c
#define _GNU_SOURCE
#include "libft.h"
#include "logs.h"
#include "logs_priv.h"
#include <stdlib.h>
#include <stdio.h>

static void	_print_title_top(bool new_line);
static void	_print_title_mid(bool new_line, const char *fmt, va_list args);

void	print_title(const char *fmt, ...)
{
	va_list	args;

	g_depth.curr++;
	if (!should_print(TITLE))
		return ;
	_print_title_top(true);
	va_start(args, fmt);
	_print_title_mid(true, fmt, args);
	va_end(args);
}

void	print_title_top(bool new_line)
{
	g_depth.curr++;
	if (should_print(TITLE))
		_print_title_top(new_line);
}

void	print_title_mid(bool new_line, const char *fmt, ...)
{
	va_list	args;

	if (!should_print(TITLE))
		return ;
	va_start(args, fmt);
	_print_title_mid(new_line, fmt, args);
	va_end(args);
}

static void	_print_title_top(bool new_line)
{
	if (DEPTH < 0)
		return ;
	if (DEPTH == 0)
		fprintf(stderr, "%s│%s\n", TITLE_COLOR, NC);
	else if (DEPTH > 1)
		_print_padding(DEFAULT_PAD, PADDING_LEN_OF((DEPTH - 1)));
	if (DEPTH > 0)
		print_link(PADDING_LEN_OF(1) + 1, TITLE_COLOR, new_line);
}

static void	_print_title_mid(bool new_line, const char *fmt, va_list args)
{
	int		len;
	int		i;
	char	*formatted;

	len = vasprintf(&formatted, fmt, args);
	if (len < 0)
		return ;
	i = 0;
	while (i < len)
	{
		formatted[i] = (char)ft_toupper(formatted[i]);
		i++;
	}
	_print_padding(DEFAULT_PAD, PADDING_LEN);
	fprintf(stderr, "%s⏺ %s%s", TITLE_COLOR, formatted, NC);
	free(formatted);
	if (new_line)
		fprintf(stderr, "\n");
}

```

./logs/4_log.c
```c
#include "logs.h"
#include "logs_priv.h"
#include <stdio.h>

void	print_log(const char *fmt, ...)
{
	va_list	args;

	if (!should_print(LOG))
		return ;
	va_start(args, fmt);
	_print_log_custom(F_NONE, true, false, fmt, args);
	va_end(args);
}

void	print_info(const char *fmt, ...)
{
	va_list	args;

	if (!should_print(LOG))
		return ;
	va_start(args, fmt);
	_print_log_custom(INFO, true, false, fmt, args);
	va_end(args);
}

void	print_warn(const char *fmt, ...)
{
	va_list	args;

	if (!should_print(LOG))
		return ;
	va_start(args, fmt);
	_print_log_custom(WARN, true, false, fmt, args);
	va_end(args);
}

void	print_pass(const char *fmt, ...)
{
	va_list	args;

	if (!should_print(LOG))
		return ;
	va_start(args, fmt);
	_print_log_custom(PASS, true, false, fmt, args);
	va_end(args);
}

void	print_log_custom(t_format format, bool indent, bool new_line, const char *fmt, ...)
{
	va_list	args;

	if (!should_print(LOG))
		return ;
	va_start(args, fmt);
	_print_log_custom(format, indent, new_line, fmt, args);
	va_end(args);
}

void	_print_log_custom(t_format format, bool indent, bool new_line, const char *fmt, va_list args)
{
	if (indent)
		_print_padding(DEFAULT_PAD, PADDING_LEN);
	if (format == INFO)
		fprintf(stderr, "%s⏺ ", GREY);
	else if (format == WARN)
		fprintf(stderr, "%s⚑ %s", YELLOW, GREY);
	else if (format == PASS)
		fprintf(stderr, "%s✔ %s", GREEN, GREY);
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "%s", NC);
	if (new_line)
		fprintf(stderr, "\n");
}

```

./logs/5_result.c
```c
#define _GNU_SOURCE
#include "libft.h"
#include "logs.h"
#include "logs_priv.h"
#include <stdio.h>
#include <stdlib.h>

static void	_print_result_mid(bool new_line, const char *fmt, va_list args);
static void	_print_result_bot(bool new_line);

void	print_result(const char *fmt, ...)
{
	va_list	args;

	if (should_print(RESULT))
	{
		va_start(args, fmt);
		if (should_print_as(RESULT) == LOG)
		{
			_print_padding(DEFAULT_PAD, PADDING_LEN_OF((DEPTH - 1)));
			_print_log_custom(PASS, false, true, fmt, args);
			fprintf(stderr, "%s", NC);
		}
		else
		{
			_print_result_mid(true, fmt, args);
			_print_result_bot(true);
		}
		va_end(args);
	}
	if (g_depth.curr >= 0)
		g_depth.curr--;
}

void	print_result_mid(bool new_line, const char *fmt, ...)
{
	va_list	args;

	if (!should_print(RESULT))
		return ;
	va_start(args, fmt);
	if (should_print_as(RESULT) == LOG)
	{
		_print_padding(DEFAULT_PAD, PADDING_LEN_OF((DEPTH - 1)));
		_print_log_custom(PASS, false, new_line, fmt, args);
	}
	else
	{
		_print_result_mid(new_line, fmt, args);
	}
	va_end(args);
}

void	print_result_bot(bool new_line)
{
	if (should_print(TITLE))
		_print_result_bot(new_line);
	if (g_depth.curr >= 0)
		g_depth.curr--;
}

static void	_print_result_mid(bool new_line, const char *fmt, va_list args)
{
	int		len;
	int		i;
	char	*formatted;

	len = vasprintf(&formatted, fmt, args);
	if (len < 0)
		return ;
	i = 0;
	while (i < len)
	{
		formatted[i] = (char)ft_toupper(formatted[i]);
		i++;
	}
	_print_padding(DEFAULT_PAD, PADDING_LEN);
	fprintf(stderr, "%s⍟ %s", RESULT_COLOR, formatted);
	free(formatted);
	if (new_line)
		fprintf(stderr, "\n");
}

static void	_print_result_bot(bool new_line)
{
	if (DEPTH <= 0)
		return ;
	_print_padding(DEFAULT_PAD, PADDING_LEN_OF((DEPTH - 1)));
	print_link(-(PADDING_LEN_OF(1) + 1), RESULT_COLOR, new_line);
}

```

./logs/6_error.c
```c
#include "logs.h"
#include "logs_priv.h"
#include <stdio.h>

static void	print_here(const char *fmt, va_list args);
static void print_ahead(const char *fmt, va_list args);

void	print_error(const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	if (g_depth.max >= 0 && g_depth.max < g_depth.curr)
		print_ahead(fmt, args);
	else
		print_here(fmt, args);
	va_end(args);
}

static void	print_here(const char *fmt, va_list args)
{
	_print_padding(DEFAULT_PAD, PADDING_LEN);
	fprintf(stderr, "%s⚑ ERROR AT DEPTH %ld ⇢ %s", BOLD_RED, g_depth.curr, NC);
	vfprintf(stderr, fmt, args);
}

static void print_ahead(const char *fmt, va_list args)
{
	_print_padding(DEFAULT_PAD, PADDING_LEN_OF((g_depth.max - g_depth.min)));
	print_link(LINK_LEN_OF(1), RED, true);
	_print_padding(DEFAULT_PAD, PADDING_LEN_OF((g_depth.max - g_depth.min + 1)));
	fprintf(stderr, "%s⚑ ERROR AT DEPTH %ld ⇢ %s", BOLD_RED, g_depth.curr, NC);
	vfprintf(stderr, fmt, args);
	print_link(-LINK_LEN_OF(1), RED, false);
}

```

./logs/logs_priv.h
```c
#ifndef LOGS_PRIV_H
# define LOGS_PRIV_H

# include "logs.h"
# include <stdarg.h>

# define TITLE_MAX_LEN	128

void	_print_padding(const char *pad, long padding_len);
void	_print_log_custom(t_format format, bool indent, bool new_line, const char *fmt, va_list args);

#endif

```

./logs/logs.h
```c
#ifndef LOGS_H
# define LOGS_H

# include <stdbool.h>
# include <sys/types.h>

/* ---------- TYPES ---------- */

typedef enum e_style
{
	TITLE,
	LOG,
	RESULT,
	HIDDEN,
	FORCED
}	t_style;

typedef enum e_format
{
	F_NONE,
	INFO,
	WARN,
	PASS
}	t_format;

typedef struct s_depth
{
	long	curr;
	long	min;
	long	max;
}	t_depth;

extern t_depth	g_depth;

/* ---------- COLORS ---------- */

# define GREY "\033[0;90m"
# define BOLD_GREY "\033[1;90m"
# define GREEN "\033[0;32m"
# define BOLD_GREEN "\033[1;32m"
# define BLUE "\033[0;34m"
# define BOLD_BLUE "\033[1;34m"
# define RED "\033[0;31m"
# define BOLD_RED "\033[1;31m"
# define YELLOW "\033[0;33m"
# define BOLD_YELLOW "\033[1;33m"
# define NC "\033[0m"

/* ---------- SETTINGS ---------- */

# define DEFAULT_DEPTH_CURR	-1
# define DEFAULT_DEPTH_MIN	-1
# define DEFAULT_DEPTH_MAX	-1
# define DEFAULT_PAD		" "
# define PADDING_SIZE		6
# define TITLE_COLOR		BOLD_BLUE
# define RESULT_COLOR		BOLD_GREEN

/* ---------- GETTERS ---------- */

# define DEPTH_OF(current, min)	(min < 0 ? -2 : current - min)
# define DEPTH					DEPTH_OF(g_depth.curr, g_depth.min)
# define PADDING_LEN_OF(depth)	(depth * PADDING_SIZE)
# define PADDING_LEN			PADDING_LEN_OF(DEPTH)
# define LINK_LEN_OF(depth)		(PADDING_LEN_OF(depth) + 1)

/* ---------- DEBUG ---------- */

#include <stdio.h>
inline void	print_depth(void)
{
	fprintf(stderr, "DEPTH = %ld | curr = %ld | min = %ld | max = %ld\n", DEPTH, g_depth.curr, g_depth.min, g_depth.max);
}

/* ---------- check.c ---------- */

bool	should_print(t_style style);
t_style	should_print_as(t_style style);

/* ---------- life_cycle.c ---------- */

void	print_start(size_t layers_count, const char *optional_title);
void	print_reset(void);
void	print_stop(void);

/* ---------- blocks.c ---------- */

void	print_as(t_style style, bool padding, bool new_line, const char *fmt, ...)			__attribute__((format(printf, 4, 5)));
void	print_link(long len, const char *color, bool new_line);
void	print_padding(t_style style, const char *pad, long padding_len);
void	print_array_u(t_style style, uint *array, size_t len, const char *array_color, const char *value_color, uint value, bool nl);
void	print_array_zu(t_style style, size_t *array, size_t len, const char *array_color, const char *value_color, size_t value, bool nl);

/* ---------- error.c ---------- */

void	print_error(const char *fmt, ...)													__attribute__((format(printf, 1, 2)));

/* ---------- title.c ---------- */

void	print_title(const char *fmt, ...)													__attribute__((format(printf, 1, 2)));
void	print_title_top(bool new_line);
void	print_title_mid(bool new_line, const char *fmt, ...)								__attribute__((format(printf, 2, 3)));

/* ---------- log.c ---------- */

void	print_log(const char *fmt, ...)														__attribute__((format(printf, 1, 2)));
void	print_info(const char *fmt, ...)													__attribute__((format(printf, 1, 2)));
void	print_warn(const char *fmt, ...)													__attribute__((format(printf, 1, 2)));
void	print_pass(const char *fmt, ...)													__attribute__((format(printf, 1, 2)));
void	print_log_custom(t_format format, bool indent, bool new_line, const char *fmt, ...) __attribute__((format(printf, 4, 5)));

/* ---------- result.c ---------- */

void	print_result(const char *fmt, ...)													__attribute__((format(printf, 1, 2)));
void	print_result_mid(bool new_line, const char *fmt, ...)								__attribute__((format(printf, 2, 3)));
void	print_result_bot(bool new_line);

#endif

```

./Makefile
```makefile
NAME			:= minishell
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -O2
DEBUG_CFLAGS	:= -Wall -Wextra -Werror -g3 -fsanitize=address,undefined

LIBFT_DIR		:= libft
LIBFT			:= $(LIBFT_DIR)/libft.a
READLINE_DIR	:= $(shell brew --prefix readline 2>/dev/null)

# DEBUG SECTION (START)
TEST_DIR		:= ./tests
TESTERS			:= $(wildcard $(TEST_DIR)/*.zsh)
FIXTURES_DIR	:= $(TEST_DIR)/fixtures
LOGS_DIR		:= $(TEST_DIR)/logs
# DEBUG SECTION (END)

SRCS			:= \
	$(wildcard logs/*.c) \
	$(wildcard srcs/*.c) \
	$(wildcard srcs/0_asm_stubs/*/*.c) \
	$(wildcard srcs/0_context/*.c) \
	$(wildcard srcs/0_context/*/*.c) \
	$(wildcard srcs/0_posix_helpers/*.c) \
	$(wildcard srcs/0_token/*.c) \
	$(wildcard srcs/0_utils/*.c) \
	$(wildcard srcs/0_utils/*/*.c) \
	$(wildcard srcs/1_shell/*.c) \
	$(wildcard srcs/2_scanner/*.c) \
	$(wildcard srcs/2_scanner/*/*.c) \
	$(wildcard srcs/2_scanner/*/*/*.c) \
	$(wildcard srcs/3_builder/*.c) \
	$(wildcard srcs/3_builder/*/*.c) \
	$(wildcard srcs/3_builder/*/*/*.c) \
	$(wildcard srcs/3_builder/*/*/*/*.c) \
	$(wildcard srcs/4_runner/*.c) \
	$(wildcard srcs/builtins/*.c) \
	$(wildcard srcs/expander/*.c) \
	$(wildcard srcs/expander/*/*.c) \
	$(wildcard srcs/expander/*/*/*.c) \
	$(wildcard srcs/history/*.c) \
	$(wildcard srcs/history/*/*.c) \
	$(wildcard srcs/params/*.c) \
	$(wildcard srcs/params/*/*.c) \
	$(wildcard srcs/params/*/*/*.c) \
	$(wildcard srcs/params/*/*/*/*.c) \
	$(wildcard srcs/params/*/*/*/*/*.c) \
	$(wildcard srcs/alias/*.c) \
	$(wildcard srcs/alias/*/*.c) \
	$(wildcard srcs/heredoc/*.c) \
	$(wildcard srcs/heredoc/*/*.c) \

INCLUDES		:= \
	-I$(READLINE_DIR)/include \
	-Iincludes \
	-Ilogs \
	-Ilibft \
	-Ilibft/buff \
	-Ilibft/buff/format \
	-Isrcs/0_utils/1_ft_getopt \
	-Isrcs/0_utils/2_serializer \
	-Isrcs/1_shell \
	-Isrcs/2_scanner \
	-Isrcs/2_scanner/lexer \
	-Isrcs/2_scanner/lexer/context \
	-Isrcs/2_scanner/lexer/input_stack \
	-Isrcs/2_scanner/lexer/operator \
	-Isrcs/2_scanner/lexer/rules \
	-Isrcs/2_scanner/reader \
	-Isrcs/3_builder/1_lr_machine \
	-Isrcs/3_builder/1_lr_machine/1_hooks \
	-Isrcs/3_builder/1_lr_machine/2_symbols \
	-Isrcs/3_builder/1_lr_machine/3_rules \
	-Isrcs/3_builder/1_lr_machine/4_first \
	-Isrcs/3_builder/1_lr_machine/5_rule_state \
	-Isrcs/3_builder/1_lr_machine/6_lr_state \
	-Isrcs/3_builder/1_lr_machine/7_transition \
	-Isrcs/3_builder/1_lr_machine/8_goto \
	-Isrcs/3_builder/1_lr_machine/9_action \
	-Isrcs/3_builder/2_parser \
	-Isrcs/3_builder/2_parser/1_qualifiers \
	-Isrcs/3_builder/2_parser/2_stack \
	-Isrcs/3_builder/2_parser/3_cst \
	-Isrcs/3_builder/3_converter \
	-Isrcs/4_runner \
	-Isrcs/alias \
	-Isrcs/alias/stack \
	-Isrcs/builtins \
	-Isrcs/expander \
	-Isrcs/expander/field \
	-Isrcs/expander/field_splitting \
	-Isrcs/expander/loader \
	-Isrcs/expander/path_name_expansion \
	-Isrcs/expander/quote_removal \
	-Isrcs/expander/quote_removal/context \
	-Isrcs/expander/substitutions \
	-Isrcs/expander/substitutions/tilde \
	-Isrcs/expander/word \
	-Isrcs/heredoc \
	-Isrcs/heredoc/body \
	-Isrcs/heredoc/queue \
	-Isrcs/history \
	-Isrcs/history/file \
	-Isrcs/history/list \
	-Isrcs/history/readline \
	-Isrcs/params/1_options \
	-Isrcs/params/2_specials \
	-Isrcs/params/3_positionals \
	-Isrcs/params/4_variables \
	-Isrcs/params/4_variables/load \
	-Isrcs/params/4_variables/load/1_envp \
	-Isrcs/params/4_variables/load/2_mandatory \
	-Isrcs/params/4_variables/load/2_mandatory/ft_getppid \
	-Isrcs/params/4_variables/load/3_up

OBJ_DIR			:= obj
OBJS			:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L$(READLINE_DIR)/lib -lreadline -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: all

debug: CFLAGS := $(DEBUG_CFLAGS)
debug: re

# DEBUG SECTION (START)
test: all
	@for tester in $(TESTERS); do \
		echo "Running $$tester"; \
		zsh "$$tester"; \
	done
# DEBUG SECTION (END)

clean:
	rm -rf $(OBJ_DIR) $(FIXTURES_DIR) $(LOGS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(TEST_GETOPT_BIN) $(TEST_GETOPT_BIN).dSYM
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus debug test_getopt test clean fclean re

```

./srcs/0_asm_stubs/ft_getpid/freebsd.c
```c
#if defined(__FreeBSD__)
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>

static int	ft_skip_field(const char *string, int index)
{
	while (string[index] && string[index] != ' ' && string[index] != '\t'
		&& string[index] != '\n')
		index++;
	while (string[index] == ' ' || string[index] == '\t')
		index++;
	return (index);
}

static pid_t	ft_parse_pid(const char *string)
{
	int		index;
	pid_t	pid;

	index = 0;
	index = ft_skip_field(string, index);
	if (string[index] < '0' || string[index] > '9')
		return ((pid_t)-1);
	pid = 0;
	while (string[index] >= '0' && string[index] <= '9')
	{
		pid = (pid * 10) + (string[index] - '0');
		index++;
	}
	return (pid);
}

static pid_t	ft_read_pid_file(const char *path)
{
	char	buf[512];
	int		fd;
	ssize_t	nread;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ((pid_t)-1);
	nread = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (nread <= 0)
		return ((pid_t)-1);
	buf[nread] = '\0';
	return (ft_parse_pid(buf));
}

pid_t	ft_getpid(void)
{
	pid_t	pid;

	pid = ft_read_pid_file("/proc/curproc/status");
	if (pid != (pid_t)-1)
		return (pid);
	return (ft_read_pid_file("/proc/self/status"));
}

#endif

```

./srcs/0_asm_stubs/ft_getpid/linux.c
```c
#if defined(__linux__)
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>

static pid_t	ft_parse_pid(const char *string)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (string[i])
	{
		if (string[i] == 'P' && string[i + 1] == 'i'
			&& string[i + 2] == 'd' && string[i + 3] == ':')
		{
			i += 4;
			while (string[i] == ' ' || string[i] == '\t')
				i++;
			pid = 0;
			while (string[i] >= '0' && string[i] <= '9')
				pid = (pid * 10) + (string[i++] - '0');
			return (pid);
		}
		i++;
	}
	return ((pid_t)-1);
}

pid_t	ft_getpid(void)
{
	char	buf[512];
	int		fd;
	ssize_t	nread;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd < 0)
		return ((pid_t)-1);
	nread = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (nread <= 0)
		return ((pid_t)-1);
	buf[nread] = '\0';
	return (ft_parse_pid(buf));
}

#endif

```

./srcs/0_asm_stubs/ft_getpid/mac_arm.c
```c
#if defined(__APPLE__) && (defined(__aarch64__) || defined(__arm64__))
# include <sys/types.h>
# include <sys/syscall.h>

pid_t	ft_getpid(void)
{
	long	ret;

	__asm__ volatile (
		"mov x16, %1\n"
		"svc #0x80\n"
		"mov %0, x0\n"
		: "=r"(ret)
		: "r"((long)SYS_getpid)
		: "x0", "x16", "memory"
	);
	return ((pid_t)ret);
}

#endif

```

./srcs/0_asm_stubs/ft_getpid/mac_x86.c
```c
#if defined(__APPLE__) && defined(__x86_64__)
# include <sys/types.h>
# include <sys/syscall.h>

pid_t	ft_getpid(void)
{
	long	ret;

	__asm__ volatile (
		"syscall\n"
		: "=a"(ret)
		: "a"(0x2000000L | (long)SYS_getpid)
		: "rcx", "r11", "memory"
	);
	return ((pid_t)ret);
}

#endif

```

./srcs/0_asm_stubs/ft_getpid/openbsd.c
```c
#if defined(__OpenBSD__)
# include <unistd.h>

pid_t	ft_getpid(void)
{
	return ((pid_t)-1);
}

#endif

```

./srcs/0_asm_stubs/ft_getppid/freebsd.c
```c
#if defined(__FreeBSD__)
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>

static int	ft_skip_field(const char *s, int i)
{
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
		i++;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (i);
}

static pid_t	ft_parse_ppid(const char *s)
{
	int		i;
	pid_t	ppid;

	i = 0;
	i = ft_skip_field(s, i);
	i = ft_skip_field(s, i);
	if (s[i] < '0' || s[i] > '9')
		return ((pid_t)-1);
	ppid = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		ppid = (ppid * 10) + (s[i] - '0');
		i++;
	}
	return (ppid);
}

static pid_t	ft_read_ppid_file(const char *path)
{
	char	buf[512];
	int		fd;
	ssize_t	nread;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ((pid_t)-1);
	nread = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (nread <= 0)
		return ((pid_t)-1);
	buf[nread] = '\0';
	return (ft_parse_ppid(buf));
}

pid_t	ft_getppid(void)
{
	pid_t	ppid;

	ppid = ft_read_ppid_file("/proc/curproc/status");
	if (ppid != (pid_t)-1)
		return (ppid);
	return (ft_read_ppid_file("/proc/self/status"));
}

#endif

```

./srcs/0_asm_stubs/ft_getppid/linux.c
```c
#if defined(__linux__)
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>

static pid_t	ft_parse_ppid(const char *s)
{
	int		i;
	pid_t	ppid;

	i = 0;
	while (s[i])
	{
		if (s[i] == 'P' && s[i + 1] == 'P' && s[i + 2] == 'i'
			&& s[i + 3] == 'd' && s[i + 4] == ':')
		{
			i += 5;
			while (s[i] == ' ' || s[i] == '\t')
				i++;
			ppid = 0;
			while (s[i] >= '0' && s[i] <= '9')
				ppid = (ppid * 10) + (s[i++] - '0');
			return (ppid);
		}
		i++;
	}
	return ((pid_t)-1);
}

pid_t	ft_getppid(void)
{
	char	buf[512];
	int		fd;
	pid_t	ppid;
	ssize_t	nread;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd < 0)
		return ((pid_t)-1);
	nread = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (nread <= 0)
		return ((pid_t)-1);
	buf[nread] = '\0';
	ppid = ft_parse_ppid(buf);
	return (ppid);
}

#endif

```

./srcs/0_asm_stubs/ft_getppid/mac_arm.c
```c
#if defined(__APPLE__) && (defined(__aarch64__) || defined(__arm64__))
# include <sys/syscall.h>
# include <unistd.h>

/*
GLOBAL FLOW:
1. The compiler prepares SYS_getppid in a register for %1.
2. `mov x16, %1` copies that syscall number into x16.
3. `svc #0x80` enters the kernel.
4. The kernel executes the getppid syscall.
5. On return, the result is in x0.
6. `mov %0, x0` copies that result into the C output operand bound to `ret`.
7. The C function then casts `ret` to int and returns it.

__asm__
=> tells the compiler: "insert this assembly template here".

volatile
=> tells the compiler not to remove this block as if it had no effect,
   and not to treat it like a normal pure computation.

"mov x16, %1"
=> mov  => copies a value from a source register to a destination register.
=> x16  => 64-bit general-purpose register used here to hold the syscall number.
=> %1   => [GCC/Clang] operand placeholder replaced by the compiler with
           the location chosen for input operand #1.

"svc #0x80"
=> svc   => (Supervisor Call) traps into the kernel.
=> #0x80 => immediate constant passed to `svc` for this target.

"mov %0, x0"
=> mov  => copies a value from a source register to a destination register.
=> %0   => [GCC/Clang] operand placeholder replaced by the compiler with
           the location chosen for output operand #0.
=> x0   => 64-bit register holding the syscall return value.

:
=> [GCC/Clang] separates the 4 parts of an extended asm block:
   template : outputs : inputs : clobbers.

"=r"(ret)
=> =    => [GCC/Clang] write-only output operand.
=> r    => [GCC/Clang] this operand must be placed in a register.
=> ret  => C variable bound to this output operand.

"r"((long)SYS_getppid)
=> r                  => [GCC/Clang] this operand must be placed in a register.
=> (long)SYS_getppid  => input value: the syscall number for getppid.

"x0", "x16", "memory"
=> x0     => [GCC/Clang] this asm may modify x0.
=> x16    => [GCC/Clang] this asm may modify x16.
=> memory => [GCC/Clang] this asm may affect memory-observable state, so the
            compiler must not make normal assumptions around memory here.
*/
pid_t	ft_getppid(void)
{
	long	ret;

	__asm__ volatile (
		"mov x16, %1\n"
		"svc #0x80\n"
		"mov %0, x0\n"
		: "=r"(ret)
		: "r"((long)SYS_getppid)
		: "x0", "x16", "memory"
	);
	return ((pid_t)ret);
}

#endif

```

./srcs/0_asm_stubs/ft_getppid/mac_x86.c
```c
#if defined(__APPLE__) && defined(__x86_64__)
# include <sys/syscall.h>
# include <unistd.h>

/*
GLOBAL FLOW:
1. The compiler prepares the Darwin x86_64 syscall number in %1.
2. The input constraint puts that value into rax.
3. `syscall` enters the kernel.
4. The kernel executes the getppid syscall.
5. On return, the result is in rax.
6. The output constraint copies that result into the C output operand bound to
	`ret`.
7. The C function then casts `ret` to int and returns it.

__asm__
=> tells the compiler: "insert this assembly template here".

volatile
=> tells the compiler not to remove this block as if it had no effect,
   and not to treat it like a normal pure computation.

"syscall"
=> syscall => enters the kernel and executes the requested syscall.

:
=> [GCC/Clang] separates the 4 parts of an extended asm block:
   template : outputs : inputs : clobbers.

"=a"(ret)
=> =    => [GCC/Clang] write-only output operand.
=> a    => [GCC/Clang] this operand must be placed in rax/eax.
=> ret  => C variable bound to this output operand.

"a"(0x2000000L | (long)SYS_getppid)
=> a                                 => [GCC/Clang] this operand must be placed 
										in rax/eax.
=> 0x2000000L                        => Darwin x86_64 UNIX/BSD syscall class 
										prefix.
=> (long)SYS_getppid                 => syscall number for getppid.
=> 0x2000000L | (long)SYS_getppid    => full Darwin x86_64 syscall number passed
										to the kernel.

"rcx", "r11", "memory"
=> rcx    => [GCC/Clang] this asm may modify rcx.
=> r11    => [GCC/Clang] this asm may modify r11.
=> memory => [GCC/Clang] this asm may affect memory-observable state, so the
            compiler must not make normal assumptions around memory here.
*/
pid_t	ft_getppid(void)
{
	long	ret;

	__asm__ volatile (
		"syscall\n"
		: "=a"(ret)
		: "a"(0x2000000L | (long)SYS_getppid)
		: "rcx", "r11", "memory"
	);
	return ((pid_t)ret);
}

#endif

```

./srcs/0_asm_stubs/ft_getppid/openbsd.c
```c
#if defined(__OpenBSD__)
# include <unistd.h>

pid_t	ft_getppid(void)
{
	return ((pid_t)-1);
}

#endif

```

./srcs/0_context/expansion/_main.c
```c
#include "context.h"

bool	is_expansion_context(char *str, t_context *context)
{
	if (is_context_param_start(str))
		return (*context = CONTEXT_PARAM, true);
	else if (is_context_arith_start(str))
		return (*context = CONTEXT_ARITH, true);
	else if (is_context_cmd_sub_start(str))
		return (*context = CONTEXT_CMD_SUB, true);
	else if (is_context_backtick_start(str))
		return (*context = CONTEXT_BACKTICK, true);
	return (false);
}

bool	is_in_expansion_whitelist(char c, t_context context)
{
	if (context == CONTEXT_NONE)
		return (is_in_context_none_whitelist(c));
	else if (context == CONTEXT_PARAM)
		return (is_in_context_param_whitelist(c));
	else if (context == CONTEXT_BACKTICK)
		return (is_in_context_backtick_whitelist(c));
	else
		return (false);
}

```

./srcs/0_context/expansion/arith.c
```c
#include "context.h"

bool	is_context_arith_start(char *str)
{
	if (str[1] != '\0' && str[2] != '\0')
		return (str[0] == '$' && str[1] == '(' && str[2] == '(');
	return (false);
}

bool	is_context_arith_ending(char c, void *nesting_depth)
{
	if (nesting_depth == NULL)
		return (false);
	return (c == ')' && *((size_t *)nesting_depth) == 0);
}

```

./srcs/0_context/expansion/backtick.c
```c
#include "context.h"

bool	is_context_backtick_start(char *str)
{
	return (str[0] == '`');
}

bool	is_in_context_backtick_special_whitelist(char c)
{
	return (c == '$' || c == '`' || c == '"' || c == '\\');
}

bool	is_in_context_backtick_whitelist(char c)
{
    return (c == '\\' || c == '$' || c == '`');
}

bool	is_context_backtick_ending(char c, void *_)
{
	return (c == '`');
}

```

./srcs/0_context/expansion/cmd_sub.c
```c
#include "context.h"

bool	is_context_cmd_sub_start(char *str)
{
	if (str[1] != '\0')
		return (str[0] == '$' && str[1] == '(');
	return (false);
}

```

./srcs/0_context/expansion/param.c
```c
#include "context.h"

bool	is_context_param_start(char *str)
{
	if (str[1] != '\0')
		return (str[0] == '$' && str[1] == '{');
	return (false);
}

bool	is_in_context_param_whitelist(char c)
{
	return ((void)c, true);
}

bool	is_context_param_ending(char c, void *_)
{
	return (c == '}');
}


```

./srcs/0_context/none.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   none.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:24:19 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 18:54:52 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

bool	is_in_context_none_whitelist(char c)
{
	return ((void)c, true);
}

bool	is_context_none_ending(char c, void *_)
{
	return (c == '\0');
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

```

./srcs/0_context/quoting/_main.c
```c
#include "context.h"

bool	is_quoting_context(char *str, t_context *context)
{
	if (is_context_squote_start(str))
		return (*context = CONTEXT_SQUOTE, true);
	else if (is_context_dollar_squote_start(str))
		return (*context = CONTEXT_DOLLAR_SQUOTE, true);
	else if (is_context_dquote_start(str))
		return (*context = CONTEXT_DQUOTE, true);
	return (false);
}

bool	is_in_quoting_whitelist(char c, t_context context)
{
	if (context == CONTEXT_NONE)
		return (is_in_context_none_whitelist(c));
	else if (context == CONTEXT_SQUOTE)
		return (is_in_context_squote_whitelist(c));
	else if (context == CONTEXT_DQUOTE)
		return (is_in_context_dquote_whitelist(c));
	else if (context == CONTEXT_DOLLAR_SQUOTE)
		return (is_in_context_dollar_squote_whitelist(c));
	else
		return (false);
}

bool	is_quoting_ending(char c, t_context context)
{
	if (context == CONTEXT_SQUOTE)
		return (is_context_squote_ending(c, NULL));
	else if (context == CONTEXT_DQUOTE)
		return (is_context_dquote_ending(c, NULL));
	else if (context == CONTEXT_DOLLAR_SQUOTE)
		return (is_context_dollar_squote_ending(c, NULL));
	else
		return (false);
}

```

./srcs/0_context/quoting/dollar_squote.c
```c
#include "context.h"

bool	is_context_dollar_squote_start(char *str)
{
	return (str[1] != '\0' && str[0] == '$' && str[1] == '\'');
}

bool	is_in_context_dollar_squote_whitelist(char c)
{
	return ((void)c, true);
}

bool	is_context_dollar_squote_ending(char c, void *_)
{
	return (c == '\'');
}

```

./srcs/0_context/quoting/dquote.c
```c
#include "context.h"

bool	is_context_dquote_start(char *str)
{
	return (str[0] == '\"');
}

bool	is_in_context_dquote_whitelist(char c)
{
	return (c == '$' || c == '`' || c == '\\' || c == '\"');
}

bool	is_context_dquote_ending(char c, void *_)
{
	return (c == '\"');
}

```

./srcs/0_context/quoting/squote.c
```c
#include "context.h"

bool	is_context_squote_start(char *str)
{
	return (str[0] == '\'');
}

bool	is_in_context_squote_whitelist(char c)
{
	return ((void)c, false);
}

bool	is_context_squote_ending(char c, void *_)
{
	return (c == '\'');
}

```

./srcs/0_context/stack/_init.c
```c
#include <stdlib.h>
#include "context.h"

t_error	context_parser_stack_item_init(t_context_parser_stack_item **item, t_context context)
{
	*item = malloc(sizeof(t_context_parser_stack_item));
	if (*item == NULL)
		return (error_sys());
	**item = (t_context_parser_stack_item){0};
	(*item)->context = context;
	return (error(ERR_NO));
}

void	context_stack_init(t_context_stack *stack)
{
	*stack = (t_context_stack){0};
	vector_init(stack, sizeof(t_context_parser_stack_item *), 0);
}

void	context_stack_free(t_context_stack *stack)
{
	vector_free(stack, free);
	*stack = (t_context_stack){0};
}

```

./srcs/0_context/stack/_utils.c
```c
#include "context.h"

t_error	context_stack_push(t_context_stack *stack, t_context_parser_stack_item *item)
{
	if (!vector_push(stack, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	context_stack_bpop(t_context_stack *stack, t_context_parser_stack_item **item)
{
	if (stack->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (!vector_pop(stack, item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	context_stack_fpop(t_context_stack *stack, t_context_parser_stack_item **item)
{
	if (stack->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (!vector_remove(stack, 0, item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	context_stack_get(
	t_context_stack *stack,
	t_context_parser_stack_item **item,
	size_t index)
{
	if (stack->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (index >= stack->len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	*item = ((t_context_parser_stack_item **)stack->data)[index];
	return (error(ERR_NO));
}

t_error	context_stack_dup(t_context_stack *dst, t_context_stack *src)
{
	size_t					i;
	t_error					err;
	t_context_parser_stack_item	*src_item;
	t_context_parser_stack_item	*dst_item;

	i = 0;
	while (i < src->len)
	{
		err = context_stack_get(src, &src_item, i);
		if (err.type)
			return (err);
		err = context_parser_stack_item_init(&dst_item, src_item->context);
		if (err.type)
			return (err);
		*dst_item = *src_item;
		dst_item->end = src_item->end;
		dst_item->start = src_item->start;
		err = context_stack_push(dst, dst_item);
		if (err.type)
			return (err);
		i++;
	}
	return (error(ERR_NO));
}

```

./srcs/0_posix_helpers/posix_getcwd.c
```c
#include "error.h"
#include "libft.h"
#include "posix_helpers.h"
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_INITIAL_CAP	128

static bool	posix_getcwd_grow_size(size_t *size)
{
	if (*size > SIZE_MAX / 2)
	{
		error_print(
			error(ERR_SIZE_MAX_REACHED),
			"posix_getcwd()",
			"unable to grow buffer");
		return (false);
	}
	*size *= 2;
	return (true);
}

t_error	posix_getcwd(char **dst)
{
	char	*buff;
	size_t	size;
	t_error	err;

	*dst = NULL;
	size = BUFF_INITIAL_CAP;
	while (true)
	{
		buff = malloc(size);
		if (!buff)
			return (error_sys());
		if (getcwd(buff, size))
			return (*dst = buff, error(ERR_NO));
		err = error_sys();
		if (err.saved_errno == EACCES)
		{
			(void)str_lcpy(buff, PWD_UNSPECIFIED_VALUE, size);
			return (*dst = buff, error(ERR_NO));
		}
		free(buff);
		if (err.saved_errno != ERANGE)
			return (err);
		if (!posix_getcwd_grow_size(&size))
			return (error(ERR_SIZE_MAX_REACHED));
	}
}

```

./srcs/0_posix_helpers/posix_write.c
```c
#include "error.h"
#include <errno.h>
#include <limits.h>
#include <unistd.h>

t_error	posix_write(int fd, const char *buff, size_t len)
{
	size_t	remaining;
	ssize_t	ret;

	remaining = 0;
	while (len > 0)
	{
		if (len > SSIZE_MAX)
		{
			remaining = len - SSIZE_MAX;
			len -= remaining;
		}
		ret = write(fd, buff, len);
		if (ret < 0 && errno == EINTR)
			continue ;
		else if (ret < 0 || (ret == 0 && len != 0))
			return (error_sys());
		else if ((size_t)ret == len && remaining == 0)
			return (error(ERR_NO));
		buff += ret;
		len -= (size_t)ret;
		len += remaining;
		remaining = 0;
	}
	return (error(ERR_NO));
}

```

./srcs/0_token/_init.c
```c
#include "token.h"

void	token_init(t_token *token)
{
	*token = (t_token){0};
	buff_init(&token->value, 0, NULL, 0);
	context_stack_init(&token->contexts);
}

void	token_free(t_token *token)
{
	context_stack_free(&token->contexts);
	buff_free(&token->value);
	*token = (t_token){0};
}

```

./srcs/0_token/_utils.c
```c
#include "token.h"

t_error	token_dup(t_token *dst, t_token *src)
{
	dst->type = src->type;
	if (!buff_dup_n(&dst->value, &src->value, src->value.len))
		return (error_sys());
	return (context_stack_dup(&dst->contexts, &src->contexts));
}

```

./srcs/0_utils/1_ft_getopt/0_utils.c
```c
#include "ft_getopt_priv.h"

#define GETOPT_FMESSAGE_CAP	32

t_error	getopt_add_option(t_getopt_state *state, t_getopt_option *src)
{
	if (!vector_push(&state->out->options, src))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	getopt_err(
	const t_getopt_state *state,
	char flag,
	const char *arg, t_error_type err_type)
{
	char	fmessage[GETOPT_FMESSAGE_CAP];

	fmessage[0] = flag;
	if (arg)
	{
		fmessage[1] = ':';
		fmessage[2] = ' ';
		str_lcpy(fmessage + 3, arg, GETOPT_FMESSAGE_CAP - 3);
		fmessage[GETOPT_FMESSAGE_CAP - 6] = '[';
		fmessage[GETOPT_FMESSAGE_CAP - 5] = '.';
		fmessage[GETOPT_FMESSAGE_CAP - 4] = '.';
		fmessage[GETOPT_FMESSAGE_CAP - 3] = '.';
		fmessage[GETOPT_FMESSAGE_CAP - 2] = ']';
		fmessage[GETOPT_FMESSAGE_CAP - 1] = '\0';
	}
	else
		fmessage[1] = '\0';
	return (error_print(error(err_type), state->in->builtin_name, fmessage, NULL, NULL));
}

```

./srcs/0_utils/1_ft_getopt/1_process_arg.c
```c
#include "ft_getopt_priv.h"

// @ret ERR_OPT_INVALID / ERR_LIBC
static t_error	getopt_process_flags_without_arg(t_getopt_state *state)
{
	t_getopt_option option;
	const char		*valid_flags;
	size_t			i;

	option.sign = state->argv[state->arg_i][0];
	option.flag = state->argv[state->arg_i][state->char_i];
	option.argument = NULL;
	if (option.sign == '-')
		valid_flags = state->in->valid_minus_flags;
	else
		valid_flags = state->in->valid_plus_flags;
	if (!valid_flags)
		return (error(ERR_OPT_INVALID));
	i = 0;
	while (valid_flags[i])
	{
		if (valid_flags[i++] == option.flag)
		{
			if (!vector_push(&state->out->options, &option))
				return (error_sys());
			state->char_i++;
			return (error(ERR_NO));
		}
	}
	return (error(ERR_OPT_INVALID));
}

// @ret ERR_OPT_INVALID_ARG / ERR_LIBC
static t_error	getopt_process_flag_optional_arg(
	t_getopt_state *state,
	t_getopt_option *option,
	t_getopt_flag_with_arg *flag_opt)
{
	const char	*arg;
	size_t		i;
	const char	*target_arg;

	arg = state->argv[state->arg_i] + state->char_i;
	state->arg_i++;
	state->char_i = 0;
	if (arg[0] == '\0')
		return (getopt_add_option(state, option));
	i = 0;
	while (flag_opt->arguments_valids[i])
	{
		target_arg = flag_opt->arguments_valids[i];
		if (str_cmp(arg, target_arg) == 0)
		{
			option->argument = target_arg;
			return (getopt_add_option(state, option));
		}
		i++;
	}
	return (getopt_err(state, option->flag, arg, ERR_OPT_INVALID_ARG));
}

// @ret ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG / ERR_LIBC
static t_error	getopt_process_flag_mandatory_arg(
	t_getopt_state *state,
	t_getopt_option *option,
	t_getopt_flag_with_arg *flag_opt)
{
	const char	*arg;
	size_t		i;

	if (state->argv[state->arg_i][state->char_i] != '\0')
		arg = state->argv[state->arg_i] + state->char_i;
	else
	{
		state->arg_i++;
		if (state->arg_i >= state->argc)
			return (getopt_err(state, option->flag, NULL, ERR_OPT_MISSING_ARG));
		arg = state->argv[state->arg_i];
	}
	state->arg_i++;
	state->char_i = 0;
	i = 0;
	while (flag_opt->arguments_valids[i])
	{
		option->argument = flag_opt->arguments_valids[i];
		if (str_cmp(arg, option->argument) == 0)
			return (getopt_add_option(state, option));
		i++;
	}
	return (getopt_err(state, option->flag, arg, ERR_OPT_INVALID_ARG));
}

// @ret ERR_OPT_INVALID / ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG / ERR_LIBC
static t_error	getopt_process_flags_with_arg(t_getopt_state *state)
{
	t_getopt_option			option;
	t_getopt_flag_with_arg	*curr;
	size_t					i;

	option.sign = state->argv[state->arg_i][0];
	option.flag = state->argv[state->arg_i][state->char_i];
	option.argument = NULL;
	i = 0;
	while (i < state->in->options_with_arg_count)
	{
		curr = &state->in->options_with_arg[i++];
		if (option.sign != curr->sign)
			continue ;
		if (curr->flag == option.flag)
		{
			state->char_i++;
			if (curr->arguments_are_optional)
				return (getopt_process_flag_optional_arg(state, &option, curr));
			return (getopt_process_flag_mandatory_arg(state, &option, curr));
		}
	}
	return (getopt_err(state, option.flag, NULL, ERR_OPT_INVALID));
}

t_error	getopt_process_arg(t_getopt_state *state)
{
	t_error	err;

	while (state->argv[state->arg_i][state->char_i] != '\0')
	{
		err = getopt_process_flags_without_arg(state);
		if (err.type == ERR_LIBC)
			return (err);
		if (err.type == ERR_OPT_INVALID)
			return (getopt_process_flags_with_arg(state));
	}
	state->arg_i++;
	state->char_i = 0;
	return (error(ERR_NO));
}

```

./srcs/0_utils/1_ft_getopt/2_main.c
```c
#include "ft_getopt_priv.h"

static bool	getopt_is_delimiter(t_getopt_state *state)
{
	const char	*arg;

	arg = state->argv[state->arg_i];
	if (str_cmp(arg, "-") == 0)
	{
		if (state->in->single_delimiter == true)
			state->arg_i++;
		return (true);
	}
	if (str_cmp(arg, "--") == 0)
	{
		state->arg_i++;
		return (true);
	}
	if ((arg[0] != '-' && arg[0] != '+') || str_cmp(arg, "+") == 0)
		return (true);
	return (false);
}

// @ret ERR_OPT_INVALID / ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG / ERR_LIBC
static t_error	getopt_process(t_getopt_state *state)
{
	t_error		err;

	while (state->arg_i < state->argc)
	{
		if (getopt_is_delimiter(state))
			break ;
		state->char_i = 1;
		err = getopt_process_arg(state);
		if (err.type != ERR_NO)
			return (err);
	}
	state->out->first_operand_index = (size_t)state->arg_i;
	return (error(ERR_NO));
}

static t_error	getopt_catch_ub(t_getopt_out *out)
{
	size_t			i;
	t_getopt_option	*a;
	t_getopt_option	*b;
	size_t			j;

	i = 0;
	while (i < out->options.len)
	{
		a = &((t_getopt_option *)out->options.data)[i++];
		if (a->argument)
			continue ;
		j = i;
		while (j < out->options.len)
		{
			b = &((t_getopt_option *)out->options.data)[j++];
			if (b->argument)
				continue ;
			if (a->sign == b->sign && a->flag == b->flag)
				return (vector_free(&out->options, NULL),
					undefined_behaviour("POSIX (XBD 12.1-3): "
					"If an option that does not have option-arguments is "
					"repeated, the results are undefined"));
		}
	}
	return (error(ERR_NO));
}

t_error	ft_getopt(int argc, char **argv, t_getopt_in *in, t_getopt_out *out)
{
	t_getopt_state	state;
	t_error			err;

	state.argc = argc;
	state.argv = argv;
	state.arg_i = 1;
	state.char_i = 0;
	state.in = in;
	state.out = out;
	(void)vector_init(&out->options, sizeof(t_getopt_option), 0);
	out->first_operand_index = 1;
	err = getopt_process(&state);
	if (err.type != ERR_NO)
	{
		vector_free(&out->options, NULL);
		return (err);
	}
	if (in->ub_on_repeated_flags)
		return (getopt_catch_ub(out));
	return (error(ERR_NO));
}

```

./srcs/0_utils/1_ft_getopt/3_dump.c
```c
#include "ft_getopt.h"
# include "debug.h"
# include <stdio.h>

static void	ft_getopt_dump_flag_with_arg(t_getopt_flag_with_arg *flag)
{
	size_t	i;

	fprintf(stderr, "[%c%c", flag->sign, flag->flag);
	if (flag->arguments_are_optional)
		fprintf(stderr, "[");
	else
		fprintf(stderr, " ");
	i = 0;
	while (flag->arguments_valids[i])
	{
		fprintf(stderr, "%s", flag->arguments_valids[i]);
		if (flag->arguments_valids[i + 1])
			fprintf(stderr, " ");
		i++;
	}
	if (flag->arguments_are_optional)
		fprintf(stderr, "]");
	fprintf(stderr, "]\n");
}

void	ft_getopt_dump_in(t_getopt_in *in)
{
	size_t	i;

	fprintf(stderr, "\nGETOPT DUMP IN\n");
	fprintf(stderr, "builtin_name=%s\n", in->builtin_name);
	fprintf(stderr, "valid_minus_flags=%s\n", in->valid_minus_flags);
	fprintf(stderr, "valid_plus_flags=%s\n", in->valid_plus_flags);
	i = 0;
	while (i < in->options_with_arg_count)
	{
		ft_getopt_dump_flag_with_arg(&in->options_with_arg[i]);
		i++;
	}
	fprintf(stderr, "options_with_arg_count=%zu\n", in->options_with_arg_count);
	fprintf(stderr, "single_delimiter=%s\n", bool_to_string(in->single_delimiter));
	fprintf(stderr, "ub_on_repeated_flags=%s\n", bool_to_string(in->ub_on_repeated_flags));
}

void	ft_getopt_dump_out(t_getopt_out *out)
{
	size_t			i;
	t_getopt_option	*option;

	fprintf(stderr, "\nGETOPT DUMP OUT\n");
	i = 0;
	while (i < out->options.len)
	{
		option = &((t_getopt_option *)out->options.data)[i];
		if (option->argument)
			fprintf(stderr, "%c%c %s\n", option->sign, option->flag, option->argument);
		else
			fprintf(stderr, "%c%c\n", option->sign, option->flag);
		i++;
	}
	fprintf(stderr, "first_operand_index=%zu\n", out->first_operand_index);
}

void	ft_getopt_dump_all(t_getopt_in *in, t_getopt_out *out)
{
	ft_getopt_dump_in(in);
	ft_getopt_dump_out(out);
}

```

./srcs/0_utils/1_ft_getopt/ft_getopt_priv.h
```c
#ifndef FT_GETOPT_PRIV_H
# define FT_GETOPT_PRIV_H

# include "ft_getopt.h"

typedef struct s_getopt_state
{
	int				argc;
	char			**argv;
	int				arg_i;
	size_t			char_i;
	t_getopt_in		*in;
	t_getopt_out	*out;
}	t_getopt_state;

/* ************************************************************************* */
/*                                   UTILS                                   */
/* ************************************************************************* */

// @ret ERR_LIBC
t_error	getopt_add_option(t_getopt_state *state, t_getopt_option *src);

// @ret error(err_type)
t_error	getopt_err(
	const t_getopt_state *state,
	char flag,
	const char *arg, t_error_type err_type);

/* ************************************************************************* */
/*                                 OPTIONS                                   */
/* ************************************************************************* */

// @ret ERR_OPT_INVALID / ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG / ERR_LIBC
t_error	getopt_process_arg(t_getopt_state *state);

#endif

```

./srcs/0_utils/2_serializer/1_serialize.c
```c
#include "libft.h"
#include "error.h"
#include "serialize_priv.h"
#include <stddef.h>
#include <stdlib.h>

static inline void copy_and_add_escape(
	const char *src,
	char **dst,
	size_t dst_cap)
{
	size_t	i;
	size_t	j;

	(*dst)[0] = '\'';
	i = 0;
	j = 1;
	while (src[i])
	{
		if (src[i] == '\'')
		{
			str_lcpy(*dst + j, ESCAPED_QUOTE, dst_cap - j);
			j += ESCAPED_QUOTE_ADDITIONAL_LEN;
		}
		else
			(*dst)[j] = src[i];
		i++;
		j++;
	}
	(*dst)[dst_cap - 2] = '\'';
	(*dst)[dst_cap - 1] = '\0';
}

t_error serialize(const char *src, char **dst)
{
	size_t	src_len;
	size_t	dst_cap;
	size_t	escape_count;

	escape_count = 0;
	src_len = 0;
	while (src[src_len])
		if (src[src_len++] == '\'')
			escape_count++;
	dst_cap = src_len + 2 + (escape_count * ESCAPED_QUOTE_ADDITIONAL_LEN) + 1;
	*dst = malloc(dst_cap);
	if (!*dst)
		return (error_sys());
	copy_and_add_escape(src, dst, dst_cap);
	return (error(ERR_NO));
}

```

./srcs/0_utils/2_serializer/2_deserialize.c
```c
#include "libft.h"
#include "error.h"
#include "serialize_priv.h"
#include <stddef.h>
#include <stdlib.h>

// @ret ERR_INVALID_FORMAT
static inline t_error copy_and_remove_escape(
	const char *src,
	char **dst,
	size_t src_len)
{
	size_t	i;
	size_t	j;

	i = 1;
	j = 0;
	while (i < src_len - 1)
	{
		(*dst)[j] = src[i];
		if (src[i] == '\'')
		{
			if (str_ncmp(src + i, ESCAPED_QUOTE, ESCAPED_QUOTE_LEN) != 0)
			{
				free(*dst);
				*dst = NULL;
				return (error_print(error(ERR_INVALID_FORMAT),
					"deserializer", src,
					NULL, NULL));
			}
			i += ESCAPED_QUOTE_ADDITIONAL_LEN;
		}
		i++;
		j++;
	}
	(*dst)[j] = '\0';
	return (error(ERR_NO));
}

t_error deserialize(const char *src, char **dst)
{
	size_t	src_len;

	src_len = str_len(src);
	if (src_len < 2 || src[0] != '\'' || src[src_len - 1] != '\'')
		return (error(ERR_INVALID_FORMAT));
	*dst = malloc(src_len + 1);
	if (!*dst)
		return (error_sys());
	return (copy_and_remove_escape(src, dst, src_len));
}

```

./srcs/0_utils/2_serializer/3_deserialize_all.c
```c
#include "libft.h"
#include "error.h"
#include "utils.h"
#include "serialize_priv.h"
#include <stddef.h>
#include <stdlib.h>

static inline bool	is_entry_start(const char *src, size_t i)
{
	return (src[i] == '\'' && (i == 0 || src[i - 1] == '\n'));
}

static inline bool	find_entry_end(const char *src, size_t start, size_t *end)
{
	size_t	i;

	i = start + 1;
	while (src[i])
	{
		if (src[i] != '\'')
			i++;
		else if (str_ncmp(src + i, ESCAPED_QUOTE, ESCAPED_QUOTE_LEN) == 0)
			i += ESCAPED_QUOTE_LEN;
		else if (src[i + 1] == '\n' || src[i + 1] == '\0')
			return (*end = i, true);
		else
			return (false);
	}
	return (false);
}

static inline bool	find_next_entry(const char *src, size_t *start, size_t *end)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		if (is_entry_start(src, i))
		{
			if (find_entry_end(src, i, end))
				return (*start = i, true);
			while (src[i] && src[i] != '\n')
				i++;
		}
		else
			i++;
	}
	return (false);
}

static inline t_error	parse_entry(const char *src, size_t len, t_vector *dst)
{
	t_error	err;
	char	*entry;
	char	*out;

	entry = str_ndup(src, len);
	if (!entry)
		return (error_sys());
	err = deserialize(entry, &out);
	free(entry);
	if (err.type == ERR_INVALID_FORMAT)
		return (error(ERR_NO));
	if (err.type)
		return (err);
	if (!vector_push(dst, &out))
		return (free(out), error_sys());
	return (error(ERR_NO));
}

t_error	deserialize_all(const char *src, t_vector *dst)
{
	size_t		i;
	size_t		start;
	size_t		end;
	t_error		err;

	if (!vector_init(dst, sizeof(char *), VECTOR_INIT_CAP))
		return (error_sys());
	i = 0;
	while (src[i])
	{
		if (!find_next_entry(src + i, &start, &end))
			break ;
		err = parse_entry(src + i + start, end - start + 1, dst);
		if (err.type)
			return (vector_free(dst, free), err);
		i += end + 1;
		while (src[i] == '\n')
			i++;
	}
	return (error(ERR_NO));
}

```

./srcs/0_utils/2_serializer/serialize_priv.h
```c
#ifndef SERIALIZE_PRIV_H
# define SERIALIZE_PRIV_H

#define ESCAPED_QUOTE 					"'\\''"
#define ESCAPED_QUOTE_LEN				4
#define ESCAPED_QUOTE_ADDITIONAL_LEN	3

#endif

```

./srcs/0_utils/assignment.c
```c
#include "libft.h"
#include "error.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

t_error assignment_split(const char *src, char **dst_name, char **dst_value)
{
	size_t	len;
	bool	has_equal;
	t_error	err;

	*dst_name = NULL;
	*dst_value = NULL;
	len = 0;
	while (src[len] && src[len] != '=')
		len++;
	if (len == 0)
		return (error(ERR_ASSIGNMENT_MISSING_NAME));
	has_equal = src[len] == '=';
	*dst_name = malloc(len + 1);
	if (!*dst_name)
		return (error_sys());
	str_lcpy(*dst_name, src, len + 1);
	if (!has_equal)
		return (error(ERR_NO));
	*dst_value = str_dup(src + len + 1);
	if (!*dst_value)
	{
		err = error_sys();
		return (free(*dst_name), *dst_name = NULL, err);
	}
	return (error(ERR_NO));
}

```

./srcs/0_utils/ft_getpwnam/_main.c
```c
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include "libft.h"

static void	ft_pw_fill(struct passwd *pw, char **field)
{
	pw->pw_name = field[0];
	pw->pw_passwd = field[1];
	pw->pw_uid = (uid_t)ft_atoi(field[2]);
	pw->pw_gid = (gid_t)ft_atoi(field[3]);
	pw->pw_gecos = field[4];
	pw->pw_dir = field[5];
	pw->pw_shell = field[6];
}

static int	ft_pw_split(char *line, struct passwd *pw, const char *name)
{
	int		i;
	int		f;
	char	*field[7];

	f = 0;
	i = 0;
	field[f++] = line;
	while (line[i] && f < 7)
	{
		if (line[i] == ':')
		{
			line[i] = '\0';
			field[f++] = line + i + 1;
		}
		i++;
	}
	if (f < 7 || str_cmp(field[0], name) != 0)
		return (0);
	return (ft_pw_fill(pw, field), 1);
}

static ssize_t	ft_pw_slurp(char *buf, size_t cap)
{
	int		fd;
	ssize_t	n;
	ssize_t	total;

	fd = open("/etc/passwd", O_RDONLY);
	if (fd < 0)
		return (-1);
	total = 0;
	n = read(fd, buf + total, cap - 1 - (size_t)total);
	while (n > 0)
	{
		total += n;
		n = read(fd, buf + total, cap - 1 - (size_t)total);
	}
	close(fd);
	if (n < 0)
		return (-1);
	return (buf[total] = '\0', total);
}

struct passwd	*ft_getpwnam(const char *name)
{
	static struct passwd	pw;
	static char				buf[65536];
	char					*line;
	char					*next;

	if (name == NULL || ft_pw_slurp(buf, sizeof(buf)) < 0)
		return (NULL);
	line = buf;
	while (*line)
	{
		next = line;
		while (*next && *next != '\n')
			next++;
		if (*next == '\n')
			*next++ = '\0';
		if (ft_pw_split(line, &pw, name))
			return (&pw);
		line = next;
	}
	return (NULL);
}

```

./srcs/0_utils/name.c
```c
#include "libft.h"

bool	name_is_valid(const char *name)
{
	size_t	i;

	if (!name || !name[0])
		return (false);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (false);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

```

./srcs/0_utils/time.c
```c
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

// TODO: stub ASM
time_t	get_now_unix_seconds(void)
{
	struct stat	stat;
	int			fds[2];

	if (pipe(fds) == -1)
		return (-1);
	if (fstat(fds[0], &stat) == -1)
		return (close(fds[0]), close(fds[1]), -1);
	return (close(fds[0]), close(fds[1]), stat.st_mtime);
}

```

./srcs/1_shell/1_life_cycle.c
```c
#include "shell_priv.h"
#include "options.h"
#include <stdlib.h>

void	shell_init(t_shell *shell)
{
	params_init(&shell->params);
	scanner_init(&shell->scanner);
	alias_init(&shell->alias);
	heredoc_init(&shell->heredoc);
	history_init(&shell->history);
	builder_init(&shell->builder);
	runner_init(&shell->runner);
}

void	shell_free(void)
{
	t_shell	*shell;

	shell = shell_get();
	if (!shell)
		return ;
	params_free(&shell->params);
	scanner_free(&shell->scanner);
	alias_free(&shell->alias);
	heredoc_free(&shell->heredoc);
	history_free(&shell->history);
	builder_free(&shell->builder);
	runner_free(&shell->runner);
	free(shell);
	shell_set(NULL);
}

void	shell_exit_on_veof(void)
{
	if (!option_is_active(OPT_INTERACTIVE))
		return ;
	if (option_is_active(OPT_IGNOREEOF))
		return ;
	exit(EXIT_SUCCESS);	// TODO: trouver une autre solution car on risque de leak
}

```

./srcs/1_shell/2_helpers.c
```c
#include "shell.h"

#define DEFAULT_NAME	"minishell"

static t_shell	*shell_singleton(t_shell *addr)
{
	static t_shell *shell = NULL;

	if (addr)
		shell = addr;
	return (shell);
}

void	shell_set(t_shell *addr)
{
	(void)shell_singleton(addr);
}

t_shell	*shell_get(void)
{
	return (shell_singleton(NULL));
}

const char	*shell_get_name(void)
{
	t_shell	*shell;

	shell = shell_get();
	if (!shell)
		return (DEFAULT_NAME);
	return (shell->params.name);
}

```

./srcs/1_shell/3_get.c
```c
#include "shell.h"

t_alias	*shell_get_alias(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->alias);
}

t_builder	*shell_get_builder(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->builder);
}

t_heredoc	*shell_get_heredoc(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->heredoc);
}

t_history	*shell_get_history(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->history);
}

t_params	*shell_get_params(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->params);
}

t_runner	*shell_get_runner(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->runner);
}

t_scanner	*shell_get_scanner(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->scanner);
}

```

./srcs/1_shell/4_load.c
```c
#include "shell.h"
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>
# include "logs.h"	// DEBUG

// ⚠️ TODO: move to runner/executor (because it will use it after each command execution)
// ERR_NO / ERR_LIBC
t_error	shell_set_stdin_to_blocking(void)
{
	int			enabled;
	struct stat	stat_buff;
	bool		is_a_terminal;
	bool		is_fifo;
	
	is_a_terminal = isatty(STDIN_FILENO);
	if (!is_a_terminal)
	{
		if (fstat(STDIN_FILENO, &stat_buff) != 0)
			return (error_print(error_sys(), "unable to check if stdin is FIFO", NULL, NULL));
		is_fifo = S_ISFIFO(stat_buff.st_mode);
		if (!is_fifo)
		{
			print_pass("stdin is not a fifo: did not set it to blocking mode\n");
			return (error(ERR_NO));
		}
	}
	enabled = 0;
	if (ioctl(STDIN_FILENO, FIONBIO, &enabled) == -1)
		return (error_print(error_sys(), "Unable to set stdin to blocking mode", NULL, NULL));
	print_pass("stdin has been set to blocking mode\n");
	return (error(ERR_NO));
}

static t_error	shell_load_scanner(t_shell *shell)
{
	t_scanner_mode	mode;

	if (option_is_active(OPT_STDIN_INPUT))
		mode = SCAN_STDIN;
	else if (option_is_active(OPT_CMD_STRING))
		mode = SCAN_STRING;
	else
		mode = SCAN_FILE;
	return (scanner_load(&shell->scanner, mode, shell->params.specials.source));
}

t_error	shell_load(t_shell *shell, int argc, char **argv, char **envp)
{
	t_error	err;

	print_title("shell_load()");
	err = params_load(&shell->params, argc, argv, envp);
	if (err.type == ERR_NO)
		err = history_load(&shell->history);
	if (err.type == ERR_NO)
		err = shell_load_scanner(shell);
	heredoc_load(&shell->heredoc, option_is_active(OPT_STDIN_INPUT));
	if (err.type == ERR_NO)
		err = builder_load(&shell->builder);
	if (err.type == ERR_NO)
		print_warn("Runner not implemented yet              => skipping loading\n");	// TODO: runner_load(&shell->runner);
	if (err.type == ERR_NO)
		err = shell_set_stdin_to_blocking();
	if (err.type != ERR_NO)
		return (err);
	print_result("shell_load()");
	return (error(ERR_NO));
}

```

./srcs/1_shell/5_exec_env.c
```c
#include "error.h"
#include "params.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG

t_error	shell_exec_env(void)
{
	t_error	err;
	char	*raw_env;

	print_title("shell_exec_env()");
	if (!option_is_active(OPT_INTERACTIVE))
	{
		print_warn("non-interactive mode => skipping ENV execution\n");
		print_result("shell_exec_env()");
		return (error(ERR_NO));
	}
	err = params_get("ENV", &raw_env);
	if (err.type != ERR_NO && err.type != ERR_VAR_NOT_FOUND)
		return (error_print(error_sys(), "internal error", NULL, NULL));
	if (!raw_env)
	{
		print_warn("no ENV file to execute => skipping.\n");
		print_result("shell_exec_env()");
		return (error(ERR_NO));
	}
	if (option_is_active(OPT_STDIN_INPUT))
	{
		print_warn("Expander and Runner not implemented yet => skipping ENV execution\n");
		// TODO: expand ENV
		// TODO: exec ENV
	}
	else
		print_warn("OPT_STDIN_INPUT is not active => skipping ENV execution\n");
	print_result("shell_exec_env()");
	return (error(ERR_NO));
}

```

./srcs/1_shell/6_run.c
```c
#include "shell_priv.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG

t_error	shell_run(int argc, char **argv, char **envp)
{
	static const char	message[] = ": unable to malloc shell data struct: ";
	t_shell				*shell;
	t_error				err;
	t_error				history_err;

	print_start(99, "shell_run()");
	shell = malloc(sizeof(*shell));
	if (!shell)
		return (error_print(error_sys(), message, NULL, NULL));
	print_title("shell_init()");
	shell_init(shell);
	print_result("shell_init()");
	shell_set(shell);
	err = shell_load(shell, argc, argv, envp);
	if (err.type != ERR_NO)
		return(err);
	err = shell_exec_env();
	if (err.type != ERR_NO)
		return (err);
	err = runner_run(&shell->runner);
	history_err = history_save();
	if (history_err.type)
		error_print(history_err, "history", NULL, NULL);
	return (err);
}

```

./srcs/1_shell/shell_priv.h
```c
#ifndef SHELL_PRIV_H
# define SHELL_PRIV_H

# include "shell.h"

void	shell_init(t_shell *shell);
t_error	shell_load(t_shell *shell, int argc, char **argv, char **envp);
t_error	shell_exec_env(void);
void	shell_set(t_shell *addr);

#endif

```

./srcs/2_scanner/_init.c
```c
#include "scanner.h"

t_error	scanner_init(t_scanner *state)
{
	*state = (t_scanner){0};
	lexer_init(&state->lexer);
	return (error(ERR_NO));
}

void	scanner_free(t_scanner *state)
{
	lexer_free(&state->lexer);
	*state = (t_scanner){0};
}

t_error	scanner_load(t_scanner *state, t_scanner_mode mode, const char *source)
{
	state->mode = mode;
	lexer_load(&state->lexer, mode == SCAN_STDIN);
	if (mode == SCAN_STRING)
		return (state->source = source, state->err);
	else if (mode == SCAN_FILE)
		return (state->source = source, state->err);
	return (state->err);
}

t_error	scanner_reset(t_scanner *state)
{

	//IMPLEMENT: reset the scanner state
	return (state->err);
}

```

./srcs/2_scanner/_utils.c
```c
#include <stdlib.h>
#include "alias.h"
#include "reader_.h"
#include "scanner_.h"

static t_error	scanner_dup_command_input(
	t_scanner *state,
	t_input_parser_stack_item *item)
{
	char	*command;

	command = str_dup(state->source);
	if (command == NULL)
		state->err = error_sys();
	item->str = str_join(command, "\n");
	if (item->str == NULL)
		state->err = error_sys();
	return (free(command), state->err);
}

t_error	scanner_read_input(t_scanner *state) 
{
	t_input_parser_stack_item	*item;

	state->err = input_parser_stack_item_init(&item);
	if (state->err.type)
		return (state->err);
	if (state->mode == SCAN_FILE)
		state->err = reader_file_input(&item->str, state->source);
	else if (state->mode == SCAN_STRING)
	{
		if (scanner_dup_command_input(state, item).type)
			return (input_parser_stack_item_free(&item), state->err);
	}
	else if (state->mode == SCAN_STDIN)
		state->err = reader_new_input(&item->str); 
	if (state->err.type || item->str == NULL)
		return (input_parser_stack_item_free(&item), state->err);
	return (state->err = input_stack_push(&state->lexer.input_stack, item));
}

t_error	scanner_alias_expand(t_scanner *state, t_token *token)
{
	t_input_parser_stack_item	*item;

	state->err = input_parser_stack_item_init(&item);
	if (state->err.type)
		return (state->err);
	state->err = alias_expand_token(&item->str, &token->value);
	if (state->err.type || item->str == NULL)
		return (input_parser_stack_item_free(&item), state->err);
	input_stack_push(&state->lexer.input_stack, item);
	token_free(token);
	if (lexer_next_token(&state->lexer, token).type)
		return (state->err = state->lexer.err);
	return (state->err);
}

```

./srcs/2_scanner/API.c
```c
#include "shell.h"
#include "heredoc.h"
#include "scanner_.h"

t_error	scanner_get_next_token(t_token *token)
{
	t_scanner	*state;

	state = shell_get_scanner();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (state->lexer.input_stack.len == 0 && scanner_read_input(state).type)
		return (state->err);
	if (lexer_next_token(&state->lexer, token).type)
		return (state->err = state->lexer.err, state->err);
	if (token->type == TOKEN_TOKEN)
		return (scanner_alias_expand(state, token));
	return (state->err);
}

t_error	scanner_report_io_here(char **path, char *delim, t_heredoc_mode mode)
{
	t_scanner	*state;

	state = shell_get_scanner();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (heredoc_add_to_queue(path, delim, mode).type)
		return (state->err = state->heredoc.err, state->err);
	return (state->err);
}

#include <stdio.h>
t_error	scanner_heredoc_read(void)
{
	t_input_parser_stack_item	*item;
	t_scanner					*state;

	printf("=====> Enter heredoc read\n");
	state = shell_get_scanner();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	printf("=====> Scanner state obtained\n");
	printf("=====> Lexer input: %s\n", state->lexer.input ? state->lexer.input->str : "NULL");
	if (state->lexer.input != NULL)
	{
		item = state->lexer.input;
		state->err = heredoc_store_all(item->str, &item->i);
		if (state->err.type)
			return (state->err = state->heredoc.err);
	}
	return (state->err);
}

```

./srcs/2_scanner/lexer/_init.c
```c
#include "lexer_.h"

void	lexer_init(t_lexer *state)
{
	*state = (t_lexer){0};
	input_stack_init(&state->input_stack);
}

void	lexer_free(t_lexer *state)
{
	input_stack_free(&state->input_stack);
	*state = (t_lexer){0};
}

void	lexer_load(t_lexer *state, bool is_stdin)
{
	state->is_stdin = is_stdin;
}

```

./srcs/2_scanner/lexer/_main.c
```c
#include "alias.h"
#include "lexer_.h"

t_error	lexer_next_token(t_lexer *state, t_token *token)
{
	t_context	context;

	state->emited_token = false;
	state->err = input_stack_get_last(&state->input_stack, &state->input);
	if (state->err.type)
		return (state->err);
	token_init(token);
	state->token = token;
	while (!state->emited_token)
	{
		if (lexer_rules(state, &context).type)
			return (state->err);
	}
	if (token->type == TOKEN_EOF && state->input_stack.len > 0)
	{
		state->err = input_stack_pop(&state->input_stack);
		if (state->err.type)
			return (state->err);
		state->err = alias_on_expansion_end();
		if (state->err.type)
			return (state->err);
	}
	return (state->input = NULL, state->err);
}

```

./srcs/2_scanner/lexer/_utils.c
```c
#include <stdlib.h>
#include "lexer_.h"

void	lexer_advance(t_lexer *state, size_t offset)
{
	state->input->i += offset;
}

t_error	lexer_consume(t_lexer *state, t_token_type type, size_t iter)
{
	size_t	i;
	char	current_char;

	i = 0;
	while (i < iter)
	{
		current_char = state->input->str[state->input->i];
		if (!buff_append(&state->token->value, &current_char, 1))
			return (state->err = error_sys());
		state->token->type = type;
		lexer_advance(state, 1);
		i++;
	}
	return (state->err);
}

t_lexer_backup	lexer_backup(t_lexer *state)
{
	t_lexer_backup res;

    res.i = state->input->i;
    res.token_type = state->token->type;
    res.context_len = state->input->context.len;
    res.token_value_len = state->token->value.len;
    res.token_contexts_len = state->token->contexts.len;
	return (res);
}

t_error	lexer_restore(t_lexer *state, t_lexer_backup backup)
{
	t_context_parser_stack_item	*item;

	while (state->input->context.len > backup.context_len)
    {
		if (context_stack_bpop(&state->input->context, NULL).type)
			return (state->err);
	}
	while (state->token->contexts.len > backup.token_contexts_len)
	{
		if (context_stack_bpop(&state->token->contexts, &item).type)
			return (state->err);
		free(item);
	}
    state->input->i = backup.i;
    state->token->type = backup.token_type;
    state->token->value.len = backup.token_value_len;
	return (state->err);
}

void	lexer_delimit_token(t_lexer *state)
{
	state->emited_token = true;
}

```

./srcs/2_scanner/lexer/context/_main.c
```c
#include "lexer_context_.h"

t_error	lexer_context(t_lexer *state, t_context context)
{
	if (context == CONTEXT_SQUOTE)
		return (lexer_context_squote(state));
	if (context == CONTEXT_DQUOTE)
		return (lexer_context_dquote(state));
	if (context == CONTEXT_DOLLAR_SQUOTE)
		return (lexer_context_dollar_squote(state));
	if (context == CONTEXT_BACKTICK)
		return (lexer_context_backtick(state));
	if (context == CONTEXT_ARITH)
		return (lexer_context_arith(state));
	if (context == CONTEXT_PARAM)
		return (lexer_context_param(state));
	if (context == CONTEXT_CMD_SUB)
		return (state->err = error(ERR_NOT_IMPLEMENTED));
	if (context == CONTEXT_NONE)
		return (state->err = error(ERR_INCOHERENT_STATE));
	return (state->err = error(ERR_INCOHERENT_STATE));
}

```

./srcs/2_scanner/lexer/context/_utils_.c
```c
#include "reader_.h"
#include "lexer_context_.h"

t_error	context_EOI(t_lexer *state)
{
	if (state->is_stdin)
		state->err = reader_continuation(&state->input->str);
	else
		state->err = error(ERR_UNEXPECTED_EOI);
	return (state->err);
}

t_error	context_escape_next_char(t_lexer *state, t_escape_args args)
{
	bool	in_special_context;

	in_special_context = false;
	if (args.is_in_special_context != NULL)
		in_special_context = args.is_in_special_context(state);
	if (in_special_context && args.is_in_special_whitelist != NULL)
	{
		if (args.is_in_special_whitelist(state->input->str[state->input->i]))
			lexer_consume(state, state->token->type, 1);
	}
	else if (!in_special_context && args.is_in_whitelist != NULL)
	{
		if (args.is_in_whitelist(state->input->str[state->input->i]))
			lexer_consume(state, state->token->type, 1);
	}
	else
		state->err = error(ERR_INCOHERENT_STATE);
	return (state->err);
}

```

./srcs/2_scanner/lexer/context/_utils.c
```c
#include "lexer_context_.h"

static t_error	context_start(t_lexer *state, t_context_args args)
{
	state->token->type = TOKEN_TOKEN;
	if (args.stack_item != NULL)
		args.stack_item->start = state->token->value.len;
	state->err = context_stack_push(&state->input->context, args.stack_item);
	if (state->err.type)
		return (state->err);
	return (lexer_consume(state, state->token->type, args.opening_len));
}

static t_error	context_end(t_lexer *state, t_context_args args)
{
	t_context_parser_stack_item	*item;

	if (lexer_consume(state, state->token->type, args.closing_len).type)
		return (state->err);
	state->err = context_stack_bpop(&state->input->context, &item);
	if (state->err.type)
		return (state->err);
	return (item->end = state->token->value.len, state->err);
}

t_error	lexer_context_unescape(t_lexer *state, t_unescape_args args)
{
	if (state->input->str[state->input->i] == '\0')
		return (context_EOI(state));
	else if (args.special_handler != NULL)
		return (args.special_handler(state, args.special_args));
	else
		return (lexer_consume(state, state->token->type, 1));
}

t_error	lexer_context_escape(t_lexer *state, t_escape_args args)
{
	if (args.enable_line_continuation &&
		state->input->str[state->input->i + 1] == '\n')
	{
		lexer_advance(state, 2);
		if (state->input->str[state->input->i] == '\0')
			return (context_EOI(state));
	}
	else if (state->input->str[state->input->i] == '\0')
		return (context_EOI(state));
	else
	{
		if (lexer_consume(state, state->token->type, 1).type)
			return (state->err);	
		if (context_escape_next_char(state, args).type)
			return (state->err);
	}
	return (state->err);
}

t_error	lexer_context_scan(t_lexer *state, t_context_args args)
{
	char		*str;
	t_context	context;

	if (context_start(state, args).type)
		return (state->err);
	while (true)
	{
		if (state->err.type)
			return (state->err);
		str = state->input->str + state->input->i;
		if (args.is_end != NULL && args.is_end(*str, args.unescaped_args))
			return (context_end(state, args));
		else if (*str == '\\')
			args.escape(state);
		else if (args.quoting != NULL && args.is_quoting(str, &context))
			args.quoting(state, context);
		else if (args.expansion != NULL && args.is_expansion(str, &context))
			args.expansion(state, context);
		else
			args.unescaped(state, args.unescaped_args);
	}
}

```

./srcs/2_scanner/lexer/context/arith.c
```c
#include "lexer_rules_.h"
#include "lexer_context_.h"

static t_error	context_arith_unescape_(t_lexer *state, void *nesting_depth)
{
	if (state->input->str[state->input->i] == '(')
	{
		(*((size_t *)nesting_depth))++;
		if (lexer_consume(state, state->token->type, 1).type)
			return (state->err);
	}
	else if (state->input->str[state->input->i] == ')')
	{
		(*((size_t *)nesting_depth))--;
		if (lexer_consume(state, state->token->type, 1).type)
			return (state->err);
	}
	else
		return (lexer_consume(state, state->token->type, 1));
	return (state->err);
}

static t_error	context_arith_escape(t_lexer *state)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_context_dquote_whitelist;
	return (lexer_context_escape(state, args));
}

static t_error	context_arith_unescape(t_lexer *state, void *nesting_depth)
{
	t_unescape_args	args;
	
	args.special_args = nesting_depth;
	args.special_handler = context_arith_unescape_;
	return (lexer_context_unescape(state, args));
}

static t_context_args	context_arith_rules(
	size_t *nesting_depth,
	t_context_parser_stack_item *item)
{
	t_context_args	res;

	res.quoting = NULL;
	res.opening_len = 3;
	res.closing_len = 1;
	res.stack_item = item;
	res.is_quoting = NULL;
	res.context = CONTEXT_ARITH;
	res.escape = context_arith_escape;
	res.unescaped_args = nesting_depth;
	res.is_end = is_context_arith_ending;
	res.expansion = lexer_rule_expansion;
	res.unescaped = context_arith_unescape;
	res.is_expansion = is_expansion_context;
	return (res);
}

t_error	lexer_context_arith(t_lexer *state)
{
	t_context_args			args;
	t_context_parser_stack_item	*item;
	t_lexer_backup			backup;
	size_t					nesting_depth;

	nesting_depth = 0;
	backup = lexer_backup(state);
	state->err = context_parser_stack_item_init(&item, CONTEXT_ARITH);
	if (state->err.type)
		return (state->err);
	state->err = context_stack_push(&state->token->contexts, item);
	if (state->err.type)
		return (state->err);
	args = context_arith_rules(&nesting_depth, item);
	if (lexer_context_scan(state, args).type)
		return (state->err);
	if (state->input->str[state->input->i] != ')')
	{
		if (lexer_restore(state, backup).type)
			return (state->err);
		return (state->err = error(ERR_CTX_END_NOT_FOUND), state->err);
	}
	if (lexer_consume(state, state->token->type, 1).type)
		return (state->err);
	return (item->end = state->token->value.len, state->err);
}

```

./srcs/2_scanner/lexer/context/backtick.c
```c
#include "lexer_rules_.h"
#include "lexer_context_.h"

static bool	is_backtick_squote_surrounded(t_lexer *state)
{
	t_context_parser_stack_item	*item;
	
	if (state->input->context.len < 2)
		return (false);
	state->err = context_stack_get(
		&state->input->context,
		&item,
		state->input->context.len - 2);
    if (state->err.type)
        return (false);
    return (item->context == CONTEXT_DQUOTE || item->context == CONTEXT_ARITH);
}

static t_error	context_backtick_escape(t_lexer *state)
{
	t_escape_args	args;

	args.is_in_whitelist = is_in_context_backtick_whitelist;
	args.is_in_special_context = is_backtick_squote_surrounded;
	args.enable_line_continuation = is_backtick_squote_surrounded(state);
	args.is_in_special_whitelist = is_in_context_backtick_special_whitelist;
	return (lexer_context_escape(state, args));
}

static t_error	context_backtick_unescape(t_lexer *state, void *_)
{
	t_unescape_args	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (lexer_context_unescape(state, args));
}

static t_context_args	context_backtick_rules(t_context_parser_stack_item *item)
{
	t_context_args	res;

	res.opening_len = 1;
	res.closing_len = 1;
	res.stack_item = item;
	res.context = CONTEXT_BACKTICK;
	res.unescaped_args = NULL;
	res.quoting = lexer_rule_quoting;
	res.is_quoting = is_quoting_context;
	res.escape = context_backtick_escape;
	res.expansion = lexer_rule_expansion;
	res.is_expansion = is_expansion_context;
	res.is_end = is_context_backtick_ending;
	res.unescaped = context_backtick_unescape;
	return (res);
}

t_error	lexer_context_backtick(t_lexer *state)
{
	t_context_parser_stack_item	*item;

	state->err = context_parser_stack_item_init(&item, CONTEXT_BACKTICK);
	if (state->err.type)
		return (state->err);
	state->err = context_stack_push(&state->token->contexts, item);
	if (state->err.type)
		return (state->err);
	return (lexer_context_scan(state, context_backtick_rules(item)));
}

```

./srcs/2_scanner/lexer/context/cmd_sub.c
```c
#include "lexer_.h"
	
t_error	context_cmd_sub(t_lexer *state)
{
	// call function to run in subshell
	return (state->err);
}

```

./srcs/2_scanner/lexer/context/dollar_squote.c
```c
#include <stdlib.h>
#include "lexer_context_.h"

static t_error	context_dollar_squote_escape(t_lexer *state)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = false;
	args.is_in_whitelist = is_in_context_dollar_squote_whitelist;
	return (lexer_context_escape(state, args));
}

static t_error	context_dollar_squote_unescape(t_lexer *state, void *_)
{
	t_unescape_args	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (lexer_context_unescape(state, args));
}

static t_context_args	context_dollar_squote_rules(t_context_parser_stack_item *item)
{
	t_context_args	res;

	res.quoting = NULL;
	res.opening_len = 2;
	res.closing_len = 1;
	res.expansion = NULL;
	res.stack_item = item;
	res.is_quoting = NULL;
	res.is_expansion = NULL;
	res.unescaped_args = NULL;
	res.context = CONTEXT_DOLLAR_SQUOTE;
	res.escape = context_dollar_squote_escape;
	res.is_end = is_context_dollar_squote_ending;
	res.unescaped = context_dollar_squote_unescape;
	return (res);
}

t_error	lexer_context_dollar_squote(t_lexer *state)
{
	t_context_parser_stack_item	*item;

	state->err = context_parser_stack_item_init(&item, CONTEXT_DOLLAR_SQUOTE);
	if (state->err.type)
		return (state->err);
	state->err = lexer_context_scan(state, context_dollar_squote_rules(item));
	return (free(item), state->err);
}

```

./srcs/2_scanner/lexer/context/dquote.c
```c
#include <stdlib.h>
#include "lexer_rules_.h"
#include "lexer_context_.h"

static t_error	context_dquote_escape(t_lexer *state)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_context_dquote_whitelist;
	return (lexer_context_escape(state, args));
}

static t_error	context_dquote_unescape(t_lexer *state, void *_)
{
	t_unescape_args	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (lexer_context_unescape(state, args));
}

static t_context_args	context_dquote_rules(t_context_parser_stack_item *item)
{
	t_context_args	res;

	res.quoting = NULL;
	res.opening_len = 1;
	res.closing_len = 1;
	res.context = CONTEXT_DQUOTE;
	res.stack_item = item;
	res.is_quoting = NULL;
	res.unescaped_args = NULL;
	res.escape = context_dquote_escape;
	res.expansion = lexer_rule_expansion;
	res.is_end = is_context_dquote_ending;
	res.unescaped = context_dquote_unescape;
	res.is_expansion = is_expansion_context;
	return (res);
}

t_error	lexer_context_dquote(t_lexer *state)
{
	t_context_parser_stack_item	*item;

	state->err = context_parser_stack_item_init(&item, CONTEXT_DQUOTE);
	if (state->err.type)
		return (state->err);
	state->err = lexer_context_scan(state, context_dquote_rules(item));
	return (free(item), state->err);
}

```

./srcs/2_scanner/lexer/context/lexer_context_.h
```c
#ifndef LEXER_CONTEXT__H
# define LEXER_CONTEXT__H

# include "lexer_.h"

/**
 * @ingroup scanner
 * @struct s_escape_args
 * @brief Configures how a backslash is handled inside a given context.
 *
 * @var s_escape_args::enable_line_continuation Whether "\\<newline>" is a line
 *                                              continuation (removed) here.
 * @var s_escape_args::is_in_whitelist Characters that keep their special
 *                                     meaning after a backslash (normal case).
 * @var s_escape_args::is_in_special_whitelist Same, but when wrapped in a
 *                                             special surrounding context.
 * @var s_escape_args::is_in_special_context Predicate detecting that special
 *                                           surrounding context (may be NULL).
 */
typedef struct s_escape_args
{
	bool	enable_line_continuation;
	bool	(*is_in_whitelist)(char);
	bool	(*is_in_special_whitelist)(char);
	bool	(*is_in_special_context)(t_lexer *);
}	t_escape_args;

/**
 * @ingroup scanner
 * @struct s_unescape_args
 * @brief Configures how a plain (non-delimiter) character is consumed.
 *
 * @var s_unescape_args::special_args Opaque state passed to the handler (e.g.
 *                                    the arithmetic nesting depth).
 * @var s_unescape_args::special_handler Optional per-character handler; when
 *                                       NULL the character is consumed as-is.
 */
typedef struct s_unescape_args
{
	void	*special_args;
	t_error	(*special_handler)(t_lexer *, void *);
}	t_unescape_args;

/**
 * @ingroup scanner
 * @struct s_context_args
 * @brief Full configuration of one context scan driven by lexer_context_scan.
 *
 * @var s_context_args::context The context tag pushed while scanning.
 * @var s_context_args::opening_len Length of the opening delimiter to consume.
 * @var s_context_args::closing_len Length of the closing delimiter to consume.
 * @var s_context_args::stack_item Item whose [start, end) span this scan fills
 *                                 in: start when the context opens, end when it
 *                                 closes (NULL to record no span).
 * @var s_context_args::unescaped_args Opaque state for the unescaped handler.
 * @var s_context_args::escape Backslash handler.
 * @var s_context_args::is_end Predicate detecting the closing delimiter.
 * @var s_context_args::unescaped Plain-character handler.
 * @var s_context_args::quoting Nested quoting handler (may be NULL).
 * @var s_context_args::is_quoting Nested quoting detector (may be NULL).
 * @var s_context_args::expansion Nested expansion handler (may be NULL).
 * @var s_context_args::is_expansion Nested expansion detector (may be NULL).
 */
typedef struct s_context_args
{
	t_context				context;
	size_t					opening_len;
	size_t					closing_len;
	t_context_parser_stack_item	*stack_item;
	void					*unescaped_args;
	t_error					(*escape)(t_lexer *);
	bool					(*is_end)(char, void *);
	t_error					(*unescaped)(t_lexer *, void *);
	t_error					(*quoting)(t_lexer *, t_context);
	bool					(*is_quoting)(char *, t_context *);
	t_error					(*expansion)(t_lexer *, t_context);
	bool					(*is_expansion)(char *, t_context *);
}	t_context_args;

/**
 * @ingroup scanner
 * @brief Handles reaching end-of-input while still inside a context.
 *
 * When streaming from stdin, reads a continuation line and resumes; otherwise
 * reports an unterminated-construct error.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO once more input is available, or ERR_UNEXPECTED_EOI.
 */
t_error	context_EOI(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Consumes the character following a backslash when whitelisted.
 *
 * Uses the special or normal whitelist depending on the surrounding context;
 * a non-whitelisted character is left for normal processing.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param args Escape configuration for the current context.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	context_escape_next_char(t_lexer *state, t_escape_args args);

/**
 * @ingroup scanner
 * @brief Generic scan loop for one quoting/expansion context.
 *
 * Pushes the context, consumes the opening delimiter, then loops handling the
 * closing delimiter, backslashes, nested quoting/expansion and plain
 * characters; on the closing delimiter it consumes it and pops the context.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param args Configuration describing this context.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_context_scan(t_lexer *state, t_context_args args);

/**
 * @ingroup scanner
 * @brief Handles a backslash inside a context (line continuation or escape).
 * @param state Pointer to the lexer state (borrowed).
 * @param args Escape configuration for the current context.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_context_escape(t_lexer *state, t_escape_args args);

/**
 * @ingroup scanner
 * @brief Consumes one plain character of a context (or end-of-input/handler).
 * @param state Pointer to the lexer state (borrowed).
 * @param args Unescaped-character configuration for the current context.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_context_unescape(t_lexer *state, t_unescape_args args);

/**
 * @ingroup scanner
 * @brief Scans a parameter expansion: ${...}.
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_context_param(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Scans an arithmetic expansion: $((...)).
 *
 * Tracks parenthesis nesting and, when the trailing ")" is missing, rolls back
 * so the caller can retry the construct as a command substitution.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, ERR_CTX_END_NOT_FOUND when it is not arithmetic.
 */
t_error	lexer_context_arith(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Scans a double-quoted section: "..." (expansions stay active).
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_context_dquote(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Scans a backquote command substitution: `...`.
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_context_backtick(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Scans a single-quoted section: '...' (everything literal).
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_context_squote(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Scans an ANSI-C quoted section: $'...'.
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_context_dollar_squote(t_lexer *state);

#endif

```

./srcs/2_scanner/lexer/context/param.c
```c
#include "lexer_rules_.h"
#include "lexer_context_.h"

static t_error	context_param_escape(t_lexer *state)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_context_param_whitelist;
	return (lexer_context_escape(state, args));
}

static t_error	context_param_unescape(t_lexer *state, void *_)
{
	t_unescape_args	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (lexer_context_unescape(state, args));
}

static t_context_args	context_param_rules(t_context_parser_stack_item *item)
{
	t_context_args	res;

	res.opening_len = 2;
	res.closing_len = 1;
	res.context = CONTEXT_PARAM;
	res.stack_item = item;
	res.unescaped_args = NULL;
	res.quoting = lexer_rule_quoting;
	res.escape = context_param_escape;
	res.is_quoting = is_quoting_context;
	res.is_end = is_context_param_ending;
	res.expansion = lexer_rule_expansion;
	res.unescaped = context_param_unescape;
	res.is_expansion = is_expansion_context;
	return (res);
}

t_error	lexer_context_param(t_lexer *state)
{
	t_context_parser_stack_item	*item;

	state->err = context_parser_stack_item_init(&item, CONTEXT_PARAM);
	if (state->err.type)
		return (state->err);
	state->err = context_stack_push(&state->token->contexts, item);
	if (state->err.type)
		return (state->err);
	return (lexer_context_scan(state, context_param_rules(item)));
}

```

./srcs/2_scanner/lexer/context/squote.c
```c
#include <stdlib.h>
#include "lexer_context_.h"

static t_error	context_squote_escape(t_lexer *state)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = false;
	args.is_in_whitelist = is_in_context_squote_whitelist;
	return (lexer_context_escape(state, args));
}

static t_error	context_squote_unescape(t_lexer *state, void *_)
{
	t_unescape_args	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (lexer_context_unescape(state, args));
}

static t_context_args	context_squote_rules(t_context_parser_stack_item *item)
{
	t_context_args	res;

	res.quoting = NULL;
	res.opening_len = 1;
	res.closing_len = 1;
	res.context = CONTEXT_SQUOTE;
	res.expansion = NULL;
	res.stack_item = item;
	res.is_quoting = NULL;
	res.is_expansion = NULL;
	res.unescaped_args = NULL;
	res.escape = context_squote_escape;
	res.is_end = is_context_squote_ending;
	res.unescaped = context_squote_unescape;
	return (res);
}

t_error	lexer_context_squote(t_lexer *state)
{
	t_context_parser_stack_item	*item;

	state->err = context_parser_stack_item_init(&item, CONTEXT_SQUOTE);
	if (state->err.type)
		return (state->err);
	state->err = lexer_context_scan(state, context_squote_rules(item));
	return (free(item), state->err);
}

```

./srcs/2_scanner/lexer/input_stack/_init.c
```c
#include <stdlib.h>
#include "input_stack_.h"

void	input_parser_stack_item_free(void *item)
{
	t_input_parser_stack_item	**item_;

	item_ = (t_input_parser_stack_item **)item;
	if ((*item_)->str != NULL)
		free((*item_)->str);
	ft_bzero((*item_)->context.data, (*item_)->context.cap);
	vector_free(&(*item_)->context, NULL);
	**item_ = (t_input_parser_stack_item){0};
	free(*item_);
	*item_ = NULL;
}

t_error	input_parser_stack_item_init(t_input_parser_stack_item **item)
{
	*item = malloc(sizeof(t_input_parser_stack_item));
	if (*item == NULL)
		return (error_sys());
	**item = (t_input_parser_stack_item){0};
	context_stack_init(&(*item)->context);
	return (error(ERR_NO));
}

void	input_stack_init(t_input_stack *stack)
{
	vector_init(stack, sizeof(t_input_parser_stack_item *), 0);
}

void	input_stack_free(t_input_stack *stack)
{
	vector_free(stack, input_parser_stack_item_free);
}

```

./srcs/2_scanner/lexer/input_stack/_main.c
```c
#include "input_stack_.h"

t_error	input_stack_pop(t_input_stack *stack)
{
	t_input_parser_stack_item	*last_item;

	if (!vector_remove(stack, stack->len - 1, (void **)&last_item))
		return (error_sys());
	return (input_parser_stack_item_free(&last_item), error(ERR_NO));
}

t_error	input_stack_push(t_input_stack *stack, t_input_parser_stack_item *item)
{
	if (!vector_push(stack, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	input_stack_get_last(t_input_stack *stack, t_input_parser_stack_item **item)
{
	if (stack->len == 0)
		return (error(ERR_EMPTY_STACK));
	*item = ((t_input_parser_stack_item **)stack->data)[stack->len - 1];
	return (error(ERR_NO));
}

```

./srcs/2_scanner/lexer/input_stack/input_stack_.h
```c
#ifndef INPUT_STACK__H
# define INPUT_STACK__H

# include "context.h"

/**
 * @ingroup scanner
 * @brief Stack of input sources, innermost on top (a vector of item pointers).
 *
 * The base input sits at the bottom; alias expansions and line continuations
 * are pushed on top and popped when exhausted, so the lexer always reads from
 * the topmost item.
 */
typedef t_vector	t_input_stack;

/**
 * @ingroup scanner
 * @struct s_input_parser_stack_item
 * @brief One input source: its text, a read cursor and its own context stack.
 *
 * Items are heap-allocated; the stack stores pointers to them so growth never
 * moves a live item out from under the lexer's borrowed pointer.
 *
 * @var s_input_parser_stack_item::i Read cursor (index into str).
 * @var s_input_parser_stack_item::str Owned input text (NUL-terminated).
 * @var s_input_parser_stack_item::context Per-input stack of open quoting/expansion
 *                                  contexts.
 */
typedef struct s_input_parser_stack_item
{
	size_t			i;
	char			*str;
	t_context_stack	context;
}	t_input_parser_stack_item;

/**
 * @ingroup scanner
 * @brief Initialises an empty input stack (a vector of item pointers).
 * @param stack Pointer to the stack to initialise (borrowed).
 */
void	input_stack_init(t_input_stack *stack);

/**
 * @ingroup scanner
 * @brief Frees the stack and every item it still holds.
 * @param stack Pointer to the stack to free (borrowed).
 */
void	input_stack_free(t_input_stack *stack);

/**
 * @ingroup scanner
 * @brief Frees one input item: its text, its context stack and the item.
 *
 * Takes the address of the stored pointer (matching the vector destructor
 * signature) and releases both the item's contents and the allocation itself.
 *
 * @param item Address of the stored item pointer (t_input_parser_stack_item **).
 */
void	input_parser_stack_item_free(void *item);

/**
 * @ingroup scanner
 * @brief Allocates and zero-initialises a new input item.
 *
 * @param item Out-parameter receiving the freshly allocated item.
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	input_parser_stack_item_init(t_input_parser_stack_item **item);

/**
 * @ingroup scanner
 * @brief Removes the top input item and frees it.
 * @param stack Pointer to the stack (borrowed).
 * @return ERR_NO on success, ERR_LIBC on internal failure.
 */
t_error	input_stack_pop(t_input_stack *stack);

/**
 * @ingroup scanner
 * @brief Pushes an item pointer as the new top of the stack.
 *
 * Ownership of @p item transfers to the stack.
 *
 * @param stack Pointer to the stack (borrowed).
 * @param item Item to push (ownership transferred).
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	input_stack_push(t_input_stack *stack, t_input_parser_stack_item *item);

/**
 * @ingroup scanner
 * @brief Reads the top input item without removing it.
 * @param stack Pointer to the stack (borrowed).
 * @param item Out-parameter receiving the borrowed top item pointer.
 * @return ERR_NO on success, ERR_EMPTY_STACK if the stack is empty.
 */
t_error	input_stack_get_last(t_input_stack *stack, t_input_parser_stack_item **item);

#endif

```

./srcs/2_scanner/lexer/lexer_.h
```c
#ifndef LEXER__H
# define LEXER__H

# include "token.h"
# include "error.h"
# include "context.h"
# include "input_stack_.h"

/**
 * @ingroup scanner
 * @struct s_lexer_backup
 * @brief Snapshot of the lexer used to roll back a speculative scan.
 *
 * Captures just enough state to undo a partial scan (used when an arithmetic
 * expansion turns out not to be one and must be retried as a command
 * substitution).
 *
 * @var s_lexer_backup::i Input cursor position to restore.
 * @var s_lexer_backup::token_type Token type to restore.
 * @var s_lexer_backup::context_len Context-stack depth to unwind back to.
 * @var s_lexer_backup::token_value_len Token value length to truncate back to.
 */
typedef struct s_lexer_backup
{
	size_t			i;
	t_token_type	token_type;
	size_t			context_len;
	size_t			token_value_len;
	size_t			token_contexts_len;
}	t_lexer_backup;

/**
 * @ingroup scanner
 * @struct s_lexer
 * @brief State of the lexer that recognises one token at a time.
 *
 * @var s_lexer::err Last error recorded by the lexer.
 * @var s_lexer::input Borrowed pointer to the current input item on top of the
 *                     stack (its string, cursor and per-input context stack).
 * @var s_lexer::token Borrowed pointer to the token currently being built.
 * @var s_lexer::is_stdin Whether input is streamed line-by-line from stdin
 *                        (interactive terminal or pipe), enabling line
 *                        continuation and here-document body reads.
 * @var s_lexer::input_stack Stack of inputs; alias expansions and line
 *                           continuations are pushed on top of the base input.
 * @var s_lexer::emited_token Set when a complete token has been delimited.
 */
typedef struct s_lexer
{
	t_error						err;
	t_input_parser_stack_item	*input;
	t_token						*token;
	bool						is_stdin;
	t_input_stack				input_stack;
	bool						emited_token;
}	t_lexer;

/**
 * @ingroup scanner
 * @brief Releases the lexer's input stack and resets it to zero.
 * @param state Pointer to the lexer state (borrowed).
 */
void			lexer_free(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Initialises the lexer to an empty, ready-to-use value.
 * @param state Pointer to the lexer state (borrowed).
 */
void			lexer_init(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Records whether input is streamed line-by-line from stdin.
 * @param state Pointer to the lexer state (borrowed).
 * @param is_stdin true when reading incrementally from stdin (terminal/pipe).
 */
void			lexer_load(t_lexer *state, bool is_stdin);

/**
 * @ingroup scanner
 * @brief Snapshots the lexer for a possible later rollback.
 * @param state Pointer to the lexer state (borrowed).
 * @return A backup capturing cursor, token type/length and context depth.
 */
t_lexer_backup	lexer_backup(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Marks the token currently being built as complete.
 * @param state Pointer to the lexer state (borrowed).
 */
void			lexer_delimit_token(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Advances the input cursor by @p offset characters (no consumption).
 * @param state Pointer to the lexer state (borrowed).
 * @param offset Number of characters to skip.
 */
void			lexer_advance(t_lexer *state, size_t offset);

/**
 * @ingroup scanner
 * @brief Restores the lexer to a previously captured backup.
 *
 * Pops contexts back to the snapshot depth, then restores the cursor, token
 * type and token value length.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param backup Snapshot to restore.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error			lexer_restore(t_lexer *state, t_lexer_backup backup);

/**
 * @ingroup scanner
 * @brief Appends @p iter input characters to the token and advances.
 *
 * Copies the next @p iter characters into the token value, tags the token with
 * @p type and advances the cursor by the same amount.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param type Token type to assign while consuming.
 * @param iter Number of characters to consume.
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error			lexer_consume(t_lexer *state, t_token_type type, size_t iter);

/**
 * @ingroup scanner
 * @brief Tests whether the current character can extend/begin an operator.
 * @param state Pointer to the lexer state (borrowed).
 * @return true when the current character is part of an operator token.
 */
bool			is_operator_char(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Consumes the current operator character into the token.
 *
 * Dispatches on the current character to the matching operator builder,
 * extending the operator token by one character.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error			lexer_add_char_into_token_operator(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Scans a quoting or expansion construct of the given context.
 *
 * Dispatches to the matching context scanner (single/double/ANSI-C quotes,
 * parameter, arithmetic, backquote). Command substitution is not yet
 * implemented.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param context Context to scan.
 * @return ERR_NO on success, or the recorded error (e.g. ERR_NOT_IMPLEMENTED).
 */
t_error			lexer_context(t_lexer *state, t_context context);

/**
 * @ingroup scanner
 * @brief Applies one POSIX token-recognition rule to the current character.
 *
 * Tested in POSIX §2.3 order: end-of-input, operator-in-progress, quoting,
 * expansion, new operator, blank, in-word, comment, then new word.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param context Out-parameter receiving the detected context, if any.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error			lexer_rules(t_lexer *state, t_context *context);

/**
 * @ingroup scanner
 * @brief Produces the next token from the top input on the stack.
 *
 * Reads the current input, initialises @p token, then applies recognition
 * rules until a token is delimited or end-of-input is reached; pops the input
 * on end-of-input.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param token Out-parameter receiving the produced token (borrowed).
 * @return ERR_NO on success, ERR_EMPTY_STACK if no input remains, or the
 *         recorded error on failure.
 */
t_error			lexer_next_token(t_lexer *state, t_token *token);

#endif

```

./srcs/2_scanner/lexer/operator/_main.c
```c
#include "lexer_operator_.h"

bool	is_operator_char(t_lexer *state)
{
	const char	*input_ptr;

	input_ptr = state->input->str + state->input->i;
	if (input_ptr[0] == '\n' && !is_in_middle_of_operator(state))
		return (true);
	else if (input_ptr[0] == '(' && !is_in_middle_of_operator(state))
		return (true);
	else if (input_ptr[0] == ')' && !is_in_middle_of_operator(state))
		return (true);
	else if (input_ptr[0] == ';')
		return (is_operator_char_semicolon(state));
	else if (input_ptr[0] == '&')
		return (is_operator_char_ampersand(state));
	else if (input_ptr[0] == '|')
		return (is_operator_char_pipe(state));
	else if (input_ptr[0] == '<')
		return (is_operator_char_less(state));
	else if (input_ptr[0] == '>')
		return (is_operator_char_great(state));
	else if (input_ptr[0] == '-' && state->token->type == TOKEN_DLESS)
		return (true);
	return (false);
}

t_error	lexer_add_char_into_token_operator(t_lexer *state)
{
	const char	*input_ptr;

	input_ptr = state->input->str + state->input->i;
	if (input_ptr[0] == '\n')
		return (lexer_consume(state, TOKEN_NEWLINE, 1));
	else if (input_ptr[0] == '(')
		return (lexer_consume(state, TOKEN_LPARENTHESIS, 1));
	else if (input_ptr[0] == ')')
		return (lexer_consume(state, TOKEN_RPARENTHESIS, 1));
	else if (input_ptr[0] == ';')
		return (operator_add_semicolon(state));
	else if (input_ptr[0] == '&')
		return (operator_add_ampersand(state));
	else if (input_ptr[0] == '|')
		return (operator_add_pipe(state));
	else if (input_ptr[0] == '<')
		return (operator_add_less(state));
	else if (input_ptr[0] == '>')
		return (operator_add_great(state));
	else if (input_ptr[0] == '-')
		return (lexer_consume(state, TOKEN_DLESSDASH, 1));
	return (state->err = error(ERR_INCOHERENT_STATE));
}

```

./srcs/2_scanner/lexer/operator/_utils.c
```c
#include "lexer_operator_.h"

bool	is_in_middle_of_operator(t_lexer *state)
{
	return (state->token->type != TOKEN_NONE
		&& state->token->type != TOKEN_TOKEN);
}

```

./srcs/2_scanner/lexer/operator/ampersand.c
```c
#include "lexer_operator_.h"

bool	is_operator_char_ampersand(t_lexer *state)
{
	if (state->token->type == TOKEN_SCOLON)
		return (true);
	else if (state->token->type == TOKEN_AMPERSAND)
		return (true);
	else if (state->token->type == TOKEN_LESS)
		return (true);
	else if (state->token->type == TOKEN_GREAT)
		return (true);
	else if (!is_in_middle_of_operator(state))
		return (true);
	return (false);
}

t_error	operator_add_ampersand(t_lexer *state)
{
	if (state->token->type == TOKEN_SCOLON)
		return (lexer_consume(state, TOKEN_SEMI_AND, 1));
	else if (state->token->type == TOKEN_AMPERSAND)
		return (lexer_consume(state, TOKEN_AND_IF, 1));
	else if (state->token->type == TOKEN_LESS)
		return (lexer_consume(state, TOKEN_LESSAND, 1));
	else if (state->token->type == TOKEN_GREAT)
		return (lexer_consume(state, TOKEN_GREATAND, 1));
	else if (state->token->type == TOKEN_NONE)
		return (lexer_consume(state, TOKEN_AMPERSAND, 1));
	return (state->err = error(ERR_INCOHERENT_STATE));
}

```

./srcs/2_scanner/lexer/operator/great.c
```c
#include "lexer_operator_.h"

bool	is_operator_char_great(t_lexer *state)
{
	if (state->token->type == TOKEN_LESS)
		return (true);
	else if (state->token->type == TOKEN_GREAT)
		return (true);
	else if (!is_in_middle_of_operator(state))
		return (true);
	return (false);
}

t_error	operator_add_great(t_lexer *state)
{
	if (state->token->type == TOKEN_LESS)
		return (lexer_consume(state, TOKEN_LESSGREAT, 1));
	else if (state->token->type == TOKEN_GREAT)
		return (lexer_consume(state, TOKEN_DGREAT, 1));
	else if (state->token->type == TOKEN_NONE)
		return (lexer_consume(state, TOKEN_GREAT, 1));
	return (state->err = error(ERR_INCOHERENT_STATE));
}

```

./srcs/2_scanner/lexer/operator/less.c
```c
#include "lexer_operator_.h"

bool	is_operator_char_less(t_lexer *state)
{
	if (state->token->type == TOKEN_LESS)
		return (true);
	else if (!is_in_middle_of_operator(state))
		return (true);
	return (false);
}

t_error	operator_add_less(t_lexer *state)
{
	if (state->token->type == TOKEN_LESS)
		return (lexer_consume(state, TOKEN_DLESS, 1));
	else if (state->token->type == TOKEN_NONE)
		return (lexer_consume(state, TOKEN_LESS, 1));
	return (state->err = error(ERR_INCOHERENT_STATE));
}

```

./srcs/2_scanner/lexer/operator/lexer_operator_.h
```c
#ifndef LEXER_OPERATOR__H
# define LEXER_OPERATOR__H

# include "lexer_.h"

/**
 * @ingroup scanner
 * @brief Tests whether the token being built is an operator in progress.
 * @param state Pointer to the lexer state (borrowed).
 * @return true when the current token has an operator type (not NONE/word).
 */
bool	is_in_middle_of_operator(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Tests whether the current character can extend a '<' operator.
 * @param state Pointer to the lexer state (borrowed).
 * @return true if the current character continues a less-than operator.
 */
bool	is_operator_char_less(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Tests whether the current character can extend a '|' operator.
 * @param state Pointer to the lexer state (borrowed).
 * @return true if the current character continues a pipe operator.
 */
bool	is_operator_char_pipe(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Tests whether the current character can extend a '>' operator.
 * @param state Pointer to the lexer state (borrowed).
 * @return true if the current character continues a greater-than operator.
 */
bool	is_operator_char_great(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Tests whether the current character can extend a ';' operator.
 * @param state Pointer to the lexer state (borrowed).
 * @return true if the current character continues a semicolon operator.
 */
bool	is_operator_char_semicolon(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Tests whether the current character can extend a '&' operator.
 * @param state Pointer to the lexer state (borrowed).
 * @return true if the current character continues an ampersand operator.
 */
bool	is_operator_char_ampersand(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Consumes a '<'-family operator character, refining its token type.
 *
 * Extends the operator into LESS, DLESS, DLESSDASH, LESSAND or LESSGREAT as
 * the following characters dictate.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	operator_add_less(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Consumes a '|'-family operator character (PIPE or OR_IF).
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	operator_add_pipe(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Consumes a '>'-family operator character, refining its token type.
 *
 * Extends the operator into GREAT, DGREAT, GREATAND or CLOBBER as the
 * following characters dictate.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	operator_add_great(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Consumes a ';'-family operator character (SCOLON, DSEMI or SEMI_AND).
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	operator_add_semicolon(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Consumes a '&'-family operator character (AMPERSAND or AND_IF).
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	operator_add_ampersand(t_lexer *state);

#endif

```

./srcs/2_scanner/lexer/operator/pipe.c
```c
#include "lexer_operator_.h"

bool	is_operator_char_pipe(t_lexer *state)
{
	if (state->token->type == TOKEN_PIPE)
		return (true);
	else if (state->token->type == TOKEN_GREAT)
		return (true);
	else if (!is_in_middle_of_operator(state))
		return (true);
	return (false);
}

t_error	operator_add_pipe(t_lexer *state)
{
	if (state->token->type == TOKEN_PIPE)
		return (lexer_consume(state, TOKEN_OR_IF, 1));
	else if (state->token->type == TOKEN_GREAT)
		return (lexer_consume(state, TOKEN_CLOBBER, 1));
	else if (state->token->type == TOKEN_NONE)
		return (lexer_consume(state, TOKEN_PIPE, 1));
	return (state->err = error(ERR_INCOHERENT_STATE));
}

```

./srcs/2_scanner/lexer/operator/semicolon.c
```c
#include "lexer_operator_.h"

bool	is_operator_char_semicolon(t_lexer *state)
{
	if (state->token->type == TOKEN_SCOLON)
		return (true);
	else if (!is_in_middle_of_operator(state))
		return (true);
	return (false);
}

t_error	operator_add_semicolon(t_lexer *state)
{
	if (state->token->type == TOKEN_SCOLON)
		return (lexer_consume(state, TOKEN_DSEMI, 1));
	else if (state->token->type == TOKEN_NONE)
		return (lexer_consume(state, TOKEN_SCOLON, 1));
	return (state->err = error(ERR_INCOHERENT_STATE));
}

```

./srcs/2_scanner/lexer/rules/_main.c
```c
#include "lexer_rules_.h"
#include "lexer_operator_.h"

t_error	lexer_rules(t_lexer *state, t_context *context)
{
	if (is_end(state))
		return (lexer_rule_end(state));
	else if (is_in_middle_of_operator(state))
		return (lexer_rule_in_middle_of_operator(state));
	else if (is_quoting_context(state->input->str + state->input->i, context))
		return (lexer_rule_quoting(state, *context));
	else if (is_expansion_context(state->input->str + state->input->i, context))
		return (lexer_rule_expansion(state, *context));
	else if (is_new_operator(state))
		return (lexer_rule_new_operator(state));
	else if (is_blank(state->input->str[state->input->i]))
		return (lexer_rule_blank(state));
	else if (is_in_middle_of_word(state))
		return (lexer_rule_in_middle_of_word(state));
	else if (is_comment(state))
		return (lexer_rule_comment(state), state->err);
	else
		return (lexer_rule_new_word(state));
}

```

./srcs/2_scanner/lexer/rules/blank.c
```c
#include "lexer_rules_.h"

t_error	lexer_rule_blank(t_lexer *state)
{
	if (state->token->type != TOKEN_NONE)
		return (lexer_delimit_token(state), state->err);
	while (is_blank(state->input->str[state->input->i]) &&
		state->input->str[state->input->i] != '\0')
		state->input->i++;
	return (state->err);
}

```

./srcs/2_scanner/lexer/rules/comment.c
```c
#include "lexer_rules_.h"

bool	is_comment(t_lexer *state)
{
	return (state->input->str[state->input->i] == '#');
}

void	lexer_rule_comment(t_lexer *state)
{
	while (state->input->str[state->input->i] != '\0' &&
		state->input->str[state->input->i] != '\n')
		state->input->i++;
}

```

./srcs/2_scanner/lexer/rules/context.c
```c
#include "lexer_rules_.h"

t_error	lexer_rule_quoting(t_lexer *state, t_context context)
{
	return (lexer_context(state, context));
}

t_error	lexer_rule_expansion(t_lexer *state, t_context context)
{
	if (context != CONTEXT_ARITH)
		return (lexer_context(state, context));
	else
	{
		if (lexer_context(state, CONTEXT_ARITH).type == ERR_CTX_END_NOT_FOUND)
		{
			state->err = error(ERR_NO);
			return (lexer_context(state, CONTEXT_CMD_SUB));
		}
		return (state->err);
	}
}

```

./srcs/2_scanner/lexer/rules/end.c
```c
#include "lexer_rules_.h"

bool	is_end(t_lexer *state)
{
	return (state->input->str[state->input->i] == '\0');
}

t_error	lexer_rule_end(t_lexer *state)
{
	lexer_delimit_token(state);
	if (state->token->type == TOKEN_NONE)
		state->token->type = TOKEN_EOF;
	return (state->err);
}

```

./srcs/2_scanner/lexer/rules/lexer_rules_.h
```c
#ifndef LEXER_RULES__H
# define LEXER_RULES__H

# include "lexer_.h"

/**
 * @ingroup scanner
 * @brief Tests whether the cursor is at end-of-input (NUL).
 * @param state Pointer to the lexer state (borrowed).
 * @return true if the current character is '\0'.
 */
bool	is_end(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Tests whether the current character starts a comment ('#').
 *
 * Only meaningful when not in the middle of a word; the dispatcher checks the
 * word rule first so a '#' inside a word stays literal.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @return true if the current character is '#'.
 */
bool	is_comment(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Tests whether a new operator starts here.
 * @param state Pointer to the lexer state (borrowed).
 * @return true if not mid-operator and the current character is an operator.
 */
bool	is_new_operator(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Tests whether a word token is currently being built.
 * @param state Pointer to the lexer state (borrowed).
 * @return true if the current token is a word.
 */
bool	is_in_middle_of_word(t_lexer *state);

/**
 * @ingroup scanner
 * @brief POSIX rule 1: end-of-input delimits the current token (or stops).
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO; delimits a pending token or marks end-of-input.
 */
t_error	lexer_rule_end(t_lexer *state);								// Rule 1

/**
 * @ingroup scanner
 * @brief POSIX rule 7: a blank delimits a pending token, else it is skipped.
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_rule_blank(t_lexer *state);							// Rule 7

/**
 * @ingroup scanner
 * @brief POSIX rule 9: discards a comment to the end of the line.
 * @param state Pointer to the lexer state (borrowed).
 */
void	lexer_rule_comment(t_lexer *state);							// Rule 9

/**
 * @ingroup scanner
 * @brief POSIX rule 10: begins a new word with the current character.
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_rule_new_word(t_lexer *state);						// Rule 10

/**
 * @ingroup scanner
 * @brief POSIX rule 6: a new operator delimits a pending word, else it starts.
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_rule_new_operator(t_lexer *state);					// Rule 6

/**
 * @ingroup scanner
 * @brief POSIX rule 8: appends the current character to the current word.
 *
 * Handles a leading backslash as a top-level escape (with line continuation).
 *
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_rule_in_middle_of_word(t_lexer *state);				// Rule 8

/**
 * @ingroup scanner
 * @brief POSIX rules 2-3: extend the operator, or delimit it when it cannot.
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_rule_in_middle_of_operator(t_lexer *state);			// Rule 2-3

/**
 * @ingroup scanner
 * @brief POSIX rule 4: scans a quoting construct, keeping it in the word.
 * @param state Pointer to the lexer state (borrowed).
 * @param context Quoting context detected at the cursor.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_rule_quoting(t_lexer *state, t_context context);		// Rule 4

/**
 * @ingroup scanner
 * @brief POSIX rule 5: scans an expansion construct, keeping it in the word.
 *
 * For an arithmetic context, falls back to command substitution when the
 * "$((" turns out not to close as arithmetic.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param context Expansion context detected at the cursor.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_rule_expansion(t_lexer *state, t_context context);	// Rule 5

#endif

```

./srcs/2_scanner/lexer/rules/operator.c
```c
#include <stdlib.h>
#include "lexer_rules_.h"
#include "lexer_operator_.h"

static bool	is_next_char_redirection(t_lexer *state)
{
	return (state->input->str[state->input->i] == '>' ||
		state->input->str[state->input->i] == '<');
}

static bool	is_token_io_number(t_lexer *state)
{
	int		io_number;
	char	*token_str;

	if (is_next_char_redirection(state))
	{
		token_str = buff_get_string(&state->token->value);
		if (token_str == NULL)
			return (state->err = error_sys(), false);
		if (!parse_int(token_str, &io_number))
			return (free(token_str), false);
		return (free(token_str), true);
	}
	return (false);
}

bool	is_new_operator(t_lexer *state)
{
	return (!is_in_middle_of_operator(state) && is_operator_char(state));
}

t_error	lexer_rule_in_middle_of_operator(t_lexer *state) // Rule 2-3
{
	if (is_operator_char(state)) // Rule 2
		return (lexer_add_char_into_token_operator(state), state->err);
	else
		return (lexer_delimit_token(state), state->err); // Rule 3
}

t_error	lexer_rule_new_operator(t_lexer *state) // Rule 6
{
	if (state->token->type != TOKEN_NONE)
	{
		if (is_token_io_number(state))
			state->token->type = TOKEN_IO_NUMBER;
		if (state->err.type)
			return (state->err);
		else
			return (lexer_delimit_token(state), state->err);
	}
	else
		return (lexer_add_char_into_token_operator(state), state->err);
}

```

./srcs/2_scanner/lexer/rules/word.c
```c
#include "lexer_rules_.h"
#include "lexer_context_.h"

static t_error	context_top_level_escape(t_lexer *state)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_context_none_whitelist;
	return (lexer_context_escape(state, args));
}

bool	is_in_middle_of_word(t_lexer *state)
{
	return (state->token->type == TOKEN_TOKEN);
}

t_error	lexer_rule_in_middle_of_word(t_lexer *state)  // Rule 8
{
	if (state->input->str[state->input->i] == '\\')
		return (context_top_level_escape(state));
	else
		return (lexer_consume(state, TOKEN_TOKEN, 1));
}

t_error	lexer_rule_new_word(t_lexer *state) // Rule 10
{
	if (state->input->str[state->input->i] == '\\')
		return (context_top_level_escape(state));
	else
		return (lexer_consume(state, TOKEN_TOKEN, 1));
}

```

./srcs/2_scanner/reader/_main.c
```c
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "reader_.h"
#include "history.h"

t_error	reader_heredoc(char **res)
{
	t_error	err;
	char	*new_input;
	char	*heredoc;

	err = readline_(&heredoc, "> ");
	if (err.type)
		return (err);
	if (*res == NULL)
		return (*res = heredoc, error(ERR_NO));
	err = history_append_to_entry(heredoc);
	if (err.type)
		return (free(heredoc), err);
	new_input = str_join(*res, heredoc);
	if (new_input == NULL)
		return (free(heredoc), error_sys());
	return (free(*res), free(heredoc), *res = new_input, error(ERR_NO));
}

t_error	reader_new_input(char **res)
{
	t_error	err;

	history_save_entry();
	err = readline_(res, "$ ");
	if (err.type)
		return (err);
	if (str_len(*res) == 1)
		return (free(*res), *res = NULL, error(ERR_NO));
	err = history_append_to_entry(*res);
	if (err.type)
		return (free(*res), err);
	return (error(ERR_NO));
}

t_error	reader_continuation(char **res)
{
	t_error	err;
	char	*new_input;
	char	*continuation;

	err = readline_(&continuation, "> ");
	if (err.type)
		return (err);
	err = history_append_to_entry(continuation);
	if (err.type)
		return (free(continuation), err);
	new_input = str_join(*res, continuation);
	if (new_input == NULL)
		return (free(continuation), error_sys());
	return (free(*res), free(continuation), *res = new_input, error(ERR_NO));
}

t_error	reader_file_input(char **res, const char *path)
{
	int		fd;
	t_buff	buffer;
	char	*content;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error(ERR_OPEN_FILE));
	buff_init(&buffer, 0, NULL, 0);
	if (!buff_read_all(&buffer, fd))
		return (close(fd), buff_free(&buffer), error_sys());
	content = buff_get_string(&buffer);
	if (content == NULL)
		return (close(fd), buff_free(&buffer), error_sys());
	*res = str_join(content, "\n");
	if (*res == NULL)
		return (close(fd), buff_free(&buffer), free(content), error_sys());
	return (close(fd), buff_free(&buffer), free(content), error(ERR_NO));
}

```

./srcs/2_scanner/reader/_utils.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "libft.h"
#include "shell.h"
#include "reader_.h"

t_error	readline_(char **res, const char *prompt)
{
	char	*input;

	*res = readline(prompt);
	while (*res == NULL)
	{
		shell_exit_on_veof();
		if (!option_is_active(OPT_INTERACTIVE))
			return (error(ERR_VEOF));
		*res = readline(prompt);
	}
	if (**res == '\0')
	{
		free(*res);
		*res = str_dup("");
		if (*res == NULL)
			return (error_sys());
	}
	input = str_join(*res, "\n");
	if (input == NULL)
		return (free(*res), error_sys());
	return (free(*res), *res = input, error(ERR_NO));
}

```

./srcs/2_scanner/reader/reader_.h
```c
#ifndef READER__H
# define READER__H

# include "error.h"

/**
 * @ingroup scanner
 * @brief Reads one here-document body line, appending it to @p res.
 *
 * Prompts for and reads a line; if @p *res is NULL it becomes the line,
 * otherwise the line is appended. The caller owns the resulting string.
 *
 * @param res In/out heap string holding the accumulated body (owned).
 * @return ERR_NO on success, ERR_NULL_ARGS if @p res is NULL, ERR_VEOF at a
 *         non-interactive end-of-input, or ERR_LIBC on allocation failure.
 */
t_error	reader_heredoc(char **res);

/**
 * @ingroup scanner
 * @brief Reads a fresh command line from standard input (primary prompt).
 *
 * Sets @p *res to a newly allocated line (newline-terminated). An empty line
 * yields @p *res == NULL with ERR_NO, so the caller can treat it as a no-op.
 *
 * @param res Out heap string receiving the line (owned), or NULL if empty.
 * @return ERR_NO on success, ERR_NULL_ARGS if @p res is NULL, ERR_VEOF at a
 *         non-interactive end-of-input, or ERR_LIBC on allocation failure.
 */
t_error	reader_new_input(char **res);

/**
 * @ingroup scanner
 * @brief Reads a continuation line and appends it to @p res (secondary prompt).
 *
 * Used when a construct spans lines (an open quote or a trailing backslash).
 * The caller owns the resulting string.
 *
 * @param res In/out heap string holding the input being continued (owned).
 * @return ERR_NO on success, ERR_NULL_ARGS if @p res is NULL, ERR_VEOF at a
 *         non-interactive end-of-input, or ERR_LIBC on allocation failure.
 */
t_error	reader_continuation(char **res);

/**
 * @ingroup scanner
 * @brief Reads an entire file into @p res.
 *
 * Opens @p path, reads it fully into a newly allocated string and closes it.
 * The caller owns the resulting string.
 *
 * @param res Out heap string receiving the file contents (owned).
 * @param path File to read (borrowed).
 * @return ERR_NO on success, ERR_NULL_ARGS if @p path is NULL, ERR_OPEN_FILE
 *         if it cannot be opened, or ERR_LIBC on allocation failure.
 */
t_error	reader_file_input(char **res, const char *path);

/**
 * @ingroup scanner
 * @brief Low-level prompted read of a single line, newline-terminated.
 *
 * Reads one line via readline(), appends a '\n', and returns it through
 * @p res. On end-of-input it lets the shell decide whether to exit; in a
 * non-interactive session that cannot exit, it surfaces ERR_VEOF instead of
 * looping.
 *
 * @param res Out heap string receiving the line (owned).
 * @param prompt Prompt string to display (borrowed).
 * @return ERR_NO on success, ERR_VEOF at a non-interactive end-of-input, or
 *         ERR_LIBC on allocation failure.
 */
t_error	readline_(char **res, const char *prompt);

#endif

```

./srcs/2_scanner/scanner_.h
```c
#ifndef SCANNER__H
# define SCANNER__H

# include "scanner.h"

/**
 * @ingroup scanner
 * @brief Reads the next chunk of input and pushes it on the lexer stack.
 *
 * Allocates an input item and fills it according to the mode (whole file,
 * duplicated command string, or one stdin line), then pushes it; on error the
 * item is freed and not pushed. Called only when the input stack is empty.
 *
 * @param state Pointer to the scanner state (borrowed).
 * @return ERR_NO on success, ERR_LIBC on allocation failure, or the reader's
 *         error.
 */
t_error		scanner_read_input(t_scanner *state);

/**
 * @ingroup scanner
 * @brief Expands a word token's alias and re-lexes from the expansion.
 *
 * When @p token expands, pushes the expansion as a new input on the lexer
 * stack and re-runs the lexer so the next token comes from the expanded text;
 * otherwise leaves @p token unchanged.
 *
 * @param state Pointer to the scanner state (borrowed).
 * @param token Word token to expand and replace (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error		scanner_alias_expand(t_scanner *state, t_token *token);

#endif

```

./srcs/3_builder/1_lr_machine/1_hooks/hook_3.c
```c
#include "parser_type.h"
#include "scanner.h"
#include "cst.h"
#include <stdlib.h>

static t_error	get_heredoc_delim(t_parser *parser, t_parser_stack_item *rhs, char **dst_str)
{
	t_token	*token;

	token = &((t_token *)parser->tokens.data)[rhs->tokens_start_id];
	*dst_str = buff_get_string(&token->value);
	if (!*dst_str)
		return (error_sys());
	return (error(ERR_NO));
}

# include <stdio.h>	// DEBUG
# include "logs.h"	// DEBUG
t_error	hook_3(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs)
{
	char			*path;	// TODO: remove
	t_buff			*path_buff;
	char			*delim;
	t_heredoc_mode	mode;
	t_error			err;

	if (len != 2)
		return (error_print(error(ERR_HOOK_INVALID_RHS_LEN), __func__, NULL, "expected 2 received %i", (int)len));
	err = get_heredoc_delim(parser, &rhs[1], &delim);
	if (err.type != ERR_NO)
		return (error_print(err, __func__, "unable to get heredoc delimiter", NULL, NULL));
	if (rhs[0].symbol == SYM_DLESSDASH)
		mode = HEREDOC_MODE_TAB_STRIP;
	else
		mode = HEREDOC_MODE_NORMAL;
	path = NULL;
	fprintf(stderr, "[PARSER] %sscanner_report_io_here(%p, %s%s%s, %i)%s\n", YELLOW, &path, BLUE, delim, YELLOW, (int)mode, NC);
	err = scanner_report_io_here(&path, delim, mode);
	if (err.type == ERR_NO)
	{
		path_buff = malloc(sizeof(t_buff));
		if (!path_buff)
			return (free(path), error_print(err, __func__, "unable to malloc heredoc path buff", NULL, NULL));
		if (!buff_init(path_buff, 0, path, -1))
			return (free(path), error_print(err, __func__, "unable to init heredoc path buff", NULL, NULL));
		cst_node_set_data(lhs->cst_node, path_buff, buff_free_void);
		parser->must_read_heredoc = true;
	}
	free(delim);
	return (err);
}

```

./srcs/3_builder/1_lr_machine/1_hooks/hook_9.c
```c
#include "parser_type.h"
#include <stdlib.h>

static inline void	update_parser_bools(t_parser *parser)
{
	parser->assignment_disabled = parser->function_body_depth > 0;
	parser->expansion_disabled = parser->function_body_depth > 0;
}

# include <stdio.h>	// DEBUG
# include "logs.h"	// DEBUG
t_error	hook_9_increment(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs)
{
	(void)rhs;
	(void)len;
	(void)lhs;
	parser->function_body_depth++;
	update_parser_bools(parser);
	fprintf(stderr, "[PARSER] %sfunction_body_depth = %zu%s\n", YELLOW, parser->function_body_depth, NC);
	return (error(ERR_NO));
}

t_error	hook_9_decrement(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs)
{
	(void)rhs;
	(void)len;
	(void)lhs;
	if (parser->function_body_depth == 0)
		return (error_print(
			error(ERR_PARSER_INVALID_STATE),
			"parser",
			"function_body_depth is already 0",
			NULL,
			NULL));
	parser->function_body_depth--;
	update_parser_bools(parser);
	fprintf(stderr, "[PARSER] %sfunction_body_depth = %zu%s\n", YELLOW, parser->function_body_depth, NC);
	return (error(ERR_NO));
}

```

./srcs/3_builder/1_lr_machine/1_hooks/hook_fname.c
```c
#include "parser_type.h"
#include "token.h"
#include "utils.h"
#include "hooks.h"
#include <stdlib.h>

# include "debug.h"	// DEBUG
static t_error	check_name(const char *hook_name, t_token *token)
{
	char		*token_value;
	bool		valid_name;
	t_error		err;

	err = error(ERR_NO);
	token_value = buff_get_string(&token->value);
	if (!token_value)
		return (error_print(error_sys(), "parser", hook_name,
			"unable to get token value", NULL, NULL));
	valid_name = name_is_valid(token_value);
	fprintf(stderr, "[PARSER] %sfunction_name_is_valid = %s%s\n", YELLOW, bool_to_string(valid_name), NC);
	if (!valid_name)
	{
		(void)error_print(error(ERR_PARSER_INVALID_FUNCTION_NAME),
			"parser", NULL, "%s", token_value);
		err = error(ERR_INVALID_SYNTAX);
	}
	free(token_value);
	return (err);
}

t_error	hook_fname(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs)
{
	t_token		*token;
	t_error		err;

	if (len != 1)
		return (error_print(error(ERR_HOOK_INVALID_RHS_LEN), __func__,
			NULL, "expected 1 received %i", (int)len));
	token = &((t_token *)parser->tokens.data)[rhs[0].tokens_start_id];
	err = check_name(__func__, token);
	if (err.type != ERR_NO)
		return (err);
	return (hook_9_increment(parser, rhs, len, lhs));
}

```

./srcs/3_builder/1_lr_machine/1_hooks/hook_store_cst.c
```c
#include "parser_type.h"
#include "parser.h"

t_error	hook_store_cst(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs)
{
	(void)rhs;
	(void)len;
	parser_store_cst(parser, lhs);
	return (error(ERR_NO));
}

```

./srcs/3_builder/1_lr_machine/1_hooks/hooks_type.h
```c
#ifndef HOOKS_TYPE_H
# define HOOKS_TYPE_H

# include "error.h"
# include <stddef.h>

typedef struct s_parser_stack_item	t_parser_stack_item;
typedef struct s_parser				t_parser;
typedef struct s_cst_node			t_cst_node;

typedef t_error	(*t_reduce_hook)(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs);

#endif

```

./srcs/3_builder/1_lr_machine/1_hooks/hooks.h
```c
#ifndef HOOKS_H
# define HOOKS_H

# include "error.h"
# include "parser_stack_type.h"

// Triggered on SYM_io_here reduction
t_error	hook_3(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs);

// Triggered by hook_fname()
t_error	hook_9_increment(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs);

// Triggered on SYM_function_body reduction
t_error	hook_9_decrement(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs);

/*
* Triggered on SYM_fname reduction
* Rule 9 starts here
* Although function_body is parsed later, only '(' ')' and linebreak can appear
* before it, so disabling assignment and expansion now is safe.
*/
t_error	hook_fname(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs);

t_error	hook_store_cst(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs);

#endif

```

./srcs/3_builder/1_lr_machine/2_symbols/1_terminal.c
```c
#include "symbols_type.h"
#include <stdbool.h>

bool	symbol_is_terminal(t_symbol symbol)
{
	return (symbol <= SYM_TERMINAL_MAX);
}

bool	symbol_is_non_terminal(t_symbol symbol)
{
	return (symbol >= SYM_NON_TERMINAL_MIN && symbol <= SYM_NON_TERMINAL_MAX);
}

```

./srcs/3_builder/1_lr_machine/2_symbols/2_nullable.c
```c
#include "lr_machine_type.h"

bool	symbol_is_nullable(t_lr_machine *machine, t_symbol symbol)
{
	return (machine->nullable_symbols[symbol]);
}

bool	symbols_are_nullable(t_lr_machine *machine, t_symbol *symbols, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (!symbol_is_nullable(machine, symbols[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	build_nullable_symbol(t_lr_machine *machine, t_symbol symbol, bool *did_add)
{
	size_t	i;
	t_rule	rule;

	i = 0;
	while (i < RULE_COUNT)
	{
		rule = machine->rules[i++];
		if (rule.lhs != symbol)
			continue ;
		if (rule.rhs_len == 0)
		{
			machine->nullable_symbols[symbol] = true;
			*did_add = true;
		}
		if (symbols_are_nullable(machine, rule.rhs, rule.rhs_len))
		{
			machine->nullable_symbols[symbol] = true;
			*did_add = true;
		}
	}
}

void	symbols_build_nullables_table(t_lr_machine *machine)
{
	t_symbol	symbol;
	bool		did_add;

	symbol = 0;
	while (symbol < SYM_COUNT)
		machine->nullable_symbols[symbol++] = false;
	did_add = true;
	while (did_add)
	{
		did_add = false;
		symbol = SYM_NON_TERMINAL_MIN;
		while (symbol <= SYM_NON_TERMINAL_MAX)
		{
			if (machine->nullable_symbols[symbol] == false)
				build_nullable_symbol(machine, symbol, &did_add);
			symbol++;
		}
	}
}

```

./srcs/3_builder/1_lr_machine/2_symbols/3_reserved.c
```c
#include "symbols_type.h"
#include <stdbool.h>

bool	symbol_is_reserved_word(t_symbol symbol)
{
	return (symbol >= SYM_RESERVED_MIN && symbol <= SYM_RESERVED_MAX);
}

```

./srcs/3_builder/1_lr_machine/2_symbols/symbols_type.h
```c
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

```

./srcs/3_builder/1_lr_machine/2_symbols/symbols.h
```c
#ifndef SYMBOLS_H
# define SYMBOLS_H

# include "lr_machine_type.h"

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup symbols_pub Symbols module public API
 *  @brief Public helpers used to classify grammar symbols and compute
 *         symbol nullability information.
 *  @warning This module must only be called by its parent module 
 *           @ref lr_machine and its sibling modules @ref hooks, @ref rules,
 *           @ref first, @ref rule_state, @ref lr_state, @ref transition,
 *           @ref goto, @ref action. All other modules must call 
 *           @ref lr_machine instead of calling this module directly.
 *
 *  This module provides predicates on @ref t_symbol values and builds the
 *  nullable-symbol table stored in @ref t_lr_machine.
 */

/* ************************************************************************* */
/*                                SYMBOLS (PUB)                              */
/* ************************************************************************* */

// TODO: doc
bool	symbol_is_reserved_word(t_symbol symbol);

/**
 * @ingroup symbols_pub
 * @brief Checks whether a symbol belongs to the non-terminal range.
 *
 * This function classifies @p symbol by testing whether it lies between
 * @ref SYM_NON_TERMINAL_MIN and @ref SYM_NON_TERMINAL_MAX, inclusive.
 *
 * @note This function does not access any external state.
 *
 * @warning Caller should pass a valid @ref t_symbol value.
 *
 * @param symbol Symbol to classify.
 * @return true if @p symbol is a non-terminal symbol, false otherwise.
 */
bool	symbol_is_non_terminal(t_symbol symbol);

/**
 * @ingroup symbols_pub
 * @brief Reports whether a symbol is currently marked as nullable.
 *
 * This function reads the nullable-symbol table stored in @p machine and
 * returns the value associated with @p symbol.
 *
 * @note This function does not validate whether the nullable table was
 *       previously computed by @ref symbols_build_nullables_table.
 *
 * @warning @p machine must NOT be NULL.
 * @warning @p symbol must be a valid index in the range `[0, @ref SYM_COUNT)`.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine holding the nullable-symbol table (borrowed, must
 *                NOT be NULL).
 * @param symbol Symbol whose nullability must be queried.
 * @return true if @p symbol is marked nullable in @p machine, false otherwise.
 */
bool	symbol_is_nullable(t_lr_machine *machine, t_symbol symbol);

/**
 * @ingroup symbols_pub
 * @brief Checks whether a symbol belongs to the terminal range.
 *
 * This function classifies @p symbol by testing whether it is less than or
 * equal to @ref SYM_TERMINAL_MAX.
 *
 * @note This function does not access any external state.
 *
 * @warning Caller should pass a valid @ref t_symbol value.
 *
 * @param symbol Symbol to classify.
 * @return true if @p symbol is a terminal symbol, false otherwise.
 */
bool	symbol_is_terminal(t_symbol symbol);

/**
 * @ingroup symbols_pub
 * @brief Reports whether all symbols in a sequence are nullable.
 *
 * This function returns true only if every symbol in the sequence referenced
 * by @p symbols is reported as nullable by @ref symbol_is_nullable.
 *
 * @note An empty sequence is considered nullable. Therefore, this function
 *       returns true when @p count is zero.
 * @note When @p count is zero, @p symbols is not accessed and can be NULL.
 *
 * @warning @p machine must NOT be NULL.
 * @warning When @p count is greater than zero, @p symbols must NOT be NULL.
 * @warning Each symbol in the sequence must be a valid index in the range
 *          `[0, @ref SYM_COUNT)`.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine holding the nullable-symbol table (borrowed, must
 *                NOT be NULL).
 * @param symbols Sequence of symbols to test (borrowed, can be NULL only when
 *                @p count is zero).
 * @param count Number of symbols in @p symbols.
 * @return true if all symbols in the sequence are nullable, false otherwise.
 */
bool	symbols_are_nullable(t_lr_machine *machine, t_symbol *symbols, size_t count);

/**
 * @ingroup symbols_pub
 * @brief Builds the nullable-symbol table of an LR machine.
 *
 * This function resets every entry of @p machine->nullable_symbols, then
 * computes a fixed point over the grammar stored in @p machine->rules.
 * A non-terminal symbol is marked nullable when at least one rule with that
 * symbol as left-hand side has an empty right-hand side or a right-hand side
 * composed entirely of nullable symbols.
 *
 * @note This function updates only the `nullable_symbols` table stored in
 *       @p machine.
 * @note The computation iterates until no new nullable symbol is discovered.
 *
 * @warning @p machine must NOT be NULL.
 * @warning @p machine->rules must already contain a valid grammar, typically
 *          populated by @ref rules_build.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine whose nullable-symbol table must be rebuilt
 *                (borrowed, must NOT be NULL).
 */
void	symbols_build_nullables_table(t_lr_machine *machine);

#endif

```

./srcs/3_builder/1_lr_machine/3_rules/rules__main.c
```c
#include "rules__type.h"
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

./srcs/3_builder/1_lr_machine/3_rules/rules__priv.h
```c
#ifndef RULES__PRIV_H
# define RULES__PRIV_H

# include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules__pub.h
```c
#ifndef RULES__PUB_H
# define RULES__PUB_H

# include "rules__type.h"

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup rules_pub Rules module public API
 *  @brief Public functions used to initialize and build the grammar rule table.
 *
 *  This module populates the parser grammar stored as an array of @ref t_rule
 *  entries.
 */

/* ************************************************************************* */
/*                                 RULES (PUB)                               */
/* ************************************************************************* */

/**
 * @ingroup rules_pub
 * @brief Builds the full grammar rule table.
 *
 * Fills the rule array referenced by @p rules with all grammar productions
 * supported by the LR machine, including production left-hand sides,
 * right-hand sides, right-hand-side lengths, and optional semantic hooks.
 *
 * @note This function writes entries identified by the various @ref t_rule_id
 *       constants.
 * @note The storage pointed to by @p rules remains owned by the caller.
 * @note The built table is intended to contain @ref RULE_COUNT entries.
 *
 * @warning @p rules must NOT be NULL.
 * @warning @p rules must reference writable storage large enough to contain
 *          exactly @ref RULE_COUNT @ref t_rule entries.
 * @warning This function does not perform any parameter validation.
 * @warning This function assumes the caller provides a rule table intended for
 *          this grammar layout.
 *
 * @param rules Rule table to populate (borrowed, must NOT be NULL).
 */
void	rules_build(t_rule *rules);

/**
 * @ingroup rules_pub
 * @brief Initializes the grammar rule table to an empty state.
 *
 * Sets the whole rule table referenced by @p rules to zero over
 * @ref RULE_COUNT entries.
 *
 * @note This clears every field of each @ref t_rule entry before the table is
 *       populated by @ref rules_build.
 * @note The storage pointed to by @p rules remains owned by the caller.
 *
 * @warning @p rules must NOT be NULL.
 * @warning @p rules must reference writable storage large enough to contain
 *          exactly @ref RULE_COUNT @ref t_rule entries.
 * @warning This function does not perform any parameter validation.
 *
 * @param rules Rule table to initialize (borrowed, must NOT be NULL).
 */
void	rules_init(t_rule *rules);

#endif

```

./srcs/3_builder/1_lr_machine/3_rules/rules__type.h
```c
#ifndef RULES__TYPE_H
# define RULES__TYPE_H

# define RULE_RHS_CAP	7

# include "symbols_type.h"
# include "hooks_type.h"

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
	RULE_FUNCTION_BODY_1,			// function_body		-> compound_command (apply rule 9)
	RULE_FUNCTION_BODY_2,			// function_body		-> compound_command redirect_list (apply rule 9)
	RULE_FUNCTION_DEFINITION_1,		// function_definition	-> fname '(' ')' linebreak function_body
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
	RULE_COUNT,						// rule_count			-> <sentinel>
	RULE_NONE						// rule_none			-> <sentinel>
}	t_rule_id;

typedef struct s_rule
{
	t_symbol		lhs;
	t_symbol		rhs[RULE_RHS_CAP];
	size_t			rhs_len;
	t_reduce_hook	hook;
}	t_rule;

#endif

```

./srcs/3_builder/1_lr_machine/3_rules/rules_and_or.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_brace_group.c
```c
#include "rules__type.h"


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

./srcs/3_builder/1_lr_machine/3_rules/rules_case_clause.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_case_item_ns.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_case_item.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_case_list_ns.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_case_list.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_cmd_name.c
```c
#include "rules__type.h"

/*
cmd_name         : WORD (apply rule 7a)
                 ;
*/
void	rules_build_cmd_name(t_rule *rules)
{
	rules[RULE_CMD_NAME_1].lhs = SYM_cmd_name;
	rules[RULE_CMD_NAME_1].rhs[0] = SYM_WORD;
	rules[RULE_CMD_NAME_1].rhs_len = 1;
}

```

./srcs/3_builder/1_lr_machine/3_rules/rules_cmd_prefix.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_cmd_suffix.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_cmd_word.c
```c
#include "rules__type.h"

/*
cmd_word         : WORD (apply rule 7b)
                 ;
*/
void	rules_build_cmd_word(t_rule *rules)
{
	rules[RULE_CMD_WORD_1].lhs = SYM_cmd_word;
	rules[RULE_CMD_WORD_1].rhs[0] = SYM_WORD;
	rules[RULE_CMD_WORD_1].rhs_len = 1;
}

```

./srcs/3_builder/1_lr_machine/3_rules/rules_command.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_complete_command.c
```c
#include "rules__type.h"
#include "hooks.h"

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
	rules[RULE_COMPLETE_COMMAND_1].hook = hook_store_cst;
}

// complete_command -> list
static void	rules_build_complete_command_2(t_rule *rules)
{
	rules[RULE_COMPLETE_COMMAND_2].lhs = SYM_complete_command;
	rules[RULE_COMPLETE_COMMAND_2].rhs[0] = SYM_list;
	rules[RULE_COMPLETE_COMMAND_2].rhs_len = 1;
	rules[RULE_COMPLETE_COMMAND_2].hook = hook_store_cst;
}

```

./srcs/3_builder/1_lr_machine/3_rules/rules_complete_commands.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_compound_command.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_compound_list.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_do_group.c
```c
#include "rules__type.h"

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
}

```

./srcs/3_builder/1_lr_machine/3_rules/rules_else_part.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_filename.c
```c
#include "rules__type.h"

/*
filename         : WORD (apply rule 2)
                 ;
*/
void	rules_build_filename(t_rule *rules)
{
	rules[RULE_FILENAME_1].lhs = SYM_filename;
	rules[RULE_FILENAME_1].rhs[0] = SYM_WORD;
	rules[RULE_FILENAME_1].rhs_len = 1;
}

```

./srcs/3_builder/1_lr_machine/3_rules/rules_fname.c
```c
#include "rules__type.h"
#include "hooks.h"

/*
fname            : NAME (apply rule 8)
                 ;
⚠️ Bash-like parser adaptation: function name is parsed as WORD,
	then validated as a POSIX name during reduction.
	(see hook_fname())
*/
void	rules_build_fname(t_rule *rules)
{
	rules[RULE_FNAME_1].lhs = SYM_fname;
	rules[RULE_FNAME_1].rhs[0] = SYM_WORD;
	rules[RULE_FNAME_1].rhs_len = 1;
	rules[RULE_FNAME_1].hook = hook_fname;
}

```

./srcs/3_builder/1_lr_machine/3_rules/rules_for_clause.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_function_body.c
```c
#include "rules__type.h"
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
	rules[RULE_FUNCTION_BODY_1].hook = hook_9_decrement;
}

// function_body -> compound_command redirect_list (apply rule 9)
static void	rules_build_function_body_2(t_rule *rules)
{
	rules[RULE_FUNCTION_BODY_2].lhs = SYM_function_body;
	rules[RULE_FUNCTION_BODY_2].rhs[0] = SYM_compound_command;
	rules[RULE_FUNCTION_BODY_2].rhs[1] = SYM_redirect_list;
	rules[RULE_FUNCTION_BODY_2].rhs_len = 2;
	rules[RULE_FUNCTION_BODY_2].hook = hook_9_decrement;
}

```

./srcs/3_builder/1_lr_machine/3_rules/rules_function_definition.c
```c
#include "rules__type.h"

/*
Original rule:
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

./srcs/3_builder/1_lr_machine/3_rules/rules_here_end.c
```c
#include "rules__type.h"

/*
here_end         : WORD (apply rule 3)
                 ;
*/
void	rules_build_here_end(t_rule *rules)
{
	rules[RULE_HERE_END_1].lhs = SYM_here_end;
	rules[RULE_HERE_END_1].rhs[0] = SYM_WORD;
	rules[RULE_HERE_END_1].rhs_len = 1;
}

```

./srcs/3_builder/1_lr_machine/3_rules/rules_if_clause.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_in.c
```c
#include "rules__type.h"

/*
in               : In (apply rule 6)
                 ;
*/
void	rules_build_in(t_rule *rules)
{
	rules[RULE_IN_1].lhs = SYM_in;
	rules[RULE_IN_1].rhs[0] = SYM_In;
	rules[RULE_IN_1].rhs_len = 1;
}

```

./srcs/3_builder/1_lr_machine/3_rules/rules_io_file.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_io_here.c
```c
#include "rules__type.h"
#include "hooks.h"

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
	rules[RULE_IO_HERE_1].hook = hook_3;
}

// io_here -> DLESSDASH here_end
static void	rules_build_io_here_2(t_rule *rules)
{
	rules[RULE_IO_HERE_2].lhs = SYM_io_here;
	rules[RULE_IO_HERE_2].rhs[0] = SYM_DLESSDASH;
	rules[RULE_IO_HERE_2].rhs[1] = SYM_here_end;
	rules[RULE_IO_HERE_2].rhs_len = 2;
	rules[RULE_IO_HERE_2].hook = hook_3;
}

```

./srcs/3_builder/1_lr_machine/3_rules/rules_io_redirect.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_linebreak.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_list.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_name.c
```c
#include "rules__type.h"

/*
name             : NAME (apply rule 5)
                 ;
*/
void	rules_build_name(t_rule *rules)
{
	rules[RULE_NAME_1].lhs = SYM_name;
	rules[RULE_NAME_1].rhs[0] = SYM_NAME;
	rules[RULE_NAME_1].rhs_len = 1;
}

```

./srcs/3_builder/1_lr_machine/3_rules/rules_newline_list.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_pattern_list.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_pipe_sequence.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_pipeline.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_program.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_redirect_list.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_separator_op.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_separator.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_sequential_sep.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_simple_command.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_start.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_subshell.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_term.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_until_clause.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_while_clause.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/3_rules/rules_wordlist.c
```c
#include "rules__type.h"

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

./srcs/3_builder/1_lr_machine/4_first/1_add.c
```c
#include "symbols_type.h"
#include <stdbool.h>

void	first_add(bool *dst, bool *did_add)
{
	if (did_add && *dst == false)
		*did_add = true;
	*dst = true;
}

void	first_add_list(bool *dst, const bool *src, bool *did_add)
{
	t_symbol	terminal;

	terminal = 0;
	while (terminal <= SYM_TERMINAL_MAX)
	{
		if (src[terminal] == true)
			first_add(&dst[terminal], did_add);
		terminal++;
	}
}

```

./srcs/3_builder/1_lr_machine/4_first/2_build.c
```c
#include "first_priv.h"
#include "symbols.h"

static void	first_set_default_and_terminals(t_lr_machine *machine)
{
	t_symbol	symbol;
	t_symbol	terminal;

	symbol = 0;
	while (symbol < SYM_COUNT)
	{
		terminal = 0;
		while (terminal <= SYM_TERMINAL_MAX)
		{
			machine->first[symbol][terminal] = false;
			terminal++;
		}
		if (symbol <= SYM_TERMINAL_MAX)
			machine->first[symbol][symbol] = true;
		symbol++;
	}
}

static void	first_build_from_rule(t_lr_machine *machine, t_rule rule, bool *did_add)
{
	size_t		pos;
	t_symbol	symbol;

	pos = 0;
	while (pos < rule.rhs_len)
	{
		symbol = rule.rhs[pos++];
		if (symbol_is_terminal(symbol))
		{
			first_add(&machine->first[rule.lhs][symbol], did_add);
			return ;
		}
		first_add_list(
			machine->first[rule.lhs],
			machine->first[symbol],
			did_add);
		if (!symbol_is_nullable(machine, symbol))
			return ;
	}
}

void	first_build_table(t_lr_machine *machine)
{
	size_t		i;
	t_rule		rule;
	bool		did_add;

	first_set_default_and_terminals(machine);
	did_add = true;
	while (did_add)
	{
		did_add = false;
		i = 0;
		while (i < RULE_COUNT)
		{
			rule = machine->rules[i];
			first_build_from_rule(machine, rule, &did_add);
			i++;
		}
	}
}

```

./srcs/3_builder/1_lr_machine/4_first/3_first.c
```c
#include "first.h"
#include "first_priv.h"
#include "symbols.h"

static inline void	reset_result(bool *result)
{
	size_t	i;

	i = 0;
	while (i <= SYM_TERMINAL_MAX)
		result[i++] = false;
}

void	first(t_lr_machine *machine, t_first_param *param)
{
	size_t		pos;
	t_symbol	symbol;

	reset_result(param->result);
	pos = 0;
	while (pos < param->count)
	{
		symbol = param->symbols[pos++];
		if (symbol_is_terminal(symbol))
		{
			param->result[symbol] = true;
			return ;
		}
		first_add_list(
			param->result,
			machine->first[symbol],
			NULL);
		if (!symbol_is_nullable(machine, symbol))
			return ;
	}
	if (param->has_lookahead)
		param->result[param->lookahead] = true;
}

```

./srcs/3_builder/1_lr_machine/4_first/first_priv.h
```c
#ifndef FIRST_PRIV_H
# define FIRST_PRIV_H

# include <stdbool.h>

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup first_priv First module internal API
 *  @brief Internal helpers used to build and combine FIRST sets.
 *  @warning These functions must only be called by the @ref first module
 *           itself.
 *
 *  This private API is intended for the implementation of the @ref first
 *  module.
 */

/* ************************************************************************* */
/*                                  PRIVATE                                  */
/* ************************************************************************* */

/**
 * @ingroup first_priv
 * @brief Marks a terminal-entry slot as present in a FIRST set.
 *
 * This helper sets the boolean entry pointed to by @p dst to true.
 * When @p did_add is not NULL, it is also set to true if the entry pointed to
 * by @p dst was false before this call.
 *
 * @note This function never clears the flag pointed to by @p did_add.
 *
 * @warning @p dst must NOT be NULL.
 * @warning When @p did_add is not NULL, it must point to writable storage.
 * @warning This function performs no parameter validation.
 *
 * @param dst Destination FIRST-set entry to mark as present (borrowed, must
 *            NOT be NULL).
 * @param did_add Optional accumulator flag updated when a new entry is added
 *                (borrowed, can be NULL).
 */
void	first_add(bool *dst, bool *did_add);

/**
 * @ingroup first_priv
 * @brief Merges terminal entries from one FIRST set into another.
 *
 * For each terminal index in the range `[0, @ref SYM_TERMINAL_MAX]`, this
 * helper checks whether the corresponding entry in @p src is true and, if so,
 * marks the matching entry in @p dst by calling @ref first_add.
 *
 * @note When @p did_add is not NULL, it is used as an accumulator flag across
 *       all copied entries.
 *
 * @warning @p dst and @p src must NOT be NULL.
 * @warning @p dst and @p src must each reference an array of at least
 *          `@ref SYM_TERMINAL_MAX + 1` boolean entries.
 * @warning This function performs no parameter validation.
 *
 * @param dst Destination FIRST-set array receiving terminal entries
 *            (borrowed, must NOT be NULL).
 * @param src Source FIRST-set array to read from (borrowed, must NOT be NULL).
 * @param did_add Optional accumulator flag updated when at least one new entry
 *                is added to @p dst (borrowed, can be NULL).
 */
void	first_add_list(bool *dst, const bool *src, bool *did_add);

#endif

```

./srcs/3_builder/1_lr_machine/4_first/first.h
```c
#ifndef FIRST_H
# define FIRST_H

# include "lr_machine_type.h"

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

/**
 * @struct s_first_param
 * @brief Parameters and output storage used by @ref first.
 *
 * @var s_first_param::symbols Sequence whose FIRST set must be computed
 *      (borrowed, can be NULL only when @ref s_first_param::count is zero).
 * @var s_first_param::count Number of symbols stored in
 *      @ref s_first_param::symbols.
 * @var s_first_param::lookahead Terminal symbol appended conceptually after
 *      the sequence when @ref s_first_param::has_lookahead is true.
 * @var s_first_param::has_lookahead Whether @ref s_first_param::lookahead must
 *      be added when the whole sequence is nullable.
 * @var s_first_param::result Output FIRST-set buffer indexed by terminal
 *      symbol. This array is overwritten by @ref first.
 */
typedef struct s_first_param
{
	t_symbol	*symbols;
	size_t		count;
	t_symbol	lookahead;
	bool		has_lookahead;
	bool		result[SYM_TERMINAL_MAX + 1];
}	t_first_param;

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup first_pub First module public API
 *  @brief Public functions used to build and query FIRST sets.
 *  @warning This module must only be called by its parent module
 *           @ref lr_machine and its sibling modules @ref hooks, @ref rules,
 *           @ref symbols, @ref rule_state, @ref lr_state, @ref transition,
 *           @ref goto, @ref action. All other modules must call @ref lr_machine
 *           instead of calling this module directly.
 *
 *  This module builds the FIRST table stored in @ref t_lr_machine and computes
 *  FIRST sets for symbol sequences.
 */

/* ************************************************************************* */
/*                                 FIRST (PUB)                               */
/* ************************************************************************* */

/**
 * @ingroup first_pub
 * @brief Computes the FIRST set of a symbol sequence.
 *
 * This function clears @p param->result, then computes the FIRST set of the
 * sequence described by @p param->symbols and @p param->count using the
 * precomputed FIRST and nullable-symbol tables stored in @p machine.
 *
 * If the first non-nullable symbol in the sequence is terminal, only that
 * terminal is added to the result. If it is non-terminal, its FIRST set is
 * merged into the result. This continues until a non-nullable symbol is
 * encountered or the sequence is exhausted. When the whole sequence is
 * nullable and @p param->has_lookahead is true, @p param->lookahead is also
 * added to the result.
 *
 * @note @p param->result is always reset before the computation starts.
 * @note When @p param->count is zero, @p param->symbols is not accessed and
 *       can be NULL.
 * @note This function stores only terminal membership inside
 *       @p param->result. Nullability itself must be queried separately
 *       through @ref symbol_is_nullable.
 *
 * @warning @p machine and @p param must NOT be NULL.
 * @warning @ref first_build_table and @ref symbols_build_nullables_table must
 *          already have been called successfully on @p machine before calling
 *          this function.
 * @warning Every symbol stored in @p param->symbols must be a valid
 *          @ref t_symbol value in the range `[0, @ref SYM_COUNT)`.
 * @warning When @p param->has_lookahead is true, @p param->lookahead must be
 *          a terminal symbol in the range `[0, @ref SYM_TERMINAL_MAX]`.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine providing the precomputed FIRST and nullable
 *                tables (borrowed, must NOT be NULL).
 * @param param Input parameters and output buffer used for the computation
 *              (borrowed, must NOT be NULL).
 */
void	first(t_lr_machine *machine, t_first_param *param);

/**
 * @ingroup first_pub
 * @brief Builds the FIRST table stored in an LR machine.
 *
 * This function resets the whole `first` table stored in @p machine, marks
 * each terminal symbol as belonging to its own FIRST set, then computes a
 * fixed point over the grammar rules stored in @p machine->rules.
 *
 * For each rule, the right-hand side is scanned from left to right. Terminal
 * symbols are added directly. Non-terminal FIRST sets are merged into the
 * left-hand side FIRST set, and the scan continues only while the current
 * symbol is nullable according to @ref symbol_is_nullable.
 *
 * @note This function updates only the `first` table stored in @p machine.
 * @note FIRST sets for terminal symbols are initialized so that each terminal
 *       contains itself.
 * @note This function stores only terminal membership. Nullable-symbol
 *       information remains stored separately in `nullable_symbols`.
 *
 * @warning @p machine must NOT be NULL.
 * @warning @p machine->rules must already contain a valid grammar, typically
 *          populated by @ref rules_build.
 * @warning The nullable-symbol table must already have been built with
 *          @ref symbols_build_nullables_table before calling this function.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine whose FIRST table must be rebuilt (borrowed, must
 *                NOT be NULL).
 */
void	first_build_table(t_lr_machine *machine);

#endif

```

./srcs/3_builder/1_lr_machine/5_rule_state/rule_state_type.h
```c
#ifndef RULE_STATE_TYPE_H
# define RULE_STATE_TYPE_H

# include "symbols_type.h"
# include <stddef.h>

/*
rule_state		aka item in LR parsing theory
rule_state.pos	aka item.dot in LR parsing theory
*/
typedef struct s_rule_state
{
	size_t		rule_id;
	size_t		pos;
	t_symbol	lookahead;
}	t_rule_state;

#endif

```

./srcs/3_builder/1_lr_machine/5_rule_state/rule_state.c
```c
#include "rule_state_type.h"
#include "rules__type.h"

bool	rule_state_equal(t_rule_state a, t_rule_state b)
{
	if (a.rule_id != b.rule_id)
		return (false);
	if (a.pos != b.pos)
		return (false);
	if (a.lookahead != b.lookahead)
		return (false);
	return (true);
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

./srcs/3_builder/1_lr_machine/5_rule_state/rule_state.h
```c
#ifndef RULE_STATE_H
# define RULE_STATE_H

# include "rules__type.h"
# include "rule_state_type.h"

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup rule_state_pub Rule state module public API
 *  @brief Public functions used to inspect and compare @ref t_rule_state
 *         values.
 *  @warning This module must only be called by its parent module
 *           @ref lr_machine and its sibling modules @ref hooks, @ref rules,
 *           @ref symbols, @ref first, @ref lr_state, @ref transition,
 *           @ref goto, @ref action. All other modules must call
 *           @ref lr_machine instead of calling this module directly.
 *
 *  This module provides helpers for comparing rule states (aka LR items) 
 *  and querying their progression within a rule.
 */

/* ************************************************************************* */
/*                              RULE_STATE (PUB)                             */
/* ************************************************************************* */

/**
 * @ingroup rule_state_pub
 * @brief Compares two rule states for exact equality.
 *
 * Two @ref t_rule_state values are considered equal when their `rule_id`,
 * `pos`, and `lookahead` fields are all equal.
 *
 * @note This function does not access external state.
 *
 * @param a First rule state to compare.
 * @param b Second rule state to compare.
 * @return true if @p a and @p b are equal, false otherwise.
 */
bool		rule_state_equal(t_rule_state a, t_rule_state b);

/**
 * @ingroup rule_state_pub
 * @brief Reports whether a rule state has reached the end of its rule.
 *
 * A rule state is considered complete when @p rule_state.pos is greater than
 * or equal to the right-hand-side length of the rule designated by
 * @p rule_state.rule_id in @p rules.
 *
 * @warning @p rules must NOT be NULL.
 * @warning @p rule_state.rule_id must designate a valid rule index in the
 *          range `[0, @ref RULE_COUNT)`.
 * @warning This function performs no parameter validation.
 *
 * @param rules Rule table to inspect (borrowed, must NOT be NULL).
 * @param rule_state Rule state to test.
 * @return true if @p rule_state is complete, false otherwise.
 */
bool		rule_state_is_complete(t_rule *rules, t_rule_state rule_state);

/**
 * @ingroup rule_state_pub
 * @brief Returns the next symbol expected by a rule state.
 *
 * When @p rule_state is not complete, this function returns the symbol located
 * at position @p rule_state.pos in the right-hand side of the rule designated
 * by @p rule_state.rule_id in @p rules.
 *
 * @note When @p rule_state is complete, this function returns @ref SYM_error.
 *
 * @warning @p rules must NOT be NULL.
 * @warning @p rule_state.rule_id must designate a valid rule index in the
 *          range `[0, @ref RULE_COUNT)`.
 * @warning This function performs no parameter validation.
 *
 * @param rules Rule table to inspect (borrowed, must NOT be NULL).
 * @param rule_state Rule state to inspect.
 * @return The next expected symbol, or @ref SYM_error if @p rule_state is
 *         complete.
 */
t_symbol	rule_state_next_symbol(t_rule *rules, t_rule_state rule_state);

#endif

```

./srcs/3_builder/1_lr_machine/6_lr_state/1_life_cycle.c
```c
#include "rule_state_type.h"
#include "lr_state_type.h"
#include <stdlib.h>

void	lr_state_init(t_lr_state *lr_state)
{
	vector_init(lr_state, sizeof(t_rule_state), 0);
}

void	lr_state_table_init(t_lr_state *lr_states)
{
	vector_init(lr_states, sizeof(t_lr_state), 0);
}

void	lr_state_free(void *lr_state)
{
	vector_free((t_lr_state *)lr_state, NULL);
}

void	lr_state_table_free(t_lr_state *lr_states)
{
	vector_free(lr_states, lr_state_free);
}

```

./srcs/3_builder/1_lr_machine/6_lr_state/2_ops.c
```c
#include "rule_state_type.h"
#include "lr_state_type.h"
#include "rule_state.h"

static bool	lr_state_contains_rule_state(
	t_lr_state *lr_state,
	t_rule_state rule_state)
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

t_error	lr_state_add_rule_state(
	t_lr_state *lr_state,
	t_rule_state rule_state,
	bool *did_add)
{
	if (lr_state_contains_rule_state(lr_state, rule_state))
		return (error(ERR_NO));
	if (!vector_push(lr_state, &rule_state))
		return (error_sys());
	if (did_add)
		*did_add = true;
	return (error(ERR_NO));
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

```

./srcs/3_builder/1_lr_machine/6_lr_state/3_registry.c
```c
#include "lr_state.h"

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

t_error	lr_state_add(t_vector *lr_states, t_lr_state *lr_state, bool *did_add)
{
	if (lr_state_find_id(lr_states, lr_state, NULL))
		return (error(ERR_NO));
	if (!vector_push(lr_states, lr_state))
		return (error_sys());
	if (did_add)
		*did_add = true;
	return (error(ERR_NO));
}

```

./srcs/3_builder/1_lr_machine/6_lr_state/4_core.c
```c
#include "lr_state.h"
#include "rule_state.h"
#include "symbols.h"
#include "first.h"

static void	compute_first(
	t_lr_machine *machine,
	t_first_param *param,
	t_rule_state rule_state)
{
	t_rule	rule;

	rule = machine->rules[rule_state.rule_id];
	if (rule_state.pos >= rule.rhs_len)
	{
		param->symbols = NULL;
		param->count = 0;
	}
	else
	{
		param->symbols = rule.rhs + (rule_state.pos + 1);
		param->count = rule.rhs_len - (rule_state.pos + 1);
	}
	param->has_lookahead = true;
	param->lookahead = rule_state.lookahead;
	first(machine, param);
}

// ERR_NO / ERR_LIBC
static t_error	add_variants(
	t_lr_state *lr_state,
	t_rule_state rule_state,
	t_first_param *first,
	bool *did_add)
{
	t_symbol	terminal;
	t_error		err;

	terminal = 0;
	while (terminal <= SYM_TERMINAL_MAX)
	{
		if (first->result[terminal] == true)
		{
			rule_state.lookahead = terminal;
			err = lr_state_add_rule_state(lr_state, rule_state, did_add);
			if (err.type != ERR_NO)
				return (err);
		}
		terminal++;
	}
	return (error(ERR_NO));
}

// ERR_NO / ERR_LIBC
static t_error	compute_rule_state(
	t_lr_machine *machine,
	t_lr_state *lr_state,
	t_rule_state rule_state,
	bool *did_add)
{
	t_symbol		next_symbol;
	t_first_param	first_param;
	size_t			rule_id;
	t_rule			rule;
	t_error			err;

	next_symbol = rule_state_next_symbol(machine->rules, rule_state);
	if (!symbol_is_non_terminal(next_symbol))
		return (error(ERR_NO));
	compute_first(machine, &first_param, rule_state);
	rule_id = 0;
	while (rule_id < RULE_COUNT)
	{
		rule = machine->rules[rule_id];
		if (rule.lhs == next_symbol)
		{
			rule_state.rule_id = rule_id;
			rule_state.pos = 0;
			err = add_variants(lr_state, rule_state, &first_param, did_add);
			if (err.type != ERR_NO)
				return (err);
		}
		rule_id++;
	}
	return (error(ERR_NO));
}

t_error	lr_state_complete(t_lr_machine *machine, t_lr_state *lr_state)
{
	t_rule_state	rule_state;
	bool			did_add;
	size_t			i;
	t_error			err;

	did_add = true;
	while (did_add)
	{
		did_add = false;
		i = 0;
		while (i < lr_state->len)
		{
			rule_state = ((t_rule_state *)lr_state->data)[i];
			err = compute_rule_state(machine, lr_state, rule_state, &did_add);
			if (err.type != ERR_NO)
				return (err);
			i++;
		}
	}
	return (error(ERR_NO));
}

t_error	lr_state_next(
	t_lr_machine *machine,
	t_lr_state *dst,
	t_lr_state *src,
	t_symbol symbol)
{
	size_t			i;
	t_rule_state	rule_state;
	t_symbol		next_symbol;
	t_error			err;

	lr_state_init(dst);
	i = 0;
	while (i < src->len)
	{
		rule_state = ((t_rule_state *)src->data)[i++];
		next_symbol = rule_state_next_symbol(machine->rules, rule_state);
		if (next_symbol != symbol)
			continue ;
		rule_state.pos++;
		err = lr_state_add_rule_state(dst, rule_state, NULL);
		if (err.type != ERR_NO)
			return (lr_state_free(dst), err);
	}
	if (dst->len > 0)
	{
		err = lr_state_complete(machine, dst);
		if (err.type != ERR_NO)
			return (lr_state_free(dst), err);
	}
	return (error(ERR_NO));
}

```

./srcs/3_builder/1_lr_machine/6_lr_state/lr_state_type.h
```c
#ifndef LR_STATE_TYPE_H
# define LR_STATE_TYPE_H

# include "libft.h"

// vector of t_rule_state (aka itemset aka state in LR parsing theory)
typedef t_vector	t_lr_state;

#endif

```

./srcs/3_builder/1_lr_machine/6_lr_state/lr_state.h
```c
#ifndef LR_STATE_H
# define LR_STATE_H

# include "lr_machine_type.h"
# include "lr_state_type.h"
# include "rule_state_type.h"

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup lr_state_pub LR state module public API
 *  @brief Public functions used to create, compare, register and derive
 *         @ref t_lr_state values.
 *  @warning This module must only be called by its parent module
 *           @ref lr_machine and its sibling modules @ref hooks, @ref rules,
 *           @ref symbols, @ref first, @ref rule_state, @ref transition,
 *           @ref goto, @ref action. All other modules must call
 *           @ref lr_machine instead of calling this module directly.
 *
 *  This module provides helpers for manipulating LR(1) states represented as
 *  sets of @ref t_rule_state values.
 */

/* ************************************************************************* */
/*                               LR_STATE (PUB)                              */
/* ************************************************************************* */

/**
 * @ingroup lr_state_pub
 * @brief Adds an LR state to a registry if it is not already present.
 *
 * This function searches @p lr_states for a state equal to @p lr_state using
 * @ref lr_state_find_id. If no equal state is found, it appends @p lr_state to
 * @p lr_states with @ref vector_push.
 *
 * @note Equality is tested with @ref lr_state_equal.
 * @note If the state already exists, this function returns true and leaves
 *       @p did_add unchanged.
 * @note If a new state is inserted and @p did_add is not NULL, `*did_add` is
 *       set to true.
 * @note Insertion copies the @ref t_lr_state structure into @p lr_states but
 *       does not duplicate the underlying rule-state buffer. After a
 *       successful insertion, that underlying storage must be considered owned
 *       by @p lr_states.
 *
 * @warning @p lr_states and @p lr_state must NOT be NULL.
 * @warning @p lr_states must be a valid vector storing @ref t_lr_state items.
 * @warning When @p did_add is not NULL, it must point to writable storage and
 *          must already have been initialized by the caller.
 * @warning After a successful insertion, caller must NOT free @p lr_state
 *          unless it knows the state was already present and therefore was not
 *          inserted.
 * @warning This function performs no parameter validation.
 *
 * @param lr_states LR-state registry to search and possibly extend
 *                  (borrowed, must NOT be NULL).
 * @param lr_state LR state to register (borrowed, underlying storage ownership
 *                 may transfer to @p lr_states on successful insertion, must
 *                 NOT be NULL).
 * @param did_add Optional flag set to true when a new state is inserted
 *                (borrowed, can be NULL).
 * @return ERR_NO / ERR_LIBC
 */
t_error	lr_state_add(t_vector *lr_states, t_lr_state *lr_state, bool *did_add);

/**
 * @ingroup lr_state_pub
 * @brief Adds a rule state to an LR state if it is not already present.
 *
 * This function checks whether @p rule_state is already contained in
 * @p lr_state. If not, it appends it to @p lr_state with @ref vector_push.
 *
 * @note Containment is tested using the same equality criteria as
 *       @ref rule_state_equal.
 * @note If @p rule_state is already present, this function returns true and
 *       leaves @p did_add unchanged.
 * @note If a new rule state is inserted and @p did_add is not NULL,
 *       `*did_add` is set to true.
 *
 * @warning @p lr_state must NOT be NULL.
 * @warning @p lr_state must be a valid vector storing @ref t_rule_state items.
 * @warning When @p did_add is not NULL, it must point to writable storage and
 *          must already have been initialized by the caller.
 * @warning This function performs no parameter validation.
 *
 * @param lr_state LR state to extend (borrowed, must NOT be NULL).
 * @param rule_state Rule state to insert if absent.
 * @param did_add Optional flag set to true when @p rule_state is newly added
 *                (borrowed, can be NULL).
 * @return ERR_NO / ERR_LIBC.
 */
t_error	lr_state_add_rule_state(t_lr_state *lr_state, t_rule_state rule_state,
			bool *did_add);

/**
 * @ingroup lr_state_pub
 * @brief Completes an LR state by computing its LR(1) closure.
 *
 * For each rule state currently stored in @p lr_state, this function examines
 * the next expected symbol. When that symbol is a non-terminal, all grammar
 * rules whose left-hand side matches that symbol are added with position 0 and
 * with lookaheads derived from the FIRST set of the remaining suffix and the
 * current lookahead.
 *
 * The process is repeated until no new rule state can be added.
 *
 * @note This function mutates @p lr_state in place.
 * @note Lookahead computation delegates to @ref first.
 * @note New rule states are inserted through @ref lr_state_add_rule_state.
 *
 * @warning @p machine and @p lr_state must NOT be NULL.
 * @warning @p machine->rules must already contain a valid grammar, typically
 *          populated by @ref rules_build.
 * @warning The nullable-symbol table and FIRST table stored in @p machine must
 *          already have been built with @ref symbols_build_nullables_table and
 *          @ref first_build_table.
 * @warning Every rule state already stored in @p lr_state must contain a valid
 *          `rule_id`, `pos`, and `lookahead`.
 * @warning On failure, rule states added before the error remain stored in
 *          @p lr_state. This function does not roll back partial progress.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine providing grammar, nullable-symbol and FIRST data
 *                (borrowed, must NOT be NULL).
 * @param lr_state LR state to complete in place (borrowed, must NOT be NULL).
 * @return ERR_NO / ERR_LIBC.
 */
t_error	lr_state_complete(t_lr_machine *machine, t_lr_state *lr_state);

/**
 * @ingroup lr_state_pub
 * @brief Compares two LR states as unordered sets of rule states.
 *
 * This function returns true when @p a and @p b have the same length and every
 * rule state stored in @p a is also contained in @p b.
 *
 * @note The current implementation treats LR states as sets and ignores item
 *       ordering.
 * @note This comparison assumes each LR state contains no duplicate
 *       @ref t_rule_state values, as enforced by @ref lr_state_add_rule_state.
 *
 * @warning @p a and @p b must NOT be NULL.
 * @warning @p a and @p b must each be valid vectors storing
 *          @ref t_rule_state items.
 * @warning This function performs no parameter validation.
 *
 * @param a First LR state to compare (borrowed, must NOT be NULL).
 * @param b Second LR state to compare (borrowed, must NOT be NULL).
 * @return true if @p a and @p b represent the same set of rule states, false
 *         otherwise.
 */
bool	lr_state_equal(t_lr_state *a, t_lr_state *b);

/**
 * @ingroup lr_state_pub
 * @brief Searches a registry for the identifier of a given LR state.
 *
 * This function scans the LR-state registry stored in @p lr_states and
 * compares each entry with @p lr_state using @ref lr_state_equal.
 *
 * @note When the state is found and @p id is not NULL, `*id` receives the
 *       matching index.
 * @note When the state is not found, @p id is left unmodified.
 *
 * @warning @p lr_states and @p lr_state must NOT be NULL.
 * @warning @p lr_states must be a valid vector storing @ref t_lr_state items.
 * @warning This function performs no parameter validation.
 *
 * @param lr_states LR-state registry to search (borrowed, must NOT be NULL).
 * @param lr_state LR state to look up (borrowed, must NOT be NULL).
 * @param id Optional output receiving the matching registry index (borrowed,
 *           can be NULL).
 * @return true if a matching LR state was found, false otherwise.
 */
bool	lr_state_find_id(t_vector *lr_states, t_lr_state *lr_state, size_t *id);

/**
 * @ingroup lr_state_pub
 * @brief Releases the storage owned by an LR state.
 *
 * This function frees the dynamic storage owned by @p lr_state through
 * @ref vector_free.
 *
 * @warning @p lr_state must NOT be NULL.
 * @warning @p lr_state must previously have been initialized with
 *          @ref lr_state_init.
 *
 * @param lr_state LR state to release (borrowed, must NOT be NULL).
 */
void	lr_state_free(void *lr_state);

/**
 * @ingroup lr_state_pub
 * @brief Initializes an empty LR state.
 *
 * This function initializes @p lr_state as a vector storing
 * @ref t_rule_state items.
 *
 * @warning @p lr_state must NOT be NULL.
 * @warning @p lr_state must not already own allocated storage. Free it first
 *          with @ref lr_state_free before reinitializing it.
 *
 * @param lr_state LR state to initialize (borrowed, must NOT be NULL).
 */
void	lr_state_init(t_lr_state *lr_state);

/**
 * @ingroup lr_state_pub
 * @brief Computes the next LR state reached by consuming a symbol.
 *
 * This function initializes @p dst, then scans every rule state stored in
 * @p src. For each rule state whose next expected symbol equals @p symbol,
 * the dot position is advanced by one and the resulting rule state is added to
 * @p dst. If at least one rule state is added, @p dst is then completed with
 * @ref lr_state_complete.
 *
 * @note On success, @p dst is always initialized by this function.
 * @note On success, @p dst may be empty when no rule state in @p src expects
 *       @p symbol.
 * @note On failure, any storage allocated for @p dst during this call is
 *       released before returning false.
 * @note The caller owns the resulting @p dst on success and must release it
 *       with @ref lr_state_free.
 *
 * @warning @p machine, @p dst and @p src must NOT be NULL.
 * @warning @p dst and @p src must not alias the same object.
 * @warning @p dst must not already own allocated storage.
 * @warning @p machine->rules must already contain a valid grammar, typically
 *          populated by @ref rules_build.
 * @warning The nullable-symbol table and FIRST table stored in @p machine must
 *          already have been built with @ref symbols_build_nullables_table and
 *          @ref first_build_table.
 * @warning Every rule state stored in @p src must contain a valid `rule_id`,
 *          `pos`, and `lookahead`.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine providing grammar, nullable-symbol and FIRST data
 *                (borrowed, must NOT be NULL).
 * @param dst Destination LR state receiving the result (owned by caller on
 *            success, must NOT be NULL).
 * @param src Source LR state to advance (borrowed, must NOT be NULL).
 * @param symbol Consumed grammar symbol.
 * @return ERR_NO / ERR_LIBC
 */
t_error	lr_state_next(t_lr_machine *machine, t_lr_state *dst, t_lr_state *src,
			t_symbol symbol);

/**
 * @ingroup lr_state_pub
 * @brief Releases an LR-state registry and all LR states stored in it.
 *
 * This function calls @ref lr_state_free on each @ref t_lr_state stored in
 * @p lr_states, then frees the registry storage itself with @ref vector_free.
 *
 * @warning @p lr_states must NOT be NULL.
 * @warning @p lr_states must previously have been initialized with
 *          @ref lr_state_table_init.
 * @warning @p lr_states must be a valid vector storing @ref t_lr_state items.
 *
 * @param lr_states LR-state registry to release (borrowed, must NOT be NULL).
 */
void	lr_state_table_free(t_lr_state *lr_states);

/**
 * @ingroup lr_state_pub
 * @brief Initializes an empty LR-state registry.
 *
 * This function initializes @p lr_states as a vector storing @ref t_lr_state
 * items.
 *
 * @warning @p lr_states must NOT be NULL.
 * @warning @p lr_states must not already own allocated storage. Free it first
 *          with @ref lr_state_table_free before reinitializing it.
 *
 * @param lr_states LR-state registry to initialize (borrowed, must NOT be
 *                  NULL).
 */
void	lr_state_table_init(t_lr_state *lr_states);

#endif

```

./srcs/3_builder/1_lr_machine/7_transition/1_life_cycle.c
```c
#include "libft.h"
#include "transition_type.h"

void	transition_init(t_vector *transitions)
{
	vector_init(transitions, sizeof(t_transition), 0);
}

void	transition_free(t_vector *transitions)
{
	vector_free(transitions, NULL);
}

```

./srcs/3_builder/1_lr_machine/7_transition/2_build.c
```c
#include "lr_state.h"
#include "transition_type.h"

// ERR_NO / ERR_LIBC
static t_error	build_initial_lr_state(
	t_lr_machine *machine,
	t_lr_state *lr_states)
{
	t_rule_state	rule_state;
	t_lr_state		lr_state;
	t_error			err;

	lr_state_init(&lr_state);
	rule_state.rule_id = RULE_START_1;
	rule_state.pos = 0;
	rule_state.lookahead = SYM_EOF;
	err = lr_state_add_rule_state(&lr_state, rule_state, NULL);
	if (err.type != ERR_NO)
		return (lr_state_free(&lr_state), err);
	err = lr_state_complete(machine, &lr_state);
	if (err.type != ERR_NO)
		return (lr_state_free(&lr_state), err);
	err = lr_state_add(lr_states, &lr_state, NULL);
	if (err.type != ERR_NO)
		return (lr_state_free(&lr_state), err);
	return (error(ERR_NO));
}

// ERR_NO / ERR_LR_STATE_NOT_FOUND / ERR_LIBC
static t_error	add_transition(
	t_lr_machine *machine,
	t_lr_state *from_lr_state,
	t_symbol symbol,
	t_lr_state *to_lr_state)
{
	t_transition	transition;
	size_t			from_id;
	size_t			to_id;

	if (!lr_state_find_id(&machine->lr_states, from_lr_state, &from_id))
		return (error(ERR_LR_STATE_NOT_FOUND));
	if (!lr_state_find_id(&machine->lr_states, to_lr_state, &to_id))
		return (error(ERR_LR_STATE_NOT_FOUND));
	transition.from_lr_state_id = from_id;
	transition.symbol = symbol;
	transition.to_lr_state_id = to_id;
	if (!vector_push(&machine->transitions, &transition))
		return (error_sys());
	return (error(ERR_NO));
}

// ERR_NO / ERR_LR_STATE_NOT_FOUND / ERR_LIBC
static t_error	build_lr_state_and_transition(
	t_lr_machine *machine,
	t_lr_state *lr_state_from,
	t_symbol symbol)
{
	t_lr_state	lr_state_new;
	bool		did_add;
	t_error		err;

	err = lr_state_next(machine, &lr_state_new, lr_state_from, symbol);
	if (err.type != ERR_NO)
		return (err);
	if (lr_state_new.len > 0)
	{
		did_add = false;
		err = lr_state_add(&machine->lr_states, &lr_state_new, &did_add);
		if (err.type != ERR_NO)
			return (lr_state_free(&lr_state_new), err);
		err = add_transition(machine, lr_state_from, symbol, &lr_state_new);
		if (err.type != ERR_NO)
		{
			if (!did_add)
				lr_state_free(&lr_state_new);
			return (err);
		}
		if (!did_add)
			lr_state_free(&lr_state_new);
	}
	return (error(ERR_NO));
}

t_error	transition_build_table(t_lr_machine *machine)
{
	size_t		i;
	t_symbol	symbol;
	t_lr_state	lr_state;
	t_error		err;

	err = build_initial_lr_state(machine, &machine->lr_states);
	if (err.type != ERR_NO)
		return (err);
	i = 0;
	while (i < machine->lr_states.len)
	{
		lr_state = ((t_lr_state *)machine->lr_states.data)[i];
		symbol = 0;
		while (symbol < SYM_COUNT)
		{
			err = build_lr_state_and_transition(machine, &lr_state, symbol);
			if (err.type != ERR_NO)
				return (err);
			symbol++;
		}
		i++;
	}
	return (error(ERR_NO));
}

```

./srcs/3_builder/1_lr_machine/7_transition/transition_type.h
```c
#ifndef TRANSITION_TYPE_H
# define TRANSITION_TYPE_H

# include "symbols_type.h"
# include <stddef.h>

typedef struct s_transition
{
	size_t		from_lr_state_id;
	t_symbol	symbol;
	size_t		to_lr_state_id;
}	t_transition;

#endif

```

./srcs/3_builder/1_lr_machine/7_transition/transition.h
```c
#ifndef TRANSITION_H
# define TRANSITION_H

# include "lr_machine_type.h"

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup transition_pub Transition module public API
 *  @brief Public functions used to initialize, build and release LR
 *         transitions.
 *  @warning This module must only be called by its parent module
 *           @ref lr_machine and its sibling modules @ref hooks, @ref rules,
 *           @ref symbols, @ref first, @ref rule_state, @ref lr_state,
 *           @ref goto, @ref action. All other modules must call
 *           @ref lr_machine instead of calling this module directly.
 *
 *  This module builds the transition table stored in @ref t_lr_machine and
 *  populates the associated LR-state registry.
 */

/* ************************************************************************* */
/*                              TRANSITION (PUB)                             */
/* ************************************************************************* */

/**
 * @ingroup transition_pub
 * @brief Builds the LR transition table of a machine.
 *
 * This function first creates the initial LR state from @ref RULE_START_1 with
 * lookahead @ref SYM_EOF, completes it with @ref lr_state_complete, and stores
 * it in `@p machine->lr_states`. It then explores every symbol in the range
 * `[0, @ref SYM_COUNT)` from every discovered LR state, computes successor
 * states with @ref lr_state_next, registers newly discovered states with
 * @ref lr_state_add, and appends the corresponding @ref t_transition entries
 * to `@p machine->transitions`.
 *
 * @note This function mutates both `@p machine->lr_states` and
 *       `@p machine->transitions`.
 * @note Newly discovered LR states are stored in `@p machine->lr_states` and
 *       reused by transition entries through their numeric identifiers.
 *
 * @warning @p machine must NOT be NULL.
 * @warning `@p machine->rules` must already contain a valid grammar, typically
 *          populated by @ref rules_build.
 * @warning The nullable-symbol table and FIRST table stored in @p machine must
 *          already have been built with @ref symbols_build_nullables_table and
 *          @ref first_build_table.
 * @warning `@p machine->lr_states` and `@p machine->transitions` must already
 *          have been initialized with @ref lr_state_table_init and
 *          @ref transition_init.
 * @warning This function is intended to build tables from an empty state. It
 *          does not clear previously stored LR states or transitions before
 *          appending new data.
 * @warning On failure, LR states and transitions added before the error remain
 *          stored in @p machine. This function does not roll back partial
 *          progress.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine whose LR-state registry and transition table must
 *                be built (borrowed, must NOT be NULL).
 * @return ERR_NO / ERR_LR_STATE_NOT_FOUND / ERR_LIBC
 */
t_error	transition_build_table(t_lr_machine *machine);

/**
 * @ingroup transition_pub
 * @brief Releases the storage owned by a transition table.
 *
 * This function frees the vector storage owned by @p transitions through
 * @ref vector_free.
 *
 * @note @ref t_transition items do not own nested dynamic resources.
 *
 * @warning @p transitions must NOT be NULL.
 * @warning @p transitions must previously have been initialized with
 *          @ref transition_init.
 *
 * @param transitions Transition table to release (borrowed, must NOT be NULL).
 */
void	transition_free(t_vector *transitions);

/**
 * @ingroup transition_pub
 * @brief Initializes an empty transition table.
 *
 * This function initializes @p transitions as a vector storing
 * contiguous @ref t_transition items.
 *
 * @note This function cannot fail with the current implementation because it
 *       delegates to @ref vector_init with a zero initial capacity.
 *
 * @warning @p transitions must NOT be NULL.
 * @warning @p transitions must not already own allocated storage. Free it
 *          first with @ref transition_free before reinitializing it.
 *
 * @param transitions Transition table to initialize (borrowed, must NOT be
 *                    NULL).
 */
void	transition_init(t_vector *transitions);

#endif

```

./srcs/3_builder/1_lr_machine/8_goto/1_life_cycle.c
```c
#include <stdlib.h>

void	goto_init(size_t ***gotos)
{
	*gotos = NULL;
}

void	goto_free(size_t lr_states_count, size_t ***gotos)
{
	size_t	i;

	if (!gotos || !*gotos)
		return ;
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

./srcs/3_builder/1_lr_machine/8_goto/2_build.c
```c
#include "goto.h"
#include "transition_type.h"
#include <stdlib.h>

// ERR_LIBC
static t_error	goto_save_error_and_free(t_lr_machine *machine, size_t count)
{
	t_error	err;
	size_t	j;

	err = error_sys();
	j = 0;
	while (j < count)
		free(machine->gotos[j++]);
	free(machine->gotos);
	machine->gotos = NULL;
	return (err);
}

// ERR_NO / ERR_LIBC
static t_error	malloc_goto_table(t_lr_machine *machine)
{
	size_t	rows;
	size_t	cols;
	size_t	i;

	rows = machine->lr_states.len;
	cols = SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1;
	machine->gotos = malloc(rows * sizeof(*machine->gotos));
	if (!machine->gotos)
		return (error_sys());
	i = 0;
	while (i < rows)
	{
		machine->gotos[i] = malloc(cols * sizeof(**machine->gotos));
		if (!machine->gotos[i])
			return (goto_save_error_and_free(machine, i));
		i++;
	}
	return (error(ERR_NO));
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

static void	goto_process_transitions(t_lr_machine *machine)
{
	size_t			i;
	t_transition	transition;
	t_symbol		symbol;
	size_t			row;
	size_t			col;

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
}

t_error	goto_build_table(t_lr_machine *machine)
{
	t_error			err;

	err = malloc_goto_table(machine);
	if (err.type != ERR_NO)
		return (err);
	goto_set_empty(machine);
	goto_process_transitions(machine);
	return (error(ERR_NO));
}

```

./srcs/3_builder/1_lr_machine/8_goto/3_core.c
```c
#include "goto.h"

bool	go_to(
	size_t **gotos,
	size_t current_lr_state_id,
	t_symbol symbol,
	size_t *new_lr_state_id)
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

./srcs/3_builder/1_lr_machine/8_goto/goto_types.h
```c
#ifndef GOTOS_TYPES_H
# define GOTOS_TYPES_H

# include "symbols_type.h"
# include <stddef.h>

typedef struct s_goto
{
	size_t		from_lr_state_id;
	t_symbol	symbol;
	size_t		to_lr_state_id;
}	t_goto;

#endif

```

./srcs/3_builder/1_lr_machine/8_goto/goto.h
```c
#ifndef GOTO_H
# define GOTO_H

# include "lr_machine_type.h"
# include <stdint.h>

# define GOTO_EMPTY	SIZE_MAX

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup goto_pub Goto module public API
 *  @brief Public functions used to initialize, build, query and release the
 *         GOTO table.
 *  @warning This module must only be called by its parent module
 *           @ref lr_machine and its sibling modules @ref hooks, @ref rules,
 *           @ref symbols, @ref first, @ref rule_state, @ref lr_state,
 *           @ref transition, @ref action. All other modules must call
 *           @ref lr_machine instead of calling this module directly.
 *
 *  This module builds the non-terminal transition table stored in
 *  @ref t_lr_machine and provides lookup helpers for it.
 */

/* ************************************************************************* */
/*                                 GOTO (PUB)                                */
/* ************************************************************************* */

/**
 * @ingroup goto_pub
 * @brief Looks up the next LR state reached through a non-terminal symbol.
 *
 * This function queries the GOTO table referenced by @p gotos for the entry
 * designated by @p current_lr_state_id and @p symbol. The symbol is converted
 * to a column index relative to @ref SYM_NON_TERMINAL_MIN.
 *
 * @note On success, the object pointed to by @p new_lr_state_id receives the
 *       destination LR-state identifier.
 * @note On failure, the object pointed to by @p new_lr_state_id is left
 *       unmodified.
 *
 * @warning @p gotos and @p new_lr_state_id must NOT be NULL.
 * @warning @p gotos must reference a valid table previously built by
 *          @ref goto_build_table.
 * @warning @p current_lr_state_id must be a valid row index in the GOTO table.
 * @warning @p symbol must be a non-terminal symbol in the range
 *          [@ref SYM_NON_TERMINAL_MIN, @ref SYM_NON_TERMINAL_MAX].
 * @warning This function performs no parameter validation except checking
 *          whether @p symbol is within the non-terminal range and whether the
 *          selected entry equals @ref GOTO_EMPTY.
 *
 * @param gotos GOTO table to query (borrowed, must NOT be NULL).
 * @param current_lr_state_id Source LR-state identifier.
 * @param symbol Non-terminal symbol to follow.
 * @param new_lr_state_id Output pointer receiving the destination LR-state
 *                        identifier (borrowed, must NOT be NULL).
 * @return true if a destination LR state exists for this transition, false
 *         otherwise.
 */
bool	go_to(size_t **gotos, size_t current_lr_state_id, t_symbol symbol,
			size_t *new_lr_state_id);

/**
 * @ingroup goto_pub
 * @brief Builds the GOTO table stored in an LR machine.
 *
 * This function allocates a two-dimensional table whose row count equals
 * `@p machine->lr_states.len` and whose column count equals the number of
 * non-terminal symbols from @ref SYM_NON_TERMINAL_MIN to
 * @ref SYM_NON_TERMINAL_MAX, inclusive. Every entry is first initialized to
 * @ref GOTO_EMPTY. The table is then populated from the transitions stored in
 * `@p machine->transitions`: only transitions labeled with non-terminal
 * symbols are copied into the resulting GOTO table.
 *
 * @note On success, ownership of the allocated table remains with @p machine
 *       and the table must later be released with @ref goto_free.
 * @note On allocation failure, this function frees any partially allocated
 *       rows and leaves `@p machine->gotos` set to NULL.
 *
 * @warning @p machine must NOT be NULL.
 * @warning `@p machine->lr_states` and `@p machine->transitions` must already
 *          have been built, typically by @ref transition_build_table.
 * @warning This function does not free a previously allocated GOTO table
 *          before overwriting `@p machine->gotos`.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine whose GOTO table must be allocated and populated
 *                (borrowed, must NOT be NULL).
 * @return ERR_NO / ERR_LIBC.
 */
t_error	goto_build_table(t_lr_machine *machine);

/**
 * @ingroup goto_pub
 * @brief Releases a previously allocated GOTO table.
 *
 * This function frees each row referenced by `*gotos`, then frees the outer
 * table pointer and sets `*gotos` to NULL.
 *
 * @note If @p gotos is NULL or if `*gotos` is NULL, this function does
 *       nothing.
 *
 * @warning When `*gotos` is not NULL, @p lr_states_count must match the number
 *          of allocated rows in the table.
 *
 * @param lr_states_count Number of rows allocated in the table.
 * @param gotos Address of the GOTO table pointer to release (borrowed, can be
 *              NULL).
 */
void	goto_free(size_t lr_states_count, size_t ***gotos);

/**
 * @ingroup goto_pub
 * @brief Initializes a GOTO table pointer to an empty state.
 *
 * This function sets `*gotos` to NULL.
 *
 * @warning @p gotos must NOT be NULL.
 *
 * @param gotos Address of the GOTO table pointer to initialize (borrowed,
 *              must NOT be NULL).
 */
void	goto_init(size_t ***gotos);

#endif

```

./srcs/3_builder/1_lr_machine/9_action/1_life_cycle.c
```c
#include "action_type.h"
#include <stdlib.h>

void	action_init(t_action ***actions)
{
	*actions = NULL;
}

void	action_free(size_t lr_states_count, t_action ***actions)
{
	size_t	i;

	if (!actions || !*actions)
		return ;
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

./srcs/3_builder/1_lr_machine/9_action/2_default.c
```c
#include "action_type.h"
#include "action.h"
#include <stdlib.h>

// ERR_LIBC
static t_error	action_save_error_and_free(t_lr_machine *machine, size_t count)
{
	t_error	err;
	size_t	j;

	err = error_sys();
	j = 0;
	while (j < count)
		free(machine->actions[j++]);
	free(machine->actions);
	machine->actions = NULL;
	return (err);
}

// ERR_NO / ERR_LIBC
static t_error	malloc_action_table(t_lr_machine *machine)
{
	size_t	rows;
	size_t	cols;
	size_t	i;

	rows = machine->lr_states.len;
	cols = SYM_TERMINAL_MAX + 1;
	machine->actions = malloc(rows * sizeof(*machine->actions));
	if (!machine->actions)
		return (error_sys());
	i = 0;
	while (i < rows)
	{
		machine->actions[i] = malloc(cols * sizeof(**machine->actions));
		if (!machine->actions[i])
			return (action_save_error_and_free(machine, i));
		i++;
	}
	return (error(ERR_NO));
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

t_error	action_build_default_table(t_lr_machine *machine)
{
	t_error	err;

	err = malloc_action_table(machine);
	if (err.type != ERR_NO)
		return (err);
	action_set_error(machine);
	return (error(ERR_NO));
}

```

./srcs/3_builder/1_lr_machine/9_action/3_core.c
```c
#include "action_priv.h"
#include "transition_type.h"
#include "rule_state_type.h"
#include "lr_state_type.h"

// DEBUG (always return ERR_LR_CONFLICT)
static t_error	print_conflict(t_action *action, size_t lr_state_id, t_symbol symbol, t_action_type target_type, size_t target_payload)
{
	t_buff	buff;
	char	*format_string;

	buff_init(&buff, 0, NULL, 0);
	if (action->type == ACTION_SHIFT)
		buff_append(&buff, " SHIFT-", -1);
	else if (action->type == ACTION_REDUCE)
		buff_append(&buff, " REDUCE-", -1);
	else if (action->type == ACTION_ACCEPT)
		buff_append(&buff, " ACCEPT-", -1);
	if (target_type == ACTION_SHIFT)
		buff_append(&buff, "SHIFT", -1);
	else if (target_type == ACTION_REDUCE)
		buff_append(&buff, "REDUCE", -1);
	else if (target_type == ACTION_ACCEPT)
		buff_append(&buff, "ACCEPT", -1);
	buff_append(&buff, " for lr_state %i and symbol %i (current payload = %i vs target = %i)", -1);
	format_string = buff_get_string(&buff);
	fprint_err(false, "⚠️ conflict", format_string,
		(int)lr_state_id, (int)symbol,
		(int)action->payload, (int)target_payload);
	return (error(ERR_LR_CONFLICT));
}

// ERR_NO / ERR_LR_CONFLICT
static t_error	add_shifts(t_lr_machine *machine)
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
				return (print_conflict(action, lr_state_id, symbol, ACTION_SHIFT, transition.to_lr_state_id));
			action->type = ACTION_SHIFT;
			action->payload = transition.to_lr_state_id;
		}
		i++;
	}
	return (error(ERR_NO));
}

// ERR_NO / ERR_LR_CONFLICT
static t_error	add_reduces(
	t_lr_machine *machine,
	size_t lr_state_id,
	t_rule_state rule_state)
{
	t_symbol	symbol;
	t_action	*action;

	symbol = rule_state.lookahead;
	action = &machine->actions[lr_state_id][symbol];
	if (action->type != ACTION_ERROR)
		return (print_conflict(action, lr_state_id, symbol, ACTION_REDUCE, rule_state.rule_id));
	action->type = ACTION_REDUCE;
	action->payload = rule_state.rule_id;
	return (error(ERR_NO));
}

// ERR_NO / ERR_LR_CONFLICT
static t_error	add_reduces_and_accept(
	t_lr_machine *machine,
	size_t lr_state_id,
	t_rule_state rule_state)
{
	t_rule		rule;
	t_action	*action;

	rule = machine->rules[rule_state.rule_id];
	if (rule_state.pos < rule.rhs_len)
		return (error(ERR_NO));
	if (rule_state.rule_id == RULE_START_1 && rule_state.lookahead == SYM_EOF)
	{
		action = &machine->actions[lr_state_id][SYM_EOF];
		if (action->type != ACTION_ERROR)
			return (print_conflict(action, lr_state_id, SYM_EOF, ACTION_ACCEPT, rule_state.rule_id));
		action->type = ACTION_ACCEPT;
		action->payload = rule_state.rule_id;
		return (error(ERR_NO));
	}
	return (add_reduces(machine, lr_state_id, rule_state));
}

// ERR_NO / ERR_LR_CONFLICT
static t_error	compute_rule_states(t_lr_machine *machine, size_t lr_state_id)
{
	t_lr_state		lr_state;
	size_t			rule_state_id;
	t_rule_state	rule_state;
	t_error			err;

	lr_state = ((t_lr_state *)machine->lr_states.data)[lr_state_id];
	rule_state_id = 0;
	while (rule_state_id < lr_state.len)
	{
		rule_state = ((t_rule_state *)lr_state.data)[rule_state_id];
		err = add_reduces_and_accept(machine, lr_state_id, rule_state);
		if (err.type != ERR_NO)
			return (err);
		rule_state_id++;
	}
	return (error(ERR_NO));
}

t_error	action_build_table(t_lr_machine *machine)
{
	size_t			lr_state_id;
	t_error			err;

	err = action_build_default_table(machine);
	if (err.type == ERR_NO)
		err = add_shifts(machine);
	if (err.type != ERR_NO)
		return (err);
	lr_state_id = 0;
	while (lr_state_id < machine->lr_states.len)
	{
		err = compute_rule_states(machine, lr_state_id);
		if (err.type != ERR_NO)
			return (err);
		lr_state_id++;
	}
	return (error(ERR_NO));
}

```

./srcs/3_builder/1_lr_machine/9_action/action_priv.h
```c
#ifndef ACTION_PRIV_H
# define ACTION_PRIV_H

# include "lr_machine_type.h"

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup action_priv Action module internal API
 *  @brief Internal helpers used to allocate and initialize the ACTION table.
 *  @warning These functions must only be called by the @ref action module
 *           itself.
 *
 *  This private API is intended for the implementation of the @ref action
 *  module.
 */

/* ************************************************************************* */
/*                                  PRIVATE                                  */
/* ************************************************************************* */

/**
 * @ingroup action_priv
 * @brief Allocates and initializes the default ACTION table of an LR machine.
 *
 * This function allocates a two-dimensional ACTION table whose row count
 * equals `@p machine->lr_states.len` and whose column count equals
 * `@ref SYM_TERMINAL_MAX + 1`. Every entry is initialized to an
 * @ref ACTION_ERROR action whose payload is @ref ACTION_PAYLOAD_EMPTY.
 *
 * @note On success, ownership of the allocated table remains with @p machine
 *       and the table must later be released with @ref action_free.
 * @note On allocation failure, this function frees any partially allocated
 *       rows and leaves `@p machine->actions` set to NULL.
 *
 * @warning @p machine must NOT be NULL.
 * @warning `@p machine->lr_states` must already have been built.
 * @warning This function does not free a previously allocated ACTION table
 *          before overwriting `@p machine->actions`.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine whose ACTION table must be allocated and
 *                initialized (borrowed, must NOT be NULL).
 * @return ERR_NO / ERR_LIBC
 */
t_error	action_build_default_table(t_lr_machine *machine);

# endif

```

./srcs/3_builder/1_lr_machine/9_action/action_type.h
```c
#ifndef ACTION_TYPE_H
# define ACTION_TYPE_H

# include <stddef.h>

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

#endif

```

./srcs/3_builder/1_lr_machine/9_action/action.h
```c
#ifndef ACTION_H
# define ACTION_H

# include "lr_machine_type.h"
# include "stdint.h"

# define ACTION_PAYLOAD_EMPTY	SIZE_MAX

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup action_pub Action module public API
 *  @brief Public functions used to initialize, build and release the ACTION
 *         table.
 *  @warning This module must only be called by its parent module
 *           @ref lr_machine and its sibling modules @ref hooks, @ref rules,
 *           @ref symbols, @ref first, @ref rule_state, @ref lr_state,
 *           @ref transition, @ref goto. All other modules must call
 *           @ref lr_machine instead of calling this module directly.
 *
 *  This module builds the terminal ACTION table stored in @ref t_lr_machine.
 */

/* ************************************************************************* */
/*                                   MACROS                                  */
/* ************************************************************************* */

/**
 * @ingroup action_pub
 * @brief Sentinel payload value used when an action has no meaningful payload.
 *
 * @note The default ACTION table initialization uses this value for
 *       @ref ACTION_ERROR entries.
 */
# define ACTION_PAYLOAD_EMPTY	SIZE_MAX

/* ************************************************************************* */
/*                                ACTION (PUB)                               */
/* ************************************************************************* */

/**
 * @ingroup action_pub
 * @brief Builds the ACTION table of an LR machine.
 *
 * This function first allocates and initializes the whole ACTION table with
 * default @ref ACTION_ERROR entries. It then fills terminal-labeled
 * transitions as @ref ACTION_SHIFT entries and completed rule states as
 * @ref ACTION_REDUCE entries. A completed start rule with lookahead
 * @ref SYM_EOF produces an @ref ACTION_ACCEPT entry.
 *
 * @note This function mutates the ACTION table stored in @p machine.
 * @note On success, ownership of the allocated ACTION table remains with
 *       @p machine and the table must later be released with @ref action_free.
 * @note The current implementation stores `rule_state.rule_id` as the payload
 *       of @ref ACTION_ACCEPT entries.
 *
 * @warning @p machine must NOT be NULL.
 * @warning `@p machine->rules`, `@p machine->lr_states`, and
 *          `@p machine->transitions` must already contain valid data,
 *          typically produced by @ref rules_build and
 *          @ref transition_build_table.
 * @warning This function does not free a previously allocated ACTION table
 *          before overwriting `@p machine->actions`.
 * @warning On failure, entries added before the error remain stored in
 *          @p machine. This function does not roll back partial progress.
 * @warning This function also fails on shift/reduce, reduce/reduce, or
 *          shift/accept conflicts. In that case, a diagnostic is printed and
 *          the function returns false.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine whose ACTION table must be allocated and
 *                populated (borrowed, must NOT be NULL).
 * @return ERR_NO / ERR_LR_CONFLICT / ERR_LIBC
 */
t_error	action_build_table(t_lr_machine *machine);

/**
 * @ingroup action_pub
 * @brief Releases a previously allocated ACTION table.
 *
 * This function frees each row referenced by `*actions`, then frees the outer
 * table pointer and sets `*actions` to NULL.
 *
 * @note If @p actions is NULL or if `*actions` is NULL, this function does
 *       nothing.
 *
 * @warning When `*actions` is not NULL, @p lr_states_count must match the
 *          number of allocated rows in the table.
 *
 * @param lr_states_count Number of rows allocated in the table.
 * @param actions Address of the ACTION table pointer to release (borrowed, can
 *                be NULL).
 */
void	action_free(size_t lr_states_count, t_action ***actions);

/**
 * @ingroup action_pub
 * @brief Initializes an ACTION table pointer to an empty state.
 *
 * This function sets `*actions` to NULL.
 *
 * @warning @p actions must NOT be NULL.
 *
 * @param actions Address of the ACTION table pointer to initialize (borrowed,
 *                must NOT be NULL).
 */
void	action_init(t_action ***actions);

#endif

```

./srcs/3_builder/1_lr_machine/lr_machine_type.h
```c
#ifndef LR_MACHINE_TYPE_H
# define LR_MACHINE_TYPE_H

# include "libft.h"
# include "rules__type.h"
# include "action_type.h"

typedef struct s_lr_machine
{
	t_rule		rules[RULE_COUNT];
	bool		nullable_symbols[SYM_COUNT];
	bool		first[SYM_COUNT][SYM_TERMINAL_MAX + 1];
	t_vector	lr_states;
	t_vector	transitions;
	size_t		**gotos;		// [lr_state][non-terminal_symbol]
	t_action	**actions;		// [lr_state][terminal_symbol]
}	t_lr_machine;

#endif

```

./srcs/3_builder/1_lr_machine/lr_machine.h
```c
#ifndef LR_MACHINE_H
# define LR_MACHINE_H

# include "lr_machine_type.h"
# include "error.h"

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup lr_machine_pub LR machine module public API
 *  @brief Public functions used to initialize, build and release an
 *         @ref t_lr_machine.
 *  @warning This module must only be called by its parent module
 *           @ref builder and its sibling modules @ref parser. All other
 *           modules must call @ref builder instead of calling this module
 *           directly.
 *
 *  This module orchestrates the construction and cleanup of the grammar,
 *  nullable-symbol, FIRST, LR-state, transition, GOTO and ACTION tables.
 */

/* ************************************************************************* */
/*                              LR_MACHINE (PUB)                             */
/* ************************************************************************* */

/**
 * @ingroup lr_machine_pub
 * @brief Builds all derived tables of an LR machine.
 *
 * This function builds the grammar rule table with @ref rules_build, then
 * computes nullable-symbol information with
 * @ref symbols_build_nullables_table, FIRST sets with @ref first_build_table,
 * LR states and transitions with @ref transition_build_table, the GOTO table
 * with @ref goto_build_table, and finally the ACTION table with
 * @ref action_build_table.
 *
 * @note This function mutates multiple fields of @p machine in place,
 *       including `rules`, `nullable_symbols`, `first`, `lr_states`,
 *       `transitions`, `gotos`, and `actions`.
 * @note This function is intended to be called after @ref lr_machine_init.
 *
 * @warning @p machine must NOT be NULL.
 * @warning @p machine must previously have been initialized with
 *          @ref lr_machine_init.
 * @warning This function does not clear previously built tables before
 *          rebuilding them.
 * @warning On failure, data successfully built before the error remain stored
 *          in @p machine. This function does not roll back partial progress.
 * @warning The current implementation temporarily changes the numeric locale
 *          and restores it only on successful completion.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine to build in place (borrowed, must NOT be NULL).
 * @return [TODO...]
 */
t_error	lr_machine_build_tables(t_lr_machine *machine);

/**
 * @ingroup lr_machine_pub
 * @brief Releases the dynamic resources owned by an LR machine.
 *
 * This function releases the transition table with @ref transition_free, the
 * ACTION table with @ref action_free, the GOTO table with @ref goto_free, and
 * the LR-state registry with @ref lr_state_table_free.
 *
 * @note This function does not free the @ref t_lr_machine object itself.
 * @note The rule table, nullable-symbol table, and FIRST table are stored
 *       inline inside @ref t_lr_machine and therefore do not require explicit
 *       deallocation.
 *
 * @warning @p machine must NOT be NULL.
 * @warning @p machine must previously have been initialized with
 *          @ref lr_machine_init.
 * @warning The row count passed internally to @ref action_free and
 *          @ref goto_free is taken from `@p machine->lr_states.len`.
 *          Corrupting that registry before cleanup would make this call
 *          unsafe.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine to release in place (borrowed, must NOT be NULL).
 */
void	lr_machine_free(t_lr_machine *machine);

/**
 * @ingroup lr_machine_pub
 * @brief Initializes an LR machine to an empty state.
 *
 * This function initializes the embedded rule table with @ref rules_init, the
 * LR-state registry with @ref lr_state_table_init, the transition table with
 * @ref transition_init, the ACTION table pointer with @ref action_init, and
 * the GOTO table pointer with @ref goto_init.
 *
 * @note After this call, @p machine is ready to be passed to
 *       @ref lr_machine_build_tables.
 * @note This function does not build derived parsing tables; it only prepares
 *       their storage and default empty state.
 *
 * @warning @p machine must NOT be NULL.
 * @warning @p machine must not already own allocated resources. Release them
 *          first with @ref lr_machine_free before reinitializing it.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine to initialize in place (borrowed, must NOT be
 *                NULL).
 */
void	lr_machine_init(t_lr_machine *machine);

#endif

```

./srcs/3_builder/1_lr_machine/main.c
```c
#include "rules__pub.h"
#include "symbols.h"
#include "first.h"
#include "lr_state.h"
#include "transition.h"
#include "transition_type.h"
#include "action.h"
#include "goto.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG

#define LR_MACHINE_ERROR_MESSAGE	"unable to build parsing tables"
#define TRANSITION_INITIAL_CAP		6000
#define LR_STATE_INITIAL_CAP		2000

void	lr_machine_init(t_lr_machine *machine)
{
	rules_init(machine->rules);
	lr_state_table_init(&machine->lr_states);
	transition_init(&machine->transitions);
	action_init(&machine->actions);
	goto_init(&machine->gotos);
}

static inline t_error	lr_machine_alloc_tables(t_lr_machine *machine)
{
	if (!vector_init(&machine->transitions, sizeof(t_transition),
		TRANSITION_INITIAL_CAP))
		return (error_sys());
	if (!vector_init(&machine->lr_states, sizeof(t_lr_state),
		LR_STATE_INITIAL_CAP))
		return (error_sys());
	return (error(ERR_NO));
}

static inline t_error	lr_machine_build_error(t_error err, const char *message)
{
	return (error_print(err, "lr_machine", message, NULL, NULL));
}

// TODO: ERR_NO / ERR_LR_STATE_NOT_FOUND / ERR_LIBC [TODO...]
t_error	lr_machine_build_tables(t_lr_machine *machine)
{
	t_error	err;

	print_title("lr_machine_build_tables()");
	rules_build(machine->rules);
	print_pass("rules table built            (entries: %'6i)\n", RULE_COUNT);
	symbols_build_nullables_table(machine);
	print_pass("nullable symbols table built (entries: %'6i)\n", SYM_COUNT);
	first_build_table(machine);
	print_pass("first table built            (entries: %'6i)\n", SYM_COUNT * (SYM_TERMINAL_MAX + 1));
	err = lr_machine_alloc_tables(machine);
	if (err.type != ERR_NO)
		return (lr_machine_build_error(err, "unable to malloc tables"));
	err = transition_build_table(machine);
	if (err.type != ERR_NO)
		return (lr_machine_build_error(err, LR_MACHINE_ERROR_MESSAGE));
	print_pass("transitions table built      (entries: %'6zu)\n", machine->transitions.len);
	print_pass("lr_states table built        (entries: %'6zu)\n", machine->lr_states.len);
	err = goto_build_table(machine);
	if (err.type != ERR_NO)
		return (lr_machine_build_error(err, LR_MACHINE_ERROR_MESSAGE));
	print_pass("gotos table built            (entries: %'6zu)\n", machine->lr_states.len * (SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1));
	err = action_build_table(machine);
	if (err.type != ERR_NO)
		return (lr_machine_build_error(err, LR_MACHINE_ERROR_MESSAGE));
	print_pass("actions table built          (entries: %'6zu)\n", machine->lr_states.len * (SYM_TERMINAL_MAX + 1));
	print_result("lr_machine_build_tables()");
	return (error(ERR_NO));
}

void	lr_machine_free(t_lr_machine *machine)
{
	transition_free(&machine->transitions);
	action_free(machine->lr_states.len, &machine->actions);
	goto_free(machine->lr_states.len, &machine->gotos);
	lr_state_table_free(&machine->lr_states);
}

```

./srcs/3_builder/2_parser/0_error.c
```c
#include "error.h"
#include <stdlib.h>

t_error	parser_internal_error(void)
{
	return (error_print(error_sys(), "parser", "internal error", NULL, NULL));
}

t_error	parser_invalid_syntax(void)
{
	return (error_print(
		error(ERR_INVALID_SYNTAX),
		"parser",
		NULL,
		NULL));
}

```

./srcs/3_builder/2_parser/0_read_heredoc.c
```c
#include "scanner.h"
#include "parser_type.h"

# include <stdio.h>
# include "logs.h"
t_error	parser_read_heredoc(t_parser *parser)
{
	if (parser->lookahead_raw_symbol != SYM_NEWLINE)
		return (error(ERR_NO));
	if (!parser->must_read_heredoc)
		return (error(ERR_NO));
	parser->must_read_heredoc = false;
	fprintf(stderr, "[PARSER] %sscanner_heredoc_read()%s\n", YELLOW, NC);
	return (scanner_heredoc_read());
}

```

./srcs/3_builder/2_parser/1_life_cycle.c
```c
#include "parser_priv.h"
#include "token.h"
#include "cst.h"
#include <stdlib.h>

void	parser_init(t_parser *parser)
{
	parser_stack_init(&parser->stack);
	(void)vector_init(&parser->tokens, sizeof(t_token), 0);
	parser->cst = NULL;
	parser->qualifiers = NULL;
	parser->lookahead_id = 0;
	parser->lookahead_raw_symbol = SYM_NONE;
	parser->lookahead_symbol = SYM_NONE;
	parser->function_body_depth = 0;
	parser->assignment_disabled = false;
	parser->expansion_disabled = false;
	parser->must_read_heredoc = false;
}

t_error	parser_reset(t_parser *parser)
{
	size_t	i;

	i = 0;
	while (i < parser->stack.len)
		parser_free_stack_item(&((t_parser_stack_item *)parser->stack.data)[i++]);
	parser->stack.len = 0;
	i = 0;
	while (i < parser->tokens.len)
		parser_free_token(&((t_token *)parser->tokens.data)[i++]);
	parser->tokens.len = 0;
	cst_node_free(&parser->cst);
	parser->cst = NULL;
	parser->lookahead_id = 0;
	parser->lookahead_raw_symbol = SYM_NONE;
	parser->lookahead_symbol = SYM_NONE;
	parser->function_body_depth = 0;
	parser->assignment_disabled = false;
	parser->expansion_disabled = false;
	parser->must_read_heredoc = false;
	return (error(ERR_NO));
}

void	parser_free_token(void *token)
{
	token_free(token);
}

void	parser_free_stack_item(void *raw_item)
{
	t_parser_stack_item	*item;

	item = raw_item;
	cst_node_free(&item->cst_node);
}

void	parser_free(t_parser *parser)
{
	vector_free(&parser->stack, parser_free_stack_item);
	vector_free(&parser->tokens, parser_free_token);
	cst_node_free(&parser->cst);
	free(parser->qualifiers);
	parser_init(parser);
}

```

./srcs/3_builder/2_parser/1_qualifiers/0_name.c
```c
#include "symbols_type.h"
#include "utils.h"

bool	qualify_try_name(const char *token_value, t_symbol *dst_symbol)
{
	if (!name_is_valid(token_value))
		return (false);
	*dst_symbol = SYM_NAME;
	return (true);
}

```

./srcs/3_builder/2_parser/1_qualifiers/0_reserved_words.c
```c
#include "libft.h"
#include "symbols_type.h"

static inline t_symbol	str_to_reserved_word_2(const char *token_value)
{
	if (str_cmp(token_value, "elif") == 0)
		return (SYM_Elif);
	else if (str_cmp(token_value, "else") == 0)
		return (SYM_Else);
	else if (str_cmp(token_value, "fi") == 0)
		return (SYM_Fi);
	else if (str_cmp(token_value, "for") == 0)
		return (SYM_For);
	else if (str_cmp(token_value, "in") == 0)
		return (SYM_In);
	else if (str_cmp(token_value, "until") == 0)
		return (SYM_Until);
	else if (str_cmp(token_value, "while") == 0)
		return (SYM_While);
	return (SYM_error);
}

static inline t_symbol	str_to_reserved_word(const char *token_value)
{
	if (str_cmp(token_value, "!") == 0)
		return (SYM_Bang);
	else if (str_cmp(token_value, "{") == 0)
		return (SYM_Lbrace);
	else if (str_cmp(token_value, "}") == 0)
		return (SYM_Rbrace);
	else if (str_cmp(token_value, "case") == 0)
		return (SYM_Case);
	else if (str_cmp(token_value, "esac") == 0)
		return (SYM_Esac);
	else if (str_cmp(token_value, "do") == 0)
		return (SYM_Do);
	else if (str_cmp(token_value, "done") == 0)
		return (SYM_Done);
	else if (str_cmp(token_value, "if") == 0)
		return (SYM_If);
	else if (str_cmp(token_value, "then") == 0)
		return (SYM_Then);
	return (str_to_reserved_word_2(token_value));
}

bool	qualify_try_reserved_word(const char *token_value, t_symbol *dst_symbol)
{
	t_symbol	symbol;

	symbol = str_to_reserved_word(token_value);
	if (symbol == SYM_error)
		return false;
	*dst_symbol = symbol;
	return (true);
}

```

./srcs/3_builder/2_parser/1_qualifiers/0_word.c
```c
#include "parser_type.h"

t_error		qualify_word(void *parser, const char *token_value)
{
	(void)token_value;
	((t_parser *)parser)->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}

```

./srcs/3_builder/2_parser/1_qualifiers/1_qualify.c
```c
#include "parser_type.h"
#include "qualifiers_priv.h"

t_error		qualify_1(void *parser, const char *token_value)
{
	t_parser	*parser_;

	parser_ = (t_parser *)parser;
	if (qualify_try_reserved_word(token_value, &parser_->lookahead_symbol))
		return (error(ERR_NO));
	parser_->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}

```

./srcs/3_builder/2_parser/1_qualifiers/2_qualify.c
```c
#include "parser_type.h"

t_error		qualify_2(void *parser, const char *token_value)
{
	t_parser	*parser_;

	(void)token_value;
	parser_ = (t_parser *)parser;
	/*
	TODO:
		"The expansions specified in 2.7 Redirection shall occur.
		As specified there, exactly one field can result (or the result is unspecified).
		And there are additional requirements on pathname expansion.""	
	*/
	parser_->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}

```

./srcs/3_builder/2_parser/1_qualifiers/4_qualify.c
```c
#include "parser_type.h"

t_error		qualify_4(void *parser, const char *token_value)
{
	if (str_cmp("esac", token_value) == 0)
		((t_parser *)parser)->lookahead_symbol = SYM_Esac;
	else
		((t_parser *)parser)->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}

```

./srcs/3_builder/2_parser/1_qualifiers/5_qualify.c
```c
#include "parser_type.h"
#include "qualifiers_priv.h"

t_error		qualify_5(void *parser, const char *token_value)
{
	if (!qualify_try_name(token_value, &((t_parser *)parser)->lookahead_symbol))
		((t_parser *)parser)->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}

```

./srcs/3_builder/2_parser/1_qualifiers/6a_qualify.c
```c
#include "parser_type.h"

t_error		qualify_6a(void *parser, const char *token_value)
{
	if (str_cmp("in", token_value) == 0)
		((t_parser *)parser)->lookahead_symbol = SYM_In;
	else
		((t_parser *)parser)->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}

```

./srcs/3_builder/2_parser/1_qualifiers/6b_qualify.c
```c
#include "parser_type.h"

t_error		qualify_6b(void *parser, const char *token_value)
{
	if (str_cmp("in", token_value) == 0)
		((t_parser *)parser)->lookahead_symbol = SYM_In;
	else if (str_cmp("do", token_value) == 0)
		((t_parser *)parser)->lookahead_symbol = SYM_Do;
	else
		((t_parser *)parser)->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}

```

./srcs/3_builder/2_parser/1_qualifiers/7a_qualify.c
```c
#include "parser_type.h"
#include "qualifiers_priv.h"

t_error		qualify_7a(void *parser, const char *token_value)
{
	t_parser	*parser_;

	parser_ = (t_parser *)parser;
	if (qualify_try_reserved_word(token_value, &parser_->lookahead_symbol))
		return (error(ERR_NO));
	return (qualify_7b(parser, token_value));
}

```

./srcs/3_builder/2_parser/1_qualifiers/7b_qualify.c
```c
#include "parser_type.h"
#include "qualifiers_priv.h"
#include "utils.h"
#include <stdlib.h>

// TODO: Ask to Alexander to implement it in scanner's token module
static bool	token_contains_unquoted_equal(const char *token)
{
	(void)token;
	// TODO: "If the TOKEN contains an unquoted (as determined while applying rule 4 from 2.3 Token Recognition) <equals-sign> character that is not part of an embedded parameter expansion, command substitution, or arithmetic expansion construct (as determined while applying rule 5 from 2.3 Token Recognition):"
	return (false);
}

t_error		qualify_7b(void *parser, const char *token_value)
{
	t_parser	*parser_;
	char		*name;
	char		*value;
	t_error		err;

	parser_ = (t_parser *)parser;
	if (token_contains_unquoted_equal(token_value) && token_value[0] != '=')
	{
		/*
		* TODO:
		* 	assignment_split() should follow these POSIX conditions:
		*		"If the TOKEN contains an unquoted (as determined while applying rule 4 from 2.3 Token Recognition) <equals-sign> character that is not part of an embedded parameter expansion, command substitution, or arithmetic expansion construct (as determined while applying rule 5 from 2.3 Token Recognition):"
		*/
		err = assignment_split(token_value, &name, &value);
		if (err.type != ERR_NO)
			return (err);
		if (name_is_valid(name) && !parser_->assignment_disabled)
			parser_->lookahead_symbol = SYM_ASSIGNMENT_WORD;
		else
			parser_->lookahead_symbol = SYM_WORD;
		free(name);
		if (value)
			free(value);
	}
	else
		parser_->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}

```

./srcs/3_builder/2_parser/1_qualifiers/8_qualify.c
```c
#include "parser_type.h"
#include "qualifiers_priv.h"

# include "utils.h"	// DEBUG
# include <stdio.h>	// DEBUG
t_error		qualify_8(void *parser, const char *token_value)
{
	t_parser	*parser_;

	parser_ = (t_parser *)parser;
	fprintf(stderr, "[QUALIFIER 8] value=%s valid_name=%d disabled_assign=%d\n",
		token_value,
		name_is_valid(token_value),
		parser_->assignment_disabled);
	if (qualify_try_reserved_word(token_value, &parser_->lookahead_symbol))
		return (error(ERR_NO));
	else if (qualify_try_name(token_value, &parser_->lookahead_symbol))
		return (error(ERR_NO));
	return (qualify_7a(parser, token_value));
}

```

./srcs/3_builder/2_parser/1_qualifiers/build_table.c
```c
#include "lr_machine_type.h"
#include "parser_type.h"
#include "rule_state_type.h"
#include "lr_state_type.h"
#include "qualifiers_priv.h"
#include <stdlib.h>

// TODO: split in multiple_files

/* ---------- DEBUG (START) ---------- */

# include <stdio.h>	// DEBUG

static inline size_t	qualifier_current_priority(t_qualifier_id qualifier_id)
{
	if (qualifier_id == QUALIFIER_7A || qualifier_id == QUALIFIER_7B)
		return (7);
	else if (qualifier_id == QUALIFIER_6A || qualifier_id == QUALIFIER_6B)
		return (6);
	return (0);
}

static inline void	detect_qualifier_conflict(t_qualifier_id current, t_qualifier_id new)
{
	size_t	current_priority;

	if (current == new)
		return ;
	current_priority = qualifier_current_priority(current);
	if (current_priority == 0)
		return ;
	if (qualifier_current_priority(new) == current_priority)
	{
		fprintf(stderr, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		fprintf(stderr, "[ERROR] conflict of qualifiers %zu\n", current_priority);
		fprintf(stderr, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	}
}

/* ---------- DEBUG (END) ---------- */

static inline bool	should_apply_qualifier_word(
	t_lr_machine *machine,
	size_t lr_state_id)
{
	return (machine->actions[lr_state_id][SYM_WORD].type != ACTION_ERROR);
}

static inline bool should_apply_qualifier_1(
	t_lr_machine *machine,
	size_t lr_state_id)
{
	if (machine->actions[lr_state_id][SYM_WORD].type != ACTION_ERROR)
		return (false);
	if (machine->actions[lr_state_id][SYM_NAME].type != ACTION_ERROR)
		return (false);
	if (machine->actions[lr_state_id][SYM_ASSIGNMENT_WORD].type != ACTION_ERROR)
		return (false);
	return (true);
}

static inline bool	rule_is_at_target(
	t_rule_state *rule_state,
	t_rule_id rule_id,
	size_t target_pos)
{
	return (rule_state->rule_id == rule_id && rule_state->pos == target_pos);
}

static inline t_qualifier_id	qualifier_default_id(
	t_lr_machine *machine,
	t_rule_state *rule_state)
{
	t_rule	*rule;

	rule = &machine->rules[rule_state->rule_id];
	if (rule_state->pos >= rule->rhs_len)
		return (QUALIFIER_NONE);
	if (rule->rhs[rule_state->pos] == SYM_WORD)
		return (QUALIFIER_WORD);
	return (QUALIFIER_NONE);
}

static inline t_qualifier_id	qualifier_6_choose_variant(
	t_lr_machine *machine,
	size_t lr_state_id)
{
	t_lr_state		*lr_state;
	t_rule_state	*rule_state;
	t_rule			*rule;
	size_t			i;

	lr_state = &((t_lr_state *)machine->lr_states.data)[lr_state_id];
	i = 0;
	while (i < lr_state->len)
	{
		rule_state = &((t_rule_state *)lr_state->data)[i];
		rule = &machine->rules[rule_state->rule_id];
		if (rule_state->pos < rule->rhs_len)
		{
			if (rule->lhs == SYM_case_clause && rule->rhs[rule_state->pos] == SYM_in)
				return (QUALIFIER_6A);
			else if (rule->lhs == SYM_for_clause && rule->rhs[rule_state->pos] == SYM_in)
				return (QUALIFIER_6B);
			else if (rule->lhs == SYM_for_clause && rule->rhs[rule_state->pos] == SYM_do_group)
				return (QUALIFIER_6B);
		}
		i++;
	}
	return (QUALIFIER_NONE);
}

static inline t_qualifier_id	qualifiers_get_id(
	t_lr_machine *machine,
	size_t lr_state_id,
	t_rule_state *rule_state)
{
	// if (rule_is_at_target(rule_state, RULE_FNAME_1, 0))
	// 	return (QUALIFIER_8);
	if (rule_is_at_target(rule_state, RULE_CMD_NAME_1, 0))
		return (QUALIFIER_7A);
	else if (rule_is_at_target(rule_state, RULE_CMD_WORD_1, 0))
		return (QUALIFIER_7B);
	else if (rule_is_at_target(rule_state, RULE_IN_1, 0))
		return (qualifier_6_choose_variant(machine, lr_state_id));
	else if (rule_is_at_target(rule_state, RULE_DO_GROUP_1, 0))
		return (qualifier_6_choose_variant(machine, lr_state_id));
	else if (rule_is_at_target(rule_state, RULE_NAME_1, 0))
		return (QUALIFIER_5);
	else if (rule_is_at_target(rule_state, RULE_PATTERN_LIST_1, 0))
		return (QUALIFIER_4);
	else if (rule_is_at_target(rule_state, RULE_HERE_END_1, 0))
		return (QUALIFIER_3);
	else if (rule_is_at_target(rule_state, RULE_PATTERN_LIST_2, 1))
		return (QUALIFIER_WORD);
	else if (rule_is_at_target(rule_state, RULE_PATTERN_LIST_3, 2))
		return (QUALIFIER_WORD);
	else if (rule_is_at_target(rule_state, RULE_FILENAME_1, 0))
		return (QUALIFIER_2);
	return (qualifier_default_id(machine, rule_state));
}

static inline void	qualifiers_set_entry_func(
	t_parser *parser,
	t_lr_machine *machine,
	size_t lr_state_id,
	t_qualifier_id qualifier_id)
{
	parser->qualifiers[lr_state_id] = NULL;
	// if (qualifier_id == QUALIFIER_8)
	// 	parser->qualifiers[lr_state_id] = qualify_8;
	if (qualifier_id == QUALIFIER_7A)
		parser->qualifiers[lr_state_id] = qualify_7a;
	else if (qualifier_id == QUALIFIER_7B)
		parser->qualifiers[lr_state_id] = qualify_7b;
	else if (qualifier_id == QUALIFIER_6A)
		parser->qualifiers[lr_state_id] = qualify_6a;
	else if (qualifier_id == QUALIFIER_6B)
		parser->qualifiers[lr_state_id] = qualify_6b;
	else if (qualifier_id == QUALIFIER_5)
		parser->qualifiers[lr_state_id] = qualify_5;
	else if (qualifier_id == QUALIFIER_4)
		parser->qualifiers[lr_state_id] = qualify_4;
	else if (qualifier_id == QUALIFIER_3)
		parser->qualifiers[lr_state_id] = qualify_word;
	else if (qualifier_id == QUALIFIER_WORD)
		parser->qualifiers[lr_state_id] = qualify_word;
	else if (qualifier_id == QUALIFIER_2)
		parser->qualifiers[lr_state_id] = qualify_2;
	else if (should_apply_qualifier_word(machine, lr_state_id))
		parser->qualifiers[lr_state_id] = qualify_word;
	else if (should_apply_qualifier_1(machine, lr_state_id))
		parser->qualifiers[lr_state_id] = qualify_1;
}

static inline void	qualifiers_build_entry(
	t_parser *parser,
	t_lr_machine *machine,
	size_t lr_state_id)
{
	t_lr_state		*lr_state;
	t_rule_state	*rule_state;
	size_t			i;
	t_qualifier_id	qualifier_id;
	t_qualifier_id	curr_qualifier_id;

	lr_state = &((t_lr_state *)machine->lr_states.data)[lr_state_id];
	qualifier_id = QUALIFIER_NONE;
	i = 0;
	while (i < lr_state->len)
	{
		rule_state = &((t_rule_state *)lr_state->data)[i];
		curr_qualifier_id = qualifiers_get_id(machine, lr_state_id, rule_state);
		detect_qualifier_conflict(qualifier_id, curr_qualifier_id);
		if (curr_qualifier_id > qualifier_id)
			qualifier_id = curr_qualifier_id;
		i++;
	}
	qualifiers_set_entry_func(parser, machine, lr_state_id, qualifier_id);
}

t_error	qualifiers_build_table(t_parser *parser, t_lr_machine *machine)
{
	size_t		state_count;
	size_t		lr_state_id;

	state_count = machine->lr_states.len;
	parser->qualifiers = malloc(state_count * sizeof(*parser->qualifiers));
	if (!parser->qualifiers)
		return (error_sys());
	lr_state_id = 0;
	while (lr_state_id < state_count)
	{
		qualifiers_build_entry(parser, machine, lr_state_id);
		lr_state_id++;
	}
	return (error(ERR_NO));
}

```

./srcs/3_builder/2_parser/1_qualifiers/qualifiers_priv.h
```c
#ifndef QUALIFIERS_PRIV_H
# define QUALIFIERS_PRIV_H

# include "error.h"
# include "symbols_type.h"
# include <stddef.h>

/*
* @note Qualifier 3 is partially applied via reduce_hook hook_3()
* @note Qualifier 9 is applied via reduce_hooks hook_9_increment() and hook_9_decrement()
*/
typedef enum qualifier_id
{
	QUALIFIER_NONE,
	QUALIFIER_WORD,
	QUALIFIER_1,
	QUALIFIER_2,
	QUALIFIER_3,
	QUALIFIER_4,
	QUALIFIER_5,
	QUALIFIER_6A,
	QUALIFIER_6B,
	QUALIFIER_7A,
	QUALIFIER_7B,
	QUALIFIER_8,
	QUALIFIER_COUNT
}	t_qualifier_id;

bool		qualify_try_reserved_word(
	const char *token_value,
	t_symbol *dst_symbol);
bool		qualify_try_name(const char *token_value, t_symbol *dst_symbol);
t_error		qualify_word(void *parser, const char *token_value);
t_error		qualify_1(void *parser, const char *token_value);
t_error		qualify_2(void *parser, const char *token_value);
t_error		qualify_4(void *parser, const char *token_value);
t_error		qualify_5(void *parser, const char *token_value);
t_error		qualify_6a(void *parser, const char *token_value);
t_error		qualify_6b(void *parser, const char *token_value);
t_error		qualify_7a(void *parser, const char *token_value);
t_error		qualify_7b(void *parser, const char *token_value);
t_error		qualify_8(void *parser, const char *token_value);

#endif

```

./srcs/3_builder/2_parser/1_qualifiers/qualifiers_type.h
```c
#ifndef QUALIFIERS_TYPE_H
# define QUALIFIERS_TYPE_H

# include "error.h"
# include <stddef.h>

typedef t_error		(*t_qualifier)(void *parser, const char *token_value);

#endif

```

./srcs/3_builder/2_parser/1_qualifiers/qualifiers.h
```c
#ifndef QUALIFIERS_H
# define QUALIFIERS_H

# include "lr_machine_type.h"
# include "parser_type.h"
# include "token.h"

t_error	qualifiers_build_table(t_parser *parser, t_lr_machine *machine);
t_error	parser_qualify_symbol(
	t_parser *parser,
	size_t lr_state_id,
	t_token	*token);

#endif

```

./srcs/3_builder/2_parser/1_qualifiers/qualify.c
```c
#include "parser_type.h"
#include "token.h"
#include <stdlib.h>

// # include "debug.h"	// DEBUG
t_error	parser_qualify_symbol(
	t_parser *parser,
	size_t lr_state_id,
	t_token	*token)
{
	char	*token_value;
	t_error	err;

	err = error(ERR_NO);
	parser->lookahead_symbol = parser->lookahead_raw_symbol;
	if (parser->lookahead_symbol != SYM_TOKEN)
	{
		// fprintf(stderr, "=> %s\n", symbol_to_string(parser->lookahead_symbol));
		return (err);
	}
	token_value = buff_get_string(&token->value);
	if (!token_value)
		return (error_print(error_sys(), "parser", __func__,
			"unable to get token value", NULL, NULL));
	if (parser->qualifiers[lr_state_id])
	{
		// fprintf(stderr, "[QUALIFIER RUN] state=%zu raw=%s value=%s qualifier=%p\n",
		// 	lr_state_id,
		// 	symbol_to_string(parser->lookahead_raw_symbol),
		// 	token_value,
		// 	parser->qualifiers[lr_state_id]);
		err = parser->qualifiers[lr_state_id](parser, token_value);
		// fprintf(stderr, "[QUALIFIER RUN] state=%zu result=%s\n",
		// 	lr_state_id,
		// 	symbol_to_string(parser->lookahead_symbol));
	}
	free(token_value);
	// fprintf(stderr, "=> %s\n", symbol_to_string(parser->lookahead_symbol));
	return (err);
}

```

./srcs/3_builder/2_parser/2_build.c
```c
#include "qualifiers.h"
# include "logs.h"

t_error	parser_build_qualifiers_table(t_parser *parser, t_lr_machine *machine)
{
	t_error	err;

	print_title(__func__, "()");
	err = qualifiers_build_table(parser, machine);
	print_pass("qualifiers table built       (entries: %zu)\n", machine->lr_states.len);
	print_result(__func__, "()");
	return (err);
}

```

./srcs/3_builder/2_parser/2_stack/parser_stack_type.h
```c
#ifndef PARSER_STACK_TYPE_H
# define PARSER_STACK_TYPE_H

# include "libft.h"
# include "cst_type.h"
# include "symbols_type.h"
# include <stddef.h>

typedef struct s_parser_stack_item
{
	t_symbol	symbol;
	size_t		lr_state_id;
	size_t		tokens_start_id;
	size_t		tokens_count;
	t_cst_node	*cst_node;
}	t_parser_stack_item;

// vector of t_parser_stack_item
typedef t_vector	t_parser_stack;

#endif

```

./srcs/3_builder/2_parser/2_stack/parser_stack.c
```c
#include "parser_stack_type.h"

void	parser_stack_init(t_parser_stack *stack)
{
	vector_init(stack, sizeof(t_parser_stack_item), 0);
}

t_parser_stack_item	*parser_stack_top(t_parser_stack *stack)
{
	if (stack->len == 0)
		return (NULL);
	return ((t_parser_stack_item *)stack->data + (stack->len - 1));
}

bool	parser_stack_push(t_parser_stack *stack, t_parser_stack_item *item)
{
	return (vector_push(stack, item));
}

bool	parser_stack_pop(t_parser_stack *stack, t_parser_stack_item *dst)
{
	return (vector_pop(stack, dst));
}

void	parser_stack_free(t_parser_stack *stack)
{
	vector_free(stack, NULL);
}

```

./srcs/3_builder/2_parser/3_cst/7_cst.c
```c
#include "error.h"
#include "parser_stack_type.h"
#include "cst_type.h"
#include <stdlib.h>

static inline t_error	cst_node_set_children(
	t_cst_node *node,
	t_parser_stack_item *rhs,
	size_t rhs_len)
{
	size_t	i;

	node->child_count = rhs_len;
	if (node->child_count == 0)
	{
		node->children = NULL;
		return (error(ERR_NO));
	}
	node->children = malloc(node->child_count * sizeof(*node->children));
	if (!node->children)
		return (error_sys());
	i = 0;
	while (i < node->child_count)
	{
		node->children[i] = rhs[i].cst_node;
		rhs[i].cst_node = NULL;
		i++;
	}
	return (error(ERR_NO));
}

t_error	cst_node_new(
	t_parser_stack_item *lhs,
	t_parser_stack_item *rhs,
	size_t rhs_len,
	t_rule_id rule_id)
{
	t_cst_node	*node;
	t_error		err;

	node = malloc(sizeof(*node));
	if (!node)
		return (error_sys());
	err = cst_node_set_children(node, rhs, rhs_len);
	if (err.type)
		return (free(node), err);
	node->symbol = lhs->symbol;
	node->rule_id = rule_id;
	node->tokens_start_id = lhs->tokens_start_id;
	node->tokens_count = lhs->tokens_count;
	node->data = NULL;
	node->free_func = NULL;
	lhs->cst_node = node;
	return (error(ERR_NO));
}

static inline void	cst_node_free_data(t_cst_node *node)
{
	if (!node->data)
		return ;
	if (node->free_func)
		node->free_func(node->data);
	else
		free(node->data);
	node->data = NULL;
}

void	cst_node_set_data(t_cst_node *node, void *data, t_cst_free_data free_f)
{
	if (node->data)
		cst_node_free_data(node);
	node->data = data;
	node->free_func = free_f;
}


void	cst_node_free(t_cst_node **node)
{
	t_cst_node	*tmp;
	size_t		i;

	if (!node || !*node)
		return ;
	tmp = *node;
	i = 0;
	while (i < tmp->child_count)
		cst_node_free(&tmp->children[i++]);
	free(tmp->children);
	cst_node_free_data(tmp);
	free(tmp);
	*node = NULL;
}

```

./srcs/3_builder/2_parser/3_cst/cst_type.h
```c
#ifndef CST_TYPE_H
# define CST_TYPE_H

# include "symbols_type.h"
# include "rules__type.h"
# include <stddef.h>

typedef void	(*t_cst_free_data)(void *data);

typedef struct s_cst_node
{
	t_symbol			symbol;
	t_rule_id			rule_id;
	size_t				tokens_start_id;
	size_t				tokens_count;
	struct s_cst_node	**children;
	size_t				child_count;
	void				*data;
	t_cst_free_data		free_func;
}	t_cst_node;

#endif

```

./srcs/3_builder/2_parser/3_cst/cst.h
```c
#ifndef CST_H
# define CST_H

# include "parser_stack_type.h"

t_error	cst_node_new(
	t_parser_stack_item *lhs,
	t_parser_stack_item *rhs,
	size_t rhs_len,
	t_rule_id rule_id);
void	cst_node_set_data(t_cst_node *node, void *data, t_cst_free_data free_f);
void	cst_node_free(t_cst_node **node);

#endif

```

./srcs/3_builder/2_parser/3_read.c
```c
#include "parser_priv.h"
#include "scanner.h"

static inline t_error	sym_conv1(t_token_type token_type, t_symbol *dst_symbol)
{
	if (token_type == TOKEN_TOKEN)
		*dst_symbol = SYM_TOKEN;
	else if (token_type == TOKEN_NEWLINE)
		*dst_symbol = SYM_NEWLINE;
	else if (token_type == TOKEN_SCOLON)
		*dst_symbol = SYM_SEMI;
	else if (token_type == TOKEN_AMPERSAND)
		*dst_symbol = SYM_AMPERSAND;
	else if (token_type == TOKEN_DSEMI)
		*dst_symbol = SYM_DSEMI;
	else if (token_type == TOKEN_SEMI_AND)
		*dst_symbol = SYM_SEMI_AND;
	else if (token_type == TOKEN_AND_IF)
		*dst_symbol = SYM_AND_IF;
	else if (token_type == TOKEN_OR_IF)
		*dst_symbol = SYM_OR_IF;
	else if (token_type == TOKEN_PIPE)
		*dst_symbol = SYM_PIPE;
	else if (token_type == TOKEN_LPARENTHESIS)
		*dst_symbol = SYM_LPARENTHESIS;
	else if (token_type == TOKEN_RPARENTHESIS)
		*dst_symbol = SYM_RPARENTHESIS;
	else
		return (error(ERR_INVALID_SYNTAX));
	return (error(ERR_NO));
}

static inline t_error	sym_conv2(t_token_type token_type, t_symbol *dst_symbol)
{
	if (token_type == TOKEN_LESSAND)
		*dst_symbol = SYM_LESSAND;
	else if (token_type == TOKEN_GREATAND)
		*dst_symbol = SYM_GREATAND;
	else if (token_type == TOKEN_LESS)
		*dst_symbol = SYM_LESS;
	else if (token_type == TOKEN_GREAT)
		*dst_symbol = SYM_GREAT;
	else if (token_type == TOKEN_CLOBBER)
		*dst_symbol = SYM_CLOBBER;
	else if (token_type == TOKEN_LESSGREAT)
		*dst_symbol = SYM_LESSGREAT;
	else if (token_type == TOKEN_DGREAT)
		*dst_symbol = SYM_DGREAT;
	else if (token_type == TOKEN_DLESS)
		*dst_symbol = SYM_DLESS;
	else if (token_type == TOKEN_DLESSDASH)
		*dst_symbol = SYM_DLESSDASH;
	else if (token_type == TOKEN_IO_NUMBER)
		*dst_symbol = SYM_IO_NUMBER;
	else if (token_type == TOKEN_EOF)
		*dst_symbol = SYM_EOF;
	else
		return (error(ERR_INVALID_SYNTAX));
	return (error(ERR_NO));
}

static t_error	symbol_convert(t_token *src_token, t_symbol *dst_symbol)
{
	t_error			err;
	t_token_type	token_type;

	token_type = src_token->type;
	err = sym_conv1(token_type, dst_symbol);
	if (err.type != ERR_NO)
		err = sym_conv2(token_type, dst_symbol);
	if (err.type != ERR_NO)
	{
		*dst_symbol = SYM_error;
		return (error_print(
			error(ERR_INVALID_SYNTAX),
			"parser",
			"unkown token type",
			NULL,
			"%i", token_type));
	}
	return (err);
}

# include <stdio.h>		// DEBUG
# include "logs.h"		// DEBUG
# include <stdlib.h>	// DEBUG
t_error	parser_read_next_symbol(t_parser *parser)
{
	t_token	token;
	t_error	err;

	err = scanner_get_next_token(&token);
	if (err.type != ERR_NO)
		return (err);
	if (!vector_push(&parser->tokens, &token))
		return (token_free(&token), parser_internal_error());
	err = symbol_convert(&token, &parser->lookahead_raw_symbol);
	if (err.type != ERR_NO)
		return (err);
	parser->lookahead_symbol = parser->lookahead_raw_symbol;
	parser->lookahead_id = parser->tokens.len - 1;
	// fprintf(stderr, "\n--------------------------------------------------\n");
	char *token_value = buff_get_string(&token.value);
	fprintf(stderr, "[PARSER] READ   => [%3zu] %s%s%s",
		parser->lookahead_id, RED, token_type_to_string(token.type), NC);
	if (token.type == TOKEN_TOKEN)
		fprintf(stderr, " (%s%s%s)", BLUE, token_value, NC);
	fprintf(stderr, "\n");
	free(token_value);
	// fprintf(stderr, "[PARSER] READ index=%zu token=%s symbol=%s value=%s\n",
	// 	parser->lookahead_id,
	// 	token_type_to_string(token.type),
	// 	symbol_to_string(parser->lookahead_raw_symbol),
	// 	buff_get_string(&token.value));
	// fprintf(stderr, "--------------------------------------------------\n");
	return (error(ERR_NO));
}

```

./srcs/3_builder/2_parser/4_shift.c
```c
#include "parser_priv.h"
#include "cst.h"

# include <stdio.h>
t_error	parser_shift(t_parser *parser, size_t lr_state_id)
{
	t_parser_stack_item	item;
	t_error			err;

	err = parser_read_heredoc(parser);
	if (err.type)
		return (err);
	item.symbol = parser->lookahead_symbol;
	item.lr_state_id = lr_state_id;
	item.tokens_start_id = parser->lookahead_id;
	item.tokens_count = 1;
	err = cst_node_new(&item, NULL, 0, RULE_NONE);
	if (err.type != ERR_NO)
		return (err);
	// fprintf(stderr, "[PARSER] SHIFT symbol=%s to_state=%zu token_start=%zu token_count=%zu\n",
	// 	symbol_to_string(item.symbol),
	// 	item.lr_state_id,
	// 	item.tokens_start_id,
	// 	item.tokens_count);
	if (!vector_push(&parser->stack, &item))
	{
		cst_node_free(&item.cst_node);
		return (parser_internal_error());
	}
	return (parser_read_next_symbol(parser));
}

```

./srcs/3_builder/2_parser/5_reduce.c
```c
#include "parser_priv.h"
#include "goto.h"
#include "cst.h"

static inline t_error	parser_new_lr_state(
	t_parser *parser,
	t_lr_machine *machine,
	t_rule *rule,
	size_t *dst)
{
	t_parser_stack		*stack;
	size_t				previous_item_id;
	t_parser_stack_item	*previous_item;
	size_t				lr_state_from;
	size_t				lr_state_to;

	stack = &parser->stack;
	previous_item_id = stack->len - rule->rhs_len - 1;
	previous_item = &((t_parser_stack_item *)stack->data)[previous_item_id];
	lr_state_from = previous_item->lr_state_id;
	lr_state_to = machine->gotos[lr_state_from][rule->lhs - SYM_NON_TERMINAL_MIN];
	if (lr_state_to == GOTO_EMPTY)
		return (error_print(error(ERR_PARSER_EMPTY_GOTO), "parser", NULL, NULL));
	*dst = lr_state_to;
	return (error(ERR_NO));
}

static inline size_t	parser_tokens_count_sum(
	t_parser_stack_item *rhs_items,
	size_t count)
{
	size_t				i;
	t_parser_stack_item	*item;
	size_t				token_count;

	token_count = 0;
	i = 0;
	while (i < count)
	{
		item = &rhs_items[i];
		token_count += item->tokens_count;
		i++;
	}
	return (token_count);
}

static t_error	parser_replace_items(
	t_parser			*parser,
	size_t 				count,
	t_parser_stack_item	*item)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (!parser_stack_pop(&parser->stack, NULL))
			return (parser_internal_error());
		i++;
	}
	if (!parser_stack_push(&parser->stack, item))
		return (parser_internal_error());
	return (error(ERR_NO));
}

# include <stdio.h>
t_error	parser_reduce(t_parser *parser, t_lr_machine *machine, size_t rule_id)
{
	t_rule				*rule;
	size_t				rhs_start;
	t_parser_stack_item	*rhs;
	t_parser_stack_item	item;
	t_error				err;

	rule = &machine->rules[rule_id];
	rhs_start = parser->stack.len - rule->rhs_len;
	rhs = &((t_parser_stack_item *)parser->stack.data)[rhs_start];
	item.symbol = rule->lhs;
	err = parser_new_lr_state(parser, machine, rule, &item.lr_state_id);
	if (err.type != ERR_NO)
		return (err);
	item.tokens_start_id = parser->lookahead_id;
	if (rule->rhs_len > 0)
		item.tokens_start_id = rhs[0].tokens_start_id;
	item.tokens_count = parser_tokens_count_sum(rhs, rule->rhs_len);
	// fprintf(stderr, "[PARSER] REDUCE rule=%zu lhs=%s goto=%zu rhs_len=%zu token_start=%zu token_count=%zu\n",
	// 	rule_id,
	// 	symbol_to_string(item.symbol),
	// 	item.lr_state_id,
	// 	rule->rhs_len,
	// 	item.tokens_start_id,
	// 	item.tokens_count);
	// fprintf(stderr, "[PARSER] REDUCE => %s [", symbol_to_string(item.symbol));
	// for (size_t i = 0; i < rule->rhs_len; i++)
	// {
	// 	fprintf(stderr, "%s", symbol_to_string(rhs[i].symbol));
	// 	if (i < rule->rhs_len - 1)
	// 		fprintf(stderr, " ");
	// 	// fprintf(stderr, "[PARSER] RHS[%zu] symbol=%s state=%zu token_start=%zu token_count=%zu\n",
	// 	// 	i,
	// 	// 	symbol_to_string(rhs[i].symbol),
	// 	// 	rhs[i].lr_state_id,
	// 	// 	rhs[i].tokens_start_id,
	// 	// 	rhs[i].tokens_count);
	// }
	// fprintf(stderr, "]\n");
	item.cst_node = NULL;
	err = cst_node_new(&item, rhs, rule->rhs_len, (t_rule_id)rule_id);
	if (err.type == ERR_NO && rule->hook)
		err = rule->hook(parser, rhs, rule->rhs_len, &item);
	if (err.type == ERR_NO)
		err = parser_replace_items(parser, rule->rhs_len, &item);
	if (err.type != ERR_NO)
		cst_node_free(&item.cst_node);
	return (err);
}

```

./srcs/3_builder/2_parser/6_cmd_name_word.c
```c
#include "parser_type.h"
#include "lr_machine_type.h"
#include "lr_state_type.h"
#include "rule_state_type.h"
#include "goto.h"
#include <stdlib.h>

// @ret ERR_LIBC
static inline t_error	get_lr_state_ids_from_stack(
	t_parser *parser,
	t_vector *dst)
{
	size_t				i;
	t_parser_stack_item	*item;

	if (!vector_init(dst, sizeof(size_t), parser->stack.len))
		return (error_sys());
	i = 0;
	while (i < parser->stack.len)
	{
		item = &((t_parser_stack_item *)parser->stack.data)[i];
		if (!vector_push(dst, &item->lr_state_id))
			return (vector_free(dst, NULL), error_sys());
		i++;
	}
	return (error(ERR_NO));
}

static inline bool	state_expects_cmd_name_or_word(
	t_lr_machine *machine,
	size_t lr_state_id)
{
	t_lr_state		*state;
	t_rule_state	*item;
	t_rule			*rule;
	size_t			i;

	state = &((t_lr_state *)machine->lr_states.data)[lr_state_id];
	i = 0;
	while (i < state->len)
	{
		item = &((t_rule_state *)state->data)[i];
		rule = &machine->rules[item->rule_id];
		if ((rule->lhs == SYM_cmd_name || rule->lhs == SYM_cmd_word)
			&& item->pos < rule->rhs_len
			&& rule->rhs[item->pos] == SYM_WORD)
			return (true);
		i++;
	}
	return (false);
}

// @ret ERR_PARSER_INVALID_STATE / ERR_PARSER_EMPTY_GOTO / ERR_LIBC
static inline t_error	simulate_reduction(
	t_lr_machine *machine,
	t_vector *lr_state_ids,
	size_t rule_id)
{
	t_rule	*rule;
	size_t	lr_state_from;
	size_t	lr_state_to;

	rule = &machine->rules[rule_id];
	if (rule->rhs_len >= lr_state_ids->len)
		return (error_print(error(ERR_PARSER_INVALID_STATE), "parser",
			"unable to simulate reduction", NULL, NULL));
	lr_state_ids->len -= rule->rhs_len;
	lr_state_from = ((size_t *)lr_state_ids->data)[lr_state_ids->len - 1];
	lr_state_to = machine->gotos[lr_state_from][rule->lhs - SYM_NON_TERMINAL_MIN];
	if (lr_state_to == GOTO_EMPTY)
		return (error_print(error(ERR_PARSER_EMPTY_GOTO), "parser",
			"unable to simulate reduction", NULL, NULL));
	if (!vector_push(lr_state_ids, &lr_state_to))
		return (error_sys());
	return (error(ERR_NO));
}

static inline t_error	free_and_return(t_vector *vector, t_error_type err_type)
{
	vector_free(vector, NULL);
	return (error(err_type));
}

t_error	parser_can_next_token_be_a_cmd_name_or_word(
	t_parser *parser,
	t_lr_machine *machine,
	bool *dst)
{
	t_vector	lr_state_ids;
	size_t		lr_state_id;
	t_action	*action;
	t_error		err;

	err = get_lr_state_ids_from_stack(parser, &lr_state_ids);
	if (err.type)
		return (err);
	while (true)
	{
		lr_state_id = ((size_t *)lr_state_ids.data)[lr_state_ids.len - 1];
		if (state_expects_cmd_name_or_word(machine, lr_state_id))
			return (*dst = true, free_and_return(&lr_state_ids, ERR_NO));
		action = &machine->actions[lr_state_id][SYM_WORD];
		if (action->type != ACTION_REDUCE)
			return (*dst = false, free_and_return(&lr_state_ids, ERR_NO));
		err = simulate_reduction(machine, &lr_state_ids, action->payload);
		if (err.type)
			break ;
	}
	vector_free(&lr_state_ids, NULL);
	return (err);
}

```

./srcs/3_builder/2_parser/main.c
```c
#include "parser.h"
#include "parser_priv.h"
#include "qualifiers.h"
#include "cst.h"
# include "debug.h"	// DEBUG

static inline t_error	parser_push_initial_state(t_parser *parser)
{
	t_parser_stack_item	item;

	item.symbol = SYM_error;
	item.lr_state_id = 0;
	item.tokens_start_id = 0;
	item.tokens_count = 0;
	item.cst_node = NULL;
	if (!vector_push(&parser->stack, &item))
		return (parser_internal_error());
	return (error(ERR_NO));
}

static inline t_error	parser_prepare_to_build_cst(t_parser *parser)
{
	t_error		err;
	size_t	i;

	i = 0;
	while (i < parser->stack.len)
		parser_free_stack_item(&((t_parser_stack_item *)parser->stack.data)[i++]);
	parser->stack.len = 0;
	err = parser_push_initial_state(parser);
	if (err.type == ERR_NO && parser->lookahead_raw_symbol == SYM_NONE)
		err = parser_read_next_symbol(parser);
	cst_node_free(&parser->cst);
	parser->cst = NULL;
	parser->function_body_depth = 0;
	parser->assignment_disabled = false;
	parser->expansion_disabled = false;
	parser->must_read_heredoc = false;
	return (err);
}

t_error	parser_store_cst(t_parser *parser, t_parser_stack_item *main_item)
{
	fprintf(stderr, "[PARSER] ACCEPT =======> %s%s%s (token_start=%zu token_count=%zu)\n",
		GREEN, symbol_to_string(main_item->symbol), NC,
		main_item->tokens_start_id,
		main_item->tokens_count);
	parser->cst = main_item->cst_node;
	main_item->cst_node = NULL;
	if (parser->lookahead_raw_symbol == SYM_NEWLINE)
		return (parser_read_heredoc(parser));
	return (error(ERR_NO));
}

static inline t_error	parser_accept(t_parser *parser)
{
	t_parser_stack_item	*main_item;

	parser->lookahead_raw_symbol = SYM_NONE;
	parser->lookahead_symbol = SYM_NONE;
	main_item = parser_stack_top(&parser->stack);
	return (parser_store_cst(parser, main_item));
}

t_error	parser_build_cst(t_parser *parser, t_lr_machine *machine)
{
	size_t		lr_state_id;
	t_token		*token;
	t_action	action;
	t_error		err;

	err = parser_prepare_to_build_cst(parser);
	while (err.type == ERR_NO && parser->cst == NULL)
	{
		lr_state_id = parser_stack_top(&parser->stack)->lr_state_id;
		token = &((t_token *)parser->tokens.data)[parser->lookahead_id];
		err = parser_qualify_symbol(parser, lr_state_id, token);
		if (err.type != ERR_NO)
			return (err);
		action = machine->actions[lr_state_id][parser->lookahead_symbol];
		if (action.type == ACTION_ERROR)
			return (parser_invalid_syntax());
		else if (action.type == ACTION_ACCEPT)
			return (parser_accept(parser));
		else if (action.type == ACTION_SHIFT)
			err = parser_shift(parser, action.payload);
		else if (action.type == ACTION_REDUCE)
			err = parser_reduce(parser, machine, action.payload);
	}
	return (err);
}

```

./srcs/3_builder/2_parser/parser_priv.h
```c
#ifndef PARSER_PRIV_H
# define PARSER_PRIV_H

# include "parser_type.h"
# include "lr_machine_type.h"
# include "token.h"

/* ************************************************************************* */
/*                                   ERROR                                   */
/* ************************************************************************* */

t_error	parser_internal_error(void);
t_error	parser_invalid_syntax(void);

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	parser_init(t_parser *parser);
void	parser_free_token(void *token);
void	parser_free_stack_item(void *raw_item);
void	parser_free(t_parser *parser);

/* ************************************************************************* */
/*                                    READ                                   */
/* ************************************************************************* */

t_error	parser_read_next_symbol(t_parser *parser);
t_error	parser_read_heredoc(t_parser *parser);

/* ************************************************************************* */
/*                                   STACK                                   */
/* ************************************************************************* */

# define STACK_INITIAL_CAP	16

void				parser_stack_init(t_parser_stack *stack);
t_parser_stack_item	*parser_stack_top(t_parser_stack *stack);
bool				parser_stack_push(t_parser_stack *stack,
	t_parser_stack_item *item);
bool				parser_stack_pop(t_parser_stack *stack,
	t_parser_stack_item *dst);
void				parser_stack_free(t_parser_stack *stack);

/* ************************************************************************* */
/*                                  ACTIONS                                  */
/* ************************************************************************* */

t_error	parser_shift(t_parser *parser, size_t lr_state_id);
t_error	parser_reduce(t_parser *parser, t_lr_machine *machine, size_t rule_id);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

#include "token.h"

const char	*token_type_to_string(t_token_type token_type);
const char	*symbol_to_string(t_symbol symbol);
const char	*action_type_to_string(t_action_type action_type);

#endif

```

./srcs/3_builder/2_parser/parser_type.h
```c
#ifndef PARSER_TYPE_H
# define PARSER_TYPE_H

# include "libft.h"
# include "qualifiers_type.h"
# include "parser_stack_type.h"

// vector of t_token
typedef t_vector	t_token_list;

typedef struct s_parser
{
	t_parser_stack	stack;
	t_token_list	tokens;
	size_t			lookahead_id;
	t_symbol		lookahead_raw_symbol;
	t_symbol		lookahead_symbol;
	t_cst_node		*cst;
	t_qualifier		*qualifiers;	// [lr_state]
	size_t			function_body_depth;
	bool			assignment_disabled;
	bool			expansion_disabled;
	bool			must_read_heredoc;
}	t_parser;

#endif

```

./srcs/3_builder/2_parser/parser.h
```c
#ifndef PARSER_H
# define PARSER_H

# include "parser_type.h"
# include "lr_machine_type.h"

void	parser_init(t_parser *parser);
t_error	parser_reset(t_parser *parser);
t_error	parser_build_qualifiers_table(t_parser *parser, t_lr_machine *machine);
t_error	parser_build_cst(t_parser *parser, t_lr_machine *machine);
t_error	parser_store_cst(t_parser *parser, t_parser_stack_item *main_item);
t_error	parser_reset(t_parser *parser);
void	parser_free(t_parser *parser);

// @ret ERR_PARSER_INVALID_STATE / ERR_PARSER_EMPTY_GOTO / ERR_LIBC
t_error	parser_can_next_token_be_a_cmd_name_or_word(
	t_parser *parser,
	t_lr_machine *machine,
	bool *dst);

#endif

```

./srcs/3_builder/3_converter/0_cst_helpers.c
```c
#include "parser_type.h"
#include "cst_type.h"
#include "token.h"
#include <stdbool.h>

t_error	converter_get_buff(
	t_parser *parser,
	t_cst_node *node,
	size_t node_token_id,
	t_buff **dst)
{
	t_token	*token;
	size_t	token_id;

	if (node_token_id >= node->tokens_count)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	token_id = node->tokens_start_id + node_token_id;
	token = &((t_token *)parser->tokens.data)[token_id];
	*dst = &token->value;
	return (error(ERR_NO));
}

t_error	converter_dup_buff(
	t_parser *parser,
	t_cst_node *node,
	size_t node_token_id,
	t_buff *dst)
{
	t_buff	*token_buff;
	t_error	err;

	err = converter_get_buff(parser, node, node_token_id, &token_buff);
	if (err.type)
		return (err);
	if (!buff_init(dst, 0, token_buff->data, (long)token_buff->len))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	converter_get_string(
	t_parser *parser,
	t_cst_node *node,
	size_t node_token_id,
	char **dst)
{
	t_buff	*buff;
	t_error	err;

	err = converter_get_buff(parser, node, node_token_id, &buff);
	if (err.type)
		return (err);
	*dst = buff_get_string(buff);
	if (!*dst)
		return (error_sys());
	return (error(ERR_NO));
}

```

./srcs/3_builder/3_converter/1_redirection/1_life_cycle.c
```c
#include "ast_type.h"
#include <stdlib.h>

void	ast_redirection_init(t_ast_redirection *redirection)
{
	redirection->operation = AST_REDIR_COUNT;
	redirection->fd = -1;
	redirection->is_location = false;
	buff_init(&redirection->location, 0, NULL, -1);
	buff_init(&redirection->word, 0, NULL, -1);
	redirection->expand_heredoc_body = false;
}

void	ast_redirection_free(void *redirection)
{
	t_ast_redirection	*redir;

	redir = (t_ast_redirection *)redirection;
	redir->operation = AST_REDIR_COUNT;
	redir->fd = -1;
	redir->is_location = false;
	buff_free(&redir->location);
	buff_free(&redir->word);
	redir->expand_heredoc_body = false;
}

void	ast_redir_list_init(t_ast_redir_list *redir_list)
{
	vector_init(redir_list, sizeof(t_ast_redirection), 0);
}

void	ast_redir_list_free(t_ast_redir_list *redir_list)
{
	vector_free(redir_list, ast_redirection_free);
}

```

./srcs/3_builder/3_converter/1_redirection/2_convert_io_file_or_here.c
```c
#include "converter_priv.h"

static inline t_error	convert_io_operator(
	t_symbol symbol,
	t_ast_redir_op *out_op)
{
	if (symbol == SYM_LESS)
		*out_op = AST_REDIR_READ;
	else if (symbol == SYM_DLESS || symbol == SYM_DLESSDASH)
		*out_op = AST_REDIR_HEREDOC;
	else if (symbol == SYM_LESSAND)
		*out_op = AST_REDIR_DUP_READ;
	else if (symbol == SYM_GREAT)
		*out_op = AST_REDIR_WRITE;
	else if (symbol == SYM_DGREAT)
		*out_op = AST_REDIR_APPEND;
	else if (symbol == SYM_GREATAND)
		*out_op = AST_REDIR_DUP_WRITE;
	else if (symbol == SYM_CLOBBER)
		*out_op = AST_REDIR_CLOBBER;
	else if (symbol == SYM_LESSGREAT)
		*out_op = AST_REDIR_READ_WRITE;
	else
		return (error(ERR_INCOHERENT_STATE));
	return (error(ERR_NO));
}

static inline bool	heredoc_should_expand(t_buff *token_buff)
{
	size_t	i;
	char	c;

	i = 0;
	while (i < token_buff->len)
	{
		c = ((char *)token_buff->data)[i];
		if (c == '\'' || c == '"' || c == '\\')
			return (false);
		i++;
	}
	return (true);
}

static inline t_error	convert_here_end(
	t_parser *parser,
	t_cst_node *here_end,
	t_ast_redirection *out)
{
	t_buff	delim;
	t_error	err;

	err = converter_dup_buff(parser, here_end, 0, &delim);
	if (err.type)
		return (ast_redirection_free(out), err);
	out->expand_heredoc_body = heredoc_should_expand(&delim);
	return (error(ERR_NO));
}

static inline t_error	convert_io_here(
	t_cst_node *io_here,
	t_ast_redirection *out)
{
	t_buff	*heredoc_path;

	heredoc_path = (t_buff *)io_here->data;
	if (!buff_dup_n(&out->word, heredoc_path, heredoc_path->len))
		return (ast_redirection_free(out), error_sys());
	return (error(ERR_NO));
}

/*
io_file          : '<'       filename
                 | LESSAND   filename
                 | '>'       filename
                 | GREATAND  filename
                 | DGREAT    filename
                 | LESSGREAT filename
                 | CLOBBER   filename
                 ;
filename         : WORD
                 ;
io_here          : DLESS     here_end
                 | DLESSDASH here_end
                 ;
here_end         : WORD
*/
t_error	convert_io_file_or_here(
	t_parser *parser,
	t_cst_node *io_file_node,
	t_ast_redirection *out)
{
	t_symbol	symbol;
	t_cst_node	*filename_node;
	t_error		err;

	symbol = io_file_node->children[0]->symbol;
	err = convert_io_operator(symbol, &out->operation);
	if (err.type)
		return (ast_redirection_free(out), err);
	if (out->operation == AST_REDIR_HEREDOC)
	{
		err = convert_io_here(io_file_node, out);
		if (err.type)
			return (err);
		return (convert_here_end(parser, io_file_node->children[1], out));
	}
	filename_node = io_file_node->children[1];
	err = converter_dup_buff(parser, filename_node, 0, &out->word);
	if (err.type)
		ast_redirection_free(out);
	return (err);
}

```

./srcs/3_builder/3_converter/1_redirection/3_convert_one.c
```c
#include "converter_priv.h"
#include "convert_io_priv.h"
#include <stdlib.h>
#include <unistd.h>

static inline int	get_default_fd(t_symbol operator_symbol)
{
	if (operator_symbol == SYM_LESS
		|| operator_symbol == SYM_DLESS
		|| operator_symbol == SYM_DLESSDASH
		|| operator_symbol == SYM_LESSAND
		|| operator_symbol == SYM_LESSGREAT)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

static inline t_error	convert_io_number(
	t_parser *parser,
	t_cst_node *io_number_node,
	t_ast_redirection *out)
{
	t_error	err;
	char	*token_string;

	err = converter_get_string(parser, io_number_node, 0, &token_string);
	if (err.type)
		return (err);
	out->fd = ft_atoi(token_string);
	free(token_string);
	return (error(ERR_NO));
}

static inline t_error	convert_io_location(
	t_parser *parser,
	t_cst_node *io_location_node,
	t_ast_redirection *out)
{
	t_error	err;
	t_buff	*token_buff;
	char	*src;

	err = converter_get_buff(parser, io_location_node, 0, &token_buff);
	if (err.type)
		return (err);
	src = ((char *)token_buff->data) + 1;
	if (!buff_append(&out->location, src, (long)token_buff->len - 2))
		return (error_sys());
	out->is_location = true;
	return (error(ERR_NO));
}

/*
io_redirect      :             io_file
                 | IO_NUMBER   io_file
                 | IO_LOCATION io_file
                 |             io_here
                 | IO_NUMBER   io_here
                 | IO_LOCATION io_here
                 ;
io_file          : '<'       filename
                 | LESSAND   filename
                 | '>'       filename
                 | GREATAND  filename
                 | DGREAT    filename
                 | LESSGREAT filename
                 | CLOBBER   filename
                 ;
filename         : WORD
                 ;
io_here          : DLESS     here_end
                 | DLESSDASH here_end
                 ;
here_end         : WORD
                 ;
*/
t_error	convert_redirection(
	t_parser *parser,
	t_cst_node *io_redirect,
	t_ast_redirection *out)
{
	t_symbol	operator_symbol;
	t_error		err;

	ast_redirection_init(out);
	if (io_redirect->child_count == 1)
	{
		operator_symbol = io_redirect->children[0]->children[0]->symbol;
		out->fd = get_default_fd(operator_symbol);
		return (convert_io_file_or_here(parser, io_redirect->children[0], out));
	}
	else if (io_redirect->children[0]->symbol == SYM_IO_NUMBER)
		err = convert_io_number(parser, io_redirect->children[0], out);
	else
		err = convert_io_location(parser, io_redirect->children[0], out);
	if (err.type)
		return (ast_redirection_free(out), err);
	return (convert_io_file_or_here(parser, io_redirect->children[1], out));
}

t_error	convert_redirection_add(
	t_parser *parser,
	t_cst_node *io_redirect,
	t_ast_redir_list *out)
{
	t_ast_redirection	redir;
	t_error				err;

	err = convert_redirection(parser, io_redirect, &redir);
	if (err.type)
		return (err);
	if (!vector_push(out, &redir))
		return (ast_redirection_free(&redir), error_sys());
	return (error(ERR_NO));
}

```

./srcs/3_builder/3_converter/1_redirection/4_convert_list.c
```c
#include "converter_priv.h"

/*
redirect_list    :               io_redirect
                 | redirect_list io_redirect
                 ;
*/
t_error	convert_redirection_add_list(
	t_parser *parser,
	t_cst_node *redirect_list,
	t_ast_redir_list *out)
{
	size_t				i;
	t_cst_node			*child;
	t_error				err;

	err = error(ERR_NO);
	i = 0;
	while (i < redirect_list->child_count && err.type == ERR_NO)
	{
		child = redirect_list->children[i];
		if (child->symbol == SYM_redirect_list)
			err = convert_redirection_add_list(parser, child, out);
		else if (child->symbol == SYM_io_redirect)
			err = convert_redirection_add(parser, child, out);
		i++;
	}
	return (err);
}

```

./srcs/3_builder/3_converter/1_redirection/convert_io_priv.h
```c
#ifndef CONVERT_IO_PRIV_H
# define CONVERT_IO_PRIV_H

# include "parser_type.h"
# include "ast_type.h"

t_error	convert_io_file_or_here(
	t_parser *parser,
	t_cst_node *io_file_node,
	t_ast_redirection *out);

#endif

```

./srcs/3_builder/3_converter/10_function/1_life_cycle.c
```c
#include "converter_priv.h"
#include <stdlib.h>

void	ast_function_def_init(t_ast_function_def *function_def)
{
	buff_init(&function_def->name, 0, NULL, -1);
	function_def->body = NULL;
	ast_redir_list_init(&function_def->redirs);
}

void	ast_function_def_free(t_ast_function_def *function_def)
{
	buff_free(&function_def->name);
	if (function_def->body)
	{
		ast_command_free(function_def->body);
		free(function_def->body);
		function_def->body = NULL;
	}
	ast_redir_list_free(&function_def->redirs);
}

```

./srcs/3_builder/3_converter/10_function/2_convert.c
```c
#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"
#include <stdlib.h>

/*
function_body    : compound_command
                 | compound_command redirect_list
                 ;
*/
static inline t_error	convert_function_body(
	t_parser *parser,
	t_cst_node *body,
	t_ast_function_def *out)
{
	t_cst_node	*redir;
	t_error		err;

	out->body = malloc(sizeof(*out->body));
	if (!out->body)
		return (error_sys());
	err = convert_compound_command(parser, body->children[0], out->body);
	if (err.type == ERR_NO && body->child_count > 1)
	{
		redir = body->children[1];
		return (convert_redirection_add_list(parser, redir, &out->redirs));
	}
	return (err);
}

/*
function_definition : fname '(' ')' linebreak function_body
                 ;
fname            : NAME
                 ;
*/
t_error	convert_function(
	t_parser *parser,
	t_cst_node *function_definition,
	t_ast_function_def *out)
{
	t_cst_node	*fname;
	t_cst_node	*body;
	t_error		err;

	ast_function_def_init(out);
	fname = function_definition->children[0];
	err = converter_dup_buff(parser, fname, 0, &out->name);
	body = function_definition->children[4];
	if (err.type == ERR_NO)
		err = convert_function_body(parser, body, out);
	if (err.type)
		ast_function_def_free(out);
	return (err);
}

```

./srcs/3_builder/3_converter/11_command/1_life_cycle.c
```c
#include "converter_priv.h"
#include <stdlib.h>

void	ast_command_init(t_ast_command *command)
{
	command->type = AST_CMD_TYPE_COUNT;
	ast_redir_list_init(&command->redirs);
	command->data = (t_ast_command_data){ 0 };
}

static inline void	ast_command_free_data(t_ast_command *command)
{
	if (command->type == AST_CMD_SIMPLE)
		ast_simple_command_free(&command->data.simple);
	else if (command->type == AST_CMD_LIST)
		ast_list_free(&command->data.list);
	else if (command->type == AST_CMD_IF)
		ast_if_free(&command->data.if_clause);
	else if (command->type == AST_CMD_FOR)
		ast_for_free(&command->data.for_clause);
	else if (command->type == AST_CMD_LOOP)
		ast_loop_free(&command->data.loop);
	else if (command->type == AST_CMD_CASE)
		ast_case_free(&command->data.case_clause);
	else if (command->type == AST_CMD_FUNCTION_DEF)
		ast_function_def_free(&command->data.function_def);
}

void	ast_command_free(void *command)
{
	t_ast_command	*cmd;

	cmd = (t_ast_command *)command;
	ast_redir_list_free(&cmd->redirs);
	if (cmd->type < AST_CMD_TYPE_COUNT)
		ast_command_free_data(cmd);
	cmd->type = AST_CMD_TYPE_COUNT;
}

```

./srcs/3_builder/3_converter/11_command/2_convert.c
```c
#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"

/*
brace_group      : Lbrace compound_list Rbrace
                 ;
*/
static inline t_error	convert_to_list(
	t_parser *parser,
	t_cst_node *node,
	t_ast_command *out)
{
	out->type = AST_CMD_LIST;
	if (node->symbol == SYM_brace_group)
		return (convert_list(parser, node->children[1], &out->data.list));
	else if (node->symbol == SYM_subshell)
		return (convert_list(parser, node, &out->data.list));
	return (error(ERR_INCOHERENT_STATE));
}

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
static inline t_error	convert_compound_command_priv(
	t_parser *parser,
	t_cst_node *compound_command,
	t_ast_command *out)
{
	t_cst_node	*child;

	child = compound_command->children[0];
	if (child->symbol == SYM_brace_group || child->symbol == SYM_subshell)
		return (convert_to_list(parser, child, out));
	else if (child->symbol == SYM_for_clause)
	{
		out->type = AST_CMD_FOR;
		return (convert_for(parser, child, &out->data.for_clause));
	}
	else if (child->symbol == SYM_case_clause)
	{
		out->type = AST_CMD_CASE;
		return (convert_case(parser, child, &out->data.case_clause));
	}
	else if (child->symbol == SYM_if_clause)
	{
		out->type = AST_CMD_IF;
		return (convert_if(parser, child, &out->data.if_clause));
	}
	else
	{
		out->type = AST_CMD_LOOP;
		return (convert_loop(parser, child, &out->data.loop));
	}
}

static inline t_error	convert_to_simple(
	t_parser *parser,
	t_cst_node *simple,
	t_ast_command *out)
{
	out->type = AST_CMD_SIMPLE;
	return (convert_simple_command(parser, simple, &out->data.simple));
}

static inline t_error	convert_to_function(
	t_parser *parser,
	t_cst_node *func,
	t_ast_command *out)
{
	out->type = AST_CMD_FUNCTION_DEF;
	return (convert_function(parser, func, &out->data.function_def));
}

t_error	convert_compound_command(
	t_parser *parser,
	t_cst_node *compound_command,
	t_ast_command *out)
{
	t_error		err;

	ast_command_init(out);
	err = error(ERR_NO);
	err = convert_compound_command_priv(parser, compound_command, out);
	if (err.type)
		ast_command_free(out);
	return (err);
}

/*
command          : simple_command
                 | compound_command
                 | compound_command redirect_list
                 | function_definition
                 ;
*/
t_error	convert_command(
	t_parser *parser,
	t_cst_node *command,
	t_ast_command *out)
{
	size_t		i;
	t_cst_node	*child;
	t_error		err;

	ast_command_init(out);
	err = error(ERR_NO);
	i = 0;
	while (i < command->child_count && err.type == ERR_NO)
	{
		child = command->children[i];
		if (child->symbol == SYM_simple_command)
			err = convert_to_simple(parser, child, out);
		else if (child->symbol == SYM_compound_command)
			err = convert_compound_command_priv(parser, child, out);
		else if (child->symbol == SYM_redirect_list)
			err = convert_redirection_add_list(parser, child, &out->redirs);
		else
			err = convert_to_function(parser, child, out);
		i++;
	}
	if (err.type)
		ast_command_free(out);
	return (err);
}

```

./srcs/3_builder/3_converter/2_simple_command/1_life_cycle.c
```c
#include "ast_type.h"
#include "converter_priv.h"
#include <stdlib.h>

void	ast_simple_command_init(t_ast_simple_command *simple_command)
{
	vector_init(&simple_command->assignments, sizeof(t_buff), 0);
	vector_init(&simple_command->words, sizeof(t_buff), 0);
	ast_redir_list_init(&simple_command->redirs);
}

void	ast_simple_command_free(void *simple_command)
{
	t_ast_simple_command	*cmd;

	cmd = (t_ast_simple_command *)simple_command;
	vector_free(&cmd->assignments, buff_free_void);
	vector_free(&cmd->words, buff_free_void);
	ast_redir_list_free(&cmd->redirs);
}

```

./srcs/3_builder/3_converter/2_simple_command/2_convert.c
```c
#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"

static inline t_error	add_buff_to(
	t_parser *parser,
	t_cst_node *node,
	t_vector *out)
{
	t_buff	token_value;
	t_error	err;

	err = converter_dup_buff(parser, node, 0, &token_value);
	if (err.type)
		return (err);
	if (!vector_push(out, &token_value))
		return (buff_free(&token_value), error_sys());
	return (error(ERR_NO));
}

static inline t_error	parse_rec(
	t_parser *parser,
	t_cst_node *node,
	t_ast_simple_command *out)
{
	size_t		i;
	t_cst_node	*child;
	t_error		err;

	err = error(ERR_NO);
	i = 0;
	while (i < node->child_count && err.type == ERR_NO)
	{
		child = node->children[i];
		if (child->symbol == SYM_io_redirect)
			err = convert_redirection_add(parser, child, &out->redirs);
		else if (child->symbol == SYM_cmd_name
			|| child->symbol == SYM_cmd_word
			|| child->symbol == SYM_WORD)
			err = add_buff_to(parser, child, &out->words);
		else if (child->symbol == SYM_ASSIGNMENT_WORD)
			err = add_buff_to(parser, child, &out->assignments);
		else
			err = parse_rec(parser, child, out);
		i++;
	}
	return (err);
}

/*
simple_command   : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
                 ;
cmd_prefix       :            io_redirect
                 | cmd_prefix io_redirect
                 |            ASSIGNMENT_WORD
                 | cmd_prefix ASSIGNMENT_WORD
                 ;
cmd_name         : WORD
                 ;
cmd_word         : WORD
                 ;
cmd_suffix       :            io_redirect
                 | cmd_suffix io_redirect
                 |            WORD
                 | cmd_suffix WORD
                 ;
*/
t_error	convert_simple_command(
	t_parser *parser,
	t_cst_node *simple_command,
	t_ast_simple_command *out)
{
	t_error		err;

	ast_simple_command_init(out);
	err = parse_rec(parser, simple_command, out);
	if (err.type)
		ast_simple_command_free(out);
	return (err);
}

```

./srcs/3_builder/3_converter/3_pipeline/1_life_cycle.c
```c
#include "converter_priv.h"
#include <stdlib.h>

void	ast_pipeline_init(t_ast_pipeline *pipeline)
{
	(void)vector_init(&pipeline->commands, sizeof(t_ast_command), 0);
	pipeline->negated = false;
}

void	ast_pipeline_free(void *pipeline)
{
	t_ast_pipeline	*pipe;

	pipe = (t_ast_pipeline *)pipeline;
	vector_free(&pipe->commands, ast_command_free);
	pipe->negated = false;
}

```

./srcs/3_builder/3_converter/3_pipeline/2_convert.c
```c
#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"

static inline t_error	add_command(
	t_parser *parser,
	t_cst_node *node,
	t_ast_pipeline *out)
{
	t_ast_command	command;
	t_error			err;

	err = convert_command(parser, node, &command);
	if (err.type)
		return (err);
	if (!vector_push(&out->commands, &command))
		return (ast_command_free(&command), error_sys());
	return (error(ERR_NO));
}

static inline t_error	parse_rec(
	t_parser *parser,
	t_cst_node *node,
	t_ast_pipeline *out)
{
	size_t		i;
	t_cst_node	*child;
	t_error		err;

	err = error(ERR_NO);
	i = 0;
	while (i < node->child_count && err.type == ERR_NO)
	{
		child = node->children[i];
		if (child->symbol == SYM_pipe_sequence)
			err = parse_rec(parser, child, out);
		else if (child->symbol == SYM_command)
			err = add_command(parser, child, out);
		else if (child->symbol == SYM_Bang)
			out->negated = true;
		i++;
	}
	return (err);
}

/*
pipeline         :      pipe_sequence
                 | Bang pipe_sequence
                 ;
pipe_sequence    :                             command
                 | pipe_sequence '|' linebreak command
                 ;
*/
t_error	convert_pipeline(
	t_parser *parser,
	t_cst_node *pipeline,
	t_ast_pipeline *out)
{
	t_error		err;

	ast_pipeline_init(out);
	err = parse_rec(parser, pipeline, out);
	if (err.type)
		ast_pipeline_free(out);
	return (err);
}

```

./srcs/3_builder/3_converter/4_and_or/1_life_cycle.c
```c
#include "converter_priv.h"
#include <stdlib.h>

void	ast_and_or_init(t_ast_and_or *and_or)
{
	vector_init(&and_or->pipelines, sizeof(t_ast_pipeline), 0);
	vector_init(&and_or->next_on_success, sizeof(bool), 0);
}

void	ast_and_or_free(void *and_or)
{
	t_ast_and_or	*and_or_node;

	and_or_node = (t_ast_and_or *)and_or;
	vector_free(&and_or_node->pipelines, ast_pipeline_free);
	vector_free(&and_or_node->next_on_success, NULL);
}

```

./srcs/3_builder/3_converter/4_and_or/2_convert.c
```c
#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"

static inline t_error	add_pipeline(
	t_parser *parser,
	t_cst_node *node,
	t_ast_and_or *out)
{
	t_ast_pipeline	pipeline;
	t_error			err;

	err = convert_pipeline(parser, node, &pipeline);
	if (err.type)
		return (err);
	if (!vector_push(&out->pipelines, &pipeline))
		return (ast_pipeline_free(&pipeline), error_sys());
	return (error(ERR_NO));
}

static inline t_error	add_operator(bool operator, t_ast_and_or *out)
{
	if (!vector_push(&out->next_on_success, &operator))
		return (error_sys());
	return (error(ERR_NO));
}

static inline t_error	parse_rec(
	t_parser *parser,
	t_cst_node *and_or,
	t_ast_and_or *out)
{
	size_t		i;
	t_cst_node	*child;
	t_error		err;

	err = error(ERR_NO);
	i = 0;
	while (i < and_or->child_count && err.type == ERR_NO)
	{
		child = and_or->children[i];
		if (child->symbol == SYM_and_or)
			err = parse_rec(parser, child, out);
		else if (child->symbol == SYM_pipeline)
			err = add_pipeline(parser, child, out);
		else if (child->symbol == SYM_AND_IF)
			err = add_operator(true, out);
		else if (child->symbol == SYM_OR_IF)
			err = add_operator(false, out);
		i++;
	}
	return (err);
}

/*
and_or           :                         pipeline
                 | and_or AND_IF linebreak pipeline
                 | and_or OR_IF  linebreak pipeline
                 ;
*/
t_error	convert_and_or(
	t_parser *parser,
	t_cst_node *and_or,
	t_ast_and_or *out)
{
	t_error		err;

	ast_and_or_init(out);
	err = parse_rec(parser, and_or, out);
	if (err.type)
		ast_and_or_free(out);
	return (err);
}

```

./srcs/3_builder/3_converter/5_list/1_life_cycle.c
```c
#include "converter_priv.h"
#include <stdlib.h>

void	ast_list_init(t_ast_list *list)
{
	vector_init(&list->and_ors, sizeof(t_ast_and_or), 0);
	vector_init(&list->asyncs, sizeof(bool), 0);
	list->subshell = false;
}

void	ast_list_free(void *list)
{
	t_ast_list	*list_node;

	list_node = (t_ast_list *)list;
	vector_free(&list_node->and_ors, ast_and_or_free);
	vector_free(&list_node->asyncs, NULL);
	list_node->subshell = false;
}

void	ast_root_init(t_ast_root *root)
{
	ast_list_init(root);
}

void	ast_root_free(t_ast_root *root)
{
	ast_list_free(root);
}


```

./srcs/3_builder/3_converter/5_list/2_convert.c
```c
#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"

static inline t_error	add_and_or(
	t_parser *parser,
	t_cst_node *node,
	t_ast_list *out)
{
	t_ast_and_or	and_or;
	t_error			err;
	bool			default_async;

	err = convert_and_or(parser, node, &and_or);
	if (err.type)
		return (err);
	if (!vector_push(&out->and_ors, &and_or))
		return (ast_and_or_free(&and_or), error_sys());
	default_async = false;
	if (!vector_push(&out->asyncs, &default_async))
		return (error_sys());
	return (error(ERR_NO));
}

static inline void	set_last_async(bool async, t_ast_list *out)
{
	bool	*raw_asyncs;

	if (async == false)
		return ;
	raw_asyncs = (bool *)out->asyncs.data;
	raw_asyncs[out->and_ors.len - 1] = async;
}

// input = compound_list / complete_command / list
static inline t_error	parse_rec(
	t_parser *parser,
	t_cst_node *node,
	t_ast_list *out)
{
	size_t		i;
	t_cst_node	*child;
	t_error		err;

	err = error(ERR_NO);
	i = 0;
	while (i < node->child_count && err.type == ERR_NO)
	{
		child = node->children[i];
		if (child->symbol == SYM_list
			|| child->symbol == SYM_term
			|| child->symbol == SYM_separator)
			err = parse_rec(parser, child, out);
		else if (child->symbol == SYM_and_or)
			err = add_and_or(parser, child, out);
		else if (child->symbol == SYM_separator_op)
			set_last_async(child->children[0]->symbol == SYM_AMPERSAND, out);
		i++;
	}
	return (err);
}

t_error	convert_list_add(
	t_parser *parser,
	t_cst_node *node,
	t_ast_list *out)
{
	t_error		err;

	if (node->symbol == SYM_subshell)
	{
		out->subshell = true;
		err = parse_rec(parser, node->children[1], out);
	}
	else
		err = parse_rec(parser, node, out);
	if (err.type)
		ast_list_free(out);
	return (err);
}

/*
subshell         : '(' compound_list ')'
                 ;
compound_list    : linebreak term
                 | linebreak term separator
                 ;
term             : term separator and_or
                 |                and_or
                 ;
complete_command : list separator_op
                 | list
                 ;
list             : list separator_op and_or
                 |                   and_or
                 ;
separator        : separator_op linebreak
                 | newline_list
                 ;
separator_op     : '&'
                 | ';'
                 ;
*/
// input = subshell / compound_list / complete_command
t_error	convert_list(
	t_parser *parser,
	t_cst_node *node,
	t_ast_list *out)
{
	ast_list_init(out);
	return (convert_list_add(parser, node, out));
}

```

./srcs/3_builder/3_converter/6_if/1_life_cycle.c
```c
#include "converter_priv.h"
#include <stdlib.h>

void	ast_if_init(t_ast_if *if_node)
{
	vector_init(&if_node->conditions, sizeof(t_ast_list), 0);
	vector_init(&if_node->bodies, sizeof(t_ast_list), 0);
	ast_list_init(&if_node->else_body);
	if_node->has_else = false;
}

void	ast_if_free(t_ast_if *if_node)
{
	vector_free(&if_node->conditions, ast_list_free);
	vector_free(&if_node->bodies, ast_list_free);
	ast_list_free(&if_node->else_body);
	if_node->has_else = false;
}

```

./srcs/3_builder/3_converter/6_if/2_convert.c
```c
#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"

static inline t_error	add_to_list(
	t_parser *parser,
	t_cst_node *compound_list,
	t_vector *out)
{
	t_ast_list	list;
	t_error		err;

	err = convert_list(parser, compound_list, &list);
	if (err.type)
		return (err);
	if (!vector_push(out, &list))
		return (ast_list_free(&list), error_sys());
	return (error(ERR_NO));
}

static inline t_error	parse_rec(
	t_parser *parser,
	t_cst_node *node,
	t_ast_if *out)
{
	t_error	err;

	if (node->child_count == 2)
	{
		out->has_else = true;
		return (convert_list(parser, node->children[1], &out->else_body));
	}
	err = add_to_list(parser, node->children[1], &out->conditions);
	if (err.type == ERR_NO)
		err = add_to_list(parser, node->children[3], &out->bodies);
	if (err.type)
		return (err);
	if (node->child_count >= 5 && node->children[4]->symbol == SYM_else_part)
		return (parse_rec(parser, node->children[4], out));
	return (err);
}

/*
if_clause        : If compound_list Then compound_list else_part Fi
                 | If compound_list Then compound_list           Fi
                 ;
else_part        : Elif compound_list Then compound_list
                 | Elif compound_list Then compound_list else_part
                 | Else compound_list
                 ;
*/
t_error	convert_if(
	t_parser *parser,
	t_cst_node *if_clause,
	t_ast_if *out)
{
	t_error		err;

	ast_if_init(out);
	err = parse_rec(parser, if_clause, out);
	if (err.type)
		ast_if_free(out);
	return (err);
}

```

./srcs/3_builder/3_converter/7_for/1_life_cycle.c
```c
#include "converter_priv.h"
#include <stdlib.h>

void	ast_for_init(t_ast_for *for_node)
{
	(void)buff_init(&for_node->var_name, 0, NULL, -1);
	vector_init(&for_node->words, sizeof(t_buff), 0);
	ast_list_init(&for_node->body);
}

void	ast_for_free(t_ast_for *for_node)
{
	buff_free(&for_node->var_name);
	vector_free(&for_node->words, buff_free_void);
	ast_list_free(&for_node->body);
}

```

./srcs/3_builder/3_converter/7_for/2_convert.c
```c
#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"

static inline t_error	add_word(
	t_parser *parser,
	t_cst_node *word,
	t_ast_for *out)
{
	t_buff	token_value;
	t_error	err;

	err = converter_dup_buff(parser, word, 0, &token_value);
	if (err.type)
		return (err);
	if (!vector_push(&out->words, &token_value))
		return (buff_free(&token_value), error_sys());
	return (err);
}

/*
wordlist         : wordlist WORD
                 |          WORD
                 ;
*/
static inline t_error	convert_wordlist(
	t_parser *parser,
	t_cst_node *wordlist,
	t_ast_for *out)
{
	t_error	err;

	if (wordlist->child_count == 1)
		return (add_word(parser, wordlist->children[0], out));
	err = convert_wordlist(parser, wordlist->children[0], out);
	if (err.type)
		return (err);
	return (add_word(parser, wordlist->children[1], out));
}

/*
do_group         : Do compound_list Done
                 ;
*/
static inline t_error	convert_do_group(
	t_parser *parser,
	t_cst_node *do_group,
	t_ast_for *out)
{
	return (convert_list(parser, do_group->children[1], &out->body));
}

static inline t_error	convert_for_clause(
	t_parser *parser,
	t_cst_node *for_clause,
	t_ast_for *out)
{
	t_buff		default_word;
	t_cst_node	*do_group;
	t_error		err;

	err = converter_dup_buff(parser, for_clause->children[1], 0, &out->var_name);
	if (err.type)
		return (err);
	if (for_clause->child_count <= 4)
	{
		if (!buff_init(&default_word, 0, "\"$@\"", -1))
			return (error_sys());
		if (!vector_push(&out->words, &default_word))
			return (buff_free(&default_word), error_sys());
	}
	if (for_clause->child_count == 7)
		err = convert_wordlist(parser, for_clause->children[5], out);
	if (err.type)
		return (err);
	do_group = for_clause->children[for_clause->child_count - 1];
	return (convert_do_group(parser, do_group, out));
}

/*
for_clause       : For name                                      do_group
                 | For name                       sequential_sep do_group
                 | For name linebreak in          sequential_sep do_group
                 | For name linebreak in wordlist sequential_sep do_group
                 ;
name             : NAME
                 ;
in               : In
                 ;
*/
t_error	convert_for(
	t_parser *parser,
	t_cst_node *for_clause,
	t_ast_for *out)
{
	t_error		err;

	ast_for_init(out);
	err = convert_for_clause(parser, for_clause, out);
	if (err.type)
		ast_for_free(out);
	return (err);
}

```

./srcs/3_builder/3_converter/8_loop/1_life_cycle.c
```c
#include "converter_priv.h"
#include <stdlib.h>

void	ast_loop_init(t_ast_loop *loop)
{
	ast_list_init(&loop->condition);
	ast_list_init(&loop->body);
	loop->condition_must_be_true = false;
}

void	ast_loop_free(t_ast_loop *loop)
{
	ast_list_free(&loop->condition);
	ast_list_free(&loop->body);
	loop->condition_must_be_true = false;
}

```

./srcs/3_builder/3_converter/8_loop/2_convert.c
```c
#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"

/*
while_clause     : While compound_list do_group
                 ;
until_clause     : Until compound_list do_group
                 ;
do_group         : Do compound_list Done
                 ;
*/
t_error	convert_loop(
	t_parser *parser,
	t_cst_node *loop,
	t_ast_loop *out)
{
	t_error		err;

	ast_loop_init(out);
	if (loop->children[0]->symbol == SYM_While)
		out->condition_must_be_true = true;
	err = convert_list(parser, loop->children[1], &out->condition);
	if (err.type == ERR_NO)
		err = convert_list(parser, loop->children[2]->children[1], &out->body);
	if (err.type)
		ast_loop_free(out);
	return (err);
}

```

./srcs/3_builder/3_converter/9_case/1_life_cycle.c
```c
#include "converter_priv.h"
#include <stdlib.h>

void	ast_case_init(t_ast_case *case_node)
{
	(void)buff_init(&case_node->word, 0, NULL, -1);
	vector_init(&case_node->patterns, sizeof(t_vector), 0);
	vector_init(&case_node->bodies, sizeof(t_ast_list), 0);
	vector_init(&case_node->fallthrough, sizeof(bool), 0);
}

static void	ast_case_free_pattern(void *pattern)
{
	t_vector	*pattern_vec;

	pattern_vec = (t_vector *)pattern;
	vector_free(pattern_vec, buff_free_void);
}

void	ast_case_free(t_ast_case *case_node)
{
	buff_free(&case_node->word);
	vector_free(&case_node->patterns, ast_case_free_pattern);
	vector_free(&case_node->bodies, ast_list_free);
	vector_free(&case_node->fallthrough, NULL);
}

```

./srcs/3_builder/3_converter/9_case/2_convert.c
```c
#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"

static inline t_error	add_word(
	t_parser *parser,
	t_cst_node *word,
	t_vector *out)
{
	t_buff	token_value;
	t_error	err;

	err = converter_dup_buff(parser, word, 0, &token_value);
	if (err.type)
		return (err);
	if (!vector_push(out, &token_value))
		return (buff_free(&token_value), error_sys());
	return (err);
}

/*
pattern_list     :                  WORD
                 |              '(' WORD
                 | pattern_list '|' WORD
                 ;
*/
static inline t_error	convert_pattern_list(
	t_parser *parser,
	t_cst_node *pattern_list,
	t_vector *out)
{
	t_cst_node	*word;
	t_error		err;

	if (pattern_list->child_count == 3)
	{
		err = convert_pattern_list(parser, pattern_list->children[0], out);
		if (err.type)
			return (err);
	}
	word = pattern_list->children[pattern_list->child_count - 1];
	return (add_word(parser, word, out));
}

/*
case_item_ns     : pattern_list ')' linebreak
                 | pattern_list ')' compound_list
                 ;
case_item        : pattern_list ')' linebreak     DSEMI linebreak
                 | pattern_list ')' compound_list DSEMI linebreak
                 | pattern_list ')' linebreak     SEMI_AND linebreak
                 | pattern_list ')' compound_list SEMI_AND linebreak
                 ;
*/
static inline t_error	convert_case_item(
	t_parser *parser,
	t_cst_node *case_item,
	t_ast_case *out)
{
	t_vector	pattern_list;
	t_ast_list	list;
	bool		fallthrough;
	t_error		err;

	(void)vector_init(&pattern_list, sizeof(t_buff), 0);
	err = convert_pattern_list(parser, case_item->children[0], &pattern_list);
	if (err.type)
		return (vector_free(&pattern_list, buff_free_void), err);
	if (!vector_push(&out->patterns, &pattern_list))
		return (vector_free(&pattern_list, buff_free_void), error_sys());
	if (case_item->children[2]->symbol == SYM_compound_list)
		err = convert_list(parser, case_item->children[2], &list);
	else
		ast_list_init(&list);
	if (err.type)
		return (err);
	if (!vector_push(&out->bodies, &list))
		return (ast_list_free(&list), error_sys());
	fallthrough = case_item->child_count >= 4
		&& case_item->children[3]->symbol == SYM_SEMI_AND;
	if (!vector_push(&out->fallthrough, &fallthrough))
		return (error_sys());
	return (err);
}

/*
case_list_ns     : case_list case_item_ns
                 |           case_item_ns
                 ;
case_list        : case_list case_item
                 |           case_item
                 ;
*/
static inline t_error	convert_case_list(
	t_parser *parser,
	t_cst_node *case_list,
	t_ast_case *out)
{
	t_error	err;

	if (case_list->child_count > 1)
	{
		err = convert_case_list(parser, case_list->children[0], out);
		if (err.type == ERR_NO)
			err = convert_case_item(parser, case_list->children[1], out);
		return (err);
	}
	return (convert_case_item(parser, case_list->children[0], out));
}

/*
case_clause      : Case WORD linebreak in linebreak case_list    Esac
                 | Case WORD linebreak in linebreak case_list_ns Esac
                 | Case WORD linebreak in linebreak              Esac
                 ;
*/
t_error	convert_case(
	t_parser *parser,
	t_cst_node *case_clause,
	t_ast_case *out)
{
	t_error		err;

	ast_case_init(out);
	err = converter_dup_buff(parser, case_clause->children[1], 0, &out->word);
	if (err.type == ERR_NO && case_clause->child_count == 7)
		err = convert_case_list(parser, case_clause->children[5], out);
	if (err.type)
		ast_case_free(out);
	return (err);
}

```

./srcs/3_builder/3_converter/ast_type.h
```c
#ifndef AST_TYPE_H
# define AST_TYPE_H

# include "libft.h"
# include "error.h"
# include <stddef.h>

/* ************************************************************************* */
/*                                 REDIRECTOR                                */
/* ************************************************************************* */

/* ---------- REDIRECT NODE (IN CONVERTER) ---------- */

typedef enum e_ast_redir_op
{
    AST_REDIR_READ,          // <			SYM_LESS
    AST_REDIR_HEREDOC,       // << / <<-	SYM_DLESS / SYM_DLESSDASH
    AST_REDIR_DUP_READ,      // <&			SYM_LESSAND
    AST_REDIR_WRITE,         // >			SYM_GREAT
    AST_REDIR_APPEND,        // >>			SYM_DGREAT
    AST_REDIR_DUP_WRITE,     // >&			SYM_GREATAND
    AST_REDIR_CLOBBER,       // >|			SYM_CLOBBER
    AST_REDIR_READ_WRITE,    // <>			SYM_LESSGREAT
	AST_REDIR_COUNT
}	t_ast_redir_op;

typedef struct s_ast_redirection
{
	t_ast_redir_op	operation;
	int				fd;					// pre-computed fd
	bool			is_location;
	t_buff			location;			// only if is_location == true
	t_buff			word;				// raw token content / heredoc file path
	bool			expand_heredoc_body;
}	t_ast_redirection;

typedef t_vector	t_ast_redir_list;	// vector of t_ast_redirection

/* ---------- REDIRECTOR MODULE (IN RUNNER) ---------- */

typedef struct s_redir_frame
{
	t_vector	fds;		// vector of int
	t_vector	backup_fds;	// vector of int (-1 if fd was closed before redirection)
}	t_redir_frame;

typedef t_vector	t_redir_stack;

void	redirect_init(t_redir_stack *stack);
t_error	redirect_push(t_redir_stack *stack, t_ast_redir_list *redirections);
t_error	redirect_pop(t_redir_stack *stack);
t_error	redirect_restore(t_redir_stack *stack);
void	redirect_free(t_redir_stack *stack);

/* ************************************************************************* */
/*                                   EXECUTOR                                */
/* ************************************************************************* */

/* ---------- SIMPLE COMMAND NODE (IN CONVERTER) ---------- */

typedef struct s_ast_simple_command
{
	t_vector			assignments;	// vector of t_buff
	t_vector			words;			// vector of t_buff
	t_ast_redir_list	redirs;			// vector of t_ast_redirection
}	t_ast_simple_command;

/* ---------- EXECUTOR (IN RUNNER) ---------- */

t_error	execute(t_ast_simple_command *cmd, int *exit_status);

/* ************************************************************************* */
/*                                    WALKER                                 */
/* ************************************************************************* */

/* ---------- LIST NODE (IN CONVERTER) ---------- */

typedef struct s_ast_pipeline
{
	t_vector	commands; 			// vector of t_ast_command
	bool		negated;
}	t_ast_pipeline;

typedef struct s_ast_and_or
{
	t_vector	pipelines;			// vector of t_ast_pipeline
	t_vector	next_on_success;	// vector of bool (&& (SYM_AND) = true, || (SYM_OR) = false)
}	t_ast_and_or;

typedef struct s_ast_list
{
	t_vector	and_ors;			// vector of t_ast_and_or
	t_vector	asyncs;				// vector of bool (& => true)
	bool		subshell;
}	t_ast_list;

/* ---------- CONTROL NODES (IN CONVERTER) ---------- */

typedef struct s_ast_if
{
	t_vector	conditions;			// vector of t_ast_list
	t_vector	bodies;				// vector of t_ast_list
	bool		has_else;
	t_ast_list	else_body;
}	t_ast_if;

typedef struct s_ast_for
{
	t_buff		var_name;
	t_vector	words;				// vector of t_buff (set to ["@"] if input doesn't contain)
	t_ast_list	body;
}	t_ast_for;

typedef struct s_ast_loop
{
	t_ast_list		condition;
	bool			condition_must_be_true;	// While = true | Until = false
	t_ast_list		body;
}	t_ast_loop;

typedef struct s_ast_case
{
	t_buff		word;				// raw tested word
	t_vector	patterns;			// vector of t_vector(t_buff)
	t_vector	bodies;				// vector of t_ast_list
	t_vector	fallthrough;		// vector of bool
}	t_ast_case;

typedef struct s_ast_command	t_ast_command;

typedef struct s_ast_function_def
{
	t_buff				name;
	t_ast_command		*body;
	t_ast_redir_list	redirs;		// vector of t_ast_redirection
}	t_ast_function_def;

/* ---------- MAIN COMMAND (IN CONVERTER) ---------- */

typedef enum e_ast_command_type
{
	AST_CMD_SIMPLE,
	AST_CMD_LIST,
	AST_CMD_IF,
	AST_CMD_FOR,
	AST_CMD_LOOP,
	AST_CMD_CASE,
	AST_CMD_FUNCTION_DEF,
	AST_CMD_TYPE_COUNT
}	t_ast_command_type;

typedef union u_ast_command_data
{
	t_ast_simple_command	simple;
	t_ast_list				list;
	t_ast_if				if_clause;
	t_ast_for				for_clause;
	t_ast_loop				loop;
	t_ast_case				case_clause;
	t_ast_function_def		function_def;
}	t_ast_command_data;

typedef struct s_ast_command
{
	t_ast_command_type	type;
	t_ast_command_data	data;
	t_ast_redir_list	redirs;		// vector of t_ast_redirection
}	t_ast_command;

typedef t_ast_list	t_ast_root;

/* ---------- WALKER (IN RUNNER) ---------- */

/* --- LIST WALKER (INTERNAL) --- */
t_error	walk_command(t_ast_command *command);
t_error	walk_pipeline(t_ast_pipeline *pipeline);
t_error	walk_and_or(t_ast_and_or *and_or);

/* --- LIST WALKER (PRIVATE) --- */
t_error	walk_list(t_ast_list *list);

/* --- CONTROL WALKER (PRIVATE) --- */
t_error	walk_if(t_ast_if *if_clause);
t_error	walk_for(t_ast_for *for_clause);
t_error	walk_loop(t_ast_loop *loop);
t_error	walk_case(t_ast_case *case_clause);
t_error	walk_func(t_ast_function_def *function_def, t_ast_redir_list *redirs);

/* --- MAIN WALKER (PRIVATE) --- */
t_error walk_ast(t_ast_root *root_ast_node);

#endif

```

./srcs/3_builder/3_converter/converter_priv.h
```c
#ifndef CONVERTER_PRIV_H
# define CONVERTER_PRIV_H

# include "libft.h"
# include "cst_type.h"
# include "ast_type.h"
# include <stdbool.h>

/* ************************************************************************* */
/*                                CST_HELPERS                                */
/* ************************************************************************* */

t_error	converter_get_buff(
	t_parser *parser,
	t_cst_node *node,
	size_t node_token_id,
	t_buff **dst);

t_error	converter_dup_buff(
	t_parser *parser,
	t_cst_node *node,
	size_t node_token_id,
	t_buff *dst);

t_error	converter_get_string(
	t_parser *parser,
	t_cst_node *node,
	size_t node_token_id,
	char **dst);
	
t_error	converter_cst_collect_relevant_children(
	t_cst_node *node,
	t_vector *dst);

/* ************************************************************************* */
/*                                REDIRECTION                                */
/* ************************************************************************* */

void	ast_redirection_init(t_ast_redirection *redirection);
// input = io_redirect
t_error	convert_redirection(
	t_parser *parser,
	t_cst_node *io_redirect,
	t_ast_redirection *out);
void	ast_redirection_free(void *redirection);

void	ast_redir_list_init(t_ast_redir_list *redir_list);
// input = io_redirect
t_error	convert_redirection_add(
	t_parser *parser,
	t_cst_node *io_redirect,
	t_ast_redir_list *out);
// input = redirect_list
t_error	convert_redirection_add_list(
	t_parser *parser,
	t_cst_node *redirect_list,
	t_ast_redir_list *out);
void	ast_redir_list_free(t_ast_redir_list *redir_list);

/* ************************************************************************* */
/*                              SIMPLE_COMMAND                               */
/* ************************************************************************* */

void	ast_simple_command_init(t_ast_simple_command *simple_command);
// input = simple_command
t_error	convert_simple_command(
	t_parser *parser,
	t_cst_node *simple_command,
	t_ast_simple_command *out);
void	ast_simple_command_free(void *simple_command);

/* ************************************************************************* */
/*                                 PIPELINE                                  */
/* ************************************************************************* */

void	ast_pipeline_init(t_ast_pipeline *pipeline);
// input = pipeline
t_error	convert_pipeline(
	t_parser *parser,
	t_cst_node *pipeline,
	t_ast_pipeline *out);
void	ast_pipeline_free(void *pipeline);

/* ************************************************************************* */
/*                                  AND_OR                                   */
/* ************************************************************************* */

void	ast_and_or_init(t_ast_and_or *and_or);
// input = and_or
t_error	convert_and_or(
	t_parser *parser,
	t_cst_node *and_or,
	t_ast_and_or *out);
void	ast_and_or_free(void *and_or);

/* ************************************************************************* */
/*                                   LIST                                    */
/* ************************************************************************* */

void	ast_list_init(t_ast_list *list);
// input = subshell / compound_list / complete_command
t_error	convert_list(
	t_parser *parser,
	t_cst_node *node,
	t_ast_list *out);
// input = subshell / compound_list / complete_command
t_error	convert_list_add(
	t_parser *parser,
	t_cst_node *node,
	t_ast_list *out);
void	ast_list_free(void *list);

/* ************************************************************************* */
/*                                    IF                                     */
/* ************************************************************************* */

void	ast_if_init(t_ast_if *if_node);
// input = if_clause
t_error	convert_if(
	t_parser *parser,
	t_cst_node *if_node,
	t_ast_if *out);
void	ast_if_free(t_ast_if *if_node);

/* ************************************************************************* */
/*                                    FOR                                    */
/* ************************************************************************* */

void	ast_for_init(t_ast_for *for_node);
// input = for_clause
t_error	convert_for(
	t_parser *parser,
	t_cst_node *for_clause,
	t_ast_for *out);
void	ast_for_free(t_ast_for *for_node);

/* ************************************************************************* */
/*                                   LOOP                                    */
/* ************************************************************************* */

void	ast_loop_init(t_ast_loop *loop);
// input = while_clause / until_clause
t_error	convert_loop(
	t_parser *parser,
	t_cst_node *loop,
	t_ast_loop *out);
void	ast_loop_free(t_ast_loop *loop);

/* ************************************************************************* */
/*                                   CASE                                    */
/* ************************************************************************* */

void	ast_case_init(t_ast_case *case_node);
// input = case_clause
t_error	convert_case(
	t_parser *parser,
	t_cst_node *case_clause,
	t_ast_case *out);
void	ast_case_free(t_ast_case *case_node);

/* ************************************************************************* */
/*                                 FUNCTION                                  */
/* ************************************************************************* */

void	ast_function_def_init(t_ast_function_def *function_def);
// input = function_definition
t_error	convert_function(
	t_parser *parser,
	t_cst_node *function_definition,
	t_ast_function_def *out);
void	ast_function_def_free(t_ast_function_def *function_def);

/* ************************************************************************* */
/*                                  COMMAND                                  */
/* ************************************************************************* */

void	ast_command_init(t_ast_command *command);
// input = command
t_error	convert_command(
	t_parser *parser,
	t_cst_node *command,
	t_ast_command *out);
// input = compound_command
t_error	convert_compound_command(
	t_parser *parser,
	t_cst_node *compound_command,
	t_ast_command *out);
void	ast_command_free(void *command);

/* ************************************************************************* */
/*                                   ROOT                                    */
/* ************************************************************************* */

void	ast_root_init(t_ast_root *root);

#endif

```

./srcs/3_builder/3_converter/converter.h
```c
#ifndef CONVERTER_H
# define CONVERTER_H

# include "error.h"
# include "cst_type.h"
# include "ast_type.h"

t_error	convert_cst_to_ast(
	t_parser *parser,
	t_cst_node *cst_root,
	t_ast_root *ast_root);

#endif

```

./srcs/3_builder/3_converter/main.c
```c
#include "error.h"
#include "cst_type.h"
#include "ast_type.h"
#include "converter_priv.h"
#include "builder.h"

static inline t_error	convert_complete_commands(
	t_parser *parser,
	t_cst_node *complete_commands,
	t_ast_root *out)
{
	t_cst_node	*first_node;
	t_error		err;

	first_node = complete_commands->children[0];
	if (complete_commands->child_count == 1)
		return (convert_list_add(parser, first_node, out));
	err = convert_complete_commands(parser, first_node, out);
	if (err.type)
		return (err);
	return (convert_list_add(parser, complete_commands->children[2], out));
}

t_error	convert_cst_to_ast(
	t_parser *parser,
	t_cst_node *cst_root,
	t_ast_root *ast_root)
{
	t_cst_node	*node;
	t_error		err;

	ast_root_init(ast_root);
	node = cst_root;
	if (node->symbol == SYM_start)
		node = node->children[0];
	if (node->symbol == SYM_program)
	{
		if (node->child_count < 2)
			return (error(ERR_NO));
		node = node->children[1];
	}
	if (node->symbol == SYM_complete_commands)
		err = convert_complete_commands(parser, node, ast_root);
	else if (node->symbol == SYM_complete_command)
		err = convert_list_add(parser, node, ast_root);
	else
		return (error(ERR_INCOHERENT_STATE));
	if (err.type)
		ast_root_free(ast_root);
	return (err);
}

```

./srcs/3_builder/cmd_name_word.c
```c
#include "shell.h"
#include "builder.h"
#include "parser.h"

t_error	builder_can_next_word_be_a_cmd_name(bool *dst)
{
	t_builder	*builder;

	builder = shell_get_builder();
	if (!builder)
		return (error(ERR_SHELL_NOT_FOUND));
	return (parser_can_next_token_be_a_cmd_name_or_word(
		&builder->parser,
		&builder->lr_machine,
		dst));
}

```

./srcs/3_builder/main.c
```c
#include "shell.h"
#include "builder.h"
#include "lr_machine.h"
#include "parser.h"
#include "converter.h"

void	builder_init(t_builder *builder)
{
	lr_machine_init(&builder->lr_machine);
	parser_init(&builder->parser);
	// TODO: converter_init(&builder->converter);
}

t_error	builder_load(t_builder *builder)
{
	t_error	err;

	err = lr_machine_build_tables(&builder->lr_machine);
	if (err.type != ERR_NO)
		return (err);
	// TODO: converter_load(&builder->converter);
	return (parser_build_qualifiers_table(
		&builder->parser,
		&builder->lr_machine));
}

# include "debug.h"	// DEBUG
t_error	builder_get_ast(t_ast_root *dst_ast)
{
	t_builder	*builder;
	t_error		err;

	builder = shell_get_builder();
	if (!builder)
		return (error(ERR_SHELL_NOT_FOUND));
	err = parser_build_cst(&builder->parser, &builder->lr_machine);
	if (err.type != ERR_NO)
		return (err);
	fprintf(stderr, "--------------------------------------------------\n");
	fprintf(stderr, "[BUILDER] CST built:\n");
	debug_dump_cst_node(builder->parser.cst);
	fprintf(stderr, "--------------------------------------------------\n");
	convert_cst_to_ast(&builder->parser, builder->parser.cst, dst_ast);
	fprintf(stderr, "[BUILDER] AST built:\n");
	debug_dump_ast(dst_ast);
	fprintf(stderr, "--------------------------------------------------\n");
	return (error(ERR_NO));
}

t_error	builder_reset(void)
{
	t_builder	*builder;

	builder = shell_get_builder();
	if (!builder)
		return (error(ERR_SHELL_NOT_FOUND));
	// TODO: converter_reset(&builder->converter);
	return (parser_reset(&builder->parser));
}

void	builder_free(t_builder *builder)
{
	lr_machine_free(&builder->lr_machine);
	parser_free(&builder->parser);
	// TODO: converter_free(&builder->converter);
}

```

./srcs/4_runner/main.c
```c
#include "error.h"
#include "runner.h"
#include "builder.h"
#include "options.h"
#include <stdbool.h>

void	runner_init(t_runner *runner)
{
	(void)runner;
	// TODO;
}

static bool	runner_continue_on_builder_error(t_runner *runner, t_error err)
{
	(void)runner;
	(void)err;
	// TODO
	return (false);
}

t_error	runner_loop_cycle(t_runner *runner)
{
	t_ast_root	ast_root;
	t_error		err;

	err = builder_get_ast(&ast_root);
	if (err.type != ERR_NO && !runner_continue_on_builder_error(runner, err))
		return (err);
	ast_root_free(&ast_root);
	// TODO: err = walk_ast(&ast_root);
	// TODO: handle non-fatal errors
	// TODO: ast_free_node(&ast_root);
	return (error(ERR_NO));
}

t_error	runner_run(t_runner *runner)
{
	t_error	err;

	if (!option_is_active(OPT_INTERACTIVE))
		return (runner_loop_cycle(runner));
	while (true)
	{
		err = runner_loop_cycle(runner);
		if (err.type)
			return (err);
	}
	return (error(ERR_NO));
}

void	runner_free(t_runner *runner)
{
	(void)runner;
	// TODO
}

```

./srcs/alias/_init.c
```c
#include <stdlib.h>
#include "alias.h"
#include "alias_stack_.h"

void	alias_init(t_alias *state)
{
	*state = (t_alias){0};
	alias_stack_init(&state->stack);
	hashmap_init(&state->map, 0, free);
}

void	alias_free(t_alias *state)
{
	alias_stack_free(&state->stack);
	hashmap_free(&state->map);
	*state = (t_alias){0};
}

```

./srcs/alias/_utils.c
```c
#include <stdlib.h>
#include "alias_.h"
#include "builder.h"
#include "context.h"
#include "alias_stack_.h"

static bool	is_word_containing_quoting(char *word)
{
	size_t	i;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '\'' ||
			is_context_squote_start(word + i) ||
			is_context_dquote_start(word + i) ||
			is_context_dollar_squote_start(word + i))
			return (true);
		i++;
	}
	return (false);
}

static bool	is_valid_alias_name(char *word)
{
	size_t	i;

	i = 0;
	while (word[i] != '\0')
	{
		if (!ft_isalnum(word[i]) &&
			word[i] != '_' &&
			word[i] != '!' &&
			word[i] != '%' &&
			word[i] != ',' &&
			word[i] != '@' &&
			word[i] != '.')
			return (false);
		i++;
	}
	return (true);
}

void	alias_print_all(t_key_value **pairs)
{
	size_t	i;

	if (pairs == NULL)
		return ;
	i = 0;
	while (pairs[i] != NULL)
	{
		if (pairs[i]->value == NULL)
			ft_printf("%s=''\n", pairs[i]->key);
		else
			ft_printf("%s='%s'\n", pairs[i]->key, (char *)pairs[i]->value);
		i++;	
	}
	free(pairs);
}

bool	is_token_alias_expandable(t_alias *state, char *word)
{
	bool	can_next_token_be_a_cmd_name;

	if (is_word_containing_quoting(word))
		return (false);
	else if (!is_valid_alias_name(word))
		return (false);
	else if (!hashmap_contains(&state->map, word))
		return (false);
	else if (alias_stack_contains(&state->stack, word))
		return (false);
	else if (!state->disable_position)
	{
		// TODO: handle error
		(void)builder_can_next_word_be_a_cmd_name(&can_next_token_be_a_cmd_name);
		if (!can_next_token_be_a_cmd_name)
			return (false);
	}
	return (true);
}

void	set_position_for_next_word(t_alias *state, char *expansion)
{
	size_t	expansion_len;
	
	if (expansion == NULL)
		return ;
	expansion_len = str_len(expansion);
	if (expansion != NULL && is_blank(expansion[expansion_len - 1]))
		state->disable_position = true;
	else
		state->disable_position = false;
}

```

./srcs/alias/alias_.h
```c
#ifndef ALIAS__H
# define ALIAS__H

# include "alias.h"

/**
 * @ingroup alias
 * @brief Prints every alias in a NULL-terminated array, then frees it.
 *
 * Prints each pair via alias_print_one() and frees the @p pairs array itself
 * (the pairs remain owned by the map). Does nothing when @p pairs is NULL.
 *
 * @param pairs NULL-terminated array of pairs (owned; freed by this call).
 */
void	alias_print_all(t_key_value **pairs);

/**
 * @ingroup alias
 * @brief Updates the position rule from a just-produced expansion.
 *
 * Sets state->disable_position when @p expansion ends with a blank, so the
 * next word is expanded too (mirroring the shell's trailing-blank rule).
 *
 * @param state Pointer to the alias state (borrowed).
 * @param expansion Expansion text just produced (borrowed), may be NULL.
 */
void	set_position_for_next_word(t_alias *state, char *expansion);

/**
 * @ingroup alias
 * @brief Tests whether a token is eligible for alias expansion.
 *
 * True when @p word is a valid unquoted alias name present in the map, is not
 * already being expanded (absent from the recursion-guard stack) and stands
 * in command position, unless a previous expansion's trailing blank lifted
 * the position requirement.
 *
 * @param state Pointer to the alias state (borrowed).
 * @param word Candidate token text (borrowed).
 * @return true if the token should be expanded, false otherwise.
 */
bool	is_token_alias_expandable(t_alias *state, char *word);

#endif

```

./srcs/alias/API.c
```c
#include <stdlib.h>
#include "shell.h"
#include "alias_.h"
#include "alias_stack_.h"

t_error	alias_on_expansion_end(void)
{
	t_alias	*state;

	state = shell_get_alias();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (state->stack.len == 0)
		return (state->err);
	return (alias_stack_pop(&state->stack), state->err);
}

t_error	alias_print(const char *name)
{
	t_key_value	*pair;
	t_alias		*state;
	t_key_value	**pairs;

	state = shell_get_alias();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (name == NULL)
		return (alias_print_all(hashmap_get_all(&state->map)), state->err);
	else
	{
		pair = hashmap_get(&state->map, name);
		if (pair == NULL)
			return (state->err);
		pairs = malloc(sizeof(t_key_value *) * 2);
		if (pairs == NULL)
			return (state->err = error_sys());
		pairs[0] = pair;
		pairs[1] = NULL;
		return (alias_print_all(pairs), state->err);
	}
}

t_error	alias_remove(const char *name)
{
	t_alias	*state;

	state = shell_get_alias();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (name == NULL)
		return (state->err);
	return (hashmap_remove(&state->map, name), state->err);
}

t_error	alias_add(const char *name, const char *value)
{
	t_alias	*state;
	char	*value_copy;

	state = shell_get_alias();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (name == NULL)
		return (state->err);
	if (value == NULL)
		value_copy = str_dup("");
	else
		value_copy = str_dup(value);
	if (value_copy == NULL)
		return (state->err = error_sys());
	if (!hashmap_put(&state->map, name, (void *)value_copy))
		return (state->err = error_sys()); // check in hashmap failure causes to check if it's error_sys
	return (state->err);
}

t_error	alias_expand_token(char **expansion, t_buff *token_value)
{
	t_alias	*state;
	char	*token_str;

	state = shell_get_alias();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	token_str = buff_get_string(token_value);
	if (token_str == NULL)
		return (state->err = error_sys());
	if (is_token_alias_expandable(state, token_str))
	{
		state->err = alias_stack_push(&state->stack, token_str);
		if (state->err.type)
			return (free(token_str), state->err);
		*expansion = hashmap_get(&state->map, token_str)->value;
		if (*expansion == NULL)
			return (state->err = error(ERR_INCOHERENT_STATE));
		*expansion = str_dup(*expansion);
		if (*expansion == NULL)
			return (state->err = error_sys());
		return (set_position_for_next_word(state, *expansion), state->err);
	}
	return (free(token_str), state->err);
}

```

./srcs/alias/stack/_init.c
```c
#include <stdlib.h>
#include "alias.h"

void	alias_stack_init(t_alias_stack *stack)
{
	vector_init(stack, sizeof(char *), 0);
}

void	alias_stack_free(t_alias_stack *stack)
{
	vector_free(stack, free);
}

```

./srcs/alias/stack/_utils.c
```c
#include <stdlib.h>
#include "alias_stack_.h"

t_error	alias_stack_push(t_alias_stack *stack, char *item)
{
	if (!vector_push(stack, &item))
		return (error_sys());
	return (error(ERR_NO));
}

void	alias_stack_pop(t_alias_stack *stack)
{
	char	*item;

	if (stack->len == 0)
		return ;
	vector_pop(stack, &item);
	if (item != NULL)
		free(item);
}

bool	alias_stack_contains(t_alias_stack *stack, char *word)
{
	size_t	i;

	i = 0;
	while (i < stack->len)
	{
		if (str_ncmp(((char **)stack->data)[i], word, str_len(word) + 1) == 0)
			return (true);
		i++;
	}
	return (false);
}

```

./srcs/alias/stack/alias_stack_.h
```c
#ifndef ALIAS_STACK__H
# define ALIAS_STACK__H

# include "error.h"
# include "alias.h"

/*
 * The t_alias_stack type (a vector of owned alias-name strings) is declared
 * in alias.h; this header documents the operations on it. The stack records
 * the aliases currently being expanded to break expansion recursion.
 */

/**
 * @ingroup alias
 * @brief Initialises an empty expansion stack.
 *
 * @param stack Pointer to the stack to initialise (borrowed).
 */
void	alias_stack_init(t_alias_stack *stack);

/**
 * @ingroup alias
 * @brief Frees the stack and every name it owns.
 *
 * @param stack Pointer to the stack to free (borrowed).
 */
void	alias_stack_free(t_alias_stack *stack);

/**
 * @ingroup alias
 * @brief Pops and frees the top alias name.
 *
 * Does nothing when the stack is empty.
 *
 * @param stack Pointer to the stack (borrowed).
 */
void	alias_stack_pop(t_alias_stack *stack);

/**
 * @ingroup alias
 * @brief Pushes an alias name, taking ownership of @p item.
 *
 * @param stack Pointer to the stack (borrowed).
 * @param item Alias name whose ownership is transferred to the stack.
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	alias_stack_push(t_alias_stack *stack, char *item);

/**
 * @ingroup alias
 * @brief Tests whether an alias name is currently being expanded.
 *
 * @param stack Pointer to the stack (borrowed).
 * @param word Alias name to look for (borrowed).
 * @return true if @p word is on the stack, false otherwise.
 */
bool	alias_stack_contains(t_alias_stack *stack, char *word);

#endif

```

./srcs/builtins/builtins_get.c
```c
#include "libft.h"
#include "builtins.h"
#include "builtins_priv.h"

#define BUILTINS_SPECIAL_COUNT		3	// TODO: 15
#define BUILTINS_NON_SPECIAL_COUNT	0	// TODO: 16

static inline const t_builtin	*builtins_get_specials(void)
{
	static const t_builtin	builtins[BUILTINS_SPECIAL_COUNT] =
	{
		// {"break", break},
		// {"colon", colon},
		// {"continue", continue},
		// {"dot", dot},
		// {"eval", eval},
		// {"exec", exec},
		// {"exit", exit},
		{"export", export},
		{"readonly", readonly},
		// {"return", return},
		// {"set", set},
		// {"shift", shift},
		// {"times", times},
		// {"trap", trap},
		{"unset", unset}
	};

	return (builtins);
}

static inline const t_builtin	*builtins_get_non_specials(void)
{
	static const t_builtin	builtins[BUILTINS_NON_SPECIAL_COUNT] =
	{
		// {"alias", alias},
		// {"bg", bg},
		// {"cd", cd},
		// {"command", command},
		// {"fc", fc},
		// {"fg", fg},
		// {"getopts", getopts},
		// {"hash", hash},
		// {"jobs", jobs},
		// {"kill", kill},
		// {"read", read},
		// {"type", type},
		// {"ulimit", ulimit},
		// {"umask", umask},
		// {"unalias", unalias},
		// {"wait", wait}
	};

	return (builtins);
}

t_builtin_function	builtins_get(const char *name, bool special)
{
	const t_builtin 	*builtins;
	size_t				i;
	size_t				count;

	if (special)
	{
		builtins = builtins_get_specials();
		count = BUILTINS_SPECIAL_COUNT;
	}
	else
	{
		builtins = builtins_get_non_specials();
		count = BUILTINS_NON_SPECIAL_COUNT;
	}
	i = 0;
	while (i < count)
	{
		if (str_cmp(name, builtins[i].name) == 0)
			return (builtins[i].function);
		i++;
	}
	return (NULL);
}

```

./srcs/builtins/builtins_priv.h
```c
#ifndef BUILTINS_PRIV_H
# define BUILTINS_PRIV_H

/* ************************************************************************* */
/*                              SPECIAL BUILTINS                             */
/* ************************************************************************* */

int		export(int argc, char **argv, char **envp);
int		readonly(int argc, char **argv, char **envp);
int		unset(int argc, char **argv, char **envp);

#endif

```

./srcs/builtins/export.c
```c
#include "params.h"
#include "ft_getopt.h"
#include "utils.h"
#include <stdlib.h>

#define EXPORT_USAGE	"-p || name[=word] ..."

// @ret ERR_UNDEFINED_BEHAVIOUR
static t_error export_catch_ub(int argc, char **argv, t_getopt_out *out)
{
	size_t	options_count;
	size_t	operand_count;

	options_count = out->options.len;
	operand_count = (size_t)argc - out->first_operand_index;
	if (options_count == 0 && operand_count == 0)
		return (undefined_behaviour("POSIX: export: DESCRIPTION: When no "
			"arguments are given, the results are unspecified."));
	if (options_count > 0 && operand_count > 0)
	{
		(void)error_print(error(ERR_BUILTIN_INVALID_USAGE), argv[0], EXPORT_USAGE, NULL, NULL);
		return (undefined_behaviour("POSIX: 12.1:8: The use of conflicting "
		"mutually-exclusive arguments produces undefined results."));
	}
	return (error(ERR_NO));
}

// @ret ERR_OPT_INVALID / ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG /
// 		ERR_UNDEFINED_BEHAVIOUR / ERR_LIBC
static t_error	export_process_options(int argc, char **argv, t_getopt_out *out)
{
	t_getopt_in	in;
	t_error		err;

	in.builtin_name = argv[0];
	in.single_delimiter = false;
	in.ub_on_repeated_flags = true;
	in.valid_minus_flags = "p";
	in.valid_plus_flags = NULL;
	in.options_with_arg = NULL;
	in.options_with_arg_count = 0;
	err = ft_getopt(argc, argv, &in, out);
	if (err.type != ERR_NO)
		return (err);
	err = export_catch_ub(argc, argv, out);
	if (err.type != ERR_NO)
	{
		vector_free(&out->options, NULL);
		return (err);
	}
	return (error(ERR_NO));
}

// @ret ERR_ASSIGNMENT_MISSING_NAME / ERR_SHELL_NOT_FOUND /
// 		ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC
static t_error	export_add_one(const char *builtin_name, const char *string)
{
	char	*name;
	char	*value;
	t_error	err;

	err = assignment_split(string, &name, &value);
	if (err.type != ERR_NO)
		return (error_print(err, builtin_name, string, NULL, NULL));
	err = params_set_variable(name, value, true, false);
	if (err.type != ERR_NO)
		(void)error_print(err, builtin_name, string, NULL, NULL);
	free(name);
	if (value)
		free(value);
	return (err);
}

// @ret ERR_ASSIGNMENT_MISSING_NAME / ERR_SHELL_NOT_FOUND /
// 		ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC
static t_error	export_add(size_t first_operand_index, int argc, char **argv)
{
	int		i;
	t_error	last_exit_code;
	t_error	exit_code;

	exit_code = error(ERR_NO);
	i = (int)first_operand_index;
	while (i < argc)
	{
		last_exit_code = export_add_one(argv[0], argv[i++]);
		if (last_exit_code.type != ERR_NO)
			exit_code = last_exit_code;
	}
	return (exit_code);
}

int	export(int argc, char **argv, char **envp)
{
	t_getopt_out	out;
	t_error			exit_code;

	(void)envp;
	exit_code = export_process_options(argc, argv, &out);
	if (exit_code.type == ERR_LIBC)
		return ((int)error_print(exit_code, argv[0], "options parsing failed", NULL, NULL).type);
	if (exit_code.type != ERR_NO)
		return ((int)exit_code.type);
	if (out.options.len > 0)
	{
		exit_code = params_print(PARAMS_PRINT_EXPORT);
		if (exit_code.type != ERR_NO)
			(void)error_print(exit_code, argv[0], "variables write failed", NULL, NULL);
	}
	else
		exit_code = export_add(out.first_operand_index, argc, argv);
	vector_free(&out.options, NULL);
	return ((int)exit_code.type);
}

```

./srcs/builtins/readonly.c
```c
#include "params.h"
#include "ft_getopt.h"
#include "utils.h"
#include <stdlib.h>

#define READONLY_USAGE	"-p || name[=word] ..."

// @ret ERR_UNDEFINED_BEHAVIOUR
static t_error readonly_catch_ub(int argc, char **argv, t_getopt_out *out)
{
	size_t	options_count;
	size_t	operand_count;

	options_count = out->options.len;
	operand_count = (size_t)argc - out->first_operand_index;
	if (options_count == 0 && operand_count == 0)
		return (undefined_behaviour("POSIX: readonly: DESCRIPTION: When no "
			"arguments are given, the results are unspecified."));
	if (options_count > 0 && operand_count > 0)
	{
		(void)error_print(error(ERR_BUILTIN_INVALID_USAGE), argv[0], READONLY_USAGE, NULL, NULL);
		return (undefined_behaviour("POSIX: 12.1:8: The use of conflicting "
		"mutually-exclusive arguments produces undefined results."));
	}
	return (error(ERR_NO));
}

// @ret ERR_OPT_INVALID / ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG /
// 		ERR_UNDEFINED_BEHAVIOUR / ERR_LIBC
static t_error	readonly_process_options(int argc, char **argv, t_getopt_out *out)
{
	t_getopt_in	in;
	t_error		err;

	in.builtin_name = argv[0];
	in.single_delimiter = false;
	in.ub_on_repeated_flags = true;
	in.valid_minus_flags = "p";
	in.valid_plus_flags = NULL;
	in.options_with_arg = NULL;
	in.options_with_arg_count = 0;
	err = ft_getopt(argc, argv, &in, out);
	if (err.type != ERR_NO)
		return (err);
	err = readonly_catch_ub(argc, argv, out);
	if (err.type != ERR_NO)
	{
		vector_free(&out->options, NULL);
		return (err);
	}
	return (error(ERR_NO));
}

// @ret ERR_ASSIGNMENT_MISSING_NAME / ERR_SHELL_NOT_FOUND /
// 		ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC
static t_error	readonly_add_one(const char *builtin_name, const char *string)
{
	char	*name;
	char	*value;
	t_error	err;

	err = assignment_split(string, &name, &value);
	if (err.type != ERR_NO)
		return (error_print(err, builtin_name, string, NULL, NULL));
	err = params_set_variable(name, value, false, true);
	if (err.type != ERR_NO)
		(void)error_print(err, builtin_name, string, NULL, NULL);
	free(name);
	if (value)
		free(value);
	return (err);
}

// @ret ERR_ASSIGNMENT_MISSING_NAME / ERR_SHELL_NOT_FOUND /
// 		ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC
static t_error	readonly_add(size_t first_operand_index, int argc, char **argv)
{
	int		i;
	t_error	last_exit_code;
	t_error	exit_code;

	exit_code = error(ERR_NO);
	i = (int)first_operand_index;
	while (i < argc)
	{
		last_exit_code = readonly_add_one(argv[0], argv[i++]);
		if (last_exit_code.type != ERR_NO)
			exit_code = last_exit_code;
	}
	return (exit_code);
}

int	readonly(int argc, char **argv, char **envp)
{
	t_getopt_out	out;
	t_error			exit_code;

	(void)envp;
	exit_code = readonly_process_options(argc, argv, &out);
	if (exit_code.type == ERR_LIBC)
		return ((int)error_print(exit_code, argv[0], "options parsing failed", NULL, NULL).type);
	if (exit_code.type != ERR_NO)
		return ((int)exit_code.type);
	if (out.options.len > 0)
	{
		exit_code = params_print(PARAMS_PRINT_READONLY);
		if (exit_code.type != ERR_NO)
			(void)error_print(exit_code, argv[0], "variables write failed", NULL, NULL);
	}
	else
		exit_code = readonly_add(out.first_operand_index, argc, argv);
	vector_free(&out.options, NULL);
	return ((int)exit_code.type);
}

```

./srcs/builtins/unset.c
```c
#include "params.h"
#include "ft_getopt.h"
#include <stdbool.h>

#define UNSET_USAGE	"[-f|-v] name..."

static bool	unset_has_option(t_getopt_out *out, char flag)
{
	t_getopt_option	*option;
	size_t			i;

	i = 0;
	while (i < out->options.len)
	{
		option = &((t_getopt_option *)out->options.data)[i];
		if (option->flag == flag)
			return (true);
		i++;
	}
	return (false);
}

// @ret ERR_OPT_INVALID / ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG /
// 		ERR_UNDEFINED_BEHAVIOUR / ERR_LIBC
static t_error	unset_process_options(int argc, char **argv, t_getopt_out *out)
{
	t_getopt_in	in;
	t_error		err;

	in.builtin_name = argv[0];
	in.single_delimiter = false;
	in.ub_on_repeated_flags = true;
	in.valid_minus_flags = "fv";
	in.valid_plus_flags = NULL;
	in.options_with_arg = NULL;
	in.options_with_arg_count = 0;
	err = ft_getopt(argc, argv, &in, out);
	if (err.type != ERR_NO)
		return (err);
	if (out->options.len > 1)
	{
		(void)error_print(error(ERR_BUILTIN_INVALID_USAGE), argv[0], UNSET_USAGE, NULL, NULL);
		vector_free(&out->options, NULL);
		return (undefined_behaviour("POSIX: 12.1:8: The use of conflicting "
			"mutually-exclusive arguments produces undefined results."));
	}
	return (error(ERR_NO));
}

// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_SHELL_NOT_FOUND /
// 		ERR_INDEX_OUT_OF_BOUND
static t_error	unset_var(size_t first_operand_index, int argc, char **argv)
{
	int		i;
	t_error	last_exit_code;
	t_error	exit_code;

	exit_code = error(ERR_NO);
	i = (int)first_operand_index;
	while (i < argc)
	{
		last_exit_code = params_unset_variable(argv[i]);
		if (last_exit_code.type != ERR_NO)
		{
			(void)error_print(last_exit_code, argv[0], argv[i], NULL, NULL);
			exit_code = last_exit_code;
		}
		i++;
	}
	return (exit_code);
}

static t_error	unset_fun(size_t first_operand_index, int argc, char **argv)
{
	// TODO
	(void)first_operand_index;
	(void)argc;
	(void)argv;
	return (error(ERR_NO));
}

int	unset(int argc, char **argv, char **envp)
{
	t_getopt_out	out;
	t_error			exit_code;

	(void)envp;
	exit_code = unset_process_options(argc, argv, &out);
	if (exit_code.type == ERR_LIBC)
		return ((int)error_print(exit_code, argv[0], "options parsing failed", NULL, NULL).type);
	if (exit_code.type != ERR_NO)
		return ((int)exit_code.type);
	if (unset_has_option(&out, 'f'))
		exit_code = unset_fun(out.first_operand_index, argc, argv);
	else
		exit_code = unset_var(out.first_operand_index, argc, argv);
	vector_free(&out.options, NULL);
	return ((int)exit_code.type);
}

```

./srcs/debug.c
```c
#include "debug.h"
#include "symbols_type.h"
#include "action_type.h"
#include "token.h"
#include "lr_machine_type.h"
#include "lr_state_type.h"
#include "rule_state_type.h"
#include "cst_type.h"
#include "ast_type.h"

#include <stdio.h>
#include <stdbool.h>

/* ************************************************************************* */
/*                                   BOOL                                    */
/* ************************************************************************* */

const char	*bool_to_string(bool value)
{
	if (value)
		return ("true");
	return ("false");
}

/* ************************************************************************* */
/*                                   TOKEN                                   */
/* ************************************************************************* */

const char	*token_type_to_string(t_token_type token_type)
{
	switch (token_type)
	{
		case TOKEN_NONE: return ("NONE");
		case TOKEN_TOKEN: return ("TOKEN");
		case TOKEN_NEWLINE: return ("NEWLINE");
		case TOKEN_SCOLON: return ("SCOLON");
		case TOKEN_AMPERSAND: return ("AMPERSAND");
		case TOKEN_DSEMI: return ("DSEMI");
		case TOKEN_SEMI_AND: return ("SEMI_AND");
		case TOKEN_AND_IF: return ("AND_IF");
		case TOKEN_OR_IF: return ("OR_IF");
		case TOKEN_PIPE: return ("PIPE");
		case TOKEN_LPARENTHESIS: return ("LPARENTHESIS");
		case TOKEN_RPARENTHESIS: return ("RPARENTHESIS");
		case TOKEN_LESSAND: return ("LESSAND");
		case TOKEN_GREATAND: return ("GREATAND");
		case TOKEN_LESS: return ("LESS");
		case TOKEN_GREAT: return ("GREAT");
		case TOKEN_CLOBBER: return ("CLOBBER");
		case TOKEN_LESSGREAT: return ("LESSGREAT");
		case TOKEN_DGREAT: return ("DGREAT");
		case TOKEN_DLESS: return ("DLESS");
		case TOKEN_DLESSDASH: return ("DLESSDASH");
		case TOKEN_IO_NUMBER: return ("IO_NUMBER");
		case TOKEN_IO_LOCATION: return ("IO_LOCATION");
		case TOKEN_EOF: return ("EOF");
		default: return ("unknown");
	}
}

/* ************************************************************************* */
/*                                  SYMBOL                                   */
/* ************************************************************************* */

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
}

/* ************************************************************************* */
/*                                   RULE                                    */
/* ************************************************************************* */

void	debug_dump_rule(t_lr_machine *machine, size_t rule_id)
{
	t_rule	*rule;
	size_t	i;

	rule = &machine->rules[rule_id];
	fprintf(stderr, "[RULE] %zu lhs=%s rhs=", rule_id, symbol_to_string(rule->lhs));
	i = 0;
	while (i < rule->rhs_len)
	{
		fprintf(stderr, "%s ", symbol_to_string(rule->rhs[i]));
		i++;
	}
	fprintf(stderr, "rhs_len=%zu hook=%p\n", rule->rhs_len, rule->hook);
}

/* ************************************************************************* */
/*                                 LR_STATE                                  */
/* ************************************************************************* */

void	debug_dump_lr_state(t_lr_machine *machine, size_t lr_state_id)
{
	t_lr_state		*state;
	t_rule_state	*rule_state;
	t_rule			*rule;
	t_symbol		next;
	size_t			i;

	state = &((t_lr_state *)machine->lr_states.data)[lr_state_id];
	fprintf(stderr, "\n[STATE %zu]\n", lr_state_id);
	i = 0;
	while (i < state->len)
	{
		rule_state = &((t_rule_state *)state->data)[i];
		rule = &machine->rules[rule_state->rule_id];
		next = SYM_NONE;
		if (rule_state->pos < rule->rhs_len)
			next = rule->rhs[rule_state->pos];
		fprintf(stderr, "rule=%zu pos=%zu lhs=%s next=%s lookahead=%s\n",
			rule_state->rule_id,
			rule_state->pos,
			symbol_to_string(rule->lhs),
			symbol_to_string(next),
			symbol_to_string(rule_state->lookahead));
		i++;
	}
	fprintf(stderr, "action[Lbrace]=%s:%zu\n",
		action_type_to_string(machine->actions[lr_state_id][SYM_Lbrace].type),
		machine->actions[lr_state_id][SYM_Lbrace].payload);
	fprintf(stderr, "action[WORD]=%s:%zu\n",
		action_type_to_string(machine->actions[lr_state_id][SYM_WORD].type),
		machine->actions[lr_state_id][SYM_WORD].payload);
	fprintf(stderr, "action[NEWLINE]=%s:%zu\n",
		action_type_to_string(machine->actions[lr_state_id][SYM_NEWLINE].type),
		machine->actions[lr_state_id][SYM_NEWLINE].payload);
}

/* ************************************************************************* */
/*                                  ACTION                                   */
/* ************************************************************************* */

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
}

/* ************************************************************************* */
/*                                    CST                                    */
/* ************************************************************************* */

static inline void	cst_log_prefix(bool *lasts, size_t depth)
{
	size_t	i;

	i = 1;
	while (i < depth)
	{
		if (lasts[i])
			fprintf(stderr, "    ");
		else
			fprintf(stderr, " │  ");
		i++;
	}
}

static inline void	cst_log_branch(bool *lasts, size_t depth, bool is_last)
{
	if (depth == 0)
		return ;
	cst_log_prefix(lasts, depth);
	if (is_last)
		fprintf(stderr, " ╰──");
	else
		fprintf(stderr, " ├──");
}

static inline void	cst_log_span(t_cst_node *node)
{
	size_t	token_end_id;

	if (node->tokens_count == 0)
	{
		fprintf(stderr, " tokens=empty");
		return ;
	}
	token_end_id = node->tokens_start_id + node->tokens_count - 1;
	fprintf(stderr, " tokens=%zu-%zu (%zu)",
		node->tokens_start_id, token_end_id, node->tokens_count);
}

static void	cst_log_node(t_cst_node *node, size_t depth, bool *lasts, bool is_last)
{
	size_t		i;
	const char	*color;

	if (!node)
		return ;
	color = NC;
	if (node->symbol <= SYM_TERMINAL_MAX)
		color = RED;
	else if (node->symbol <= SYM_complete_command)
		color = GREEN;
	else if (node->symbol <= SYM_NON_TERMINAL_MAX)
		color = YELLOW;
	cst_log_branch(lasts, depth, is_last);
	fprintf(stderr, "%s%s%s", color, symbol_to_string(node->symbol), NC);
	if (node->rule_id != RULE_NONE)
		fprintf(stderr, " rule=%i", (int)node->rule_id);
	cst_log_span(node);
	if (node->data)
		fprintf(stderr, " data=%p", node->data);
	fprintf(stderr, "\n");
	lasts[depth] = is_last;
	i = 0;
	while (i < node->child_count)
	{
		cst_log_node(node->children[i], depth + 1, lasts,
			i + 1 == node->child_count);
		i++;
	}
}

void	debug_dump_cst_node(t_cst_node *node)
{
	bool	lasts[256];
	if (!node)
		return ;
	cst_log_node(node, 0, lasts, true);
}

/* ************************************************************************* */
/*                                    AST                                    */
/* ************************************************************************* */

#ifndef MAGENTA
# define MAGENTA "\033[35m"
#endif
#ifndef CYAN
# define CYAN "\033[36m"
#endif

#define AST_AT(type, vec, i) (&((type *)(vec)->data)[i])

static inline const char	*ast_bool(bool value)
{
	if (value)
		return ("true");
	return ("false");
}

static inline void	ast_log_prefix(bool *lasts, size_t depth)
{
	size_t	i;

	i = 1;
	while (i < depth)
	{
		if (lasts[i])
			fprintf(stderr, "    ");
		else
			fprintf(stderr, " │  ");
		i++;
	}
}

static inline void	ast_log_branch(bool *lasts, size_t depth, bool is_last)
{
	if (depth == 0)
		return ;
	ast_log_prefix(lasts, depth);
	if (is_last)
		fprintf(stderr, " ╰──");
	else
		fprintf(stderr, " ├──");
}

static inline void	ast_log_head(
	bool *lasts,
	size_t depth,
	bool is_last,
	const char *color,
	const char *name)
{
	ast_log_branch(lasts, depth, is_last);
	fprintf(stderr, "%s%s%s", color, name, NC);
	lasts[depth] = is_last;
}

static void	ast_log_token_value(t_buff *buff)
{
	size_t	i;
	char	c;

	fprintf(stderr, " (%s", BLUE);
	i = 0;
	while (i < buff->len)
	{
		c = ((char *)buff->data)[i];
		if (c == '\n')
			fprintf(stderr, "\\n");
		else if (c == '\t')
			fprintf(stderr, "\\t");
		else if (c == '\r')
			fprintf(stderr, "\\r");
		else if (c == ')')
			fprintf(stderr, "\\)");
		else if (c == '\\')
			fprintf(stderr, "\\\\");
		else
			fprintf(stderr, "%c", c);
		i++;
	}
	fprintf(stderr, "%s)", NC);
}

static void	ast_log_buff(const char *name, t_buff *buff)
{
	fprintf(stderr, " %s", name);
	ast_log_token_value(buff);
}

static const char	*ast_redir_op_to_string(t_ast_redir_op op)
{
	if (op == AST_REDIR_READ)
		return ("READ");
	if (op == AST_REDIR_HEREDOC)
		return ("HEREDOC");
	if (op == AST_REDIR_DUP_READ)
		return ("DUP_READ");
	if (op == AST_REDIR_WRITE)
		return ("WRITE");
	if (op == AST_REDIR_APPEND)
		return ("APPEND");
	if (op == AST_REDIR_DUP_WRITE)
		return ("DUP_WRITE");
	if (op == AST_REDIR_CLOBBER)
		return ("CLOBBER");
	if (op == AST_REDIR_READ_WRITE)
		return ("READ_WRITE");
	return ("INVALID");
}

static const char	*ast_command_type_to_string(t_ast_command_type type)
{
	if (type == AST_CMD_SIMPLE)
		return ("SIMPLE");
	if (type == AST_CMD_LIST)
		return ("LIST");
	if (type == AST_CMD_IF)
		return ("IF");
	if (type == AST_CMD_FOR)
		return ("FOR");
	if (type == AST_CMD_LOOP)
		return ("LOOP");
	if (type == AST_CMD_CASE)
		return ("CASE");
	if (type == AST_CMD_FUNCTION_DEF)
		return ("FUNCTION_DEF");
	return ("INVALID");
}

static void	ast_log_redirection(
	t_ast_redirection *redir,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	ast_log_head(lasts, depth, is_last, RED, "REDIRECTION");
	fprintf(stderr, " op=%s", ast_redir_op_to_string(redir->operation));
	fprintf(stderr, " fd=%d", redir->fd);
	fprintf(stderr, " is_location=%s", ast_bool(redir->is_location));
	if (redir->is_location)
		ast_log_buff("location", &redir->location);
	ast_log_buff("word", &redir->word);
	fprintf(stderr, " expand_heredoc_body=%s",
		ast_bool(redir->expand_heredoc_body));
	fprintf(stderr, "\n");
}

static void	ast_log_redir_list(
	const char *name,
	t_ast_redir_list *redirs,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t	i;

	ast_log_head(lasts, depth, is_last, RED, name);
	fprintf(stderr, " count=%zu\n", redirs->len);
	i = 0;
	while (i < redirs->len)
	{
		ast_log_redirection(AST_AT(t_ast_redirection, redirs, i),
			depth + 1, lasts, i + 1 == redirs->len);
		i++;
	}
}

static void	ast_log_buff_vector(
	const char *name,
	const char *item_name,
	t_vector *vector,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t	i;
	t_buff	*buff;

	ast_log_head(lasts, depth, is_last, CYAN, name);
	fprintf(stderr, " count=%zu\n", vector->len);
	i = 0;
	while (i < vector->len)
	{
		buff = AST_AT(t_buff, vector, i);
		ast_log_head(lasts, depth + 1, i + 1 == vector->len,
			CYAN, item_name);
		ast_log_token_value(buff);
		fprintf(stderr, "\n");
		i++;
	}
}

static void	ast_log_list(
	const char *name,
	t_ast_list *list,
	size_t depth,
	bool *lasts,
	bool is_last);

static void	ast_log_command(
	t_ast_command *command,
	size_t depth,
	bool *lasts,
	bool is_last);

static void	ast_log_simple_command(
	t_ast_simple_command *cmd,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t	child_count;
	size_t	child_id;

	child_count = 3;
	child_id = 0;
	ast_log_head(lasts, depth, is_last, GREEN, "SIMPLE_COMMAND");
	fprintf(stderr, " assignments=%zu words=%zu redirs=%zu\n",
		cmd->assignments.len, cmd->words.len, cmd->redirs.len);
	ast_log_buff_vector("ASSIGNMENTS", "ASSIGNMENT",
		&cmd->assignments, depth + 1, lasts, ++child_id == child_count);
	ast_log_buff_vector("WORDS", "WORD",
		&cmd->words, depth + 1, lasts, ++child_id == child_count);
	ast_log_redir_list("REDIRS", &cmd->redirs,
		depth + 1, lasts, ++child_id == child_count);
}

static void	ast_log_pipeline(
	t_ast_pipeline *pipeline,
	size_t depth,
	bool *lasts,
	bool is_last,
	const char *next_op)
{
	size_t	i;

	ast_log_head(lasts, depth, is_last, YELLOW, "PIPELINE");
	fprintf(stderr, " negated=%s commands=%zu", ast_bool(pipeline->negated),
		pipeline->commands.len);
	if (next_op)
		fprintf(stderr, " next=%s", next_op);
	fprintf(stderr, "\n");
	i = 0;
	while (i < pipeline->commands.len)
	{
		ast_log_command(AST_AT(t_ast_command, &pipeline->commands, i),
			depth + 1, lasts, i + 1 == pipeline->commands.len);
		i++;
	}
}

static void	ast_log_and_or(
	t_ast_and_or *and_or,
	size_t depth,
	bool *lasts,
	bool is_last,
	bool async)
{
	size_t		i;
	bool		*ops;
	const char	*next_op;

	ast_log_head(lasts, depth, is_last, YELLOW, "AND_OR");
	fprintf(stderr, " pipelines=%zu operators=%zu async=%s\n",
		and_or->pipelines.len, and_or->next_on_success.len,
		ast_bool(async));
	ops = (bool *)and_or->next_on_success.data;
	i = 0;
	while (i < and_or->pipelines.len)
	{
		next_op = NULL;
		if (i < and_or->next_on_success.len)
		{
			if (ops[i])
				next_op = "&&";
			else
				next_op = "||";
		}
		ast_log_pipeline(AST_AT(t_ast_pipeline, &and_or->pipelines, i),
			depth + 1, lasts, i + 1 == and_or->pipelines.len, next_op);
		i++;
	}
}

static void	ast_log_list(
	const char *name,
	t_ast_list *list,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t	i;
	bool	*asyncs;

	ast_log_head(lasts, depth, is_last, GREEN, name);
	fprintf(stderr, " and_ors=%zu asyncs=%zu subshell=%s\n",
		list->and_ors.len, list->asyncs.len, ast_bool(list->subshell));
	asyncs = (bool *)list->asyncs.data;
	i = 0;
	while (i < list->and_ors.len)
	{
		ast_log_and_or(AST_AT(t_ast_and_or, &list->and_ors, i),
			depth + 1, lasts, i + 1 == list->and_ors.len, asyncs[i]);
		i++;
	}
}

static void	ast_log_if(
	t_ast_if *if_node,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t	i;
	size_t	total;
	size_t	id;

	total = if_node->conditions.len * 2 + if_node->has_else;
	id = 0;
	ast_log_head(lasts, depth, is_last, MAGENTA, "IF");
	fprintf(stderr, " branches=%zu has_else=%s\n",
		if_node->conditions.len, ast_bool(if_node->has_else));
	i = 0;
	while (i < if_node->conditions.len)
	{
		ast_log_list("CONDITION", AST_AT(t_ast_list, &if_node->conditions, i),
			depth + 1, lasts, ++id == total);
		ast_log_list("BODY", AST_AT(t_ast_list, &if_node->bodies, i),
			depth + 1, lasts, ++id == total);
		i++;
	}
	if (if_node->has_else)
		ast_log_list("ELSE", &if_node->else_body,
			depth + 1, lasts, true);
}

static void	ast_log_for(
	t_ast_for *for_node,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	ast_log_head(lasts, depth, is_last, MAGENTA, "FOR");
	ast_log_buff("var", &for_node->var_name);
	fprintf(stderr, " words=%zu\n", for_node->words.len);
	ast_log_buff_vector("WORDS", "WORD", &for_node->words,
		depth + 1, lasts, false);
	ast_log_list("BODY", &for_node->body, depth + 1, lasts, true);
}

static void	ast_log_loop(
	t_ast_loop *loop,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	ast_log_head(lasts, depth, is_last, MAGENTA, "LOOP");
	fprintf(stderr, " condition_must_be_true=%s\n",
		ast_bool(loop->condition_must_be_true));
	ast_log_list("CONDITION", &loop->condition, depth + 1, lasts, false);
	ast_log_list("BODY", &loop->body, depth + 1, lasts, true);
}

static void	ast_log_case_item(
	t_ast_case *case_node,
	size_t index,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	bool	*fallthrough;

	fallthrough = (bool *)case_node->fallthrough.data;
	ast_log_head(lasts, depth, is_last, MAGENTA, "CASE_ITEM");
	fprintf(stderr, " index=%zu fallthrough=%s\n",
		index, ast_bool(fallthrough[index]));
	ast_log_buff_vector("PATTERNS", "PATTERN",
		AST_AT(t_vector, &case_node->patterns, index),
		depth + 1, lasts, false);
	ast_log_list("BODY", AST_AT(t_ast_list, &case_node->bodies, index),
		depth + 1, lasts, true);
}

static void	ast_log_case(
	t_ast_case *case_node,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t	i;

	ast_log_head(lasts, depth, is_last, MAGENTA, "CASE");
	ast_log_buff("word", &case_node->word);
	fprintf(stderr, " items=%zu\n", case_node->patterns.len);
	i = 0;
	while (i < case_node->patterns.len)
	{
		ast_log_case_item(case_node, i, depth + 1, lasts,
			i + 1 == case_node->patterns.len);
		i++;
	}
}

static void	ast_log_function(
	t_ast_function_def *function,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	size_t	child_count;
	size_t	id;

	child_count = 1;
	if (function->redirs.len > 0)
		child_count++;
	id = 0;
	ast_log_head(lasts, depth, is_last, MAGENTA, "FUNCTION_DEF");
	ast_log_buff("name", &function->name);
	fprintf(stderr, " redirs=%zu\n", function->redirs.len);
	if (function->body)
		ast_log_command(function->body, depth + 1, lasts,
			++id == child_count);
	if (function->redirs.len > 0)
		ast_log_redir_list("REDIRS", &function->redirs,
			depth + 1, lasts, ++id == child_count);
}

static void	ast_log_command_data(
	t_ast_command *command,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	if (command->type == AST_CMD_SIMPLE)
		ast_log_simple_command(&command->data.simple, depth, lasts, is_last);
	else if (command->type == AST_CMD_LIST)
		ast_log_list("LIST", &command->data.list, depth, lasts, is_last);
	else if (command->type == AST_CMD_IF)
		ast_log_if(&command->data.if_clause, depth, lasts, is_last);
	else if (command->type == AST_CMD_FOR)
		ast_log_for(&command->data.for_clause, depth, lasts, is_last);
	else if (command->type == AST_CMD_LOOP)
		ast_log_loop(&command->data.loop, depth, lasts, is_last);
	else if (command->type == AST_CMD_CASE)
		ast_log_case(&command->data.case_clause, depth, lasts, is_last);
	else if (command->type == AST_CMD_FUNCTION_DEF)
		ast_log_function(&command->data.function_def, depth, lasts, is_last);
}

static void	ast_log_command(
	t_ast_command *command,
	size_t depth,
	bool *lasts,
	bool is_last)
{
	ast_log_head(lasts, depth, is_last, BLUE, "COMMAND");
	fprintf(stderr, " type=%s redirs=%zu\n",
		ast_command_type_to_string(command->type), command->redirs.len);
	ast_log_command_data(command, depth + 1, lasts,
		command->redirs.len == 0);
	if (command->redirs.len > 0)
		ast_log_redir_list("COMMAND_REDIRS", &command->redirs,
			depth + 1, lasts, true);
}

void	debug_dump_ast(t_ast_root *root)
{
	bool	lasts[256];

	if (!root)
		return ;
	ast_log_list("AST_ROOT", root, 0, lasts, true);
}

```

./srcs/error.c
```c
#include "error.h"
#include "posix_helpers.h"
#include "shell.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
# include <debug.h>	// DEBUG

#define SEPARATOR		": "

// TODO: split in 2 functions and move to another file
const char	*error_to_string(t_error err)
{
	if (err.type == ERR_NO)
		return ("success");
	else if (err.type == ERR_ASSIGNMENT_MISSING_NAME)
		return ("missing assignment name");
	else if (err.type == ERR_BUILTIN_INVALID_USAGE)
		return ("usage");
	else if (err.type == ERR_HOOK_INVALID_RHS_LEN)
		return ("invalid rhs len");
	else if (err.type == ERR_INDEX_OUT_OF_BOUND)
		return ("index out of bound");
	else if (err.type == ERR_INVALID_FORMAT)
		return ("invalid format");
	else if (err.type == ERR_LIBC)
		return (strerror(err.saved_errno));
	else if (err.type == ERR_LR_CONFLICT)
		return ("LR conflict");
	else if (err.type == ERR_LR_STATE_NOT_FOUND)
		return ("LR state not found");
	else if (err.type == ERR_OPT_INVALID)
		return ("invalid option");
	else if (err.type == ERR_OPT_INVALID_ARG)
		return ("invalid option argument");
	else if (err.type == ERR_OPT_MISSING_ARG)
		return ("missing option argument");
	else if (err.type == ERR_PARSER_EMPTY_GOTO)
		return ("empty goto");
	else if (err.type == ERR_PARSER_INVALID_FUNCTION_NAME)
		return ("invalid function name");
	else if (err.type == ERR_PARSER_INVALID_STATE)
		return ("invalid state");
	else if (err.type == ERR_SHELL_NOT_FOUND)
		return ("shell data not found");
	else if (err.type == ERR_SHIFT_INVALID_VALUE)
		return ("shift value is out of range");
	else if (err.type == ERR_SIZE_MAX_REACHED)
		return ("SIZE_MAX has been reached");
	else if (err.type == ERR_UNDEFINED_BEHAVIOUR)
		return ("undefined behaviour 🤪");
	else if (err.type == ERR_VAR_INVALID_NAME)
		return ("invalid variable name");
	else if (err.type == ERR_VAR_MISSING_EQUAL)
		return ("missing '='");
	else if (err.type == ERR_VAR_NOT_FOUND)
		return ("variable not found");
	else if (err.type == ERR_VAR_READ_ONLY)
		return ("readonly variable");
	else if (err.type == ERR_NULL_ARGS)
		return ("null arguments");
	else if (err.type == ERR_TOKEN_INIT)
		return ("token initialization failed");
	else if (err.type == ERR_CTX_END_NOT_FOUND)
		return ("context end not found");
	else if (err.type == ERR_VALUE_OUT_OF_RANGE)
		return ("value out of range");
	else if (err.type == ERR_LEX_INCOMPLETE)
		return ("incomplete lexical input");
	else if (err.type == ERR_INVALID_SYNTAX)
		return ("invalid syntax");
	else if (err.type == ERR_EMPTY_STACK)
		return ("empty stack");
	else if (err.type == ERR_VEOF)
		return ("unexpected end of input");
	else if (err.type == ERR_EMPTY_CONTINUATION)
		return ("empty continuation");
	else if (err.type == ERR_INVALID_ARGS)
		return ("invalid arguments");
	else if (err.type == ERR_FILE_STAT)
		return ("file stat failed");
	else if (err.type == ERR_OPEN_FILE)
		return ("unable to open file");
	else if (err.type == ERR_INCOHERENT_STATE)
		return ("incoherent state");
	else if (err.type == ERR_NOT_IMPLEMENTED)
		return ("not implemented");
	else if (err.type == ERR_HEREDOC_FILE_LIMIT)
		return ("heredoc file limit reached");
	else if (err.type == ERR_UNEXPECTED_EOI)
		return ("unexpected end of input");
	else if (err.type == ERR_NO_DELIM)
		return ("missing delimiter");
	return ("unknown");
}

t_error	error_priv(t_error_type type, const char *caller)
{
	t_error	err;

	err.type = type;
	err.saved_errno = 0;
	err.printed = false;
	// if (type != ERR_NO)
	// 	fprintf(stderr, RED "===> [ERROR] from [%s()] type = %s\n" NC, caller, error_to_string(err));
	(void)caller;
	return (err);
}

t_error	error_sys_priv(const char *caller)
{
	t_error	err;

	err.type = ERR_LIBC;
	err.saved_errno = errno;
	err.printed = false;
	// fprintf(stderr, RED "===> [ERROR] from [%s()] type = ERR_LIBC (%s)\n" NC, caller, error_to_string(err));
	(void)caller;
	return (err);
}

static void	error_print_format(const char *fstring, va_list args)
{
	va_list	copy;
	t_buff	buff;

	va_copy(copy, args);
	(void)buff_init(&buff, 0, NULL, -1);
	if (buff_append_vformat(&buff, fstring, copy))
	{
		(void)posix_write(STDERR_FILENO, buff.data, buff.len);
		(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	}
	va_end(copy);
	buff_free(&buff);
}

t_error	error_print(t_error err, ...)
{
	va_list		args;
	const char	*shell_name;
	const char	*string;

	if (err.printed)
		return (err);
	shell_name = shell_get_name();
	(void)posix_write(STDERR_FILENO, shell_name, str_len(shell_name));
	(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	va_start(args, err);
	string = va_arg(args, const char *);
	while (string)
	{
		(void)posix_write(STDERR_FILENO, string, str_len(string));
		(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
		string = va_arg(args, const char *);
	}
	string = va_arg(args, const char *);
	if (string)
		error_print_format(string, args);
	va_end(args);
	string = error_to_string(err);
	(void)posix_write(STDERR_FILENO, string, str_len(string));
	(void)posix_write(STDERR_FILENO, "\n", 1);
	return (err.printed = true, err);
}

```

./srcs/expander/_init.c
```c
#include <stdlib.h>
#include "expander_.h"
#include "expander_loader_.h"

void	expander_init(t_expander *state, t_expander_role role)
{
	*state = (t_expander){0};
	state->role = role;
	expander_fields_init(&state->fields);
	expander_word_init(&state->word_exp);
	expander_fields_init(&state->fields_exp);
}

void	expander_free(t_expander *state)
{
	expander_fields_free(&state->fields);
	expander_word_free(&state->word_exp);
	expander_fields_free(&state->fields_exp);
	*state = (t_expander){0};
}

t_error	expander_load(t_expander *state, t_buff word, t_context_stack *stack)
{
	size_t				word_len;
	t_expander_word		word_copy;
	t_expander_loader	loader_state;

	expander_loader_init(&loader_state);
	state->err = expander_loader_load(&loader_state, stack, word);
	if (state->err.type)
		return (expander_loader_free(&loader_state), state->err);
	word_len = str_len(loader_state.word);
	while (loader_state.i < word_len)
	{
		state->err = expander_loader_build(&loader_state);
		if (state->err.type)
			return (expander_loader_free(&loader_state), state->err);
	}
	state->err = expander_word_dup(&word_copy, &loader_state.loaded_word);
	if (state->err.type)
	{
		expander_loader_free(&loader_state);
		return (expander_word_free(&word_copy), state->err);
	}
	state->err = expander_fields_push(&state->fields, word_copy);
	return (expander_loader_free(&loader_state), state->err);
}

```

./srcs/expander/API.c
```c
#include "quote_removal_.h"
#include "expander_loader_.h"
#include "field_splitting_.h"
#include "path_name_expansion.h"
#include "expander_substitutions.h"

t_error	expander_expand_word(
	char ***expansion,
	t_buff value,
	t_context_stack	*contexts,
	t_expander_role role)
{
	t_expander	state;

	expander_init(&state, role);
	if (expander_load(&state, value, contexts).type)
		return (expander_free(&state), state.err);
	if (substitutions(&state).type)
		return (expander_free(&state), state.err);
	if (field_splitting(&state).type)
		return (expander_free(&state), state.err);
	if (path_name_expansion(&state).type)
		return (expander_free(&state), state.err);
	if (quote_removal(&state).type)
		return (expander_free(&state), state.err);
	state.err = expander_loader_extract(&state.fields, expansion);
	return (expander_free(&state), state.err);
}

```

./srcs/expander/expander_.h
```c
#ifndef EXPANDER__H
# define EXPANDER__H

# include "expander.h"
# include "expander_field_.h"

typedef struct s_expander
{
	t_error				err;
	t_expander_role		role;
	t_expander_word		word;
	t_expander_fields	fields;
	t_expander_word		word_exp;
	t_expander_fields	fields_exp;
}	t_expander;

void	expander_free(t_expander *state);
void	expander_init(t_expander *state, t_expander_role role);
t_error	expander_load(t_expander *state, t_buff word, t_context_stack *stack);

#endif

```

./srcs/expander/field_splitting/_main.c
```c
#include "field_splitting_.h"

t_error	field_splitting(t_expander *state)
{
	return (state->err);
}

```

./srcs/expander/field_splitting/field_splitting_.h
```c
#ifndef FIELD_SPLITTING__H
# define FIELD_SPLITTING__H

# include "expander_.h"

t_error	field_splitting(t_expander *state);

#endif

```

./srcs/expander/field/_init.c
```c
#include "expander_field_.h"

void	expander_fields_init(t_expander_fields *fields)
{
	vector_init(fields, sizeof(t_expander_word), 0);
}

void	expander_fields_free(t_expander_fields *fields)
{
	vector_free(fields, (void (*)(void *))expander_word_free);
}

```

./srcs/expander/field/_utils.c
```c
#include "expander_field_.h"

t_error	expander_fields_push(t_expander_fields *fields, t_expander_word item)
{
	if (!vector_push(fields, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	expander_fields_pop(t_expander_fields *fields, t_expander_word *item)
{
	if (fields->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (!vector_remove(fields, 0, item))
		return (error_sys());
	return (error(ERR_NO));
}

```

./srcs/expander/field/expander_field_.h
```c
#ifndef EXPANDER_FIELD__H
# define EXPANDER_FIELD__H

# include "error.h"
# include "libft.h"
# include "expander_word_.h"

typedef t_vector	t_expander_fields;

void	expander_fields_init(t_expander_fields *fields);
void	expander_fields_free(t_expander_fields *fields);

t_error	expander_fields_push(t_expander_fields *fields, t_expander_word item);
t_error	expander_fields_pop(t_expander_fields *fields, t_expander_word *item);

#endif

```

./srcs/expander/loader/_init.c
```c
#include "expander_loader_.h"

void	expander_loader_init(t_expander_loader *state)
{
	*state = (t_expander_loader){0};
	context_stack_init(&state->stack);
	expander_word_init(&state->loaded_word);
	context_stack_init(&state->loading_stack);
}

void	expander_loader_free(t_expander_loader *state)
{
	context_stack_free(&state->stack);
	expander_word_free(&state->loaded_word);
	context_stack_free(&state->loading_stack);
	if (state->context_item)
		state->context_item = NULL;
	*state = (t_expander_loader){0};
}

t_error	expander_loader_load(
	t_expander_loader *state,
	t_context_stack *stack,
	t_buff word)
{
	state->word = buff_get_string(&word);
	if (state->word == NULL)
		return (state->err = error_sys());
	if (stack == NULL)
		return (state->err);
	return (state->err = context_stack_dup(&state->stack, stack));
}

```

./srcs/expander/loader/_main.c
```c
#include <stdlib.h>
#include "expander_loader_.h"

t_error	expander_loader_build(t_expander_loader *state)
{
	state->quoting = CONTEXT_NONE;
	if (is_substitution_start(state))
		expander_loader_substitution(state);
	else if (is_char_escaped(state))
		expander_loader_consume(state, 2);
	else if (is_quoting_context(state->word + state->i, &state->quoting))
		expander_loader_quoted(state);
	else
		expander_loader_consume(state, 1);
	return (state->err);
}

static t_error	expander_loader_word_extract(t_expander_word word, char **str)
{
	size_t					i;
	t_error					err;
	t_expander_word_item	item;

	i = 0;
	*str = malloc(sizeof(char) * (word.len + 1));
	if (*str == NULL)
		return (error_sys());
	while (word.len > 0)
	{
		err = expander_word_pop(&word, &item);
		if (err.type)
			return (free(*str), *str = NULL, err);
		if (item.c == '\0' && word.len > 0)
			continue ;
		(*str)[i++] = item.c;
	}
	return ((*str)[i] = '\0', error(ERR_NO));
}

t_error	expander_loader_extract(t_expander_fields *fields, char ***words)
{
	size_t			i;
	t_error			err;
	t_expander_word	word;
	char 			*str;

	i = 0;
	*words = malloc(sizeof(char *) * (fields->len + 1));
	if (!*words)
		return (error_sys());
	ft_bzero(*words, sizeof(char *) * (fields->len + 1));
	while (fields->len > 0)
	{
		err = expander_fields_pop(fields, &word);
		if (err.type)
			return (str_array_free(words), err);
		err = expander_loader_word_extract(word, &str);
		if (err.type)
			return (str_array_free(words), expander_word_free(&word), err);
		(*words)[i++] = str;
		expander_word_free(&word);
	}
	return (error(ERR_NO));
}

```

./srcs/expander/loader/_utils.c
```c
#include <stdlib.h>
#include "expander_loader_.h"

bool	is_char_escaped(t_expander_loader *state)
{
	char	next_char;
	char	current_char;
	bool	is_in_whitelist;

	current_char = state->word[state->i];
	next_char = state->word[state->i + 1];
	if (state->quoting != CONTEXT_NONE)
		is_in_whitelist = is_in_quoting_whitelist(next_char, state->quoting);
	else
		is_in_whitelist = is_in_expansion_whitelist(next_char, state->quoting);
	return (current_char == '\\' && next_char != '\0' && is_in_whitelist);
}

bool	is_substitution_start(t_expander_loader *state)
{
	t_context_parser_stack_item	*item;

	if (state->stack.len == 0)
		return (false);
	state->err = context_stack_get(&state->stack, &item, 0);
	if (state->err.type || item == NULL)
		return (false);
	return (state->i == item->start);
}

t_error	expander_loader_push_context(t_expander_loader *state)
{
	t_context_parser_stack_item	*item;

	if (state->stack.len == 0)
		return (state->err);
	state->err = context_stack_fpop(&state->stack, &item);
	if (state->err.type)
		return (state->err);
	state->err = context_stack_push(&state->loading_stack, item);
	if (state->err.type)
		return (free(item), state->err);
	return (state->context_item = item, state->err);
}

t_error	expander_loader_pop_context(t_expander_loader *state)
{
	t_context_parser_stack_item	*item;
	size_t					last_i;
	
	state->err = context_stack_bpop(&state->loading_stack, &item);
	if (state->err.type)
		return (state->err);
	free(item);
	if (state->loading_stack.len > 0)
	{
		last_i = state->loading_stack.len - 1;
		state->err = context_stack_get(&state->loading_stack, &item, last_i);
		if (state->err.type)
			return (state->err);
		state->context_item = item;
	}
	else
		state->context_item = NULL;
	return (state->err);
}

t_error	expander_loader_consume(t_expander_loader *state, size_t count)
{
	size_t					i;
	t_expander_word_item	item;
	t_context				quoting;
	t_context				current;
	char					current_char;
	
	i = 0;
	quoting = state->quoting;
	if (state->context_item == NULL)
		current = CONTEXT_NONE;
	else
		current = state->context_item->context;
	while (i < count)
	{
		current_char = state->word[state->i++];
		item = expander_word_item_init(current_char, quoting, current, false);
		state->err = expander_word_push(&state->loaded_word, item);
		if (state->err.type)
			return (state->err);
		i++;
	}
	return (state->err);
}

```

./srcs/expander/loader/context.c
```c
#include "expander_loader_.h"

static t_error	expander_loader_char(t_expander_loader *state)
{
	if (is_char_escaped(state))
	{
		if (expander_loader_consume(state, 1).type)
			return (state->err);
	}
	return (expander_loader_consume(state, 1));
}

static t_error	expander_loader_context(t_expander_loader *state)
{
	if (is_substitution_start(state))
		return (expander_loader_substitution(state));
	else
		return (expander_loader_char(state));
}

t_error	expander_loader_substitution(t_expander_loader *state)
{
	if (expander_loader_push_context(state).type)
		return (state->err);
	while (state->i < state->context_item->end)
	{
		if (state->i != state->context_item->start)
		{
			if (is_substitution_start(state))
				return (expander_loader_substitution(state));
			else if (expander_loader_char(state).type)
				return (state->err);
		}
		else if (expander_loader_char(state).type)
			return (state->err);
	}
	return (expander_loader_pop_context(state));
}

t_error	expander_loader_quoted(t_expander_loader *state)
{
	char	current;

	if (state->quoting != CONTEXT_DOLLAR_SQUOTE)
		expander_loader_consume(state, 1);
	else
		expander_loader_consume(state, 2);
	if (state->err.type)
		return (state->err);
	current = state->word[state->i];
	while (current != '\0' && !is_quoting_ending(current, state->quoting))
	{
		if (expander_loader_context(state).type)
			return (state->err);
		current = state->word[state->i];
	}
	if (state->word[state->i] == '\0')
		return (state->err);
	return (expander_loader_consume(state, 1));
}

```

./srcs/expander/loader/expander_loader_.h
```c
#ifndef EXPANDER_LOADER__H
# define EXPANDER_LOADER__H

# include "error.h"
# include "context.h"
# include "expander_word_.h"
# include "expander_field_.h"

typedef struct s_expander_loader
{
	size_t					i;
	t_error					err;
	char					*word;
	t_context_stack			stack;
	t_context				quoting;
	t_expander_word			loaded_word;
	t_context_stack			loading_stack;
	t_context_parser_stack_item	*context_item;
}	t_expander_loader;

void	expander_loader_init(t_expander_loader *state);
void	expander_loader_free(t_expander_loader *state);
t_error	expander_loader_load(t_expander_loader *state, t_context_stack *stack,
			t_buff word);

bool	is_char_escaped(t_expander_loader *state);
bool	is_substitution_start(t_expander_loader *state);
t_error	expander_loader_pop_context(t_expander_loader *state);
t_error	expander_loader_push_context(t_expander_loader *state);
t_error	expander_loader_consume(t_expander_loader *state, size_t count);

t_error	expander_loader_quoted(t_expander_loader *state);
t_error	expander_loader_substitution(t_expander_loader *state);

t_error	expander_loader_build(t_expander_loader *state);
t_error	expander_loader_extract(t_expander_fields *fields, char ***words);
	
#endif

```

./srcs/expander/path_name_expansion/path_name_expansion.h
```c
#ifndef PATH_NAME_EXPANSION_H
# define PATH_NAME_EXPANSION_H

# include "expander_.h"

typedef struct s_path_name_expansion
{
	size_t	i;
	t_error	err;
	char	*word;
	bool	reached_EOW;
}	t_path_name_expansion;

t_error	path_name_expansion(t_expander *state);

#endif

```

./srcs/expander/quote_removal/_main.c
```c
#include "quote_removal_.h"
#include "quote_removal_context_.h"

t_error	quote_removal_quoted(
	t_expander *state,
	t_context context,
	t_expander_word *word,
	t_expander_word *word_expanded)
{
	t_expander_word_item	item;

	if (context == CONTEXT_SQUOTE)
		context_squote(state, word, word_expanded);
	else if (context == CONTEXT_DQUOTE)
		context_dquote(state, word, word_expanded);
	else if (context == CONTEXT_DOLLAR_SQUOTE)
	{
		state->err = expander_word_pop(word, &item);
		if (state->err.type)
			return (state->err);
		context_dollar_squote(state, word, word_expanded);
	}
	return (state->err);
}

t_error	quote_remove_char(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	t_expander_word_item	item;

	state->err = expander_word_pop(word, &item);
	if (state->err.type)
		return (state->err);
	if (item.opt.is_expand_res)
		state->err = expander_word_push(word_exp, item);
	else if (item.opt.quoted == CONTEXT_NONE)
	{
		if (item.c != '\\')
			state->err = expander_word_push(word_exp, item);
		else
		{
			if (word->len == 0)
				return (state->err = error(ERR_NO));
			state->err = expander_word_pop(word, &item);
			if (state->err.type)
				return (state->err);
			state->err = expander_word_push(word_exp, item);
		}
	}
	else
		quote_removal_quoted(state, item.opt.quoted, word, word_exp);
	return (state->err);
}

t_error	quote_removal_word(t_expander *state, t_expander_fields *fields)
{
	t_expander_word	word;
	t_expander_word	word_exp;

	state->err = expander_fields_pop(&state->fields, &word);
	if (state->err.type)
		return (state->err);
	expander_word_init(&word_exp);
	while (word.len > 0)
	{
		if (quote_remove_char(state, &word, &word_exp).type)
		{
			expander_word_free(&word);
			expander_word_free(&word_exp);
			return (state->err);
		}
	}
	expander_word_free(&word);
	state->err = expander_fields_push(fields, word_exp);
	if (state->err.type)
		expander_word_free(&word_exp);
	return (state->err);
}

t_error	quote_removal(t_expander *state)
{
	t_expander_fields	fields;

	expander_fields_init(&fields);
	while (state->fields.len > 0)
	{
		if (quote_removal_word(state, &fields).type)
			return (expander_fields_free(&fields), state->err);
	}
	expander_fields_free(&state->fields);
	state->fields = fields;
	return (state->err);
}

```

./srcs/expander/quote_removal/context/_utils.c
```c
#include "quote_removal_context_.h"

static t_error	context_escape(
	t_expander *state,
	t_context_args args,
	t_expander_word_item item)
{
	t_expander_word_item	escaped_item;

	state->err = expander_word_pop(args.word, &escaped_item);
	if (state->err.type)
		return (state->err);
	if (!args.is_in_whitelist(escaped_item.c))
	{
		state->err = expander_word_push(args.word_expanded, item);
		if (state->err.type)
			return (state->err);
	}
	return (state->err = expander_word_push(args.word_expanded, escaped_item));
}

static t_error	context_end(t_expander *state, t_context_args args)
{
	t_expander_word_item	item;

	if (args.word_expanded->len != 0)
		return (state->err);
	item = expander_word_item_init('\0', args.context, args.context, false);
	return (state->err = expander_word_push(args.word_expanded, item));
}

t_error	context_scan(t_expander *state, t_context_args args)
{
	t_expander_word_item	item;

	while (true)
	{
		state->err = expander_word_pop(args.word, &item);
		if (state->err.type)
			return (state->err);
		if (args.is_end != NULL && args.is_end(item.c, NULL))
			return (context_end(state, args));
		else if (item.c == '\\' && args.is_in_whitelist != NULL)
		{
			state->err = context_escape(state, args, item);
			if (state->err.type)
				return (state->err);
		}
		else
		{
			state->err = expander_word_push(args.word_expanded, item);
			if (state->err.type)
				return (state->err);
		}
	}
}

```

./srcs/expander/quote_removal/context/dollar_squote.c
```c
#include "context.h"
#include "quote_removal_context_.h"

static t_context_args	context_dollar_squote_rules(
	t_expander_word *word,
	t_expander_word *word_expanded)
{
	t_context_args	args;

	args.word = word;
	args.context = CONTEXT_DOLLAR_SQUOTE;
	args.word_expanded = word_expanded;
	args.is_end = is_context_dollar_squote_ending;
	args.is_in_whitelist = is_in_context_dollar_squote_whitelist;
	return (args);
}

t_error	context_dollar_squote(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	return (context_scan(state, context_dollar_squote_rules(word, word_exp)));
}

```

./srcs/expander/quote_removal/context/dquote.c
```c
#include "context.h"
#include "quote_removal_context_.h"

static t_context_args	context_dquote_rules(
	t_expander_word *word,
	t_expander_word *word_expanded)
{
	t_context_args	args;
	
	args.word = word;
	args.context = CONTEXT_DQUOTE;
	args.word_expanded = word_expanded;
	args.is_end = is_context_dquote_ending;
	args.is_in_whitelist = is_in_context_dquote_whitelist;
	return (args);
}

t_error	context_dquote(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	return (context_scan(state, context_dquote_rules(word, word_exp)));
}

```

./srcs/expander/quote_removal/context/quote_removal_context_.h
```c
#ifndef QUOTE_REMOVAL_CONTEXT__H
# define QUOTE_REMOVAL_CONTEXT__H

#include "expander_.h"

typedef struct s_context_args
{
	t_expander_word	*word;
	t_context		context;
	t_expander_word	*word_expanded;
	bool			(*is_end)(char, void *);
	bool			(*is_in_whitelist)(char);
}	t_context_args;

t_error	context_scan(t_expander *state, t_context_args args);

t_error	context_squote(t_expander *state, t_expander_word *word,
			t_expander_word *word_exp);
t_error	context_dquote(t_expander *state, t_expander_word *word,
			t_expander_word *word_exp);
t_error	context_dollar_squote(t_expander *state, t_expander_word *word,
			t_expander_word *word_exp);

#endif

```

./srcs/expander/quote_removal/context/squote.c
```c
#include "context.h"
#include "quote_removal_context_.h"

static t_context_args	context_squote_rules(
	t_expander_word *word,
	t_expander_word *word_expanded)
{
	t_context_args	args;
	
	args.word = word;
	args.context = CONTEXT_SQUOTE;
	args.is_in_whitelist = NULL;
	args.word_expanded = word_expanded;
	args.is_end = is_context_squote_ending;
	return (args);
}

t_error	context_squote(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	return (context_scan(state, context_squote_rules(word, word_exp)));
}

```

./srcs/expander/quote_removal/quote_removal_.h
```c
#ifndef QUOTE_REMOVAL__H
# define QUOTE_REMOVAL__H

# include "error.h"
# include "expander_.h"

t_error	quote_removal(t_expander *state);

#endif

```

./srcs/expander/substitutions/_main.c
```c
#include "expander_substitutions.h"

t_error	substitutions(t_expander *state)
{
	return (state->err);
}

```

./srcs/expander/substitutions/expander_substitutions.h
```c
#ifndef EXPANDER_SUBSTITUTIONS_H
# define EXPANDER_SUBSTITUTIONS_H

# include "error.h"
# include "expander_.h"

t_error	substitutions(t_expander *state);

#endif

```

./srcs/expander/substitutions/tilde/_main.c
```c
#include "utils.h"
#include "params.h"
#include "tilde_expansion_.h"

bool	is_tilde_expansion(t_expander *state, t_expander_word *word)
{
	t_expander_word_item	item;

	state->err = expander_word_peek(word, &item);
	if (state->err.type)
		return (false);
	return (item.c == '~');
}

t_error	tilde_extract_username(t_expander *state, char **username)
{
	size_t					i;
	t_expander_word_item	item;

	i = 0;
	while (i + 1 < state->word.len)
	{
		state->err = expander_word_get(&state->word, i + 1, &item);
		if (state->err.type)
			return (state->err);
		if (item.c == '/')
			break ;
		else if (state->role == EXPANDER_ASSIGNMENT && item.c == ':')
			break ;
		else if (item.opt.quoted != CONTEXT_NONE)
			return (*username = NULL, state->err);
		i++;
	}
	return (state->err = expander_word_to_str(&state->word, username, 1, i));
}

t_error	tilde_resolve_path(t_expander *state, char **path, char *username)
{
	struct passwd *password;

	if (username[0] == '\0')
		return (state->err = params_get("HOME", path));
	else
	{
		password = ft_getpwnam(username);
		if (password == NULL)
			return (state->err = error_sys());
		return (*path = password->pw_dir, state->err);
	}
}

t_error	tilde_expansion(t_expander *state)
{
	t_expander_word_item_opt	opt;
	t_expander_word_item		item;
	char						*path;
	char						*username;

	if (tilde_extract_username(state, &username).type || username == NULL)
		return (state->err);
	if (tilde_resolve_path(state, &path, username).type || path == NULL)
		return (state->err);
	state->err = expander_word_pop(&state->word, &item);
	if (state->err.type)
		return (state->err);
	opt = (t_expander_word_item_opt){
		.is_expand_res = true,
		.quoted = item.opt.quoted,
		.context = item.opt.context,
	};
	state->err = expander_word_from_str(&state->word, path, opt);
	if (state->err.type)
		return (state->err);
	state->err = expander_word_remove(&state->word, 0, str_len(path));
	return (state->err);
}

```

./srcs/expander/substitutions/tilde/tilde_expansion_.h
```c
#ifndef TILDE_EXPANSION__H
# define TILDE_EXPANSION__H

#include "expander_.h"

bool	is_tilde_expansion(t_expander *state, t_expander_word *word);

#endif

```

./srcs/expander/word/_init.c
```c
#include "expander_word_.h"

void		expander_word_init(t_expander_word *word)
{
	vector_init(word, sizeof(t_expander_word_item), 0);
}

void		expander_word_free(t_expander_word *word)
{
	vector_free(word, NULL);
}

t_expander_word_item	expander_word_item_init(
	char c,
	t_context quoted,
	t_context context,
	bool is_expand_res)
{
	t_expander_word_item	item;

	item.c = c;
	if (quoted != CONTEXT_SQUOTE 
		&& quoted != CONTEXT_DQUOTE
		&& quoted != CONTEXT_DOLLAR_SQUOTE)
		quoted = CONTEXT_NONE;
	item.opt.quoted = quoted;
	item.opt.context = context;
	item.opt.is_expand_res = is_expand_res;
	return (item);
}

```

./srcs/expander/word/_utils_.c
```c
#include <stdlib.h>
#include "expander_word_.h"

t_error	expander_word_remove(t_expander_word *word, size_t start, size_t len)
{
	size_t					i;
	t_expander_word_item	item;

	i = 0;
	while (i < len)
	{
		if (word->len <= start + i)
			return (error(ERR_NO));
		if (!vector_remove(word, start, &item))
			return (error(ERR_NO));
		i++;
	}
	return (error(ERR_NO));
}

t_error	expander_word_to_str(
	t_expander_word *word,
	char **str,
	size_t start,
	size_t len)
{
	size_t					i;
	t_error					err;
	t_expander_word_item	item;

	*str = malloc(sizeof(char) * (len + 1));
	if (*str == NULL)
		return (error_sys());
	i = 0;
	while (i < len)
	{
		if (word->len <= start + i)
			return (free(*str), error(ERR_INDEX_OUT_OF_BOUND));
		err = expander_word_get(word, start + i, &item);
		if (err.type)
			return (free(*str), err);
		(*str)[i++] = item.c;
	}
	return ((*str)[i] = '\0', error(ERR_NO));
}

t_error	expander_word_from_str(
	t_expander_word *word,
	const char *str,
	t_expander_word_item_opt opt)
{
	size_t					i;
	t_error					err;
	t_expander_word_item	item;

	i = 0;
	while (str[i] != '\0')
	{
		item = expander_word_item_init(
			str[i],
			opt.quoted,
			opt.context,
			opt.is_expand_res);
		err = expander_word_push(word, item);
		if (err.type)
			return (err);
		i++;
	}
	return (error(ERR_NO));
}

```

./srcs/expander/word/_utils.c
```c
#include "expander_word_.h"

t_error	expander_word_push(t_expander_word *word, t_expander_word_item item)
{
	if (!vector_push(word, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	expander_word_pop(t_expander_word *word, t_expander_word_item *item)
{
	if (word->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (!vector_remove(word, 0, item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	expander_word_dup(t_expander_word *dst, t_expander_word *src)
{
	if (!vector_dup(dst, src))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	expander_word_peek(t_expander_word *word, t_expander_word_item *item)
{
	if (word->len == 0)
		return (error(ERR_EMPTY_STACK));
	return (*item = ((t_expander_word_item *)word->data)[0], error(ERR_NO));
}

t_error	expander_word_get(
	t_expander_word *word,
	size_t index,
	t_expander_word_item *item)
{
	if (word->len == 0)
		return (error(ERR_EMPTY_STACK));
	else if (index >= word->len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	return (*item = ((t_expander_word_item *)word->data)[index], error(ERR_NO));
}

```

./srcs/expander/word/expander_word_.h
```c
#ifndef EXPANDER_WORD__H
# define EXPANDER_WORD__H

# include "error.h"
# include "libft.h"
# include "context.h"

typedef t_vector	t_expander_word;

typedef struct s_expander_word_item_opt
{
	t_context	quoted;
	t_context	context;
	bool		is_expand_res;
}	t_expander_word_item_opt;

typedef struct s_expander_word_item
{
	char						c;
	t_expander_word_item_opt	opt;
}	t_expander_word_item;

void					expander_word_init(t_expander_word *word);
void					expander_word_free(t_expander_word *word);
t_expander_word_item	expander_word_item_init(char c, t_context quoted,
							t_context context, bool is_expand_res);

t_error					expander_word_peek(t_expander_word *word,
							t_expander_word_item *item);
t_error					expander_word_push(t_expander_word *word,
							t_expander_word_item item);
t_error					expander_word_pop(t_expander_word *word,
							t_expander_word_item *item);
t_error					expander_word_dup(t_expander_word *dst,
							t_expander_word *src);
t_error					expander_word_get(t_expander_word *word,
							size_t index, t_expander_word_item *item);
t_error					expander_word_remove(t_expander_word *word,
							size_t start, size_t len);
t_error					expander_word_to_str(t_expander_word *word, char **str,
							size_t start, size_t len);
t_error	expander_word_from_str(t_expander_word *word, const char *str,
							t_expander_word_item_opt opt);

#endif
	
```

./srcs/heredoc/_init.c
```c
#include "heredoc.h"
#include "heredoc_queue_.h"
#include "utils.h"

void	heredoc_init(t_heredoc *state)
{
	*(state) = (t_heredoc){0};
	heredoc_queue_init(&state->queue);
	state->file_id = (size_t)get_now_unix_seconds();
}

void	heredoc_free(t_heredoc *state)
{
	heredoc_queue_free(&state->queue);
	*(state) = (t_heredoc){0};
}

void	heredoc_load(t_heredoc *state, bool is_stdin)
{
	state->is_stdin = is_stdin;
}

```

./srcs/heredoc/_utils.c
```c
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "heredoc_.h"
#include "expander.h"

t_error	heredoc_build_delimiter(t_heredoc *state, char **delim)
{
	char	*delim_;
	t_buff	delim_buff;
	char	**delim_exp;

	if (!buff_init(&delim_buff, 0, *delim, (long)str_len(*delim)))
		return (state->err = error_sys());
	state->err = expander_expand_word(
		&delim_exp,
		delim_buff,
		NULL,
		EXPANDER_HEREDOC_DELIMITER);
	if (state->err.type || delim_exp == NULL)
		return (buff_free(&delim_buff), free(*delim), state->err);
	buff_free(&delim_buff);
	if (delim_exp[0] == NULL)
		return (free(*delim), str_array_free(&delim_exp), state->err);
	delim_ = str_join(delim_exp[0], "\n");
	if (delim_ == NULL)
		state->err = error_sys();
	str_array_free(&delim_exp);
	return (free(*delim), *delim = delim_, state->err);
}

static t_error	heredoc_build_path(t_heredoc *state, char **path)
{
	char	*id;
	t_buff	path_buff;

	if (!buff_init(&path_buff, 0, /*"/tmp/minishell_heredoc_"*/"/home/alexander/Documents/42/common_core/minishell/heredoc_", 59))
		return (state->err = error_sys());
	id = ft_ltoa((long)state->file_id);
	if (id == NULL || id[0] == '-')
		return (free(id), buff_free(&path_buff), state->err = error_sys());
	if (!buff_append(&path_buff, id, (long)str_len(id)))
		return (free(id), buff_free(&path_buff), state->err = error_sys());
	free(id);
	*path = buff_get_string(&path_buff);
	if (*path == NULL)
		return (buff_free(&path_buff), state->err = error_sys());
	return (buff_free(&path_buff), state->err);
}

t_error	heredoc_create_file(t_heredoc *state, char **path)
{
	int	fd;

	fd = -1;
	while (fd == -1)
	{
		if (heredoc_build_path(state, path).type)
			return (state->err);
		fd = open(*path, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd == -1 && errno != EEXIST)
			return (free(*path), state->err = error_sys());
		if (fd == -1)
			free(*path);
		state->file_id++;
	}
	return (close(fd), state->err);
}

```

./srcs/heredoc/API.c
```c
#include <stdlib.h>
#include "shell.h"
#include "heredoc_.h"
#include "heredoc_body_.h"
#include "heredoc_queue_.h"

t_error	heredoc_store_all(char *input, size_t *start)
{
	t_heredoc_queue_item	item;
	t_heredoc				*state;

	state = shell_get_heredoc();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	while (state->queue.len != 0)
	{
		state->err = heredoc_queue_pop(&state->queue, &item);
		if (state->err.type)
			return (state->err);
		if (state->is_stdin)
			heredoc_body_store(state, &item, NULL, NULL);
		else
			heredoc_body_store(state, &item, input, start);
		if (state->err.type)
			return (state->err);
	}
	return (state->err);
}

t_error	heredoc_add_to_queue(char **path, char *delim, t_heredoc_mode mode)
{
	t_heredoc_queue_item	item;
	t_heredoc				*state;

	state = shell_get_heredoc();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (heredoc_create_file(state, path).type)
		return (state->err);
	item.path = str_dup(*path);
	if (item.path == NULL)
		return (free(*path), state->err = error_sys());
	item.delim = str_dup(delim);
	if (item.delim == NULL)
		return (free(*path), free(item.path), state->err = error_sys());
	if (heredoc_build_delimiter(state, &item.delim).type)
		return (free(*path), heredoc_queue_item_free(&item), state->err);
	item.mode = mode;
	state->err = heredoc_queue_push(&state->queue, item);
	if (state->err.type)
		return (free(*path), heredoc_queue_item_free(&item), state->err);
	return (state->err);
}

```

./srcs/heredoc/body/_init.c
```c
#include <stdlib.h>
#include "heredoc_body_.h"
#include "heredoc_queue_.h"

void	heredoc_body_init(t_heredoc_body *state)
{
	*(state) = (t_heredoc_body){0};
	buff_init(&state->content, 0, NULL, 0);
}

void	heredoc_body_free(t_heredoc_body *state)
{
	buff_free(&state->content);
	heredoc_queue_item_free(state->item);
	if (state->input != NULL)
		free(state->input);
	if (state->line != NULL)
		free(state->line);
	*(state) = (t_heredoc_body){0};
}

t_error	heredoc_body_load(
	t_heredoc_body *state,
	t_heredoc_queue_item *item,
	char *input,
	size_t *i)
{
	state->i = i;
	state->item = item;
	if (input != NULL)
	{
		state->input = str_dup(input);
		if (state->input == NULL)
			return (state->err = error_sys());
	}
	return (state->err);
}

```

./srcs/heredoc/body/_main.c
```c
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "reader_.h"
#include "heredoc_body_.h"

t_error	heredoc_body_get_content_no_tty(t_heredoc_body *state)
{
	char	*match_EOL;

	if (state->input == NULL)
		return (state->err = error(ERR_NO_DELIM));
	while (true)
	{
		match_EOL = str_chr(state->input + *state->i, '\n');
		if (match_EOL == NULL)
			return (state->err = error(ERR_NO_DELIM));
		else if (heredoc_body_extract_line(state, match_EOL, state->i).type)
			return (state->err);
		if (is_line_delimiter(state))
			return (state->err);
		else if (heredoc_body_line_to_content(state).type)
			return (state->err);
	}
}

static t_error	heredoc_body_tty_EOI(t_heredoc_body *state, size_t *i)
{
	state->line = str_dup(state->input + *i);
	if (state->line == NULL)
		return (state->err = error_sys());
	return (*i = 0, free(state->input), state->input = NULL, state->err);
}

t_error	heredoc_body_get_content_tty(t_heredoc_body *state)
{
	size_t	i;
	char	*match_EOL;

	i = 0;
	while (true)
	{
		if (state->input == NULL)
		{
			state->err = reader_heredoc(&state->input);
			if (state->err.type)
				return (state->err);
		}
		match_EOL = str_chr(state->input + i, '\n');
		if (match_EOL == NULL)
		{
			if (heredoc_body_tty_EOI(state, &i).type)
				return (state->err);
		}
		else if (heredoc_body_extract_line(state, match_EOL, &i).type)
			return (state->err);
		if (is_line_delimiter(state))
			return (state->err);
		else if (heredoc_body_line_to_content(state).type)
			return (state->err);
	}
}

t_error	heredoc_body_store(
	t_heredoc *state,
	t_heredoc_queue_item *item,
	char *input,
	size_t *start)
{
	t_heredoc_body	body;

	heredoc_body_init(&body);
	if (heredoc_body_load(&body, item, input, start).type)
		return (heredoc_body_free(&body), state->err = body.err);
	if (!state->is_stdin)
	{
		if (heredoc_body_get_content_no_tty(&body).type)
			return (heredoc_body_free(&body), state->err = body.err);
	}
	else
	{
		if (heredoc_body_get_content_tty(&body).type)
			return (heredoc_body_free(&body), state->err = body.err);
	}
	if (heredoc_body_save_content(&body).type)
		return (heredoc_body_free(&body), state->err = body.err);
	return (heredoc_body_free(&body), state->err);
}

```

./srcs/heredoc/body/_utils.c
```c
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "heredoc_body_.h"

t_error	heredoc_body_save_content(t_heredoc_body *state)
{
	int	fd;

	fd = open(state->item->path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (state->err = error_sys());
	if (write(fd, state->content.data, state->content.len) == -1)
		state->err = error_sys();
	return (close(fd), state->err);
}

t_error	heredoc_body_line_to_content(t_heredoc_body *state)
{
	size_t	line_len;

	line_len = str_len(state->line);
	if (!buff_append(&state->content, state->line, (long)line_len))
		return (state->err = error_sys());
	return (free(state->line), state->line = NULL, state->err);
}

t_error	heredoc_body_extract_line(t_heredoc_body *state, char *EOL, size_t *i)
{
	char	*start;
	size_t	line_len;

	start = state->input + *i;
	*i += (size_t)(EOL - start) + 1;
	line_len = (size_t)(EOL - start) + 1;
	state->line = str_sub(start, 0, line_len);
	if (state->line == NULL)
		state->err = error_sys();
	return (state->err);
}

bool	is_line_delimiter(t_heredoc_body *state)
{
	size_t	delim_len;
	char	*trimmed_line;

	delim_len = str_len(state->item->delim);
	if (state->item->mode == HEREDOC_MODE_TAB_STRIP)
	{
		trimmed_line = str_trim_leading(state->line, "\t");
		if (trimmed_line == NULL)
			return (state->err = error_sys(), true);
		free(state->line);
		state->line = trimmed_line;
	}
	return (!str_ncmp(state->line, state->item->delim, delim_len));
}

```

./srcs/heredoc/body/heredoc_body_.h
```c
#ifndef HEREDOC_BODY__H
# define HEREDOC_BODY__H

# include "heredoc.h"

/**
 * @ingroup heredoc
 * @struct s_heredoc_body
 * @brief Scratch state for reading and storing one heredoc body.
 *
 * @var s_heredoc_body::i Cursor into the source text; in non-interactive mode
 *                        it borrows the caller's input index, advanced as lines
 *                        are consumed.
 * @var s_heredoc_body::err Last error recorded while reading the body.
 * @var s_heredoc_body::item The heredoc being filled (owned for the body's
 *                           lifetime; released by heredoc_body_free()).
 * @var s_heredoc_body::input Text the body is read from: a deep copy of the
 *                            caller's buffer (non-interactive) or the
 *                            accumulated terminal input (interactive); owned.
 * @var s_heredoc_body::line Current line being examined (owned).
 * @var s_heredoc_body::content Accumulated body bytes to write out (owned).
 */
typedef struct s_heredoc_body
{
	size_t					*i;
	t_error					err;
	t_heredoc_queue_item	*item;
	char					*input;
	char					*line;
	t_buff					content;
}	t_heredoc_body;

/**
 * @ingroup heredoc
 * @brief Initialises a body state to an empty, ready-to-use value.
 *
 * Zeroes the structure and initialises the content buffer.
 *
 * @param state Pointer to the body state to initialise (borrowed).
 */
void	heredoc_body_init(t_heredoc_body *state);

/**
 * @ingroup heredoc
 * @brief Releases every resource held by a body state.
 *
 * Frees the content buffer, the owned heredoc item (its path and delimiter),
 * the input copy and the current line, then resets the structure to zero.
 *
 * @param state Pointer to the body state to free (borrowed).
 */
void	heredoc_body_free(t_heredoc_body *state);

/**
 * @ingroup heredoc
 * @brief Binds a body state to its item and input source.
 *
 * Stores the item and cursor and, in non-interactive mode, takes a deep copy
 * of @p input so the body owns the text it reads.
 *
 * @param state Pointer to the body state (borrowed).
 * @param item Heredoc to fill (ownership held for the body's lifetime).
 * @param input Source text to copy and scan, or NULL for interactive reading.
 * @param i Cursor into @p input (borrowed), advanced as the body is read.
 * @return ERR_NO on success, or ERR_LIBC if the input copy fails.
 */
t_error	heredoc_body_load(t_heredoc_body *state, t_heredoc_queue_item *item,
			char *input, size_t *i);

/**
 * @ingroup heredoc
 * @brief Tests whether the current line is the heredoc delimiter.
 *
 * In TAB_STRIP mode the line's leading tabs are removed first (replacing the
 * stored line), then it is compared against the newline-terminated delimiter
 * for a full-line match.
 *
 * @param state Pointer to the body state (borrowed).
 * @return true if the line is the delimiter (or on allocation failure, with
 *         state->err set), false otherwise.
 */
bool	is_line_delimiter(t_heredoc_body *state);

/**
 * @ingroup heredoc
 * @brief Writes the accumulated body to the heredoc's temporary file.
 *
 * Truncates and opens the item's path, writes the collected content and
 * closes the file.
 *
 * @param state Pointer to the body state (borrowed).
 * @return ERR_NO on success, or ERR_LIBC on open or write failure.
 */
t_error	heredoc_body_save_content(t_heredoc_body *state);

/**
 * @ingroup heredoc
 * @brief Appends the current line to the body content and clears it.
 *
 * Copies the current line into the content buffer, then frees it and sets the
 * line pointer back to NULL.
 *
 * @param state Pointer to the body state (borrowed).
 * @return ERR_NO on success, or ERR_LIBC on allocation failure.
 */
t_error	heredoc_body_line_to_content(t_heredoc_body *state);

/**
 * @ingroup heredoc
 * @brief Extracts the next line (up to and including @p match_EOL) from input.
 *
 * Stores the newline-terminated line in state->line and advances @p i past it.
 *
 * @param state Pointer to the body state (borrowed).
 * @param match_EOL Pointer to the line's terminating newline within the input.
 * @param i In/out cursor into the input, advanced past the extracted line.
 * @return ERR_NO on success, or ERR_LIBC on allocation failure.
 */
t_error	heredoc_body_extract_line(t_heredoc_body *state, char *match_EOL,
			size_t *i);

/**
 * @ingroup heredoc
 * @brief Reads one heredoc's body to completion and stores it.
 *
 * Sets up a private body state, reads lines until the delimiter (interactively
 * when @p input is NULL, otherwise from @p input with @p start advanced),
 * writes the collected body to the heredoc's temporary file, and frees all
 * scratch state including the item. The outcome is mirrored into
 * @p state->err.
 *
 * @param state Pointer to the owning heredoc state (borrowed); receives the
 *              resulting error.
 * @param item Heredoc to fill (consumed: freed by this call).
 * @param input Source text in non-interactive mode (borrowed), or NULL to read
 *              interactively.
 * @param start In/out cursor into @p input, advanced past the consumed body.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	heredoc_body_store(t_heredoc *state, t_heredoc_queue_item *item,
			char *input, size_t *start);

#endif

```

./srcs/heredoc/heredoc_.h
```c
#ifndef HEREDOC__H
# define HEREDOC__H

# include "error.h"
# include "heredoc.h"

/**
 * @ingroup heredoc
 * @brief Creates a fresh, uniquely named temporary file for a heredoc body.
 *
 * Builds a path from the state's monotonic counter and opens it with
 * O_CREAT | O_EXCL; on a name clash it bumps the counter and retries, so the
 * returned path is guaranteed not to collide with an existing file. The file
 * is created empty and closed immediately; the body is written later.
 *
 * @param state Pointer to the heredoc state (borrowed); its file counter is
 *              advanced.
 * @param path Out-parameter receiving the newly allocated path (owned by the
 *             caller on success, freed internally on failure).
 * @return ERR_NO on success, or ERR_LIBC on allocation or open failure.
 */
t_error	heredoc_create_file(t_heredoc *state, char **path);

/**
 * @ingroup heredoc
 * @brief Turns a raw delimiter word into the string body lines match against.
 *
 * Removes the quotes from @p *delim and appends a trailing newline, so the
 * result matches a whole body line exactly. On success the old @p *delim is
 * replaced by a freshly allocated string; the previous pointer is not freed
 * here (the caller owns whatever it passed in).
 *
 * @param state Pointer to the heredoc state (borrowed).
 * @param delim In/out delimiter; on success @p *delim points to a new owned
 *              string, on failure it is left untouched.
 * @return ERR_NO on success, or ERR_LIBC on allocation failure.
 */
t_error	heredoc_build_delimiter(t_heredoc *state, char **delim);

#endif

```

./srcs/heredoc/queue/_init.c
```c
#include <stdlib.h>
#include "heredoc_queue_.h"

void	heredoc_queue_item_free(void *item)
{
	t_heredoc_queue_item	*item_;

	item_ = (t_heredoc_queue_item *)item;
	free(item_->path);
	free(item_->delim);
	*item_ = (t_heredoc_queue_item){0};
}

void	heredoc_queue_init(t_heredoc_queue *queue)
{
	vector_init(queue, sizeof(t_heredoc_queue_item), 0);
}

void	heredoc_queue_free(t_heredoc_queue *queue)
{
	vector_free(queue, heredoc_queue_item_free);
}

```

./srcs/heredoc/queue/_utils.c
```c
#include "heredoc_queue_.h"

t_error	heredoc_queue_push(t_heredoc_queue *queue, t_heredoc_queue_item item)
{
	if (!vector_push(queue, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	heredoc_queue_pop(t_heredoc_queue *queue, t_heredoc_queue_item *item)
{
	if (queue->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (!vector_remove(queue, 0, item))
		return (error_sys());
	return (error(ERR_NO));
}

```

./srcs/heredoc/queue/heredoc_queue_.h
```c
#ifndef HEREDOC_QUEUE__H
# define HEREDOC_QUEUE__H

# include "heredoc.h"

/**
 * @ingroup heredoc
 * @brief Frees the owned fields of one queued heredoc item.
 *
 * Frees the item's path and delimiter, then zeroes the item. Used as the
 * per-element destructor when freeing the queue. The @c void* signature lets
 * it serve as the vector element-free callback.
 *
 * @param item Pointer to the t_heredoc_queue_item to release (borrowed shell,
 *             owned contents).
 */
void	heredoc_queue_item_free(void *item);

/**
 * @ingroup heredoc
 * @brief Initialises an empty heredoc queue.
 *
 * @param queue Pointer to the queue to initialise (borrowed).
 */
void	heredoc_queue_init(t_heredoc_queue *queue);

/**
 * @ingroup heredoc
 * @brief Frees a heredoc queue and every item it still holds.
 *
 * Releases each remaining item through heredoc_queue_item_free() and the queue
 * storage itself.
 *
 * @param queue Pointer to the queue to free (borrowed).
 */
void	heredoc_queue_free(t_heredoc_queue *queue);

/**
 * @ingroup heredoc
 * @brief Appends a heredoc item to the back of the queue.
 *
 * The item is copied into the queue by value; the queue thereby takes
 * ownership of the item's path and delimiter pointers.
 *
 * @param queue Pointer to the queue (borrowed).
 * @param item Item to enqueue (its owned pointers are transferred to the
 *             queue on success).
 * @return ERR_NO on success, or ERR_LIBC on allocation failure.
 */
t_error	heredoc_queue_push(t_heredoc_queue *queue, t_heredoc_queue_item item);

/**
 * @ingroup heredoc
 * @brief Removes the front heredoc item from the queue.
 *
 * Copies the oldest item into @p item and drops it from the queue, moving
 * ownership of its path and delimiter to the caller.
 *
 * @param queue Pointer to the queue (borrowed).
 * @param item Out-parameter receiving the dequeued item (its pointers become
 *             owned by the caller).
 * @return ERR_NO on success, ERR_EMPTY_STACK if the queue is empty, or
 *         ERR_LIBC on failure.
 */
t_error	heredoc_queue_pop(t_heredoc_queue *queue, t_heredoc_queue_item *item);

#endif

```

./srcs/history/_init.c
```c
#include "error.h"
#include "history_.h"

void	history_init(t_history *state)
{
	*state = (t_history){0};
	history_list_init(&state->list);
	history_file_init(&state->file);
	history_rl_init(&state->rl_history);
	buff_init(&state->current_input, 0, NULL, 0);
}

void	history_free(t_history *state)
{
	history_list_free(&state->list);
	history_file_free(&state->file);
	buff_free(&state->current_input);
	history_rl_free(&state->rl_history);
	*state = (t_history){0};
}

t_error	history_load(t_history *state)
{
	ssize_t	max;

	if (history_load_path_env(state).type)
		return (state->err);
	if (history_load_size_env(state).type)
		return (state->err);
	max = state->rl_history.max;
	if (history_file_load(&state->file, &state->list, max).type)
		return (state->err = state->file.err);
	if (history_rl_load(&state->rl_history, &state->list).type)
		return (state->err = state->rl_history.err);
	return (state->err);
}

```

./srcs/history/_utils.c
```c
#include <stdlib.h>
#include "utils.h"
#include "history.h"

static t_error	history_prepare_entry(
	t_history *state,
	t_buff *content,
	char *entry)
{
	char 	*serial_entry;

	state->err = serialize(entry, &serial_entry);
	if (state->err.type)
		return (free(entry), state->err);
	if (!buff_append(content, serial_entry, (long)str_len(serial_entry)))
		return (free(serial_entry), free(entry), state->err = error_sys());
	if (!buff_append(content, "\n", 1))
		return (free(serial_entry), free(entry), state->err = error_sys());
	return (free(serial_entry), serial_entry = NULL, state->err);
}

static t_error	history_build_from_current(t_history *state, t_buff *content)
{
	char	*entry;

	if (state->current_input.len != 0)
	{
		if (state->current_input.data[state->current_input.len - 1] == '\n')
			state->current_input.len--;
		entry = buff_get_string(&state->current_input);
		if (entry == NULL)
			return (error_sys());
		if (history_prepare_entry(state, content, entry).type)
			return (free(entry), state->err);
		free(entry);
	}
	return (state->err);
}

static t_error	history_build_from_list(
	t_history *state,
	t_buff *content,
	size_t start)
{
	size_t	i;
	char	*entry;

	i = start;
	while (i < state->list.len)
	{
		state->err = history_list_get(&state->list, &entry, i);
		if (state->err.type)
			return (state->err);
		if (history_prepare_entry(state, content, entry).type)
			return (free(entry), state->err);
		free(entry);
		entry = NULL;
		i++;
	}
	return (state->err);
}

t_error	history_build_file_content(t_history *state, size_t start)
{
	t_buff	content;

	free(state->file.content);
	buff_init(&content, 0, NULL, 0);
	if (history_build_from_list(state, &content, start).type)
		return (buff_free(&content), state->err);
	if (history_build_from_current(state, &content).type)
		return (buff_free(&content), state->err);
	state->file.content = buff_get_string(&content);
	if (state->file.content == NULL)
		return (buff_free(&content), state->err = error_sys());
	return (buff_free(&content), state->err);
}

```

./srcs/history/API.c
```c
#include "shell.h"
#include <stdlib.h>
#include "error.h"
#include "history.h"
#include "history_.h"

t_error	history_save_entry(void)
{
	char		*entry;
	t_history	*state;
	
	state = shell_get_history();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (state->current_input.len == 0)
		return (state->err);
	if (state->current_input.data[state->current_input.len - 1] == '\n')
		state->current_input.len--;
	entry = buff_get_string(&state->current_input);
	if (entry == NULL)
		return (state->err = error_sys());
	state->err = history_list_push(&state->list, entry);
	if (state->err.type)
		return (free(entry), state->err);
	buff_free(&state->current_input);
	buff_init(&state->current_input, 0, NULL, 0);
	if (history_rl_add(&state->rl_history, &state->list, 1).type)
		return (state->err = state->rl_history.err);
	return (state->err);
}

t_error	history_append_to_entry(char *entry)
{
	t_history	*state;

	state = shell_get_history();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (!buff_append(&state->current_input, entry, (long)str_len(entry)))
		return (state->err = error_sys());
	return (state->err);
}

t_error	history_save(void)
{
	t_history	*state;

	state = shell_get_history();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (history_build_file_content(state, state->file.loaded_count).type)
		return (state->err);
	return (state->err = history_file_write(&state->file));
}

```

./srcs/history/file/_init.c
```c
#include <stdlib.h>
#include "utils.h"
#include "history_file_.h"

void	history_file_init(t_history_file *state)
{
	*state = (t_history_file){0};
}

void	history_file_free(t_history_file *state)
{
	free(state->content);
	*state = (t_history_file){0};
}

t_error	history_file_load(t_history_file *state, t_history_list *list, ssize_t max)
{
	size_t		i;
	char		*entry;
	t_vector	file_entries;

	if (history_file_read(state).type)
		return (state->err);
	state->err = deserialize_all(state->content, &file_entries);
	if (state->err.type)
		return (state->err);
	i = 0;
	while (file_entries.len > 0 && (max < 0 || i < (size_t)max))
	{
		if (!vector_remove(&file_entries, file_entries.len - 1, &entry))
			return (vector_free(&file_entries, free), state->err = error_sys());
		state->err = history_list_insert(list, entry, 0);
	 	if (state->err.type)
	 		return (vector_free(&file_entries, free), free(entry), state->err);
		entry = NULL;
		i++;
	}
	state->loaded_count = list->len;
	vector_free(&file_entries, free);
	return (state->err);
}

```

./srcs/history/file/_main.c
```c
#include <fcntl.h>
#include <unistd.h>
#include "history_file_.h"

t_error	history_file_read(t_history_file *state)
{
	int		fd;
	t_buff	content_buff;

	if (history_file_open(state, &fd, O_RDONLY).type)
		return (state->err);
	buff_init(&content_buff, 0, NULL, 0);
	if (!buff_read_all(&content_buff, fd))
		return (buff_free(&content_buff), state->err = error_sys());
	close(fd);
	if (content_buff.len == 0)
		return (buff_free(&content_buff), state->err);
	state->content = buff_get_string(&content_buff);
	if (state->content == NULL)
		return (buff_free(&content_buff), state->err = error_sys());
	return (buff_free(&content_buff), state->err);
}

t_error	history_file_write(t_history_file *state)
{
	int	fd;

	if (history_file_open(state, &fd, O_WRONLY | O_APPEND).type)
		return (state->err);
	if (write(fd, state->content, str_len(state->content)) == -1)
		return (close(fd), state->err = error_sys());
	return (close(fd), state->err);
}

```

./srcs/history/file/_utils.c
```c
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "history_file_.h"

t_error	history_file_open(t_history_file *state, int *fd, int flags)
{
	*fd = open(state->path, flags, 0644);
	if (*fd == -1 && errno != ENOENT)
		return (state->err = error_sys());
	if (*fd == -1)
	{
		*fd = open(state->path, O_CREAT | flags, 0644);
		if (*fd == -1)
			return (state->err = error_sys());
	}
	return (state->err);
}

```

./srcs/history/file/history_file_.h
```c
#ifndef HISTORY_FILE__H
# define HISTORY_FILE__H

# include "error.h"
# include "history_list_.h"

/**
 * @ingroup history
 * @struct s_history_file
 * @brief On-disk backing of the history.
 *
 * @var s_history_file::err Last error recorded by the file backing.
 * @var s_history_file::path Path of the history file (owned).
 * @var s_history_file::content Working buffer holding serialised entries,
 *                              consumed while parsing and rebuilt before
 *                              writing (owned).
 * @var s_history_file::loaded_count Number of entries loaded from the file,
 *                                   marking the prefix already persisted.
 */
typedef struct s_history_file
{
	t_error	err;
	char 	*path;
	char	*content;
	size_t	loaded_count;
}	t_history_file;

/**
 * @ingroup history
 * @brief Initialises a file backing to a zeroed value.
 *
 * @param state Pointer to the file backing to initialise (borrowed).
 */
void	history_file_init(t_history_file *state);

/**
 * @ingroup history
 * @brief Frees the content buffer and resets the file backing.
 *
 * @param state Pointer to the file backing to free (borrowed).
 */
void	history_file_free(t_history_file *state);

/**
 * @ingroup history
 * @brief Reads and parses the history file into @p list.
 *
 * Reads the whole file, then extracts entries from newest to oldest,
 * inserting each at the front of @p list so chronological order is preserved,
 * keeping at most @p max entries (@p max < 0 means no limit). Records the
 * resulting count in state->loaded_count.
 *
 * @param state Pointer to the file backing (borrowed).
 * @param list Destination entry list, which takes ownership of each entry.
 * @param max Maximum number of entries to keep, or a negative value for all.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	history_file_load(t_history_file *state, t_history_list *list, ssize_t max);

/**
 * @ingroup history
 * @brief Opens the history file, creating it when missing.
 *
 * Opens state->path with @p flags, retrying with O_CREAT if the file does
 * not exist.
 *
 * @param state Pointer to the file backing (borrowed).
 * @param fd Out-parameter receiving the opened descriptor.
 * @param flags open(2) flags to use.
 * @return ERR_NO on success, ERR_LIBC on failure.
 */
t_error	history_file_open(t_history_file *state, int *fd, int flags);

/**
 * @ingroup history
 * @brief Reads the whole history file into state->content.
 *
 * Leaves state->content NULL when the file is empty.
 *
 * @param state Pointer to the file backing (borrowed).
 * @return ERR_NO on success, ERR_LIBC on failure.
 */
t_error	history_file_read(t_history_file *state);

/**
 * @ingroup history
 * @brief Appends state->content to the history file on disk.
 *
 * @param state Pointer to the file backing (borrowed).
 * @return ERR_NO on success, ERR_LIBC on failure.
 */
t_error	history_file_write(t_history_file *state);

#endif

```

./srcs/history/history_.h
```c
#ifndef HISTORY__H
# define HISTORY__H

#include "history.h"

/**
 * @ingroup history
 * @brief Resolves the history file path from the environment.
 *
 * Reads $HISTFILE, falling back to $HOME/.sh_history when it is unset, and
 * stores the resulting path in state->file.path.
 *
 * @param state Pointer to the history state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	history_load_path_env(t_history *state);

/**
 * @ingroup history
 * @brief Resolves the history size cap from the environment.
 *
 * Reads $HISTSIZE into state->rl_history.max. An unset value means unlimited
 * (-1); any non-negative value below 128 is raised to 128.
 *
 * @param state Pointer to the history state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	history_load_size_env(t_history *state);

/**
 * @ingroup history
 * @brief Builds the file content buffer from the list tail.
 *
 * Serialises and concatenates the list entries from index @p start onward
 * into state->file.content, replacing any previous content.
 *
 * @param state Pointer to the history state (borrowed).
 * @param start Index of the first list entry to include.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	history_build_file_content(t_history *state, size_t start);

#endif

```

./srcs/history/list/_init.c
```c
#include <stdlib.h>
#include "history_list_.h"

void	history_list_clean(void *item)
{
	char	*str;

	str = *(char **)item;
	if (str)
		free(str);
}

void	history_list_init(t_history_list *list)
{
	*list = (t_history_list){0};
	vector_init(list, sizeof(char *), 0);
}

void	history_list_free(t_history_list *list)
{
	vector_free(list, history_list_clean);
	*list = (t_history_list){0};
}

```

./srcs/history/list/_main.c
```c
#include <stdlib.h>
#include "history_list_.h"

t_error	history_list_push(t_history_list *list, char *item)
{
	if (!vector_push(list, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	history_list_insert(t_history_list *list, char *item, size_t index)
{
	if (!vector_insert(list, index, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	history_list_get(t_history_list *list, char **item, size_t i)
{
	char	*item_;

	if (list->len == 0)
		return (error(ERR_EMPTY_STACK));
	else if (i >= list->len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	item_ = str_dup(((char **)list->data)[i]);
	if (item_ == NULL)
		return (error_sys());
	return (*item = item_, error(ERR_NO));
}

```

./srcs/history/list/history_list_.h
```c
#ifndef HISTORY_LIST__H
# define HISTORY_LIST__H

# include "error.h"
# include "libft.h"

/**
 * @ingroup history
 * @brief In-memory history entries, stored as a vector of owned strings.
 *
 * Each element is a heap-allocated, plain (non-serialised) entry string owned
 * by the list. Entries enter as owned pointers and leave only as deep copies.
 */
typedef t_vector	t_history_list;

/**
 * @ingroup history
 * @brief Frees one stored entry (vector element destructor).
 *
 * @param item Pointer to the stored entry string to free.
 */
void	history_list_clean(void *item);

/**
 * @ingroup history
 * @brief Initialises an empty entry list.
 *
 * @param list Pointer to the list to initialise (borrowed).
 */
void	history_list_init(t_history_list *list);

/**
 * @ingroup history
 * @brief Frees the list and every entry it owns.
 *
 * @param list Pointer to the list to free (borrowed).
 */
void	history_list_free(t_history_list *list);

/**
 * @ingroup history
 * @brief Appends an entry to the list, taking ownership of @p item.
 *
 * @param list Pointer to the list (borrowed).
 * @param item Entry string whose ownership is transferred to the list.
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	history_list_push(t_history_list *list, char *item);

/**
 * @ingroup history
 * @brief Returns a serialised copy of the entry at index @p i.
 *
 * Duplicates the stored entry and encodes it for storage; the returned
 * *item is freshly allocated and owned by the caller.
 *
 * @param list Pointer to the list (borrowed).
 * @param item Out-parameter receiving the freshly allocated copy.
 * @param i Index of the entry to read.
 * @return ERR_NO on success, ERR_EMPTY_STACK if the list is empty,
 *         ERR_INDEX_OUT_OF_BOUND if @p i is past the end, or ERR_LIBC on
 *         allocation failure.
 */
t_error	history_list_get(t_history_list *list, char **item, size_t i);

/**
 * @ingroup history
 * @brief Inserts an entry at @p index, taking ownership of @p item.
 *
 * @param list Pointer to the list (borrowed).
 * @param item Entry string whose ownership is transferred to the list.
 * @param index Position at which to insert the entry.
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	history_list_insert(t_history_list *list, char *item, size_t index);

#endif

```

./srcs/history/load_env.c
```c
#include <stdlib.h>
#include "params.h"
#include "history.h"

t_error	history_load_path_env(t_history *state)
{
	char	*path;

	state->err = params_get("HISTFILE", &state->file.path);
	if (state->err.type && state->err.type != ERR_VAR_NOT_FOUND)
		return (state->err);
	if (state->err.type == ERR_VAR_NOT_FOUND || state->file.path == NULL)
	{
		state->err = params_get("HOME", &path);
		if (state->err.type && state->err.type != ERR_VAR_NOT_FOUND)
			return (state->err);
		state->file.path = str_join(path, "/.sh_history");
		if (state->file.path == NULL)
			return (free(path), state->err = error_sys());
		free(path);
	}
	return (state->err = error(ERR_NO));
}

t_error	history_load_size_env(t_history *state)
{
	ssize_t	max;
	char	*max_str;
	
	state->err = params_get("HISTSIZE", &max_str);
	if (state->err.type && state->err.type != ERR_VAR_NOT_FOUND)
		return (state->err);
	if (state->err.type == ERR_VAR_NOT_FOUND || max_str == NULL)
		state->rl_history.max = -1;
	else
	{
		max = (ssize_t)ft_atol(max_str);
		state->rl_history.max = max;
		if (max >= 0 && max < 128)
			state->rl_history.max = 128;
	}
	return (state->err = error(ERR_NO));
}

```

./srcs/history/readline/_init.c
```c
#include <stdio.h>
#include <readline/readline.h>
#include "history_readline_.h"

void	history_rl_init(t_history_rl *state)
{
	state->count = 0;
}

void	history_rl_free(t_history_rl *state)
{
	rl_clear_history();
	state->count = 0;
}

t_error	history_rl_load(t_history_rl *state, t_history_list *list)
{
	return (history_rl_add(state, list, list->len));
}

```

./srcs/history/readline/_main.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include "history_list_.h"
#include "history_readline_.h"

t_error	history_rl_add(t_history_rl *state, t_history_list *list, size_t count)
{
	ssize_t	i;
	char	*entry;
	ssize_t	entries_to_add;

	if (count == 0)
		return (state->err);
	entries_to_add = history_rl_to_add_count(state, count);
	if (entries_to_add < 0)
	{
		history_rl_free(state);
		entries_to_add = -entries_to_add;
	}
	i = (ssize_t)list->len - entries_to_add;
	if (i < 0)
		i = 0;
	while ((size_t)i < list->len)
	{
		state->err = history_list_get(list, &entry, (size_t)i++);
		if (state->err.type)
			return (state->err);
		add_history(entry);
		free(entry);
		state->count++;
	}
	return (state->err);
}

```

./srcs/history/readline/_utils.c
```c
#include "history_readline_.h"

ssize_t	history_rl_to_add_count(t_history_rl *state, size_t count)
{
	if (state->max < 0)
		return ((ssize_t)count);
	else if (state->count + count > (size_t)(state->max))
		return (-(ssize_t)state->max);
	else
		return ((ssize_t)count);
}

```

./srcs/history/readline/history_readline_.h
```c
#ifndef HISTORY_READLINE__H
# define HISTORY_READLINE__H

# include "error.h"
# include "history_list_.h"

/**
 * @ingroup history
 * @struct s_history_rl
 * @brief Bookkeeping for the entries mirrored into readline's history.
 *
 * readline keeps its own private copies of the strings it is given; this
 * structure only tracks how many entries were mirrored and the cap to honour.
 *
 * @var s_history_rl::err Last error recorded while mirroring.
 * @var s_history_rl::max Maximum number of entries to keep, or -1 for
 *                        unlimited.
 * @var s_history_rl::count Number of entries currently mirrored in readline.
 */
typedef struct s_history_rl
{
	t_error	err;
	ssize_t	max;
	size_t	count;
}	t_history_rl;

/**
 * @ingroup history
 * @brief Initialises the readline bookkeeping.
 *
 * @param state Pointer to the readline bookkeeping (borrowed).
 */
void	history_rl_init(t_history_rl *state);

/**
 * @ingroup history
 * @brief Clears readline's history and resets the mirrored count.
 *
 * @param state Pointer to the readline bookkeeping (borrowed).
 */
void	history_rl_free(t_history_rl *state);

/**
 * @ingroup history
 * @brief Mirrors the whole entry list into readline.
 *
 * @param state Pointer to the readline bookkeeping (borrowed).
 * @param list Entry list to mirror (borrowed; copied out, never owned).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	history_rl_load(t_history_rl *state, t_history_list *list);

/**
 * @ingroup history
 * @brief Computes how many of the last entries readline should add.
 *
 * Returns @p count when below the cap. A negative result signals that the
 * readline history must be cleared first because the cap was reached; its
 * magnitude is the number of entries to re-add.
 *
 * @param state Pointer to the readline bookkeeping (borrowed).
 * @param count Number of new entries being considered.
 * @return The count to add, negated when a clear-and-refill is required.
 */
ssize_t	history_rl_to_add_count(t_history_rl *state, size_t count);

/**
 * @ingroup history
 * @brief Adds the last @p count list entries to readline.
 *
 * Honours the cap (clearing and refilling when it is reached). Each entry is
 * deep copied out of the list and copied again by readline, so the list keeps
 * ownership of its data.
 *
 * @param state Pointer to the readline bookkeeping (borrowed).
 * @param list Entry list to read from (borrowed).
 * @param count Number of trailing entries to add.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	history_rl_add(t_history_rl *state, t_history_list *list, size_t count);

#endif

```

./srcs/main.c
```c
#include "shell.h"
# include <locale.h>	// DEBUG
# include "logs.h"		// DEBUG

int	main(int argc, char **argv, char **envp)
{
	t_error	err;

	setlocale(LC_NUMERIC, "de_DE");	// DEBUG
	err = shell_run(argc, argv, envp);
	if (err.type)
		error_print(err);
	shell_free();
	print_stop();
	setlocale(LC_NUMERIC, "");	// DEBUG
	return ((int)err.type);
}

```

./srcs/params/1_life_cycle.c
```c
#include "params.h"
#include <stdlib.h>

void	params_init(t_params *params)
{
	params->name = NULL;
	var_init(&params->variables);
	options_init(&params->options);
	specials_init(&params->specials);
	positionals_init(&params->positionals);
}

void	params_free(t_params *params)
{
	params->name = NULL;
	var_free(&params->variables);
	options_free(&params->options);
	specials_free(&params->specials);
	positionals_free(&params->positionals);
}

```

./srcs/params/1_options/1_life_cycle.c
```c
#include "options.h"

void	options_init(t_option *options)
{
	*options = 0u;
}

void	options_free(t_option *options)
{
	(void)options;
	return ;
}

```

./srcs/params/1_options/2_helpers.c
```c
#include "shell.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG

// TODO: masque une potentielle erreur !
bool	option_is_active(t_option option)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (false);
	return ((params->options & option) != 0);
}

bool	option_is_active_in(t_option options, t_option option)
{
	return ((options & option) != 0);
}

void	option_set(t_option *options, t_option option, bool on)
{
	if (on)
		print_pass("Setting ON  option %s\n", option_to_string(option));
	else
		print_pass("Setting OFF option %s\n", option_to_string(option));
	if (on)
		*options |= option;
	else
		*options &= ~option;
}

static void	options_add_to_string(t_option options, char **dst, size_t *i_ptr)
{
	size_t	i;

	i = *i_ptr;
	if (option_is_active_in(options, OPT_MONITOR))
		(*dst)[i++] = 'm';
	if (option_is_active_in(options, OPT_NOEXEC))
		(*dst)[i++] = 'n';
	if (option_is_active_in(options, OPT_NOUNSET))
		(*dst)[i++] = 'u';
	if (option_is_active_in(options, OPT_VERBOSE))
		(*dst)[i++] = 'v';
	if (option_is_active_in(options, OPT_XTRACE))
		(*dst)[i++] = 'x';
	if (option_is_active_in(options, OPT_CMD_STRING))
		(*dst)[i++] = 'c';
	if (option_is_active_in(options, OPT_STDIN_INPUT))
		(*dst)[i++] = 's';
	*i_ptr = i;
}

t_error	options_get(t_option options, char **dst)
{
	size_t	i;

	*dst = malloc(OPT_SINGLE_COUNT + 1);
	if (!*dst)
		return (error_sys());
	i = 0;
	if (option_is_active_in(options, OPT_EXPORT_ALL))
		(*dst)[i++] = 'a';
	if (option_is_active_in(options, OPT_NOTIFY))
		(*dst)[i++] = 'b';
	if (option_is_active_in(options, OPT_NOCLOBBER))
		(*dst)[i++] = 'C';
	if (option_is_active_in(options, OPT_ERREXIT))
		(*dst)[i++] = 'e';
	if (option_is_active_in(options, OPT_NOGLOB))
		(*dst)[i++] = 'f';
	if (option_is_active_in(options, OPT_HASHALL))
		(*dst)[i++] = 'h';
	if (option_is_active_in(options, OPT_INTERACTIVE))
		(*dst)[i++] = 'i';
	options_add_to_string(options, dst, &i);
	(*dst)[i] = '\0';
	return (error(ERR_NO));
}

```

./srcs/params/1_options/3_flags.c
```c
#include "options.h"

static inline bool	options_process_flag1(t_option *options, char flag, bool on)
{
	if (flag == 'a')
		option_set(options, OPT_EXPORT_ALL, on);
	else if (flag == 'b')
		option_set(options, OPT_NOTIFY, on);
	else if (flag == 'C')
		option_set(options, OPT_NOCLOBBER, on);
	else if (flag == 'e')
		option_set(options, OPT_ERREXIT, on);
	else if (flag == 'f')
		option_set(options, OPT_NOGLOB, on);
	else if (flag == 'h')
		option_set(options, OPT_HASHALL, on);
	else if (flag == 'i')
		option_set(options, OPT_INTERACTIVE, on);
	else
		return (false);
	return (true);
}

static inline bool	options_process_flag2(
	t_option *options,
	char flag,
	bool on,
	bool *explicit_plus_m)
{
	if (flag == 'm')
	{
		option_set(options, OPT_MONITOR, on);
		*explicit_plus_m = !on;
	}
	else if (flag == 'n')
		option_set(options, OPT_NOEXEC, on);
	else if (flag == 'u')
		option_set(options, OPT_NOUNSET, on);
	else if (flag == 'v')
		option_set(options, OPT_VERBOSE, on);
	else if (flag == 'x')
		option_set(options, OPT_XTRACE, on);
	else if (flag == 'c')
		option_set(options, OPT_CMD_STRING, on);
	else if (flag == 's')
		option_set(options, OPT_STDIN_INPUT, on);
	else
		return (false);
	return (true);
}

t_error	options_process_flag(
	t_option *options,
	char flag,
	bool on,
	bool *explicit_plus_m)
{
	char flag_string[2];

	if (options_process_flag1(options, flag, on))
		return (error(ERR_NO));
	if (options_process_flag2(options, flag, on, explicit_plus_m))
		return (error(ERR_NO));
	flag_string[0] = flag;
	flag_string[1] = '\0';
	error_print(error(ERR_OPT_INVALID), flag_string, NULL, NULL);
	return (error(ERR_OPT_INVALID));
}

```

./srcs/params/1_options/4_named.c
```c
#include "libft.h"
#include "options.h"

static bool	options_process_name1(
	t_option *options,
	const char *arg,
	bool on,
	bool *explicit_plus_m)
{
	if (str_cmp(arg, "allexport") == 0)
		option_set(options, OPT_EXPORT_ALL, on);
	else if (str_cmp(arg, "errexit") == 0)
		option_set(options, OPT_ERREXIT, on);
	else if (str_cmp(arg, "monitor") == 0)
	{
		option_set(options, OPT_MONITOR, on);
		*explicit_plus_m = !on;
	}
	else if (str_cmp(arg, "noclobber") == 0)
		option_set(options, OPT_NOCLOBBER, on);
	else if (str_cmp(arg, "noglob") == 0)
		option_set(options, OPT_NOGLOB, on);
	else if (str_cmp(arg, "noexec") == 0)
		option_set(options, OPT_NOEXEC, on);
	else if (str_cmp(arg, "notify") == 0)
		option_set(options, OPT_NOTIFY, on);
	else
		return (false);
	return (true);
}

static bool	options_process_name2(t_option *options, const char *arg, bool on)
{
	if (str_cmp(arg, "nounset") == 0)
		option_set(options, OPT_NOUNSET, on);
	else if (str_cmp(arg, "verbose") == 0)
		option_set(options, OPT_VERBOSE, on);
	else if (str_cmp(arg, "xtrace") == 0)
		option_set(options, OPT_XTRACE, on);
	else if (str_cmp(arg, "ignoreeof") == 0)
		option_set(options, OPT_IGNOREEOF, on);
	else if (str_cmp(arg, "nolog") == 0)
		option_set(options, OPT_NOLOG, on);
	else if (str_cmp(arg, "pipefail") == 0)
		option_set(options, OPT_PIPEFAIL, on);
	else if (str_cmp(arg, "vi") == 0)
		option_set(options, OPT_VI, on);
	else
		return (false);
	return (true);
}

t_error	options_process_name(
	t_option *options,
	const char *arg,
	bool on,
	bool *explicit_plus_m)
{
	if (options_process_name1(options, arg, on, explicit_plus_m))
		return (error(ERR_NO));
	if (options_process_name2(options, arg, on))
		return (error(ERR_NO));
	error_print(error(ERR_OPT_INVALID_ARG), arg, NULL, NULL);
	return (error(ERR_OPT_INVALID_ARG));
}

```

./srcs/params/1_options/5_load.c
```c
#include "options_priv.h"
#include "ft_getopt.h"
#include "logs.h"
#include <unistd.h>

static void	options_build_getopt_in(t_getopt_in *in)
{
	static const char				*valid_flags = "abCefhimnuvxcs";
	static const char				*valid_o_args[] = {
		"allexport", "errexit", "monitor", "noclobber", "noglob", "noexec",
		"notify", "nounset", "verbose", "xtrace", "ignoreeof", "nolog",
		"pipefail", "vi", NULL};
	static t_getopt_flag_with_arg	flags_w_arg[] = {
	{'-', 'o', valid_o_args, false},
	{'+', 'o', valid_o_args, false}
	};

	in->builtin_name = "sh";
	in->ub_on_repeated_flags = true;
	in->single_delimiter = true;
	in->valid_minus_flags = valid_flags;
	in->valid_plus_flags = valid_flags;
	in->options_with_arg = flags_w_arg;
	in->options_with_arg_count = sizeof(flags_w_arg) / sizeof(*flags_w_arg);
}

// @ret ERR_OPT_INVALID
static t_error	options_apply_getopt_out(
	t_option *options,
	t_getopt_out *out,
	bool *explicit_plus_m)
{
	t_getopt_option	option;
	size_t			i;
	t_error			err;

	i = 0;
	while (i < out->options.len)
	{
		option = ((t_getopt_option *)out->options.data)[i];
		if (!option.argument)
			err = options_process_flag(
				options, option.flag, option.sign == '-', explicit_plus_m);
		else
			err = options_process_name(
				options, option.argument, option.sign == '-', explicit_plus_m);
		if (err.type != ERR_NO)
			return (err);
		i++;
	}
	return (error(ERR_NO));
}

static void	options_finalize(
	t_option *options,
	size_t remaining_args,
	bool explicit_plus_m)
{
	if (!option_is_active_in(*options, OPT_CMD_STRING) && remaining_args == 0)
		option_set(options, OPT_STDIN_INPUT, true);
	if (option_is_active_in(*options, OPT_STDIN_INPUT)
		&& isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
		option_set(options, OPT_INTERACTIVE, true);
	if (option_is_active_in(*options, OPT_INTERACTIVE) && !explicit_plus_m)
		option_set(options, OPT_MONITOR, true);
}

t_error	options_load(
	t_option *options,
	int argc,
	char **argv,
	size_t *start_index)
{
	t_getopt_in		in;
	t_getopt_out	out;
	bool			explicit_plus_m;
	size_t			remaining_args;
	t_error			err;

	print_title("options_load()");
	*options = 0u;
	explicit_plus_m = false;
	options_build_getopt_in(&in);
	err = ft_getopt(argc, argv, &in, &out);
	if (err.type != ERR_NO)
		return (err);
	err = options_apply_getopt_out(options, &out, &explicit_plus_m);
	vector_free(&out.options, NULL);
	if (err.type != ERR_NO)
		return (err);
	*start_index = out.first_operand_index;
	print_result("options_load()");
	print_title("options_finalize()");
	if (*start_index >= (size_t)argc)
		remaining_args = 0;
	else
		remaining_args = (size_t)argc - *start_index;
	options_finalize(options, remaining_args, explicit_plus_m);
	print_result("options_finalize()");
	return (error(ERR_NO));
}

```

./srcs/params/1_options/6_dump.c
```c
#include "options.h"
# include <stdio.h>
# include "debug.h"

const char	*option_to_string(t_option option)
{
	if (option == OPT_EXPORT_ALL)
		return ("a");
	else if (option == OPT_NOTIFY)
		return ("b");
	else if (option == OPT_NOCLOBBER)
		return ("C");
	else if (option == OPT_ERREXIT)
		return ("e");
	else if (option == OPT_NOGLOB)
		return ("f");
	else if (option == OPT_HASHALL)
		return ("h");
	else if (option == OPT_INTERACTIVE)
		return ("i");
	else if (option == OPT_MONITOR)
		return ("m");
	else if (option == OPT_NOEXEC)
		return ("n");
	else if (option == OPT_NOUNSET)
		return ("u");
	else if (option == OPT_VERBOSE)
		return ("v");
	else if (option == OPT_XTRACE)
		return ("x");
	else if (option == OPT_CMD_STRING)
		return ("c");
	else if (option == OPT_STDIN_INPUT)
		return ("s");
	else if (option == OPT_IGNOREEOF)
		return ("ignoreeof");
	else if (option == OPT_NOLOG)
		return ("nolog");
	else if (option == OPT_PIPEFAIL)
		return ("pipefail");
	else if (option == OPT_VI)
		return ("vi");
	return ("unknown");
}

void	options_dump(void)
{
	unsigned int	option;
	const char		*name;
	const char		*value;

	fprintf(stderr, "\nDUMP OPTIONS\n");
	option = 1u << 0;
	while (option <= OPT_VI)
	{
		name = option_to_string(option);
		value = bool_to_string(option_is_active(option));
		fprintf(stderr, "OPTION %s=%s\n", name, value);
		option <<= 1;
	}
}

```

./srcs/params/1_options/options_priv.h
```c
#ifndef OPTIONS_PRIV_H
# define OPTIONS_PRIV_H

# include "options.h"

// @ret ERR_OPT_INVALID
t_error	options_process_flag(
	t_option *options,
	char flag,
	bool on,
	bool *explicit_plus_m);

// @ret ERR_OPT_INVALID_ARG
t_error	options_process_name(
	t_option *options,
	const char *arg,
	bool on,
	bool *explicit_plus_m);

#endif

```

./srcs/params/1_options/options.h
```c
#ifndef OPTIONS_H
# define OPTIONS_H

# include "error.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

# define OPT_EXPORT_ALL		(1u << 0)	// -a: all variables are exported by default
# define OPT_NOTIFY			(1u << 1)	// -b: immediate notification of terminated jobs
# define OPT_NOCLOBBER		(1u << 2)	// -C: prevent file overwrite with '>'
# define OPT_ERREXIT		(1u << 3)	// -e: exit on command error
# define OPT_NOGLOB			(1u << 4)	// -f: disable pathname expansion (globbing)
# define OPT_HASHALL		(1u << 5)	// -h: remember command locations (hashing)
# define OPT_INTERACTIVE	(1u << 6)	// -i: shell is interactive (not settable via 'set')
# define OPT_MONITOR		(1u << 7)	// -m: enable job control
# define OPT_NOEXEC			(1u << 8)	// -n: read commands but do not execute
# define OPT_NOUNSET		(1u << 9)	// -u: error on unset variables
# define OPT_VERBOSE		(1u << 10)	// -v: print input lines as read
# define OPT_XTRACE			(1u << 11)	// -x: print commands and arguments after expansion
# define OPT_CMD_STRING		(1u << 12)	// -c: read commands from command_string instead of stdin/file
# define OPT_STDIN_INPUT	(1u << 13)	// -s: read commands from standard input
# define OPT_IGNOREEOF		(1u << 14)	// -o ignoreeof: prevent an interactive shell from exiting on end-of-file
# define OPT_NOLOG			(1u << 15)	// -o nolog: prevent function definitions from being entered in command history (may have no effect)
# define OPT_PIPEFAIL		(1u << 16)	// -o pipefail: derive pipeline exit status from all commands, not just the last one
# define OPT_VI				(1u << 17)	// -o vi: enable shell command line editing using the built-in vi editor
# define OPT_SINGLE_COUNT	14

typedef uint32_t	t_option;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	options_init(t_option *options);
void	options_free(t_option *options);

// @ret ERR_OPT_INVALID / ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG / ERR_LIBC
t_error	options_load(
	t_option *options,
	int argc,
	char **argv,
	size_t *start_index);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

void	option_set(t_option *options, t_option option, bool on);
bool	option_is_active(t_option option);
bool	option_is_active_in(t_option options, t_option option);

// @ret ERR_NO / ERR_LIBC
t_error	options_get(t_option options, char **dst);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

void		options_dump(void);
const char	*option_to_string(t_option option);

#endif

```

./srcs/params/2_load.c
```c
#include "params.h"
#include <stdlib.h>

// TODO: check what POSIX means by "If both '-' and '--' are given as **ARGUMENTS**"
static void	params_catch_undefined_1(int argc, char **argv)
{
	int		i;
	bool	single_found;
	bool	double_found;

	single_found = false;
	double_found = false;
	i = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == '\0')
			double_found = true;
		else if (argv[i][0] == '-' && argv[i][1] == '\0')
			single_found = true;
		if (single_found && double_found)
			undefined_behaviour("POSIX: sh: OPERANDS: "
				"If both '-' and '--' are given as arguments, "
				"the results are undefined");
		i++;
	}
}

static void	params_catch_undefined_2(int argc, char **argv, int start)
{
	if (argv[start - 1][0] != '-' || argv[start - 1][1] != '-' || argv[start - 1][2] != '\0')
		start++;
	while (start < argc)
	{
		if (argv[start][0] == '-' && argv[start][1] == '\0')
			undefined_behaviour("POSIX: sh: OPERANDS: "
				"If other operands precede the single "
				"<hyphen-minus>, the results are undefined");
		start++;
	}
}

t_error	params_load(t_params *params, int argc, char **argv, char **envp)
{
	t_error	err;
	size_t	start_index;
	
	params_catch_undefined_1(argc, argv);
	params->name = argv[0];
	start_index = 1;
	err = options_load(&params->options, argc, argv, &start_index);
	if (err.type != ERR_NO)
		return (err);
	params_catch_undefined_2(argc, argv, (int)start_index);
	err = specials_load(&params->specials, argc, argv, &start_index);
	if (err.type != ERR_NO)
		return (err);
	err = positionals_load(&params->positionals, argc, argv, start_index);
	if (err.type != ERR_NO)
		return (err);
	err = var_load(&params->variables, envp);
	if (err.type != ERR_NO)
		return (err);
	/* ---------- DEBUG: START ---------- */
	// var_dump();
	// options_dump();
	// specials_dump();
	// positionals_dump();
	// params_dump();
	/* ---------- DEBUG: END ---------- */
	return (error(ERR_NO));
}

```

./srcs/params/2_specials/1_life_cycle.c
```c
#include "specials.h"
#include <stdlib.h>

void	specials_init(t_specials *specials)
{
	specials->zero = NULL;
	specials->source = NULL;
	specials->pid = -1;
	specials->last_bg_pid = -1;
	specials->last_status = 0;
}

void	specials_free(t_specials *specials)
{
	specials_init(specials);
}

```

./srcs/params/2_specials/2_load.c
```c
#include "asm_stubs.h"
#include "options.h"
#include "specials.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG
# include <inttypes.h>	// DEBUG

// @ret ERR_OPT_INVALID
static t_error	specials_load_cmd_string(
	t_specials *specials,
	int argc,
	char **argv,
	size_t *operand_index)
{
	if ((size_t)argc < *operand_index + 1)
	{
		error_print(error(ERR_OPT_INVALID), "-c needs an argument", NULL, NULL);
		return (error(ERR_OPT_INVALID));
	}
	specials->source = argv[(*operand_index)++];
	if ((size_t)argc >= *operand_index + 1)
		specials->zero = argv[(*operand_index)++];
	print_pass("command_string (-c) mode initialized\n");
	print_pass("zero set to              '%s'\n", specials->zero);
	print_pass("source set to            '%s'\n", specials->source);
	return (error(ERR_NO));
}

// @ret ERR_SHELL_NOT_FOUND / ERR_OPT_INVALID
static t_error	specials_load_source_and_zero(
	t_specials *specials,
	int argc,
	char **argv,
	size_t *operand_index)
{
	specials->source = NULL;
	specials->zero = argv[0];
	if (option_is_active(OPT_CMD_STRING))
		return (specials_load_cmd_string(specials, argc, argv, operand_index));
	else if (option_is_active(OPT_STDIN_INPUT))
	{
		print_pass("standard_input (-s) mode initialized\n");
		// return (error(ERR_NO));
	}
	else if ((size_t)argc >= *operand_index + 1)
	{
		print_pass("command_file mode initialized\n");
		specials->source = argv[(*operand_index)++];
		specials->zero = specials->source;
	}
	print_pass("zero set to              '%s'\n", specials->zero);
	print_pass("source set to            '%s'\n", specials->source);
	return (error(ERR_NO));
}

t_error	specials_load(
	t_specials *specials,
	int argc,
	char **argv,
	size_t *start_index)
{
	t_error	err;

	print_title("specials_load()");
	err = specials_load_source_and_zero(specials, argc, argv, start_index);
	if (err.type != ERR_NO)
		return (err);
	specials->last_bg_pid = -1;
	print_pass("last_bg_pid set to       %jd\n", (intmax_t)specials->last_bg_pid);
	specials->last_status = EXIT_SUCCESS;
	print_pass("last_status set to       %i\n", specials->last_status);
	specials->pid = ft_getpid();
	print_pass("pid set to               %jd\n", (intmax_t)specials->pid);
	print_result("specials_load()");
	return (error(ERR_NO));
}

```

./srcs/params/2_specials/3_get_set.c
```c
#include "libft.h"
#include "specials.h"

t_error	specials_get(const t_specials *specials, char name, char **dst)
{
	*dst = NULL;
	if (name == '0')
		*dst = str_dup(specials->zero);
	else if (name == '$')
		*dst = ft_pidtoa(specials->pid);
	else if (name == '!')
	{
		if (specials->last_bg_pid == -1)
			return (error(ERR_NO));
		*dst = ft_pidtoa(specials->last_bg_pid);
	}
	else if (name == '?')
		*dst = ft_ltoa(specials->last_status);
	else
		return (error(ERR_VAR_NOT_FOUND));
	if (*dst == NULL)
		return (error_sys());
	return (error(ERR_NO));
}

void	specials_set_last_bg_pid(t_specials *specials, pid_t value)
{
	specials->last_bg_pid = value;
}

void	specials_set_last_status(t_specials *specials, int value)
{
	specials->last_status = value;
}

```

./srcs/params/2_specials/4_dump.c
```c
#include "shell.h"
# include <stdio.h>

void	specials_dump(void)
{
	t_shell 	*shell;
	t_specials	*specials;

	fprintf(stderr, "\nDUMP SPECIALS\n");
	shell = shell_get();
	if (!shell)
		error_print(error(ERR_SHELL_NOT_FOUND), "specials_dump()", NULL, NULL);
	specials = &shell->params.specials;
	if (specials->source)
		fprintf(stderr, "SPECIAL source='%s'\n", specials->source);
	else
		fprintf(stderr, "SPECIAL source=NULL\n");
	if (specials->zero)
		fprintf(stderr, "SPECIAL 0='%s'\n", specials->zero);
	else
		fprintf(stderr, "SPECIAL 0=NULL\n");
	fprintf(stderr, "SPECIAL $=%jd\n", (intmax_t)specials->pid);
	fprintf(stderr, "SPECIAL !=%jd\n", (intmax_t)specials->last_bg_pid);
	fprintf(stderr, "SPECIAL ?=%i\n", specials->last_status);
}

```

./srcs/params/2_specials/specials.h
```c
#ifndef SPECIALS_H
# define SPECIALS_H

# include "error.h"
# include <stddef.h>
# include <sys/types.h>

typedef struct s_specials
{
	char	*source;		// (internal, can be NULL)
	char	*zero;			// $0 (NOT editable after instanciation)
	pid_t	pid;			// $$ (NOT editable after instanciation)
	pid_t	last_bg_pid;	// $!
	int		last_status;	// $?
}	t_specials;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	specials_init(t_specials *specials);

// @ret ERR_NO / ERR_SHELL_NOT_FOUND / ERR_OPT_INVALID.
t_error	specials_load(
	t_specials *specials,
	int argc,
	char **argv,
	size_t *start_index);
	
void	specials_free(t_specials *specials);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// @warning: *dst is owned by caller, he must free it.
// @ret ERR_NO / ERR_VAR_NOT_FOUND / ERR_LIBC.
t_error	specials_get(const t_specials *specials, char name, char **dst);
void	specials_set_last_bg_pid(t_specials *specials, pid_t value);
void	specials_set_last_status(t_specials *specials, int value);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

void	specials_dump(void);

#endif

```

./srcs/params/3_get.c
```c
#include "libft.h"
#include "shell.h"

static bool	params_is_special(char name)
{
	static const char specials[] = "0$!?";

	return (str_chr(specials, name) != NULL);
}

t_error	params_get(const char *name, char **dst)
{
	t_params	*params;

	*dst = NULL;
	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	if (name[0] == '\0')
		return (error(ERR_NO));
	if (name[0] == '-' && name[1] == '\0')
		return (options_get(params->options, dst));
	if (name[0] == '#' && name[1] == '\0')
		return (positionals_get_one(&params->positionals, name, dst));
	if (name[1] == '\0' && params_is_special(name[0]))
		return (specials_get(&params->specials, name[0], dst));
	if (ft_isdigit(name[0]))
		return (positionals_get_one(&params->positionals, name, dst));
	return (var_get(name, dst));
}

t_error	params_get_positionals(t_positionals *dst)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (positionals_get(&params->positionals, dst));
}

t_error	params_build_envp(char ***dst_envp)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (var_build_envp(&params->variables, dst_envp));
}

```

./srcs/params/3_positionals/1_life_cycle.c
```c
#include "positionals.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG

void	positionals_init(t_positionals_stack *stack)
{
	vector_init(stack, sizeof(t_positionals), 0);
}

static t_error	positionals_free_partial(t_positionals *positionals)
{
	size_t	i;
	t_error	err;

	err = error_sys();
	i = 0;
	while (i < positionals->count)
		free(positionals->params[i++]);
	free(positionals->params);
	positionals->params = NULL;
	return (err);
}

t_error	positionals_load(
	t_positionals_stack *stack,
	int argc,
	char **argv,
	size_t start_index)
{
	t_positionals	positionals;

	print_title("positionals_load()");
	positionals.params = NULL;
	positionals.count = 0;
	if (start_index < (size_t)argc)
	{
		positionals.params =
			malloc(sizeof(*positionals.params) * ((size_t)argc - start_index));
		if (!positionals.params)
			return (error_sys());
	}
	while (start_index < (size_t)argc)
	{
		positionals.params[positionals.count] = str_dup(argv[start_index]);
		if (!positionals.params[positionals.count])
			return (positionals_free_partial(&positionals));
		positionals.count++;
		print_pass("$%zu = '%s'\n", positionals.count, argv[start_index]);
		start_index++;
	}
	if (!vector_push(stack, &positionals))
		return (positionals_free_partial(&positionals));
	print_pass("$# = %zu\n", positionals.count);
	print_result("positionals_load()");
	return (error(ERR_NO));
}

void	positionals_free_item(void *positionals)
{
	size_t			i;
	t_positionals	*casted;

	casted = (t_positionals *)positionals;
	i = 0;
	while (i < casted->count)
	{
		free(casted->params[i]);
		i++;
	}
	free(casted->params);
	casted->params = NULL;
	casted->count = 0;
}

void	positionals_free(t_positionals_stack *stack)
{
	vector_free(stack, positionals_free_item);
}

```

./srcs/params/3_positionals/2_ops.c
```c
#include "positionals.h"
#include "positionals_priv.h"
#include <stdlib.h>

t_error	positionals_push(
	t_positionals_stack *stack,
	t_positionals *positionals)
{
	if (!vector_push(stack, positionals))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	positionals_pop(t_positionals_stack *stack)
{
	if (stack->len <= 1)
		return (error(ERR_NO));
	if (!vector_pop(stack, positionals_free_item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	positionals_replace(
	t_positionals_stack *stack,
	t_positionals *positionals)
{
	if (stack->len == 0)
		return (error(ERR_VAR_NOT_FOUND));
	if (!vector_pop(stack, positionals_free_item))
		return (error_sys());
	if (!vector_push(stack, positionals))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	positionals_shift(t_positionals_stack *stack, size_t n)
{
	t_positionals	*positionals;
	size_t			i;

	if (n == 0)
		return (error(ERR_NO));
	if (stack->len == 0)
		return (error(ERR_VAR_NOT_FOUND));
	positionals = &((t_positionals *)stack->data)[stack->len - 1];
	if (n > positionals->count)
		return (error(ERR_SHIFT_INVALID_VALUE));
	i = 0;
	while (i < n)
		free(positionals->params[i++]);
	i = 0;
	while (i + n < positionals->count)
	{
		positionals->params[i] = positionals->params[i + n];
		i++;
	}
	while (i < positionals->count)
		positionals->params[i++] = NULL;
	positionals->count -= n;
	return (error(ERR_NO));
}

```

./srcs/params/3_positionals/3_get.c
```c
#include "positionals.h"
#include <stdint.h>

t_error	positionals_get(const t_positionals_stack *stack, t_positionals *dst)
{
	if (stack->len == 0)
		return (error(ERR_VAR_NOT_FOUND));
	*dst = ((t_positionals *)stack->data)[stack->len - 1];
	return (error(ERR_NO));
}

static bool	positionals_name_is_digits_only(const char *name)
{
	size_t	i;

	i = 0;
	while (name[i])
	{
		if (name[i] < '0' || name[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

t_error	positionals_get_one(
	const t_positionals_stack *stack,
	const char *name,
	char **dst)
{
	t_error			err;
	t_positionals	current;
	size_t			index;

	*dst = NULL;
	err = positionals_get(stack, &current);
	if (err.type != ERR_NO)
		return (err);
	if (name[0] == '#' && name[1] == '\0')
	{
		*dst = ft_zutoa(current.count);
		if (!*dst)
			return (error_sys());
		return (error(ERR_NO));
	}
	if (!positionals_name_is_digits_only(name))
		return (error(ERR_VAR_INVALID_NAME));
	index = ft_atozu(name);
	if (index == 0 || index > current.count || index == SIZE_MAX)
		return (error(ERR_VAR_NOT_FOUND));
	*dst = str_dup(current.params[index - 1]);
	if (!*dst)
		return (error_sys());
	return (error(ERR_NO));
}

```

./srcs/params/3_positionals/4_dump.c
```c
#include "shell.h"
# include <stdio.h>

static void	positionals_dump_depth(t_positionals_stack *stack, size_t depth)
{
	t_positionals	*positionals;
	size_t			count;
	size_t			i;

	positionals = &((t_positionals *)stack->data)[depth];
	count = positionals->count;
	i = 0;
	while (i < count)
	{
		fprintf(stderr, "POSITIONALS[%zu] %zu='%s'\n", depth, i, positionals->params[i]);
		i++;
	}
	fprintf(stderr, "POSITIONALS #=%zu\n", count);
}

void	positionals_dump(void)
{
	t_shell 			*shell;
	t_positionals_stack	*stack;
	size_t				count;
	size_t				i;

	fprintf(stderr, "\nDUMP POSITIONALS\n");
	shell = shell_get();
	if (!shell)
		error_print(error(ERR_SHELL_NOT_FOUND), "positionals_dump()", NULL, NULL);
	stack = &shell->params.positionals;
	count = stack->len;
	i = 0;
	while (i < count)
	{
		positionals_dump_depth(stack, i);
		i++;
		if (i < count)
			fprintf(stderr, "---\n");
	}
}

```

./srcs/params/3_positionals/positionals_priv.h
```c
#ifndef POSITIONALS_PRIV_H
# define POSITIONALS_PRIV_H

// 'void *' to match the vector_free() callback signature
void	positionals_free_item(void *positionals);

#endif

```

./srcs/params/3_positionals/positionals.h
```c
#ifndef POSITIONALS_H
# define POSITIONALS_H

# include "libft.h"
# include "error.h"

typedef struct s_positionals
{
	char	**params;	// $@ / $* / $n
	size_t	count;		// $#
}	t_positionals;

typedef t_vector	t_positionals_stack;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	positionals_init(t_positionals_stack *stack);

// @ret ERR_NO / ERR_LIBC
t_error	positionals_load(
	t_positionals_stack *stack,
	int argc,
	char **argv,
	size_t start_index);

void	positionals_free(t_positionals_stack *stack);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// @note stack takes ownership of positionals on success only.
// @ret ERR_NO / ERR_LIBC
t_error	positionals_push(
	t_positionals_stack *stack,
	t_positionals *positionals);

// @ret ERR_NO / ERR_VAR_NOT_FOUND / ERR_SHIFT_INVALID_VALUE.
t_error	positionals_shift(t_positionals_stack *stack, size_t n);

// @ret ERR_NO / ERR_LIBC
t_error	positionals_pop(t_positionals_stack *stack);

// @note stack takes ownership of positionals on success only.
// @warning src must not alias any frame already owned by stack.
// @ret ERR_NO / ERR_VAR_NOT_FOUND / ERR_LIBC
t_error	positionals_replace(
	t_positionals_stack *stack,
	t_positionals *positionals);

// @warning dst->params is borrowed; caller must NOT free or mutate it.
// @ret ERR_NO / ERR_VAR_NOT_FOUND
t_error	positionals_get(const t_positionals_stack *stack, t_positionals *dst);

// @warning: caller owns *dst, he must free it.
// @ret ERR_NO / ERR_VAR_NOT_FOUND / ERR_VAR_INVALID_NAME / ERR_LIBC
t_error	positionals_get_one(
	const t_positionals_stack *stack,
	const char *name,
	char **dst);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

void	positionals_dump(void);

#endif

```

./srcs/params/4_set.c
```c
#include "shell.h"

t_error	params_set_variable(
	const char *name,
	const char *value,
	bool export,
	bool readonly)
{
	return (var_set(name, value, export, readonly));
}

t_error	params_unset_variable(const char *name)
{
	return (var_unset(name));
}

t_error	params_set_last_bg_pid(pid_t value)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	specials_set_last_bg_pid(&params->specials, value);
	return (error(ERR_NO));
}

t_error	params_set_last_status(int value)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	specials_set_last_status(&params->specials, value);
	return (error(ERR_NO));
}

t_error	params_set_option(t_option option, bool on)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	option_set(&params->options, option, on);
	return (error(ERR_NO));
}

```

./srcs/params/4_variables/1_life_cycle.c
```c
#include "variables.h"
#include "variables_priv.h"
#include "var_load_envp.h"
#include "var_load_mandatory.h"
#include "var_load_up.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG

t_var	var_new(const char *name, const char *value, bool export, bool ronly)
{
	t_var	res;

	res.name = str_dup(name);
	if (value)
		res.value = str_dup(value);
	else
		res.value = NULL;
	res.export = export;
	res.readonly = ronly;
	return (res);
}

void	var_free_one(void *var)
{
	t_var	*var_casted;

	var_casted = (t_var *)var;
	if (var_casted->name)
		free(var_casted->name);
	var_casted->name = NULL;
	if (var_casted->value)
		free(var_casted->value);
	var_casted->value = NULL;
	var_casted->export = false;
	var_casted->readonly = false;
}

void	var_init(t_var_list *variables)
{
	vector_init(variables, sizeof(t_var), 0);
}

t_error	var_load(t_var_list *variables, char **envp)
{
	t_error	err;

	print_title("var_load_envp()");
	err = var_load_envp(envp);
	if (err.type != ERR_NO)
		return (err);
	print_result("var_load_envp()            => (entries: %'6zu)", variables->len);
	print_title("var_load_mandatory()");
	err = var_load_mandatory();
	if (err.type != ERR_NO)
		return (err);
	print_result("var_load_mandatory()       => (entries: %'6zu)", variables->len);
	print_title("var_load_up()");
	err = var_load_up();
	if (err.type != ERR_NO)
		return (err);
	print_result("var_load_up()              => (entries: %'6zu)", variables->len);
	return (error(ERR_NO));
}

void	var_free(t_var_list *variables)
{
	vector_free(variables, var_free_one);
}

```

./srcs/params/4_variables/2_helpers.c
```c
#include "libft.h"
#include "variables.h"
#include "variables_priv.h"
#include <stdlib.h>

bool	var_find(const t_var_list *variables, const char *name, size_t *res)
{
	size_t	i;
	size_t	len;
	t_var	*curr;

	len = 0;
	while (name[len] != '\0')
		len++;
	i = 0;
	while (i < variables->len)
	{
		curr = &((t_var *)variables->data)[i];
		if (str_ncmp(name, curr->name, len + 1) == 0)
		{
			*res = i;
			return (true);
		}
		i++;
	}
	return (false);
}

```

./srcs/params/4_variables/3_registry.c
```c
#include "libft.h"
#include "shell.h"
#include "variables_priv.h"
#include "options.h"
#include "utils.h"
#include <stdlib.h>

static t_error	var_save_err_and_free(t_var *var)
{
	t_error	err;

	err = error_sys();
	var_free_one(var);
	return (err);
}

// value can be NULL
// @ret ERR_VAR_READ_ONLY / ERR_LIBC
static t_error	var_update_value(
	t_var *var,
	const char *value,
	bool export,
	bool readonly)
{
	char	*new_value;

	if (var->readonly && value)
		return (error(ERR_VAR_READ_ONLY));
	if (value)
	{
		new_value = str_dup(value);
		if (!new_value)
			return (error_sys());
		free(var->value);
		var->value = new_value;
	}
	if (export)
		var->export = true;
	if (readonly)
		var->readonly = true;
	return (error(ERR_NO));
}

t_error	var_set(const char *name, const char *value, bool export, bool readonly)
{
	t_params	*params;
	t_var_list	*list;
	size_t		var_index;
	t_var		*current_var;
	t_var		new_var;

	if (!name_is_valid(name))
		return (error(ERR_VAR_INVALID_NAME));
	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	list = &params->variables;
	if (var_find(list, name, &var_index))
	{
		current_var = &((t_var *)list->data)[var_index];
		return (var_update_value(current_var, value, export, readonly));
	}
	if (option_is_active(OPT_EXPORT_ALL))
		export = true;
	new_var = var_new(name, value, export, readonly);
	if (!new_var.name || (value && !new_var.value))
		return (var_save_err_and_free(&new_var));
	if (!vector_push(list, &new_var))
		return (var_save_err_and_free(&new_var));
	return (error(ERR_NO));
}

t_error	var_get(const char *name, char **dst_val)
{
	t_params	*params;
	t_var_list	*list;
	size_t		var_index;
	t_var		*var;
	char		*res;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	list = &params->variables;
	if (!name_is_valid(name))
		return (error(ERR_VAR_INVALID_NAME));
	if (!var_find(list, name, &var_index))
		return (error(ERR_VAR_NOT_FOUND));
	res = NULL;
	var = &((t_var *)list->data)[var_index];
	if (var->value)
	{
		res = str_dup(var->value);
		if (!res)
			return (error_sys());
	}
	*dst_val = res;
	return (error(ERR_NO));
}

t_error	var_unset(const char *name)
{
	t_params	*params;
	t_var_list	*list;
	size_t		var_index;
	t_var		*var;

	if (!name_is_valid(name))
		return (error(ERR_VAR_INVALID_NAME));
	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	list = &params->variables;
	if (!var_find(list, name, &var_index))
		return (error(ERR_NO));
	var = &((t_var *)list->data)[var_index];
	if (var->readonly)
		return (error(ERR_VAR_READ_ONLY));
	var_free_one(var);
	if (!vector_remove(list, var_index, NULL))
		return (error(ERR_INDEX_OUT_OF_BOUND));
	return (error(ERR_NO));
}

```

./srcs/params/4_variables/4_print.c
```c
#include "shell.h"
#include "variables_priv.h"
#include "posix_helpers.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>

// @ret ERR_LIBC
static t_error	var_print_one(const char *prefix, const t_var *var)
{
	t_buff	buff;
	char	*escaped_value;
	t_error	err;

	if (!buff_init(&buff, 0, prefix, -1))
		return (error_sys());
	if (!buff_append(&buff, var->name, -1))
		return (err = error_sys(), buff_free(&buff), err);
	if (var->value)
	{
		if (!buff_append(&buff, "=", -1))
			return (err = error_sys(), buff_free(&buff), err);
		err = serialize(var->value, &escaped_value);
		if (err.type != ERR_NO)
			return (buff_free(&buff), err);
		if (!buff_append(&buff, escaped_value, -1))
			return (err = error_sys(), free(escaped_value), buff_free(&buff),
				err);
		free(escaped_value);
	}
	if (!buff_append(&buff, "\n", -1))
		return (err = error_sys(), buff_free(&buff), err);
	err = posix_write(STDOUT_FILENO, buff.data, buff.len);
	return (buff_free(&buff), err);
}

t_error	var_print(t_var_print_mode mode)
{
	t_params	*params;
	t_var_list	*list;
	t_var		*var;
	size_t		i;
	t_error		err;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	list = &params->variables;
	i = 0;
	err = error(ERR_NO);
	while (i < list->len)
	{
		var = &((t_var *)list->data)[i];
		if (mode == VAR_PRINT_EXPORT && var->export)
			err = var_print_one("export ", var);
		else if (mode == VAR_PRINT_READONLY && var->readonly)
			err = var_print_one("readonly ", var);
		if (err.type != ERR_NO)
			break ;
		i++;
	}
	return (err);
}

```

./srcs/params/4_variables/5_build_envp.c
```c
#include "variables_priv.h"
#include <stdlib.h>

// @ret ERR_LIBC
static t_error	var_build_entry(
	const char *name,
	const char *value,
	char **dst)
{
	size_t	name_len;
	size_t	value_len;
	size_t	dst_size;

	name_len = str_len(name);
	value_len = str_len(value);
	dst_size = name_len + value_len + 2;
	*dst = malloc(dst_size);
	if (!*dst)
		return (error_sys());
	str_lcpy(*dst, name, dst_size);
	(*dst)[name_len] = '=';
	if (value_len > 0)
		str_lcpy(*dst + name_len + 1, value, dst_size - name_len - 1);
	else
		(*dst)[name_len + 1] = '\0';
	return (error(ERR_NO));
}

t_error	var_build_envp(const t_var_list *variables, char ***dst_envp)
{
	size_t		envp_i;
	size_t		var_i;
	const t_var	*var;
	t_error		err;

	*dst_envp = malloc((variables->len + 1) * sizeof(**dst_envp));
	if (!*dst_envp)
		return (error_sys());
	envp_i = 0;
	var_i = 0;
	while (var_i < variables->len)
	{
		var = &((const t_var *)variables->data)[var_i++];
		if (!var->value || !var->export)
			continue ;
		err = var_build_entry(var->name, var->value, &(*dst_envp)[envp_i]);
		if (err.type != ERR_NO)
			return (str_array_free(dst_envp), err);
		envp_i++;
	}
	(*dst_envp)[envp_i] = NULL;
	return (error(ERR_NO));
}

```

./srcs/params/4_variables/6_dump.c
```c
#include "shell.h"
#include "variables_priv.h"
# include <stdio.h>
# include "debug.h"

void	var_dump_one(t_var *var)
{
	if (var->value)
		fprintf(stderr, "VAR name='%s' value='%s' exported=%s readonly=%s\n",
			var->name,
			var->value,
			bool_to_string(var->export),
			bool_to_string(var->readonly));
	else
		fprintf(stderr, "VAR name='%s' value=NULL exported=%s readonly=%s\n",
			var->name,
			bool_to_string(var->export),
			bool_to_string(var->readonly));
}

void	var_dump(void)
{
	t_shell 	*shell;
	t_var_list	*var_list;
	t_var		*var;
	size_t		i;

	fprintf(stderr, "\nDUMP VARIABLES\n");
	shell = shell_get();
	if (!shell)
	{
		error_print(error(ERR_SHELL_NOT_FOUND), "var_dump()", NULL, NULL);
		return ;
	}
	var_list = &shell->params.variables;
	i = 0;
	while (i < var_list->len)
	{
		var = &((t_var *)var_list->data)[i];
		var_dump_one(var);
		i++;
	}
}

```

./srcs/params/4_variables/load/1_envp/main.c
```c
#include "variables.h"
#include "utils.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG

// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_READ_ONLY / ERR_LIBC.
static t_error	process_variable(
	const char *name,
	const char *value)
{
	t_error	err;

	err = var_set(name, value, true, false);
	if (err.type == ERR_VAR_INVALID_NAME)
		return (error(ERR_NO));
	if (err.type == ERR_NO)
		print_pass("'%s' = '%s'\n", name, value);
	return (err);
}

/*
1. Load envp variables with valid shell names
	- exported = true
	- readonly = false
	- invalid names: do not initialize shell variables from them
*/
t_error	var_load_envp(char **envp)
{
	size_t	i;
	char	*name;
	char	*value;
	t_error	err;

	if (!envp)
		return (error(ERR_NO));
	i = 0;
	while (envp[i])
	{
		err = assignment_split(envp[i++], &name, &value);
		if (err.type != ERR_NO)
			return (err);
		if (!value)
			continue ;
		err = process_variable(name, value);
		free(name);
		free(value);
		if (err.type != ERR_NO)
			return (err);
	}
	return (error(ERR_NO));
}

```

./srcs/params/4_variables/load/1_envp/var_load_envp.h
```c
#ifndef VAR_LOAD_ENVP_H
# define VAR_LOAD_ENVP_H

#include "error.h"

// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_load_envp(char **envp);

#endif

```

./srcs/params/4_variables/load/2_mandatory/1_ifs.c
```c
#include "variables.h"
# include "logs.h"	// DEBUG

/*
cf [2.5.3 Shell Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05_03)
- "The shell shall set IFS to <space><tab><newline> when it is invoked"
*/
t_error	var_set_ifs(void)
{
	t_error	err;
	char	ifs_value[4];

	ifs_value[0] = ' ';
	ifs_value[1] = '\t';
	ifs_value[2] = '\n';
	ifs_value[3] = '\0';
	err = var_set("IFS", ifs_value, false, false);
	if (err.type != ERR_NO)
		return (err);
	print_pass("'IFS' has been set to '%s'\n", ifs_value);
	return (error(ERR_NO));
}

```

./srcs/params/4_variables/load/2_mandatory/2_pwd.c
```c
#include "variables.h"
#include "posix_helpers.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/stat.h>
# include "logs.h"	// DEBUG

static bool pwd_has_no_dot_components(const char *pwd)
{
	size_t	i;
	size_t	start;
	size_t	len;
	
	i = 1;
	while (pwd[i] != '\0')
	{
		start = i;
		while (pwd[i] != '\0' && pwd[i] != '/')
			i++;
		len = i - start;
		if (len == 1 && pwd[start] == '.')
			return (false);
		if (len == 2 && pwd[start] == '.' && pwd[start + 1] == '.')
			return (false);
		while (pwd[i] == '/')
			i++;
	}
	return (true);
}

/*
cf [POSIX.1-2024, Base Definitions, header <sys/stat.h>](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_stat.h.html)
	- "A file identity is uniquely determined by the combination of st_dev and st_ino"
*/
// @ret ERR_LIBC.
static t_error	pwd_is_the_current_working_dir(const char *pwd, bool *res)
{
	struct stat	current;
	struct stat	from_pwd;

	*res = false;
	if (stat(".", &current) == -1)
		return (error_sys());
	if (stat(pwd, &from_pwd) == -1)
	{
		if (errno == ENOENT || errno == ENOTDIR || errno == ELOOP
			|| errno == ENAMETOOLONG)
			return (error(ERR_NO));
		return (error_sys());
	}
	if (current.st_dev != from_pwd.st_dev)
		return (error(ERR_NO));
	if (current.st_ino != from_pwd.st_ino)
		return (error(ERR_NO));
	*res = true;
	return (error(ERR_NO));
}

/*
cf [2.5.3 Shell Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05_03)
	- "the value is an absolute pathname"
	- "the value does not contain any components that are dot or dot-dot"
	- "the value is [...] the current working directory"
*/
// @ret ERR_LIBC.
static t_error	var_pwd_is_valid(const char *pwd, bool *res)
{
	*res = false;
	if (!pwd)
		return (error(ERR_NO));
	if (pwd[0] != '/')
		return (error(ERR_NO));
	if (!pwd_has_no_dot_components(pwd))
		return (error(ERR_NO));
	return (pwd_is_the_current_working_dir(pwd, res));
}

/*
cf [2.5.3 Shell Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05_03)
	a) "If a value for PWD is passed to the shell in the environment when it is executed, the value is an absolute pathname of the current working directory [...optional...] and the value does not contain any components that are dot or dot-dot, then the shell shall set PWD to the value from the environment"
	b) "Otherwise, the sh utility sets PWD to the pathname that would be output by pwd -P" (= getcwd())
*/
t_error	var_set_pwd(void)
{
	char	*pwd;
	t_error	err;
	bool	is_valid;

	err = var_get("PWD", &pwd);
	if (err.type != ERR_NO && err.type != ERR_VAR_NOT_FOUND)
		return (err);
	if (err.type == ERR_NO)
	{
		err = var_pwd_is_valid(pwd, &is_valid);
		free(pwd);
		if (err.type != ERR_NO)
			return (err);
		if (is_valid)
			return (print_pass("'PWD' is already valid\n"), error(ERR_NO));
	}
	err = posix_getcwd(&pwd);
	if (err.type != ERR_NO)
		return (err);
	err = var_set("PWD", pwd, false, false);
	if (err.type == ERR_NO)
		print_pass("'PWD' has been set to '%s'\n", pwd);
	free(pwd);
	return (err);
}

```

./srcs/params/4_variables/load/2_mandatory/3_ppid.c
```c
#include "asm_stubs.h"
#include "variables.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG

/*
cf [2.5.3 Shell Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05_03)
	- Set by the shell to the decimal value of its parent process ID during initialization of the shell
*/
t_error	var_set_ppid(void)
{
	char	*ppid;
	t_error	error;

	ppid = ft_pidtoa(ft_getppid());
	if (!ppid)
		return (error_sys());
	error = var_set("PPID", ppid, false, false);
	print_pass("'PPID' has been set to '%s'\n", ppid);
	free(ppid);
	return (error);
}

```

./srcs/params/4_variables/load/2_mandatory/main.c
```c
#include "error.h"
#include "var_load_mandatory_priv.h"

/*
2. Initialize mandatory variables
	- IFS = <space><tab><newline>
	- PWD = current working directory (from env or self initialized)
	- PPID = parent process id
*/
t_error	var_load_mandatory(void)
{
	t_error	error;

	error = var_set_ifs();
	if (error.type != ERR_NO)
		return (error);
	error = var_set_pwd();
	if (error.type != ERR_NO)
		return (error);
	return (var_set_ppid());
}

```

./srcs/params/4_variables/load/2_mandatory/var_load_mandatory_priv.h
```c
#ifndef VAR_LOAD_MANDATORY_PRIV_H
# define VAR_LOAD_MANDATORY_PRIV_H

# include "error.h"

// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_set_ifs(void);

// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_set_pwd(void);

// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_set_ppid(void);

#endif

```

./srcs/params/4_variables/load/2_mandatory/var_load_mandatory.h
```c
#ifndef VAR_LOAD_MANDATORY_H
# define VAR_LOAD_MANDATORY_H

# include "error.h"

// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_load_mandatory(void);

#endif

```

./srcs/params/4_variables/load/3_up/main.c
```c
#include "variables.h"
#include <stdlib.h>
#include <unistd.h>
# include "logs.h"	// DEBUG

// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
static t_error	var_init_target_up(const char *name, const char *value)
{
	t_error	err;
	char	*current_value;

	err = var_get(name, &current_value);
	if (err.type == ERR_NO)
	{
		free(current_value);
		return (error(ERR_NO));
	}
	if (err.type == ERR_VAR_NOT_FOUND)
		err = var_set(name, value, false, false);
	if (err.type == ERR_NO)
		print_pass("'%s' has been set to '%s'\n", name, value);
	return (err);
}

/*
3. Initialize [UP] defaults if you support User Portability Utilities
	- PS1 = "$ " if absent
	- PS2 = "> " if absent
	- PS4 = "+ " if absent
*/
t_error	var_load_up(void)
{
	t_error	err;

	err = var_init_target_up("PS1", "$ ");
	if (err.type != ERR_NO)
		return (err);
	err = var_init_target_up("PS2", "> ");
	if (err.type != ERR_NO)
		return (err);
	return (var_init_target_up("PS4", "+ "));
}

```

./srcs/params/4_variables/load/3_up/var_load_up.h
```c
#ifndef VAR_LOAD_UP_H
# define VAR_LOAD_UP_H

#include "error.h"

// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_load_up(void);

#endif

```

./srcs/params/4_variables/variables_priv.h
```c
#ifndef VARIABLES_PRIV_H
# define VARIABLES_PRIV_H

# include "variables.h"
# include <stddef.h>

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

typedef struct s_var
{
	char	*name;
	char	*value;
	bool	export;
	bool	readonly;
}	t_var;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

// @warning: if name var.name == NULL => ERR_LIBC
t_var	var_new(const char *name, const char *value, bool export, bool ronly);
void	var_free_one(void *var);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

bool	var_find(const t_var_list *variables, const char *name, size_t *res);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

void	var_dump_one(t_var *var);

#endif

```

./srcs/params/4_variables/variables.h
```c
#ifndef VARIABLES_H
# define VARIABLES_H

# include "libft.h"
# include "error.h"
# include <stdbool.h>

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

typedef t_vector	t_var_list;

typedef enum e_var_print_mode
{
	VAR_PRINT_EXPORT,
	VAR_PRINT_READONLY
}	t_var_print_mode;

/* ************************************************************************* */
/*                                 LIFE CYCLE                                */
/* ************************************************************************* */

void	var_init(t_var_list *variables);

// ERR_VAR_INVALID_NAME / ERR_VAR_NOT_FOUND / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_load(t_var_list *variables, char **envp);

void	var_free(t_var_list *variables);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// @warning: *dst_val can be NULL if var->value == NULL (error will be ERR_NO).
// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_INVALID_NAME / ERR_VAR_NOT_FOUND
// 		/ ERR_LIBC.
t_error	var_get(const char *name, char **dst_val);

// @ret ERR_SHELL_NOT_FOUND / ERR_LIBC
t_error	var_print(t_var_print_mode mode);

// value can be NULL.
// export == false and rdonly == false are ignored if variable already exists.
// if variable doesn't exist yet and option_is_active(OPT_EXPORT_ALL)
// 		=> export will be set to true even if export == false.
// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY
// 		/ ERR_LIBC.
t_error	var_set(const char *name, const char *value, bool export, bool rdonly);

// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY /
// 		ERR_INDEX_OUT_OF_BOUND
t_error	var_unset(const char *name);

// @ret ERR_LIBC
t_error	var_build_envp(const t_var_list *variables, char ***dst_envp);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

void	var_dump(void);

#endif

```

./srcs/params/5_edit_positionals.c
```c
#include "shell.h"

t_error	params_push_positionals(t_positionals *src)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (positionals_push(&params->positionals, src));
}

t_error	params_shift_positionals(size_t n)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (positionals_shift(&params->positionals, n));
}

t_error	params_replace_positionals(t_positionals *src)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (positionals_replace(&params->positionals, src));
}

t_error	params_pop_positionals(void)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (positionals_pop(&params->positionals));
}

```

./srcs/params/6_print.c
```c
#include "params.h"

t_error params_print(t_params_print_mode mode)
{
	return var_print((t_var_print_mode)mode);
}

```

./srcs/params/7_dump.c
```c
#include "shell.h"
#include "variables_priv.h"
#include <stdlib.h>
# include <stdio.h>

static void	params_dump_scalar(const char *name)
{
	char		*value;
	t_error		err;

	err = params_get(name, &value);
	if (err.type != ERR_NO)
	{
		fprintf(stderr, "PARAMS '%s'=[ERROR: '%s']\n", name, error_to_string(err));
		return ;
	}
	if (value)
	{
		fprintf(stderr, "PARAMS '%s'='%s'\n", name, value);
		free(value);
	}
	else
		fprintf(stderr, "PARAMS '%s'=NULL\n", name);
}

static void	params_dump_variables(void)
{
	t_shell 	*shell;
	t_var_list	*var_list;
	t_var		*var;
	size_t		i;

	shell = shell_get();
	if (!shell)
		error_print(error(ERR_SHELL_NOT_FOUND), "params_dump_variables()", NULL, NULL);
	var_list = &shell->params.variables;
	i = 0;
	while (i < var_list->len)
	{
		var = &((t_var *)var_list->data)[i];
		params_dump_scalar(var->name);
		i++;
	}
}

static void	params_dump_options(void)
{
	params_dump_scalar("-");
}

static void	params_dump_specials(void)
{
	params_dump_scalar("0");
	params_dump_scalar("$");
	params_dump_scalar("!");
	params_dump_scalar("?");
}

static void	params_dump_positionals(void)
{
	t_shell	*shell;
	t_error	err;
	char	*count_s;
	size_t	count;
	size_t	i;
	char	*name;

	shell = shell_get();
	if (!shell)
	{
		error_print(error(ERR_SHELL_NOT_FOUND), "params_dump_positionals()", NULL, NULL);
		return ;
	}
	err = positionals_get_one(&shell->params.positionals, "#", &count_s);
	if (err.type != ERR_NO)
	{
		error_print(err, "params_dump_positionals()", NULL, NULL);
		return ;
	}
	count = ft_atozu(count_s);
	free(count_s);
	i = 1;
	while (i <= count)
	{
		name = ft_zutoa(i);
		if (!name)
		{
			error_print(error_sys(), "params_dump_positionals()", NULL, NULL);
			break ;
		}
		params_dump_scalar(name);
		free(name);
		i++;
	}
	params_dump_scalar("#");
}

void	params_dump(void)
{
	fprintf(stderr, "\nDUMP PARAMS\n");
	params_dump_variables();
	params_dump_options();
	params_dump_specials();
	params_dump_positionals();
}

```

./srcs/TODO.c
```c
#include "error.h"
#include "expander_.h"
#include <stdbool.h>

// TODO

t_error	path_name_expansion(t_expander *state)
{
	(void)state;
	return (error(ERR_NO));
}

```

./srcs/ub.c
```c
#include "libft.h"
#include "posix_helpers.h"
#include <unistd.h>

#define UB_SUFFIX	"\" 🤪\n ╰──▶ Byyye! 👋\n"

t_error	undefined_behaviour(const char *message)
{
// 	const char	ascii[] = "                                              =..==-==                                              \n
//                                          -=-=-======-=+---                                          \n
//                                      -=======++++++--:.::-=::                                       \n
//                                   :==--=******#######*+-::-===                                      \n
//                                 .==-:+*######*###########*:-=+=                                     \n
//                                .-+-=#####*#################=-#=--                                   \n
//                               :==-*#%%%%#################%##+-=*=-                                  \n
//                               -==+%%%%%%%##########*#####%%%%=-==*+-                                \n
//                              .==+#%%%%%%%#################%%%#+::-++-.                              \n
//                             ===-+#%%%%%%%###########*****##%%#=:-:-=*=                              \n
//                            :--:-=##%%%%###++++**#*+==----==+#%*:::-:==-                             \n
//                           --=::-=*%%%#+=---=+=*###*++==++*#*#%%=-:-:=-:                             \n
//                           ----=--#%%%+***-:::=+##*#====++***#%%#===-+=:                             \n
//                           .=:::.-#%%%#+*#*+=++#%##*#*+==++*#%%%#+*=+=+:                             \n
//                           :--=+--*%%%#%##***##%%%#**#*+***##%%%%*#=---             +##%             \n
//                            :--=#*+#%%%%%####++%%%#*###*-+**#%%%%**+-:             =###@             \n
//                      ###*  .:--#+=##%#%%##*++****+=+=**+==**#%#%*#.-=:            ####%-            \n
//                :%%%%#**++   ---#+=*#%%###*++*###*********+=+*##%#*-=:             :##%%#            \n
//              @%%%#*++++- ##*  -=*#*#####***#*###*++++=+*++++***##-==-              #%#%%*           \n
//             @%##=+#%%%%##**+  -=:#####*****+==::++-**+:.==+++**%:.:-=-             ##%#%%           \n
//            @%%#%%%%##*=:      -=::.=*******+*##*+++++****+++****-:::               :*#%#%%#         \n
//            %%%%###+.         ::-:.:..**+*****###*+**+*****+++**+...                 +##%%#%         \n
//          %%%%##*+*+           ::::....++++*****************+++=..                   ***###%%        \n
//         %%%%%#####%%###%%=.............=++++**********+***++++.......:::            **####%%%       \n
//        #%%%##########*++:...............+======++=+========++ .:................:= #**#####%%       \n
//    ::.:%%%##*+****+......................-+=======-----====. ......................****#####%%      \n
//   :::.*%%%####*******+...-**++++..... ......==----------:  .... .........-***+...#*##########*:+    \n
//   ::.:%%%#####*+****########*****+:..  ......   ....     ...... .......++**#########**######%#=:#   \n
// *:::.#%%%%#####**######***+=-........  ......          .......  .......:..:=+**#######*#%####%%=-#  \n
// :::.=%%%%##***###*****+:  .........     ...                      ..............=**############%#:-  \n
// ..:-%%%#**+******+++-... .........        .                     .................=+*#*####***##%%=  \n
// ..*%%%##*******+-..    ... ......  .         .                  ........ ...........+*****++**###+:@\n
// ..:%#######***-     ....... ........                            ......... .... .... ..=****+*****-.:\n
// :....-*******:       .. ....... ....                            ......... ..   ...   . .#*####=.....\n
// .....   .:++-          .............                            .............       . . ......   ...\n
//                                                                                                                                                                                       \n
// \n
// \n
// @@@  @@@  @@@  @@@  @@@@@@@   @@@@@@@@  @@@@@@@@  @@@  @@@  @@@  @@@@@@@@  @@@@@@@               @@@@@@@   @@@@@@@@  @@@  @@@   @@@@@@   @@@  @@@  @@@   @@@@@@   @@@  @@@  @@@@@@@   \n
// @@@  @@@  @@@@ @@@  @@@@@@@@  @@@@@@@@  @@@@@@@@  @@@  @@@@ @@@  @@@@@@@@  @@@@@@@@              @@@@@@@@  @@@@@@@@  @@@  @@@  @@@@@@@@  @@@  @@@  @@@  @@@@@@@@  @@@  @@@  @@@@@@@@  \n
// @@!  @@@  @@!@!@@@  @@!  @@@  @@!       @@!       @@!  @@!@!@@@  @@!       @@!  @@@              @@!  @@@  @@!       @@!  @@@  @@!  @@@  @@!  @@@  @@!  @@!  @@@  @@!  @@@  @@!  @@@  \n
// !@!  @!@  !@!!@!@!  !@!  @!@  !@!       !@!       !@!  !@!!@!@!  !@!       !@!  @!@              !@   @!@  !@!       !@!  @!@  !@!  @!@  !@!  @!@  !@!  !@!  @!@  !@!  @!@  !@!  @!@  \n
// @!@  !@!  @!@ !!@!  @!@  !@!  @!!!:!    @!!!:!    !!@  @!@ !!@!  @!!!:!    @!@  !@!              @!@!@!@   @!!!:!    @!@!@!@!  @!@!@!@!  @!@  !@!  !!@  @!@  !@!  @!@  !@!  @!@!!@!   \n
// !@!  !!!  !@!  !!!  !@!  !!!  !!!!!:    !!!!!:    !!!  !@!  !!!  !!!!!:    !@!  !!!              !!!@!!!!  !!!!!:    !!!@!!!!  !!!@!!!!  !@!  !!!  !!!  !@!  !!!  !@!  !!!  !!@!@!    \n
// !!:  !!!  !!:  !!!  !!:  !!!  !!:       !!:       !!:  !!:  !!!  !!:       !!:  !!!              !!:  !!!  !!:       !!:  !!!  !!:  !!!  :!:  !!:  !!:  !!:  !!!  !!:  !!!  !!: :!!   \n
// :!:  !:!  :!:  !:!  :!:  !:!  :!:       :!:       :!:  :!:  !:!  :!:       :!:  !:!              :!:  !:!  :!:       :!:  !:!  :!:  !:!   ::!!:!   :!:  :!:  !:!  :!:  !:!  :!:  !:!  \n
// ::::: ::   ::   ::   :::: ::   :: ::::   ::        ::   ::   ::   :: ::::   :::: ::               :: ::::   :: ::::  ::   :::  ::   :::    ::::     ::  ::::: ::  ::::: ::  ::   :::  \n
//  : :  :   ::    :   :: :  :   : :: ::    :        :    ::    :   : :: ::   :: :  :               :: : ::   : :: ::    :   : :   :   : :     :      :     : :  :    : :  :    :   : :  \n
//                                                                                                                                                                                       ";
	
// 	posix_write(STDERR_FILENO, ascii, str_len(ascii));

	(void)posix_write(STDOUT_FILENO, "\"", 1);
	(void)posix_write(STDOUT_FILENO, message, str_len(message));
	(void)posix_write(STDOUT_FILENO, UB_SUFFIX, str_len(UB_SUFFIX));
	return (error(ERR_UNDEFINED_BEHAVIOUR));
}

```

