NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS =	ft_printf.c\
		ft_pchar.c\
		ft_pstr.c\
		ft_pnbr.c\
		ft_punsigned.c\
		ft_phex.c\
		ft_pvoid.c\


OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
fclean:
	rm -f $(NAME) $(OBJS)
	
re: fclean all

.PHONY: clean fclean all re