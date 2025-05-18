NAME = minishell
RM = rm -rf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MKDIR = mkdir -p
OBJDIR = OBJECTS
RLFLAGS = -lreadline
CMPL = $(CC) $(CFLAGS)
SRC		=	./src/utils/ft_load.c \
			./src/utils/input_check.c \
			./src/utils/free_functs.c \
			./src/utils/ft_entry.c \
			./src/utils/ft_error.c \
			./src/utils/ft_exit.c \
			./src/utils/ft_signal.c \
			./src/utils/utils2.c \
			./src/parser/ft_trim_quotes.c \
			./src/parser/lexer_utils.c \
			./src/parser/lexer.c \
			./src/parser/parser.c \
			./src/load_cmd/load_cmd.c \
			./src/load_cmd/load_cmd_utils.c \
			./src/load_cmd/load_cmd_error.c \
			./src/load_cmd/heredocfile.c \
			./src/expander/expander.c \
			./src/expander/expander_utils.c \
			./src/executer/ft_execute.c \
			./src/executer/get_path.c \
			./src/built_in/ft_cd.c \
			./src/built_in/ft_echo.c \
			./src/built_in/ft_env.c \
			./src/built_in/ft_export.c \
			./src/built_in/ft_pwd.c \
			./src/built_in/ft_unset.c \
			./src/built_in/ft_exit_cmd.c \
			./src/built_in/built_in_utils.c \
			./src/main.c

OBJS =		./src/utils/ft_load.o \
			./src/utils/input_check.o \
			./src/utils/free_functs.o \
			./src/utils/ft_entry.o \
			./src/utils/ft_error.o \
			./src/utils/ft_exit.o \
			./src/utils/ft_signal.o \
			./src/utils/utils2.o \
			./src/parser/ft_trim_quotes.o \
			./src/parser/lexer_utils.o \
			./src/parser/lexer.o \
			./src/parser/parser.o \
			./src/load_cmd/load_cmd.o \
			./src/load_cmd/load_cmd_utils.o \
			./src/load_cmd/load_cmd_error.o \
			./src/load_cmd/heredocfile.o \
			./src/expander/expander.o \
			./src/expander/expander_utils.o \
			./src/executer/ft_execute.o \
			./src/executer/get_path.o \
			./src/built_in/ft_cd.o \
			./src/built_in/ft_echo.o \
			./src/built_in/ft_env.o \
			./src/built_in/ft_export.o \
			./src/built_in/ft_pwd.o \
			./src/built_in/ft_unset.o \
			./src/built_in/ft_exit_cmd.o \
			./src/built_in/built_in_utils.o \
			./src/main.o

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft all
	@$(CMPL) $(RLFLAGS) $(OBJS) ./libft/libft.a -o $(NAME)

clean:
	@make -C ./libft clean
	@$(RM) $(OBJS)

fclean: clean
	@make -C ./libft fclean
	@$(RM) $(NAME)

re: fclean all

v :
	valgrind -s --leak-check=full --show-leak-kinds=definite ./$(NAME)

.PHONY: all clean fclean re
