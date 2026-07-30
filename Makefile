NAME				:= minishell
CC					:= cc
DEPFLAGS			:= -MMD -MP
CFLAGS				:= \
	-Wall -Wextra -Wdeprecated -Werror \
	-O2 \
	-DDEBUG_PARSING -DDEBUG_AST -DDEBUG_INSTANCES	# -DNDEBUG (disable assert())
DEBUG_CFLAGS		:= \
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
OBJ_DIR				:= obj

# LIBFT (START)
LIBFT_DIR			:= libft
LIBFT_INCLUDES		:= -I$(LIBFT_DIR)
LIBFT				:= $(LIBFT_DIR)/libft.a
# LIBFT (END)

# LOGS (START)
LOGS_DIR			:= logs
LOGS_INCLUDES		:= -I$(LOGS_DIR)
LOGS_SRCS			:= $(wildcard $(LOGS_DIR)/*.c)
LOGS_OBJS			:= $(LOGS_SRCS:%.c=$(OBJ_DIR)/%.o)
LOGS_DEPS			:= $(LOGS_OBJS:.o=.d)
# LOGS (END)

# GRAMMAR (START)
GRAM_DIR			:= 1_grammar
GRAM_INCLUDES		:= -I$(GRAM_DIR)/includes
GRAM_SRCS			:= \
	$(wildcard $(GRAM_DIR)/srcs/*.c) \
	$(wildcard $(GRAM_DIR)/srcs/*/*.c)
GRAM_OBJS			:= $(GRAM_SRCS:%.c=$(OBJ_DIR)/%.o)
GRAM_DEPS			:= $(GRAM_OBJS:.o=.d)
# GRAMMAR (END)

# GENERATOR (START)
GEN_DIR				:= 2_generator
GEN_NAME			:= $(GEN_DIR)/lr_generator
GEN_INCLUDES		:= \
	$(GRAM_INCLUDES) \
	$(LIBFT_INCLUDES) \
	$(LOGS_INCLUDES) \
	-I$(GEN_DIR)/includes \
	-I$(GEN_DIR)/srcs/2_rules \
	-I$(GEN_DIR)/srcs/3_first \
	-I$(GEN_DIR)/srcs/5_lr_state \
	-I$(GEN_DIR)/srcs/8_action \
	-I$(GEN_DIR)/srcs/9_qualifiers \
	-I$(GEN_DIR)/srcs/2_serialize \
	-I$(GEN_DIR)/srcs/2_serialize/write_c_file
GEN_SRCS			:= \
	$(wildcard $(GEN_DIR)/srcs/*.c) \
	$(wildcard $(GEN_DIR)/srcs/*/*.c) \
	$(wildcard $(GEN_DIR)/srcs/*/*/*.c)
GEN_CORE_OBJS		:= $(GEN_SRCS:%.c=$(OBJ_DIR)/%.o)
GEN_OBJS			:= $(GEN_CORE_OBJS) $(GRAM_OBJS) $(LOGS_OBJS)
GEN_DEPS			:= $(GEN_CORE_OBJS:.o=.d)
# GENERATOR (END)

# LR_TABLES (START)
LR_TAB_DIR			:= 3_lr_tables
LR_TAB_BASE_DIR		:= $(LR_TAB_DIR)/1_base
LR_TAB_GEN_DIR		:= $(LR_TAB_DIR)/2_generated
LR_TAB_FILES		:= lr_tables.h lr_tables.c
LR_TAB_GEN_FILES	:= $(addprefix $(LR_TAB_GEN_DIR)/,$(LR_TAB_FILES))
LR_TAB_BASE_FILES	:= $(addprefix $(LR_TAB_BASE_DIR)/,$(LR_TAB_FILES))
LR_TAB_MARKER		:= $(LR_TAB_GEN_DIR)/.generated
LR_TAB_INCLUDES		:= \
	$(GRAM_INCLUDES) \
	-I$(LR_TAB_GEN_DIR)
LR_TAB_SRCS			:= $(LR_TAB_GEN_DIR)/lr_tables.c
LR_TAB_CORE_OBJS	:= $(LR_TAB_SRCS:%.c=$(OBJ_DIR)/%.o)
LR_TAB_OBJS			:= $(LR_TAB_CORE_OBJS) $(GRAM_OBJS)
LR_TAB_DEPS			:= $(LR_TAB_CORE_OBJS:.o=.d)
# LR_TABLES (END)

# READLINE (START)
READLINE_DIR		:= $(shell brew --prefix readline 2>/dev/null)
READLINE_INCLUDES	:= -I$(READLINE_DIR)/include
READLINE_LIBS		:= -L$(READLINE_DIR)/lib -lreadline
# READLINE (END)

# DEBUG SECTION (START)
TEST_CFLAGS			:= -Wall -Wextra -Wdeprecated -Werror -O2
TEST_DIR			:= ./tests
TEST_SCRIPTS		:= $(wildcard $(TEST_DIR)/*.zsh)
TEST_MAIN			:= $(TEST_DIR)/test_posix_suite.zsh
TEST_FIXT_DIR		:= $(TEST_DIR)/fixtures
TEST_LOGS_DIR		:= $(TEST_DIR)/logs
# DEBUG SECTION (END)

# SHELL (START)
SHELL_DIR			:= 4_shell
SHELL_SRCS			:= \
	$(wildcard $(SHELL_DIR)/srcs/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/0_asm_stubs/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/0_context/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/0_context/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/0_posix_helpers/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/0_posix_helpers/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/0_token/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/0_token/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/0_utils/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/0_utils/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/0_utils/*/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/1_shell/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/2_scanner/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/2_scanner/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/2_scanner/*/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/3_builder/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/3_builder/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/3_builder/*/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/3_builder/*/*/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/4_runner/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/4_runner/0_cmd_expansion/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/4_runner/1_walker/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/4_runner/1_walker/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/4_runner/2_preparator/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/4_runner/2_preparator/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/alias/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/alias/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/ast/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/ast/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/builtins/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/builtins/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/cmd/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/cmd/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/cmd_sub/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/env/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/env/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/env/*/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/env/*/*/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/env/*/*/*/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/expander/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/expander/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/expander/*/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/expander/*/*/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/history/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/history/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/lexer/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/lexer/*/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/redirector/*.c) \
	$(wildcard $(SHELL_DIR)/srcs/redirector/*/*.c)

SHELL_INCLUDES		:= \
	$(LR_TAB_INCLUDES) \
	$(LIBFT_INCLUDES) \
	$(LOGS_INCLUDES) \
	$(READLINE_INCLUDES) \
	-I$(SHELL_DIR)/includes \
	-I$(SHELL_DIR)/srcs/0_context \
	-I$(SHELL_DIR)/srcs/0_context/expansion \
	-I$(SHELL_DIR)/srcs/0_context/quoting \
	-I$(SHELL_DIR)/srcs/0_context/stack \
	-I$(SHELL_DIR)/srcs/0_posix_helpers \
	-I$(SHELL_DIR)/srcs/0_posix_helpers/posix_open \
	-I$(SHELL_DIR)/srcs/0_utils \
	-I$(SHELL_DIR)/srcs/0_utils/ft_getopt \
	-I$(SHELL_DIR)/srcs/0_utils/serializer \
	-I$(SHELL_DIR)/srcs/0_utils/file \
	-I$(SHELL_DIR)/srcs/0_utils/ft_getpwnam \
	-I$(SHELL_DIR)/srcs/1_shell \
	-I$(SHELL_DIR)/srcs/2_scanner \
	-I$(SHELL_DIR)/srcs/2_scanner/recognition \
	-I$(SHELL_DIR)/srcs/2_scanner/recognition/operator \
	-I$(SHELL_DIR)/srcs/2_scanner/reader \
	-I$(SHELL_DIR)/srcs/2_scanner/heredoc \
	-I$(SHELL_DIR)/srcs/2_scanner/heredoc/body \
	-I$(SHELL_DIR)/srcs/3_builder/1_parser \
	-I$(SHELL_DIR)/srcs/3_builder/0_cst \
	-I$(SHELL_DIR)/srcs/3_builder/1_parser/1_item_stack \
	-I$(SHELL_DIR)/srcs/3_builder/1_parser/2_here_stack \
	-I$(SHELL_DIR)/srcs/3_builder/2_converter \
	-I$(SHELL_DIR)/srcs/3_builder/2_converter/1_redirection \
	-I$(SHELL_DIR)/srcs/4_runner \
	-I$(SHELL_DIR)/srcs/4_runner/0_cmd_expansion \
	-I$(SHELL_DIR)/srcs/4_runner/1_walker \
	-I$(SHELL_DIR)/srcs/4_runner/1_walker/0_xtrace \
	-I$(SHELL_DIR)/srcs/4_runner/1_walker/walk_pipeline \
	-I$(SHELL_DIR)/srcs/4_runner/2_preparator \
	-I$(SHELL_DIR)/srcs/4_runner/2_preparator/1_resolve \
	-I$(SHELL_DIR)/srcs/4_runner/2_preparator/2_assign \
	-I$(SHELL_DIR)/srcs/4_runner/2_preparator/3_dispatch \
	-I$(SHELL_DIR)/srcs/ast \
	-I$(SHELL_DIR)/srcs/builtins \
	-I$(SHELL_DIR)/srcs/builtins/0_error \
	-I$(SHELL_DIR)/srcs/builtins/cd \
	-I$(SHELL_DIR)/srcs/builtins/echo \
	-I$(SHELL_DIR)/srcs/builtins/env \
	-I$(SHELL_DIR)/srcs/builtins/set \
	-I$(SHELL_DIR)/srcs/cmd \
	-I$(SHELL_DIR)/srcs/cmd/cmd_execute \
	-I$(SHELL_DIR)/srcs/cmd/cmd_search \
	-I$(SHELL_DIR)/srcs/cmd_sub \
	-I$(SHELL_DIR)/srcs/env/1_options \
	-I$(SHELL_DIR)/srcs/env/2_specials \
	-I$(SHELL_DIR)/srcs/env/3_positionals \
	-I$(SHELL_DIR)/srcs/env/4_variables \
	-I$(SHELL_DIR)/srcs/env/4_variables/load \
	-I$(SHELL_DIR)/srcs/env/4_variables/load/1_envp \
	-I$(SHELL_DIR)/srcs/env/4_variables/load/2_mandatory \
	-I$(SHELL_DIR)/srcs/env/4_variables/load/2_mandatory/ft_getppid \
	-I$(SHELL_DIR)/srcs/env/4_variables/load/3_up \
	-I$(SHELL_DIR)/srcs/env/5_functions \
	-I$(SHELL_DIR)/srcs/env/6_process \
	-I$(SHELL_DIR)/srcs/env/6_process/process \
	-I$(SHELL_DIR)/srcs/env/7_cmd_cache \
	-I$(SHELL_DIR)/srcs/env/8_fds \
	-I$(SHELL_DIR)/srcs/env/8_fds/1_stack_and_frame \
	-I$(SHELL_DIR)/srcs/env/8_fds/2_fd_tracker \
	-I$(SHELL_DIR)/srcs/env/9_signal \
	-I$(SHELL_DIR)/srcs/env/9_signal/sig_action \
	-I$(SHELL_DIR)/srcs/env/10_alias \
	-I$(SHELL_DIR)/srcs/env/10_alias/1_alias_table \
	-I$(SHELL_DIR)/srcs/env/10_alias/2_alias_stack \
	-I$(SHELL_DIR)/srcs/env/10_alias/3_alias_forbidden \
	-I$(SHELL_DIR)/srcs/expander \
	-I$(SHELL_DIR)/srcs/expander/expansion \
	-I$(SHELL_DIR)/srcs/expander/field \
	-I$(SHELL_DIR)/srcs/expander/field_splitting \
	-I$(SHELL_DIR)/srcs/expander/loader \
	-I$(SHELL_DIR)/srcs/expander/loader/context \
	-I$(SHELL_DIR)/srcs/expander/path_name_expansion \
	-I$(SHELL_DIR)/srcs/expander/path_name_expansion/path_comps \
	-I$(SHELL_DIR)/srcs/expander/path_name_expansion/globbing \
	-I$(SHELL_DIR)/srcs/expander/path_name_expansion/path_matches \
	-I$(SHELL_DIR)/srcs/expander/quote_removal \
	-I$(SHELL_DIR)/srcs/expander/quote_removal/context \
	-I$(SHELL_DIR)/srcs/expander/substitutions \
	-I$(SHELL_DIR)/srcs/expander/substitutions/tilde \
	-I$(SHELL_DIR)/srcs/expander/substitutions/param \
	-I$(SHELL_DIR)/srcs/expander/substitutions/param/unbraced \
	-I$(SHELL_DIR)/srcs/expander/substitutions/param/braced \
	-I$(SHELL_DIR)/srcs/expander/substitutions/cmd_sub \
	-I$(SHELL_DIR)/srcs/expander/substitutions/dollar_squote \
	-I$(SHELL_DIR)/srcs/expander/substitutions/arith \
	-I$(SHELL_DIR)/srcs/expander/substitutions/backtick \
	-I$(SHELL_DIR)/srcs/expander/word \
	-I$(SHELL_DIR)/srcs/history \
	-I$(SHELL_DIR)/srcs/history/file \
	-I$(SHELL_DIR)/srcs/history/list \
	-I$(SHELL_DIR)/srcs/history/readline \
	-I$(SHELL_DIR)/srcs/lexer \
	-I$(SHELL_DIR)/srcs/lexer/context \
	-I$(SHELL_DIR)/srcs/lexer/input_stack \
	-I$(SHELL_DIR)/srcs/redirector
SHELL_CORE_OBJS		:= $(SHELL_SRCS:%.c=$(OBJ_DIR)/%.o)
SHELL_OBJS			:= $(SHELL_CORE_OBJS) $(LR_TAB_OBJS) $(LOGS_OBJS)
SHELL_DEPS			:= $(SHELL_CORE_OBJS:.o=.d)
# SHELL (END)

# LOGS MACRO (START)
define BUILD_SECTION
	@$(MAKE) -sq $(1) || { \
		status=$$?; \
		if [ $$status -eq 1 ]; then \
			echo "compiling $(2)..."; \
			$(MAKE) -s $(1); \
		else \
			exit $$status; \
		fi; \
	}
endef
# LOGS MACRO (END)

# INCLUDES SELECTION (START)
$(LOGS_OBJS): BUILD_INCLUDES := $(LOGS_INCLUDES)
$(GRAM_OBJS): BUILD_INCLUDES := $(GRAM_INCLUDES)
$(GEN_CORE_OBJS): BUILD_INCLUDES := $(GEN_INCLUDES)
$(LR_TAB_CORE_OBJS): BUILD_INCLUDES := $(LR_TAB_INCLUDES)
$(SHELL_CORE_OBJS): BUILD_INCLUDES := $(SHELL_INCLUDES)
# INCLUDES SELECTION (END)

# PUBLIC RULES (START)
all: $(NAME)

tables:
	@if [ ! -f $(LR_TAB_MARKER) ] \
		|| [ ! -f $(LR_TAB_GEN_DIR)/lr_tables.h ] \
		|| [ ! -f $(LR_TAB_GEN_DIR)/lr_tables.c ]; then \
		rm -f $(LR_TAB_MARKER); \
	fi
	@$(MAKE) -s $(LR_TAB_MARKER)
# PUBLIC RULES (END)

# PRIVATE RULES (START)
_compile_logs:
	$(call BUILD_SECTION,$(LOGS_OBJS),logs)

_compile_grammar:
	$(call BUILD_SECTION,$(GRAM_OBJS),grammar)

_compile_generator: | _compile_logs _compile_grammar
	$(call BUILD_SECTION,$(GEN_CORE_OBJS),generator)

_compile_tables:
	$(call BUILD_SECTION,$(LR_TAB_CORE_OBJS),lr tables)

_compile_shell:
	$(call BUILD_SECTION,$(SHELL_CORE_OBJS),shell)
# PRIVATE RULES (END)

$(LIBFT):
	@echo "compiling libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)

$(GEN_NAME): $(GEN_OBJS) $(LIBFT) | _compile_generator
	@echo "linking generator..."
	@$(CC) $(CFLAGS) $(GEN_OBJS) $(LIBFT) -o $(GEN_NAME)

$(LR_TAB_MARKER): $(GRAM_SRCS) $(GEN_SRCS) | $(GEN_NAME)
	@echo "generating lr tables..."
	@mkdir -p $(LR_TAB_GEN_DIR)
	@./$(GEN_NAME)
	@touch $(LR_TAB_MARKER)

$(NAME): $(SHELL_OBJS) $(LIBFT)
	@echo "linking shell..."
	@$(CC) $(CFLAGS) $(SHELL_OBJS) $(LIBFT) $(READLINE_LIBS) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(DEPFLAGS) $(CFLAGS) $(BUILD_INCLUDES) -c $< -o $@

bonus: all

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
	rm -f $(GEN_NAME)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(LR_TAB_MARKER)
	@mkdir -p $(LR_TAB_GEN_DIR)
	@cp $(LR_TAB_BASE_FILES) $(LR_TAB_GEN_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

-include $(LOGS_DEPS)
-include $(GRAM_DEPS)
-include $(GEN_DEPS)
-include $(LR_TAB_DEPS)
-include $(SHELL_DEPS)

.PHONY: all bonus gen debug test clean fclean re
