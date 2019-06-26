##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Compilation
##

LIB_PATH	=	./lib/my

SRC_proj	=	src/main.c \
				src/args_handler.c \
				src/mychap.c \
				src/headers.c \
				src/socket.c \
				src/error.c \
				src/free.c \

SRC_test	= 	tests/test.c

OBJ		=	$(SRC_proj:.c=.o)

CFLAGS		+=	-W -Wall -Wextra -g

LDFLAG		=	-lcriterion -lgcov

MAKE =		@make -s -C

NAME	=	client

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) $(LIB_PATH) re
	@gcc $(OBJ) -o $(NAME) $(CFLAGS) -I./include -L./lib/my -lmy

tests_run:
	cc -o units $(SRC_proj) $(SRC_test) $(LDFLAG) --coverage
	./units

clean:
	rm -f $(OBJ) *.gcno *.gcda

fclean: clean_lib clean
	rm -f $(NAME)

re: fclean all

clean_lib:
	$(MAKE) $(LIB_PATH) fclean
