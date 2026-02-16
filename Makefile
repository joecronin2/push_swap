CC = cc
CFLAGS = -Wall -Wextra -g -I$(LIBFT_DIR) # TODO

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS += -I$(LIBFT_DIR)

NAME = push_swap
SRCS = main.c stack.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	# cp $(LIBFT) $(NAME)
	# ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS) 
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean 
	$(MAKE) all

.PHONY: all clean fclean re

