# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 14:45:53 by haycicek          #+#    #+#              #
#    Updated: 2023/02/17 14:45:56 by haycicek         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
LIBFT = libft
FLAG = -Wall -Wextra -Werror
all: $(NAME)
		@gcc $(FLAG) server.c $(NAME) -o server
		@gcc $(FLAG) client.c $(NAME) -o client
$(NAME): $(LIBFT)
		@make -C $(LIBFT)
		@cp libft/libft.a .
		@echo "✅"
clean:
		@make clean -C $(LIBFT)
fclean: clean
		@make fclean -C $(LIBFT)
		@rm -rf $(NAME)
		@rm -rf server client
		@echo "🗑️"
re: fclean all

.PHONY: clean fclean all