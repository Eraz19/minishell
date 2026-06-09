NAME			:= minishell
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -O2 # -DNDEBUG # -g3 -fsanitize=address,undefined # -fsanitize=leak # -fsanitize=memory

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
	$(wildcard srcs/params/*/*/*/*/*.c)

INCLUDES		:= \
	-I$(READLINE_DIR)/include \
	-Iincludes \
	-Ilogs \
	-Ilibft \
	-Ilibft/buff \
	-Ilibft/buff/format \
	-Isrcs/1_shell \
	-Isrcs/2_scanner \
	-Isrcs/2_scanner/lexer \
	-Isrcs/2_scanner/reader \
	-Isrcs/2_scanner/lexer/rules \
	-Isrcs/2_scanner/lexer/token \
	-Isrcs/2_scanner/lexer/context \
	-Isrcs/2_scanner/lexer/operator \
	-Isrcs/2_scanner/lexer/context/context_stack \
	-Isrcs/2_scanner/heredoc \
	-Isrcs/2_scanner/heredoc/here_queue \
	-Isrcs/2_scanner/heredoc/heredoc_body \
	-Isrcs/2_scanner/alias \
	-Isrcs/2_scanner/alias/alias_stack \
	-Isrcs/expander/quote_remove \
	-Isrcs/expander/quote_remove/rules \
	-Isrcs/expander/quote_remove/context \
	-Isrcs/history \
	-Isrcs/history/history_rl \
	-Isrcs/history/history_list \
	-Isrcs/history/history_file \
	-Isrcs/3_builder/1_lr_machine \
	-Isrcs/3_builder/1_lr_machine/1_hooks \
	-Isrcs/3_builder/1_lr_machine/2_rules \
	-Isrcs/3_builder/1_lr_machine/3_symbols \
	-Isrcs/3_builder/1_lr_machine/4_first \
	-Isrcs/3_builder/1_lr_machine/5_rule_state \
	-Isrcs/3_builder/1_lr_machine/6_lr_state \
	-Isrcs/3_builder/1_lr_machine/7_transition \
	-Isrcs/3_builder/1_lr_machine/8_goto \
	-Isrcs/3_builder/1_lr_machine/9_action \
	-Isrcs/3_builder/2_parser \
	-Isrcs/3_builder/2_parser/x_stack \
	-Isrcs/params/1_options \
	-Isrcs/params/2_specials \
	-Isrcs/params/3_positionals \
	-Isrcs/params/4_variables \
	-Isrcs/params/4_variables/load \
	-Isrcs/params/4_variables/load/1_envp \
	-Isrcs/params/4_variables/load/2_mandatory \
	-Isrcs/params/4_variables/load/2_mandatory/ft_getppid \
	-Isrcs/params/4_variables/load/3_up \
	-Isrcs/builtins

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

.PHONY: all bonus test_getopt test clean fclean re
