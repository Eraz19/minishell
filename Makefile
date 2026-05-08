NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address

LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a

SRCS		:= \
	$(wildcard srcs/*.c) \
	$(wildcard srcs/0_posix_helpers/*.c) \
	$(wildcard srcs/1_loader/*.c) \
	$(wildcard srcs/3_builder/*.c) \
	$(wildcard srcs/3_builder/1_lr_machine/*/*.c) \
	$(wildcard srcs/builtins/*/*.c) \
	$(wildcard srcs/variables/*.c) \
	$(wildcard srcs/variables/0_load/1_envp/*.c) \
	$(wildcard srcs/variables/0_load/2_mandatory/*.c) \
	$(wildcard srcs/variables/0_load/2_mandatory/0_ft_getppid/*.c) \
	$(wildcard srcs/variables/0_load/3_up/*.c)

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
	-Isrcs/3_builder/builtins \
	-Isrcs/3_builder/builtins/export \
	-Isrcs/3_builder/builtins/readonly \
	-Isrcs/3_builder/builtins/unset \
	-Isrcs/3_builder/variables/load \
	-Isrcs/3_builder/variables/load/1_envp \
	-Isrcs/3_builder/variables/load/2_mandatory \
	-Isrcs/3_builder/variables/load/2_mandatory/ft_getppid \
	-Isrcs/3_builder/variables/load/3_up

OBJ_DIR		:= obj
OBJ			:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

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
