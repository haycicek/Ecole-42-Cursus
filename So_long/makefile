# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 19:35:12 by haycicek          #+#    #+#              #
#    Updated: 2023/06/16 19:36:56 by haycicek         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
OBJECTS = $(shell find ./ -name "*.o")
A = $(shell find ./ -name "*.a")
CC = gcc

FLAGS = -framework OpenGL  -framework AppKit -L./minilibx -lmlx -g

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

CFILES = $(shell find . -name "*.c")
	
all:
	@make -C ./libft
	@make -C ./ft_printf
	@make -C ./minilibx
	$(CC) ./src/*.c ./libft/libft.a  ./ft_printf/libftprintf.a  $(FLAGS) -o so_long

clean:
	@rm -f $(OBJECTS)
	@echo $(R)Removed [$(OBJECTS)]$(X)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(A)
	@echo $(R)Removed [$(NAME)]$(X)

re: fclean all

norm:
	@echo $(Y)[--NORMINETTE SUCCES %100 CLEAN CODE...]$(G)
	norminette $(shell find ./src/ -name "*.c")

.PHONY: all clean fclean re