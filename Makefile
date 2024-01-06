PROGRAM = tttree
SRCS 	= main.c
OBJS	= $(SRCS:%.c=%.o)
CC		= gcc

all:	$(PROGRAM)

test:	$(PROGRAM)
	sh test.sh

$(PROGRAM):	$(OBJS)
	$(CC) $^ -o $@

clean:
	rm -rf $(OBJS)
	rm -rf g1.dot
	rm -rf g2.dot
	rm -rf g1.png
	rm -rf g2.png

fclean: clean
	rm -rf $(PROGRAM)
	rm -rf g.png

re: fclean all
