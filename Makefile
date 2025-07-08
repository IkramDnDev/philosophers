NAME	= philo
CC		= cc
CFLAGS	= -Werror -Wall -Wextra -pthread 

-fsanitize=address -g
SRC_PATH = src/
OBJ_PATH = objects/

SRC		=	main.c \
			parsing.c \
			philo_utils.c \
			libft_utils.c \
			print.c \
			init.c \
			philo_routine.c \
			ft_free.c \
			time.c \
			philo_actions.c \

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INC		= -I ./includes/

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean