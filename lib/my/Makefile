##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Make lib
##

SRC		=	my_split.c

DEST_LIB_DIR	=	.

OBJ	=	$(SRC:.c=.o)

CFLAGS	+=	-W -Wall -Wextra -g

NAME	=	libmy.a

all: $(NAME)

$(GCC): $(OBJ)
	gcc $(OBJ) -o $(NAME) $(CFLAGS)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
