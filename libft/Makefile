# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/12 00:00:00 by Copilot           #+#    #+#              #
#    Updated: 2026/03/30 23:06:25 by adouieb          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#                                   VARIABLES                                  #
# ============================================================================ #

# Variable to control header printing (0 = print, 1 = suppress)
PREC_RULE:=0
IN_TEST:=0
# Variable to catch norminette errors
NORM_ERRORS:=""

# Project name for display
PROJECT:=libft

# Compiler and flags
CC:=cc
CC_FLAGS:=-Werror -Wextra -Wall

# Archiver and flags
AR:=ar
AR_FLAGS:=-rc

# Directories
BUILD_DIR:=build
HDR_DIR:=includes
SRC_DIR:=srcs
OBJ_DIR:=objs
TEST_DIR:=test

# Output library name
NAME:=${BUILD_DIR}/libft.a

GNL_DIR   :=${SRC_DIR}/gnl
CHAR_DIR  :=${SRC_DIR}/char
LIST_DIR  :=${SRC_DIR}/list
MATH_DIR  :=${SRC_DIR}/math
BUFFER_DIR:=${SRC_DIR}/buffer
STRING_DIR:=${SRC_DIR}/string
PRINTF_DIR:=${SRC_DIR}/printf

BUFFER_SRCS:=${BUFFER_DIR}/constructor/cbuf.c	\
		${BUFFER_DIR}/constructor/dbuf.c		\
		${BUFFER_DIR}/constructor/free.c		\
		${BUFFER_DIR}/method/find.c				\
		${BUFFER_DIR}/method/shift.c			\
		${BUFFER_DIR}/method/insert.c			\
		${BUFFER_DIR}/method/compare.c
CHAR_SRCS:=${CHAR_DIR}/isalnum.c	\
		${CHAR_DIR}/isalpha.c		\
		${CHAR_DIR}/isascii.c		\
		${CHAR_DIR}/isdigit.c		\
		${CHAR_DIR}/isprint.c		\
		${CHAR_DIR}/isspace.c		\
		${CHAR_DIR}/tolower.c		\
		${CHAR_DIR}/toupper.c		\
		${CHAR_DIR}/ishexdigit.c	\
		${CHAR_DIR}/islowercase.c	\
		${CHAR_DIR}/isuppercase.c
LIST_SRCS:=${LIST_DIR}/constructor/free.c	\
		${LIST_DIR}/constructor/lst.c		\
		${LIST_DIR}/constructor/node.c		\
		${LIST_DIR}/method/get.c 			\
		${LIST_DIR}/method/iter.c			\
		${LIST_DIR}/method/insert.c
MATH_BASIC_SRCS:=${MATH_DIR}/abs.c			\
		${MATH_DIR}/ceil.c					\
		${MATH_DIR}/floor.c					\
		${MATH_DIR}/max.c					\
		${MATH_DIR}/min.c					\
		${MATH_DIR}/round.c					\
		${MATH_DIR}/sqrt.c					\
		${MATH_DIR}/power.c					\
		${MATH_DIR}/is_prime.c
MATH_2D_SRCS:=${MATH_DIR}/linear_algebra/2D/constructor/free.c	\
		${MATH_DIR}/linear_algebra/2D/constructor/vec2_arr.c	\
		${MATH_DIR}/linear_algebra/2D/constructor/vec2_f32.c	\
		${MATH_DIR}/linear_algebra/2D/constructor/vec2_i32.c	\
		${MATH_DIR}/linear_algebra/2D/constructor/vec2_u32.c	\
		${MATH_DIR}/linear_algebra/2D/method/add.c				\
		${MATH_DIR}/linear_algebra/2D/method/arr_add.c			\
		${MATH_DIR}/linear_algebra/2D/method/cross_product.c	\
		${MATH_DIR}/linear_algebra/2D/method/dot_product.c		\
		${MATH_DIR}/linear_algebra/2D/method/equal.c			\
		${MATH_DIR}/linear_algebra/2D/method/iter.c				\
		${MATH_DIR}/linear_algebra/2D/method/multiply.c			\
		${MATH_DIR}/linear_algebra/2D/method/norm.c				\
		${MATH_DIR}/linear_algebra/2D/method/normalize.c		\
		${MATH_DIR}/linear_algebra/2D/method/substract.c		\
		${MATH_DIR}/linear_algebra/2D/method/swap.c
MATH_3D_SRCS:=${MATH_DIR}/linear_algebra/3D/constructor/free.c	\
		${MATH_DIR}/linear_algebra/3D/constructor/vec3_arr.c	\
		${MATH_DIR}/linear_algebra/3D/constructor/vec3_f32.c	\
		${MATH_DIR}/linear_algebra/3D/constructor/vec3_i32.c	\
		${MATH_DIR}/linear_algebra/3D/constructor/vec3_u32.c	\
		${MATH_DIR}/linear_algebra/3D/method/add.c				\
		${MATH_DIR}/linear_algebra/3D/method/arr_add.c			\
		${MATH_DIR}/linear_algebra/3D/method/arr_set.c			\
		${MATH_DIR}/linear_algebra/3D/method/cross_product.c	\
		${MATH_DIR}/linear_algebra/3D/method/dot_product.c		\
		${MATH_DIR}/linear_algebra/3D/method/equal.c			\
		${MATH_DIR}/linear_algebra/3D/method/filter.c			\
		${MATH_DIR}/linear_algebra/3D/method/iter.c				\
		${MATH_DIR}/linear_algebra/3D/method/multiply.c			\
		${MATH_DIR}/linear_algebra/3D/method/norm.c				\
		${MATH_DIR}/linear_algebra/3D/method/normalize.c		\
		${MATH_DIR}/linear_algebra/3D/method/substract.c
MATH_4D_CONSTRUCTOR_SRCS:=${MATH_DIR}/linear_algebra/4D/constructor/quaternion.c	\
		${MATH_DIR}/linear_algebra/4D/constructor/vec4_f32.c						\
		${MATH_DIR}/linear_algebra/4D/constructor/vec4_i32.c						\
		${MATH_DIR}/linear_algebra/4D/constructor/vec4_u32.c
MATH_4D_METHOD_SRCS:=${MATH_DIR}/linear_algebra/4D/method/equal.c	\
		${MATH_DIR}/linear_algebra/4D/method/norm.c					\
		${MATH_DIR}/linear_algebra/4D/method/normalize.c			\
		${MATH_DIR}/linear_algebra/4D/method/quaternion.c
PRINTF_SRCS:=${PRINTF_DIR}/printf.c			\
		${PRINTF_DIR}/rule.c				\
		${PRINTF_DIR}/parse.c				\
		${PRINTF_DIR}/flags.c				\
		${PRINTF_DIR}/convert_args.c		\
		${PRINTF_DIR}/flags_precision.c
GNL_SRCS:=${GNL_DIR}/get_next_line.c	\
		${GNL_DIR}/free.c				\
		${GNL_DIR}/reader.c 			\
		${GNL_DIR}/constructor.c
STRING_SRCS:=${STRING_DIR}/constructor/cstr.c		\
		${STRING_DIR}/constructor/dstr.c			\
		${STRING_DIR}/constructor/free.c			\
		${STRING_DIR}/constructor/dstr_arr.c		\
		${STRING_DIR}/constructor/cstr_arr.c		\
		${STRING_DIR}/method/arr_add.c				\
		${STRING_DIR}/method/sub.c					\
		${STRING_DIR}/method/find.c					\
		${STRING_DIR}/method/iter.c					\
		${STRING_DIR}/method/trim.c					\
		${STRING_DIR}/method/print.c				\
		${STRING_DIR}/method/split.c				\
		${STRING_DIR}/method/resize.c				\
		${STRING_DIR}/method/remove.c				\
		${STRING_DIR}/method/unwrap.c				\
		${STRING_DIR}/method/insert.c				\
		${STRING_DIR}/method/repeat.c				\
		${STRING_DIR}/method/compare.c				\
		${STRING_DIR}/method/int_conversion.c		\
		${STRING_DIR}/method/long_conversion.c		\
		${STRING_DIR}/method/char_conversion.c		\
		${STRING_DIR}/method/buffer_conversion.c

TUPLE_DIR:=${SRC_DIR}/tuple

TUPLE_SRCS:=${TUPLE_DIR}/tuple.c

SRCS:=${BUFFER_SRCS}			\
	${GNL_SRCS}				\
	${CHAR_SRCS}			\
	${LIST_SRCS}			\
	${MATH_BASIC_SRCS}		\
	${MATH_2D_SRCS}			\
	${MATH_3D_SRCS}			\
	${MATH_4D_CONSTRUCTOR_SRCS}\
	${MATH_4D_METHOD_SRCS}	\
	${PRINTF_SRCS}			\
	${STRING_SRCS}			\
	${TUPLE_SRCS}

# Object files (flat naming with category prefixes to avoid collisions)
GNL_OBJS=$(addprefix $(OBJ_DIR)/gnl_,$(notdir $(GNL_SRCS:.c=.o)))
CHAR_OBJS=$(addprefix $(OBJ_DIR)/char_,$(notdir $(CHAR_SRCS:.c=.o)))
LIST_OBJS=$(addprefix $(OBJ_DIR)/list_,$(notdir $(LIST_SRCS:.c=.o)))
MATH_BASIC_OBJS=$(addprefix $(OBJ_DIR)/math_,$(notdir $(MATH_BASIC_SRCS:.c=.o)))
MATH_2D_OBJS=$(addprefix $(OBJ_DIR)/math_2d_,$(notdir $(MATH_2D_SRCS:.c=.o)))
MATH_3D_OBJS=$(addprefix $(OBJ_DIR)/math_3d_,$(notdir $(MATH_3D_SRCS:.c=.o)))
MATH_4D_CONSTRUCTOR_OBJS=$(addprefix $(OBJ_DIR)/math_4d_constructor_,$(notdir $(MATH_4D_CONSTRUCTOR_SRCS:.c=.o)))
MATH_4D_METHOD_OBJS=$(addprefix $(OBJ_DIR)/math_4d_method_,$(notdir $(MATH_4D_METHOD_SRCS:.c=.o)))
BUFFER_OBJS=$(addprefix $(OBJ_DIR)/buffer_,$(notdir $(BUFFER_SRCS:.c=.o)))
PRINTF_OBJS=$(addprefix $(OBJ_DIR)/printf_,$(notdir $(PRINTF_SRCS:.c=.o)))
STRING_OBJS=$(addprefix $(OBJ_DIR)/string_,$(notdir $(STRING_SRCS:.c=.o)))
TUPLE_OBJS=$(addprefix $(OBJ_DIR)/tuple_,$(notdir $(TUPLE_SRCS:.c=.o)))

OBJS=${BUFFER_OBJS}			\
	${GNL_OBJS}				\
	${CHAR_OBJS}			\
	${LIST_OBJS}			\
	${MATH_BASIC_OBJS}		\
	${MATH_2D_OBJS}			\
	${MATH_3D_OBJS}			\
	${MATH_4D_CONSTRUCTOR_OBJS}\
	${MATH_4D_METHOD_OBJS}	\
	${PRINTF_OBJS}			\
	${STRING_OBJS}			\
	${TUPLE_OBJS}

# ============================================================================ #
#                                   HELPER                                     #
# ============================================================================ #

# Helper functions to map object files back to their source files
get-gnl-src = $(filter %/$(patsubst gnl_%.o,%.c,$(notdir $(1))),$(GNL_SRCS))
get-char-src = $(filter %/$(patsubst char_%.o,%.c,$(notdir $(1))),$(CHAR_SRCS))
get-list-src = $(filter %/$(patsubst list_%.o,%.c,$(notdir $(1))),$(LIST_SRCS))
get-math-basic-src = $(filter %/$(patsubst math_%.o,%.c,$(notdir $(1))),$(MATH_BASIC_SRCS))
get-math-2d-src = $(filter %/$(patsubst math_2d_%.o,%.c,$(notdir $(1))),$(MATH_2D_SRCS))
get-math-3d-src = $(filter %/$(patsubst math_3d_%.o,%.c,$(notdir $(1))),$(MATH_3D_SRCS))
get-math-4d-constructor-src = $(filter %/$(patsubst math_4d_constructor_%.o,%.c,$(notdir $(1))),$(MATH_4D_CONSTRUCTOR_SRCS))
get-math-4d-method-src = $(filter %/$(patsubst math_4d_method_%.o,%.c,$(notdir $(1))),$(MATH_4D_METHOD_SRCS))
get-buffer-src = $(filter %/$(patsubst buffer_%.o,%.c,$(notdir $(1))),$(BUFFER_SRCS))
get-printf-src = $(filter %/$(patsubst printf_%.o,%.c,$(notdir $(1))),$(PRINTF_SRCS))
get-string-src = $(filter %/$(patsubst string_%.o,%.c,$(notdir $(1))),$(STRING_SRCS))
get-tuple-src = $(filter %/$(patsubst tuple_%.o,%.c,$(notdir $(1))),$(TUPLE_SRCS))

# ============================================================================ #
#                                    RULES                                     #
# ============================================================================ #

.SECONDEXPANSION:

# Default rule: builds the library
all:
	@# Print header if this is the top-level call
	@if [ "$(PREC_RULE)" = "0" ]; \
	then \
		echo " \033[0;34m----- libft -----\033[0m"; \
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
	@# Build the library
	@if [ -f $(NAME) ] && [ -z "$$(find $(SRC_DIR) -newer $(NAME) 2>/dev/null)" ]; \
	then \
		echo " \033[0;33mNothing\033[0m to be done for '$(NAME)' (already up to date)"; \
	else \
		mkdir -p $(BUILD_DIR); \
		if [ ! -f $(NAME) ]; \
		then \
			$(MAKE) $(NAME) --no-print-directory -s; \
		fi; \
		if [ -d $(HDR_DIR) ]; \
		then \
			cp -r $(HDR_DIR) $(BUILD_DIR)/; \
		fi; \
		if [ -d $(SRC_DIR) ]; \
		then \
			cp -r $(SRC_DIR) $(BUILD_DIR)/; \
		fi; \
		echo " \033[0;32mSUCCESSFULLY\033[0m created build directory"; \
	fi

# Explicit compilation rules using secondexpansion to map sources to objects
$(BUFFER_OBJS): $(OBJ_DIR)/buffer_%.o: $$(call get-buffer-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@
$(CHAR_OBJS): $(OBJ_DIR)/char_%.o: $$(call get-char-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@
$(LIST_OBJS): $(OBJ_DIR)/list_%.o: $$(call get-list-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@
$(MATH_BASIC_OBJS): $(OBJ_DIR)/math_%.o: $$(call get-math-basic-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@
$(MATH_2D_OBJS): $(OBJ_DIR)/math_2d_%.o: $$(call get-math-2d-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@
$(MATH_3D_OBJS): $(OBJ_DIR)/math_3d_%.o: $$(call get-math-3d-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@
$(MATH_4D_CONSTRUCTOR_OBJS): $(OBJ_DIR)/math_4d_constructor_%.o: $$(call get-math-4d-constructor-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@
$(MATH_4D_METHOD_OBJS): $(OBJ_DIR)/math_4d_method_%.o: $$(call get-math-4d-method-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@
$(PRINTF_OBJS): $(OBJ_DIR)/printf_%.o: $$(call get-printf-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@
$(GNL_OBJS): $(OBJ_DIR)/gnl_%.o: $$(call get-gnl-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@
$(STRING_OBJS): $(OBJ_DIR)/string_%.o: $$(call get-string-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@
$(TUPLE_OBJS): $(OBJ_DIR)/tuple_%.o: $$(call get-tuple-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@

# Archives object files into the library
$(NAME): $(OBJS)
	@$(AR) $(AR_FLAGS) $@ $(OBJS) -o ${NAME}

# Cleans object files
clean:
	@# Print header if this is the top-level call
	@if [ "$(PREC_RULE)" = "0" ]; \
	then \
		echo " \033[0;34m----- libft -----\033[0m"; \
	fi
	@# Delete object directory if it exists
	@if [ -d ${OBJ_DIR} ] && [ "$(wildcard ${OBJ_DIR}/*)" ]; \
	then \
		rm -rf ${OBJ_DIR}/*; \
		if [ "$(IN_TEST)" -eq 0 ]; \
		then \
			echo " \033[0;31mDeleting\033[0m $(PROJECT) all obj files"; \
		fi; \
	elif [ "$(IN_TEST)" -eq 0 ]; \
	then \
		echo " \033[0;33mAlready\033[0m deleted $(PROJECT) all obj files"; \
	fi

# Cleans object files and the library
fclean:
	@# Print header if this is the top-level call
	@if [ "$(PREC_RULE)" = "0" ]; \
	then \
		echo " \033[0;34m----- libft -----\033[0m"; \
	fi
	@# Clean objects (suppress header)
	@$(MAKE) clean PREC_RULE=1 --no-print-directory
	@# Delete the library file
	@if [ -d ${BUILD_DIR} ]; \
	then \
		rm -rf $(BUILD_DIR); \
		if [ "$(IN_TEST)" -eq 0 ]; \
		then \
			echo " \033[0;31mDeleting\033[0m $(PROJECT) build"; \
		fi; \
	elif [ "$(IN_TEST)" -eq 0 ]; \
	then \
		echo " \033[0;33mAlready\033[0m deleted $(PROJECT) build"; \
	fi

# Rebuilds everything from scratch
re:
	@# Print header if this is the top-level call
	@if [ "$(PREC_RULE)" = "0" ]; \
	then \
		echo " \033[0;34m----- libft -----\033[0m"; \
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

# ============================================================================ #
#                                    TESTS                                     #
# ============================================================================ #

LIB_ALREADY_UP_TO_DATE:=0

TEST_NAME:=${TEST_DIR}/libft_tests

# Subdirectories for source files

GNL_TEST_DIR   :=${TEST_DIR}/gnl
CHAR_TEST_DIR  :=${TEST_DIR}/char
LIST_TEST_DIR  :=${TEST_DIR}/list
MATH_TEST_DIR  :=${TEST_DIR}/math
BUFFER_TEST_DIR:=${TEST_DIR}/buffer
STRING_TEST_DIR:=${TEST_DIR}/string
PRINTF_TEST_DIR:=${TEST_DIR}/printf

# Test source files
STRING_TEST_SRCS:=${STRING_TEST_DIR}/test_string_comprehensive.c \
		${STRING_TEST_DIR}/test_string_edge_cases.c

BUFFER_TEST_SRCS:=${BUFFER_TEST_DIR}/test_buffer_comprehensive.c \
		${BUFFER_TEST_DIR}/test_buffer_edge_cases.c

LIST_TEST_SRCS:=${LIST_TEST_DIR}/test_list_comprehensive.c \
		${LIST_TEST_DIR}/test_list_edge_cases.c

CHAR_TEST_SRCS:=${CHAR_TEST_DIR}/test_char_comprehensive.c

MATH_TEST_SRCS:=${MATH_TEST_DIR}/test_math_comprehensive.c \
		${MATH_TEST_DIR}/test_math_vector.c \
		${MATH_TEST_DIR}/test_math_advanced.c \
		${MATH_TEST_DIR}/test_math_edge_cases.c

PRINTF_TEST_SRCS:=${PRINTF_TEST_DIR}/test_printf_comprehensive.c \
		${PRINTF_TEST_DIR}/test_printf_edge_cases.c

GNL_TEST_SRCS:=${GNL_TEST_DIR}/test_gnl_comprehensive.c \
		${GNL_TEST_DIR}/test_gnl_edge_cases.c

# Malloc failure tests
MALLOC_FAILURE_TEST_SRCS:=${TEST_DIR}/test_malloc_failure_example.c

# Malloc wrapper for failure testing
MALLOC_WRAPPER:=${TEST_DIR}/malloc_wrapper.c

# Unified test runner
TEST_MAIN:=${TEST_DIR}/test_main.c

ALL_TEST_SRCS:=${TEST_MAIN} 	\
	${MALLOC_WRAPPER} 			\
	${GNL_TEST_SRCS} 			\
	${LIST_TEST_SRCS} 			\
	${CHAR_TEST_SRCS} 			\
	${MATH_TEST_SRCS}			\
	${PRINTF_TEST_SRCS}			\
	${STRING_TEST_SRCS} 		\
	${BUFFER_TEST_SRCS}			\
	${MALLOC_FAILURE_TEST_SRCS}

# Linker flags for malloc wrapping
WRAP_FLAGS:=-Wl,--wrap=malloc -Wl,--wrap=calloc -Wl,--wrap=realloc

# Build unified test executable
test:
	@# Print header if this is the top-level call
	@if [ "$(PREC_RULE)" = "0" ]; \
	then \
		echo " \033[0;34m----- libft -----\033[0m"; \
	fi
	@# Check norminette compliance (optional)
	@if command -v norminette >/dev/null 2>&1; \
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
	fi
	@echo ;
	@echo " \033[0;34m----- Building Libft -----\033[0m"
	@# Clean objects (suppress header)
	@$(MAKE) all PREC_RULE=1 IN_TEST=1 --no-print-directory
	@# Set LIB_ALREADY_UP_TO_DATE to 1 if the library was rebuilt
	@if [ ! -f $(NAME) ] || [ -n "$$(find $(SRC_DIR) -newer $(NAME) 2>/dev/null)" ]; \
	then \
		LIB_ALREADY_UP_TO_DATE=1; \
	fi
	@echo ;
	@# Check if valgrind is installed
	@if command -v valgrind >/dev/null 2>&1; \
	then \
		echo " \033[0;34m----- Building Test Suite with Debug Symbols -----\033[0m"; \
		$(CC) $(CC_FLAGS) -g3 -Wno-format-zero-length -Wno-format-overflow $(WRAP_FLAGS) -I./test -I${HDR_DIR} ${ALL_TEST_SRCS} -L${BUILD_DIR} -lft -lm -o ${TEST_NAME}; \
		echo " \033[0;32mSUCCESSFULLY\033[0m generated ${TEST_NAME} (with debug symbols + malloc wrapper)"; \
		echo ; \
		echo " \033[0;34m----- Running Tests with Valgrind -----\033[0m"; \
		./test/run_leak_test.sh ./${TEST_NAME}; \
	else \
		echo " \033[0;34m----- Building Test Suite -----\033[0m"; \
		$(CC) $(CC_FLAGS) -Wno-format-zero-length -Wno-format-overflow $(WRAP_FLAGS) -I./test -I${HDR_DIR} ${ALL_TEST_SRCS} -L${BUILD_DIR} -lft -lm -o ${TEST_NAME}; \
		echo " \033[0;32mSUCCESSFULLY\033[0m generated ${TEST_NAME} (with malloc wrapper)"; \
		echo ; \
		echo " \033[0;34m----- Running All Tests -----\033[0m"; \
		./${TEST_NAME}; \
		echo ; \
		echo " \033[0;33m⚠️  Valgrind not installed - skipping leak detection\033[0m"; \
		echo " Install with: sudo apt-get install valgrind"; \
	fi
	@rm -f ${TEST_NAME}
	@# Clean up object files when build for test (suppress header)
	@if [ "$(LIB_ALREADY_UP_TO_DATE)" -eq 0 ]; \
	then \
		$(MAKE) fclean PREC_RULE=1 IN_TEST=1 --no-print-directory; \
	fi

# Phony targets
.PHONY: all clean fclean re test test_clean
