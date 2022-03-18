NAME	= minishell

CC	= gcc
CFLAGS	= -g -Wall -Werror -Wextra
RM	= rm -f
VALGRIND =	valgrind --leak-check=full --show-leak-kinds=all

INCLUDES_DIR	= ./includes ./libs/libft
SRC_DIR	= ./src
OBJ_DIR	 = ./src/build

LIBFT_PATH	 = ./libs/libft
LIBFT	= $(LIBFT_PATH)/libft.a
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft
INCLUDES	= $(addprefix -I,$(INCLUDES_DIR))

SRCS	= minishell.c megastart.c command_line.c process.c execute_process.c \
			minishell_utils.c metacharacters_treat.c quotes_treat.c \
			line_input_treat.c redirections_treat.c space_treat.c \
			init_struct.c lst_utils.c env_operations.c env.c \
			check_builtins.c builtin_export.c \

OBJS	:= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
SRCS	:= $(addprefix $(SRC_DIR)/,$(SRCS))

all:	$(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INCLUDES) $(LIBFT_FLAGS) -lreadline

$(LIBFT):
	make -C $(LIBFT_PATH)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LIBFT_FLAGS)

clean:
	make clean -C $(LIBFT_PATH)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

re:	fclean all

run: all
	./$(NAME) $$ARG

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME) $$ARG

.PHONY:	all clean fclean re go valgrind
