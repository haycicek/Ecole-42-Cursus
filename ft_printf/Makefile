# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 14:11:15 by haycicek          #+#    #+#              #
#    Updated: 2023/01/19 14:11:27 by haycicek         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror

SRC = ft_*.c;

OBJ = ft_*.o

all: ${NAME}

${NAME}:
	@gcc ${FLAGS} -c ${SRC}
	@ar -rcs ${NAME} ${OBJ}

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re