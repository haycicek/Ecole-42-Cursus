# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 14:22:36 by haycicek          #+#    #+#              #
#    Updated: 2023/02/17 14:22:50 by haycicek         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAG = -Wall -Wextra -Werror
SRC = $(shell find . ! -name "ft_lst*.c" -name "ft_*.c")
BONUS = $(shell find . -name "ft_lst*.c")

CC		= gcc

all: $(NAME)

$(NAME):
	@$(CC) $(FLAG) -c $(SRC)
	@ar rc $(NAME) *.o
bonus:
	@$(CC) $(FLAG) -c $(BONUS)
	@ar rc $(NAME) *.o
clean:
	@/bin/rm -f  *.o *.out
fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re