NAME = philosophers

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCS =	main.c\
		init.c\
		threads.c\
		utils.c\

OBJS = $(SRCS:%.c=%.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(OBJS)

re: fclean all