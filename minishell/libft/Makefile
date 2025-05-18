NAME = libft.a
RM = rm -rf
CC = gcc
FLAG = -Wall -Wextra -Werror
CMPL = $(CC) $(FLAG) -c
MKDIR = mkdir
MV = mv
SRC = 	./split.c			\
 		./strchr.c			\
 		./strdup.c			\
 		./strjoin.c			\
		./strlcpy.c			\
 		./strlen.c 			\
		./strcmp.c			\
 		./strncmp.c 		\
		./substr.c			\
		./putstr_fd.c		\
		./calloc.c			\
		./itoa.c			\
		./isalnum.c			\
		./isalpha.c			\
		./strcpy.c			\
		./strcat.c			\
		./atoi.c			\
		./isdigit.c			\
		./bzero.c			\
		./memset.c			\
		./strstr.c

OBJ = $(SRC:.c=.o)
OBJDIR = OBJECTS

all: $(NAME)

$(NAME) :
	@$(MKDIR) $(OBJDIR)
	@$(CMPL) $(SRC)
	@ar rc $(NAME) $(OBJ)
	@$(MV) $(OBJ) $(OBJDIR)

clean :
	@$(RM) $(OBJDIR)

fclean : clean
	@$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all bonus clean fclean re
