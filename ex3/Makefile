NAME = best
SRCS = main3.c score.c
OBJS = $(SRCS:%.c=%.o)
CFLAGS = -lm
CC	 = gcc

all: $(NAME)
	./best "6xoxOOOX2xo1ox1oXx2xo4oox4ox 84 o" 35
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

test:	$(NAME)
	./best "o899999999 11 x" 35

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
