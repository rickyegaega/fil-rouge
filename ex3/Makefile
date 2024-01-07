NAME = best
SRCS = main3.c score.c
OBJS = $(SRCS:%.c=%.o)
CFLAGS = -lm
CC	 = gcc

all: $(NAME)
	./best "994o4999999 35 x" 6
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

test:	$(NAME)
	./best "6xoxOOOX2xo1ox1oXx2xo4oox4ox 84 o" 5

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
