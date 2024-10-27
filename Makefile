NAME = philosophers

CC = gcc
CFLAGS = -Wall -Werror -Wextra

PRINTF = ./printf/libftprintf.a

SRCS =	main.c\
		init.c\
		launcher.c\
		utils.c\
		randomizer.c\

OBJS = $(SRCS:%.c=%.o)


all: $(NAME)

$(NAME): $(OBJS)
	@make -s all -C printf
	$(CC) $(CFLAGS) $(OBJS) $(PRINTF) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(PRINTF)
	@make -s clean -C printf

fclean: clean
	@make -s fclean -C printf
	rm -f $(NAME) $(OBJS)

re: fclean all