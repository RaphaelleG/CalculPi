NAME = main

FILES = \
			main.c \
			big_int.c \
			utils.c \

OBJ = $(FILES:%.c=%.o)

CC ?= gcc

CFLAGS = -g -Wall -std=c11
# CFLAGS = -Wall -Werror -Wextra -std=c11

LDLIBS = -lm -lreadline

.PHONY: all
all : $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDLIBS)
	@echo "executer ./$@"

%.o: %.c
	@$(CC) $(CFLAGS) -c $? -o $@
	@echo "Compiling $?"

.PHONY: fclean
fclean:
	rm -rf *~ *.o $(NAME)
	rm -rf .DS_Store~

.PHONY: re
re: fclean all
