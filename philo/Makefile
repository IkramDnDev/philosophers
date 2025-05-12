NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c parsing.c philo_utils.c
OBJS = $(SRCS:%.c=%.o)

HEADER = philo.h

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJS): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean