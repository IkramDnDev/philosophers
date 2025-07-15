NAME	= philo
CC		= cc
CFLAGS	= -Werror -Wall -Wextra -g -fsanitize=thread
SRC_PATH = src
HEADER = include/philo.h

SRCS =	main.c \
		$(SRC_PATH)/parsing.c \
		$(SRC_PATH)/monitor.c \
		$(SRC_PATH)/libft_utils.c \
		$(SRC_PATH)/print.c \
		$(SRC_PATH)/init.c \
		$(SRC_PATH)/philo_routine.c \
		$(SRC_PATH)/ft_free.c \
		$(SRC_PATH)/time.c \

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean