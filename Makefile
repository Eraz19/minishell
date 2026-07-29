NAME			:= minishell
CC				:= cc
DEPFLAGS		:= -MMD -MP
CFLAGS			:= \
	-Wall -Wextra -Wdeprecated -Werror \
	-O2 \
	-DDEBUG_PARSING -DDEBUG_AST -DDEBUG_INSTANCES	# -DNDEBUG (disable assert())
DEBUG_CFLAGS	:= \
	-Wall -Wextra -Wdeprecated -Werror \
	-O0 -g3 -fsanitize=address,undefined \
	-DDEBUG_ERROR_TRACE \
	-DDEBUG_LOGS \
	-DDEBUG_PARAMS \
	-DDEBUG_PARSING \
	-DDEBUG_CST \
	-DDEBUG_AST \
	-DDEBUG_HISTORY \
	-DDEBUG_CMD_SUB \
	-DDEBUG_INSTANCES
OBJ_DIR			:= obj

# LIBFT (START)
LIBFT_DIR		:= libft
LIBFT_INCLUDES	:= -I$(LIBFT_DIR)
LIBFT			:= $(LIBFT_DIR)/libft.a
READLINE_DIR	:= $(shell brew --prefix readline 2>/dev/null)
# LIBFT (END)

# LOGS (START)
LOGS_DIR		:= logs
LOGS_INCLUDES	:= -I$(LOGS_DIR)
LOGS_SRCS		:= $(wildcard $(LOGS_DIR)/*.c)
LOGS_OBJS		:= $(LOGS_SRCS:%.c=$(OBJ_DIR)/%.o)
# LOGS (END)

# GRAMMAR (START)
GRAM_DIR		:= 1_grammar
GRAM_INCLUDES	:= -I$(GRAM_DIR)/includes
GRAM_SRCS		:= \
	$(wildcard $(GRAM_DIR)/srcs/*.c) \
	$(wildcard $(GRAM_DIR)/srcs/*/*.c)
GRAM_OBJS		:= $(GRAM_SRCS:%.c=$(OBJ_DIR)/%.o)
# GRAMMAR (END)

# GENERATOR (START)
GEN_DIR			:= 2_generator
GEN_NAME		:= $(GEN_DIR)/lr_generator
GEN_INCLUDES	:= \
	$(GRAM_INCLUDES) \
	$(LIBFT_INCLUDES) \
	$(LOGS_INCLUDES) \
	-I$(GEN_DIR)/includes \
	-I$(GEN_DIR)/srcs/2_rules \
	-I$(GEN_DIR)/srcs/3_first \
	-I$(GEN_DIR)/srcs/5_lr_state \
	-I$(GEN_DIR)/srcs/8_action \
	-I$(GEN_DIR)/srcs/9_qualifiers
GEN_SRCS		:= \
	$(wildcard $(GEN_DIR)/srcs/*.c) \
	$(wildcard $(GEN_DIR)/srcs/*/*.c) \
	$(wildcard $(GEN_DIR)/srcs/*/*/*.c)
GEN_CORE_OBJS	:= $(GEN_SRCS:%.c=$(OBJ_DIR)/%.o)
GEN_OBJS		:= $(GEN_CORE_OBJS) $(GRAM_OBJS) $(LOGS_OBJS)
GEN_DEPS		:= $(GEN_OBJS:.o=.d)
LR_TABLES_DIR		:= 3_lr_tables
LR_TABLES_BASE_DIR	:= $(LR_TABLES_DIR)/1_base
LR_TABLES_GEN_DIR	:= $(LR_TABLES_DIR)/2_generated
LR_TABLES_FILES		:= lr_tables.h lr_tables.c
# GENERATOR (END)

# DEBUG SECTION (START)
TEST_CFLAGS		:= -Wall -Wextra -Wdeprecated -Werror -O2
TEST_DIR		:= ./tests
TEST_SCRIPTS	:= $(wildcard $(TEST_DIR)/*.zsh)
TEST_MAIN		:= $(TEST_DIR)/test_posix_suite.zsh
TEST_FIXT_DIR	:= $(TEST_DIR)/fixtures
TEST_LOGS_DIR	:= $(TEST_DIR)/logs
# DEBUG SECTION (END)

SRCS			:= \
	$(wildcard logs/*.c) \
	$(wildcard srcs/*.c) \
	$(wildcard srcs/0_asm_stubs/*/*.c) \
	$(wildcard srcs/0_context/*.c) \
	$(wildcard srcs/0_context/*/*.c) \
	$(wildcard srcs/0_posix_helpers/*.c) \
	$(wildcard srcs/0_posix_helpers/*/*.c) \
	$(wildcard srcs/0_token/*.c) \
	$(wildcard srcs/0_token/*/*.c) \
	$(wildcard srcs/0_utils/*.c) \
	$(wildcard srcs/0_utils/*/*.c) \
	$(wildcard srcs/0_utils/*/*/*.c) \
	$(wildcard srcs/1_shell/*.c) \
	$(wildcard srcs/2_scanner/*.c) \
	$(wildcard srcs/2_scanner/*/*.c) \
	$(wildcard srcs/2_scanner/*/*/*.c) \
	$(wildcard srcs/3_builder/*.c) \
	$(wildcard srcs/3_builder/*/*.c) \
	$(wildcard srcs/3_builder/*/*/*.c) \
	$(wildcard srcs/3_builder/*/*/*/*.c) \
	$(wildcard srcs/4_runner/*.c) \
	$(wildcard srcs/4_runner/0_cmd_expansion/*.c) \
	$(wildcard srcs/4_runner/1_walker/*.c) \
	$(wildcard srcs/4_runner/1_walker/*/*.c) \
	$(wildcard srcs/4_runner/2_preparator/*.c) \
	$(wildcard srcs/4_runner/2_preparator/*/*.c) \
	$(wildcard srcs/alias/*.c) \
	$(wildcard srcs/alias/*/*.c) \
	$(wildcard srcs/ast/*.c) \
	$(wildcard srcs/ast/*/*.c) \
	$(wildcard srcs/builtins/*.c) \
	$(wildcard srcs/builtins/*/*.c) \
	$(wildcard srcs/cmd/*.c) \
	$(wildcard srcs/cmd/*/*.c) \
	$(wildcard srcs/cmd_sub/*.c) \
	$(wildcard srcs/env/*.c) \
	$(wildcard srcs/env/*/*.c) \
	$(wildcard srcs/env/*/*/*.c) \
	$(wildcard srcs/env/*/*/*/*.c) \
	$(wildcard srcs/env/*/*/*/*/*.c) \
	$(wildcard srcs/expander/*.c) \
	$(wildcard srcs/expander/*/*.c) \
	$(wildcard srcs/expander/*/*/*.c) \
	$(wildcard srcs/expander/*/*/*/*.c) \
	$(wildcard srcs/history/*.c) \
	$(wildcard srcs/history/*/*.c) \
	$(wildcard srcs/lexer/*.c) \
	$(wildcard srcs/lexer/*/*.c) \
	$(wildcard srcs/lr_machine/*.c) \
	$(wildcard srcs/lr_machine/*/*.c) \
	$(wildcard srcs/redirector/*.c) \
	$(wildcard srcs/redirector/*/*.c)

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
	-Isrcs/0_utils/ft_getopt \
	-Isrcs/0_utils/serializer \
	-Isrcs/0_utils/file \
	-Isrcs/0_utils/ft_getpwnam \
	-Isrcs/1_shell \
	-Isrcs/2_scanner \
	-Isrcs/2_scanner/recognition \
	-Isrcs/2_scanner/recognition/operator \
	-Isrcs/2_scanner/reader \
	-Isrcs/2_scanner/heredoc \
	-Isrcs/2_scanner/heredoc/body \
	-Isrcs/3_builder/1_parser \
	-Isrcs/3_builder/0_cst \
	-Isrcs/3_builder/1_parser/1_item_stack \
	-Isrcs/3_builder/1_parser/2_here_stack \
	-Isrcs/3_builder/2_converter \
	-Isrcs/3_builder/2_converter/1_redirection \
	-Isrcs/4_runner \
	-Isrcs/4_runner/0_cmd_expansion \
	-Isrcs/4_runner/1_walker \
	-Isrcs/4_runner/1_walker/0_xtrace \
	-Isrcs/4_runner/1_walker/walk_pipeline \
	-Isrcs/4_runner/2_preparator \
	-Isrcs/4_runner/2_preparator/1_resolve \
	-Isrcs/4_runner/2_preparator/2_assign \
	-Isrcs/4_runner/2_preparator/3_dispatch \
	-Isrcs/ast \
	-Isrcs/builtins \
	-Isrcs/builtins/0_error \
	-Isrcs/builtins/cd \
	-Isrcs/builtins/echo \
	-Isrcs/builtins/env \
	-Isrcs/builtins/set \
	-Isrcs/cmd \
	-Isrcs/cmd/cmd_execute \
	-Isrcs/cmd/cmd_search \
	-Isrcs/cmd_sub \
	-Isrcs/env/1_options \
	-Isrcs/env/2_specials \
	-Isrcs/env/3_positionals \
	-Isrcs/env/4_variables \
	-Isrcs/env/4_variables/load \
	-Isrcs/env/4_variables/load/1_envp \
	-Isrcs/env/4_variables/load/2_mandatory \
	-Isrcs/env/4_variables/load/2_mandatory/ft_getppid \
	-Isrcs/env/4_variables/load/3_up \
	-Isrcs/env/5_functions \
	-Isrcs/env/6_process \
	-Isrcs/env/6_process/process \
	-Isrcs/env/7_cmd_cache \
	-Isrcs/env/8_fds \
	-Isrcs/env/8_fds/1_stack_and_frame \
	-Isrcs/env/8_fds/2_fd_tracker \
	-Isrcs/env/9_signal \
	-Isrcs/env/9_signal/sig_action \
	-Isrcs/env/10_alias \
	-Isrcs/env/10_alias/1_alias_table \
	-Isrcs/env/10_alias/2_alias_stack \
	-Isrcs/env/10_alias/3_alias_forbidden \
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
	-Isrcs/history \
	-Isrcs/history/file \
	-Isrcs/history/list \
	-Isrcs/history/readline \
	-Isrcs/lexer \
	-Isrcs/lexer/context \
	-Isrcs/lexer/input_stack \
	-Isrcs/lr_machine \
	-Isrcs/lr_machine/1_hooks \
	-Isrcs/lr_machine/2_symbols \
	-Isrcs/lr_machine/3_rules \
	-Isrcs/lr_machine/4_first \
	-Isrcs/lr_machine/5_rule_state \
	-Isrcs/lr_machine/6_lr_state \
	-Isrcs/lr_machine/7_transition \
	-Isrcs/lr_machine/8_goto \
	-Isrcs/lr_machine/9_action \
	-Isrcs/lr_machine/10_qualifiers \
	-Isrcs/redirector

OBJS			:= $(SRCS:%.c=$(OBJ_DIR)/%.o)
DEPS			:= $(OBJS:.o=.d)

$(OBJS): BUILD_INCLUDES := $(INCLUDES)
$(GEN_OBJS): BUILD_INCLUDES := $(GEN_INCLUDES)

all: $(NAME)

$(LIBFT):
	@echo "compiling libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L$(READLINE_DIR)/lib -lreadline -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(DEPFLAGS) $(CFLAGS) $(BUILD_INCLUDES) -c $< -o $@

bonus: all

# GENERATOR (START)
gen:
	@echo "compiling grammar..."
	@$(MAKE) -s $(GRAM_OBJS)
	@$(MAKE) -s $(LIBFT)
	@echo "compiling logs..."
	@$(MAKE) -s $(LOGS_OBJS)
	@echo "compiling generator..."
	@$(MAKE) -s $(GEN_NAME)
	@mkdir -p $(LR_TABLES_GEN_DIR)
	@./$(GEN_NAME)

$(GEN_NAME): $(GEN_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(GEN_OBJS) $(LIBFT) -o $(GEN_NAME)

# GENERATOR (END)

debug: CFLAGS := $(DEBUG_CFLAGS)
debug: re

# DEBUG SECTION (START)
test: CFLAGS := $(TEST_CFLAGS)
test:
	@echo "compiling..."
	@$(MAKE) re >/dev/null
	$(TEST_MAIN)
# 	@for tester in $(TEST_SCRIPTS); do \
# 		echo "Running $$tester"; \
# 		zsh "$$tester"; \
# 	done
# DEBUG SECTION (END)

clean:
	rm -rf $(OBJ_DIR) $(TEST_FIXT_DIR) $(TEST_LOGS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(GEN_NAME)
	@mkdir -p $(LR_TABLES_GEN_DIR)
	@cp $(addprefix $(LR_TABLES_BASE_DIR)/,$(LR_TABLES_FILES)) \
		$(LR_TABLES_GEN_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

-include $(DEPS)
-include $(GEN_DEPS)

.PHONY: all bonus gen debug test clean fclean re
