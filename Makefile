NAME			:= minishell
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -O2 -DDEBUG_LOGS -DDEBUG_PARSING -DDEBUG_AST	# -DNDEBUG (disable assert())
DEBUG_CFLAGS	:= \
	-Wall -Wextra -Werror \
	-O0 -g3 -fsanitize=address,undefined \
	-DDEBUG_ERROR_TRACE \
	-DDEBUG_LOGS \
	-DDEBUG_PARAMS \
	-DDEBUG_HISTORY \
	-DDEBUG_PARSING \
	-DDEBUG_CST \
	-DDEBUG_AST

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
	$(wildcard srcs/0_input_mode/*.c) \
	$(wildcard srcs/0_posix_helpers/*.c) \
	$(wildcard srcs/0_posix_helpers/*/*.c) \
	$(wildcard srcs/0_token/*.c) \
	$(wildcard srcs/0_token/*/*.c) \
	$(wildcard srcs/0_utils/*.c) \
	$(wildcard srcs/0_utils/*/*.c) \
	$(wildcard srcs/1_shell/*.c) \
	$(wildcard srcs/lexer/*.c) \
	$(wildcard srcs/lexer/*/*.c) \
	$(wildcard srcs/2_scanner/*.c) \
	$(wildcard srcs/2_scanner/*/*.c) \
	$(wildcard srcs/2_scanner/*/*/*.c) \
	$(wildcard srcs/3_builder/*.c) \
	$(wildcard srcs/3_builder/*/*.c) \
	$(wildcard srcs/3_builder/*/*/*.c) \
	$(wildcard srcs/3_builder/*/*/*/*.c) \
	$(wildcard srcs/4_runner/*.c) \
	$(wildcard srcs/4_runner/0_cmd_expansion/*.c) \
	$(wildcard srcs/4_runner/0_tokens/*.c) \
	$(wildcard srcs/4_runner/1_redirector/*.c) \
	$(wildcard srcs/4_runner/1_redirector/*/*.c) \
	$(wildcard srcs/4_runner/2_executor/*.c) \
	$(wildcard srcs/4_runner/2_executor/*/*.c) \
	$(wildcard srcs/4_runner/3_walker/*.c) \
	$(wildcard srcs/ast/*.c) \
	$(wildcard srcs/ast/*/*.c) \
	$(wildcard srcs/builtins/*.c) \
	$(wildcard srcs/cmd_cache/*.c) \
	$(wildcard srcs/expander/*.c) \
	$(wildcard srcs/expander/*/*.c) \
	$(wildcard srcs/expander/*/*/*.c) \
	$(wildcard srcs/expander/*/*/*/*.c) \
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
	-Ilibft/src/buff \
	-Ilibft/src/buff/format \
	-Isrcs/0_context \
	-Isrcs/0_context/expansion \
	-Isrcs/0_context/quoting \
	-Isrcs/0_context/stack \
	-Isrcs/0_posix_helpers \
	-Isrcs/0_posix_helpers/posix_open \
	-Isrcs/0_utils \
	-Isrcs/0_utils/1_ft_getopt \
	-Isrcs/0_utils/2_serializer \
	-Isrcs/0_utils/ft_getpwnam \
	-Isrcs/1_shell \
	-Isrcs/lexer \
	-Isrcs/lexer/context \
	-Isrcs/lexer/input_stack \
	-Isrcs/2_scanner \
	-Isrcs/2_scanner/recognition \
	-Isrcs/2_scanner/recognition/operator \
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
	-Isrcs/3_builder/3_converter/1_redirection \
	-Isrcs/4_runner \
	-Isrcs/4_runner/0_cmd_expansion \
	-Isrcs/4_runner/0_tokens \
	-Isrcs/4_runner/1_redirector \
	-Isrcs/4_runner/1_redirector/1_stack_and_frame \
	-Isrcs/4_runner/1_redirector/2_tracker \
	-Isrcs/4_runner/1_redirector/3_fd_manager \
	-Isrcs/4_runner/2_executor \
	-Isrcs/4_runner/2_executor/0_cmd \
	-Isrcs/4_runner/2_executor/0_entry_is_target \
	-Isrcs/4_runner/2_executor/1_resolver \
	-Isrcs/4_runner/2_executor/2_assignator \
	-Isrcs/4_runner/2_executor/3_searcher \
	-Isrcs/4_runner/2_executor/4_dispatcher \
	-Isrcs/4_runner/3_walker \
	-Isrcs/alias \
	-Isrcs/alias/stack \
	-Isrcs/ast \
	-Isrcs/builtins \
	-Isrcs/expander \
	-Isrcs/expander/expansion \
	-Isrcs/expander/field \
	-Isrcs/expander/field_splitting \
	-Isrcs/expander/loader \
	-Isrcs/expander/loader/context \
	-Isrcs/expander/path_name_expansion \
	-Isrcs/expander/path_name_expansion/path_comps \
	-Isrcs/expander/path_name_expansion/globbing \
	-Isrcs/expander/path_name_expansion/path_matches \
	-Isrcs/expander/quote_removal \
	-Isrcs/expander/quote_removal/context \
	-Isrcs/expander/substitutions \
	-Isrcs/expander/substitutions/tilde \
	-Isrcs/expander/substitutions/param \
	-Isrcs/expander/substitutions/param/unbraced \
	-Isrcs/expander/substitutions/param/braced \
	-Isrcs/expander/substitutions/cmd_sub \
	-Isrcs/expander/substitutions/dollar_squote \
	-Isrcs/expander/substitutions/arith \
	-Isrcs/expander/substitutions/backtick \
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
	-Isrcs/params/4_variables/load/3_up \
	-Isrcs/params/5_functions

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
