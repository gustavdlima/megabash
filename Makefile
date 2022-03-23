NAME			= minishell

CC				= gcc
CFLAGS			= -g -Wall -Werror -Wextra
RM				= rm -f
VALGRIND 		= valgrind --leak-check=full --show-leak-kinds=all

INCLUDES_DIR	= includes libs/libft
INCLUDES		= $(addprefix -I,$(INCLUDES_DIR))

SRC_DIR			= ./src
OBJ_DIR	 		= ./build
ENV_PATH		= environment/
LIST_PATH 		= list_utils/
UTILS_PATH		= utils/


LIBFT_PATH	 	= ./libs/libft
LIBFT			= $(LIBFT_PATH)/libft.a
LIBFT_FLAGS		= -L$(LIBFT_PATH) -lft

SRCS	=	minishell.c			\
			$(ENV_PATH)environment.c 		\
			$(ENV_PATH)env_operations.c 	\
			$(LIST_PATH)env_list_utils.c 	\
			$(UTILS_PATH)utils.c 			\

OBJS	:= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
SRCS	:= $(addprefix $(SRC_DIR)/,$(SRCS))


all:	$(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INCLUDES) $(LIBFT_FLAGS) -lreadline

$(LIBFT):
	make -C $(LIBFT_PATH)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(ENV_PATH))
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(LIST_PATH))
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(UTILS_PATH))
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
