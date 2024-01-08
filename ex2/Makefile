NAME = best
SRCS = super.c score.c
OBJS = $(SRCS:%.c=%.o)
CC	 = gcc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

test:	$(NAME)
	./best 3

clean:
	rm -f $(OBJS)
	rm super_morpion.dot

fclean: clean
	rm -f $(NAME)
	rm g.png

re: fclean all

.PHONY: all clean fclean re
