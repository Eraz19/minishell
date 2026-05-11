NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -O2 # -DNDEBUG # -g3 -fsanitize=address,undefined # -fsanitize=leak # -fsanitize=memory

LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a

SRCS		:= \
	$(wildcard srcs/*.c) \
	$(wildcard srcs/0_posix_helpers/*.c) \
	$(wildcard srcs/0_asm_stubs/*/*.c) \
	$(wildcard srcs/1_shell/*.c) \
	$(wildcard srcs/3_builder/*.c) \
	$(wildcard srcs/3_builder/*/*.c) \
	$(wildcard srcs/3_builder/*/*/*.c) \
	$(wildcard srcs/builtins/*.c) \
	$(wildcard srcs/builtins/*/*.c) \
	$(wildcard srcs/params/*.c) \
	$(wildcard srcs/params/*/*.c) \
	$(wildcard srcs/params/*/*/*.c) \
	$(wildcard srcs/params/*/*/*/*.c) \
	$(wildcard srcs/params/*/*/*/*/*.c)

INCLUDES	:= \
	-Ilibft \
	-Iincludes \
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
	-Isrcs/builtins \
	-Isrcs/builtins/export \
	-Isrcs/builtins/readonly \
	-Isrcs/builtins/unset \
	-Isrcs/params/1_variables \
	-Isrcs/params/1_variables/load \
	-Isrcs/params/1_variables/load/1_envp \
	-Isrcs/params/1_variables/load/2_mandatory \
	-Isrcs/params/1_variables/load/2_mandatory/ft_getppid \
	-Isrcs/params/1_variables/load/3_up \
	-Isrcs/params/2_options \
	-Isrcs/params/3_specials \
	-Isrcs/params/4_functions

OBJ_DIR		:= obj
OBJS		:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: all

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
