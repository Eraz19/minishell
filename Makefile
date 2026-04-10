# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/17 18:30:00 by adouieb           #+#    #+#              #
#    Updated: 2026/04/09 17:09:54 by adouieb          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#                                   VARIABLES                                  #
# ============================================================================ #

# Variable to control header printing (0 = print, 1 = suppress)
PREC_RULE:=0
# Variable to catch norminette errors
NORM_ERRORS:=""

# Project name for display
PROJECT:=minishell

# Compiler and flags
CC:=cc
CC_FLAGS:=-Wall -Wextra -Werror
LDFLAGS:=-lreadline

# Directories
HDR_DIR:=includes
SRC_DIR:=srcs
OBJ_DIR:=objs
LIB_DIR:=libft
LIB_HDR_DIR:=$(LIB_DIR)/includes
LIB_BUILD_DIR:=$(LIB_DIR)/build

PROMPT_DIR=${SRC_DIR}/prompt
PROMPT_LABEL_DIR=${PROMPT_DIR}/label
PROMPT_HISTORY_DIR=${PROMPT_DIR}/history
PROMPT_DISPLAY_DIR=${PROMPT_DIR}/display

# Output executable name
NAME:=minishell

INCLUDES:=-I$(LIB_HDR_DIR)	\
	-I$(HDR_DIR)			\
	-I$(PROMPT_LABEL_DIR)	\
	-I$(PROMPT_HISTORY_DIR)	\
	-I$(PROMPT_DISPLAY_DIR)

PROMPT_DISPLAY_SRCS=${PROMPT_DISPLAY_DIR}/display_prompt.c

PROMPT_LABEL_SRCS=${PROMPT_LABEL_DIR}/prompt_label.c

PROMPT_HISTORY_SRCS=${PROMPT_HISTORY_DIR}/prompt_history.c

SRCS:=${PROMPT_DISPLAY_SRCS}	\
	${PROMPT_LABEL_SRCS}		\
	${PROMPT_HISTORY_SRCS}		\
	${SRC_DIR}/main.c

OBJS=$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ============================================================================ #
#                                    RULES                                     #
# ============================================================================ #

# Default rule: builds the executable
all:
	@# Print header if this is the top-level call
	@if [ "$(PREC_RULE)" = "0" ]; \
	then \
		${MAKE} libft --no-print-directory -s; \
		echo " \033[0;34m----- ${PROJECT} -----\033[0m"; \
		if command -v norminette >/dev/null 2>&1; \
		then \
			NORM_ERRORS=$$(norminette $(SRC_DIR) $(HDR_DIR) 2>&1); \
			if [ $$? -ne 0 ]; \
			then \
				echo " \033[0;35mChecking\033[0m norminette compliance \033[0;31m✗\033[0m"; \
				echo "$$NORM_ERRORS" | sed 's/^/ /'; \
				echo ; \
				echo " \033[0;31mNorminette errors found. Aborting build.\033[0m"; \
				exit 1; \
			else \
				echo " \033[0;35mChecking\033[0m norminette compliance \033[0;32m✓\033[0m"; \
			fi; \
		else \
			echo " \033[0;33mSkipping\033[0m norminette check (not installed)"; \
		fi; \
	fi
	@# Build executable
	@if [ -f $(NAME) ] && [ -z "$$(find $(SRC_DIR) -newer $(NAME) 2>/dev/null)" ]; \
	then \
		echo " \033[0;33mNothing\033[0m to be done for '$(NAME)' (already up to date)"; \
	else \
		if [ ! -f $(NAME) ]; \
		then \
			$(MAKE) $(NAME) --no-print-directory -s && \
			echo " \033[0;32mSUCCESSFULLY\033[0m created executable '$(NAME)'"; \
		fi; \
	fi

# Explicit compilation rules for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo " Generating $@"
	@$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

# Linking rule for the final executable
$(NAME): $(OBJS)
	@$(CC) $(CC_FLAGS) $(INCLUDES) -L$(LIB_BUILD_DIR) $(OBJS) -lft $(LDFLAGS) -o $(NAME)

# Rule to build the libft library
libft:
	@make -C $(LIB_DIR) --no-print-directory -s

# Rule for bonus
bonus: all

# Cleans object files
clean:
	@# Only clean sub-libraries if this is a standalone clean (not called from fclean)
	@if [ "$(PREC_RULE)" = "0" ]; \
	then \
		make -C $(LIB_DIR) clean --no-print-directory -s; \
		echo " \033[0;34m----- ${PROJECT} -----\033[0m"; \
	fi
	@# Delete object directory if it exists
	@if [ -d ${OBJ_DIR} ] && [ "$(wildcard ${OBJ_DIR}/*)" ]; \
	then \
		rm -rf $(OBJ_DIR)/*; \
		echo " \033[0;31mDeleting\033[0m $(PROJECT) all obj files"; \
	else \
		echo " \033[0;33mAlready\033[0m deleted $(PROJECT) all obj files"; \
	fi

# Cleans object files and the executable
fclean:
	@# Print header if this is the top-level call
	@if [ "$(PREC_RULE)" = "0" ]; \
	then \
		make -C $(LIB_DIR) fclean --no-print-directory -s; \
		echo " \033[0;34m----- ${PROJECT} -----\033[0m"; \
	fi
	@# Clean objects (suppress header)
	@$(MAKE) clean PREC_RULE=1 --no-print-directory
	@# Delete the executable
	@if [ -f ${NAME} ]; \
	then \
		rm -f $(NAME); \
		echo " \033[0;31mDeleting\033[0m $(PROJECT) executable"; \
	else \
		echo " \033[0;33mAlready\033[0m deleted $(PROJECT) executable"; \
	fi

# Rebuilds everything from scratch
re:
	@# Print header if this is the top-level call
	@if [ "$(PREC_RULE)" = "0" ]; \
	then \
		make -C $(LIB_DIR) re --no-print-directory -s; \
		echo " \033[0;34m----- ${PROJECT} -----\033[0m"; \
		if command -v norminette >/dev/null 2>&1; \
		then \
			NORM_ERRORS=$$(norminette $(SRC_DIR) $(HDR_DIR) 2>&1); \
			if [ $$? -ne 0 ]; \
			then \
				echo " \033[0;35mChecking\033[0m norminette compliance \033[0;31m✗\033[0m"; \
				echo "$$NORM_ERRORS" | sed 's/^/ /'; \
				echo ; \
				echo " \033[0;31mNorminette errors found. Aborting build.\033[0m"; \
				exit 1; \
			else \
				echo " \033[0;35mChecking\033[0m norminette compliance \033[0;32m✓\033[0m"; \
			fi; \
		else \
			echo " \033[0;33mSkipping\033[0m norminette check (not installed)"; \
		fi; \
	fi
	@# Full clean (suppress header)
	@$(MAKE) fclean PREC_RULE=1 --no-print-directory
	@# Add a newline for readability if top-level
	@if [ "$(PREC_RULE)" = "0" ]; \
	then \
		echo ; \
	fi
	@# Build all (suppress header)
	@$(MAKE) all PREC_RULE=1 --no-print-directory

.PHONY: all clean fclean re libft mlx bonus
