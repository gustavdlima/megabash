NAME			= minishell

CC				= gcc
CFLAGS			= -g -Wall -Wextra #-Werror
RM				= rm -f
VALGRIND 		= valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp


INCLUDES_DIR	= includes libs/libft
INCLUDES		= $(addprefix -I,$(INCLUDES_DIR))

SRC_DIR			= ./src
OBJ_DIR	 		= ./build
ENV_PATH		= environment/
LIST_PATH 		= list_utils/
UTILS_PATH		= utils/
INPUT_PATH		= input/
TOKEN_PATH		= tokenizer/
BUILTIN_PATH	= builtins/
FREE_PATH		= free_functions/
SIGNAL_PATH		= signal/
COMMAND_PATH	= command/
PARSE_PATH		= parse/

LIBFT_PATH	 	= ./libs/libft
LIBFT			= $(LIBFT_PATH)/libft.a
LIBFT_FLAGS		= -L$(LIBFT_PATH) -lft

SRCS	=	minishell.c	\
			$(INPUT_PATH)expand_env.c					\
			$(INPUT_PATH)read_input.c					\
			$(INPUT_PATH)check_input.c					\
			$(INPUT_PATH)treat_input.c					\
			$(INPUT_PATH)treat_operators.c				\
			$(INPUT_PATH)validate_input.c				\
			$(INPUT_PATH)is_builtin.c					\
			$(COMMAND_PATH)cmd_path.c					\
			$(BUILTIN_PATH)chdir.c						\
			$(BUILTIN_PATH)exit.c						\
			$(BUILTIN_PATH)export.c						\
			$(BUILTIN_PATH)pwd.c						\
			$(BUILTIN_PATH)unset.c						\
			$(TOKEN_PATH)quotes.c						\
			$(TOKEN_PATH)special_or_metacharacters.c	\
			$(TOKEN_PATH)tokenizer.c					\
			$(PARSE_PATH)parsing.c						\
			$(ENV_PATH)environment.c 					\
			$(ENV_PATH)env_operations.c 				\
			$(SIGNAL_PATH)signal.c						\
			$(LIST_PATH)env_list_utils.c 				\
			$(LIST_PATH)cmd_list_utils.c 				\
			$(LIST_PATH)token_list_utils.c 				\
			$(UTILS_PATH)treat_input_utils.c			\
			$(UTILS_PATH)dollar_utils.c					\
			$(UTILS_PATH)utils.c 						\
			$(UTILS_PATH)validate_utils.c 				\
			$(FREE_PATH)free.c							\

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
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(TOKEN_PATH))
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(INPUT_PATH))
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(BUILTIN_PATH))
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(FREE_PATH))
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(SIGNAL_PATH))
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(COMMAND_PATH))
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(PARSE_PATH))
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LIBFT_FLAGS)

clean:
	make clean -C $(LIBFT_PATH)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

re:	fclean all

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME) $$ARG

.PHONY:	all clean fclean re valgrind
