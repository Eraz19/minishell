MAKEFLAGS			+= --no-print-directory

NAME				:= minishell
CC					:= cc
DEPFLAGS			:= -MMD -MP
CFLAGS				:= -Wall -Wextra -Wdeprecated -Werror -D_GNU_SOURCE -O2
DEBUG_CFLAGS		:= -Wall -Wextra -Wdeprecated -Werror -D_GNU_SOURCE -O0 -g3 -fsanitize=address,undefined
OBJ_DIR				:= obj

# LIBFT (START)
LIBFT_DIR			:= libft
LIBFT_INCLUDES		:= -I$(LIBFT_DIR)
LIBFT				:= $(LIBFT_DIR)/libft.a
# LIBFT (END)

# GRAMMAR (START)
GRAM_DIR			:= 1_grammar
GRAM_INCLUDES		:= \
	$(LIBFT_INCLUDES) \
	-I$(GRAM_DIR)/includes
GRAM_SRCS			:= $(shell find $(GRAM_DIR)/srcs -type f -name '*.c' | sort)
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
GEN_SRCS			:= $(shell find $(GEN_DIR)/srcs -type f -name '*.c' | sort)
GEN_CORE_OBJS		:= $(GEN_SRCS:%.c=$(OBJ_DIR)/%.o)
GEN_OBJS			:= $(GEN_CORE_OBJS) $(GRAM_OBJS)
GEN_DEPS			:= $(GEN_CORE_OBJS:.o=.d)
# GENERATOR (END)

# LR_TABLES (START)
LR_TAB_DIR			:= 3_lr_tables
LR_TAB_BASE_DIR		:= $(LR_TAB_DIR)/1_base
LR_TAB_GEN_DIR		:= $(LR_TAB_DIR)/2_generated
LR_TAB_FILES		:= lr_tables.h lr_tables.c
LR_TAB_GEN_FILES	:= $(addprefix $(LR_TAB_GEN_DIR)/,$(LR_TAB_FILES))
LR_TAB_BASE_FILES	:= $(addprefix $(LR_TAB_BASE_DIR)/,$(LR_TAB_FILES))
LR_TAB_INPUTS		:= \
	$(shell find $(GRAM_DIR) $(GEN_DIR) $(LIBFT_DIR)/src \
		-type f \( -name '*.c' -o -name '*.h' \)) \
	$(shell find $(LIBFT_DIR) -type f -name '*.h' \
		! -path '$(LIBFT_DIR)/*/*')
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

# SHELL (START)
SHELL_DIR			:= 4_shell
SHELL_SRCS			:= $(shell find $(SHELL_DIR)/srcs -type f -name '*.c' | sort)
SHELL_INCLUDES		:= \
	$(LR_TAB_INCLUDES) \
	$(LIBFT_INCLUDES) \
	$(READLINE_INCLUDES) \
	-I$(SHELL_DIR)/includes \
	-I$(SHELL_DIR)/srcs/0_posix_helpers/ \
	-I$(SHELL_DIR)/srcs/0_token/context \
	-I$(SHELL_DIR)/srcs/0_token/context/context_stack \
	-I$(SHELL_DIR)/srcs/0_token/context/context_stack_item \
	-I$(SHELL_DIR)/srcs/0_token/token_pool \
	-I$(SHELL_DIR)/srcs/0_utils/ft_getopt \
	-I$(SHELL_DIR)/srcs/0_utils/serializer \
	-I$(SHELL_DIR)/srcs/0_utils/file \
	-I$(SHELL_DIR)/srcs/1_shell \
	-I$(SHELL_DIR)/srcs/2_scanner \
	-I$(SHELL_DIR)/srcs/2_scanner/heredoc \
	-I$(SHELL_DIR)/srcs/2_scanner/heredoc/body \
	-I$(SHELL_DIR)/srcs/2_scanner/lexer \
	-I$(SHELL_DIR)/srcs/2_scanner/lexer/backup \
	-I$(SHELL_DIR)/srcs/2_scanner/lexer/input_stack \
	-I$(SHELL_DIR)/srcs/2_scanner/lexer/input_stack_item \
	-I$(SHELL_DIR)/srcs/2_scanner/lexer/token_recognition \
	-I$(SHELL_DIR)/srcs/2_scanner/lexer/token_recognition/context \
	-I$(SHELL_DIR)/srcs/2_scanner/lexer/token_recognition/context/scan \
	-I$(SHELL_DIR)/srcs/2_scanner/lexer/token_recognition/operator \
	-I$(SHELL_DIR)/srcs/2_scanner/reader \
	-I$(SHELL_DIR)/srcs/2_scanner/reader/interactive \
	-I$(SHELL_DIR)/srcs/3_builder/0_cst \
	-I$(SHELL_DIR)/srcs/3_builder/1_parser \
	-I$(SHELL_DIR)/srcs/3_builder/1_parser/1_item_stack \
	-I$(SHELL_DIR)/srcs/3_builder/1_parser/2_here_stack \
	-I$(SHELL_DIR)/srcs/3_builder/2_converter \
	-I$(SHELL_DIR)/srcs/3_builder/2_converter/0_convert_io_redir \
	-I$(SHELL_DIR)/srcs/4_runner \
	-I$(SHELL_DIR)/srcs/4_runner/1_walker \
	-I$(SHELL_DIR)/srcs/4_runner/1_walker/0_xtrace \
	-I$(SHELL_DIR)/srcs/4_runner/1_walker/walk_pipeline \
	-I$(SHELL_DIR)/srcs/ast \
	-I$(SHELL_DIR)/srcs/builtins \
	-I$(SHELL_DIR)/srcs/builtins/0_error \
	-I$(SHELL_DIR)/srcs/builtins/cd \
	-I$(SHELL_DIR)/srcs/builtins/echo \
	-I$(SHELL_DIR)/srcs/builtins/env \
	-I$(SHELL_DIR)/srcs/builtins/set \
	-I$(SHELL_DIR)/srcs/cmd \
	-I$(SHELL_DIR)/srcs/cmd/1_cmd_resolve \
	-I$(SHELL_DIR)/srcs/cmd/2_cmd_assign \
	-I$(SHELL_DIR)/srcs/cmd/3_cmd_search \
	-I$(SHELL_DIR)/srcs/cmd/4_cmd_execute \
	-I$(SHELL_DIR)/srcs/cmd_sub \
	-I$(SHELL_DIR)/srcs/env/1_options \
	-I$(SHELL_DIR)/srcs/env/2_specials \
	-I$(SHELL_DIR)/srcs/env/3_positionals \
	-I$(SHELL_DIR)/srcs/env/4_variables \
	-I$(SHELL_DIR)/srcs/env/4_variables/load \
	-I$(SHELL_DIR)/srcs/env/4_variables/load/1_envp \
	-I$(SHELL_DIR)/srcs/env/4_variables/load/2_mandatory \
	-I$(SHELL_DIR)/srcs/env/4_variables/load/3_up \
	-I$(SHELL_DIR)/srcs/env/5_functions \
	-I$(SHELL_DIR)/srcs/env/6_process \
	-I$(SHELL_DIR)/srcs/env/7_cmd_cache \
	-I$(SHELL_DIR)/srcs/env/8_fds \
	-I$(SHELL_DIR)/srcs/env/8_fds/1_stack_and_frame \
	-I$(SHELL_DIR)/srcs/env/8_fds/2_fd_tracker \
	-I$(SHELL_DIR)/srcs/env/9_signal \
	-I$(SHELL_DIR)/srcs/env/9_signal/sig_action \
	-I$(SHELL_DIR)/srcs/env/9_signal/sig_build_name \
	-I$(SHELL_DIR)/srcs/env/9_signal/sig_id_to_no \
	-I$(SHELL_DIR)/srcs/env/9_signal/sig_no_to_id \
	-I$(SHELL_DIR)/srcs/env/9_signal/sig_parse_name \
	-I$(SHELL_DIR)/srcs/env/10_alias \
	-I$(SHELL_DIR)/srcs/env/10_alias/1_alias_table \
	-I$(SHELL_DIR)/srcs/env/10_alias/2_alias_stack \
	-I$(SHELL_DIR)/srcs/expander \
	-I$(SHELL_DIR)/srcs/expander/expansion \
	-I$(SHELL_DIR)/srcs/expander/field \
	-I$(SHELL_DIR)/srcs/expander/field_splitting \
	-I$(SHELL_DIR)/srcs/expander/loader \
	-I$(SHELL_DIR)/srcs/expander/loader/context \
	-I$(SHELL_DIR)/srcs/expander/match_pattern \
	-I$(SHELL_DIR)/srcs/expander/path_name_expansion \
	-I$(SHELL_DIR)/srcs/expander/path_name_expansion/globbing \
	-I$(SHELL_DIR)/srcs/expander/path_name_expansion/path_comps \
	-I$(SHELL_DIR)/srcs/expander/path_name_expansion/path_matches \
	-I$(SHELL_DIR)/srcs/expander/quote_removal \
	-I$(SHELL_DIR)/srcs/expander/quote_removal/context \
	-I$(SHELL_DIR)/srcs/expander/substitutions \
	-I$(SHELL_DIR)/srcs/expander/substitutions/arith \
	-I$(SHELL_DIR)/srcs/expander/substitutions/backtick \
	-I$(SHELL_DIR)/srcs/expander/substitutions/cmd_sub \
	-I$(SHELL_DIR)/srcs/expander/substitutions/dollar_squote \
	-I$(SHELL_DIR)/srcs/expander/substitutions/param \
	-I$(SHELL_DIR)/srcs/expander/substitutions/param/braced \
	-I$(SHELL_DIR)/srcs/expander/substitutions/param/unbraced \
	-I$(SHELL_DIR)/srcs/expander/substitutions/tilde \
	-I$(SHELL_DIR)/srcs/expander/word \
	-I$(SHELL_DIR)/srcs/history \
	-I$(SHELL_DIR)/srcs/history/adapter \
	-I$(SHELL_DIR)/srcs/history/file \
	-I$(SHELL_DIR)/srcs/history/list \
	-I$(SHELL_DIR)/srcs/history/load_env \
	-I$(SHELL_DIR)/srcs/redirector
SHELL_CORE_OBJS		:= $(SHELL_SRCS:%.c=$(OBJ_DIR)/%.o)
SHELL_OBJS			:= $(SHELL_CORE_OBJS) $(LR_TAB_OBJS)
SHELL_DEPS			:= $(SHELL_CORE_OBJS:.o=.d)
# SHELL (END)

# TEST (START)
TEST_CFLAGS			:= -Wall -Wextra -Wdeprecated -Werror -O2 -D_GNU_SOURCE
TEST_DIR			:= ./tests
TEST_SCRIPTS		:= $(shell find $(TEST_DIR) -type f -name '*.zsh' \
	! -path '$(TEST_DIR)/*/*' | sort)
TEST_MAIN			:= $(TEST_DIR)/test_posix_suite.zsh
TEST_FIXT_DIR		:= $(TEST_DIR)/fixtures
TEST_LOGS_DIR		:= $(TEST_DIR)/logs
# TEST (END)

# BUILD MACRO (START)
define BUILD_SECTION
	@status=0; \
	$(MAKE) -srq CFLAGS="$(CFLAGS)" $(1) || status=$$?; \
	if [ $$status -eq 1 ]; then \
		echo "🧠 compiling  $(2)..."; \
		$(MAKE) -sr CFLAGS="$(CFLAGS)" $(1); \
	elif [ $$status -ne 0 ]; then \
		exit $$status; \
	fi
endef
# BUILD MACRO (END)

# INCLUDES SELECTION (START)
$(GRAM_OBJS): BUILD_INCLUDES := $(GRAM_INCLUDES)
$(GEN_CORE_OBJS): BUILD_INCLUDES := $(GEN_INCLUDES)
$(LR_TAB_CORE_OBJS): BUILD_INCLUDES := $(LR_TAB_INCLUDES)
$(SHELL_CORE_OBJS): BUILD_INCLUDES := $(SHELL_INCLUDES)
# INCLUDES SELECTION (END)

# PUBLIC RULES (START)
all: _build_shell

tables: _generate_tables
# PUBLIC RULES (END)

# PRIVATE RULES (START)
_force_libft:

_compile_grammar:
	$(call BUILD_SECTION,$(GRAM_OBJS),grammar)

_build_generator: $(LIBFT) _compile_grammar # _compile_logs
	$(call BUILD_SECTION,$(GEN_CORE_OBJS),generator)
	@$(MAKE) -s CFLAGS="$(CFLAGS)" $(GEN_NAME)

_generate_tables: 
	@if [ ! -f $(LR_TAB_MARKER) ] \
		|| [ ! -f $(LR_TAB_GEN_DIR)/lr_tables.h ] \
		|| [ ! -f $(LR_TAB_GEN_DIR)/lr_tables.c ]; then \
		rm -f $(LR_TAB_MARKER); \
	fi
	@$(MAKE) -s CFLAGS="$(CFLAGS)" $(LR_TAB_MARKER)

_compile_tables: _generate_tables
	$(call BUILD_SECTION,$(LR_TAB_CORE_OBJS),lr tables)

_build_shell: $(LIBFT) _compile_tables # _compile_logs
	$(call BUILD_SECTION,$(SHELL_CORE_OBJS),shell)
	@$(MAKE) -s CFLAGS="$(CFLAGS)" $(NAME)
# PRIVATE RULES (END)

$(LIBFT): _force_libft
	@$(MAKE) -s -C $(LIBFT_DIR)

$(GEN_NAME): $(GEN_OBJS) $(LIBFT)
	@echo "👉 linking    generator..."
	@$(CC) $(CFLAGS) $(GEN_OBJS) $(LIBFT) -o $(GEN_NAME)

$(LR_TAB_MARKER): $(LR_TAB_INPUTS)
	@$(MAKE) -s _build_generator
	@echo "🧮 generating lr tables..."
	@mkdir -p $(LR_TAB_GEN_DIR)
	@./$(GEN_NAME)
	@touch $(LR_TAB_MARKER)

$(NAME): $(SHELL_OBJS) $(LIBFT)
	@echo "👉 linking    shell..."
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
	@echo "🧪 preparing for tests..."
	@$(MAKE) re CFLAGS="$(CFLAGS)"
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

-include $(shell find $(GRAM_DEPS) -type f 2>/dev/null)
-include $(shell find $(GEN_DEPS) -type f 2>/dev/null)
-include $(shell find $(LR_TAB_DEPS) -type f 2>/dev/null)
-include $(shell find $(SHELL_DEPS) -type f 2>/dev/null)

.PHONY: all tables bonus debug test clean fclean re \
	_force_libft _compile_grammar _compile_tables \
	_build_generator _generate_tables _build_shell
